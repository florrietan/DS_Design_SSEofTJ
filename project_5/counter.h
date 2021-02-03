//
//  counter.h
//  project5-mac
//
//  Created by florrie on 2020/10/25.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef counter_h
#define counter_h
#include "queue.h"
using namespace std;

class Counter {
private:
    int num;//顾客总人数
    Queue<int> A,B;//A、B两个队列代表A、B两个柜台
    
public:
    void initialize();//初始化 输入顾客信息
    void output(); //按照柜台要求输出处理完成的顾客编号
};

void Counter::initialize() {
    cout << "请输入数据,第一个数字为总人数，后面为顾客编号，以空格隔开:" << endl;
    while(1) {
        cin >> num;
        if(num <= 0) cout << "输入非法！请重新输入一个正整数作为总人数：" << endl;
        else break;
    }
    int i = 0,j = 0;//i表示A队列中已有元素个数、j表示B队列中已有元素个数
    int temp = 0;//temp用于每次输入顾客编号
    for(;i+j < num;) {//A、B中元素总合达到总人数时循环结束
        while(1) {
            cin >> temp;
            if(temp <= 0) cout << "输入非法！请重新输入一个正整数作为序号：" << endl;
            else break;
        }
        if(temp%2 == 1) {A.enQueue(temp);i++;} //奇数放到A中
        else {B.enQueue(temp);j++;} //偶数放到B中
    }
//    cout << "A柜台有客户:";
//    A.showQueue();
//    cout <<"B柜台有客户:";
//    B.showQueue();
}

void Counter::output() {
    cout << "输出为:" << endl;
    int i = 0,j = 0;//i表示A中已经输出的元素个数，j表示B中已经输出的元素个数
    int temp = 0;//temp是从A、B中取出的队首元素
    for(;i+j < num;){
        //若A、B有一个为空
        if(A.getSize() == 0){//若A已为空
            while(B.getSize()){//让B中元素逐个出队、并输出
                temp = B.deQueue();
                cout << temp;
                if(B.getSize() != 0) cout << " ";//不是最后一个元素，则需输出空格
            }
            break;
        }
        if(B.getSize() == 0) {//若B已为空
            while(A.getSize()) {//让A中元素逐个出队、并输出
                temp = A.deQueue();
                cout << temp << " ";
                temp = A.deQueue();
                cout << temp;
                if(A.getSize() != 0) cout << " ";//不是最后一个元素，则需输出空格
            }
            break;
        }
        //这一段是处理A柜台
        if(A.getSize() >= 2) { //A中至少还有两个元素时
            i = i+2;//从A队列中取出两个元素并输出
            temp = A.deQueue();
            cout << temp << " ";
            temp = A.deQueue();
            cout << temp;
            if(i+j != num) cout << " ";//不是最后一个元素，则需输出空格
        }
        else if(A.getSize() == 1) { //A中还有一个元素时
            i++;//只能取出A中仅剩的一个元素
            temp = A.deQueue();//A已空
            cout << temp;
            if(i+j != num) cout << " ";//不是最后一个元素，则需输出空格
        }
        //然后处理B柜台
        if(B.getSize()) {  //若B不为空
            j++;//从队列B中取出一个元素
            temp = B.deQueue();
            cout << temp;
            if(i+j != num) cout << " ";//不是最后一个元素，则需输出空格
        }
    }
    cout<<endl;
}

#endif /* counter_h */
