import math
import unittest
from view.validation import *
from model.model import Model


class MyTestCase(unittest.TestCase):

    def test_valid_1(self):
        v = Validation()
        self.assertEqual(v.validation("cos(sin(tan(asin(acos(atan)"), False)

    def test_valid_2(self):
        v = Validation()
        self.assertEqual(v.validation("32+12-(18.6-)"), False)

    def test_valid_3(self):
        v = Validation()
        self.assertEqual(v.validation("32/(12*(18.6-)"), False)

    def test_valid_4(self):
        v = Validation()
        self.assertEqual(v.validation("mod3ln"), False)

    def test_valid_5(self):
        v = Validation()
        self.assertEqual(v.validation("127-a+cis(son(lg(laq(acus(2)))))"), False)

    def test_valid_6(self):
        v = Validation()
        self.assertEqual(v.validation("x.123z*aspo(2)/sqrt(/)"), False)

    def test_valid_7(self):
        v = Validation()
        self.assertEqual(v.validation("ln(-3) * 3 mod 2 )"), False)

    def test_valid_8(self):
        v = Validation()
        self.assertEqual(v.validation("25+$3-c0s(@-4)/"), False)

    def test_valid_9(self):
        v = Validation()
        self.assertEqual(v.validation("13$(^mod5*!/(&+5)18"), False)

    def test_valid_10(self):
        v = Validation()
        self.assertEqual(v.validation("37/"), False)

    def test_valid_11(self):
        v = Validation()
        self.assertEqual(v.validation("37+"), False)

    def test_valid_12(self):
        v = Validation()
        self.assertEqual(v.validation("(2+3)x"), False)

    def test_valid_13(self):
        v = Validation()
        self.assertEqual(v.validation("80*+13"), False)

    def test_valid_14(self):
        v = Validation()
        self.assertEqual(v.validation("sin(3) + * 4"), False)

    def test_valid_15(self):
        v = Validation()
        self.assertEqual(v.validation("3sin(3)"), False)

    def test_valid_16(self):
        v = Validation()
        self.assertEqual(v.validation("18(4-89)"), False)

    def test_valid_17(self):
        v = Validation()
        self.assertEqual(v.validation("sin(3)+3mod"), False)

    def test_valid_18(self):
        v = Validation()
        self.assertEqual(v.validation("123.123.123 + 1"), False)

    def test_valid_19(self):
        v = Validation()
        self.assertEqual(v.validation("123.123.123 * 1"), False)

    def test_valid_20(self):
        v = Validation()
        self.assertEqual(v.validation("(x+2.123.2)"), False)

    def test_valid_21(self):
        v = Validation()
        self.assertEqual(v.validation("sin(2mod3)+e-12"), False)

    def test_valid_22(self):
        v = Validation()
        self.assertEqual(v.validation("sin(.1)"), False)

    def test_valid_23(self):
        v = Validation()
        self.assertEqual(v.validation("sqrt(cos(x + 2.)) * 3mod2.1223"), False)

    def test_valid_24(self):
        v = Validation()
        self.assertEqual(v.validation("sqrt(cos(x + 2.0)) * 3mod2.1223"), True)

    def test_valid_25(self):
        v = Validation()
        self.assertEqual(v.validation("(1/4e)*(4^3-2^5)+(1/2)^(-2)*(-2)"), False)

    def test_valid_26(self):
        v = Validation()
        self.assertEqual(v.validation("13e-1 * sin(2) - 1.87"), True)

    def test_valid_27(self):
        v = Validation()
        self.assertEqual(v.validation("-0.23-8"), True)

    def test_polish_notaion_1(self):
        m = Model()
        self.assertEqual(m.result("((3^2 - 2^3)^2)"), 1)

    def test_polish_notaion_2(self):
        m = Model()
        self.assertEqual(m.result("((2^3 - 3^2)^77) / 7^(-1)"), -7)

    def test_polish_notaion_3(self):
        m = Model()
        self.assertEqual(m.result("10+sin(cos(log(5+1)))"), 10.653510057399632)

    def test_polish_notaion_4(self):
        m = Model()
        self.assertEqual(m.result("0.8^0*(3^3+5^5)^0+(1/5)^(-1)"), 6)

    def test_polish_notaion_5(self):
        m = Model()
        self.assertEqual(m.result("(1/4)*(4^3-2^5)+(1/2)^(-2)*(-2)"), 0)

    def test_polish_notaion_6(self):
        m = Model()
        self.assertEqual(m.result("-5.8734/12+(0.000076*sqrt(0.99)-9mod3)"), -0.4893743809547799)

    def test_polish_notaion_7(self):
        m = Model()
        self.assertEqual(m.result("sin(cos(log(3^2 - 2^3)))"), 0.8414709848078965)

    def test_polish_notaion_8(self):
        m = Model()
        self.assertEqual(m.result("atan(0.678456)"), 0.59612010125075288)

    def test_polish_notaion_9(self):
        m = Model()
        self.assertEqual(m.result("asin(0.678456)"), 0.7456588827547209)

    def test_polish_notaion_10(self):
        m = Model()
        self.assertEqual(m.result("acos(0.0331)"), 1.5376902796978882)

    def test_polish_notaion_11(self):
        m = Model()
        self.assertEqual(m.result("-tan(sqrt(9))"), 0.1425465430742778)

    def test_polish_notaion_12(self):
        m = Model()
        self.assertEqual(m.result("5mod2*ln(sqrt(2.9-0.13))+(-1.987)"), -1.4775763399003765)

    def test_polish_notaion_13(self):
        m = Model()
        self.assertTrue(math.isnan(m.result("-sqrt(9)/((1/4)*(4^3-2^5)+(1/2)^(-2)*(-2))")))

    def test_polish_notaion_14(self):
        m = Model()
        self.assertEqual(m.result("sin(x)", -1), -0.8414709848078965)

    def test_polish_notaion_15(self):
        m = Model()
        self.assertEqual(m.result("18+(2e-1)"), 18.2)


if __name__ == '__main__':
    unittest.main()
