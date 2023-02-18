//
// Created by 于一 on 2023/2/18.
//
#include <iostream>
#include <mathutil.h>
#include <math_symbol.h>

int main(int argc, char *argv[]) {
    using namespace std;
    cout << "the inverse of sqrt() is " << mathlib::getInvert(std::string("sqrt")) << endl;
    cout << "the delta symbol is " << mathlib::getSymbol(std::string("delta")) << endl;
    cout << "the Pi is:" << Pi << endl;

    mathlib::useOpenEXR();
    return 0;
}