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
public:
    Function(string);//конструктор
    void CreateRPN(string);//построение полиза
    float GetY(float); //медот для вычисления координаты Y по координате X
    void Update(string);//обновляет полиз
};