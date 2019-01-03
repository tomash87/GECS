import abc
from collections import OrderedDict
import copy
import math
import scipy.stats
import numpy
import sys
import time
import functools
from subprocess import Popen
import multiprocessing
from db import prepare_connection

__author__ = 'Tomasz Pawlak'


#
# Database part
#

def normalize_data(db):
    cursor = db.cursor()

    problem_mapping = {}

    for (_from, _to) in problem_mapping.items():
        cursor.execute("UPDATE experiments SET in_problem=:to WHERE in_problem=:from", {"from": _from, "to": _to})

    method_mapping = {}

    for (_from, _to) in method_mapping.items():
        cursor.execute("UPDATE experiments SET in_method=:to WHERE in_method=:from", {"from": _from, "to": _to})

    cursor.execute(r'''CREATE TEMP VIEW IF NOT EXISTS experimentStatistics AS
                   SELECT *,
                   SUBSTR(in_problem, 1, LENGTH(in_problem) - 2) AS in_problemDim,
                   SUBSTR(in_problem, 1, LENGTH(in_problem) - 2) || '-' || in_samples  AS problemDimSamples,
                   SUBSTR(in_problem, 1, LENGTH(in_problem) - 2) || '-' || (CASE WHEN in_quadratic IS NULL THEN 'linear' WHEN in_quadratic=1 THEN 'polynomial' END) AS in_problemDimInst,
                   g.bestModelFitness AS trainingFitness,
                   modelVariableCount - benchmarkVariableCount AS diffModelTermCount,
                   modelConstraintCount - benchmarkConstraintCount AS diffModelConstraintCount,
                   syntaxAngle/CAST(MAX(enabledConstraintCount, benchmarkConstraintCount) AS REAL) AS avgAngle,
                   IFNULL(CAST(modelTestTruePositives AS REAL)/CAST(modelTestTruePositives + modelTestFalseNegatives AS REAL), 0.0) AS testSensitivity,
                   IFNULL(CAST(modelTestTrueNegatives AS REAL)/CAST(modelTestTrueNegatives + modelTestFalsePositives AS REAL), 0.0) AS testSpecificity,
                   IFNULL(CAST(modelTestTruePositives + modelTestTrueNegatives AS REAL)/CAST(modelTestTruePositives + modelTestFalsePositives + modelTestFalseNegatives + modelTestTrueNegatives AS REAL), 0.0) AS testAccuracy,
                   IFNULL(CAST(modelTestTruePositives AS REAL)/CAST(modelTestTruePositives + modelTestFalsePositives AS REAL), 0.0) AS testPrecision,
                   IFNULL(CAST(2*modelTestTruePositives AS REAL)/CAST(2*modelTestTruePositives + modelTestFalsePositives + modelTestFalseNegatives AS REAL), 0.0) AS testF,
                   IFNULL(CAST(modelTestTruePositives AS REAL)/(modelTestTruePositives + modelTestFalseNegatives + modelTestFalsePositives), 0.0) AS feasibleJaccard,
                   IFNULL(CAST(modelTestTrueNegatives AS REAL)/(modelTestTrueNegatives + modelTestFalseNegatives + modelTestFalsePositives), 0.0) AS infeasibleJaccard,
                   CASE WHEN in_quadratic IS NULL THEN 'linear' WHEN in_quadratic=1 THEN 'polynomial' END AS instruction
                   FROM experiments e LEFT JOIN generations g ON g.id = (SELECT MAX(id) FROM generations WHERE parent=e.id)''')


def prepare_indexes(db):
    cursor = db.cursor()
    cursor.execute("CREATE INDEX IF NOT EXISTS constraintsParent ON constraints(parent)")
    cursor.execute("CREATE INDEX IF NOT EXISTS variablesParent ON variables(parent)")
    cursor.execute("CREATE INDEX IF NOT EXISTS generationsParentGeneration ON generations(parent, generation)")
    # cursor.execute("CREATE INDEX IF NOT EXISTS fitnessParent ON fitness(parent)")
    cursor.execute("CREATE INDEX IF NOT EXISTS experimentsIn_problemBenchmarkVariableCountIn_samples ON experiments(in_problem, benchmarkVariableCount, in_samples, in_name)")
    cursor.execute("ANALYZE")


def prepare_db(filename="statistics.sqlite"):
    start = time.time()
    db = prepare_connection(filename)
    prepare_indexes(db)
    normalize_data(db)
    print("Database prepared in %.2fs" % (time.time() - start))
    return db


#
# Prameters for statistical objects
#

class ParameterSet:
    def __init__(self, axis=None, plot=None, table=None, analyzer=None):
        self.axis = axis or {}
        self.plot = plot or {}
        self.table = table or {}
        self.analyzer = analyzer or {}


def expand(*parameters):
    if len(parameters) == 0:
        return

    clone = copy.deepcopy(parameters[0])
    for i in range(1, len(parameters)):
        if parameters[i] is None:
            continue
        elif type(parameters[i]) == dict:
            clone.update(parameters[i])
        else:
            clone.axis.update(parameters[i].axis)
            clone.plot.update(parameters[i].plot)
            clone.table.update(parameters[i].table)
            clone.analyzer.update(parameters[i].analyzer)

    return clone


#
# Values of parameters
#

defaults = ParameterSet()
defaults.axis = {
    "xmode=": "normal",  # log
    "ymode=": "normal",  # log
    "xmin=": 0,
    "xmax=": 100,
    "ymin=": 0,
    "ymax=": 1,
    "xtick=": "{}",
    "ytick=": "{}",
}
defaults.plot = {
    "mark repeat=": 15,
}
defaults.table = {
    "cfmode": "pm",  # How to show confidence intervals: none, pm, both, bar
    "barcffullheight": 1.0,  # Value of confidence interval referring to full ceil height
    "content": "data",  # What is content of the table: none, data
    "heatmap": {
        "min": 0.0,
        "max": 1.0,
        "min_color": "red!90!white",
        "max_color": "green",
    },
    "total_row": "ranks",  # Data to put in last row of table; none, ranks
    "number_format": "%.2f",
    "first_column_title": "Problem",
    "border": {"top", "bottom"},
}
defaults.analyzer = {
    "plot_id_x": 0.85,
    "plot_id_y": 0.9,
    "plots_in_row": 3,
    "name_suffix": "",
    "ymax_percentile": 99.0,
    "ymax_cf_percentile": 97.5,
    "best": -1.0E9,  # best value on for a particular criterion (used in ranks) and formatting
    "pcritical": None,  # None, or critical probability for which the test is conclusive (test's p-value is less than this value)
    "novalue": float("nan"), # value inserted in table when query returns none
}

plot_parameters = {
    "ball": ParameterSet(),
    "ball3": ParameterSet(),
    "ball3-linear": ParameterSet(),
    "ball3-polynomial": ParameterSet(),
    "ball4": ParameterSet(),
    "ball5": ParameterSet(),
    "ball5-linear": ParameterSet(),
    "ball5-polynomial": ParameterSet(),
    "ball6": ParameterSet(),
    "ball6-linear": ParameterSet(),
    "ball6-polynomial": ParameterSet(),
    "ball7": ParameterSet(),
    "simplex": ParameterSet(),
    "simplex3": ParameterSet(),
    "simplex3-linear": ParameterSet(),
    "simplex3-polynomial": ParameterSet(),
    "simplex4": ParameterSet(),
    "simplex5": ParameterSet(),
    "simplex5-linear": ParameterSet(),
    "simplex5-polynomial": ParameterSet(),
    "simplex6": ParameterSet(),
    "simplex6-linear": ParameterSet(),
    "simplex6-polynomial": ParameterSet(),
    "simplex7": ParameterSet(),
    "cube": ParameterSet(),
    "cube3": ParameterSet(),
    "cube3-linear": ParameterSet(),
    "cube3-polynomial": ParameterSet(),
    "cube4": ParameterSet(),
    "cube5": ParameterSet(),
    "cube5-linear": ParameterSet(),
    "cube5-polynomial": ParameterSet(),
    "cube6": ParameterSet(),
    "cube6-linear": ParameterSet(),
    "cube6-polynomial": ParameterSet(),
    "cube7": ParameterSet(),
}

series_parameters = {
    "E0": ParameterSet({},{
        "draw=": "magenta",
        "mark=": "triangle*",
        "mark options=": "{fill=magenta, scale=0.5, solid}",
    }),
    "E0R": ParameterSet({},{
        "draw=": "magenta",
        "mark=": "diamond*",
        "dashed": "",
        "mark options=": "{fill=magenta, scale=0.5, solid}",
    }),
    "E1": ParameterSet({},{
        "draw=": "magenta",
        "mark=": "square*",
        "dotted": "",
        "mark options=": "{fill=magenta, scale=0.5, solid}",
    }),
    "E1R": ParameterSet({},{
        "draw=": "cyan",
        "mark=": "triangle*",
        "mark options=": "{fill=cyan, scale=0.5, solid}",
    }),
    "E2": ParameterSet({},{
        "draw=": "cyan",
        "mark=": "diamond*",
        "dashed": "",
        "mark options=": "{fill=cyan, scale=0.5, solid}",
    }),
    "E2R": ParameterSet({},{
        "draw=": "cyan",
        "mark=": "square*",
        "dotted": "",
        "mark options=": "{fill=cyan, scale=0.5, solid}",
    }),
    "K0": ParameterSet({},{
        "draw=": "lime",
        "mark=": "triangle*",
        "mark options=": "{fill=lime, scale=0.5, solid}",
    }),
    "K0R": ParameterSet({},{
        "draw=": "lime",
        "mark=": "diamond*",
        "dashed": "",
        "mark options=": "{fill=lime, scale=0.5, solid}",
    }),
    "K1": ParameterSet({},{
        "draw=": "lime",
        "mark=": "triangle*",
        "mark options=": "{fill=lime, scale=0.5, solid}",
    }),
    "K1R": ParameterSet({},{
        "draw=": "lime",
        "mark=": "diamond*",
        "dashed": "",
        "mark options=": "{fill=lime, scale=0.5, solid}",
    }),
    "K2": ParameterSet({},{
        "draw=": "lime",
        "mark=": "triangle*",
        "mark options=": "{fill=lime, scale=0.5, solid}",
    }),
    "K2R": ParameterSet({},{
        "draw=": "lime",
        "mark=": "diamond*",
        "dashed": "",
        "mark options=": "{fill=lime, scale=0.5, solid}",
    }),
}


class Statistics:
    __metaclass__ = abc.ABCMeta

    def __init__(self, db, query, query_params, stat_params, plot_ids, series, name_template="%(query)s_%(params)s_%(series)s"):
        """query - query name, query_params - dict, series - list"""
        self.db = db
        self.query = queries[query]
        self.params = stat_params
        self.plots = OrderedDict([(k, None) for k in plot_ids])
        self.series = series
        self.name = name_template % dict(query=query,
                                         params="_".join(
                                             str(v)[:20].replace('*', '_').replace('<', '_').replace('/', '_').replace('"', '').replace('=', '') for (k, v) in
                                             sorted(query_params.items())),
                                         series="_".join(str(v)[:20] for v in series))
        self.name = self.name[:120]

        params = expand(defaults, self.params)

        start = time.time()
        sys.stdout.write("Quering for %s... " % self.name)

        # execute queries, obtain data
        for plot_id in self.plots:
            p = copy.deepcopy(query_params)
            p.update({"plot_id": plot_id})
            self.plots[plot_id] = OrderedDict()
            for series in self.series:
                p.update({"series": series})
                cursor = db.cursor()
                q = self.query
                for (k, v) in p.items():
                    q = q.replace("`:" + k + "`", str(v))  # for names of database objects

                cursor.execute(q, p)
                self.plots[plot_id][series] = dict(name=series,
                                                   header=[column[0] for column in cursor.description],
                                                   data=cursor.fetchall())

                if len(self.plots[plot_id][series]["data"]) == 0:
                    print("No data for plot_id/series: %s/%s" % (plot_id, series))
                elif self.plots[plot_id][series]["data"][0][0] is None:
                    # del self.plots[plot_id][series]
                    self.plots[plot_id][series]["data"] = [[params.analyzer["novalue"] for column in cursor.description]]
                    print("Query returned null for plot_id/series: %s/%s" % (plot_id, series))

        print("%.2fs" % (time.time() - start))

    @abc.abstractmethod
    def get_full_document(self):
        raise NotImplementedError("Override me")

    def get_name(self):
        return self.name

    def get_processor(self):
        return None

    def format_name_latex(self, name: str):
        map = { }

        if name in map:
            return map[name]

        if name.startswith("simplex"):
            return "Simp$_%s$" % name[-1:]
        if name.startswith("cube") or name.startswith("simplex") or name.startswith("ball"):
            return "%s%s$_%s$" % (name[:1].upper(), name[1:-1], name[-1:])
        if name[-1:] == 'R':
            return name[:-1]

        return name

    def save(self, filename=None):
        filename = filename or "output/" + self.name + ".tex"

        print("Saving %s..." % self.name)

        file = None
        try:
            doc = self.get_full_document()
            file = open(filename, "w")
            file.write(doc)
        finally:
            if file is not None:
                file.close()


class Plot(Statistics):
    def __init__(self, db, query, query_params, stat_params, plot_ids, series, name_template="%(query)s_%(params)s_%(series)s"):
        super(Plot, self).__init__(db, query, query_params, stat_params, plot_ids, series, name_template)
        self.legend_printed = False

    def get_preamble(self):
        return r'''\documentclass[10pt,a4paper,oneside]{article}
               \usepackage{tikz}
               \usepackage{pgfplots}
               \usepackage{pgfplotstable}
               \usepackage[margin=0cm, left=0cm, paperwidth=14cm, paperheight=20.5cm]{geometry}
               \pgfplotsset{width=4.9cm,height=3.9cm,compat=1.5}
               \pgfplotsset{every axis/.append style={%
                   font=\scriptsize,%
                   draw=black,%
                   thick,%
                   %tick style={ultra thin},%
                   %axis background/.style={fill=red},%
                   axis line style={ultra thin},%
                   enlarge x limits=false,%
                   enlarge y limits=false,%
                   xtick=\empty,%
                   ytick=\empty,%
                   thin%
                   }%
               }%
               \tikzset{every mark/.append style={%
                        scale=0.5,%
                        solid%
			        }%
		       }%
               \pgfplotsset{every y tick label/.append style={%
                       /pgf/number format/fixed%
                   }%
               }%
               \pgfplotsset{every axis legend/.append style={%
                       font=\footnotesize%
                   }%
               }%
               '''

    def get_header(self, params):
        return r''' \begin{document}
                    \begin{center}
                    \tabcolsep=0em
                    \begin{tabular}{%(columns)s}
               ''' % dict(columns="r" * params.analyzer["plots_in_row"])

    def get_footer(self):
        return r''' \end{tabular}
                    \end{center}
                    \begin{center}
                        \vspace{-1em}
                        \ref{Legend}
                   \end{center}
               \end{document}
               '''

    def get_plot(self, plot_id, params):
        """Gets LaTeX code for given plotID and list of series"""
        params = expand(params, plot_parameters[plot_id])
        out = r'''\begin{tikzpicture}
                   %(data)s
                   %(cf)s
                   %(main)s
              \end{tikzpicture}
              ''' % dict(data="\n".join(r"\pgfplotstableread{%s}{\dataTable%s}" % (self.serialize_data(self.plots[plot_id][series], params),
                                                                                   self.escape_name(plot_id + series)) for series in
                                        self.plots[plot_id]),
                         main=self.get_axis(plot_id, params),
                         cf=self.get_cf_axes(plot_id, params))
        return out

    def get_cf_axes(self, plot_id, params):
        if "yMin" not in list(self.plots[plot_id].values())[0]["header"]:
            return ""  # no cf in this plot

        params = expand(params, plot_parameters[plot_id])
        return "\n".join(self.get_cf_axis(plot_id, series, params) for series in self.plots[plot_id])

    def get_cf_axis(self, plot_id, series, params):
        """Gets LaTeX code for confidence interval axis"""
        params = expand(params, series_parameters[series])
        if "xlabel=" in params.axis:
            del (params.axis["xlabel="])
        if "ylabel=" in params.axis:
            del (params.axis["ylabel="])
        if "xtick=" in params.axis:
            del (params.axis["xtick="])
        if "ytick=" in params.axis:
            del (params.axis["ytick="])

        out = r'''\begin{axis}[
                   stack plots=y,
                   area style,
                   %(params)s
              ]
              \addplot[opacity=0]
                  table[x=x, y=yMin]{\dataTable%(data_table)s}
              \closedcycle;
              \addplot[draw=none, opacity=0.5, fill=%(fill)s]
                  table[x=x, y expr=\thisrow{yMax}-\thisrow{yMin}]{\dataTable%(data_table)s}
              \closedcycle;
              \end{axis}
              ''' % dict(params=",\n".join("%s%s" % (k, v) for (k, v) in params.axis.items()),
                         data_table=self.escape_name(plot_id + series),
                         fill="%s!15!white" % params.plot["draw="] if "draw=" in params.plot else "darkgray")

        return out

    def get_axis(self, plot_id, params):
        legend = ""
        if not self.legend_printed:
            self.legend_printed = True
            legend = r'''
                       legend entries={
                           %(legend)s
                       },
                       legend style={cells={anchor=west}},
                       legend to name=Legend,
                       legend columns=%(legend_cols)d,
                       ''' % dict(legend=",\n".join("{%s}" % self.format_name_latex(k) for k in self.series),
                                  legend_cols=self.get_legend_column_number())

        out = r'''\begin{axis}[
                       axis on top,
                       %(params)s,%(legend)sextra description/.code={
                           \node at (%(plot_id_x)f, %(plot_id_y)f) {%(plot_id)s};
                       }
                       ]
                       %(series)s
                  \end{axis}
                  ''' % dict(params=",\n".join("%s%s" % (k, v) for (k, v) in params.axis.items()),
                             legend=legend,
                             plot_id=plot_id,
                             plot_id_x=params.analyzer["plot_id_x"],
                             plot_id_y=params.analyzer["plot_id_y"],
                             series="\n".join(r'''\addplot[%(params)s]
                                                   table[x=x,y=y]{\dataTable%(data_table)s};
                                               ''' % dict(
                                 params=",".join("%s%s" % (k, v) for (k, v) in expand(params, series_parameters[serie]).plot.items()),
                                 data_table=self.escape_name(plot_id + serie)) for serie in self.plots[plot_id]))
        return out

    def get_full_document(self):
        params = expand(defaults, self.params)
        params = self.params

        self.legend_printed = False
        out = self.get_preamble()
        out += self.get_header(params)

        plots_in_row = params.analyzer["plots_in_row"]
        counter = 0
        for plot_id in self.plots:
            params = expand(defaults, self.params)
            params.axis["ymax="] = self.calculate_y_max(plot_id, params)
            if counter % plots_in_row != 0:
                params.axis["ylabel="] = ""
            if counter < len(self.plots) - plots_in_row:
                params.axis["xlabel="] = ""

            out += self.get_plot(plot_id, params)
            counter += 1
            if counter % plots_in_row == 0:
                out += "\\\\\n"
            else:
                out += "&"

        out += self.get_footer()
        return out

    def calculate_y_max(self, plot_id, params):
        params = expand(params, plot_parameters[plot_id])
        values = []
        max_values = []
        for (name, series) in self.plots[plot_id].items():
            header = series["header"]
            data = series["data"]
            if "y" not in header:
                return 1.0
            y_idx = header.index("y")
            yMax_idx = None
            if "yMax" in header:
                yMax_idx = header.index("yMax")

            for row in data:
                if row[y_idx] is not None:
                    values.append(row[y_idx])
                    if yMax_idx is not None:
                        max_values.append(row[yMax_idx])

        if len(values) == 0:
            return 1

        percentile = params.analyzer["ymax_percentile"]
        extra_perc = 0.0
        if percentile > 100.0:
            extra_perc = percentile - 100.0
            percentile = 100.0

        return min(max((1.0 + extra_perc * 0.01) * numpy.percentile(values, percentile),
                       numpy.percentile(max_values, params.analyzer["ymax_cf_percentile"]) if len(max_values) > 0 else 0), 1.0e4)

    def get_legend_column_number(self):
        max_cols = 5
        total = len(self.series)
        rows = int(math.ceil(float(total) / float(max_cols)))
        cols = int(math.ceil(float(total) / float(rows)))
        return cols

    def serialize_data(self, data, params):
        max_value = (params.axis["ymax="] + 1) * 200.0 if "ymax=" in params.axis else 1000.0
        min_value = -max_value
        out = "%(header)s\n" \
              "%(data)s\n" % dict(header="\t".join(data["header"]),
                                  data="\n".join(
                                      "\t".join((str(max(min(value, max_value), min_value)) if value is not None else "0") for value in row) for row
                                      in data["data"]))
        return out

    @staticmethod
    def escape_name(name):
        map = {
            "0": "zero",
            "1": "one",
            "2": "two",
            "3": "three",
            "4": "four",
            "5": "five",
            "6": "six",
            "7": "seven",
            "8": "eight",
            "9": "nine",
            "-": "hyphen",
        }
        return functools.reduce(lambda x, y: x.replace(y, map[y]), map, name)

    def get_processor(self):
        return "pdflatex"


class Table(Statistics):
    def __init__(self, db, query, query_params, stat_params, plot_ids, series, name_template="%(query)s_%(params)s_%(series)s"):
        super(Table, self).__init__(db, query, query_params, stat_params, plot_ids, series, name_template)

    def get_header(self, params):
        return r'''
                \begin{tabular}{l%(column_def)s}
                    %(border_top)s
                    %(column_title)s&%(header)s\\
                    \hline%%
            ''' % dict(column_def=(dict(none="r" * len(self.series),
                                        pm="rl" * len(self.series),
                                        bar="r" * len(self.series),
                                        both="rrl" * len(self.series))[params.table["cfmode"]]),
                       border_top="\\hline%" if "top" in params.table["border"] else "",
                       column_title=params.table["first_column_title"],
                       header=(dict(none="&".join("%s\hspace*{\\fill}" % self.format_name_latex(s) for s in self.series),
                                    pm="&".join("\multicolumn{2}{c}{%s}" % self.format_name_latex(s) for s in self.series),
                                    bar="&".join("%s\hspace*{\\fill}" % self.format_name_latex(s) for s in self.series),
                                    both="&".join("\multicolumn{3}{c}{%s}" % self.format_name_latex(s) for s in self.series))[params.table["cfmode"]]))

    def get_value(self, plot_id, series, params):
        params = expand(params, series_parameters[series["name"]] if series["name"] in series_parameters else None)

        header = series["header"]
        data = series["data"]
        y_idx = header.index("y")
        if "yMin" in header:
            yMin_idx = header.index("yMin")
        if "yMax" in header:
            yMax_idx = header.index("yMax")
        if "pValue" in header:
            pValue_idx = header.index("pValue")

        if len(data) < 1:
            return ""
        elif len(data) > 1:
            print("Too many rows (%d) for series %s" % (len(data), series["name"]))

        if params.analyzer["best"] is not None and data[0][y_idx] is not None:
            best_value = min(abs((s["data"][0][y_idx] if s["data"][0][y_idx] is not None else float("NaN")) - params.analyzer["best"]) for s in self.plots[plot_id].values())
            is_best = abs(data[0][y_idx] - params.analyzer["best"]) == best_value
        else:
            is_best = False

        if params.analyzer["pcritical"] is not None and data[0][pValue_idx] is not None:
            is_conclusive = data[0][pValue_idx] <= params.analyzer["pcritical"]
        else:
            is_conclusive = False

        heatmap = ''
        if params.table["heatmap"] is not None and data[0][y_idx] is not None:
            h_params = params.table["heatmap"]
            transform = h_params["transform"] if "transform" in h_params else lambda x: x
            float_intensity = (transform(data[0][y_idx]) - h_params["min"]) / (h_params["max"] - h_params["min"]) * 100
            intensity = int(float_intensity) if not math.isnan(float_intensity) else 50
            intensity = min(intensity, 100)
            intensity = max(intensity, 0)
            color = "%s!%d!%s" % (h_params["max_color"], intensity, h_params["min_color"])
            heatmap = r'''\cellcolor{%s}''' % color

        out = "%s" % (self.format_number(data[0][y_idx], params))

        if is_best:
            out = "\\mathbf{%s}" % out

        if is_conclusive:
            out = "\\underline{%s}" % out

        out = "$%s$" % out

        if params.table["cfmode"] == "none":
            out = heatmap + out
        elif params.table["cfmode"] == "pm":
            out += r"%s&%s{\tiny$\pm %s$}" % (heatmap, heatmap, self.format_number(0.5 * (float(data[0][yMax_idx]) - float(data[0][yMin_idx])), params))
        elif params.table["cfmode"] == "bar":
            cf = 0.5 * (float(data[0][yMax_idx]) - float(data[0][yMin_idx]))
            # y = abs(float(data[0][y_idx]))
            y = params.table["barcffullheight"]
            height = min(cf / y, 1.0) if y != 0.0 else 0.0  # 0..1
            out += r"%s\,\begin{tikzpicture}[y=0.75em,baseline=1pt]\draw[very thick] (0,0) -- (0,%.2f);\end{tikzpicture}" % (heatmap, height)
        elif params.table["cfmode"] == "both":
            out = r"%(hmap)s~{\tiny$%(left)s \leq $}&%(hmap)s%(value)s&%(hmap)s{\tiny$\leq %(right)s$}~" % dict(
                hmap=heatmap,
                left=self.format_number(data[0][yMin_idx], params),
                value=out,
                right=self.format_number(data[0][yMax_idx], params))

        return out

    def format_number(self, number, params):
        if number is None:
            return ""
        number = float(number)
        if abs(number) > 1.0e4 and not math.isinf(number):
            return "%s10^{%d}" % (r"-1\times" if number < 0.0 else "", int(round(math.log10(abs(number)))))
        elif math.isinf(number):
            return "\infty"
        return params.table["number_format"] % number

    def get_row(self, plot_id, params):
        params = expand(params, plot_parameters[plot_id] if plot_id in plot_parameters else None)
        if params.table["content"] == "data":
            return "%(plot_id)s&%(data)s" % dict(plot_id=self.format_name_latex(plot_id),
                                                 data="&".join(
                                                     self.get_value(plot_id, series, params) for (name, series) in self.plots[plot_id].items()))
        return ""

    def get_footer(self, params):
        out = ''
        if params.table["total_row"] == "ranks":
            columns = dict(none=1, pm=2, bar=1, both=3)[params.table["cfmode"]]
            ranks = self.get_ranks(params)
            out += r'''\hline%%
                    Rank:&%(ranks)s\\
                ''' % dict(ranks="&".join(r"\multicolumn{%d}{c}{%s}" % (columns, self.format_number(r, params)) for r in ranks))
        out += r'''
            %(border_bottom)s
            \end{tabular}
        ''' % dict(border_bottom="\\hline%" if "bottom" in params.table["border"] else "")
        return out

    def get_ranks(self, params):
        ranks = [0.0] * len(list(self.plots.values())[0])
        for (plot_id, series) in self.plots.items():
            tmp_ranks = [float(self.format_number(float(s["data"][0][s["header"].index("y")]), params)) for s in series.values()]
            tmp_ranks = [abs(r - params.analyzer["best"]) for r in tmp_ranks]
            tmp_ranks = scipy.stats.rankdata(tmp_ranks)
            ranks = map(sum, zip(ranks, tmp_ranks))
        ranks = [r / float(len(self.plots)) for r in ranks]
        return ranks

    def get_full_document(self):
        params = expand(defaults, self.params)

        out = self.get_header(params)
        for plot_id in self.plots:
            out += self.get_row(plot_id, params) + "\\\\\n"
        out += self.get_footer(params)
        return out

    def get_processor(self):
        return "tex"


class RTable(Statistics):
    def __init__(self, db, query, query_params, stat_params, plot_ids, series, name_template="%(query)s_%(params)s_%(series)s"):
        super(RTable, self).__init__(db, query, query_params, stat_params, plot_ids, series, name_template)

    def get_full_document(self):
        params = expand(defaults, self.params)

        out = r'''source('../friedman.r', chdir = T)
            methods <- c(%(methods)s)
            problems <- c(%(problems)s)
            Data <- data.frame(
                Table = c(%(data)s),
                Methods = factor(rep(methods, %(problem_count)d)),
                Problems = factor(c(%(problems_rep)s))
            )
            output <- friedman.test.with.post.hoc(Table ~ Methods | Problems, Data, to.print.friedman = F, to.plot.parallel = F, to.plot.boxplot = F)
            source('../friedmanPostAnalysis.r', chdir = T)
            png('%(name)s-friedman.png')
            plot(graph, layout=layout.circle, vertex.size=50, edge.color='Black')
            dev.off()
            sink('%(name)s-friedman.tex')
            cat(paste('Friedman\'s p-value = $', pvalue(output[[1]]), '$', sep=''))
            print(xtable(matrix, digits = 3), type='latex', sanitize.text.function = function(x){x})
            sink()
            ''' % dict(methods=", ".join("'%s'" % self.format_name_latex(s) for s in list(self.plots.values())[0]),
                       problems=", ".join("'%s'" % p for p in self.plots),
                       data=self.serialize_data(params),
                       problem_count=len(self.plots),
                       problems_rep=", ".join("rep(c('%s'), %d)" % (p, len(self.series)) for p in self.plots),
                       name=self.name)
        return out

    def serialize_data(self, params):
        y_idx = list(list(self.plots.values())[0].values())[0]["header"].index("y")
        out = ",".join(
            ",".join(
                "%.13e" % (
                    abs(float(s["data"][0][y_idx]) - params.analyzer["best"]) if params.analyzer["best"] is not None else float(s["data"][0][y_idx]))
                for (n, s) in series.items())
            for (plot_id, series) in self.plots.items())
        return out

    def get_processor(self):
        return "r"

    def format_name_latex(self, name: str):
        name = Statistics.format_name_latex(self, name)
        name = name.replace(r'''\textsc''', r'''\\textsc''')
        return name


class Runner:
    def __init__(self, statistics):
        self.statistics = statistics
        self.processors = {
            "tex": {
                "command": None,
                "arguments": [],
                "extension": ".tex"
            },
            "pdflatex": {
                "command": "pdflatex",
                "arguments": ["-interaction=batchmode"],
                "extension": ".tex"
            },
            "r": {
                "command": "r",
                "arguments": ["--vanilla", "-f"],
                "extension": ".r"
            }
        }

    def run(self):
        processes = []

        for stat in self.statistics:
            params = self.processors[stat.get_processor()]

            filename = stat.get_name() + params["extension"]
            filepath = "output/" + filename
            stat.save(filepath)
            if params["command"] is not None:
                command_line = [params["command"]] + params["arguments"] + [filename]
                processes.append(Popen(command_line, cwd="output"))

                # Wait for running processes (prevent creating too many processes at once)
                while len(processes) >= multiprocessing.cpu_count():
                    time.sleep(0.1)
                    for p in processes:
                        p.poll()
                        if p.returncode is not None:
                            processes.remove(p)

        for p in processes:
            p.wait()


queries = {
    "generational_avg":
        r'''SELECT
                g.generation AS x,
                AVG(`:criterion`) AS y,
                AVG(`:criterion`) - 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMin,
                AVG(`:criterion`) + 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMax
            FROM experimentStatistics e
            JOIN generations g ON e.id=g.parent
            WHERE
                e.in_problemDimInst = :plot_id || '-' || :instruction
                AND e.in_name = :series
                AND e.in_samples = 300
                AND g.generation <= 50
            GROUP BY
                g.generation
            ORDER BY
                g.generation
        ''',
    "final_avg_fixed":
        r'''SELECT
                AVG(`:criterion`) AS y,
                AVG(`:criterion`) - 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMin,
                AVG(`:criterion`) + 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMax
            FROM experimentStatistics e
            WHERE
                e.in_problemDim = :plot_id
                AND e.in_name = :series
                AND e.in_samples = 300
                AND e.instruction = :instruction
            LIMIT 1
        ''',
    "final_avg":
        r'''SELECT
                AVG(`:criterion`) AS y,
                AVG(`:criterion`) - 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMin,
                AVG(`:criterion`) + 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMax,
                1.0 - TTEST(`:criterion`, :mean) AS pValue
            FROM experimentStatistics e
            WHERE
                e.in_problem = :problem
                AND e.in_samples = :plot_id
                AND e.in_name = :method
                AND e.benchmarkVariableCount = :series
                AND e.instruction = :instruction
            LIMIT 1
        ''',
}


def main():
    db = prepare_db("statistics.sqlite")

    dims = [3, 4, 5, 6, 7]
    samples = []
    # samples += [10, 20, 30, 40, 50]
    samples += [100, 200, 300, 400, 500]
    raw_problems = ["ball", "simplex", "cube"]
    problems = ["cube%d" % d for d in dims] + ["simplex%d" % d for d in dims] + ["ball%d" % d for d in dims]
    methods1 = ["E11", "E12", "E13", "EB11", "EB12", "EB13", "K11", "K12", "K13", "KB11", "KB12", "KB13", "E21", "E22", "E23", "EB21", "EB22", "EB23", "K21", "K22", "K23", "KB21", "KB22", "KB23"]
    methods2 = ["E11R", "E12R", "E13R", "EB11R", "EB12R", "EB13R", "K11R", "K12R", "K13R", "KB11R", "KB12R", "KB13R", "E21R", "E22R", "E23R", "EB21R", "EB22R", "EB23R", "K21R", "K22R", "K23R", "KB21R", "KB22R", "KB23R"]

    instructions = ['linear', 'polynomial']

    p_table = ParameterSet(
        analyzer={"best": None, "pcritical": 0.95},
        table={"total_row": "none",
               "first_column_title": "$m$\\textbackslash{}$n$",
               "cfmode": "bar",
               "border": {}})
    p_angle = expand(p_table, ParameterSet(
        analyzer={"best": None, "pcritical": 0.90},  # two-tailed t-test with alpha=0.9 is equivalent to one-tiled with alpha=0.95
        table={
                "barcffullheight": 0.1,
                "total_row": "none",
                "heatmap": {
                   "min": 0.0,
                   "max": math.pi * 0.5,
                   "min_color": "green",
                   "max_color": "red!90!white",
                }
        }
    ))

    p_plot = ParameterSet(
        analyzer={
            "best": 0.0,
            "plot_id_x": 0.8,
            "plot_id_y": 0.9,
            "ymax_percentile": 95.0,
            "ymax_cf_percentile": 92.5,
        },
        axis={
            # "ymode=": "log",
            "ymin=": 0,
            "xmax=": 50,
            "ylabel=": "Mean fitness",
            "xlabel=": "Generations"
        })

    p_table_ex1 = ParameterSet(
        analyzer={
            "best": 1.0,
            "novalue": -1.0,
        },
        table={
            "heatmap": {
                "min": 0.0,
                "max": 1.0,
                "min_color": "red!70!yellow!80!white",
                "max_color": "green!70!lime",
            },
            "cfmode": "bar",
            "barcffullheight": 0.1,
            "border": {},
            "number_format": "%.2f",
            "first_column_title": "\\hspace*{-0.1em}Problem\\hspace*{-0.25em}"
        }
    )

    p_table_ex3_size = expand(p_table_ex1, ParameterSet(
        analyzer={
            "best": 0.0
        },
        table={
            "barcffullheight": 2.0,
        }
    ))

    p_table_ex3_angle = expand(p_table_ex1, ParameterSet(
        analyzer={
            "best": 0.0
        },
        table={
            "barcffullheight": 0.1,
        }
    ))

    p_table_ex3_jaccard = expand(p_table_ex1, ParameterSet(
        analyzer={
            "best": 1.0
        },
        table={
            "barcffullheight": 0.1,
        }
    ))

    plots = []

    for instruction in instructions:
        methods = methods1 if instruction == 'linear' else methods2

        # experiment 1
        # plots.append(Plot(db, "generational_avg", {"criterion": "g.bestModelFitness", "instruction": instruction}, p_plot, problems, methods))
        plots.append(Table(db, "final_avg_fixed", {"criterion": "feasibleJaccard", "instruction": instruction}, p_table_ex1, problems, methods))
        plots.append(RTable(db, "final_avg_fixed", {"criterion": "feasibleJaccard", "instruction": instruction}, p_table_ex1, problems, methods))
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "bestFitness", "instruction": instruction}, p_table_ex1, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "bestFitness", "instruction": instruction}, p_table_ex1, problems, methods))

        for method in []:
            for problem in raw_problems:
                # experiment 2
                plots.append(Table(db, "final_avg", {"problem": problem, "criterion": 'avgAngle', 'method': method, 'instruction': instruction, 'mean': 0.0}, p_angle, samples, dims))
                plots.append(
                    Table(db, "final_avg", {"problem": problem, "criterion": 'diffModelTermCount', 'method': method, 'instruction': instruction, 'mean': 0.0}, p_diff_term, samples, dims))
                plots.append(
                    Table(db, "final_avg", {"problem": problem, "criterion": 'diffModelConstraintCount', 'method': method, 'instruction': instruction, 'mean': 0.0}, p_diff, samples, dims))
                plots.append(Table(db, "final_avg", {"problem": problem, "criterion": 'feasibleJaccard', 'method': method, 'instruction': instruction, 'mean': 1.0}, p_jaccard, samples, dims))
                plots.append(Table(db, "final_avg", {"problem": problem, "criterion": 'infeasibleJaccard', 'method': method, 'instruction': instruction, 'mean': 1.0}, p_testset, samples, dims))
                plots.append(Table(db, "final_avg", {"problem": problem, "criterion": 'testSensitivity', 'method': method, 'instruction': instruction, 'mean': 1.0}, p_testset, samples, dims))
                plots.append(Table(db, "final_avg", {"problem": problem, "criterion": 'testPrecision', 'method': method, 'instruction': instruction, 'mean': 1.0}, p_testset, samples, dims))
                plots.append(Table(db, "final_avg", {"problem": problem, "criterion": 'testAccuracy', 'method': method, 'instruction': instruction, 'mean': 1.0}, p_testset, samples, dims))

        # plots.append(Table(db, "final_avg_fixed", {"criterion": "enabledConstraintCount", "instruction": instruction}, p_table_ex3_size, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "enabledConstraintCount", "instruction": instruction}, p_table_ex3_size, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "avgAngle", "instruction": instruction}, p_table_ex3_angle, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "avgAngle", "instruction": instruction}, p_table_ex3_angle, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "feasibleJaccard", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "feasibleJaccard", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "testPrecision", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "testPrecision", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "testSensitivity", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "testSensitivity", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "enabledConstraintCount", "instruction": instruction}, p_table_ex3_size, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "enabledConstraintCount", "instruction": instruction}, p_table_ex3_size, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "avgAngle", "instruction": instruction}, p_table_ex3_angle, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "avgAngle", "instruction": instruction}, p_table_ex3_angle, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "feasibleJaccard", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "feasibleJaccard", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "testPrecision", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "testPrecision", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        #
        # plots.append(Table(db, "final_avg_fixed", {"criterion": "testSensitivity", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))
        # plots.append(RTable(db, "final_avg_fixed", {"criterion": "testSensitivity", "instruction": instruction}, p_table_ex3_jaccard, problems, methods))

    runner = Runner(plots)
    runner.run()

if __name__ == "__main__":
    main()
