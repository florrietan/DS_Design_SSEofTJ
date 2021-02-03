//
//  main.cpp
//  project2-mac
//
//  Created by florrie on 2020/10/10.
//  Copyright © 2020 Florrie. All rights reserved.
//
#include "intersection.h"
#include <iostream>
using namespace std;

int main()
{
    numList s1,s2,s3;
    cout<<"请输入链表1的数据，以-1结束:"<<endl;
    s1.input();
    cout<<"请输入链表2的数据，以-1结束:"<<endl;
    s2.input();
    s3=s1*s2;
    cout<<"链表1、链表2的交集为："<<endl;
    s3.display();
    return 0;
}
