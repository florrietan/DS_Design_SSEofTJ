//
//  main.cpp
//  project-9
//
//  Created by florrie on 2020/12/15.
//  Copyright © 2020 Florrie. All rights reserved.
//
#include "graph.h"
int main() {
    DirectedGraph curricula;
    if(curricula.initialize() == false) {
        ofstream outFile;//写文件
        outFile.open("outputSchedule.txt");
        outFile << "课程数目错误，无法排课！" << endl;
        return 0;
    }
    curricula.topoSort();
    curricula.distribute();
    return 0;
}
