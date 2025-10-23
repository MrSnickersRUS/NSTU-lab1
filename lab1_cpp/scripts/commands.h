#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

using namespace std;

enum Container {
        ARRAY, SINGLE_LIST, DOUBLE_LIST, QUEUE, STACK, TREE
};

enum Operation {
    PUSH, DEL, GET, POP, INS, PRINT, ISMEMBER,
    REP, LEN, ADDHEAD, ADDTAIL, ADDBEFORE, ADDAFTER,
    READ
};

void processQuery(const string& query, const string& filePath);

#endif