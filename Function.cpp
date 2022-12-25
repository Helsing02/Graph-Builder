#include "Function.h"

#define PI 3.14159265

using std::string;
using std::isnan;
using std::isinf;
using std::stack;
using std::map;
using std::isnan;
using std::isinf;

bool Function::letter(char c) {
    if ('a' <= c && c <= 'z') return true;
    return false;
}
bool Function::digit(char c) {
    if ('0' <= c && c <= '9') return true;
    return false;
}
bool Function::operation(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return true;
    return false;
}

int Function::set_rpn(string s) {
    transform(s.begin(), s.end(), s.begin(), tolower);
    map <string, int> operationPriority = { { "(", 0 },
                                { "+", 1 },
                                { "-", 1 },
                                { "*", 2 },
                                { "/", 2 },
                                { "~", 3 },
                                { "^", 4 },
                                { "sin()", 5 },
                                { "asin()", 5 },
                                { "sinh()", 5 },
                                { "asinh()", 5 },
                                { "cos()", 5 },
                                { "acos()", 5 },
                                { "cosh()", 5 },
                                { "acosh()", 5 },
                                { "tan()", 5 },
                                { "atan()", 5 },
                                { "tanh()", 5 },
                                { "atanh()", 5 },
                                { "cotan()", 5 },
                                { "acotan()", 5 },
                                { "cotanh()", 5 },
                                { "acotanh()", 5 },
                                { "abs()", 5 },
                                { "grad()", 5 },
                                { "exp()", 5 },
                                { "root()", 5 },
                                { "sgn()", 5 },
                                { "log()", 5 },
                                { "log10()", 5 },
                                { "loga()", 5 } };
    stack <string> Stek;
    int len = (int)s.length();
    string symbols;
    int brackets = 0, dig = 0, oper = 0, checkabs = 0, countroot = 0, check_loga = 0, check_digit_in_abs = 0, count_abs = 0, last_abs = 0, next = 0, previous = 0;
    bool minus_in_root = false, check_minus = false;

    for (int i = 0; i < len; i++) {
        if (s[i] != '|') last_abs = 0;
        if (digit(s[i])) {
            if (i > 0) {
                previous = i - 1;
                while (previous > 0 && s[previous] == ' ') previous--;
                if (previous >= 0 && (!operation(s[previous]) && s[previous] != '(' && s[previous] != ',' && s[previous] != ' ' && s[i - 1] != 'g' && s[previous] != '|')) return 1;
            }
            bool dot = false;
            symbols = s[i];
            while ((i + 1 < len) && (digit(s[i + 1]) || s[i + 1] == '.')) {
                if (digit(s[i + 1])) symbols += s[i + 1];
                if (s[i + 1] == '.') {
                    if ((i + 2 < len) && !digit(s[i + 2])) return 1;
                    symbols += s[i + 1];
                    if (dot == false) dot = true;
                    else return 1;
                }
                i++;
            }
            m_expression.push_back(symbols);
            dig++;
        }
        else if (operation(s[i])) {
            if (i == len - 1) return 1;
            next = i + 1;
            while (next < len - 1 && s[next] == ' ') next++;
            if (s[next] == ')' || s[next] == ',') return 1;
            if (operation(s[i]) && operation(s[next])) return 1;

            if (i == 0 && s[i] != '-') return 1;
            previous = i;
            if (i > 0) {
                previous = i - 1;
                while (previous > 0 && s[previous] == ' ') previous--;
                if (i != 0 && (s[previous] == '(' || s[previous] == '|') && operation(s[next])) return 1;
                if (previous == 0 && s[previous] == ' ' && s[i] != '-') return 1;
                if ((s[previous] == '(' || s[previous] == ',') && s[i] != '-') return 1;
            }
            symbols = s[i];
            if ((s[i] == '-') && (i == 0 || (previous == 0 && s[previous] == ' ') || s[previous] == '(' || minus_in_root == true || check_minus == true)) symbols = "~";
            check_minus = false;
            while ((!Stek.empty()) && (operationPriority[Stek.top()] >= operationPriority[symbols])) {
                m_expression.push_back(Stek.top());
                Stek.pop();
            }
            minus_in_root = false;
            Stek.push(symbols);
            oper++;
        }
        else if (letter(s[i])) {
            if (i > 0) {
                previous = i - 1;
                while (previous > 0 && s[previous] == ' ') previous--;
                if (previous >= 0 && (!operation(s[previous]) && s[previous] != '(' && s[previous] != ',' && s[previous] != ' ' && s[previous] != '|')) return 1;
            }
            if (s[i] == 'x') {
                m_expression.push_back("x");
                dig++;
            }
            else if (s[i] == 'p') {
                if ((i + 1 < len) && s[i + 1] == 'i') {
                    m_expression.push_back("pi");
                    i++;
                    dig++;
                }
                else return 1;
            }
            else {
                int f = 0;
                switch (s[i]) {
                case 'r':
                    if ((i + 4 < len) && (s[i + 1] == 'o') && (s[i + 2] == 'o') && (s[i + 3] == 't')) {
                        countroot++;
                        symbols = "root()";
                        i = i + 3;
                        oper++;
                    }
                    else return 1;
                    break;
                case 'g':
                    if ((i + 4 < len) && (s[i + 1] == 'r') && (s[i + 2] == 'a') && (s[i + 3] == 'd')) {
                        symbols = "grad()";
                        i = i + 3;
                    }
                    else return 1;
                    break;
                case 's':
                    if ((i + 4 < len) && (s[i + 1] == 'i') && (s[i + 2] == 'n')) {
                        if (s[i + 3] == 'h') {
                            symbols = "sinh()";
                            i++;
                        }
                        else symbols = "sin()";
                        i = i + 2;
                    }
                    else if ((i + 2 < len) && s[i + 1] == 'h') {
                        symbols = "sinh()";
                        i++;
                    }
                    else if ((i + 3 < len) && (s[i + 1] == 'g') && (s[i + 2] == 'n')) {
                        symbols = "sgn()";
                        i = i + 2;
                    }
                    else return 1;
                    break;
                case 'c':
                    if ((i + 4 < len) && (s[i + 1] == 'o') && (s[i + 2] == 's')) {
                        if (s[i + 3] == 'h') {
                            symbols = "cosh()";
                            i++;
                        }
                        else symbols = "cos()";
                        i = i + 2;
                    }
                    else if ((i + 2 < len) && s[i + 1] == 'h') {
                        symbols = "cosh()";
                        i++;
                    }
                    else if ((i + 6 < len) && (s[i + 1] == 'o') && (s[i + 2] == 't') && (s[i + 3] == 'a') && (s[i + 4] == 'n')) {
                        if (s[i + 5] == 'h') {
                            symbols = "cotanh()";
                            i++;
                        }
                        else symbols = "cotan()";
                        i = i + 4;
                    }
                    else if ((i + 4 < len) && (s[i + 1] == 't') && (s[i + 2] == 'g')) {
                        if (s[i + 3] == 'h') {
                            symbols = "cotanh()";
                            i++;
                        }
                        else symbols = "cotan()";
                        i = i + 2;
                    }
                    else return 1;
                    break;
                case 't':
                    if ((i + 4 < len) && (s[i + 1] == 'a') && (s[i + 2] == 'n')) {
                        if (s[i + 3] == 'h') {
                            symbols = "tanh()";
                            i++;
                        }
                        else symbols = "tan()";
                        i = i + 2;
                    }
                    else if ((i + 3 < len) && s[i + 1] == 'g') {
                        if (s[i + 2] == 'h') {
                            symbols = "tanh()";
                            i++;
                        }
                        else symbols = "tan()";
                        i++;
                    }
                    else return 1;
                    break;
                case 'a':
                    if ((i + 3 < len) && (s[i + 1] == 'r') && (s[i + 2] == 'c')) f = f + 2;
                    if ((i + f + 5 < len) && (s[i + f + 1] == 's') && (s[i + f + 2] == 'i') && (s[i + f + 3] == 'n')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "asinh()";
                            i++;
                        }
                        else symbols = "asin()";
                        i = i + f + 3;
                    }
                    else if ((i + f + 5 < len) && (s[i + f + 1] == 'c') && (s[i + f + 2] == 'o') && (s[i + f + 3] == 's')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "acosh()";
                            i++;
                        }
                        else symbols = "acos()";
                        i = i + f + 3;
                    }
                    else if ((i + f + 5 < len) && (s[i + f + 1] == 't') && (s[i + f + 2] == 'a') && (s[i + f + 3] == 'n')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "atanh()";
                            i++;
                        }
                        else symbols = "atan()";
                        i = i + f + 3;
                    }
                    else if ((i + f + 4 < len) && (s[i + f + 1] == 't') && (s[i + f + 2] == 'g')) {
                        if (s[i + f + 3] == 'h') {
                            symbols = "atanh()";
                            i++;
                        }
                        else symbols = "atan()";
                        i = i + f + 2;
                    }
                    else if ((i + f + 7 < len) && (s[i + f + 1] == 'c') && (s[i + f + 2] == 'o') && (s[i + f + 3] == 't') && (s[i + f + 4] == 'a') && (s[i + f + 5] == 'n')) {
                        if (s[i + f + 6] == 'h') {
                            symbols = "acotanh()";
                            i++;
                        }
                        else symbols = "acotan()";
                        i = i + f + 5;
                    }
                    else if ((i + f + 5 < len) && (s[i + f + 1] == 'c') && (s[i + f + 2] == 't') && (s[i + f + 3] == 'g')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "acotanh()";
                            i++;
                        }
                        else symbols = "acotan()";
                        i = i + f + 3;
                    }
                    else if ((i + 3 < len) && (s[i + 1] == 'b') && (s[i + 2] == 's')) {
                        symbols = "abs()";
                        i = i + 2;
                    }
                    else return 1;
                    break;
                case 'e':
                    if ((i + 3 < len) && (s[i + 1] == 'x') && (s[i + 2] == 'p')) {
                        symbols = "exp()";
                        i = i + 2;
                    }
                    else {
                        symbols = "e";
                        m_expression.push_back("e");
                        dig++;
                    }
                    break;
                case 'l':
                    if ((i + 2 < len) && (s[i + 1] == 'n')) {
                        symbols = "log()";
                        i++;
                    }
                    else if ((i + 5 < len) && (s[i + 1] == 'o') && (s[i + 2] == 'g') && (s[i + 3] == '1') && (s[i + 4] == '0') && (s[i + 5] == '(')) {
                        symbols = "log10()";
                        i = i + 4;
                        check_loga = 1;
                    }
                    else if ((i + 3 < len) && (s[i + 1] == 'o') && (s[i + 2] == 'g')) {
                        symbols = "loga()";
                        int i1 = i + 3;
                        if (digit(s[i1])) {
                            check_loga = 1;
                            while (s[i1] != '(') {
                                if (i1 == len - 1 || (!(digit(s[i1])) && s[i1] != '.')) return 1;
                                i1++;
                            }
                        }
                        else if (s[i1] == '(') {
                            int check1 = 1;
                            i1++;
                            while (check1 != 0) {
                                if (s[i1] == '(') check1++;
                                if (s[i1] == ')') check1--;
                                i1++;
                            }
                            if (s[i1] != '(') return 1;
                        }
                        else return 1;
                        i = i + 2;
                        oper++;
                    }
                    else return 1;
                    break;
                default:
                    return 1;
                    break;
                }
                if ((symbols != "e" && symbols != "loga()" && symbols != "log10()") && s[i + 1] != '(') return 1;
                if (symbols != "e") {
                    while ((!Stek.empty()) && (operationPriority[Stek.top()] >= operationPriority[symbols])) {
                        m_expression.push_back(Stek.top());
                        Stek.pop();
                    }
                    Stek.push(symbols);
                }
            }
        }
        else {
            int check2;
            switch (s[i]) {
            case '|':
                if (i == 0) {
                    while ((!Stek.empty()) && (operationPriority[Stek.top()] >= operationPriority["abs()"])) {
                        m_expression.push_back(Stek.top());
                        Stek.pop();
                    }
                    Stek.push("abs()");
                    Stek.push("(");
                    brackets++;
                    checkabs++;
                    check_digit_in_abs = dig;
                    if (i + 1 == len) return 1;
                    next = i + 1;
                    while (next < len - 1 && s[next] == ' ') next++;
                    if (s[next] == '-') check_minus = true;
                    last_abs = 1;
                }
                else if (i == len - 1 && checkabs > 0) {
                    if (last_abs == 1) return 1;
                    previous = i - 1;
                    while (previous > 0 && s[previous] == ' ') previous--;
                    if (operation(s[previous])) return 1;
                    while ((!Stek.empty()) && (Stek.top() != "(")) {
                        m_expression.push_back(Stek.top());
                        Stek.pop();
                    }
                    if (Stek.top() == "(") Stek.pop();
                    brackets--;
                    checkabs--;
                    if (check_digit_in_abs == dig) return 1;
                    check_digit_in_abs = 0;
                }
                else {
                    previous = i - 1;
                    while (previous > 0 && s[previous] == ' ') previous--;
                    next = i + 1;
                    while (next < len - 1 && s[next] == ' ') next++;

                    if ((operation(s[previous]) || s[previous] == '(' || s[previous] == ',' || s[previous] == '|' || s[previous] == ' ') && (letter(s[next]) || digit(s[next]) || s[next] == '(' || s[next] == '|' || s[next] == '-')) {
                        if (last_abs == 2) return 1;
                        while ((!Stek.empty()) && (operationPriority[Stek.top()] >= operationPriority["abs()"])) {
                            m_expression.push_back(Stek.top());
                            Stek.pop();
                        }
                        Stek.push("abs()");
                        Stek.push("(");
                        brackets++;
                        checkabs++;
                        check_digit_in_abs = dig;
                        if (s[next] == '-') check_minus = true;
                        last_abs = 1;
                    }
                    else if ((letter(s[previous]) || digit(s[previous]) || s[previous] == ')' || s[previous] == '|') && (operation(s[next]) || s[next] == ')' || s[next] == ',' || s[next] == '|' || s[next] == ' ')) {
                        if (checkabs == 0) return 1;
                        if (last_abs == 1) return 1;
                        previous = i - 1;
                        while (previous > 0 && s[previous] == ' ') previous--;
                        if (operation(s[previous])) return 1;
                        while ((!Stek.empty()) && (Stek.top() != "(")) {
                            m_expression.push_back(Stek.top());
                            Stek.pop();
                        }
                        if (Stek.top() == "(") Stek.pop();
                        brackets--;
                        checkabs--;
                        if (check_digit_in_abs == dig) return 1;
                        check_digit_in_abs = 0;
                        last_abs = 2;
                    }
                    else return 1;
                }
                break;
            case '(':
                if (i == len - 1) return 1;
                next = i + 1;
                while (next < len - 1 && s[next] == ' ') next++;
                if (s[next] == ')') return 1;
                if (s[next] == ' ' && next == len - 1) return 1;
                if (i > 0) {
                    previous = i - 1;
                    while (previous > 0 && s[previous] == ' ') previous--;
                    if (digit(s[previous]) && check_loga == 0) return 1;
                }
                check_loga = 0;
                Stek.push("(");
                brackets++;
                break;
            case ')':
                if ((i == 0) || (brackets == 0)) return 1;
                next = i;
                if (i < len - 1) {
                    next++;
                    while (next < len - 1 && s[next] == ' ') next++;
                    if (!operation(s[next]) && s[next] != ')' && s[next] != ',' && s[next] != '(' && s[next] != ' ' && s[next] != '|') return 1;
                }
                previous = i - 1;
                check2 = -1;
                while (check2 != 0 && previous > 0) {
                    if (s[previous] == '(') check2++;
                    if (s[previous] == ')') check2--;
                    if (s[previous] == '|') count_abs++;
                    previous--;
                }
                if (count_abs % 2 == 1) return 1;
                count_abs = 0;
                while ((!Stek.empty()) && (Stek.top() != "(")) {
                    m_expression.push_back(Stek.top());
                    Stek.pop();
                }
                if (Stek.top() == "(") Stek.pop();
                brackets--;
                if ((Stek.empty() && s[next] == '(') || (!Stek.empty() && Stek.top() != "loga()" && s[next] == '(')) return 1;
                break;
            case ' ':
                break;
            case ',':
                if (countroot > 0) {
                    previous = i - 1;
                    while (s[previous] == ' ') previous--;
                    if (s[previous] == '(') return 1;
                    next = i + 1;
                    while (s[next] == ' ') next++;
                    i = next - 1;
                    if (s[next] == '-') minus_in_root = true;
                    else if (!digit(s[next]) && !letter(s[next]) && s[next] != '(' && s[next] != '|') return 1;
                    while ((!Stek.empty()) && (Stek.top() != "(")) {
                        m_expression.push_back(Stek.top());
                        Stek.pop();
                    }
                    countroot--;
                    if (!Stek.empty()) {
                        Stek.pop();
                        if (Stek.top() != "root()") return 1;
                        Stek.push("(");
                    }
                }
                else return 1;
                break;
            default:
                return 1;
                break;
            }
        }
    }
    while (!Stek.empty()) {
        if (Stek.top() == "(") return 1;
        else {
            m_expression.push_back(Stek.top());
            Stek.pop();
        }
    }
    if (brackets != 0) return 1;
    if (checkabs != 0) return 1;
    if ((dig == 0) || (countroot != 0)) return 1;
    if (dig >= 2 && oper == 0) return 1;
    return 0;
}

int Function::set_exp(string s) {
    while (!m_expression.empty()) {
        m_expression.pop_back();
    }
    int numberoferror = set_rpn(s);
    return numberoferror;
}

double Function::get_y(double x) {
    stack <double> Stek1;
    double first = 0;
    double second = 0;
    double z;

    for (string s : m_expression) {
        if (digit(s[0])) {
            double l = 0, number = 0;
            for (int j = 0; j < s.length(); j++) {
                if (s[j] == '.') l = s.length() - j - 1;
                else number = number * 10 + ((double)s[j] - 48);
            }
            z = number / pow(10, l);
        }
        else if (operation(s[0])) {
            second = Stek1.top();
            Stek1.pop();
            first = Stek1.top();
            Stek1.pop();
            switch (s[0]) {
            case '+':
                z = first + second;
                break;
            case '-':
                z = first - second;
                break;
            case '*':
                z = first * second;
                break;
            case '/':
                if (second == 0) return nan("1");
                z = first / second;
                break;
            case '^':
                if (first == 0.0 && second == 0.0) return nan("1");
                z = pow(first, second);
                break;
            }
        }
        else if (s[0] == '~') {
            first = Stek1.top();
            Stek1.pop();
            z = 0 - first;
        }
        else if (letter(s[0])) {
            if (s == "loga()") {
                second = Stek1.top();
                Stek1.pop();
                first = Stek1.top();
                Stek1.pop();
                if (first == 1 || first <= 0) return nan("1");
                z = (log10(second)) / (log10(first));
            }
            else if (s == "root()") {
                second = Stek1.top();
                Stek1.pop();
                first = Stek1.top();
                Stek1.pop();
                z = pow(fabs(first), 1.0 / second);
                if (first < 0 && (floor(second) == second) && ((int)second % 2 != 0)) z = 0 - z;
                if (first < 0 && (floor(second) == second) && ((int)second % 2 == 0)) return nan("1");
            }
            else if (s == "x") z = x;
            else if (s == "pi") z = PI;
            else if (s == "e") z = exp(1);
            else {
                first = Stek1.top();
                Stek1.pop();
                if (s == "sin()") z = sin(first);
                else if (s == "sinh()") z = sinh(first);
                else if (s == "cos()") z = cos(first);
                else if (s == "cosh()") z = cosh(first);
                else if (s == "tan()") z = tan(first);
                else if (s == "tanh()") z = tanh(first);
                else if (s == "cotan()") z = 1.0 / (tan(first));
                else if (s == "cotanh()") z = (exp(first) + exp(0.0 - first)) / (exp(first) - exp(0.0 - first));
                else if (s == "asin()") z = asin(first);
                else if (s == "asinh()") z = asinh(first);
                else if (s == "acos()") z = acos(first);
                else if (s == "acosh()") z = acosh(first);
                else if (s == "atan()") z = atan(first);
                else if (s == "atanh()") z = atanh(first);
                else if (s == "acotan()") z = PI / 2.0 - atan(first);
                else if (s == "acotanh()") z = 1.0 / 2 * log((first + 1) / (first - 1));
                else if (s == "log()") z = log(first);
                else if (s == "log10()") z = log10(first);
                else if (s == "exp()") z = exp(first);
                else if (s == "abs()") z = fabs(first);
                else if (s == "grad()") z = first * (PI / 180);
                else if (s == "sgn()") {
                    if (first > 0) z = 1.0;
                    else if (first == 0) z = 0.0;
                    else z = -1.0;
                }
                else {
                    exit(0);
                }
            }
        }
        else z = nan("1");

        if (isnan(z) || isinf(fabs(z))) return nan("1");
        else Stek1.push(z);
    }
    first = Stek1.top();
    Stek1.pop();
    if (first == -0.0) return 0;
    if (isnan(first) || isinf(fabs(first))) return nan("1");
    else return first;
}
