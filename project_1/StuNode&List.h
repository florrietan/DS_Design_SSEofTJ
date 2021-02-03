//"StuNode&List.h"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class StuNode{
friend class StuList;
private:
    int number;
    string name;
    string gender;
    int age;
    string post;
    StuNode *link;
public:
    StuNode(int num=0,string name_="stu0",string gender_="男",int age_=0,string post_="无",StuNode *p=NULL){
        number=num;
        name=name_;
        gender=gender_;
        age=age_;
        post=post_;
        p=NULL;
    }
};

class StuList{
private:
    StuNode *first,*last;
    int length;
public:
    StuList();   //构造函数
    void set_list();  //创建表，建立学生的信息
    void show_list(); //打印表单

    StuNode * search();   //按学号搜索学生，并返回该学生的地址
    bool insert();  //将学生插入到链表逻辑顺序上的第x个位置
    void edit();  //修改指定学号的学生的信息
    void remove(); //删除指定学号的学生的信息
};



//"StuNode&List.cpp"

StuList::StuList()
{
    first=new StuNode;
    first->link=NULL;
    last=first;
}

void StuList::set_list()
{
    int number,age;
    string gender,name,post;
    cout<<"首先请建立考生系统!"<<endl<<"请输入考生人数:";
    cin>>length;
    while(length<1){      //循环检查是否越界，输入合法则退出本循环
        cout<<"输入非法！人数需为正整数，请重新输入"<<endl<<"请输入考生人数：";
        cin>>length;
    }
    cout<<"请依次输入考生的考号，姓名，性别，年龄及报考类别"<<endl;
    for(int i=0;i<length;i++) {
        cin>>number>>name>>gender>>age>>post;
        StuNode *newnode=new StuNode(number,name,gender,age,post);//调用StuNode类的构造函数
        last->link=newnode; //后插入法建立链表，插入到last节点后
        last=newnode; //更新last节点为newnode
    }
    cout<<endl;
}

void StuList::show_list()
{
    StuNode *current=first->link;  //已经指向头节点后的第一个节点
    cout<<"---------------table below---------------"<<endl;  //表单的分割线
    cout<<setw(4)<<"考号"<<setw(6)<<"姓名"<<setw(6)<<"性别"<<setw(6)<<"年龄"<<setw(10)<<"报考类别"<<endl;
    for(int i=0;i<length;i++) {
        cout<<setw(4)<<current->number<<setw(10)<<current->name<<setw(6)<<current->gender<<setw(6)<<current->age<<setw(8)<<current->post<<endl;
        current=current->link;
    }
    cout<<"---------------table above---------------"<<endl<<endl; //表单的分割线
}


StuNode * StuList::search()
{
    int num;
    bool exist=false;
    StuNode *current=first->link;
    cout<<"请输入您要查找的考生的考号：";
    cin>>num;
    while(!exist){
        current=first->link;  //指向头节点后的第一个有效节点
        while(current!=NULL){
            if(current->number==num) {exist=true;break;} //找到该生，跳出内层循环
            else current=current->link; //否则后移
        }  //此循环结束时，可能已查到该学生，也可能是current指向了null（到达表尾）
        if(exist==true) break; //该生存在，跳出外层循环，将开始后续的信息输出
        cerr<<"输入错误！未找到学号为"<<num<<"的学生，请重新输入："<<endl; //该生不存在，重新输入
        cin>>num;
    }
   cout<<"您查找的"<<num<<"号考生信息如下："<<endl<<setw(4)<<"考号"<<setw(10)<<"姓名"<<setw(6)<<"性别"<<setw(6)<<"年龄"<<setw(10)<<"报考类别"<<endl;
    cout<<setw(4)<<current->number<<setw(10)<<current->name<<setw(6)<<current->gender<<setw(6)<<current->age<<setw(8)<<current->post<<endl<<endl;
    current=current->link;

    return current;
}

bool StuList::insert()
{
    int position;
    cout<<"请输入您要插入的考生的位置：";
    cin>>position;
    while(position>length+1||position<1) {
        cerr<<"输入越界!输入范围应是1～"<<length+1<<"之间的正整数，请重新输入位置："<<endl;
        cin>>position;
    } //position范围是1～length+1，循环检查；
    cout<<"请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别"<<endl;
    int number,age;
    string name,post,gender;
    cin>>number>>name>>gender>>age>>post;
    StuNode *newnode=new StuNode(number,name,gender,age,post);
    if(newnode==NULL) {cerr<<"分配失败"<<endl;return false;}
    StuNode *current=first;  //指向头指针
    for(int i=1;i<=length+1;i++){
        if(i==position) break; //current指向插入位置前到那一个节点时break
        current=current->link; //否则后移
    }
    newnode->link=current->link; //将newnode节点链接到current后面
    current->link=newnode;
    length++;  //插入一个人后将length计数器+1
    return true;
}

void StuList::edit()
{
    cout<<"请输入您要修改信息的考生的考号：";
    int num;
    bool exist=false;
    StuNode *current=first->link;  //已指向头节点后的第一个节点
    cin>>num;
    while(!exist){
        current=first->link; //指向头节点后的第一个有效节点
        for(int i=1;i<length+1;i++){
            if(current->number==num) {exist=true;break;} //如果找到则退出内层循环
            current=current->link; //否则后移
        }
        if(exist==true) break; //该生存在，跳出外层循环、准备输入新的信息
        cerr<<"输入错误！未找到学号为"<<num<<"的学生，请重新输入："<<endl;
        cin>>num;
    }
    cout<<"请依次输入考生的考号，姓名，性别，年龄及报考类别"<<endl;
    int number,age;
    string name,post,gender;
    cin>>number>>name>>gender>>age>>post;
    current->number=number;
    current->name=name;
    current->gender=gender;
    current->age=age;
    current->post=post;
}

void StuList::remove()
{
    cout<<"请输入您要删除的考生的考号：";
    int num;
    bool exist=false;
    cin>>num;
    StuNode *current,*del;
    while(!exist){
        current=first; //current从头节点开始，current一直在del前一个
        del=first->link;  //del从头节点后的第一个有意义节点开始，del是要删除的
        while((del->number!=num)&&(del->link!=NULL)){ //判断del是否指向删除节点或为空
            current=del; //current、del一起后移
            del=del->link;
        } //循环结束时，要么是已经到了链尾，要么是已经找到了指定学号的考生
        if(del->number!=num) {  //该生不存在
            cerr<<"输入错误！未找到学号为"<<num<<"的学生，请重新输入："<<endl;
            cin>>num;
            continue;
        }
        else {  //存在，删除
            exist=true;
            current->link=del->link;
            length--;  //记得将length计数器-1
            delete del;
        }
    }
}
#pragma once
