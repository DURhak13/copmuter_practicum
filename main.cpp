#include <iostream>
#include <string>
#include "complex.h"
#include "quadraticSolver.h"
using namespace std;

int main() {
    string mode;
    cout << "\n Введите оператор (для комплексных чисел: +, -, *, /; И два комплексных числа ";
    cout << "\n Для квадратного уравнения: (quad), а также коэфиценты a , b , c ";

    while (true) {
        cin >> mode;

        if (mode == "quad") {
            double a, b, c;
            cout << "\nВведите коэффициенты ";
            cin >> a >> b >> c;
            solveQuadratic(a, b, c);
        }

        else if (mode == "+" || mode == "-" || mode == "*" || mode == "/") {
            Complex a, b, result;

            cout << "\nВведите первое число ";
            cin >> a.real >> a.imag;

            cout << "Введите второе число ";
            cin >> b.real >> b.imag;

            switch (mode[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }

            cout << "Результат: ";
            result.print();
            cout << endl;
        }
        // Если введен неверный оператор, завершить выполнение
        else {
            cout << "\n Неверный оператор. Программа завершена." << endl;
            break;
        }
    }

    return 0;
}
