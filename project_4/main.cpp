//
//  main.cpp
//  danmu-mac
//
//  Created by florrie on 2020/10/24.
//  Copyright © 2020 Florrie. All rights reserved.
//

#include "calculator.h"
int main() {
    Calculator cal;
    char ifContinue;//是否继续输入下一个要计算的表达式
    while(1){
        cal.input();
        cal.convert();
        double result = cal.calculate();
        cout << "result is " << result << endl;
        cout << "----------------------------" << endl;
        cout << "是否继续？输入y以继续，输入n以结束" << endl;
        cin >> ifContinue;
        if(ifContinue == 'n') {cout << "进程已结束!" << endl;break;}
    }
    return 0;
}
