class Deposit():
    def __init__(self):
        self.percent = 0
        self.tax = 0
        self.total_sum = 0

    def calculate(self, dep_sum: float, monthD: int, type_term: int, pr_rate: float, tax_rate: float, t_p: int, capitalisation: bool):
        so = 1000000 * (7.50 / 100)
        procent_tmp = 0
        d = 0
        if type_term == 0:
            monthD *= 12
        days = int(monthD * 30.41666666)
        if not capitalisation:
            self.percent = dep_sum * ((pr_rate / 12 / 100) * monthD)
            self.total_sum = dep_sum + self.percent
        if capitalisation:
            if t_p == 0:
                d = 365
            elif t_p == 1:
                days /= 7
                d = 52
            elif t_p == 2:
                days = monthD
                d = 12
            elif t_p == 3:
                days = int(monthD / 3)
                d = 4
            elif t_p == 4:
                days = int(monthD / 6)
                d = 2
            elif t_p == 5 and monthD > 11:
                days = int(monthD / 12)
                d = 1
            elif t_p == 6 or monthD < 12:
                self.calculate(dep_sum, monthD, 2, pr_rate, tax_rate, type_term, False)
                self.total_sum = self.percent + dep_sum
                return
            for _ in range(days):
                procent_tmp = dep_sum * (pr_rate / 100 / d)
                self.percent += procent_tmp
                dep_sum += procent_tmp
            self.total_sum = dep_sum
        tmp = self.percent
        s = float(monthD / 12)
        ex_tax = so * s
        self.tax = (self.percent - ex_tax) * (tax_rate / 100) if tmp > ex_tax else 0

