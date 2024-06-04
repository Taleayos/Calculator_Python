#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

enum oper_type {
// priority = 0;
    number = 1,
    x = 2,
// priority = 1;
    t_plus = 3,
    t_minus = 4,
// priority = 2;
    t_mult = 5,
    t_div = 6,
    t_mod = 7,
// priority = 3;
    t_stepen = 8,
// priority = 4;
    t_sin = 9,
    t_cos = 10,
    t_tan = 11,
    t_acos = 12,
    t_asin = 13,
    t_atan = 14,
    t_sqrt = 15,
    t_ln = 16,
    t_log = 17,
// priority = -1;
    sk_open = 19,
// priority = 5;
    sk_close = 20
};

struct ParcVal {
    double value;
    oper_type type;
    int priority;
};

class Model {

 public:

  Model() {};

  bool ValidCheck(std::string &str);

  double PolishNotation(wchar_t* str, double x);

  void MathCount(std::stack<ParcVal>& numberStack_, std::stack<ParcVal>& operStack_);

  bool IsNumber(char a);

  int IsOperator(char a);

  bool IsFunction(char a);

  bool IsSin(char *str);

  bool IsCos(char *str);

  bool IsTan(char *str);

  int IsArc(char *str);

  bool IsSqrt(char *str);

  bool IsLog(char *str);

  bool IsLn(char *str);

  bool IsMod(char *str);

  int CheckPriority(oper_type value);

  void SetX(const double value);

  void MPCheck(char &ptr_ch, std::string &str, int &res, int &flag_point,
               size_t &i);

  void OperCheck(char &ptr_ch, std::string &str, int &res, int &flag_point,
                 size_t &i);

  void DotCheck(char &ptr_ch, std::string &str, int &res, int &flag_point,
                size_t &i);

  void FunkCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                 int &flag_bracket);

  void ModCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                int &flag_point);

  void OpenBrackCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                      int &flag_bracket);

  void CloseBrackCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                       int &flag_bracket, int &flag_point);

  void ECheck(char &ptr_ch, std::string &str, int &res, size_t &i);

  void PushFunc(char &ch, std::stringstream &sstr, std::stack<ParcVal>& operStack_);

  void PushOper(char &ch, std::stringstream &sstr, std::stack<ParcVal>& numberStack_, std::stack<ParcVal> &operStack_);

  bool XValidation(std::string &str);

//  bool GetTopNumberStack();

 private:
//  std::stack<ParcVal> operStack_;
//  std::stack<ParcVal> numberStack_;
//  double x_value_;

};  // class Model;

extern "C" {
    Model* Model_new(){ return new Model(); }
//    void Model_Set_X(Model* model, double value) { model->SetX(value); }
    double Model_Result(Model* model, wchar_t* str, double x){ return model->PolishNotation(str, x); }
}

#endif /* MODEL_H */
