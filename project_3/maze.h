//
//  maze.h
//  project3-mac
//
//  Created by florrie on 2020/12/6.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef maze_h
#define maze_h
#include "stack.h"
#include <iomanip>

class Coordinate {//作为StackNode节点数据的类型
friend class Maze;
private:
    int m_x;
    int m_y;
public:
    Coordinate(int x = 0,int y = 0) {
        m_x = x;
        m_y = y;
    }
    ~Coordinate(){};
    void input(int size){ //用于输入迷宫起点、终点的坐标
        while(1) {
            cin>>m_x>>m_y;
            if(m_x < 0 || m_y < 0 || m_x >= size || m_y >= size)
                cout << "请重新输入！起点、终点坐标请输入0~" << size-1 <<"之间的正整数：" << endl;
            else break;
        }
    }
    /*一些运算符重载*/
    bool operator==(Coordinate right){
        if(this->m_x == right.m_x && this->m_y == right.m_y) return true;
        else return false;
    }
    bool operator!=(Coordinate right){
        if(this->m_x == right.m_x && this->m_y == right.m_y) return false;
        else return true;
    }
    void operator=(Coordinate right){
        this->m_x = right.m_x;
        this->m_y = right.m_y;
    }
};


class Maze {
private:
    int **board;//用于动态开辟二维数组，存放迷宫中障碍物的分布情况
    int boardSize; //规定生成的迷宫大小是 boardSize * boardSize
    Coordinate entrance,exit;//两个Coordinate类对象，存放迷宫的起点和终点
    Stack<Coordinate> path;//实体化为Coordinate类的栈，存放走过的路径
    /*私有函数*/
    void showBoard(); //打印迷宫
    
    bool goUp(Coordinate &c,Coordinate &top) {//c是当前所处理的位置，top是栈顶元素的位置
        //向上移动，先检查纵轴方向是否会越界
        if(c.m_y-1 < 0) return false;
        else c.m_y--; //使当前点上移一格
        if(path.findEle(c) == true) { //若移动后的节点已经在栈中则表明重复回溯，则应换一个方向
            c.m_y++;//还原
            return false;
        }
        if(board[c.m_x][c.m_y] == 0 && c!=top)
            return true;//若邻格为0不是障碍、且不是来时的路径，可行
        else {
            c.m_y++;//还原
            return false;
        }
    }//使当前点上移一格
    
    bool goDown(Coordinate &c,Coordinate &top) {
        if(c.m_y+1 >= boardSize) //检查是否越界
            return false;
        c.m_y++;//使当前点下移一格
        if(path.findEle(c) == true) { //若移动后的节点已经在栈中，结束回溯
            c.m_y--;//还原
            return false;
        }
        if(board[c.m_x][c.m_y] == 0 && c!=top)
            return true;//若邻格为0不是障碍、且不是来时的路径，可行
        else {
            c.m_y--;//还原
            return false;
        }
    }//使当前点下移一格
    
    bool goLeft(Coordinate &c,Coordinate &top) {
        if(c.m_x-1 < 0) //检查是否越界
            return false;
        c.m_x--;
        if(path.findEle(c) == true) { //若移动后的节点已经在栈中，结束回溯
            c.m_x++;//还原
            return false;
        }
        
        if(board[c.m_x][c.m_y] == 0 && c!=top)
            return true;
        else {
            c.m_x++;//还原
            return false;
        }
    }//使当前点左移一格
    
    bool goRight(Coordinate &c,Coordinate &top) {
        if(c.m_x+1 >= boardSize) //检查是否越界
            return false;
        c.m_x++;
        if(path.findEle(c) == true) { //若移动后的节点已经在栈中，结束回溯
            c.m_x--;//还原
            return false;
        }
        
        if(board[c.m_x][c.m_y] == 0 && c!=top)
            return true;
        else {
            c.m_x--;//还原
            return false;
        }
    }//使当前点右移一格
    
public:
    Maze(){board = nullptr;boardSize = 0;} //构造函数
    void initialize();//初始化迷宫
    void findPath();//寻找路径
    void showPath();//打印出找到的路径
};



/*Maze的函数定义*/
void Maze::showBoard() {
    int i = 0,j = 0;
    cout << "     ";
    for(i = 0;i < boardSize;i++) {
        cout << "c" << left << setw(2) << i;
        if(i != boardSize-1) cout << " ";//打印列标
    }
    cout << endl;
    for(i = 0;i < boardSize;i++) { //打印迷宫的二维数组
        for(j = 0;j <= boardSize;j++) {
            if(j == 0) {cout  << "r" << left << setw(2) << i;}//为第一列，则输出行标
            else cout << left << setw(2) << board[i][j-1];//非首列，输出二维数组的元素值
            if(j != boardSize) cout<<"  ";
        }
        cout << endl;
    }
}

void Maze::initialize() {
    int i = 0,j = 0;
    cout << "请输入迷宫的大小，以创建一个大小为n*n的迷宫"<<endl;
    while(1) {
        cin >> boardSize;
        if(boardSize <= 0) cout << "请您重新输入一个正整数作为迷宫大小：";
        else break;
    }
    board = new int *[boardSize]; //接下来三行是创建n*n的动态二维数组
    for(i = 0;i < boardSize;i++) {
        board[i] = new int[boardSize];
    }
    cout << "请输入一个" << boardSize<< "*" << boardSize <<
    "大小的矩阵以初始化迷宫，0表示可行，1表示障碍" << endl;
    for(i = 0;i < boardSize;i++) { //初始化迷宫的二维数组
        for(j = 0;j < boardSize;j++)
            cin >> board[i][j];
    }
    cout << "请按照x、y的顺序输入迷宫入口与出口的坐标" << endl;
    entrance.input(boardSize);
    exit.input(boardSize);
    cout << "--------------------------------------"<<endl<<"您输入的迷宫为" << endl;
    showBoard();
}

void Maze::findPath() {
    Coordinate current = entrance,pre = current;
    path.push(entrance);//先将起点放入栈中
    while(current != exit) { //到达终点循环才结束
        //按照上、下、左、右的顺序进行试探
        if(goUp(current,pre) == true) {//上移可行
            path.getTop(pre);//移动前的current的值赋给pre
            path.push(current);//将移动后的点放入栈中
        }
        else if(goDown(current,pre) == true) {//下移可行
            path.getTop(pre);//移动前的current的值赋给pre
            path.push(current);//将移动后的点放入栈中
        }
        else if(goLeft(current,pre) == true) {//左移可行
            path.getTop(pre);//移动前的current的值赋给pre
            path.push(current);//将移动后的点放入栈中
        }
        else if(goRight(current,pre) == true) {//右移可行
            path.getTop(pre);//移动前的current的值赋给pre
            path.push(current);//将移动后的点放入栈中
        }
        //上下左右都行不通，遇到死路:
        else {
            path.pop(pre);//栈顶元素四个方向都走不动，则令其出栈作为pre元素
            path.getTop(current);//取新栈顶元素为current，开始回溯
        }
    } //while循环结束
}

void Maze::showPath() {
    Coordinate current;
    Stack<Coordinate> temp;//辅助栈，让输出路径变成从起点出发的
    int len = path.getSize();
    cout<< setw(55) << setfill('-') << '-' << endl <<"为您找到的路径是："<<endl;
    for(int i = 0;i < len;i++) {//path栈中的元素出栈、放入temp辅助栈中，以实现逆序
        path.pop(current);
        temp.push(current);
    }
    for(int i = 0;i < len;i++){//temp辅助栈中的元素一个个出栈、输出
        temp.pop(current);
        cout<<"("<<current.m_x<<","<<current.m_y<<")";
        if(i != len - 1) cout<<" --> ";
    }
    cout<<endl;
}


#endif /* maze_h */
