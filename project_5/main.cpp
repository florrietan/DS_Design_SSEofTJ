//
//  main.cpp
//  project5-mac
//
//  Created by florrie on 2020/10/25.
//  Copyright © 2020 Florrie. All rights reserved.
//
#include "counter.h"
int main() {
    Counter bank;
    bank.initialize();
    bank.output();
    cout<<"进程已结束"<<endl;
    return 0;
}
