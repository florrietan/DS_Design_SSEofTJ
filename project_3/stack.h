//
//  stack.h
//  project3-mac
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
class Stack {        
private:
    class StackNode {//嵌套定义了一个节点类
    public:
        Type data;//data域类型为Type
        StackNode *link;
        StackNode(StackNode *p = NULL) {link = NULL;}
        StackNode(Type &t,StackNode *p = NULL) {data = t;link = NULL;}
        ~StackNode(){};
    };
    StackNode *top;//栈顶指针
    int m_length; //统计栈中元素个数

public:
    Stack(StackNode *p = NULL) {top = NULL;m_length = 0;} //构造函数
    ~Stack(){}; //析构函数
    void push(Type& x); //x元素进栈
    bool pop(Type& x); //栈顶元素出栈，并返回该栈顶元素
    bool getTop(Type& x); //读取栈顶元素
    bool isEmpty(); //判断栈是否为空
    bool findEle(Type& x);
    int getSize(); //读取、计算栈中元素个数
    void makeEmpty(); //清空栈
};


/*Stack类函数定义*/

template <typename Type>
bool Stack<Type>::isEmpty() {
    if(top == NULL) return true;
    else return false;
}

template <typename Type>
void Stack<Type>::push(Type &x) {
    StackNode *newnode;
    newnode = new StackNode(x);//调用StackNode类构造函数
    newnode -> link = top;//将原栈顶元素链到新栈顶元素的link域
    top = newnode;//更新栈顶元素
    getSize();//重新统计、更新栈内元素个数
}

template <typename Type>
bool Stack<Type>::pop(Type &x) {
    if(isEmpty()) return false;//false若栈已为空，返回false
    x = top -> data; //通过引用返回出栈的栈顶元素的值
    StackNode *del = top; //删除指针指向原栈顶元素
    top = top -> link; //修改栈顶指针、指向新的栈顶元素，逻辑上删除栈顶元素
    delete del; //释放内存
    getSize(); //重新统计栈内元素个数
    return true;
}

template <typename Type>
bool Stack<Type>::getTop(Type &x) {
    if(isEmpty()) return false;
    x = top -> data;
    return true;
}

template <typename Type>
bool Stack<Type>::findEle(Type &x) {
    StackNode *p = top;
    int i = 0;
    for(i = 0;i < m_length;i++) {
        if(p->data == x) return true; //栈中找到目标元素，返回true
        else p = p->link; //否则指针后移，继续寻找
    }
    return false;
}

template <typename Type>
int Stack<Type>::getSize() {
    StackNode *p = top;
    int size = 0;
    while(p != NULL) {
        size++;
        p = p -> link;
    }
    m_length = size;
    return size;
}

template <typename Type>
void Stack<Type>::makeEmpty(){
    int i = 0;
    Type temp;
    while(i < m_length) {
        pop(temp);
        i++;
    }
}
#endif /* stack_h */
