//
// Created by david on 06/04/2022.
//

#include "Register.h"

/////// CONSTRUCTORS & DECONSTRUCTOR

// Default Constructor
Register::Register() = default;

// Overloaded Constructor, if it is used to initlialize it with a CSV-File
Register::Register(const string& path){
    loadData(path);
}

// Copying an existing object, there is only a main pointer object _employees and several indixes of pointers; therefore nothing else has to be initialized
Register::Register(const Register& other)
{
    deleteAllRecords();
    Subordinates subordinates;
    map<string, string> tempMapOfSubordinates;
    // Initializiation of main store of Pointers to single Records (Own pointer adresses)
    for(auto _employee : other._employees){
        auto *myRecord = new Employee(*_employee);
        _employees.push_back(myRecord);
        _indexByName.insert(make_pair(myRecord->getName(), myRecord));
        insertRecordInSet(myRecord->getDepartment(),myRecord,_indexByDepartments);
        insertRecordInSet(myRecord->getDepartment(),myRecord,_indexByDepartments);
        tempMapOfSubordinates.insert(pair<string, string>(myRecord->getName(),myRecord->getBoss()));
        for(const string& workingday:myRecord->getWorkingDays()){
            insertRecordInSet(workingday,myRecord,_indexByWorkingDays);
        }
    }
    subordinates = findEmployees(tempMapOfSubordinates);
    insertSubordinates(subordinates);
}

//Deconstructor
Register::~Register(){
    // Destroy all pointers stored in vector _employees
    deleteAllRecords();
}

/////// OPERATOR OVERLOADING

//Operator overloading "=" to assign (copy) one object to another, with different pointers.
Register& Register::operator= (const Register& rhv){
    if(this == &rhv){
        return *this;
    }
    //copy and swap idiom
    Register temp(rhv); //Use the constructor of Stage 6 to copy object
    swap(temp, *this); //Swap object
    return *this; //return object
}

/////// GENERAL PUBLIC FUNCTIONS

// Same code can be used in Destructor
// Delete all heap pointers in main employees and clear everything
// This has to be done due correct destruction, reload of data or copying an object with new pointers
void Register::deleteAllRecords(){
    for(Employee *employee:_employees){
        delete employee;
    }
    _employees.clear();
    _indexByName.clear();
    _indexByDepartments.clear();
    _indexBySubordinates.clear();
    _indexByWorkingDays.clear();
}

// Is DataSet Empty, important check, for user ui, to give correct messages.
bool Register::isDataSetEmpty(){
    return _employees.empty();
}


//Load data - one of the MOST IMPORTANT!!! and extensive functions in this class
void Register::loadData(const string& path){ // Filepath to read from

    // Firstly clean all data, if there are already data loaded
    if(!isDataSetEmpty()){
        deleteAllRecords();
    }

    fstream fin;

    // Open csv file and put it into the input stream
    fin.open(path, ios::in);

    // Read the Data from the file
    // as String Vector
    vector<string> row, workingDays;
    string line, word;

    // Needed for further recursive operation after loading
    Subordinates subordinates;
    map<string, string> tempMapOfSubordinates;

    while(getline(fin, line)) {

        // Used for breaking words
        stringstream s(line);

        // Clear temporary rows
        row.clear();
        workingDays.clear();

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, '\t')) {

            //At the end of line, there are the Working days, which have to be packed as a vector
            if (row.size() >= 5) {
                workingDays.push_back(word);
            }

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }


        // A pointer in Heap memory with "new" keyword is generated (manually managed memory)
        auto *myRecord = new Employee(row[0], stoi(row[1]), row[2], row[3], row[4], workingDays);

        //Main storage of pointers
        _employees.push_back(myRecord);

        //Indexed storage of the same pointers to faster retrieve some search results by index
        // 1:1 relationship, Exceptions that there are two persons with the exact name are not considered here
        _indexByName.insert(make_pair(row[0], myRecord));

        //Department 1:n relationship, it is used a set, instead of vector because the time-complexity to read it is therefore log(n) ordered set, instead of O(n)
        insertRecordInSet(row[2], myRecord, _indexByDepartments);

        //Simple storage for subordinate<->boss 1:1 relationship, basis for any further algorithm
        tempMapOfSubordinates.insert(pair<string, string>(row[0], row[4]));

        //Index of working days Mon, Tue, Wed, Thu, Fri and the related employees who work on these days.
        for (const string &workingday: workingDays) {
            insertRecordInSet(workingday, myRecord, _indexByWorkingDays);
        }
    }
    //Create a Set of Boss -> Direct and Indirect Subordinates, recursively, complex
    //1:n relationship, it is used a set, instead of vector because the time-complexity to read it is therefore log(n) ordered set, instead of O(n)
    subordinates = findEmployees(tempMapOfSubordinates);
    insertSubordinates(subordinates);
}


/////// PUBLIC PRINT FUNCTIONS, USED IN main.cpp
void Register::printAllRecords() const{
    cout<<"------- All records -------"<<endl;
    EmplVector employees = getStorage();
    for(Employee *employee:employees){
        cout<<employee;
    }
}

void Register::printDataSetSize() const{
    cout<<"------- Database size: -------"<<endl;
    size_t dbSize = _employees.size();
    cout<<"Number of records: "<<dbSize<<" records"<<endl;
}


void Register::printRecordByName(string& name) const{
    cout<<"------- "<<"Chosen name: "<<name<<" -------"<<endl;
    auto it = _indexByName.find(name);
    if (it != _indexByName.end()){
        cout<<it->second;
    }else{
        cout << "No entry with the name "<<name<<" found. Please try again.";
    }
}


void Register::printRecordsByDepartment(string& department) const{
    cout<<"------- "<<"Department: "<<department<<" -------"<<endl;
    auto it = _indexByDepartments.find(department);
    if (it != _indexByDepartments.end()){
        for(Employee *employee:it->second){ //Loop through set
            cout<<employee;
        }
    }else{
        cout << "There are no records for department "<<department<<" found. Please try again.";
    }
}

void Register::printRecordsByBoss(string& boss) const{
    cout<<"------- "<<"Boss: "<<boss<<" -------"<<endl;
    cout<<"Subordinates: "<<endl;
    auto it = _indexBySubordinates.find(boss);
    if (it != _indexBySubordinates.end()){
        for(Employee *employee:it->second){ //Loop through set
            cout<<employee;
        }
    }else{
        cout << "There are no records for boss: "<<boss<<" found. Please try again.";
    }
}

void Register::printRecordsByWorkingDay(string& workDay) const{
    cout<<"------- "<<"Workday: "<<workDay<<" -------"<<endl;
    auto it = _indexByWorkingDays.find(workDay);
    if (it != _indexByWorkingDays.end()){
        for(Employee *employee:it->second){ //Loop through set
            cout<<employee;
        }
    }else{
        cout << "There are no records for Workday "<<workDay<<" found. Please try again.";
    }
}

void Register::printEmployeesInAgeRange(size_t& lowerLimit,size_t& upperLimit) const{
    cout<<"------- All records between age: "<<lowerLimit<<" and "<<upperLimit<<" -------"<<endl;
    EmplVector employees = getStorage();
    for(Employee *employee:employees){
        if(lowerLimit<=employee->getAge() && employee->getAge()<=upperLimit)
            cout<<employee;
    }
}

/////// PRIVATE HELPER FUNCTIONS

// Swap auxiliary function swap for copy-and-swap approach in assigning one object to another
void Register::swap(Register& lhv, Register rhv) noexcept{
    std::swap(lhv._employees, rhv._employees);
    std::swap(lhv._indexByName, rhv._indexByName);
    std::swap(lhv._indexByDepartments, rhv._indexByDepartments);
    std::swap(lhv._indexBySubordinates, rhv._indexBySubordinates);
    std::swap(lhv._indexByWorkingDays, rhv._indexByWorkingDays);
}

//Default get all employees back, this was one task of the PDF, however I get it in the print functions directly from the private field, protected by const!
const EmplVector& Register::getStorage() const{
    return _employees;
}


// Important direct and indirect query for other queries, 'Name' is normally a very unique attribute.
const IndexByName& Register::getIndexByName() const{
    return _indexByName;
}

// HELPER FUNCTIONS, which repeat themselves
void Register::insertRecordInSet(string mapKey,Employee *employee,IndexSetOfEmployees& indexSetofEmployees){
    auto it = indexSetofEmployees.find(mapKey);
    if (it != indexSetofEmployees.end()){ // if key is found, get it by "it"
        it->second.insert(employee); //"it" is iterator pointer to key, ->second access the set, then insert the new employee pointer
    }else{ //If not found, make a new key value pair with a new set and the first entry
        set<Employee*> mySet = {employee};
        indexSetofEmployees.insert(make_pair(mapKey,mySet));
    }
}

void Register::insertSubordinates(Subordinates subordinates) {
    for (auto p: subordinates) {
        for (const string &subordinate: p.second) {
            auto it = _indexByName.find(subordinate);
            insertRecordInSet(const_cast<string &>(p.first), it->second, _indexBySubordinates);
        }
    }
}


// Recursive DP function to find all employees who directly or indirectly
// report to a given manager and store the result in "result".
set<string> Register::findAllReportingEmployees(const string& boss,map<string, set<string>> &managerToEmployeeMappings,map<string, set<string>> &result)
{
    // if the subproblem is already seen before
    if (result.find(boss) != result.end())
    {
        // return the already computed mapping
        return result[boss];
    }

    // find all employees reporting directly to the current manager
    set<string> managerEmployees = managerToEmployeeMappings[boss];

    // find all employees reporting indirectly to the current manager
    for (const string& employee: managerToEmployeeMappings[boss])
    {
        // find all employees reporting to the current employee
        set<string> employees = findAllReportingEmployees(employee,managerToEmployeeMappings, result);

        // move those employees to the current manager
        for (const string& c: employees){
            managerEmployees.insert(c);
        }
    }

    // save the result to avoid recomputation and return it
    result[boss] = managerEmployees;
    return managerEmployees;
}


// Find all employees who directly or indirectly reports to a manager
map<string, set<string>> Register::findEmployees(map<string, string> &employeeToManagerMappings)
{
    // store manager to employee mappings in a new map.
    // `unordered_set<char>` is used since a manager can have several employees mapped
    map<string, set<string>> managerToEmployeeMappings;

    // fill the above map with the manager to employee mappings
    for (auto& it: employeeToManagerMappings)
    {
        string employee = it.first;
        string boss = it.second;

        // don't map an employee with itself
        if (employee != boss) {
            managerToEmployeeMappings[boss].insert(employee);
        }
    }

    // construct an ordered map to store the result
    map<string, set<string>> result;

    // find all reporting employees (direct and indirect) for every manager
    // and store the result in a map
    for (auto p: employeeToManagerMappings)
    {
        findAllReportingEmployees(p.first, managerToEmployeeMappings, result);
    }

    return result;
}














