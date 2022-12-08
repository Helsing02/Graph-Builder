#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#include <algorithm>
#define PI 3.14159265  
#define MAX 2147483647

class Function {
private:
    std::vector <std::string> expression;
    bool Letter(char);
    bool Digit(char);
    bool Operation(char);
    
public:
    Function();
    int CreateRPN(std::string);
    double GetY(double);
    int Update(std::string);
};