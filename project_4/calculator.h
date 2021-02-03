//
//  calculator.h
//  project4-mac
//
//  Created by florrie on 2020/10/24.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef calculator_h
#define calculator_h
#include "stack.h"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Calculator {
private:
    Stack<double> operands; //计算后缀表达式时存放操作数的栈
    Stack<char> operators; //将中缀表达式转换成后缀表达式时存放操作符的栈
    string infix,postfix; //分别存放中缀、后缀表达式
    /*一些私有函数*/
    bool operationIsValid(char ch);//判断当前字符是否是运算符
    int priority(char c);//计算字符c的优先级
    bool priorityCompare(char c1,char c2);//比较当前字符与栈顶字符优先级，true表示栈顶元素优先级低于当前元素、可以入栈
    double doOperate(char c,double left,double right);//左右操作数与运算符c做运算
    
public:
    void input() {cout<<"请输入表达式："<<endl;cin>>infix;}
    void convert();//中缀转后缀
    double calculate();//计算后缀表达式
};

bool Calculator::operationIsValid(char ch) {
    switch (ch) {
        case '(':return true;break;
        case ')':return true;break;
        case '+':return true;break;
        case '-':return true;break;
        case '*':return true;break;
        case '/':return true;break;
        case '%':return true;break;
        case '^':return true;break;
        default:return false;break;
    }
}

int Calculator::priority(char c) {
    switch (c) {
        case '(': return 1;break;
        case '^': return 2;break;
        case '*': return 3;break;
        case '/': return 3;break;
        case '%': return 3;break;
        case '-': return 4;break;
        case '+': return 4;break;
        case ')': return 0;break;
        default : return -1;break;
    }
}

bool Calculator::priorityCompare(char c1,char c2) {
    //c1是栈顶元素，c2是当前处理元素current
    int pr1 = priority(c1),pr2 = priority(c2);
    if(pr1 > pr2) return true;
    else return false;
}

double Calculator::doOperate(char c,double left,double right) {
    switch (c) {
        case '+':return left + right;break;
        case '-':return left - right;break;
        case '*':return left * right;break;
        case '/':return left / right;break;
        case '%':return (int)left % (int)right;break;
        case '^':return pow(left,right);break;
        default: return 0;break;
    }
}

void Calculator::convert() {
    int i=0;
    char top_ele,current,temp;
    bool input; //true则让current进栈，false则退栈
    bool single = false;//true则代表是单目运算符
    for(i = 0;infix[i] != '=';i++) { //输入以=结束，读到=则结束
        current = infix[i];
        operators.getTop(top_ele);//用于和当前运算符比较优先级
        //一、读到数字
        if(operationIsValid(current) == false) {
            postfix = postfix + current;//数字直接放入postfix
            if(single == true) {//若数字前一个读到的是单目运算符
                operators.pop(temp);//取出那个单目运算符，后缀表达式的末两位已经是添加的0和当前读到的数字了
                postfix = postfix + temp;//再将将该单目运算符放入后缀表达式
            }
            continue;//处理完数字，直接开始读下一个字符
        }
        single=false;//重置single
        
        //二、以下是读到字符的情况
        /*先判断是不是单目运算符,单目的都先进栈并在读到下一个操作数后立马弹出*/
        if(i == 0 && current != '(') {
            //运算符如果出现在中缀表达式开头、且不是左括号，则是单目运算符
            postfix = postfix+'0';//单目运算符前加零
            single = true;
        }
        else if(operationIsValid(infix[i-1]) && current != '(' && infix[i-1] != ')') {
            //如果前一个仍是除左、右括号之外的操作符，则是单目的+或者-
            postfix = postfix+'0';//单目运算符前加零不影响结果，故可转成双目运算
            single = true;
        }
        if(single == true) {operators.push(current);continue;}//单目运算符先进栈，然后直接开始读下一个
        
        /*判断操作符current是否进栈的五种情况*/
        input = priorityCompare(top_ele,current); //栈顶元素优先级低于current时为true、加入后缀表达式，否则为false
        //1、读入的字符为第一个有效运算符时，直接进栈
        if(operators.isEmpty()) {
            operators.push(current);
            continue;
        }
        //2、若为右括号')',则弹出操作符栈里的元素，直到弹出左括号'('
        if(current == ')') {
            while(top_ele != '(') {
                operators.pop(temp); //弹出括号中的元素，它们优先运算、先加入后缀表达式中
                postfix = postfix + temp; //将弹出元素放到postfix末尾
                operators.getTop(top_ele); //更新栈顶元素
            }
            operators.pop(temp);//弹出'('元素
        }
        //3、若为栈顶为'('，current就直接进栈，因为左括号'('在栈里的优先级最低！
        else if(top_ele == '(') {
            operators.push(current);
            continue;
        }
        //4、栈顶元素优先级较低，直接进栈
        else if(input == true){
            operators.push(current);
        }
        //5、栈顶元素优先级较高或相等时
        else {
            operators.pop(temp); //弹出栈顶元素
            postfix=postfix+temp; //将弹出元素放到postfix末尾
            operators.push(current);//再将current放入栈中
        }
    }//读完中缀表达式
    
    operators.getSize();
    while(!operators.isEmpty()) {//将栈中操作符逐一取出、放到后缀表达式中
        char temp;
        operators.pop(temp);
        postfix=postfix+temp;
    }
    /*调试部分*/
//    cout<<"postfix is:"<<postfix<<endl;
}

double Calculator::calculate() {//计算后缀表达式postfix
    int i = 0,len = (int)postfix.length();
    char current;
    double right,left,result;
    for(i = 0;i < len;i++){
        current = postfix[i];
        //遇到操作数则进栈,栈中操作数数据类型为double
        if(current >= 48 && current <= 57) {
            double temp = (int)current - 48;
            operands.push(temp);
        }
        else { //遇到运算符则让两个操作数出栈
            operands.pop(right);//先出栈的是右操作数
            operands.pop(left);//后出栈的是左操作数
            result=doOperate(current,left,right); //得到计算值
            operands.push(result); //让计算值进栈
        }
    }
    operands.pop(result);
    operators.makeEmpty();//释放操作符栈
    operands.makeEmpty();//释放操作数栈
    infix.clear();//清空中缀串以便计算下一个式子
    postfix.clear();//清空后缀串
    return result;
}

#endif /* calculator_h */
