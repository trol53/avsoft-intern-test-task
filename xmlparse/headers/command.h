#ifndef XMLPARSE_COMMAND_H
#define XMLPARSE_COMMAND_H

#include "department.h"
#include "employment.h"
#include <vector>
#include <map>

class Command {
public:
    virtual void execute(std::map <Department, std::vector<Employment>>&) = 0;
    virtual void undo(std::map <Department, std::vector<Employment>>&) = 0;
    virtual bool is_available() = 0;
};

class Create_Department : public Command{

public:

    Create_Department() = default;

    void execute(std::map <Department, std::vector<Employment>>& dict) override;

    void undo(std::map <Department, std::vector<Employment>>& dict) override;

    bool is_available() override;

    std::string last_name = "";
};

class Delete_Departament : public Command{
public:

    Delete_Departament() = default;

    void execute(std::map <Department, std::vector<Employment>>& dict) override;

    void undo(std::map <Department, std::vector<Employment>>& dict) override;

    bool is_available() override;

    std::pair<Department, std::vector<Employment>> node;
};

class Create_Employment : public Command {
public:
    Create_Employment() = default;

    void execute(std::map <Department, std::vector<Employment>>& dict) override;

    void undo(std::map <Department, std::vector<Employment>>& dict) override;

    bool is_exist(std::vector<Employment>& employs, Employment& employ);

    bool is_available() override;



    Department last_dep;
    Employment last_empl;
};

class Delete_Employment : public Command {
public:
    Delete_Employment() = default;

    void execute(std::map <Department, std::vector<Employment>>& dict) override ;

    void undo(std::map <Department, std::vector<Employment>>& dict) override;

    std::vector<Employment>::iterator find_employ(std::vector<Employment>& employs, Employment& employ);

    bool is_available()override;

    Employment last_empl;
    Department last_dep;

};

class Change_Department : public Command {
public:

    Change_Department() = default;

    void execute(std::map <Department, std::vector<Employment>>& dict) override;

    void undo(std::map <Department, std::vector<Employment>>& dict) override;

    bool is_available() override;

    Department last_dep;
    Department new_dep;
};

class Change_Employment : public Command{
public:

    Change_Employment() = default;

    void execute(std::map <Department, std::vector<Employment>>& dict) override;

    void undo(std::map <Department, std::vector<Employment>>& dict) override;

    void input_change(Employment& employ);



    std::vector<Employment>::iterator find_employ(std::vector<Employment>& employs);

    bool is_available() override;
    Employment new_empl;
    Employment last_empl;
    Department last_dep;
};


#endif //XMLPARSE_COMMAND_H
