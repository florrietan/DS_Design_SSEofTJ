//
//  intersection.h
//  project2-mac
//
//  Created by florrie on 2020/10/10.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef intersection_h
#define intersection_h


#include <iostream>
using namespace std;

class numNode{
friend class numList;
private:
    int digit;  //存储数值
    numNode *link; //指针域
public:
    numNode(int num=-1,numNode *link=NULL){digit=num;link=NULL;} //有默认参数的构造函数
    ~numNode(){}; //析构函数
};

class numList{
private:
    numNode *first,*last; //first指向头节点，last用于后插入法建立链表
    int length; //记录链表长度
public:
    numList(); //构造函数
    void input(); //输入函数
    void display(); //打印函数
    numList operator*(numList lst); //重载*以实现求交集
    void operator=(numList lst); //重载=以复制链表
};

numList::numList()
{
    first=new numNode;
    last=first;
    length=0;
    if(first==NULL) cerr<<"创建新节点失败！"<<endl;
}

void numList::input()
{
    bool legal=true; //检查输入是否合法，默认是合法的
    while(1){
        int num;
        cin>>num; //输入数据
        if(num<1&&num!=-1) { //若输入不合法
            cerr<<"输入非法！请重新输入，每个数均需为正整数："<<endl;
            legal=false; //不合法
        }
        if(num==-1&&legal==false) { //如果已有不合法数据存在
            legal=true; //重置为合法
            last=first; //尾指针重新回到开头，前面输入的数据全都无效
            length=0; //长度也要记得置零
            continue;} //在输入不合法的情况下，读到-1应被跳过;且结束这轮越界的输入后，记得重置legal为true,将last指针重新指向头节点
        if(num==-1&&legal==true) break; //若输入全都合法时，读到-1即停止输入，且-1不会存入链表中！
        
        numNode *newnode=new numNode(num); //调用构造函数新建节点
        last->link=newnode; //尾插入法向链表中添加新节点
        last=newnode; //更新尾指针
        length++; //长度+1
    }
}

void numList::display()
{
    numNode *current=first->link;//指向第一个有效节点
    if(length==0) cout<<"NULL"; //空表，输出NULL
    for(int i=0;i<length;i++){ //非空，循环输出
        cout<<current->digit;
        if(i!=(length-1)) cout<<" ";//非最后元素后输出空格
        current=current->link;//current指针后移
    }
    cout<<endl;
}

numList numList::operator*(numList lst)
{   //重载的*符号的左操作数为链表1，右操作数为链表2（即lst）
    numList new_list; //新建一个作为return值的对象
    numNode *p,*q;
    numNode *newnode;
    int i=0,j=0;
    int len1=this->length,len2=lst.length;
    p=this->first->link; //p指向链表1的头指针后的第一个有效节点
    q=lst.first->link;//q指向链表2头指针后的第一个有效节点
    for(;i<len1&&j<len2;){  //若p、q有一个为空则无法进入本循环
        int dif=(p->digit)-(q->digit); //dif存s1、s2当前元素的差值
        if(dif==0){//当前元素相同，则放入第三个链表new_list中,p、q均后移!!!
            newnode=new numNode(p->digit,NULL); //调用构造函数新建节点
            if(newnode==NULL) {cerr<<"分配失败！"<<endl;}
            new_list.last->link=newnode; //后插入法插入新节点
            new_list.last=newnode; //更新尾节点
            new_list.length++; //长度++
            p=p->link; //当前指针后移
            q=q->link;
            i++;
            j++;
        }
        else if(dif>0){ //p指向节点的digit值大于q，则q向后移，p不动
            q=q->link; //s2的当前指针后移
            j++;
        }
        else { //p指向节点的digit值小于q，则p向后移，q不动
            p=p->link; //s1的当前指针后移
            i++;
        }
    } //while循环结束
    return new_list;
}

void numList::operator=(numList lst) //将lst对象复制给该对象（=的左操作数）
{
    this->first=lst.first;
    this->last=lst.last;
    this->length=lst.length;
}


#endif /* intersection_h */

