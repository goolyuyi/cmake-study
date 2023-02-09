//
// Created by goolyuyi on 2/11/2023.
//
#include <iostream>
#include <calc.h>

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

int main(int argc, char *argv[]) {
    using namespace std;
    cout << "hello" << endl;
    cout << add(1, 2) << endl;
    cout << "SHA:" << STRINGIFY(SHA) << endl;
    return 0;
}