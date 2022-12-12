#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#include <algorithm>
#define PI 3.14159265  

class Function {
private:
    std::vector <std::string> m_expression;
    bool letter(char);
    bool digit(char);
    bool operation(char);
    int set_rpn(std::string);
    
public:
    int set_exp(std::string);
    double get_y(double);
};