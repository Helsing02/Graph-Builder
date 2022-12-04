#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#define PI 3.14159265   

class Function {
private:
    std::vector <std::string> expression;
    bool Letter(char);
    bool Digit(char);
    bool Operation(char);
    void CreateRPN(std::string);
public:
    Function(std::string);
    float GetY(float); 
    void Update(std::string);
};
