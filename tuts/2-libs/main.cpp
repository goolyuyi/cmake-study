
#include <iostream>
#include "yilib.h"

int main() {
    std::cout << "hello" << std::endl;
    std::cout << yilib::get_version() << std::endl;

#ifdef FOO
    std::cout << "FOO defined" << std::endl;
#endif
    return 0;
}