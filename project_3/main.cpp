//
//  main.cpp
//  project3-mac
//
//  Created by florrie on 2020/12/6.
//  Copyright © 2020 Florrie. All rights reserved.
//

#include "maze.h"

int main() {
    Maze maze;
    maze.initialize();
    maze.findPath();
    maze.showPath();
    return 0;
}
