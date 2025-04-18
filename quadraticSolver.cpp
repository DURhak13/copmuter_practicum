#include <iostream>
#include <cmath>
#include "quadraticSolver.h"
using namespace std;

void solveQuadratic(double a, double b, double c) {
    if (a == 0) {
        cout << "Это не квадратное уравнение." << endl;
        return;
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        double x1 = (-b + sqrt(discriminant)) / (2 * a);
        double x2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "Корни уравнения: x1 = " << x1 << ", x2 = " << x2 << endl;
    } else {
        double realPart = -b / (2 * a);
        double imagPart = sqrt(-discriminant) / (2 * a);
        Complex x1{realPart, imagPart};
        Complex x2{realPart, -imagPart};
        cout << "Комплексные корни: x1 = ";
        x1.print();
        cout << ", x2 = ";
        x2.print();
        cout << endl;
    }
}
