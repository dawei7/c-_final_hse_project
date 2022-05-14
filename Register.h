//
// Created by david on 04/04/2022.
//

#ifndef FINAL_PROJECT_REGISTER_H
#define FINAL_PROJECT_REGISTER_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

#include "Record.h"

using namespace std;

typedef Record Employee; // Just give an alias for Record class constructor
typedef vector<Employee*> EmplVector; // Pointer Vector of Employees (Record-class) objects
typedef map<string, Employee*> IndexByName;
typedef map<string, set<Employee*>> IndexSetOfEmployees;
typedef map<string, set<string>> Subordinates;

class Register {

public:
    /////// CONSTRUCTORS & DECONSTRUCTOR

    // Default Constructor
    Register();

    // Overloaded Constructor, if it is used to initlialize it with a CSV-File
    explicit Register(const string& path);

    // Copying an existing object, there is only a main pointer object _employees and several indixes of pointers; therefore nothing else has to be initialized
    Register(const Register& other);

    //Deconstructor
    ~Register();

    /////// OPERATOR OVERLOADING

    //Operator overloading "=" to assign (copy) one object to another, with different pointers.
    Register& operator= (const Register& rhv);

    /////// GENERAL PUBLIC FUNCTIONS

    // Same code can be used in Destructor
    // Delete all heap pointers in main employees and clear everything
    // This has to be done due correct destruction, reload of data or copying an object with new pointers
    void deleteAllRecords();

    //Load data - one of the MOST IMPORTANT!!! and extensive functions in this class, used in main.cpp
    void loadData(const string& path);

    // Is DataSet Empty, important check, for user ui, to give correct messages.
    bool isDataSetEmpty();

    /////// PUBLIC PRINT FUNCTIONS, USED IN main.cpp
    void printAllRecords() const;
    void printDataSetSize() const;
    void printRecordByName(string& name) const;
    void printRecordsByDepartment(string& department) const;
    void printRecordsByBoss(string& boss) const;
    void printRecordsByWorkingDay(string& workDay) const;
    void printEmployeesInAgeRange(size_t& lowerLimit,size_t& upperLimit) const;



private:
    /////// PRIVATE FIELDS
    // _employees as main storage of pointers; the other are indexes of pointers to retrieve it by the print functions as fast as possible
    EmplVector _employees;
    IndexByName _indexByName;
    IndexSetOfEmployees _indexByDepartments;
    IndexSetOfEmployees _indexBySubordinates;
    IndexSetOfEmployees _indexByWorkingDays;

    /////// PRIVATE HELPER FUNCTIONS


    // Swap auxiliary function swap for copy-and-swap approach in assigning one object to another
    static void swap(Register& lhv, Register rhv) noexcept;


    //Default get all employees back, this was one task of the PDF, however I get it in the print functions directly from the private field, protected by const!
    const EmplVector& getStorage() const;

    // Important direct and indirect query for other queries, 'Name' is normally a very unique attribute.
    const IndexByName& getIndexByName() const;

    // HELPER FUNCTIONS, which repeat themselves
    void insertRecordInSet(string mapKey,Employee *employee,IndexSetOfEmployees& indexSetofEmployees);
    void insertSubordinates(Subordinates subordinates);

    // Recursive DP function to find all employees who directly or indirectly
    // report to a given manager and store the result in "result".
    set<string> findAllReportingEmployees(const string& boss,map<string, set<string>> &managerToEmployeeMappings,map<string, set<string>> &result);
    map<string, set<string>> findEmployees(map<string, string> &employeeToManagerMappings);
};


#endif //FINAL_PROJECT_REGISTER_H
