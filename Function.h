#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <stack>

#define PI 3.14159265   

class Function
{
private:
    std::vector <std::string> m_expression;
    bool letter(char);
    bool digit(char);
    bool operation(char);
    int create_RPN(std::string);
public:
    double get_y(double);
    int set_exp(std::string);
};
