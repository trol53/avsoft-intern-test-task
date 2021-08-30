#include "headers/worker.h"

void Worker::Run(){
    std::string flag;
    print_menu();
    while(true){
        std::getline(std::cin, flag);
        if (flag == "1"){
            Command* create_dep = new Create_Department;
            create_dep->execute(dict);
            if (create_dep->is_available())
                commands.push(create_dep);
        }else if(flag == "2"){
            Command* create_empl = new Create_Employment;
            create_empl->execute(dict);
            if (create_empl->is_available())
                commands.push(create_empl);
        } else if (flag == "3"){
            Command* delete_dep = new Delete_Departament;
            delete_dep->execute(dict);
            if (delete_dep->is_available())
                commands.push(delete_dep);
        } else if (flag == "4"){
            Command* delete_empl = new Delete_Employment;
            delete_empl->execute(dict);
            if (delete_empl->is_available())
                commands.push(delete_empl);
        } else if (flag == "5"){
            Command* change_dep = new Change_Department;
            change_dep->execute(dict);
            if (change_dep->is_available())
                commands.push(change_dep);
        } else if (flag == "6"){
            Command* change_empl = new Change_Employment;
            change_empl->execute(dict);
            if (change_empl->is_available())
                commands.push(change_empl);
        }else if (flag == "7"){
            print_tree();
        } else if (flag == "8"){
            if (!commands.empty()) {
                commands.top()->undo(dict);
                commands.pop();
            }
        } else if (flag == "9"){
            break;
        }
    }
}

void Worker::print_menu(){
    std::cout << "input your next act\n" <<
              "1 - create new department\n" <<
              "2 - create new employment\n" <<
              "3 - delete department\n" <<
              "4 - delete employment\n" <<
              "5 - change department\n" <<
              "6 - change deployment\n" <<
              "7 - print tree\n" <<
              "8 - undo last act\n" <<
              "9 - exit\n";
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
