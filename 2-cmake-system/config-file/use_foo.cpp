//
// Created by 于一 on 2023/2/14.
//

#include "foo.h"
#include <iostream>

int main() {
#ifdef FOO_ENABLE
    std::cout<< FOO_STRING<< std::endl;
#endif
    return 0;
}