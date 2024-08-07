/* Project on Employee Management System */

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

int getValidInt(const string&);
float getValidFloat();

const char* fileName = "employee.dat";

class Employee {
    int EmpID;
    char EmpName[50], post[50], department[30];
    float salary;

public:
    void getdata() {
        cout << "\nEnter Employee ID: ";
        EmpID = getValidInt("employee ID"); // Get valid integer input for Employee ID
        cout << "Enter name of employee: ";
        cin.ignore();
        cin.getline(EmpName, 50);
        cout << "Enter Post of the Employee: ";
        cin.getline(post, 50);
        cout << "Enter Employee's Department: ";
        cin.getline(department, 50);
        cout << "Enter Salary: ";
        salary = getValidFloat(); // Get valid float input for salary
    }

    void showdata() 
	{
        cout << setw(10) << left << EmpID << setw(33) << EmpName << setw(33) << post << setw(25) << department << setw(10) << fixed << setprecision(2) << salary << endl;
        cout << string(114, '-') << endl;
    }

    int getID()
	{
        return EmpID;
    }

    char* getdepartment() 
	{
        return department;
    }
};

// Function to read and validate integer input
int getValidInt(const string& prompt) {
    int number;
	char input[20];
    while (true) 
	{
      cin>>input;

        // Check if the input string represents a valid integer
        bool valid = true;
        number = 0;
        for ( int i = 0; i < strlen(input); ++i) {
            if (input[i] < '0' || input[i] > '9') {
                valid = false;
                break;
            }
            number = number * 10 + (input[i] - '0');
        }
        if (valid && strlen(input)!=0) {
            return number;
        } else {
            cout << "Invalid input. Please enter a numeric value for " << prompt << ": ";
        }
        // Clear the error state and ignore the rest of the input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Function to read and validate float input
float getValidFloat() {
    float number;
    while (true) {
        string input;
        cin >> input;

        // Check if the input string represents a valid float
        bool valid = true;
        number = 0.0f;
        bool decimalPoint = false;
        float divisor = 10.0f;

        for (size_t i = 0; i < input.length(); ++i) {
            if (input[i] == '.') {
                if (decimalPoint) {
                    valid = false;
                    break;
                }
                decimalPoint = true;
            } 
			else if (input[i] >= '0' && input[i] <= '9') 
			{
                if (decimalPoint) {
                    number += (input[i] - '0') / divisor;
                    divisor *= 10.0f;
                } 
				else 
				{
                    number = number * 10.0f + (input[i] - '0');
                }
            } 
			else 
			{
                valid = false;
                break;
            }
        }
        if (valid && !input.empty()) 
		{
            return number;
        } 
		else 
		{
            cout << "Invalid input. Please enter a numeric value for salary: ";
        }
        // Clear the error state and ignore the rest of the input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void printHeader() 
{
    cout << endl << string(114, '-');
    cout << endl << setw(10) << "ID" << setw(33) << "Name" << setw(33) << "Post" << setw(25) << "Department" << setw(12) << "Salary" << endl;
    cout << string(114, '-') << endl;
}

void sortEmployeesById(Employee* employees, int count) 
{
    // Implementing a simple bubble sort algorithm to sort employees by EmpID
    for (int i = 0; i < count - 1; i++) 
	{
        for (int j = i + 1; j < count; j++) 
		{
            if (employees[i].getID() > employees[j].getID()) 
			{
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
}

int main() 
{
    Employee emp, e, tem;
    int id, choice, isFound, counter, recordNo, location;
    char ch, Dept[50];
    char tempFile[] = "temp.dat";
    fstream file, temp;

    while (1) {
        cout << "\n\n\t\t\t\t  WELCOME TO EMPLOYEE MANAGEMENT SYSTEM";
        cout << "\n\t\t\t\t\t\tMAIN MENU";
        cout << "\n\t\t\t\t============================================";
        cout << "\n\t\t\t\t[1] Add a new record";
        cout << "\n\t\t\t\t[2] Search record from employee id";
        cout << "\n\t\t\t\t[3] List employee of particular department";
        cout << "\n\t\t\t\t[4] Display all employee";
        cout << "\n\t\t\t\t[5] Update record of an employee";
        cout << "\n\t\t\t\t[6] Delete record of particular employee";
        cout << "\n\t\t\t\t[7] Exit from the program";
        cout << "\n\t\t\t\t============================================";
        cout << "\n\t\t\t\tEnter your choice (1-7): ";
        choice = getValidInt("your choice"); // Get valid integer input for choice

        switch (choice) 
		{
            case 1:
                emp.getdata();
                file.open(fileName, ios::in | ios::binary);
                isFound = 0;
                file.read((char*)&e, sizeof(e));
                if (file) {
                    while (!file.eof()) {
                        if (e.getID() == emp.getID()) //checks if the id already exists
						{
                            cout << "\nThis ID already exists......Try for another ID" << endl;
                            isFound = 1;
                            file.close();
                            break;
                        }
                        file.read((char*)&e, sizeof(e));
                    }
                    if (isFound == 1) 
						break;
                }
                file.close();
                file.open(fileName, ios::app | ios::binary);
                if (!file) {
                    file.open(fileName, ios::out | ios::binary);
                }
                file.seekp(0, ios::end);
                file.write((char*)&emp, sizeof(emp));
                cout << "\nNew record has been added successfully...... " << endl;
                file.close();
                break;
            case 2:
                isFound = 0;
                cout << "\nEnter ID of an employee whose record is to be searched: ";
                id = getValidInt("the ID to search"); // Get valid integer input for ID

                file.open(fileName, ios::in | ios::binary);
                file.seekg(0, ios::beg);

                while (file.read((char*)&e, sizeof(e))) {
                    if (e.getID() == id) {
                        cout << "\n\nThe record found....." << endl;
                        cout.setf(ios::left, ios::adjustfield);

                        printHeader();
                        e.showdata();
                        cout.unsetf(ios::left);
                        isFound = 1;
                        break;
                    }

                }

                if (isFound == 0)
                    cout << endl << "Data not found for employee having id '" << id <<"'"<< endl;
                file.close();
                break;
            case 3:
                isFound = 0;
                cout << "\nEnter department name to list employee within it: ";
                cin.ignore(); // Clear newline left in the buffer
                cin.getline(Dept, 50);
                file.open(fileName, ios::in | ios::binary);
                file.seekg(0, ios::beg);
                Employee employees[1000]; // Fixed-size array to store employees
                counter = 0;
                while (file.read((char*)&e, sizeof(e))) {
                    if (strcmp(e.getdepartment(), Dept) == 0) 
					{
                        if (isFound == 0) 
						{
                            // Print headers only once
                            cout << "\nThe records found for department \"" << Dept << "\":" << endl;
                            cout.setf(ios::left, ios::adjustfield);

                            printHeader();
                        }
                        employees[counter++] = e; // Add each employee to the array
                        isFound = 1;
                    }
                }
                // Sort the employees by EmpID
                sortEmployeesById(employees, counter);
                for (int i = 0; i < counter; i++) 
				{
                    employees[i].showdata();
                }
                cout.unsetf(ios::left);
                if (isFound == 0) 
				{
                    cout << "\nData Not Found for \"" << Dept << "\" department\n" << endl;
                }
                else
                {
                	cout<<endl<<counter<<" records found for \""<<Dept<<"\" department .....\n"<<endl;
				}
                file.close();
                break;
            case 4:
                file.open(fileName, ios::in | ios::binary);
                if (!file) 
				{
                    cout << "No records found" << endl;
                    break;
                }
                else
                cout << "\nRecords of employee:" << endl;
                
                file.seekg(0, ios::beg);

                Employee empl[1000]; // Fixed-size array to store employees
                counter = 0;

                while (file.read((char*)&e, sizeof(e))) 
				{
                    empl[counter++] = e; // Add each employee to the array
                }

                // Sort the employees by EmpID
                sortEmployeesById(empl, counter);

               //Display all the records in ascending order of EmpID
			    for (int i = 0; i < counter; i++) 
				{
					//print headers only once
                    if (i == 0) 
					{
                        cout.setf(ios::left, ios::adjustfield);
                        printHeader();
                    }
                    empl[i].showdata();
                }
                cout.unsetf(ios::left);

                cout << endl << counter << " records found....\n" << endl;
                file.close();
                break;
            
            case 5:
                recordNo = 0;
                cout << endl << "Enter Employee ID whose record is to be modified:";
                id=getValidInt("the ID to be modified");

                isFound = 0;
                file.open(fileName, ios::in | ios::out | ios::binary);

                while (file.read((char*)&e, sizeof(e))) {
                    recordNo++;
                    if (e.getID() == id) {
                        cout << "\nThe old record of employee having ID '" << id << "' is:" << endl;
                        cout.setf(ios::left, ios::adjustfield);
                        printHeader();
                        e.showdata();
                        cout.unsetf(ios::left);

                        isFound = 1;
                        break;
                    }
                    
                }
                if (isFound == 0) {
                    cout << "\nData Not Found for employee having ID '" << id <<"'"<< endl;
                    file.close();
                    break;
                }
                isFound = 0;
                location = (recordNo - 1) * sizeof(e);
                file.clear();
                file.seekg(0, ios::beg);
                cout << "\nEnter new record for employee having ID '" << id<<"':" << endl;
                e.getdata();
                file.read((char*)&tem, sizeof(tem));
                while (file.read((char*)&tem, sizeof(tem))) {
                    if (e.getID() == tem.getID() && tem.getID() != id) { // Validate that the new ID does not already exist (except for the current record)
                        cout << "\n\n!!!  Unable to modify the record  !!!";
                        cout << "\nThis ID already exists... Try for another ID\n" << endl;
                        isFound = 1;
                        break;
                    }
                }
                if (isFound == 0) {
                    // Write the new record in place of the old record
                    file.clear();
                    file.seekp(location, ios::beg);
                    file.write((char*)&e, sizeof(e));
                    cout << "\n\nRecord has been modified successfully.....\n" << endl;
                }
                file.close();
                break;
            case 6:
                isFound = 0;
                cout << "\nEnter ID of employee whose record is to be deleted: ";
                id = getValidInt("the ID for the deletion of record"); // Get valid integer input for ID
                file.open(fileName, ios::in | ios::binary);
                file.seekg(0, ios::beg);

                while (file.read((char*)&e, sizeof(e))) {
                    recordNo++;
                    if (e.getID() == id) {
                        cout << "\nThe old record of employee having ID '" << id << "' is:" << endl;
                        cout.setf(ios::left, ios::adjustfield);
                        printHeader();
                        e.showdata();
                        cout.unsetf(ios::left);
                        isFound = 1;
                        break;
                    }
                }

                temp.open(tempFile, ios::out | ios::binary);
                if (isFound == 0) {
                    file.clear();
                    temp.clear();
                    temp.close();
                    file.close();
                    cout << endl << "Data Not Found for Employee ID '" << id <<"'\n"<< endl;
                    break;
                } 
				else 
				{
                    file.clear();
                    file.seekg(0, ios::beg);
                    file.read((char*)&e, sizeof(e));
                    while (!file.eof()) {
                        if (e.getID() != id) {
                            temp.write((char*)&e, sizeof(e));
                        }
                        file.read((char*)&e, sizeof(e));
                    }
                    temp.close();
                    file.close();
                    remove(fileName);
                    rename(tempFile, fileName);
                    cout << endl << "Record of Employee having ID '" << id << "' deleted successfully....\n" << endl;
                }
                break;
            case 7:
                cout << "\n\nExiting......Thank you for using Employee Management System"<<endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice, please try again.\n" << endl;
        }
    }

    return 0;
}

