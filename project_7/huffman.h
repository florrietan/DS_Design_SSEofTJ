//
//  huffman.h
//  project7-mac
//
//  Created by florrie on 2020/11/15.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef huffman_h
#define huffman_h
#include <iostream>
using namespace std;

class hfmNode {
friend class HuffmanTree;
private:
    double weight;//节点的权值，在本项目中代表木板的长度、也是砍它的花销
    hfmNode *left,*right,*pre;//指针域有左子女、右子女、前驱
public:
    hfmNode(double w=0,hfmNode *p=NULL,hfmNode *l=NULL,hfmNode *r=NULL){
        weight=w;
        pre=p;
        left=l;
        right=r;
    }
};

class HuffmanTree {
private:
    double N;//所需木头块数
    double result;//最后输出最小花费的结果
    hfmNode *root;//最后霍夫曼树的根
    hfmNode **forest;//存放树的森林（指针数组）
    double *weight;//存放权重的数组
    void sort(int len);//对权重排序
    void preOrder(hfmNode *sub);//先序遍历霍夫曼树
    void form();//构造霍夫曼树
public:
    HuffmanTree(){N=0;result=0;}
    ~HuffmanTree(){};
    void initialize();//初始化函数
    void run(); //运行
};

void HuffmanTree::preOrder(hfmNode *sub) {
    hfmNode *l = NULL,*r = NULL;//子树根节点的左、右孩子
    l = sub->left;
    r = sub->right;
    if(sub == NULL) return;//子树为空，结束函数
    if(l != NULL && r != NULL) result = result + sub->weight;//若sub节点有左右子树，则将它权重的值加到result中（只有内节点是既有左孩子又有右孩子的）
    preOrder(sub->left);//递归遍历sub的左子树
    preOrder(sub->right);//递归遍历sub的右子树
}

void HuffmanTree::sort(int len) {//len是森林中剩余树的个数
    int i = 0,j = 0;
    hfmNode *temp = NULL;
    for(j = 0;j < len-1;j++){//对剩余树的根节点权值进行从大到小的冒泡排序
        for(i = 0;i < len-1-j;i++){
            if(forest[i]->weight < forest[i+1]->weight){
                temp = forest[i];
                forest[i] = forest[i+1];
                forest[i+1] = temp;
            }
        }
    }
    
//    for(i=0;i<len;i++)
//        cout<<forest[i]->weight<<" ";
//    cout<<endl;
}

void HuffmanTree::form() {
    sort(N);//先对N棵子树排序
    int len = N,i = 0;
    for(i = 0;i < N-1;i++) {
        root = new hfmNode(forest[len-1]->weight + forest[len-2]->weight);//合并两个具有最小权值的根节点，成为一个新节点，其权值之和赋给新节点
        result = result + root->weight;//将新的内部节点权值加到结果result中
//        cout << "root->weight: " << root->weight << endl << "result :" << result << endl;
        root->left = forest[len-1];//根节点权值最小的树成为新根节点的左子树
        root->right = forest[len-2];//根节点权值次小的树成为新根节点的右子树
        forest[len-1] = NULL;//将一维指针数组的末尾元素置为NULL
        forest[len-2] = root;//新根节点放到数组的倒数第二个位置
        len--;//森林中树的数量减一
        sort(len);//再次对森林的根节点权值排序
    }
}

void HuffmanTree::initialize() {
    cout << "请输入需要的木头总块数：";
    cin >> N;
    int temp = (int)N;//temp取N的整数部分
    while(N <= 0 || (double)(N-temp) != 0){//检查输入是否是整数、是正数
        cout << "输入不合法！请重新输入一个正整数:" << endl;
        cin >> N;
        temp = (int)N;
    }
    weight = new double[N];//动态创建一维数组储存每块木板的长度
    forest = new hfmNode *[N];//动态创建一维的指针数组，存储森林里的树
    int i = 0;
    cout << "请分别输入这" << N << "块木头的长度：";
    for(i = 0;i < N;i++) {
        cin >> weight[i];
        while(weight[i] <= 0) {//输入不合法
            cout << "输入不合法！请重新输入大于零的数:" << endl;
            cin >> weight[i];
        }
        forest[i] = new hfmNode(weight[i]);//新建一个节点，每个木块长度作为一棵树根节点的权值，存到forest数组里
    }
}

void HuffmanTree::run() {
    form();
    cout<<"最少需花费："<<result<<"元"<<endl;
}
#endif /* huffman_h */
