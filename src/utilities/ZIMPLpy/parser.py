import ply.lex as lex


# TODO: incomplete
class Model:
    def __init__(self):
        self.numbs = dict()
        self.strgs = dict()
        self.bools = dict()
        self.sets = dict()
        self.vars = dict()

    def is_defined(self, symbol):
        return symbol in self.numbs or symbol in self.strgs or symbol in self.bools or symbol in self.sets or symbol in self.vars

    def is_initialized(self, symbol):
        if symbol in self.numbs:
            return self.numbs[symbol] is not None
        if symbol in self.strgs:
            return self.numbs[symbol] is not None
        if symbol in self.bools:
            return self.numbs[symbol] is not None
        if symbol in self.sets:
            return self.numbs[symbol] is not None
        if symbol in self.vars:
            return self.numbs[symbol] is not None
        return False


class Lexer:
    tokens = (
        'POW',
        'ASGN',
        'CMP_EQ',
        'CMP_LE',
        'CMP_GE',
        'CMP_LT',
        'CMP_GT',
        'CMP_NE',
        'FAC',
        'NOT',
        'AND',
        'OR',
        'XOR',
        'DECLSET',
        'DECLPAR',
        'DECLVAR',
        'DECLMAX',
        'DECLMIN',
        'DECLSUB',
        'DECLSOS',
        'DEFNUMB',
        'DEFSTRG',
        'DEFBOOL',
        'DEFSET',
        'IN',
        'WITH',
        'DO',
        'BINARY',
        'INTEGER',
        'REAL',
        'SUM',
        'PROD',
        'FORALL',
        'EXISTS',
        'VIF',
        'IF',
        'THEN',
        'ELSE',
        'END',
        'TO',
        'UNTIL',
        'BY',
        'UNION',
        'INTER',
        'SYMDIFF',
        'CROSS',
        'PROJ',
        'WITHOUT',
        'MOD',
        'DIV',
        'MIN',
        'MAX',
        'ARGMIN',
        'ARGMAX',
        'READ',
        'AS',
        'SKIP',
        'USE',
        'COMMENT',
        'SCALE',
        'SEPARATE',
        'CHECKONLY',
        'INDICATOR',
        'CARD',
        'ABS',
        'VABS',
        'SGN',
        'ROUND',
        'FLOOR',
        'CEIL',
        'LOG',
        'LN',
        'EXP',
        'SQRT',
        'SIN',
        'COS',
        'TAN',
        'ASIN',
        'ACOS',
        'ATAN',
        'POWER',
        'SGNPOW',
        'PRIORITY',
        'STARTVAL',
        'DEFAULT',
        'SUBSETS',
        'POWERSET',
        'INDEXSET',
        'PRINT',
        'CHECK',
        'INFTY',
        'RANDOM',
        'ORD',
        'TYPE1',
        'TYPE2',
        'IMPLICIT',
        'LENGTH',
        'SUBSTR',
        'MATCH',
        'NUMB',
        # extra tokens:
        'ID',
        #'DEFNAME',
        #'NUMBSYM',
        #'STRGSYM',
        #'VARSYM',
        #'SETSYM',
        #'NUMBDEF',
        #'STRGDEF',
        #'BOOLDEF',
        #'SETDEF'
    )

    t_POW = r'\*\*|\^'
    t_ASGN = r':='
    t_CMP_EQ = r'=='
    t_CMP_LE = r'<='
    t_CMP_GE = r'>='
    t_CMP_LT = r'<'
    t_CMP_GT = r'>'
    t_CMP_NE = r'!='
    t_FAC = r'!'
    t_NOT = r'not'
    t_AND = r'and'
    t_OR = r'or'
    t_XOR = r'xor'
    t_IN = r'in'
    t_WITH = r'with|\|'
    t_DO = r'do|:'
    t_BINARY = r'binary'
    t_INTEGER = r'integer'
    t_REAL = r'real'
    t_SUM = r'sum'
    t_PROD = r'prod'
    t_FORALL = r'forall'
    t_EXISTS = r'exists'
    t_VIF = r'vif'
    t_IF = r'if'
    t_THEN = r'then'
    t_ELSE = r'else'
    t_END = r'end'
    t_TO = r'to'
    t_UNTIL = r'\.\.'
    t_BY = r'by'
    t_UNION = r'union'
    t_INTER = r'inter'
    t_SYMDIFF = r'symdiff'
    t_CROSS = r'cross'
    t_PROJ = r'proj'
    t_WITHOUT = r'without|\\'
    t_MOD = r'mod|modulo'
    t_DIV = r'div'
    t_MIN = r'min'
    t_MAX = r'max'
    t_ARGMIN = r'argmin'
    t_ARGMAX = r'argmax'
    t_READ = r'read'
    t_AS = r'as'
    t_SKIP = r'skip'
    t_USE = r'use'
    t_COMMENT = r'comment'
    t_SCALE = r'scale'
    t_SEPARATE = r'separate'
    t_CHECKONLY = r'checkonly'
    t_INDICATOR = r'indicator'
    t_CARD = r'card'
    t_ABS = r'abs'
    t_VABS = r'vabs'
    t_SGN = r'sgn'
    t_ROUND = r'round'
    t_FLOOR = r'floor'
    t_CEIL = r'ceil'
    t_LOG = r'log'
    t_LN = r'ln'
    t_EXP = r'exp'
    t_SQRT = r'sqrt'
    t_SIN = r'sin'
    t_COS = r'cos'
    t_TAN = r'tan'
    t_ASIN = r'asin'
    t_ACOS = r'acos'
    t_ATAN = r'atan'
    t_POWER = r'pow'
    t_SGNPOW = r'sgnpow'
    t_PRIORITY = r'priority'
    t_STARTVAL = r'startval'
    t_DEFAULT = r'default'
    t_SUBSETS = r'subsets'
    t_POWERSET = r'powerset'
    t_INDEXSET = r'indexset'
    t_PRINT = r'print'
    t_CHECK = r'check'
    t_INFTY = r'infinity'
    t_RANDOM = r'random'
    t_ORD = r'ord'
    t_TYPE1 = r'type1'
    t_TYPE2 = r'type2'
    t_IMPLICIT = r'implicit'
    t_LENGTH = r'length'
    t_SUBSTR = r'substr'
    t_MATCH = r'match'

    def t_DECLSET(self, t):
        r'set'
        self.yydecl = 'DECLSET'
        return t

    def t_DECLPARAM(self, t):
        r'param'
        self.yydecl = 'DECLPARAM'
        return t

    def t_DECLVAR(self, t):
        r'var'
        self.yydecl = 'DECLVAR'
        return t

    def t_DECLMAX(self, t):
        r'maximize'
        self.yydecl = 'DECLMAX'
        return t

    def t_DECLMIN(self, t):
        r'minimize'
        self.yydecl = 'DECLMIN'
        return t

    def t_DECLSUB(self, t):
        r'subto'
        self.yydecl = 'DECLSUB'
        return t

    def t_DECLSOS(self, t):
        r'sos'
        self.yydecl = 'DECLSOS'
        return t

    def t_DEFNUMB(self, t):
        r'defnumb'
        self.yydecl = 'DEFNUMB'
        return t

    def t_DEFSTRG(self, t):
        r'defstrg'
        self.yydecl = 'DEFSTRG'
        return t

    def t_DEFBOOL(self, t):
        r'defbool'
        self.yydecl = 'DEFBOOL'
        return t

    def t_DEFSET(self, t):
        r'defset'
        self.yydecl = 'DEFSET'
        return t

    def t_NUMB(self, t):
        r'([0-9]+("."[0-9]+)?([eEdD][-+]?[0-9]+)?)|("."[0-9]+([eEdD][-+]-?[0-9]+)?)'
        t.value = float(t.value)
        return t

    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += len(t.value)

    def t_ID(self, t):
        r'[A-Za-z_][A-Za-z0-9_]*'
        if t.value in {'DECLSUB', 'DECLMIN', 'DECLMAX', 'DECLSOS'}:
            # If it is sure that this is the name for a constraint or
            # objective, or sos, we do not need to lookup the name.
            yydecl = 0
        elif t.value in {'DECLSET', 'DECLPAR', 'DECLVAR', 'DEFNUMB', 'DEFSTRG', 'DEFBOOL', 'DEFSET'}:
            if self.model.is_defined(t.value):
                raise ValueError("Redefinition of %s in line %d." % (t.value, t.lexer.lineno))
            what = self.yydecl
            self.yydecl = 0

            if what == 'DEFNUMB':
                self.model.numbs[t.value] = None
                t.value = (t.value, 'DEFNAME')
                return t
            elif what == 'DEFSTRG':
                self.model.strgs[t.value] = None
                t.value = (t.value, 'DEFNAME')
                return t
            elif what == 'DEFBOOL':
                self.model.bools[t.value] = None
                t.value = (t.value, 'DEFNAME')
                return t
            elif what == 'DEFSET':
                self.model.sets[t.value] = None
                t.value = (t.value, 'DEFNAME')
                return t
        else:
            assert self.yydecl == 0
            if self.model.is_initialized(t.value):
                if t.value in self.model.numbs:
                    t.value = (t.value, "NUMBSYM")
                    return t
                elif t.value in self.model.strgs:
                    t.value = (t.value, "STRGSYM")
                    return t
                elif t.value in self.model.vars:
                    t.value = (t.value, "")


    def __init__(self):
        self.yydecl = 0
        self.model = Model()