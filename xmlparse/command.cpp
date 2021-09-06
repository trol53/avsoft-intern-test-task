#include <iostream>
#include "headers/command.h"

void Create_Department::execute(std::map <Department, std::vector<Employment>>& dict){
    std::cout << "input department name:\n";
    std::string name;
    std::getline(std::cin, name);
    Department dep(name);
    if (dict.find(dep) == dict.end()){
        dict.insert({dep, std::vector<Employment>(0)});
        last_name = name;
    } else {
        std::cout << "already exist\n";
    }
}
void Create_Department::undo(std::map <Department, std::vector<Employment>>& dict){
    Department dep(last_name);
    dict.erase(dep);
}

bool Create_Department::is_available(){
    return !last_name.empty();
}

void Delete_Departament::execute(std::map <Department, std::vector<Employment>>& dict){
    std::cout << "input department name:\n";
    std::string name;
    std::getline(std::cin, name);
    Department dep(name);
    auto iter = dict.find(dep);
    if (iter != dict.end()){
        node = *iter;
        dict.erase(iter);
    } else {
        std::cout << "wrong name\n";
    }
}

void Delete_Departament::undo(std::map <Department, std::vector<Employment>>& dict){
    dict.insert({node.first, node.second});
}

bool Delete_Departament::is_available(){
    return !node.first.name.empty();
}

void Create_Employment::execute(std::map <Department, std::vector<Employment>>& dict){
    std::cout << "input department name:\n";
    std::string name;
    std::getline(std::cin, name);
    Department dep(name);
    auto iter = dict.find(dep);
    if (iter != dict.end()){
        Employment employ;
        employ.input();
        last_dep = iter->first;
        iter->second.push_back(employ);
        std::vector<Employment> tmp = std::move(iter->second);
        dict.erase(iter);
        dep.set_average_salary(tmp);
        dep.set_employments_count(tmp.size());
        dict.insert({dep, tmp});
    } else {
        std::cout << "Wrong name\n";
    }
}

void Create_Employment::undo(std::map <Department, std::vector<Employment>>& dict) {
    auto iter = dict.find(last_dep);
    std::vector<Employment> tmp = std::move(iter->second);
    tmp.pop_back();
    dict.erase(iter);
    dict.insert({last_dep, tmp});

}

bool Create_Employment::is_available(){
    return !last_dep.name.empty();
}

void Delete_Employment::execute(std::map <Department, std::vector<Employment>>& dict) {
    std::cout << "input department name:\n";
    std::string name;
    std::getline(std::cin, name);
    Department dep(name);
    auto iter = dict.find(dep);
    if (iter != dict.end()){
        Employment employ;
        std::cout << "input FLM of employment\n";
        auto iter_employ = find_employ(iter->second, employ);
        if (iter_employ != iter->second.end()){
            last_empl = *iter_employ;
            last_dep = iter->first;
            iter->second.erase(iter_employ);
            std::vector<Employment> tmp = std::move(iter->second);
            dep.set_average_salary(tmp);
            dep.set_employments_count(tmp.size());
            dict.erase(iter);
            dict.insert({dep, tmp});
        } else {
            std::cout << "wrong name\n";
        }
    } else {
        std::cout << "wrong name\n";
    }
}

void Delete_Employment::undo(std::map <Department, std::vector<Employment>>& dict) {
    auto iter = dict.find(last_dep);
    iter->second.push_back(last_empl);
    std::vector<Employment> tmp = std::move(iter->second);
    dict.erase(iter);
    dict.insert({last_dep, tmp});
}

std::vector<Employment>::iterator Delete_Employment::find_employ(std::vector<Employment>& employs, Employment& employ){
    std::string name;
    std::getline(std::cin, name);
    employ.set_first_name(name);
    std::getline(std::cin, name);
    employ.set_last_name(name);
    std::getline(std::cin, name);
    employ.set_middle_name(name);
    auto iter = employs.begin();
    for (; iter != employs.end(); iter++){
        if (*iter == employ){
            break;
        }
    }
    return iter;
}

bool Delete_Employment::is_available(){
    return !last_dep.name.empty();
}

void Change_Department::execute(std::map <Department, std::vector<Employment>>& dict){
    std::cout << "input department name:\n";
    std::string name;
    std::getline(std::cin, name);
    Department dep(name);
    auto iter = dict.find(dep);
    if (iter != dict.end()){
        last_dep = iter->first;
        std::cout << "input new name:\n";
        std::getline(std::cin, name);
        std::vector<Employment> tmp = std::move(iter->second);
        dep = iter->first;
        dep.set_name(name);
        dict.erase(iter);
        dict.insert({dep, tmp});
        new_dep = dep;
    } else {
        std::cout << "wrong name\n";
    }
}

void Change_Department::undo(std::map <Department, std::vector<Employment>>& dict) {
    auto iter = dict.find(new_dep);
    std::vector<Employment> tmp = std::move(iter->second);
    dict.erase(iter);
    dict.insert({last_dep, tmp});
}

bool Change_Department::is_available() {
    return !new_dep.name.empty();
}

void Change_Employment::execute(std::map <Department, std::vector<Employment>>& dict) {
    std::cout << "input department name:\n";
    std::string name;
    std::getline(std::cin, name);
    Department dep(name);
    auto iter = dict.find(dep);
    if (iter != dict.end()){
        Employment employ;
        std::cout << "input FLM of employment\n";
        auto iter_employ = find_employ(iter->second);
        if (iter_employ != iter->second.end()){
            last_empl = *iter_employ;
            last_dep = iter->first;
            employ = *iter_employ;
            input_change(employ);
            new_empl = employ;
            *iter_employ = employ;
            std::vector<Employment> tmp = std::move(iter->second);
            dep.set_average_salary(tmp);
            dep.set_employments_count(tmp.size());
            dict.erase(iter);
            dict.insert({dep, tmp});

        } else {
            std::cout << "wrong name\n";
        }
    } else {
        std::cout << "wrong name\n";
    }
}

void Change_Employment::undo(std::map <Department, std::vector<Employment>>& dict) {
    auto iter = dict.find(last_dep);
    auto employ_iter = iter->second.begin();
    while (*employ_iter != new_empl){
        employ_iter++;
    }
    *employ_iter = last_empl;
    std::vector<Employment> tmp = std::move(iter->second);
    dict.erase(iter);
    dict.insert({last_dep, tmp});
}

void Change_Employment::input_change(Employment& employ){
    std::string flag;
    std::cout << "choose field for change\n" <<
              "1 - first name\n" <<
              "2 - last name\n" <<
              "3 - middle name\n" <<
              "4 - salary\n" <<
              "5 - function\n";
    std::getline(std::cin, flag);
    std::string tmp;
    if (flag == "1"){
        std::cout << "input new name\n";
        std::getline(std::cin, tmp);
        employ.set_first_name(tmp);
    } else if (flag == "2"){
        std::cout << "input new name\n";
        std::getline(std::cin, tmp);
        employ.set_last_name(tmp);
    } else if (flag == "3") {
        std::cout << "input new name\n";
        std::getline(std::cin, tmp);
        employ.set_middle_name(tmp);
    } else if (flag == "4"){
        std::cout << "input new salary\n";
        std::getline(std::cin, tmp);
        employ.set_salary(std::atoi(tmp.c_str()));
    } else if (flag == "5"){
        std::cout << "input new function\n";
        std::getline(std::cin, tmp);
        employ.set_function(tmp);
    }

}



std::vector<Employment>::iterator Change_Employment::find_employ(std::vector<Employment>& employs){
    Employment employ;
    std::string name;
    std::getline(std::cin, name);
    employ.set_first_name(name);
    std::getline(std::cin, name);
    employ.set_last_name(name);
    std::getline(std::cin, name);
    employ.set_middle_name(name);
    auto iter = employs.begin();
    for (; iter != employs.end(); iter++){
        if (*iter == employ){
            break;
        }
    }
    return iter;
}

bool Change_Employment::is_available(){
    return  !last_dep.name.empty();
}


