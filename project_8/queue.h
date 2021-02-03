//
//  queue.h
//  project5-mac
//
//  Created by florrie on 2020/10/25.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef queue_h
#define queue_h
#include <iostream>
using namespace std;


template <typename Type>
class Queue {
private:
    class queueNode {
    public:
        Type data;
        queueNode * link;
        queueNode(queueNode *p = nullptr) {link = nullptr;}
        queueNode(Type d = 0,queueNode * p = nullptr) {data = d;link = nullptr;}
        ~queueNode(){};
    };
    
    queueNode *first,*rear;
    int length;
    void showQueue();
public:
    Queue(queueNode *p = nullptr,queueNode *q = nullptr){first = p;rear = q;length = 0;}
    ~Queue(){};
    void enQueue(Type x);
    Type deQueue();
    int getSize();
    bool getFront(Type x);
    bool isEmpty();
    void makeEmpty();
};

template <typename Type>
bool Queue<Type>::isEmpty()
{
    if(first == nullptr) return true;//头指针为空，则队列为空
    else return false;
}

template <typename Type>
void Queue<Type>::enQueue(Type x)
{
    queueNode *newnode = new queueNode(x);
    if(first == nullptr) { //插入的作为头节点时，需更新first指针
        first = newnode;
        rear = newnode;
    }
    else { //插入的作为非头节点，只需更新rear指针
        rear->link = newnode;
        rear = newnode;
    }
    getSize();
}

template <typename Type>
Type Queue<Type>::deQueue()
{
    Type x ;
    if(isEmpty()) return -1;
    x = first->data;
    queueNode *del = first;
    first = first->link;
    delete del;
    getSize();
    return x;
}

template <typename Type>
bool Queue<Type>::getFront(Type x)
{
    if(isEmpty()) return false;
    x = first->data;
    return true;
}

template <typename Type>
int Queue<Type>::getSize()
{
    queueNode *p=first;
    int len=0;
    while (p!=nullptr) {
        len++;
        p=p->link;
    }
    length=len;
    return len;
}

template <typename Type>
void Queue<Type>::makeEmpty()
{
    int i=0;
    while(i<length) {
        deQueue();
        i++;
    }
}

template <typename Type>
void Queue<Type>::showQueue()
{
    int i = 0;
    queueNode *current = first;
    for(i = 0;i < length;i++) {
        cout << current->data << " ";
//        deQueue(temp);
//        cout<<temp<<" ";
        current = current->link;
    }
    cout<<endl;
}

#endif /* queue_h */
