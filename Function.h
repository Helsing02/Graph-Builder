#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#define PI 3.14159265   

using namespace std;

class Function {
private:
    vector <string> expression;
    bool Letter(char);
    bool Digit(char);
    bool Operation(char);
    void CreateRPN(string);
public:
    Function(string);
    float GetY(float); 
    void Update(string);
};
