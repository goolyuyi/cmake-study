//
// Created by goolyuyi on 2/9/2023.
//
#include <iostream>

void dog() {
    using namespace std;
    cout << "a husky" << endl;

#ifdef FOO_FLAG
    cout<<"dog-lib::FOO_FLAG is defined"<<endl;
#endif
}

int get_age(){
    return 3;
}