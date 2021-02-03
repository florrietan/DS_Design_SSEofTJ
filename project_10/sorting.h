//
//  sorting.h
//  project10-mac
//
//  Created by florrie on 2020/12/1.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef sorting_h
#define sorting_h

#include <time.h>
#include <cmath>
#include "sortingtable.h"
// define start time and end time
#define BEGIN_RECORD                    \
    {                                   \
        clock_t ____temp_begin_time___; \
        ____temp_begin_time___ = clock();

#define END_RECORD(dtime)                                                    \
    dtime = float(clock() - ____temp_begin_time___) / CLOCKS_PER_SEC * 1000; \
    }

class Sort {
private:
    int m_num; //用户自定义
    int *m_array; //该指针开辟来用于存放数据的数组
    int m_choice; //表示选择的排序方式
    int m_RMN; //表示交换次数
    int m_time; //表示排序所用时间
    
    /*以下是一些辅助私有函数*/
    void randomArray();
    int * copyArray();
    void swap(int &a,int &b) {int temp = a;a = b;b = temp;}
    void selectSort(int *array,const int i);
    void shellInsert(int *array,const int gap);
    int partition(int *array, const int low,const int high);
    void quickSort(int *array,const int left,const int right);//快速排序
    void filterDown(int *heap,const int i,const int endOfHeap);
    void merge(int *array1,int *array2,const int left,const int mid,const int right);
    void doSort(int *array1,int *array2,int left,int right);
    void radixSort(int *array,int left,int right,int d);
    int getDigit(int a,int d);
    
    /*以下是几个主要排序函数*/
    void bubbleSort();//冒泡排序
    void selectSort();//选择排序
    void straightInsertSort();//直接插入排序
    void shellSort();//希尔排序
    void quickSort();//快速排序
    void heapSort(); //堆排序
    void mergeSort();//归并排序
    void radixSort();//基数排序
    
public:
    Sort() {m_array = nullptr;m_num = 0;m_choice = 0;m_RMN = 0;m_time = 0;}
    ~Sort() {};
    void initialize();
    void run();
};

/*下面是函数定义部分*/
void Sort::initialize() {
    cout << "排序算法比较:" << endl;
    cout << "1 ---- 冒泡排序" << endl;
    cout << "2 ---- 选择排序" << endl;
    cout << "3 ---- 直接插入排序" << endl;
    cout << "4 ---- 希尔排序" << endl;
    cout << "5 ---- 快速排序" << endl;
    cout << "6 ---- 堆排序" << endl;
    cout << "7 ---- 归并排序" << endl;
    cout << "8 ---- 基数排序" << endl;
    cout << "9 ---- 退出程序" << endl;

    cout << "请输入要产生的随机数的个数：";
    cin >> m_num;
    m_array = new int[m_num];
    randomArray();
}

void Sort::run() {
    while(m_choice != 9) {
        m_time = 0;
        m_RMN = 0;
        cout << "请选择排序算法：";
        cin >> m_choice;
        switch (m_choice) {
            case 1 :
                bubbleSort();
                cout << "冒泡排序所用时间：" << m_time << endl;
                cout << "冒泡排序交换次数：" << m_RMN << endl;
                break;
            case 2 :
                selectSort();
                cout << "选择排序所用时间：" << m_time << endl;
                cout << "选择排序交换次数：" << m_RMN << endl;
                break;
            case 3 :
                straightInsertSort();
                cout << "直接插入排序所用时间：" << m_time << endl;
                cout << "直接插入排序交换次数：" << m_RMN << endl;
                break;
            case 4 :
                shellSort();
                cout << "希尔排序所用时间：" << m_time << endl;
                cout << "希尔排序交换次数：" << m_RMN << endl;
                break;
            case 5 :
                quickSort();
                cout << "快速排序所用时间：" << m_time << endl;
                cout << "快速排序交换次数：" << m_RMN << endl;
                break;
            case 6 :
                heapSort();
                cout << "堆排序所用时间：" << m_time << endl;
                cout << "堆排序交换次数：" << m_RMN << endl;
                break;
            case 7 :
                mergeSort();
                cout << "归并排序所用时间：" << m_time << endl;
                cout << "归并排序比较次数：" << m_RMN << endl;
                break;
            case 8 :
                radixSort();
                cout << "基数排序所用时间：" << m_time << endl;
                cout << "基数排序交换次数：" << m_RMN << endl;
                break;
            case 9 :
                cout << "您已退出程序！" << endl;
                break;
            default :
                cout << "没有该操作！请重新输入：" << endl;
                break;
        }//switch结束
    }//while循环结束
}//函数定义结束

void Sort::randomArray() {
    int i = 0;
    srand((unsigned)time(NULL)); //产生随机种子
    for(i = 0;i < m_num;i++) {
        m_array[i] = rand() % (5*m_num+1) + 0; //0~5*m_num
    }
}

int * Sort::copyArray() {
    int * tempArray = new int[m_num];//存储的复制数组
    for(int i = 0;i < m_num;i++)
        tempArray[i]=m_array[i];//复制数组
    return tempArray;
}

/*冒泡排序*/
void Sort::bubbleSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int *tempArray = copyArray();
    int i = 0,j = 0,temp = 0;
    for(i = 0;i < m_num-1;i++) {//需要完成num-1趟冒泡
        for(j = 0;j < m_num-i-1;j++) {
            if(tempArray[j] > tempArray[j+1]) { //大数后移
                temp = tempArray[j];
                tempArray[j] = tempArray[j+1];
                tempArray[j+1]=temp;
                m_RMN++;
            }//if语句结束
        }//内层循环结束
    }//外层循环结束
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);
}

/*选择排序*/
void Sort::selectSort(int *array,const int i){
    int k = i;
    for (int j = i+1;j < m_num;j++)
        if (array[j] < array[k]) k = j; //当前具最小关键码的对象
    if (k != i) {//需要与第i个元素交换
        swap (array[i],array[k]);
        m_RMN++;
    }
}

void Sort::selectSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int *tempArray = copyArray();
    for(int i = 0;i < m_num-1;i++)
        selectSort(tempArray,i);
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);
}

/*直接插入法排序*/
void Sort::straightInsertSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int *tempArray = copyArray();
    int i = 0,j = 0,insertPos = 0,temp = 0;
    for(i = 1;i < m_num;i++) {
        insertPos = i;
        for(j = 0;j < i;j++){
            if(tempArray[i] < tempArray[j]) {insertPos = j;break;}//不可取等于，保证排序的稳定性
        }
        if(insertPos != i) {//插入位置发生了改变,需要将部分数据后移
            temp = tempArray[i];
            m_RMN++;
            for(j = i;j > insertPos;j--)
                {tempArray[j] = tempArray[j-1];m_RMN++;}//insertPos~i-1之间都后移一格
            tempArray[insertPos] = temp;
            m_RMN++;
        }
    }
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);
}

/*希尔排序*/
void Sort::shellInsert(int *array,const int gap) {
    for (int i = gap; i < m_num; i++) {
        int temp = array[i];
        int j = i;
        while (j >= gap && temp < array[j-gap]) {
            array[j] = array[j-gap];
            j -= gap;
            m_RMN++;
        }
        array[j] = temp;
    }
    m_RMN = m_RMN + 2;
}

void Sort::shellSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int gap = m_num/2;
    int *tempArray = copyArray();
    while(gap > 0) {
        shellInsert(tempArray, gap);
        gap = gap/2.2;
    }
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);
}

/*快速排序*/
int Sort::partition (int *array, const int low,const int high ) {
    int pivotPos = low; //基准位置
    int pivot = array[low];//选定轴点的值
    for(int i = low+1;i <= high;i++)
        if(array[i] < pivot && ++pivotPos != i) {swap(array[pivotPos],array[i]);m_RMN++;}
    //小于基准对象的交换到区间的左侧去
    swap(array[low],array[pivotPos]);
    m_RMN++;
    return pivotPos;
}

void Sort::quickSort (int *array,const int left,const int right) {
    //在待排序区间left∼right中递归地进行快速排序
    if(left < right) {
        int pivotPos = partition(array,left,right); //划分
        quickSort(array,left,pivotPos-1);
        //在左子区间递归进行快速排序
        quickSort(array,pivotPos+1,right);
        //在左子区间递归进行快速排序
    }
}

void Sort::quickSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int *tempArray = copyArray();
    quickSort(tempArray,0,m_num-1);
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);
}

/*堆排序*/
void Sort::filterDown (int *heap,const int i,const int endOfHeap ) {//堆调整算法
    int current = i;
    int child = 2*i+1;
    int temp = heap[i];
    while(child <= endOfHeap) {
        if(child +1 <= endOfHeap && heap[child] < heap[child+1]) child = child+1;
        if (temp >= heap[child]) break;
        else {
            heap[current] = heap[child];
            current = child;
            child = 2*child+1;
            m_RMN++;
        }
    }
    heap[current] = temp;
}

void Sort::heapSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int *tempArray = copyArray();
    int level = 1,i = 0;
    for(i = 0;level < m_num;i++)
        level = level * 2;
    level = i - 1;
    //将表转换成堆
    for(i = (m_num - 2) / 2; i >= 0; i--)
        filterDown(tempArray,i,m_num-1);
    
    for (int i = m_num-1;i >= 1;i--) {
        swap(tempArray[0],tempArray[i]); //堆顶元素与未排序的末尾元素交换
        m_RMN++;
        filterDown(tempArray,0,i-1 ); //重建最大堆
    }
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);
}

/*归并排序*/
//合并序列
void Sort::merge(int *array1,int *array2,const int left,const int mid,const int right) {
    for(int i = left;i <= right;i++)
        array2[i] = array1[i];
    int s1 = left,s2 = mid + 1,t = left;//s1、s2是指向array1、array2的指针，t是存放指针
    while(s1 <= mid && s2 <= right) { //未检测完，进行两两比较
        if(array2[s1] <= array1[s2]) array1[t++] = array2[s1++];
        else array1[t++] = array2[s2++];
        m_RMN++;//在此表示比较次数加1
    }
    while (s1 <= mid) array1[t++] = array2[s1++];
    while (s2 <= right) array1[t++] = array2[s2++];
}
//划分
void Sort::doSort(int *array1,int *array2,int left,int right) {
    if(left >= right) return;
    int mid = (left + right) / 2;
    doSort(array1,array2,left,mid);
    doSort(array1,array2,mid + 1,right);
    merge(array1,array2,left,mid,right);
}

void Sort::mergeSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int *tempArray = copyArray();
    int *newArray = new int[m_num];
    doSort(tempArray,newArray,0,m_num-1);
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);
    delete [] newArray;

}

/*基数排序MSD*/
int Sort::getDigit(int a,int d) {
    int temp = a,i = 0;
    while (temp != 0) {
        temp = temp / 10;
        i++;
    }//得到该数的位数
    if(d > i) {return 0;}//超过位数，返回0（如取99的第三位即百位是不存在的，则返回0）
    temp = a;//第d位的数字
    for(i = 0;i < d;i++) {
        temp = a - a/10*10; //temp从原数字个位开始，每次取最低位的数字
        a = a/10; //原数除以10，砍掉末尾数字
    }
    return temp;
}

void Sort::radixSort(int *array,int left,int right,int d) {//先按第d位基数作为关键码排序
    if(d == 0) return;//递归结束条件;
    int i = 0,j = 0,count[10]={0},pos[10]={0};//count存储i基数桶中元素
    int *bucket = new int[right-left+1];//pos存储i桶最后一个元素在bucket数组中的位置
    for(i = left;i <= right;i++) {//统计每个桶元素的个数
        count[getDigit(array[i],d)]++;
    }
    pos[0] = count[0]-1;//第0个桶结束位置是为0的元素个数-1
    for(j = 1;j < 10;j++)
        pos[j] = pos[j-1] + count[j];//j个桶末尾位置是count[j-1]~count[j]-1
    for(i = left;i <= right;i++) {//按位分配到桶中，存于bucket数组
        j = getDigit(array[i],d);
        bucket[pos[j]] = array[i];
        pos[j]--;//位置减1
    }
    for(i = left,j = 0;i <= right;i++,j++)
        array[i] = bucket[j];//辅助数组复制给array数组
    //桶内递归
    for(i = 0;i < 10;i++) {//10个大桶
        if(i == 0) left = left;
        else  left = right+1;//递归调用
        right = left+count[i]-1;
        if(left >= right) continue;//无元素或只有一个，不必再排序
        radixSort(array,left,right,d-1);
    }
}

void Sort::radixSort() {
    m_RMN = 0;
    unsigned long startTime = clock();
    int *tempArray = copyArray();
    int temp = 10*m_num,d = 0;
    while (temp != 0) {
        temp = temp / 10;
        d++;
    }//得到该数的位数
    radixSort(tempArray,0,m_num-1,d);
    m_RMN = 0;
    unsigned long endTime = clock();
    m_time = (int)(endTime - startTime);

}
#endif /* sorting_h */
