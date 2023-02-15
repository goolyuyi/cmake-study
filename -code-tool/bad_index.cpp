//
// Created by goolyuyi on 2/10/2023.
//
#include <iostream>
#include <string>

void set_b(bool &b, const int val) {
    if (val > 1)
        b = true;
}

int main(int argc, char *argv[]) {
    const char *names[]{"aaaa", "bbbb"};

    std::string x{names[3]};
    std::cout << x << std::endl;

    bool b;
    set_b(b, argc);
    if (b)
        std::cout << "b is true" << std::endl;
}