import abc
import os
import re
import sqlite3
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
        cursor.execute("UPDATE experiments SET problem=:to WHERE problem=:from", {"from": _from, "to": _to})

    name_mapping = {}

    for (_from, _to) in name_mapping.items():
        cursor.execute("UPDATE experiments SET name=:to WHERE name=:from", {"from": _from, "to": _to})

    try:
        cursor.execute("ALTER TABLE parameters ADD COLUMN PROBLEM NUMERIC NULL")
        cursor.execute("ALTER TABLE parameters ADD COLUMN TRAINING_SIZE NUMERIC NULL")
    except:
        pass
    cursor.execute("SELECT id, EXTRA_PARAMETERS FROM parameters WHERE PROBLEM IS NULL OR TRAINING_SIZE IS NULL")
    extra_params_parser = re.compile(r"(?P<param>[a-zA-Z0-9_]+)='?(?P<value>[a-zA-Z0-9_]+)'?")
    for row in cursor.fetchall():
        params = dict(extra_params_parser.findall(row[1]))
        params["id"] = row[0]
        cursor.execute("UPDATE parameters SET PROBLEM=:PROBLEM, TRAINING_SIZE=:TRAINING_SIZE WHERE id=:id", params)
    try:
        cursor.execute("COMMIT")
    except:
        pass

    cursor.execute(r'''CREATE TEMP VIEW IF NOT EXISTS experimentStat AS
                       SELECT *
                       FROM experiments e 
                       LEFT JOIN parameters p ON e.id = p.parent
                       LEFT JOIN generations g ON e.id = g.parent
                       WHERE g.end = 0 
                       AND e.error_exctype IS NULL''')

    cursor.execute(r'''CREATE TEMP VIEW IF NOT EXISTS experimentFinalStat AS
                   SELECT * 
                   FROM experiments e 
                   LEFT JOIN parameters p ON e.id = p.parent
                   LEFT JOIN generations g ON e.id = g.parent
                   WHERE g.end = 1 
                   AND e.error_exctype IS NULL''')


def prepare_indexes(db):
    cursor = db.cursor()
    cursor.execute("CREATE INDEX IF NOT EXISTS parametersParentNameProblemTrainingSize ON parameters(parent, EXPERIMENT_NAME, PROBLEM, TRAINING_SIZE)")
    cursor.execute("CREATE INDEX IF NOT EXISTS generationsParentEnd ON generations(parent, end)")
    cursor.execute("CREATE INDEX IF NOT EXISTS generationsParentEndTotalTime ON generations(parent, end, TOTAL_TIME)")
    cursor.execute("ANALYZE")


def prepare_db(filename="../results/results.sqlite") -> sqlite3.Connection:
    start = time.time()
    db = prepare_connection(filename)
    normalize_data(db)
    prepare_indexes(db)
    print("Database prepared in %.2fs" % (time.time() - start))
    return db


#
# Parameters for statistical objects
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
    "xmax=": 60,
    "ymin=": 0,
    "ymax=": None,
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
        "min_color": "red!70!yellow!80!white",
        "max_color": "green!70!lime",
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
    "best": 1.0E9,  # best value on a particular criterion (used in ranks) and formatting
    "pcritical": None,  # None, or critical probability for which the test is conclusive (test's p-value is less than this value)
    "novalue": float("nan"),  # value inserted in table when query returns none
}

plot_parameters = {
    "chvatal_diet": ParameterSet(),
    "facility_location": ParameterSet(),
    "queens1": ParameterSet(),
    "queens2": ParameterSet(),
    "queens3": ParameterSet(),
    "queens4": ParameterSet(),
    "queens5": ParameterSet(),
    "steinerbaum": ParameterSet(),
    "tsp": ParameterSet(),
}

series_parameters = {
    "SS": ParameterSet({}, {
        "draw=": "magenta",
        "mark=": "triangle*",
        "mark options=": "{fill=magenta, scale=0.6, solid}",
    }),
    "SI": ParameterSet({}, {
        "draw=": "magenta",
        "mark=": "asterisk",
        "mark options=": "{fill=magenta, scale=0.6, solid}",
    }),
    "SC": ParameterSet({}, {
        "draw=": "magenta",
        "mark=": "diamond*",
        "mark options=": "{fill=magenta, scale=0.6, solid}",
    }),
    "V1S": ParameterSet({}, {
        "draw=": "cyan",
        "dashed": "",
        "mark=": "triangle*",
        "mark options=": "{fill=cyan, scale=0.6, solid}",
    }),
    "V1I": ParameterSet({}, {
        "draw=": "cyan",
        "dashed": "",
        "mark=": "asterisk",
        "mark options=": "{fill=cyan, scale=0.6, solid}",
    }),
    "V1C": ParameterSet({}, {
        "draw=": "cyan",
        "dashed": "",
        "mark=": "diamond*",
        "mark options=": "{fill=cyan, scale=0.6, solid}",
    }),
    "F2S": ParameterSet({}, {
        "draw=": "green!80!lime",
        "densely dotted": "",
        "mark=": "triangle*",
        "mark options=": "{fill=green!80!lime, scale=0.6, solid}",
    }),
    "F2I": ParameterSet({}, {
        "draw=": "green!80!lime",
        "densely dotted": "",
        "mark=": "asterisk",
        "mark options=": "{fill=green!80!lime, scale=0.6, solid}",
    }),
    "F2C": ParameterSet({}, {
        "draw=": "green!80!lime",
        "densely dotted": "",
        "mark=": "diamond*",
        "mark options=": "{fill=green!80!lime, scale=0.6, solid}",
    }),
    "300x3": ParameterSet({}, {
        "draw=": "magenta",
        "mark=": "triangle*",
        "mark options=": "{fill=magenta, scale=0.6, solid}",
    }),
    "300x5": ParameterSet({}, {
        "draw=": "magenta",
        "mark=": "asterisk",
        "mark options=": "{fill=magenta, scale=0.6, solid}",
    }),
    "300x7": ParameterSet({}, {
        "draw=": "magenta",
        "mark=": "diamond*",
        "mark options=": "{fill=magenta, scale=0.6, solid}",
    }),
    "500x3": ParameterSet({}, {
        "draw=": "cyan",
        "densely dashed": "",
        "mark=": "triangle*",
        "mark options=": "{fill=cyan, scale=0.6, solid}",
    }),
    "500x5": ParameterSet({}, {
        "draw=": "cyan",
        "densely dashed": "",
        "mark=": "asterisk",
        "mark options=": "{fill=cyan, scale=0.6, solid}",
    }),
    "500x7": ParameterSet({}, {
        "draw=": "cyan",
        "densely dashed": "",
        "mark=": "diamond*",
        "mark options=": "{fill=cyan, scale=0.6, solid}",
    }),
    "700x3": ParameterSet({}, {
        "draw=": "green!80!lime",
        "densely dotted": "",
        "mark=": "triangle*",
        "mark options=": "{fill=green!80!lime, scale=0.6, solid}",
    }),
    "700x5": ParameterSet({}, {
        "draw=": "green!80!lime",
        "densely dotted": "",
        "mark=": "asterisk",
        "mark options=": "{fill=green!80!lime, scale=0.6, solid}",
    }),
    "700x7": ParameterSet({}, {
        "draw=": "green!80!lime",
        "densely dotted": "",
        "mark=": "diamond*",
        "mark options=": "{fill=green!80!lime, scale=0.6, solid}",
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
        sys.stdout.write("Querying for %s... " % self.name)

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
        map = {"chvatal_diet": "diet",
               "facility_location": "facility"}

        if name in map:
            return map[name]

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
               \pgfplotsset{width=4.9cm,height=3.9cm,compat=1.15}
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
                             plot_id=self.format_name_latex(plot_id),
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
        # params = self.params  # HACK: ?

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
        if "ymax=" in params.axis and params.axis["ymax="] is not None and params.axis["ymax="] != "":
            return params.axis["ymax="]

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
        max_value = (params.axis["ymax="] + 3) * 1000.0 if "ymax=" in params.axis else 1000.0
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
            "_": "lowline",
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

        out = r'''source('%(dir)s/friedman.r', chdir = T)
            methods <- c(%(methods)s)
            problems <- c(%(problems)s)
            Data <- data.frame(
                Table = c(%(data)s),
                Methods = factor(rep(methods, %(problem_count)d)),
                Problems = factor(c(%(problems_rep)s))
            )
            output <- friedman.test.with.post.hoc(Table ~ Methods | Problems, Data, to.print.friedman = F, to.plot.parallel = F, to.plot.boxplot = F)
            source('%(dir)s/friedmanPostAnalysis.r', chdir = T)
            png('%(name)s-friedman.png')
            plot(graph, layout=layout.circle, vertex.size=50, edge.color='Black')
            dev.off()
            sink('%(name)s-friedman.tex')
            cat(paste('Friedman\'s p-value = $', pvalue(output[[1]]), '$', sep=''))
            print(xtable(matrix, digits = 3), type='latex', sanitize.text.function = function(x){x})
            sink()
            ''' % dict(dir=os.path.dirname(__file__),
                       methods=", ".join("'%s'" % self.format_name_latex(s) for s in list(self.plots.values())[0]),
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
            filepath = "../output/" + filename
            stat.save(filepath)
            if params["command"] is not None:
                command_line = [params["command"]] + params["arguments"] + [filename]
                processes.append(Popen(command_line, cwd="../output"))

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
                gen AS x,
                AVG(`:criterion`) AS y,
                AVG(`:criterion`) - 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMin,
                AVG(`:criterion`) + 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMax
            FROM experimentStat
            WHERE
                EXPERIMENT_NAME = :series
                AND PROBLEM = :plot_id
                AND TRAINING_SIZE IN (53, 92, 300)  -- no problem has more than one of these values
            GROUP BY
                gen
            ORDER BY
                gen
        ''',
    "time_avg":
        r'''SELECT
                x,
                AVG(y) AS y,
                AVG(y) - 1.959963985 * SQRT((AVG(y * y) - AVG(y) * AVG(y))/CAST(COUNT(y) AS REAL)) AS yMin,
                AVG(y) + 1.959963985 * SQRT((AVG(y * y) - AVG(y) * AVG(y))/CAST(COUNT(y) AS REAL)) AS yMax
            FROM 
                (SELECT 
                    e1.id,
                    e1.total_time AS x, 
                    MAX(e2.`:criterion`) AS y  -- last value from e2.`:criterion` (for last generation finished at time e1.total_time)
                FROM
                experimentStat e1 CROSS JOIN experimentStat e2
                WHERE
                    e1.EXPERIMENT_NAME = :series
                    AND e1.PROBLEM = :plot_id
                    AND e1.TRAINING_SIZE IN (53, 92, 300)  -- no problem has more than one of these values
                    AND e2.EXPERIMENT_NAME = :series
                    AND e2.PROBLEM = :plot_id
                    AND e2.TRAINING_SIZE IN (53, 92, 300)  -- no problem has more than one of these values
                    AND e1.TOTAL_TIME >= e2.TOTAL_TIME
                GROUP BY
                    e1.id, e1.gen, e2.id
                )
            WHERE x <= 1200
            GROUP BY
                id, x
            HAVING COUNT(*) >= 10
            ORDER BY
                x
        ''',
    "final_avg_fixed":
        r'''SELECT
                AVG(`:criterion`) AS y,
                AVG(`:criterion`) - 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMin,
                AVG(`:criterion`) + 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMax
            FROM experimentFinalStat
            WHERE
                PROBLEM = :plot_id
                AND EXPERIMENT_NAME = :series
                AND TRAINING_SIZE IN (53, 92, 300)  -- no problem has more than one of these values
            LIMIT 1
        ''',
    "final_avg":
        r'''SELECT
                AVG(`:criterion`) AS y,
                AVG(`:criterion`) - 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMin,
                AVG(`:criterion`) + 1.959963985 * SQRT((AVG(`:criterion` * `:criterion`) - AVG(`:criterion`) * AVG(`:criterion`))/CAST(COUNT(`:criterion`) AS REAL)) AS yMax
                --TTEST(`:criterion`, GROUND_TRUTH_TEST_FITNESS) AS pValue
            FROM experimentFinalStat
            WHERE
                PROBLEM = :plot_id
                AND TRAINING_SIZE = :series
                AND EXPERIMENT_NAME = '700x5'
            LIMIT 1
        ''',
}


def main():
    db = prepare_db("../results/results.sqlite")

    problems = ["chvatal_diet", "facility_location", "queens1", "queens2", "queens3", "queens4", "queens5", "steinerbaum", "tsp"]
    training_sizes = {p: [100, 200, 300, 400, 500] for p in problems}
    training_sizes["queens1"] = [92]
    training_sizes["steinerbaum"] = [53]

    cx = ["S", "V1", "F2"]
    mt = ["S", "I", "C"]
    ps = ["300", "500", "700"]
    ts = ["3", "5", "7"]

    series = {'tuning': [], 'tuning2': [], 'scaling': []}
    # tuning pass 1: cx * mt
    series['tuning'] += [c + m for c in cx for m in mt]

    # tuning pass 2: ps * ts
    series['tuning2'] += ["%sx%s" % (pop, t) for pop in ps for t in ts]

    # scaling
    series['scaling'] += [100, 200, 300, 400, 500]
    problems_scaling = [p for p in problems if p not in {"queens1", "steinerbaum"}]

    p_plot = ParameterSet(
        analyzer={
            "best": 1.0,
            "plot_id_x": 0.76,
            "plot_id_y": 0.10,
            # "ymax_percentile": 100.0,
            # "ymax_cf_percentile": 100.0
        },
        plot={
            "mark repeat=": 10,
        },
        axis={
            # "ymode=": "log",
            "ymin=": "",
            "ymax=": 1.01,
            "xmax=": 60,
            "ylabel=": "Mean best fitness",
            "xlabel=": "Generations"
        })

    p_time = expand(p_plot, ParameterSet(
        plot={
            "mark repeat=": 15,
        },
        axis={
            "xmin=": 10,
            "xmax=": "",
            # "xmode=": "log",
            "xlabel=": "Time",
        }
    ))

    p_table = ParameterSet(
        analyzer={
            "best": 1.0,
            "novalue": -1.0,
        },
        table={
            "heatmap": {
                "min": 0.4,
                "max": 1.0,
                "min_color": "red!70!yellow!80!white",
                "max_color": "green!70!lime",
            },
            "cfmode": "bar",
            "barcffullheight": 0.1,
            "number_format": "%.2f",
            "first_column_title": "\\hspace*{-0.1em}Problem\\hspace*{-0.25em}"
        }
    )

    plots = []

    # plots.append(Plot(db, "time_avg", {"criterion": "best_fitness"}, p_time, problems, series["tuning"]))
    # plots.append(Plot(db, "time_avg", {"criterion": "best_fitness"}, p_time, problems, series["tuning2"]))

    plots.append(Plot(db, "generational_avg", {"criterion": "best_fitness"}, p_plot, problems, series["tuning"]))
    plots.append(Plot(db, "generational_avg", {"criterion": "best_fitness"}, p_plot, problems, series["tuning2"]))

    plots.append(Table(db, "final_avg_fixed", {"criterion": "best_fitness"}, p_table, problems, series["tuning"]))
    plots.append(Table(db, "final_avg_fixed", {"criterion": "best_fitness"}, p_table, problems, series["tuning2"]))
    plots.append(Table(db, "final_avg_fixed", {"criterion": "test_fitness"}, p_table, problems, series["tuning"]))
    plots.append(Table(db, "final_avg_fixed", {"criterion": "test_fitness"}, p_table, problems, series["tuning2"]))

    plots.append(RTable(db, "final_avg_fixed", {"criterion": "best_fitness"}, p_table, problems, series["tuning"]))
    plots.append(RTable(db, "final_avg_fixed", {"criterion": "best_fitness"}, p_table, problems, series["tuning2"]))
    plots.append(RTable(db, "final_avg_fixed", {"criterion": "test_fitness"}, p_table, problems, series["tuning"]))
    plots.append(RTable(db, "final_avg_fixed", {"criterion": "test_fitness"}, p_table, problems, series["tuning2"]))

    # plots.append(Table(db, "final_avg", {"criterion": "best_fitness"}, p_table, problems_scaling, series["scaling"]))
    # plots.append(Table(db, "final_avg", {"criterion": "best_fitness"}, p_table, problems_scaling, series["scaling"]))
    # plots.append(Table(db, "final_avg", {"criterion": "test_fitness"}, p_table, problems_scaling, series["scaling"]))
    # plots.append(Table(db, "final_avg", {"criterion": "test_fitness"}, p_table, problems_scaling, series["scaling"]))
    #
    # plots.append(Plot(db, "generational_avg", {"criterion": "best_fitness"}, p_plot, problems_scaling, series["scaling"]))

    db.close()
    runner = Runner(plots)
    runner.run()


if __name__ == "__main__":
    main()
