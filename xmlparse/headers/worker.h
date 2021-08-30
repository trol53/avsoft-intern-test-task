#ifndef XMLPARSE_WORKER_H
#define XMLPARSE_WORKER_H

#include "parser.h"
#include "command.h"
#include <stack>

class Worker {
public:

    Worker(std::map<Department, std::vector<Employment>>& dict) : dict(dict){}

    void Run();

    ~Worker();

private:

    void print_menu();

    void print_tree();

    std::stack<Command*> commands;
    std::map<Department, std::vector<Employment>> dict;
};


#endif //XMLPARSE_WORKER_H
