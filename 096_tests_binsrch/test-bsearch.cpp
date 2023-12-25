#include <cmath>
#include <iostream>
#include <cstdio>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
protected:
    unsigned remaining;
    Function<int, int> * f;
    const char * mesg;

public:
    CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) : remaining(n), f(fn), mesg(m) {}
    virtual int invoke(int arg) {
        if (remaining == 0) {
            fprintf(stderr, "Too many function invocations in %s\n", mesg);
            exit(EXIT_FAILURE);
        }
        remaining--;
        return f->invoke(arg);
    }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
    int maxNum;
    //max invocations of f
    if (high > low) {
        maxNum = log(high - low) / log(2) + 1;
    }
    else {
        maxNum = 1;
    }
    CountedIntFn * function = new CountedIntFn(maxNum, f, mesg);
    //perform the binary search
    int res = binarySearchForZero(function, low, high);
    //check the answer
    if (res != expected_ans) {
        fprintf(stderr, "The result of funtion %s is wrong!\n", mesg);
        exit(EXIT_FAILURE);
    }
}

class SinFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return 10000000 * (sin(arg/100000.0) - 0.5);
    }
};

class PositiveConstantFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return 10; 
    }
};

class NegativeConstantFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return -10;
    }
};

class PositiveGradientFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return 2 * arg + 4;
    }
};

class NegativeGradientFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return -2 * arg + 4;
    }
};

class QuadraticFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return pow((arg-5), 2);
    }
};

class CubicFunction : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return pow((arg-5), 3);
    }
};

int main(int argc, char ** argv) {
    SinFunction sf;
    PositiveConstantFunction pf;
    NegativeConstantFunction nf;
    PositiveGradientFunction pgf;
    NegativeGradientFunction ngf;
    QuadraticFunction qf;
    CubicFunction cf;

    check(&sf, 0, 150000, 52359, "Sin in range[0, 150000])");
    check(&pf, 0, 10, 0, "positive constant function in range[0, 10]");
    check(&pf, -10, 10, -10, "positive constant function in range[-10, 10]");
    check(&nf, 0, 100, 99, "negative constant function in range[-10, 10]");
    check(&pgf, 0, 100, 0, "positive gradient function in range[0, 100]");
    check(&pgf, -10, 100, -2, "positive gradient function in range[-10, 100]");
}