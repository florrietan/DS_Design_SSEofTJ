//
//  main.cpp
//  project 1
//
//  Created by florrie on 2020/10/8.
//  Copyright © 2020 florrie. All rights reserved.
//

#include "StuNode&List.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    StuList slist;
    slist.set_list();
    slist.show_list();
    int choice=9999;   //1插入，2删除，3查找，4修改，0退出
    while(choice){
        cout<<"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，0为退出）"<<endl;
        cin>>choice;
        bool show=true; //若操作是有效操作（即未越界、非结束的0）则打印表单
        switch (choice) {
            case 0: show=false;break;
            case 1: slist.insert();break;
            case 2: slist.remove();break;
            case 3: slist.search();break;
            case 4: slist.edit();break;
            default: cout<<"您输入的操作不存在！请重新选择0、1、2、3、4中的一个操作"<<endl;show=false;break;
        }
        if(show!=false) slist.show_list();
    }
    cout<<"已结束操作"<<endl;
    return 0;
}
