//
//  graph.h
//  project9-mac
//
//  Created by florrie on 2020/12/13.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef graph_h
#define graph_h
#include "queue.h"
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>

class Course {
    friend class DirectedGraph;
private:
    string m_serial;//课程编号
    string m_name;//课程名称
    int m_hours;//课程周学时
    int m_semester;//指定开课学期
    string m_preCourses;//先修课程
    int m_inDegree;//统计先修课程的个数,即入度
    int m_outDegree;//统计有多少课依赖于本门课，即出度；排课时优先排出度不为0的
    int *m_weekday;//动态开辟数组，存储课程安排在周几；若为nullptr表示该课程还未排入课表
public:
    Course() {m_inDegree = 0;m_outDegree = 0;m_weekday = nullptr;}
    bool operator==(Course right) { //重载==运算符
        if(this->m_name == right.m_name && this->m_serial == right.m_serial && this->m_hours == right.m_hours && this->m_semester == right.m_semester && this->m_preCourses ==right.m_preCourses) return true;
        else return false;}
    
};

class DirectedGraph {
private:
    Course *vertex; //存储顶点的一维数组
    int **matrix; //存储邻接矩阵的二维数组
    int numVertex; //顶点个数
    int coursesPerTerm[8];//存储每学期开课门数的数组
    int *topoSequence;//存储课程在数组序号下的拓扑序列
    Course *schedule[10][5];//课表的二维数组，十行表示每天10节小课，五列表示周一至周五
    
    int preBySerial(char c1,char c2,char c3);//根据先修课程的序号找到先修课程在顶点数组中的序号
    bool initializeVertex();//初始化顶点
    void initializeMatrix();//初始化邻接矩阵
    bool find5Classes(Course *c);//为5学时的课程c排课
    bool find3Classes(Course *c,int num);//为一周有3*num学时的课程c排课
    bool find2Classes(Course *c,int num);//为一周有2*num学时的课程c排课
public:
    DirectedGraph() {numVertex = 0;vertex = nullptr;matrix = nullptr;}
    ~DirectedGraph() {delete []vertex; delete []matrix;}
    bool initialize();//公有初始化借口
    void topoSort();//寻找拓扑序列
    void distribute();//将课程分配填充到课表中
};

int DirectedGraph::preBySerial(char c1,char c2,char c3) {
    if(c1 == '\0') return -1;//不存在先修课程，返回-1
    for(int i = 0;i < numVertex;i++)
        if(vertex[i].m_serial[0] == c1 && vertex[i].m_serial[1] == c2 && vertex[i].m_serial[2] == c3) return i;
    return -1;
}

bool DirectedGraph::initializeVertex() {
    ifstream inFile;//输入文件流
    int i = 0,j = 0;
    inFile.open("inputCourses.txt");
    //第一次读文件是获得顶点的个数
    while(!inFile.eof()) { //inFile.eof()==1表示文件已读完
        string line;
        getline(inFile,line);//读一行
        numVertex++;//每一行代表一个课程、对应有一个顶点
    }
    inFile.close();//关闭文件
    numVertex--;//减去第一行（因为第一行是指定每学期开课数量）
    vertex = new Course[numVertex];//创建顶点数组
    matrix = new int*[numVertex];//这三行是创建邻接矩阵
    for(i = 0;i < numVertex;i++)
        matrix[i] = new int[numVertex];
    for(i = 0;i < numVertex;i++)//先将矩阵各元素初始化为0
        for(j = 0;j < numVertex;j++)
            matrix[i][j] = 0;
    //第二次读文件是初始化顶点
    inFile.open("inputCourses.txt");
    for(i = 0;i < 8;i++)
        inFile >> coursesPerTerm[i];
    int result = 0;//边界保护
    for(i = 0;i < 8;i++)
        result = result + coursesPerTerm[i];
    if(result != numVertex) return false;
    i = 0;//i重新置零
    while(!inFile.eof()) { //inFile.eof()==1表示文件已读完
        inFile >> vertex[i].m_serial >> vertex[i].m_name >> vertex[i].m_hours >> vertex[i].m_semester;
        getline(inFile,vertex[i].m_preCourses);//一行中剩下的全读到先修课程信息里
        for(int a = 0;vertex[i].m_preCourses[a] != '\0';a++) {//统计先修课程个数
            if(vertex[i].m_preCourses[a] == 'c') vertex[i].m_inDegree++;//统计入度
        }
//        cout<<i<<": "<<vertex[i].m_preCourses<<endl;
//        cout<<i<<": "<<vertex[i].m_numPreC<<endl;
        i++;
    }
    inFile.close();
    return true;
}

void DirectedGraph::initializeMatrix() {
    int i = 0,j = 0,row = 0,col = 0;
    string pre;
    for(i = 0;i < numVertex;i++) {
        col = i;//顶点作为有向边的终点，对于邻接矩阵里的列元素
        for(j = 0;j < vertex[i].m_inDegree;j++) {//入读个数即先修课程个数，找到它所有的先修课程
            pre[0] = vertex[i].m_preCourses[j*3+1+j];//+j表示前面有j个空格
            pre[1] = vertex[i].m_preCourses[j*3+2+j];
            pre[2] = vertex[i].m_preCourses[j*3+3+j];
            row = preBySerial(pre[0],pre[1],pre[2]); //找到先修课程的编号
            if(row>=0 && row < numVertex) {matrix[row][col] = 1;} //修改矩阵
        }
    }
    for(i = 0;i < numVertex;i++)//统计出度
        for(j = 0;j < numVertex;j++)
            if(matrix[i][j] == 1) vertex[i].m_outDegree++;
}

bool DirectedGraph::initialize() {
    if(initializeVertex() == false) return false;
    initializeMatrix();
    return true;
}

void DirectedGraph::topoSort() { //拓扑序列不唯一，所以实际排课时优先排 指定该学期开课的和出度不为0的课
    topoSequence = new int[numVertex];//存储拓扑序列的数组
    int i = 0,*count = new int[numVertex];//存储变化的入度的count数组
    Queue<int> queue;//用于存储入读为0的课程，队列使刚变为0的课程拍到稍靠后的位置，实现了为拓扑序列分层、便于排课
    for(i = 0;i < numVertex;i++) {//初始化存储入度的count数组
        count[i] = vertex[i].m_inDegree;
    }
    int cnt = 0;
    for(i = 0;i < numVertex;i++) //入度为零且有指定开课学期的课程先进队列，排课时优先
        if(count[i] == 0 && vertex[i].m_semester != 0) queue.enQueue(i);
    for(i = 0;i < numVertex;i++) //入度为零且出度不为零的课程再进队列，排课时优先
        if(count[i] == 0 && vertex[i].m_outDegree != 0) queue.enQueue(i);
    for(i = 0;i < numVertex;i++) //剩余入度为零课程进队列
        if(count[i] == 0 && vertex[i].m_outDegree == 0 && vertex[i].m_semester == 0) queue.enQueue(i);
    
    for(i = 0;i < numVertex;i++) //期望输出n个顶点
        if(queue.isEmpty() == true) { //中途队列空,有环，转出
            cout << "网络中有回路，不存在拓扑序列" << endl;
            return;
        }
        else { //继续拓扑排序
            int j = queue.deQueue();//取出一个元素
            topoSequence[cnt] = j; //存到拓扑序列中
            cnt++;//拓扑序列中元素个数+1
            int row = j;//表示作为边的终点
            //接下来遍历出栈顶点那一列，修改它相关边的终点的入度count数组
            for(int col = 0;col < numVertex;col++) {
                if(matrix[row][col] == 1) {
                    count[col]--;//入度减1
                    if(count[col] == 0) queue.enQueue(col);//若入度减1后变为零，则将该顶点加入队列
                }
            }
        }//大else语句结束,输出顶点的for循环也结束
    
    for(int i = 0;i < numVertex;i++)
        cout<<vertex[topoSequence[i]].m_name<<" ";
    cout<<endl;
}

void DirectedGraph::distribute() {
    int term = 0;//表示学期数
    int addedCourses = 0;
    ofstream outFile;//写文件
    outFile.open("outputSchedule.txt");
    
    for(term = 1;term <= 8;term++) {//主体循环，term是从1～8
        //每一学期开始都要重新初始化课表为空
        addedCourses = 0;
        for(int i = 0;i < 10;i++)
            for(int j = 0;j < 5;j++)
                schedule[i][j] = nullptr;
        for(int i = 0;i < numVertex;i++) {
            Course *current = &vertex[topoSequence[i]];
            //若该课未指定开课学期或就应在term学期开课，则可参与本学期排课
            string name = current->m_name;
            if(current -> m_semester != 0 && current -> m_semester != term) continue;
            if(current -> m_weekday == nullptr) {//尚未排入
                switch (current -> m_hours) {//根据课程周学时数进行排课
                    case 3://优先找3*1节连上的
                        if(find3Classes(current,1) == false) break;
                        break;
                    case 4://找2*2节课，两天不相邻
                        if(find2Classes(current,2) == false) break;
                        break;
                    case 5://找2+3节课，两天不相邻
                        if(find5Classes(current) == false) break;
                        break;
                    case 6://优先3+3,或者2+2+2，两天不相邻
                        if(find3Classes(current,2) == false) break;
                        break;
                    default:
                        break;
                }
                addedCourses++;//本学期已排入课程数量+1
            }
            //term是1～8，所以在数组中调用要减1
            if(addedCourses == coursesPerTerm[term-1]) break;//本学期开课数量已达到，结束拓扑的循环、开始下学期排课
        }
        
        outFile << "schedule of term " << term << "，本学期开课门数为 " << coursesPerTerm[term-1] << endl;
        outFile << left << setw(28)<<setfill(' ')<<"周一"<<setw(28)<<setfill(' ')<<"周二"<<setw(28)<<setfill(' ')<<"周三"<<setw(28)<<setfill(' ')<<"周四"<<setw(28)<<setfill(' ')<<"周五"<<endl;
        for(int i = 0;i < 10;i++) {
            for(int j = 0;j < 5;j++)
                if(schedule[i][j] != nullptr) {
                    outFile << left << setw(28) << setfill(' ') << schedule[i][j]->m_name;
                }
            
                else outFile << left << setw(28) << setfill(' ') << "----";
            outFile << endl;
        }
        outFile << endl;
        
    } //term==9 主体循环结束
    
}

bool DirectedGraph::find5Classes(Course *c) {
    c->m_weekday = new int[2];
    int round = 0,temp = 0;
    //先找3再找2
    round = 1;//为1表示在找3节课，为2表示在找2节课
    for(int wkday = 1;wkday <= 5;wkday++) {
        if(round == 1 && (schedule[2][wkday-1] == nullptr || schedule[7][wkday-1] == nullptr)) { //3~5or8~10
            if(schedule[2][wkday-1] == nullptr) {schedule[2][wkday-1] = schedule[3][wkday-1] = schedule[4][wkday-1] = c;temp = 2;}//表示3~5开课
            else {schedule[7][wkday-1] = schedule[8][wkday-1] = schedule[9][wkday-1] = c;temp = 7;}//表示8~10开课
            round = 2;
            c->m_weekday[0] = wkday-1;
        }
        if(round == 2 && (schedule[0][wkday-1] == nullptr || schedule[5][wkday-1] == nullptr)) {//1~2or6~7
            //相隔需有一天
            if(wkday-1 - c->m_weekday[0] <= 1) continue;
            if(schedule[0][wkday-1] == nullptr) {schedule[0][wkday-1] = schedule[1][wkday-1] = c;}//表示1~2开课
            else {schedule[5][wkday-1] = schedule[6][wkday-1] = c;}//表示6～7开课
            c->m_weekday[1] = wkday-1;
            return true;
        }
    }
    if(round == 2 && temp != 0) { //如果3找到、2没找到，需重置那3节课
        schedule[temp][c->m_weekday[0]] = schedule[temp+1][c->m_weekday[0]] = schedule[temp+2][c->m_weekday[0]] = nullptr;
    }
    //先找2再找3
    round = 1;temp = 0;//round==1表示在找2节课，为2表示在找3节课
    for(int wkday = 1;wkday <= 5;wkday++) {
        if(round == 1 && (schedule[0][wkday-1] == nullptr || schedule[5][wkday-1] == nullptr)) { //1~2or6~7
            if(schedule[0][wkday-1] == nullptr) {schedule[0][wkday-1] = schedule[1][wkday-1] = c;temp = 0;}//表示1~2开课
            else {schedule[5][wkday-1] = schedule[6][wkday-1] = c;temp = 5;}//表示6～7开课
            round = 2;
            c->m_weekday[0] = wkday-1;
        }
        if(round == 2 && (schedule[2][wkday-1] == nullptr || schedule[7][wkday-1] == nullptr)) {//3~5or8~10
            //相隔需有一天
            if(wkday-1 - c->m_weekday[0] <= 1) continue;
            if(schedule[2][wkday-1] == nullptr) {schedule[2][wkday-1] = schedule[3][wkday-1] = schedule[4][wkday-1] = c;}//表示3~5开课
            else {schedule[7][wkday-1] = schedule[8][wkday-1] = schedule[9][wkday-1] = c;}//表示8~10开课
            c->m_weekday[1] = wkday-1;
            return true;
        }
    }
    if(round == 2) { //如果2找到、3没找到，需重置那2节课
        schedule[temp][c->m_weekday[0]] = schedule[temp+1][c->m_weekday[0]]  = nullptr;
    }
    c->m_weekday = nullptr;
    return false;
}

bool DirectedGraph::find3Classes(Course *c,int num) {
    int cnt = 0,*temp = new int[num];//存储是上午还是下午开课
    c->m_weekday = new int[num];//存储开课是周几
    for(int wkday = 1;wkday <= 5 || cnt == num;wkday++) {
        if(cnt == num) {//已找到可以排下的，开始修改课表
            for(int i = 0;i < cnt;i++)
                switch (temp[i]) {
                    case 0://上午开课
                        schedule[2][c->m_weekday[i]] = schedule[3][c->m_weekday[i]] = schedule[4][c->m_weekday[i]] = c;
                        break;
                    case 1://下午开课
                        schedule[7][c->m_weekday[i]] = schedule[8][c->m_weekday[i]] = schedule[9][c->m_weekday[i]] = c;
                    default:
                        break;
                }
            return true;
        }
        string name = c->m_name;
        Course *p = schedule[2][wkday-1];
        p = schedule[7][wkday-1];
        if(schedule[2][wkday-1] == nullptr) {//看当天的3~5是否可排
            //若与前一天开课中间相隔不到一天，continue
            if(cnt != 0 && (wkday-1 - c->m_weekday[cnt-1] <= 1)) continue;
            c->m_weekday[cnt] = wkday-1;
            temp[cnt] = 0;//temp[i]为0表示上午开课
            cnt++;
        }
        else if(schedule[7][wkday-1] == nullptr) {//看当天的8~10是否可排
            //若与前一天开课中间相隔不到一天，continue
            if(cnt != 0 && (wkday-1 - c->m_weekday[cnt-1] <= 1)) continue;
            c->m_weekday[cnt] = wkday-1;
            temp[cnt] = 1;//temp[i]为1表示下午开课
            cnt++;
        }
    }
    c->m_weekday = nullptr;//5天中都没找到合适的，重置m_weekday
    return false;//并返回false
}

bool DirectedGraph::find2Classes(Course *c,int num) {
    int cnt = 0,*temp = new int[num];
    c->m_weekday = new int[num];
    //先看每天的1~2、6～7是否可排
    for(int wkday = 1;wkday <= 5;wkday++) {
        if(cnt == num) {//已找到可以排下的
            for(int i = 0;i < cnt;i++)
                switch (temp[i]) {
                    case 0://1～2开课
                        schedule[0][c->m_weekday[i]] = schedule[1][c->m_weekday[i]] = c;
                        break;
                    case 1://6～7开课
                        schedule[5][c->m_weekday[i]] = schedule[6][c->m_weekday[i]] = c;
                    default:
                        break;
                }
            return true;
        }
        if(schedule[0][wkday-1] == nullptr || schedule[5][wkday-1] == nullptr) {
            //若与前一天开课中间相隔不到一天，continue
            if(cnt != 0 && (wkday-1 - c->m_weekday[cnt-1] <= 1)) continue;
            c->m_weekday[cnt] = wkday-1;
            if(schedule[0][wkday-1] == nullptr) temp[cnt] = 0;//temp[i]为0表示1~2开课
            else temp[cnt] = 1;//temp[i]为1表示6～7开课
            cnt++;
        }
    }
    //再次遍历，再看3~5、8～10是否可排
    for(int wkday = 1;wkday <= 5;wkday++) {
        if(cnt == num) {//已找到可以排下的
            for(int i = 0;i < cnt;i++)
                switch (temp[i]) {
                    case 2://1～2开课
                        schedule[2][c->m_weekday[i]] = schedule[3][c->m_weekday[i]] = c;
                        break;
                    case 3://6～7开课
                        schedule[7][c->m_weekday[i]] = schedule[8][c->m_weekday[i]] = c;
                    default:
                        break;
                }
            return true;
        }
        if(schedule[2][wkday-1] == nullptr || schedule[7][wkday-1] == nullptr) {
            //若与前一天开课中间相隔不到一天，continue
            if(cnt != 0 && (wkday-1 - c->m_weekday[cnt-1] <= 1)) continue;
            c->m_weekday[cnt] = wkday-1;
            if(schedule[2][wkday-1] == nullptr) temp[cnt] = 2;//temp[i]为2表示3~4开课
            else temp[cnt] = 3;//temp[i]为3表示8～9开课
            cnt++;
        }
    }
    c->m_weekday = nullptr;//5天中都没找到合适的，重置m_weekday
    return false;//并返回false
}

#endif /* graph_h */
