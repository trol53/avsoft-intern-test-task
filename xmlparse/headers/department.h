#ifndef XMLPARSE_DEPARTMENT_H
#define XMLPARSE_DEPARTMENT_H

#include <string>
#include <vector>
#include "employment.h"


class Department{
public:

    Department(): name(""), employments_count(0), average_salary(0){};

    Department(std::string& str) : name(str), employments_count(0), average_salary(0){};

//    bool operator==(Department& rhs);
//    bool operator<(Department& rhs);

    void set_name(const std::string& name){
        this->name = name;
    }

    bool operator ==(const Department& rhs){
        return name == rhs.name;
    }

    bool operator <(const Department& rhs) const {
        return name < rhs.name;
    }

    void set_average_salary(std::vector<Employment>& employs){
            double salary = 0;
            for (auto employ : employs){
                salary += employ.salary;
            }
            average_salary = salary / employs.size();
    }

    void set_employments_count(int count){
        employments_count = count;
    }

    void print() const{
        std::cout << name << '\n' <<
            "employments count: " << employments_count << '\n' <<
            "average salary: " << average_salary << '\n';
    }

    std::string name;
    int employments_count;
    double average_salary;
};







#endif //XMLPARSE_DEPARTMENT_H
