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
    friend class Counter;
private:
    class QueueNode {
    public:
        Type data; //模版类型为Type的data域
        QueueNode *link;
        QueueNode(QueueNode *p = nullptr) {link = nullptr;}//构造函数
        QueueNode(Type d = 0,QueueNode *p = nullptr) {data = d;link = nullptr;} //构造函数2
        ~QueueNode(){};//析构函数
    };
    
    QueueNode *first,*rear; //用尾插入方法建立链表，除头指针外还需要尾指针
    int m_length; //队列中元素个数
    void showQueue(); //打印队列元素
    
public:
    Queue(QueueNode *p = nullptr,QueueNode *q = nullptr){first = p;rear = q;m_length = 0;}
    ~Queue(){};
    void enQueue(Type x);//x进队列
    Type deQueue(); //让队首元素出队，返回值是队首元素
    int getSize(); //统计、返回队列中剩余元素个数
    bool getFront(Type x);//取队首元素，若队列为空则返回false
    bool isEmpty();//判断队列是否为空
    void makeEmpty();//清空队列
};

template <typename Type>
bool Queue<Type>::isEmpty() {
    if(first == nullptr) return true;//头指针为空，则队列为空
    else return false;
}

template <typename Type>
void Queue<Type>::enQueue(Type x) {
    QueueNode *newnode = new QueueNode(x);
    if(first == nullptr) { //插入的作为头节点时，需更新first指针
        first = newnode;//头指针是newnode
        rear = newnode;//尾指针也是
    }
    else { //插入的作为非头节点，只需更新rear指针
        rear->link = newnode;//新节点连到原队尾节点上
        rear = newnode;//更新rear指针
    }
    getSize();
}

template <typename Type>
Type Queue<Type>::deQueue() {
    Type x;//用做返回值
    if(isEmpty()) return -1;//若队列为空
    x = first->data; //不空，将队首元素值赋给x
    QueueNode *del = first;
    first = first->link; //更新队首元素
    delete del; //释放原来的队首元素
    getSize(); //重新统计队列中元素个数
    return x;
}

template <typename Type>
bool Queue<Type>::getFront(Type x) {
    if(isEmpty()) return false;//若队列为空，返回false
    x = first->data;//不空，将队首元素值赋给引用参数x
    return true;
}

template <typename Type>
int Queue<Type>::getSize() {
    QueueNode *p = first;
    int len = 0;
    while(p != nullptr) {
        len++;
        p = p->link;
    }
    m_length = len;
    return len;
}

template <typename Type>
void Queue<Type>::makeEmpty() {
    int i = 0;
    while(i < m_length) {
        deQueue();//让元素逐一出队
        i++;
    }
    m_length = 0;//置队中元素个数为0
}

template <typename Type>
void Queue<Type>::showQueue() {
    int i = 0;
    QueueNode *current = first;
    for(i = 0;i < m_length;i++) {
        cout << current->data << " ";//输出current的data域
        current = current->link;//current后移
    }
    cout<<endl;
}

#endif /* queue_h */
