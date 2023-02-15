//
// Created by 于一 on 2023/2/15.
//

#include <iostream>
#include "api.h"
#include "dog-lib.h"

int main(int argc, char *argv[]) {
    using namespace std;
    cout << "welcome" << endl;

    printAPIVersion();

    dog();

    return 0;
}