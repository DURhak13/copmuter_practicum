#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex {
    double real;
    double imag;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    void print() const;
};

#endif
