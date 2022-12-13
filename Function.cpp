﻿#include "Function.h"

using std::string;
using std::stack;
using std::map;
using std::cout;

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
                                { "log()", 5 },
                                { "log10()", 5 },
                                { "loga()", 5 } };
    stack <string> Stek;
    int len = (int)s.length();
    string symbols;
    int brackets = 0, dig = 0, checkabs = 0, countroot = 0, next = 0, previous = 0;
    bool minus_in_root = false;

    for (int i = 0; i < len; i++) {
        if (digit(s[i])) {
            if (i > 0) {
                previous = i - 1;
                while (previous > 0 && s[previous] == ' ') previous--;
                if (previous >= 0 && (!operation(s[previous]) && s[previous] != '(' && s[previous] != ',' && s[previous] != ' ')) return 4;
            }
            bool dot = false;
            symbols = s[i];
            while (digit(s[i + 1]) || (s[i + 1] == ' ') || (s[i + 1] == '.')) {
                if (digit(s[i + 1])) symbols += s[i + 1];
                if (s[i + 1] == '.') {
                    symbols += s[i + 1];
                    if (dot == false) dot = true;
                    else return 2;
                }
                i++;
            }
            m_expression.push_back(symbols);
            dig++;
        }
        else if (operation(s[i])) {
            if (i == len - 1) return 3;
            next = i + 1;
            while (next < len - 1 && s[next] == ' ') next++;
            if (s[next] == ')' && s[next] == ',') return 3;
            if (minus_in_root == true && operation(s[next])) return 3;
            int next2 = next + 1;
            while (next2 < len - 1 && s[next2] == ' ') next2++;
            if (operation(s[next]) && operation(s[next2])) return 3;

            if (i == 0 && s[i] != '-') return 2;
            previous = i;
            if (i > 0) {
                previous = i - 1;
                while (previous > 0 && s[previous] == ' ') previous--;
                if (i != 0 && s[previous] == '(' && operation(s[next])) return 3;
                if (previous == 0 && s[i] != '-') return 3;
                if ((s[i] != '-') && operation(s[previous])) return 3;

            }
            symbols = s[i];
            if ((s[i] == '-') && (previous == 0 || operation(s[previous]) || s[previous] == '(' || minus_in_root == true || (s[previous] == '|' && checkabs == true))) symbols = "~";
            while ((!Stek.empty()) && (operationPriority[Stek.top()] >= operationPriority[symbols])) {
                m_expression.push_back(Stek.top());
                Stek.pop();
            }
            minus_in_root = false;
            Stek.push(symbols);
        }
        else if (letter(s[i])) {
            if (i > 0) {
                previous = i - 1;
                while (previous > 0 && s[previous] == ' ') previous--;
                if (previous >= 0 && (!operation(s[previous]) && s[previous] != '(' && s[previous] != ',' && s[previous] != ' ')) return 4;
            }
            if (s[i] == 'x') {
                m_expression.push_back("x");
                dig++;
            }
            else if (s[i] == 'p') {
                if (s[i + 1] == 'i') {
                    m_expression.push_back("pi");
                    i++;
                    dig++;
                }
                else return 2;
            }
            else {
                int f = 0;
                switch (s[i]) {
                case 'r':
                    if ((s[i + 1] == 'o') && (s[i + 2] == 'o') && (s[i + 3] == 't') && (s[i + 4] == '(')) {
                        countroot++;
                        symbols = "root()";
                        i = i + 3;
                    }
                    else return 2;
                    break;
                case 'g':
                    if ((s[i + 1] == 'r') && (s[i + 2] == 'a') && (s[i + 3] == 'd')) {
                        symbols = "grad()";
                        i = i + 3;
                    }
                    else return 2;
                    break;
                case 's':
                    if ((s[i + 1] == 'i') && (s[i + 2] == 'n')) {
                        if (s[i + 3] == 'h') {
                            symbols = "sinh()";
                            i++;
                        }
                        else symbols = "sin()";
                        i = i + 2;
                    }
                    else if (s[i + 1] == 'h') {
                        symbols = "sinh()";
                        i++;
                    }
                    else return 2;
                    break;
                case 'c':
                    if ((s[i + 1] == 'o') && (s[i + 2] == 's')) {
                        if (s[i + 3] == 'h') {
                            symbols = "cosh()";
                            i++;
                        }
                        else symbols = "cos()";
                        i = i + 2;
                    }
                    else if (s[i + 1] == 'h') {
                        symbols = "cosh()";
                        i++;
                    }
                    else if ((s[i + 1] == 'o') && (s[i + 2] == 't') && (s[i + 3] == 'a') && (s[i + 4] == 'n')) {
                        if (s[i + 5] == 'h') {
                            symbols = "cotanh()";
                            i++;
                        }
                        else symbols = "cotan()";
                        i = i + 4;
                    }
                    else if ((s[i + 1] == 't') && (s[i + 2] == 'g')) {
                        if (s[i + 3] == 'h') {
                            symbols = "cotanh()";
                            i++;
                        }
                        else symbols = "cotan()";
                        i = i + 2;
                    }
                    else return 2;
                    break;
                case 't':
                    if ((s[i + 1] == 'a') && (s[i + 2] == 'n')) {
                        if (s[i + 3] == 'h') {
                            symbols = "tanh()";
                            i++;
                        }
                        else symbols = "tan()";
                        i = i + 2;
                    }
                    else if (s[i + 1] == 'g') {
                        if (s[i + 2] == 'h') {
                            symbols = "tanh()";
                            i++;
                        }
                        else symbols = "tan()";
                        i++;
                    }
                    else return 2;
                    break;
                case 'a':
                    if ((s[i + 1] == 'r') && (s[i + 2] == 'c')) f = f + 2;
                    if ((s[i + f + 1] == 's') && (s[i + f + 2] == 'i') && (s[i + f + 3] == 'n')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "asinh()";
                            i++;
                        }
                        else symbols = "asin()";
                        i = i + f + 3;
                    }
                    else if ((s[i + f + 1] == 'c') && (s[i + f + 2] == 'o') && (s[i + f + 3] == 's')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "acosh()";
                            i++;
                        }
                        else symbols = "acos()";
                        i = i + f + 3;
                    }
                    else if ((s[i + f + 1] == 't') && (s[i + f + 2] == 'a') && (s[i + f + 3] == 'n')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "atanh()";
                            i++;
                        }
                        else symbols = "atan()";
                        i = i + f + 3;
                    }
                    else if ((s[i + f + 1] == 't') && (s[i + f + 2] == 'g')) {
                        if (s[i + f + 3] == 'h') {
                            symbols = "atanh()";
                            i++;
                        }
                        else symbols = "atan()";
                        i = i + f + 2;
                    }
                    else if ((s[i + f + 1] == 'c') && (s[i + f + 2] == 'o') && (s[i + f + 3] == 't') && (s[i + f + 4] == 'a') && (s[i + f + 5] == 'n')) {
                        if (s[i + f + 6] == 'h') {
                            symbols = "acotanh()";
                            i++;
                        }
                        else symbols = "acotan()";
                        i = i + f + 5;
                    }
                    else if ((s[i + f + 1] == 'c') && (s[i + f + 2] == 't') && (s[i + f + 3] == 'g')) {
                        if (s[i + f + 4] == 'h') {
                            symbols = "acotanh()";
                            i++;
                        }
                        else symbols = "acotan()";
                        i = i + f + 3;
                    }
                    else if ((s[i + 1] == 'b') && (s[i + 2] == 's')) {
                        symbols = "abs()";
                        i = i + 2;
                    }
                    else return 2;
                    break;
                case 'e':
                    if (s[i + 1] == '^') {
                        symbols = "exp()";
                        i++;
                    }
                    else if ((s[i + 1] == 'x') && (s[i + 2] == 'p')) {
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
                    if ((s[i + 1] == 'n')) {
                        symbols = "log()";
                        i++;
                    }
                    else if ((s[i + 1] == 'o') && (s[i + 2] == 'g') && (s[i + 3] == '1') && (s[i + 4] == '0') && (s[i + 5] == '(')) {
                        symbols = "log10()";
                        i = i + 4;
                    }
                    else if ((s[i + 1] == 'o') && (s[i + 2] == 'g')) {
                        if (s[i + 3] == '(') {
                            int k = i;
                            while (s[k] != ')') k++;
                            if (s[k + 1] == '(') symbols = "loga()";
                            else symbols = "log()";
                        }
                        else {
                            if (digit(s[i + 3]) || letter(s[i + 3])) symbols = "loga()";
                        }
                        i = i + 2;
                    }
                    else return 2;
                    break;
                default:
                    return 2;
                    break;
                }
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
            int w = 0;
            switch (s[i]) {
            case '|':
                if (checkabs == 0) {
                    while ((!Stek.empty()) && (operationPriority[Stek.top()] >= operationPriority["abs()"])) {
                        m_expression.push_back(Stek.top());
                        Stek.pop();
                    }
                    Stek.push("abs()");
                    Stek.push("(");
                    brackets++;
                    checkabs++;
                }
                else {
                    while ((!Stek.empty()) && (Stek.top() != "(")) {
                        m_expression.push_back(Stek.top());
                        Stek.pop();
                    }
                    if (Stek.top() == "(") Stek.pop();
                    brackets--;
                    checkabs--;
                }
                break;
            case '(':
                if (i == len - 1) return 1;
                next = i + 1;
                while (next < len - 1 && s[next] == ' ') next++;
                if (s[next] == ')') return 4;
                if (s[next] == ' ' && next == len - 1) return 4;
                Stek.push("(");
                brackets++;
                break;
            case ')':
                if ((i == 0) || (brackets == 0)) return 1;
                next = i;
                while (i != len - 1 && next < len - 1 && s[next] == ' ') next++;
                if ((i != len - 1) && !operation(s[next]) && s[next] != ')' && s[next] != ',') return 2;
                while ((!Stek.empty()) && (Stek.top() != "(")) {
                    m_expression.push_back(Stek.top());
                    Stek.pop();
                }
                if (Stek.top() == "(") Stek.pop();
                brackets--;
                break;
            case ' ':
                break;
            case ',':
                if (countroot > 0) {
                    w = i - 1;
                    while (s[w] == ' ') w--;
                    if (s[w] == '(') return 4;
                    w = i + 1;
                    while (s[w] == ' ') w++;
                    i = w - 1;
                    if (s[w] == '-') minus_in_root = true;
                    else if (!digit(s[w]) && !letter(s[w]) && s[w] != '(') return 2;
                    while ((!Stek.empty()) && (Stek.top() != "(")) {
                        m_expression.push_back(Stek.top());
                        Stek.pop();
                    }
                    countroot--;
                }
                else return 4;
                break;
            default:
                return 2;
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
    if ((dig == 0) || (countroot != 0)) return 4;
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

    for (string s : m_expression) {
        if (digit(s[0])) {
            double l = 0, number = 0;
            for (int j = 0; j < s.length(); j++) {
                if (s[j] == '.') l = s.length() - j - 1;
                else number = number * 10 + ((double)s[j] - 48);
            }
            number = number / pow(10, l);
            Stek1.push(number);
        }
        else if (operation(s[0])) {
            second = Stek1.top();
            Stek1.pop();
            first = Stek1.top();
            Stek1.pop();
            switch (s[0]) {
            case '+':
                Stek1.push(first + second);
                break;
            case '-':
                Stek1.push(first - second);
                break;
            case '*':
                Stek1.push(first * second);
                break;
            case '/':
                //if (second == 0) return MAX;
                Stek1.push(first / second);
                break;
            case '^':
                double z = pow(first, second);
                Stek1.push(z);
                break;
            }
        }
        else if (s[0] == '~') {
            first = Stek1.top();
            Stek1.pop();
            double z = 0 - first;
            Stek1.push(z);
        }
        else if (letter(s[0])) {
            if (s == "loga()") {
                second = Stek1.top();
                Stek1.pop();
                first = Stek1.top();
                Stek1.pop();
                //if (first == 1 || first < 0) return MAX;
                double z = (log10(second)) / (log10(first));
                Stek1.push(z);
            }
            else if (s == "root()") {
                second = Stek1.top();
                Stek1.pop();
                first = Stek1.top();
                Stek1.pop();
                double z = pow(abs(first), 1.0 / second);
                if (first < 0 && (floor(second) == second) && ((int)second % 2 != 0)) z = 0 - z;
                //if (first < 0 && (floor(second) == second) && ((int)second % 2 == 0)) return MAX;
                Stek1.push(z);
            }
            else if (s == "x") Stek1.push(x);
            else if (s == "pi") Stek1.push(PI);
            else if (s == "e") Stek1.push(exp(1));
            else {
                first = Stek1.top();
                Stek1.pop();
                if (s == "sin()") Stek1.push(sin(first));
                else if (s == "sinh()") Stek1.push(sinh(first));
                else if (s == "cos()") Stek1.push(cos(first));
                else if (s == "cosh()") Stek1.push(cosh(first));
                else if (s == "tan()") Stek1.push(tan(first));
                else if (s == "tanh()") Stek1.push(tanh(first));
                else if (s == "cotan()") Stek1.push(1 / (tan(first)));
                else if (s == "cotanh()") {
                    double z = (exp(first) + exp(0.0 - first)) / (exp(first) - exp(0.0 - first));
                    Stek1.push(z);
                }
                else if (s == "asin()") Stek1.push(asin(first));
                else if (s == "asinh()") Stek1.push(asinh(first));
                else if (s == "acos()") Stek1.push(acos(first));
                else if (s == "acosh()") Stek1.push(acosh(first));
                else if (s == "atan()") Stek1.push(atan(first));
                else if (s == "atanh()") Stek1.push(atanh(first));
                else if (s == "acotan()") Stek1.push(PI / 2.0 - atan(first));
                else if (s == "acotanh()") {
                    double z = 1.0 / 2 * log((first + 1) / (first - 1));
                    Stek1.push(z);
                }
                else if (s == "log()") Stek1.push(log(first));
                else if (s == "log10()") Stek1.push(log10(first));
                else if (s == "exp()") Stek1.push(exp(first));
                else if (s == "abs()") Stek1.push(abs(first));
                else if (s == "grad()") Stek1.push(first * (PI / 180));
                else {
                    cout << "Error when finding Y";
                    exit(0);
                }
            }
        }
        else {
            cout << "Error when finding Y";
            exit(0);
        }
    }
    first = Stek1.top();
    Stek1.pop();
    return first;
}