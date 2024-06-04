
from model.model import Model
from model.credit_model import Credit
from model.deposit_model import Deposit

class Presenter():
    def __init__(self):
        self.model = Model()
        self.credit = Credit()
        self.deposit = Deposit()

    def calculate(self, result_str: str, x_value: float=1):
        res = self.model.result(result_str, x_value)
        return res

    def credit_calculate(self, credit_sum: float, month_year: int, m_y_type: int, percent: float, type_credit: bool):
        self.credit.calculate(credit_sum, month_year, m_y_type, percent, type_credit)
        return self.credit

    def deposit_calculate(self, dep_sum: float, monthD: int, type_term: int, pr_rate: float, tax_rate: float, t_p: int, capitalisation: bool):
        self.deposit.calculate(dep_sum, monthD, type_term, pr_rate, tax_rate, t_p, capitalisation)
        return self.deposit


if __name__ == "__main__":
    pass