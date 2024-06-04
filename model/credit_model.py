
class Credit():
    def __init__(self):
        self.month_pay_max = 0
        self.month_pay_min = 0
        self.over_pay = 0
        self.sum_pay = 0

    def calculate(self, credit_sum: float, month_year: int, m_y_type: int, percent: float, type_credit: bool):
        if m_y_type == 0:
            month_year *= 12
        if type_credit == 0:
            self.month_pay_min = credit_sum * (((percent / 100 / 12) * pow((1 + (percent / 100 / 12)), month_year)) / (pow(1 + ((percent / 100 / 12)), month_year) - 1))
            self.over_pay = (month_year * self.month_pay_min) - credit_sum
            self.sum_pay = credit_sum + self.over_pay
            self.month_pay_max = self.month_pay_min
        else:
            sum_tmp = credit_sum
            for i in range(month_year, 0, -1):
                self.month_pay_max = (credit_sum / i) + (credit_sum * (percent / 100 / 12))
                if i == month_year:
                    self.month_pay_min = self.month_pay_max
                self.sum_pay += self.month_pay_max
                credit_sum -= sum_tmp / month_year
            self.over_pay = self.sum_pay - sum_tmp


