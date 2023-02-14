//
// Created by goolyuyi on 2/10/2023.
//
#include "dog-lib.h"
#include <cassert>
#include <iostream>

int main(int argc, char *argv[]) {
    assert(get_age() == 3);
    std::cout << "dog-lib test passed!" << std::endl;
    return 0;
}