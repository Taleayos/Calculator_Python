
class Validation:

    def __init__(self):
        self.res = True
        self.flag_bracket = 0
        self.ptr_ch = ' '
        self.flag_point = 0
        self.i = 0
    def is_operator(self, l: str):
        return l in ["+", "-", "/", "*", "^"]


    def validation(self, string: str):
        n = len(string)
        while self.i != n:
            if string[self.i].isnumeric() or string[self.i] == 'x':
                if self.ptr_ch == ' ' or self.ptr_ch.isnumeric() or self.is_operator(self.ptr_ch) > 0 or self.ptr_ch in ['(', '.', 'e']:
                    self.ptr_ch = string[self.i]
                    self.i += 1
                    if self.i == n and self.flag_point != 0:
                        self.flag_point -= 1
                        # self.i -= 1
                else:
                    self.res = False
            elif string[self.i] == '-' or string[self.i] == '+':
                self.MPCheck(string, n)
            elif self.is_operator(string[self.i]) > 0:
                self.OperCheck(string, n)
            elif string[self.i] == '.':
                self.DotCheck(string)
            elif self.IsFunction(string[self.i]) and not self.IsMod(string):
                self.FunkCheck(string)
            elif self.IsFunction(string[self.i]) and self.IsMod(string):
                self.ModCheck(string, n)
            elif string[self.i] == '(':
                self.OpenBrackCheck(string)
            elif string[self.i] == ')':
                self.CloseBrackCheck(string)
            elif string[self.i] == 'e':
                self.ECheck(string)
            elif string[self.i] == ' ':
                self.i += 1
            else:
                self.res = False
            if self.res == False:
                return self.res
        if self.flag_bracket != 0:
            self.res = False
        if self.flag_point != 0:
            self.res = False
        return self.res

    def MPCheck(self, string: str, n: int):
        if self.ptr_ch in [' ', '(', 'x', ')', 'e'] or self.ptr_ch.isnumeric():
            if self.i + 1 == n:
                self.res = False
            else:
                self.ptr_ch = string[self.i]
                self.i += 1
                if self.flag_point != 0:
                    self.flag_point -= 1
            if self.flag_point != 0:
                self.res = False
        else:
            self.res = False


    def OperCheck(self, string: str, n):
        if self.ptr_ch in [' ', 'x', ')'] or self.ptr_ch.isnumeric() and self.i > 0:
            self.i += 1
            if self.i == n:
                self.res = False
            else:
                self.ptr_ch = string[self.i - 1]
                if self.flag_point != 0:
                    self.flag_point -= 1
            if self.flag_point != 0:
                self.res = False
        else:
            self.res = False


    def DotCheck(self, string: str):
        if self.ptr_ch.isnumeric():
            self.i += 1
            if string[self.i].isnumeric():
                self.ptr_ch = string[self.i - 1]
                self.flag_point += 1
            else:
                self.res = False
        else:
            self.res = False


    def IsFunction(self, string: str):
        return string in ['s', 'c', 'm', 't', 'a', 'l']


    def IsMod(self, string: str):
        new_string = string[self.i:]
        return new_string.startswith("mod")


    def FunkCheck(self, string: str):
        new_string = string[self.i:]
        if self.ptr_ch in [' ', '('] or self.is_operator(self.ptr_ch) > 0:
            if new_string.startswith('cos(') or new_string.startswith('sin(') or new_string.startswith('tan(') or new_string.startswith('log('):
                self.ptr_ch = '('
                self.i += 4
                self.flag_bracket += 1
            elif new_string.startswith('sqrt(') or new_string.startswith('acos(') or new_string.startswith('asin(') or new_string.startswith('atan('):
                self.ptr_ch = '('
                self.i += 5
                self.flag_bracket += 1
            elif new_string.startswith('ln('):
                self.ptr_ch = '('
                self.i += 3
                self.flag_bracket += 1
            else:
                self.res = False
        else:
            self.res = False


    def ModCheck(self, string: str, n):
        if self.ptr_ch.isnumeric() or self.ptr_ch == 'x':
            if self.i + 3 == n:
                self.res = False
            elif ((string[self.i + 3].isnumeric() and string[self.i + 3] != '0') or (
                    string[self.i + 3] == ' ' and string[self.i + 4].isnumeric()) or string[self.i + 3] == 'x'
                    or (string[self.i + 3] == ' ' and self.i + 4 != n and string[self.i + 4] == 'x')):
                self.ptr_ch = ' '
                self.i += 3
                if (self.flag_point != 0):
                    self.res = False

            else:
                self.res = False
        else:
            self.res = False

    def OpenBrackCheck(self, string: str):
        if self.ptr_ch == ' ' or self.is_operator(self.ptr_ch) > 0 or self.ptr_ch == '(':
            self.ptr_ch = string[self.i]
            self.flag_bracket += 1
            self.i += 1
        else:
            self.res = False

    def CloseBrackCheck(self, string: str):
        if self.ptr_ch == ' ' or self.ptr_ch.isnumeric() or self.ptr_ch == 'x' or self.ptr_ch == ')':
            self.ptr_ch = string[self.i]
            self.flag_bracket -= 1
            if self.flag_point != 0:
                self.flag_point -= 1
            if self.flag_point != 0:
                self.res = False
            self.i += 1
        else:
            self.res = False

    def ECheck(self, string: str):
        if (self.ptr_ch.isnumeric() and string[self.i + 1].isnumeric()) or (self.ptr_ch.isnumeric() and string[self.i + 1] == '-'
                                                                            and string[self.i + 2].isnumeric()):
            self.ptr_ch = string[self.i]
            self.i += 1
        else:
            self.res = False

    def x_validaton(self, string: str):
        try:
            float(string)
            return True
        except Exception as exp:
            return False