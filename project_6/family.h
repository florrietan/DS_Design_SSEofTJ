//
//  family.h
//  project6-mac
//
//  Created by florrie on 2020/11/13.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef family_h
#define family_h
#include <iostream>
using namespace std;

class FamilyNode {
    friend class FamilyTree;//便于树类访问节点信息
private:
    string m_name;//成员姓名
    FamilyNode *firstchild,*sibling,*pre;//节点有三个指针域，存放长子、相邻兄弟和前驱节点
public:
    FamilyNode(FamilyNode *fc=NULL,FamilyNode *sib=NULL,FamilyNode *p=NULL){firstchild=NULL;sibling=NULL;pre=NULL;}//构造函数
    FamilyNode(string n,FamilyNode *p=NULL,FamilyNode *fc=NULL,FamilyNode *sib=NULL){m_name=n;pre=p;firstchild=NULL;sibling=NULL;}//含名字参数的构造函数
    ~FamilyNode(){};
};


class FamilyTree {
private:
    FamilyNode *root;//指向祖先
    bool locate(FamilyNode *sub,string name,FamilyNode *&current);//根据姓名找到该成员的指针
    FamilyNode *preMember(FamilyNode *sub,FamilyNode *current);//根据姓名找到该成员前驱的指针（前驱可能是父亲、可能是兄弟）
    FamilyNode *lastChild(FamilyNode *current);//找到current节点的最后一个孩子
    void allChildren(FamilyNode *father); //打印出father的所有孩子
    /*以下是承担主要功能的函数*/
    void establish();//为某成员建立家庭
    bool search();//查找成员
    void insert();//为成员插入子女成员
    void remove();//删除成员
    void edit();//修改成员信息
        
public:
    void initialize();//初始化家谱系统
    void run();//系统开始运行
    FamilyTree(){root=NULL;}
    ~FamilyTree() {};
};

//私有函数部分
bool FamilyTree::locate(FamilyNode *sub,string name,FamilyNode *&current) {//根据name找成员地址
    if(sub == NULL) {return false;}//若子树根节点为空了也未找到，则该成员不存在、返回false
    if(sub->m_name == name) {current=sub;return true;}//若子树根节点就是所寻节点，根节点地址赋给current
    locate(sub->firstchild,name,current);//递归在当前节点的长子域中寻找
    locate(sub->sibling,name,current);//递归在当前节点的兄弟域中寻找
    return true;
}

/*
FamilyNode* FamilyTree::preMember(FamilyNode *sub,FamilyNode *current) {
    if(end == false) { //尚未找到
        if(sub == NULL) return current->pre;//若
        if(sub->firstchild == current) {
            current->pre = sub;
            end = true;
            return current->pre;
        }
        if(sub->sibling == current) {
            current->pre = sub;
            end = true;
            cout << current->pre->m_name << endl;
            return current->pre;
        }
        preMember(sub->firstchild,current);//从长子域中找
        preMember(sub->sibling,current);//从兄弟域中找
    }
    return current->pre;
}
 */

/*
bool FamilyTree::parent(FamilyNode *sub,string name,FamilyNode *&father)
{
    FamilyNode *temp=root;
    if(sub==NULL) {return false;}
    if(sub->firstchild->m_name==name) {father=sub;return true;}
    if(sub->sibling->m_name==name) {
        name=sub->sibling->m_name;
        parent(temp,name,father);
        return true;
    }
    parent(sub->firstchild,name,father);
    parent(sub->sibling, name,father);
    return true;
}
 */

FamilyNode* FamilyTree::lastChild(FamilyNode *current) {
    if(current->firstchild==NULL) return NULL;//没有孩子，直接return NULL
    current=current->firstchild;//指针移动到长子
    while(current->sibling != NULL) current=current->sibling;//后面还有兄弟姐妹则后移
    return current;//返回最后的一个孩子
}

void FamilyTree::allChildren(FamilyNode *father) {
    FamilyNode *current = father;
    current = current->firstchild;//移到长子域
    if(current == NULL){ //没有子女
        cout << father->m_name << "没有子女"<<endl;
        return;
    }
    else cout << father->m_name << "的子女是：" << current->m_name;//有子女则先打印出长子的姓名
    while(current->sibling != NULL){ //current后面还有未输出的兄弟姐妹
        cout << "、";
        current = current->sibling;//current后移
        cout << current->m_name;//输出长子的兄弟姐妹
    }
    cout<<endl;
}

//公有函数部分
void FamilyTree::initialize() {
    cout << "首先建立一个家谱！" << endl << "请输入祖先的名字来创建这个家族：";
    string name;
    cin >> name;
    root = new FamilyNode(name);
    cout << "此家族的祖先是:" << name << endl;
    cout << "本家谱管理系统有以下操作:" << endl;
    cout << "A ---- 建立家庭" << endl;
    cout << "B ---- 插入家庭成员" << endl;
    cout << "C ---- 搜索家庭成员" << endl;
    cout << "D ---- 删除家庭成员" << endl;
    cout << "E ---- 修改成员信息" << endl;
    cout << "F ---- 退出家谱系统" << endl;
}

void FamilyTree::run() {
    char operation = 'Z';//初始化operation为无意义操作
    while(operation != 'F') {
        cout << "---------------------------------------"<<endl;
        cout << "请从A～E中选择一个操作,F表示退出系统：";
        cin >> operation;
        switch (operation) {
            case 'A':
                establish();break;
            case 'B':
                insert();break;
            case 'C':
                search();break;
            case 'D':
                remove();break;
            case 'E':
                edit();break;
            case 'F':
                break;
            default: //包括'F'
                cout << "本系统中不存在该操作!" << endl;break;
        }
    }
    cout<<"您已退出本家谱管理系统！"<<endl;
}

void FamilyTree::establish() {
    string name_f,name_c;//name_c用于存储输入的子女姓名
    int num_c = 1,i = 1;
    cout << "请输入要建立家庭的人的姓名：";
    FamilyNode *father = NULL,*current = NULL;
    while(1) { //边界保护部分
        cin >> name_f; //输入父亲的名字
        locate(root,name_f,father);//定位父亲的地址
        if(father != NULL) break;//判断该节点是否存在
        else cout << name_f << "不存在,请重新输入要建立家庭的人的姓名:" << endl;
    }
    cout << "请输入他的子女个数:";
    while(1) { //边界保护
        cin >> num_c;//输入子女个数
        if(num_c <= 0) cout << "输入非法！请输入正整数作为子女个数：";
        else break;
    }
    cout << "请依次输入孩子的姓名：";
    cin >> name_c; //输入长子的姓名
    father->firstchild = new FamilyNode(name_c,father); //长子存储到父亲的长子域中
    current = father->firstchild; //当前指针指向长子
    while(i < num_c) { //i初始值为1
        cin >> name_c; //输入长子之后的子女姓名
        current->sibling = new FamilyNode(name_c,current); //非长子子女通过sibling域存储
        current = current->sibling; //指向之后的兄弟姐妹
        i++;
    }
    allChildren(father);//打印出该成员的所有子女
}

void FamilyTree::insert() {
    string name_f,name_c;
    FamilyNode *current = NULL,*lc = NULL,*temp = nullptr;
    cout << "请输入要添加子女的人的姓名：";
    while (1) { //边界保护
        cin >> name_f; //输入父亲的名字
        locate(root,name_f,current);//定位父亲的地址
        if(current != NULL) break;//判断该节点是否存在于家谱中
        else cout << name_f << "不存在,请重新输入:" << endl;
    }
    cout << "请输入子女的姓名：";
    while (1) {
        temp = NULL;
        cin >> name_c; //输入子女的名字
        locate(root,name_c,temp);//定位子女是否存在
        if(temp == NULL) break;//该节点不存在，可以添加
        else cout << name_c << "已存在,请重新输入:" << endl;
    }
    lc = lastChild(current);//定位父亲的最后一个孩子
    if(lc == NULL) {//他一个孩子也没有，加到firstchild域
        current->firstchild = new FamilyNode(name_c,current);
    }
    else {//加到原来最后一个孩子的sibling域
        lc->sibling = new FamilyNode(name_c,current);
    }
    allChildren(current);
}

bool FamilyTree::search() {
    string name;
    cout << "输入要查找的人的姓名：";
    cin >> name;
    FamilyNode *current = NULL;
    locate(root,name,current);//在家谱中定位名叫name的人
    if(current == NULL)  {cout << name << "不存在！" << endl;return false;}
    allChildren(current);//打印查找的人的所有子女
    return true;
}

void FamilyTree::remove() {
    string name;
    FamilyNode *current = NULL,*father = NULL;
    cout << "输入要删除的人的姓名：";
    while (1) { //判断输入是否合法
        cin >> name; //输入名字
        locate(root,name,current);
        if(current != NULL) break;//该节点存在
        else cout << name << "不存在,请重新输入:" << endl;
    }
    if(current == root){ //判断删除节点是否是祖先
        cout << name << "为本家谱的祖先，不可删除！" << endl;
        return;//结束函数
    }
    father = current->pre;
    if(father->firstchild == current){//若删除成员是长子
        father->firstchild = current->sibling;//修改他父亲的长子域
    }
    else father->sibling = NULL;//不是长子，将前驱的兄弟域置为NULL
    cout << "已删除" << name << "!" << endl;//逻辑上已删除节点
    
    //以下是物理上删除节点，回收内存
    if(current->firstchild == NULL) {//若current没有孩子，直接删除
        delete current;
    }
    else { //若有孩子
        FamilyNode *del = current;
        current = current->firstchild;//移到长子域
        delete del;//释放内存
        while(current->sibling != NULL){ //current后面还有未处理的兄弟姐妹
            del = current;
            current = current->sibling;//移到兄弟域
            delete del;//释放内存
        }
        delete current;//循环结束后直接删除掉当前节点
    }
}

void FamilyTree::edit() {
    string name,name_new;
    FamilyNode *current = NULL;
    cout<<"请输入要修改的人当前的姓名：";
    while(1) { //判断输入是否合法
        cin >> name; //输入名字
        locate(root,name,current);//在家谱中定位该成员
        if(current != NULL) break;//该节点存在
        else cout << name << "不存在,请重新输入:" << endl;
    }
    cout << "请输入修改后的姓名：";
    cin >> name_new;
    current->m_name = name_new;//修改name域
    cout << name << "已改名为：" << name_new << endl;
    allChildren(current);
}

#endif /* family_h */
