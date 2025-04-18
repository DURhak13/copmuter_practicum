#include <iostream>
#include "complex.h"
using namespace std;

Complex Complex::operator+(const Complex& other) const {
    return {real + other.real, imag + other.imag};
}

Complex Complex::operator-(const Complex& other) const {
    return {real - other.real, imag - other.imag};
}

Complex Complex::operator*(const Complex& other) const {
    return {
        real * other.real - imag * other.imag,
        real * other.imag + imag * other.real
    };
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    return {
        (real * other.real + imag * other.imag) / denominator,
        (imag * other.real - real * other.imag) / denominator
    };
}

void Complex::print() const {
    if (imag < 0)
        cout << real << " - " << -imag << "i";
    else
        cout << real << " + " << imag << "i";
}
