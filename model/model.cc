#include "model.h"

bool Model::ValidCheck(std::string &str) {
  int res = 1;
  size_t n = str.length();
  int flag_bracket = 0;
  char ptr_ch = ' ';
  int flag_point = 0;
  for (size_t i = 0; i < n && res != 0; ++i) {
    if (IsNumber(str[i]) || str[i] == 'x') {
      if (ptr_ch == ' ' || IsNumber(ptr_ch) || IsOperator(ptr_ch) > 0 ||
          ptr_ch == '(' || ptr_ch == '.' || ptr_ch == 'e') {
        ptr_ch = str[i];
        if (str[++i] == '\0' && flag_point != 0) {
          --flag_point;
        }
        --i;
      } else {
        res = 0;
      }
    } else if (str[i] == '-' || str[i] == '+') {
      MPCheck(ptr_ch, str, res, flag_point, i);
    } else if (IsOperator(str[i]) > 0) {
      OperCheck(ptr_ch, str, res, flag_point, i);
    } else if (str[i] == '.') {
      DotCheck(ptr_ch, str, res, flag_point, i);
    } else if (IsFunction(str[i]) && !(IsMod(&str[i]))) {
      FunkCheck(ptr_ch, str, res, i, flag_bracket);
    } else if (IsFunction(str[i]) && (IsMod(&str[i]))) {
      ModCheck(ptr_ch, str, res, i, flag_point);
    } else if (str[i] == '(') {
      OpenBrackCheck(ptr_ch, str, res, i, flag_bracket);
    } else if (str[i] == ')') {
      CloseBrackCheck(ptr_ch, str, res, i, flag_bracket, flag_point);
    } else if (str[i] == 'e') {
      ECheck(ptr_ch, str, res, i);
    } else if (str[i] == ' ') {
    } else {
      res = 0;
    }
  }
  if (flag_bracket != 0) {
    res = 0;
  }
  if (flag_point != 0) {
    res = 0;
  }
  return res;
}

double Model::PolishNotation(wchar_t* x, double x_value) {
  std::stack<ParcVal> numberStack_;
  std::stack<ParcVal> operStack_;
  std::wstring ws(x);
  std::string str(ws.begin(), ws.end());
  std::stringstream sstr{str};
  char ch;
  double value;
  bool flagUnar = true;
  while (!sstr.eof()) {
    ch = sstr.peek();
    if (ch == ' ') {
      sstr.ignore();
      continue;
    }
    if (IsNumber(ch)) {
      sstr >> value;
      numberStack_.push({value, number, CheckPriority(number)});
      flagUnar = false;
      continue;
    }
    if (ch == 'x') {
      numberStack_.push({x_value, number, CheckPriority(number)});
      sstr.ignore();
      flagUnar = false;
      continue;
    }
    if ((ch == '-' && flagUnar) || (ch == '+' && flagUnar)) {
      numberStack_.push({0, number, CheckPriority(number)});
      operStack_.push(
          {0, (ch == '-' ? t_minus : t_plus), CheckPriority(t_minus)});
      flagUnar = false;
      sstr.ignore();
      continue;
    }
    if (IsOperator(ch) > 0 || ch == 'm') {
      PushOper(ch, sstr, numberStack_, operStack_);
      continue;
    }
    if (IsFunction(ch) && (ch != 'm')) {
      PushFunc(ch, sstr, operStack_);
      continue;
    }
    if (ch == '(') {
      operStack_.push({0, sk_open, CheckPriority(sk_open)});
      sstr.ignore();
      flagUnar = true;
      continue;
    }
    if (ch == ')') {
      while (operStack_.top().type != sk_open) {
        MathCount(numberStack_, operStack_);
      }
      operStack_.pop();
      sstr.ignore();
      continue;
    }
  }
  while (operStack_.size() != 0) {
    MathCount(numberStack_, operStack_);
  }
  return numberStack_.top().value;
}

void Model::MathCount(std::stack<ParcVal>& numberStack_, std::stack<ParcVal>& operStack_) {
  double a = 0.0, b = 0.0;
  a = numberStack_.top().value;
  numberStack_.pop();
  oper_type ot = operStack_.top().type;
  if (ot < 9 || ot == 18) {
    b = numberStack_.top().value;
    numberStack_.pop();
    if (ot == t_plus)
      b += a;
    else if (ot == t_minus)
      b -= a;
    else if (ot == t_mult)
      b *= a;
    else if (ot == t_div) {
      if (a != 0)
        b /= a;
      else
        b = NAN;
    } else if (ot == t_mod)
      b = fmod(b, a);
    else if (ot == t_stepen)
      b = pow(b, a);
  } else {
    if (ot == t_sin)
      b = sin(a);
    else if (ot == t_cos)
      b = cos(a);
    else if (ot == t_tan)
      b = tan(a);
    else if (ot == t_acos)
      b = acos(a);
    else if (ot == t_asin)
      b = asin(a);
    else if (ot == t_atan)
      b = atan(a);
    else if (ot == t_sqrt)
      b = sqrt(a);
    else if (ot == t_ln)
      b = log(a);
    else if (ot == t_log)
      b = log10(a);
  }
  operStack_.pop();
  numberStack_.push({b, number, CheckPriority(number)});
}

bool Model::IsNumber(char a) { return (a >= 48 && a <= 57); }
int Model::IsOperator(char a) {
  int res = 0;
  switch (a) {
    case '+':
      res = 3;
      break;
    case '-':
      res = 4;
      break;
    case '*':
      res = 5;
      break;
    case '/':
      res = 6;
      break;
    case '^':
      res = 8;
      break;
  }
  return res;
}
bool Model::IsFunction(char a) {
  return (a == 's' || a == 'c' || a == 'm' || a == 't' || a == 'a' || a == 'l');
}

bool Model::IsSin(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "sin(");
}

bool Model::IsCos(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "cos(");
}

bool Model::IsTan(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "tan(");
}

int Model::IsArc(char *str) {
  int res = 0;
  char Ch = str[0];
  if (Ch == 'a') {
    str++;
    if (IsSin(str)) {
      res = 13;
    } else if (IsCos(str)) {
      res = 12;
    } else if (IsTan(str)) {
      res = 14;
    }
  }
  return res;
}

bool Model::IsSqrt(char *str) {
  return (static_cast<std::string>(str).substr(0, 5) == "sqrt(");
}

bool Model::IsLog(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "log(");
}

bool Model::IsLn(char *str) {
  return (static_cast<std::string>(str).substr(0, 3) == "ln(");
}

bool Model::IsMod(char *str) {
  return (static_cast<std::string>(str).substr(0, 3) == "mod");
}

int Model::CheckPriority(oper_type value) {
  int res = -2;
  if (value == 19) res = -1;
  if (value == 1 || value == 2) res = 0;
  if (value == 3 || value == 4) res = 1;
  if (value >= 5 && value <= 7) res = 2;
  if (value == 8) res = 3;
  if (value >= 9 && value <= 17) res = 4;
  if (value == 20) res = 5;
  return res;
}

//void Model::SetX(double value) { x_value_ = value; }

void Model::MPCheck(char &ptr_ch, std::string &str, int &res,
                         int &flag_point, size_t &i) {
  if (ptr_ch == ' ' || IsNumber(ptr_ch) || ptr_ch == '(' || ptr_ch == 'x' ||
      ptr_ch == ')' || ptr_ch == 'e') {
    ++i;
    if (str[i] == '\0') {
      res = 0;
    } else {
      --i;
      ptr_ch = str[i];
      if (flag_point != 0) {
        flag_point--;
      }
    }
    if (flag_point != 0) {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void Model::OperCheck(char &ptr_ch, std::string &str, int &res,
                           int &flag_point, size_t &i) {
  if ((ptr_ch == ' ' || IsNumber(ptr_ch) || ptr_ch == 'x' || ptr_ch == ')') &&
      i > 0) {
    ++i;
    if (str[i] == '\0') {
      res = 0;
    } else {
      --i;
      ptr_ch = str[i];
      if (flag_point != 0) {
        flag_point--;
      }
    }
    if (flag_point != 0) {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void Model::DotCheck(char &ptr_ch, std::string &str, int &res,
                          int &flag_point, size_t &i) {
  if (IsNumber(ptr_ch)) {
    if (IsNumber(str[++i])) {
      ptr_ch = str[--i];
      flag_point++;
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void Model::FunkCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                           int &flag_bracket) {
  if (ptr_ch == ' ' || IsOperator(ptr_ch) > 0 || ptr_ch == '(') {
    if (IsCos(&str[i]) || IsSin(&str[i]) || IsTan(&str[i]) || IsLog(&str[i])) {
      ptr_ch = '(';
      i += 3;
      flag_bracket++;
    } else if (IsSqrt(&str[i]) || IsArc(&str[i])) {
      ptr_ch = '(';
      i += 4;
      flag_bracket++;
    } else if (IsLn(&str[i])) {
      ptr_ch = '(';
      i += 2;
      flag_bracket++;
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void Model::ModCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                          int &flag_point) {
  if (IsNumber(ptr_ch) || ptr_ch == 'x') {
    if (((IsNumber(str[i + 3]) && (str[i + 3] != '0')) ||
         (str[i + 3] == ' ' && IsNumber(str[i + 4]))) ||
        ((str[i + 3] == 'x') || (str[i + 3] == ' ' && str[i + 4] == 'x'))) {
      ptr_ch = ' ';
      i += 2;
      --flag_point;
      if (flag_point != 0) {
        res = 0;
      }
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void Model::OpenBrackCheck(char &ptr_ch, std::string &str, int &res,
                                size_t &i, int &flag_bracket) {
  if (ptr_ch == ' ' || (IsOperator(ptr_ch) > 0) || ptr_ch == '(') {
    ptr_ch = str[i];
    flag_bracket++;
  } else {
    res = 0;
  }
}

void Model::CloseBrackCheck(char &ptr_ch, std::string &str, int &res,
                                 size_t &i, int &flag_bracket,
                                 int &flag_point) {
  if (ptr_ch == ' ' || IsNumber(ptr_ch) || ptr_ch == 'x' || ptr_ch == ')') {
    ptr_ch = str[i];
    flag_bracket--;
    if (flag_point != 0) {
      flag_point--;
    }
    if (flag_point != 0) {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void Model::ECheck(char &ptr_ch, std::string &str, int &res, size_t &i) {
  if ((IsNumber(ptr_ch) && IsNumber(str[i + 1])) ||
      (IsNumber(ptr_ch) && str[i + 1] == '-' && IsNumber(str[i + 2]))) {
    ptr_ch = str[i];
  } else {
    res = 0;
  }
}

void Model::PushOper(char &ch, std::stringstream &sstr, std::stack<ParcVal>& numberStack_, std::stack<ParcVal> &operStack_) {
  int res = IsOperator(ch);
  if (ch == 'm') {
    res = 7;
    for (int i = 0; i < 2; ++i) {
      sstr.ignore();
    }
  }
  if (operStack_.size() == 0) {
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
    sstr.ignore();
  } else if (operStack_.size() != 0 &&
             (CheckPriority(static_cast<oper_type>(res)) >
              operStack_.top().priority)) {
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
    sstr.ignore();
  } else if (operStack_.size() != 0 &&
             (CheckPriority(static_cast<oper_type>(res)) <=
              operStack_.top().priority)) {
    while (operStack_.size() != 0 && (CheckPriority(static_cast<oper_type>(
                                          res)) <= operStack_.top().priority)) {
      MathCount(numberStack_, operStack_);
    }
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
    sstr.ignore();
  }
}

void Model::PushFunc(char &ch, std::stringstream &sstr, std::stack<ParcVal>& operStack_) {
  int i = 0;
  char tmp[5] = {'\0'};
  for (i = 0; i < 5 && ch != '('; ++i) {
    ch = sstr.peek();
    tmp[i] = ch;
    if (ch != '(') sstr.ignore();
  }
  if (IsLn(tmp)) {
    operStack_.push({0, t_ln, CheckPriority(t_ln)});
  }
  if (IsSin(tmp)) {
    operStack_.push({0, t_sin, CheckPriority(t_sin)});
  }
  if (IsCos(tmp)) {
    operStack_.push({0, t_cos, CheckPriority(t_cos)});
  }
  if (IsTan(tmp)) {
    operStack_.push({0, t_tan, CheckPriority(t_tan)});
  }
  if (IsArc(tmp) > 0) {
    int res = IsArc(tmp);
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
  }
  if (IsSqrt(tmp)) {
    operStack_.push({0, t_sqrt, CheckPriority(t_sqrt)});
  }
  if (IsLog(tmp)) {
    operStack_.push({0, t_log, CheckPriority(t_log)});
  }
}

bool Model::XValidation(std::string &str) {
  int res = 1;
  int flag_point = 0;
  int flag_oper = 0;
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '.') ++flag_point;
    if (IsOperator(str[i])) ++flag_oper;
  }
  if (flag_oper > 1 || flag_point > 1) res = 0;
  return res;
}

//bool Model::GetTopNumberStack() {
//    return !numberStack_.empty();
//}
//
//int main() {
//    Model m;
//    std::string str = "10 "
//
//    double x = m.PolishNotation(str, 1);
//    std::cout << x << std::endl;
//}