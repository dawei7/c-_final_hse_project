//
// Created by david on 04/04/2022.
//

#include "Register.h"

using namespace std;

int main(){


    /*
    // Little Smoke Test
    Register employees = Register();

    //Register employees = Register("employees.csv");
    employees.loadData("employees.csv");

    cout<<"employees object 1"<<endl;
    employees.printAllRecords();

    string name = "Asiyah Joseph";
    employees.printRecordByName(name);

    employees.deleteAllRecords();

    employees.loadData("employees.csv");

    employees.printAllRecords();

    Register employees_2 = Register(employees);

    employees.deleteAllRecords();

    cout<<"employees object 2"<<endl;
    //Contionue with copied object employees_2, pointers are newly creatred, otherwise it wouldn't work after deleting all records from original object.
    string department = "acc";
    employees_2.printRecordsByDepartment(department);
    employees_2.printRecordsByBoss(name);

    string workday="Mon";
    employees_2.printRecordsByWorkingDay(workday);

    size_t lowerLimit = 20;
    size_t upperLimit = 30;

    employees_2.printEmployeesInAgeRange(lowerLimit,upperLimit);

    Register employees_3 = employees_2;

    cout<<"employees object 3"<<endl;
    employees_3.printRecordsByBoss(name);
    */

    // Initialize a register object
    Register employees = Register();

    string UI=
            "\n"
            "\n"
            "Employee database\n"
            "=================\n"
            "(L) Load a file\n"
            "(C) Clear the dataset\n"
            "(N) Print number of records in the dataset\n"
            "(P) Print all records\n"
            "(E) Print an employee by their name\n"
            "(D) Print all employees by their department\n"
            "(A) Print all employees with an age in a given range\n"
            "(S) Print all direct & indirect subordinates from an Employee as a whole.\n"
            "(W) Print all Employee, who work on a specified workday.\n"
            "(X) Exit\n"
            "Choose an action:\n";

    string input, line, isDataSetEmpty, filePath;
    size_t lowerAgeLimit, upperAgeLimit;
    cout<<UI; //First time it is shown for sure
    while(true){ //Infinite Loop, until Case is 'X', then return 0 and finish program.

        cin >> input;
        if (input.length() != 1) {
            cout << "You've typed in not exactly 1 character."<<endl;
            cout << "please type exactly 1 characters to choose among the executable options."<<endl;
        } else {
            switch (toupper(input[0])) {
                case 'X':
                    return 0;
                case 'L':
                    cout << "Please specify the filepath:" << endl;
                    cin >> filePath;
                    if (!employees.isDataSetEmpty()) {employees.deleteAllRecords();} //If database is not empty, please delete all records firstly
                    employees.loadData(filePath);
                    if(employees.isDataSetEmpty()){
                        cout<<"Something went wrong. The data could not be loaded correctly."<<endl;
                        break;}
                    break;
                case 'C':
                    if(employees.isDataSetEmpty()){break;}
                    employees.deleteAllRecords();
                    cout<<"Database successfully deleted. Please load new data."<<endl;
                    break;
                case 'N':
                    if(employees.isDataSetEmpty()){break;}
                    employees.printDataSetSize();
                    break;
                case 'P':
                    if(employees.isDataSetEmpty()){break;}
                    employees.printAllRecords();
                    break;
                case 'E':
                    if(employees.isDataSetEmpty()){break;}
                    cout<<"Please type in the employees 'full name' e.g. 'Caius Mueller'"<<endl;
                    getline(cin >> ws, line);
                    employees.printRecordByName(line);
                    break;
                case 'D':
                    if(employees.isDataSetEmpty()){break;}
                    cout<<"Please type in the department e.g. 'acc','it','crm','mngr','head'"<<endl;
                    getline(cin >> ws, line);
                    employees.printRecordsByDepartment(line);
                    break;
                case 'A':
                    if(employees.isDataSetEmpty()){break;}
                    cout<<"Please insert lower age limit:"<<endl;
                    cin>>lowerAgeLimit;
                    cout<<"Please insert upper age limit:"<<endl;
                    cin>>upperAgeLimit;
                    employees.printEmployeesInAgeRange(lowerAgeLimit,upperAgeLimit);
                    break;
                case 'S':
                    if(employees.isDataSetEmpty()){break;}
                    cout<<"Please type in the employees 'full name' in e.g. 'Asiyah Joseph'"<<endl;
                    getline(cin >> ws, line);
                    employees.printRecordsByBoss(line);
                    break;
                case 'W':
                    if(employees.isDataSetEmpty()){break;}
                    cout<<"Please type one of the following workdays: 'Mon','Tue','Wed','Thu','Fri','Sat','Sun'"<<endl;
                    getline(cin >> ws, line);
                    employees.printRecordsByWorkingDay(line);
                    break;

                default:
                    break;
            }
        }
        isDataSetEmpty = employees.isDataSetEmpty()?"\nAttention: Please load data (L) firstly, before choosing any other option.":"\nDataSet "+ filePath + " loaded.";
        cout << isDataSetEmpty;
        cout << UI;
    }

    return 0;
}
