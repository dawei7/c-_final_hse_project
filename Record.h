//
// Created by david on 04/04/2022.
//

#ifndef FINAL_PROJECT_RECORD_H
#define FINAL_PROJECT_RECORD_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<string> vecWorkingDays;


class Record {

public:
    //Constructor
    Record(const string &empName,const size_t &empAge,const string &empDepartment,const string &empPosition ,const string &empBoss, const vecWorkingDays &empWorkingDays);

    // Getter Functions of private variables, used for age selection and copying of register object
    string getName() const;
    size_t getAge() const;
    string getDepartment() const;
    string getPosition() const;
    string getBoss() const;
    vecWorkingDays getWorkingDays() const;

private:
    string _empName;
    size_t _empAge;
    string _empDepartment;
    string _empPosition;
    string _empBoss;
    vecWorkingDays _empWorkingDays;

    // Operator "<<" overloading
    friend ostream& operator<<(ostream& os, Record* record);
};


#endif //FINAL_PROJECT_RECORD_H
