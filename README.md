# Calculator_Python

Implementation of SmartCalc in Python.

- A desktop application of calculator is developed in Python.
- The installer, which will install the application to the system is prepared.
- The program is implemented using the  MVP pattern, and:
  - there is no business logic code in the view code;
  - there is no interface code in the model, presenter and view model.
- The "core" of the calculator in the form of an algorithm for the formation and calculation of the Polish notation and various computational functions connect as a dynamic library in C/C++ from the Calculator_CPP projects.
- The full coverage of the methods in the model layer with unit tests prepared.
- The application has a help section with a description of the program interface in random form.
- The program stores the history of operations, allowes loading expressions from the history, and clear the entire history.
- The history is saved between runs of the application.
- Both integers and real numbers are entered into the program, written either in point or exponential form.
- Calculation of arbitrary bracketed arithmetic expressions in infix notation.
- Calculate arbitrary parenthesized arithmetic expressions in infix notation with substitution of the _x_ variable as a number.
- Plotting a function defined by an expression in infix notation with the variable _x_ (with coordinate axes, scale markers, and grid with adaptive step)
- The user must be able to enter up to 255 characters.

 ## Credit сalculator

- Input: total loan amount, term, interest rate, type (annuity, differentiated);
- Output: monthly payment, overpayment for the loan, total repayment.

## Deposit calculator

- Input: deposit amount, deposit term, interest rate, tax rate, periodicity of payments, capitalization of interest, list of additions, list of partial withdrawals;
- Output: accrued interest, tax amount, amount on deposit by the end of the term.

## Configuration and logging

- Reading of settings from configuration file when the program runs aded.
- 3 parameters to choose from, such as background color, font size and text style included in the configuration file .

Add logging to the application:
- The program save logs in the logs folder, one file per period.
- Files are named according to the following pattern: `logs_dd-MM-yy-hh-mm-ss` (the time of file creation).

