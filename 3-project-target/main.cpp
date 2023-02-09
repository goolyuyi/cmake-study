//
// Created by goolyuyi on 2/8/2023.
//
void cat();

#include <iostream>
#include "dog-lib.h"

int main(int argc, char *argv[]) {
    cat();
    dog();

#ifdef FOO_FLAG
    using namespace std;
    cout<<"main::FOO_FLAG is defined"<<endl;
#endif

    return 0;
}