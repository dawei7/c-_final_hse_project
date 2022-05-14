//
// Created by david on 06/04/2022.
//

#include "Record.h"

//Constructor
Record::Record(const string &empName,const size_t &empAge,const string &empDepartment,const string &empPosition ,const string &empBoss, const vecWorkingDays &empWorkingDays)
{
    _empName = empName;
    _empAge = empAge;
    _empDepartment = empDepartment;
    _empPosition = empPosition;
    _empBoss = (empBoss.empty()) ? "None" : empBoss; // Placeholder value if boss doesn't exist
    _empWorkingDays = empWorkingDays;
}

// Getter Functions of private variables, used for age selection and copying of register object
string Record::getName() const{return _empName;}
size_t Record::getAge() const{return _empAge;}
string Record::getDepartment() const{return _empDepartment;}
string Record::getPosition() const{return _empPosition;}
string Record::getBoss() const{return _empBoss;}
vecWorkingDays Record::getWorkingDays() const{return _empWorkingDays;}

//Operator overloading, everytime a record is printed with output stream e.g. cout<<, there is printed the custom format as below
ostream& operator<<(ostream& os, Record* record)
{
    return os<<"Name: "<<record->_empName<<", Age: "<<record->_empAge<<", Department: "<<record->_empDepartment<<", Position: "<<record->_empPosition<<", Boss: "<<record->_empBoss<<endl;
}