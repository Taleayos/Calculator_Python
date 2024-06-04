from PyQt5 import QtWidgets
from view.view import Ui_View

if __name__ == "__main__":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    View = QtWidgets.QWidget()
    ui = Ui_View()
    ui.setupUi(View)
    View.show()
    sys.exit(app.exec_())