from ctypes import cdll
from ctypes import *

try:
    with open("../../config.conf", "r") as f:
        prefix = f.readlines()
except Exception as exp:
    try:
        with open("other/config.conf", "r") as f:
            prefix = f.readlines()
    except Exception as exp:
        print(exp)
prefix += ["/model/libmodel.so"]
path = ''.join(prefix)

lib = cdll.LoadLibrary(path)
lib.Model_Result.restype = c_double
class PTEST(c_void_p): pass  # opaque pointer aids type-checking
lib.Model_Result.argtypes = PTEST, c_wchar_p, c_double

class Model(object):
    def __init__(self):
        self.obj = lib.Model_new()

    def result(self, s, x=1):
        return lib.Model_Result(self.obj, s, x)

    # def setX(self, value):
    #     lib.Model_Set_X(self.obj, value)

if __name__ == "__main__":
    m = Model()
    s = "(1/4)*(4^3-2^5)+(1/2)^(-2)*(-2)"
    # m.setX(1)
    x = m.result(s)
    print(x)