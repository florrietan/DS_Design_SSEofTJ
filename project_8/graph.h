//
//  graph.h
//  project8-mac
//
//  Created by florrie on 2020/12/13.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef graph_h
#define graph_h
#include "queue.h"


template <typename VertexType> //Graph<char> graph;
class Graph {
private:
    class MSTNode {
        public:
        int m_v1,m_v2;//边两侧顶点在数组中的序号
        float m_cost;//边的权值
        MSTNode () {m_cost = 0;}
        MSTNode (int v1,int v2,float cost) {m_v1 = v1;m_v2 = v2;m_cost = cost;}
        ~MSTNode (){};
        void editNode (int v1,int v2,float cost) {m_v1 = v1;m_v2 = v2;m_cost = cost;}
    };

    VertexType *vertex; //存储顶点的一维数组
    float **matrix; //存储邻接矩阵的二维数组
    int numVertex; //顶点个数
    int numEdge; //边的个数
    MSTNode *mstPrim;//存储最小生成树的节点
    
    int vertexNum(char v) { //找到名叫v的顶点在数组中的序号
        for(int i = 0;i < numVertex;i++) if(vertex[i] == v) return i;
        return -1;
    }
    void showPrim();//打印出最小生成树

public:
    const float maxCost = 999;//最大权值，表示不通
    Graph() {numVertex = 0;numEdge = 0;vertex = nullptr;matrix = nullptr;mstPrim = nullptr;}
    ~Graph() {delete []vertex; delete []matrix;}
    void initialize();//初始化
    void run();//运行系统
    void insertVertex();//初始化图的顶点
    void insertEdge();//初始化图的边
    void Prim();//用Prim算法生成最小生成树
};


template <typename VertexType>
void Graph<VertexType>::initialize() {
    cout << "**            电网造价模拟系统              **" << endl;
    cout << "===========================================" << endl;
    cout << "**           A -- 创建电网顶点             **" << endl;
    cout << "**           B -- 添加电网的边             **" << endl;
    cout << "**           C -- Prim生成MST             **" << endl;
    cout << "**           E -- 退出程序                 **" << endl;
}

template <typename VertexType>
void Graph<VertexType>::run() {
    char choice = NULL;
    while(choice != 'E') {
        cout << "请您选择一个操作：";
        cin >> choice;
        switch (choice) {
            case 'A':
                insertVertex();break;
            case 'B':
                insertEdge();break;
            case 'C':
                Prim();break;
            case 'D':
                cout<<"您已选择退出电网造价模拟系统！"<<endl;
            default:
                break;
        }//switch结束
    }//while循环结束
}

template <typename VertexType>
void Graph<VertexType>::insertVertex() {
    cout << "请输入顶点的个数：";
    while(1) {  //边界保护
        cin >> numVertex;
        if(numVertex <= 0) cout << "请重新输入正整数作为顶点个数：";
        else break;
    }
    mstPrim = new MSTNode[numVertex-1];//最小生成树里边的个数是顶点数减1，依此创建mstPrim数组
    vertex = new char[numVertex];//动态创建存储顶点的一维数组
    cout << "请依次输入各顶点的名称：";//输入顶点
    for(int i = 0;i < numVertex;i++) {
        cin >> vertex[i];
    }
    matrix = new float *[numVertex]; //动态生成邻接矩阵的二维数组
    for(int i = 0;i < numVertex;i++)
        matrix[i] = new float[numVertex];
    for(int i = 0;i < numVertex;i++)//最开始将任意两点间的开销初始化为maxCost，表示不通
        for(int j = 0;j < numVertex;j++)
            matrix[i][j] = maxCost;
}

template <typename VertexType>
void Graph<VertexType>::insertEdge() {
    char v1,v2;
    float cost = 0;
    int i = 0,j = 0,cnt = 0;
    Queue<int> newVertex;//暂存输入边两侧顶点的序号
    Queue<float> newCost;//暂存输入边的权值
    cout << "以输入\"? ? 0\"代表结束输入"<<endl;
    while(1) {
        cout << "请输入两个顶点及它们之间边的代价：";
        cin >> v1 >> v2 >> cost;//输入一组边的权值、顶点
        if(v1 == '?' && v2 == '?' && cost == 0) break;//输入终止条件
        if(cost <= 0) {cout << "请输入正数作为代价！" << endl;continue;}
        //边界保护：因为是简单图，所以边数不可超过上限
        if(numEdge == numVertex*(numVertex-1)/2)
            {cout << "输入边已经超过上限，已构成完全图！输入无效，将停止输入。" << endl;break;}
        i = vertexNum(v1);//取两个顶点在数组中的序号
        j = vertexNum(v2);
        //边界保护，检查顶点是否存在于图中
        if(i == -1 ||j == -1) {cout << "只能输入已存在的顶点！请重新输入!" << endl;continue;}
        if(i >= 0 && i < numVertex && j >= 0 && j < numVertex) numEdge++;//得到边的条数
        newVertex.enQueue(i);//将顶点v1的编号放入队列中
        newVertex.enQueue(j);//将顶点v2的编号放入队列中
        newCost.enQueue(cost);//将边的权值放入队列中
    }//while循环结束，边的输入结束
    
    //下面开始将边的信息存入邻接矩阵中:
    for(cnt = 0; cnt < numEdge;cnt++) {
        i = newVertex.deQueue();//取出左侧顶点的序号
        j = newVertex.deQueue();//取出右侧顶点的序号
        cost = newCost.deQueue();//取出边的权重
        matrix[i][j] = cost;//无向图，对称地置数
        matrix[j][i] = cost;
    }
}

template <typename VertexType>
void Graph<VertexType>::Prim() {
    char startPoint;//Prim算法的起点
    int start,i,cnt;
    int *nearVex = new int[numVertex];//存放各顶点到MST中最近的顶点
    float *lowCost = new float[numVertex];//存放各顶点到MST中最小开销
    cout << "请选择Prim算法下的起点为：";
    cin >> startPoint;
    start = vertexNum(startPoint);//取startPoint的序号
    for(i = 0;i < numVertex;i++) {//初始化nearVex和lowCost数组
        nearVex[i] = start;//此时均离startPoint最近
        lowCost[i] = matrix[start][i];//权值为startPoint到当前点的代价
    }
    nearVex[start] = -1;//初始化结束(若顶点已经在MST中，则对应的nearVex中置为-1
    
    for(cnt = 0;cnt < numVertex-1;cnt++) {//需要循环n-1次, 往mstPrim中再加入n-1个顶点
        float min = maxCost;
        int minVex = 0;//minVex是当前到生成树权值最小的顶点的编号
        for(i = 0;i < numVertex;i++) {//寻找 到生成树权值最小的顶点
            if(nearVex[i] != -1 && lowCost[i] < min) {minVex = i;min = lowCost[i];}
        }
        mstPrim[cnt].editNode(nearVex[minVex],minVex,lowCost[minVex]);
        nearVex[minVex] = -1;
        //下面检查更新nearVex数组和lowCost数组：
        for(i = 0; i < numVertex;i++) {
            //若i不在生成树中,检查minVex加入MST后是否影响lowCost[i]
            if(nearVex[i] != -1 && matrix[minVex][i] < lowCost[i]) {
                lowCost[i] = matrix[minVex][i];
                nearVex[i] = minVex;
            }
        }//检查更新两个数组部分结束
        
    }
    cout << "由" << startPoint << "点开始的Prim算法下的最小生成树为："<<endl;
    showPrim();
}

template <typename VertexType>
void Graph<VertexType>::showPrim() {
    int i = 0,v1,v2;
    float cost;
    for(i = 0;i < numVertex-1;i++) {
        v1 = mstPrim[i].m_v1;
        v2 = mstPrim[i].m_v2;
        cost = mstPrim[i].m_cost;
        cout << vertex[v1] << "<--" << cost << "-->" << vertex[v2];
        if( i!= numVertex - 2) cout<<"       ";
    }
    cout<<endl;
}

#endif /* graph_h */
