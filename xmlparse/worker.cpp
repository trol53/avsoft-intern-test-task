#include "headers/worker.h"

void Worker::Run(){
    std::string file_name;
    std::cout << "input file name\n";
    std::getline(std::cin, file_name);
    dict = pars.Load(file_name);
    int flag;
    std::string tmp;
    Command* command;
    print_menu();
    bool break_check = true;
    while(break_check){
        std::getline(std::cin, tmp);
        flag = std::atoi(tmp.c_str());
        switch (flag) {

        case 0:
            std::cout << "input new file name\n";
            std::getline(std::cin, file_name);
            dict = pars.Load(file_name);
            break;
        case 1:
            command = new Create_Department;
            command->execute(dict);
            if (command->is_available())
                commands.push(command);
            break;
        case 2:
            command = new Create_Employment;
            command->execute(dict);
                if (command->is_available())
                    commands.push(command);
            break;
        case 3:
            command = new Delete_Departament;
            command->execute(dict);
            if (command->is_available())
                commands.push(command);
            break;
        case 4:
            command = new Delete_Employment;
            command->execute(dict);
            if (command->is_available())
                commands.push(command);
            break;
        case 5:
            command = new Change_Department;
            command->execute(dict);
            if (command->is_available())
                commands.push(command);
            break;
        case 6:
            command = new Change_Employment;
            command->execute(dict);
            if (command->is_available())
                commands.push(command);
            break;
        case 7:
            print_tree();
            break;
        case 8:
            if (!commands.empty()) {
                commands.top()->undo(dict);
                commands.pop();
            }
            break;
        case 9:
            std::cout << "input file name\n";
            std::getline(std::cin, file_name);
            pars.Save(file_name, dict);
        case 10:
            break_check = false;
            break;
        }
        print_menu();
    }
}

void Worker::print_menu(){
    std::cout << "input your next act\n" <<
              "0 - load new file\n" <<
              "1 - create new department\n" <<
              "2 - create new employment\n" <<
              "3 - delete department\n" <<
              "4 - delete employment\n" <<
              "5 - change department\n" <<
              "6 - change employment\n" <<
              "7 - print tree\n" <<
              "8 - undo last act\n" <<
              "9 - save\n" <<
              "10 - exit\n";
}

void Worker::print_tree(){
    for (auto node : dict){
        node.first.print();
        for (auto empl : node.second){
            empl.print();
        }
    }
}

Worker::~Worker(){
	while(!commands.empty()){
		delete commands.top();
		commands.pop();
	}
}
