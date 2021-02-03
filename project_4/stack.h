//
//  stack.h
//  danmu-mac
//
//  Created by florrie on 2020/10/24.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef stack_h
#define stack_h
#include <iostream>
#include <string>
using namespace std;

template <typename Type>
class Stack{
private:
    class stackNode {
    public:
        Type data;
        stackNode * link;
        stackNode(stackNode * p = NULL) {link = NULL;}
        stackNode(Type& t,stackNode * p = NULL) {data = t;link = NULL;}
        ~stackNode(){};
    };
    stackNode * top;
    int m_length;

public:
    Stack(stackNode * p=NULL) {top=NULL;m_length=0;} //构造函数
    ~Stack(){}; //析构函数
    void push(Type& x); //x元素进栈
    bool pop(Type& x); //栈顶元素出栈，并返回该栈顶元素
    bool getTop(Type& x); //读取栈顶元素
    bool isEmpty(); //判断栈是否为空
    int getSize(); //读取栈中元素个数
    void makeEmpty(); //清空栈
};


template <typename Type>
bool Stack<Type>::isEmpty()
{
    if(top==NULL) return true;
    else return false;
}

template <typename Type>
void Stack<Type>::push(Type& x )
{
    stackNode * newnode;
    newnode=new stackNode(x,top);
    newnode->link=top;
    top=newnode;
    getSize();
}

template <typename Type>
bool Stack<Type>::pop(Type& x)
{
    if(isEmpty()) return false;
    x=top->data;
    stackNode * del=top;
    top=top->link;
    delete del;
    getSize();
    return true;
}

template <typename Type>
bool Stack<Type>::getTop(Type& x)
{
    if(isEmpty()) return false;
    x=top->data;
    return true;
}

template <typename Type>
int Stack<Type>::getSize()
{
    stackNode * p=top;
    int size=0;
    while(p!=NULL) {
        size++;
        p=p->link;
    }
    m_length=size;
    return size;
}

template <typename Type>
void Stack<Type>::makeEmpty()
{
    int i=0;
    Type temp;
    while(i < m_length) {
        pop(temp);
        i++;
    }
}
#endif /* stack_h */
