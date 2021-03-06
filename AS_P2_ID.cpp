/*
	==================================================
	DBS Project Milestone 2:
	==================================================
	Name:       Bhavikkumar Hemantbhai Mistry
	mail:       bhmistry@myseneca.ca
	student id: 128788213
	section:    ZBB
*/

#define _CRT_SECURE_NO_WARNINGS// it is a preprocessor definition added when we don't want compiler to suggest secure versions of library functions

// Header Files
#include <iostream>  // it stands for input/output stream and contain defintions of object like cin, cout and etc
#include <occi.h> // it is the header defined by programmer that contain declaration of function needed for this code
using oracle::occi::Environment;// it says that this code is using oracle occi Environment
using oracle::occi::Connection;// it means that Oracle connection is being used in this progam
using namespace oracle::occi;// it states that everything in this code is within oracle::occi namespace
using namespace std;// std stands for standard, it means all the things in this code is within std namespace

// Definition of function getInt
int getint(const char* valid = nullptr)
{
	int choice, occurence;// two integer type variables choice and occurence are declared

	// if statement is declared here if not valid then do nothing
	if (!valid)
	{
		;
	}

	// if the condition in if statement is not accepted then enter else statement
	else
	{
		cout << valid; // print data in variable valid
	}

	// do while loop is declared here
	// this loop will work unti the condition in while is valid
	do {
		occurence = 0; // value of occurence is set to zero
		cin >> choice; // value entered for choice is stored in the variable choice

		// enter if statement if cin.fail() is valid
		if (cin.fail())
		{
			cout << "Bad Integral Value, Enter again: "; // prmopt that says the entered integral value is bad, enter the value again
			cin.clear();  // calling function clear to clear the error flags
			cin.ignore(10000, '\n'); //this statement is used to skip newline and it will only skip upto 10000 characters
			occurence = 1; // value of variable occurence is changed to 1
		}

		//when the condition in if statement is not valid enter else statement
		else
		{
			char ch; // a variable ch of type character is declared
			ch = cin.get(); //value of variable nextChar is set cin.get()

			// if statement is used here which says that do nothing when ch = newline 
			if (ch == '\n')
			{
				;
			}

			// when ch is not equal to newline then enter else statement
			else
			{
				cout << "Enter only an integer: ";// prompt to enter an integer
				cin.clear();// calling function clear to clear the error flags
				cin.ignore(10000, '\n');//this statement is used to skip newline and it will only skip upto 1000 characters
				occurence = 1; // value of occurence is set to 1
			}
		}
	} while (occurence == 1);// condition for do while loop which make this loop work until condition is valid
	return choice; // it will return the value of variable choice
}

// Defintion of Function menu
int menu()
{
	// a list of things is being printed with there sequence number
	// print as given below all in newline 
	cout << "* HR Menu *" << "\n";
	cout << "1) Find Employee" << "\n";
	cout << "2) Employees Report" << "\n";
	cout << "3) Add Employee" << "\n";
	cout << "4) Update Employee" << "\n";
	cout << "5) Remove Employee" << "\n";
	cout << "0) Exit" << "\n";
	int choice = getint("Enter an choice (0-5): ");// integer type variable is declared and assigned to getInt() function and prompt is passed in it to enter an choice
	return choice; // value of variable choice is returned
}

// Employee struct it contains almost all varibles required in this code
struct Employee
{
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char officecode[10];
	int reportsTo[100];
	char jobTitle[50];
	char city[50];
	char extension[10];
};

// Defintion of function findEmployee
//This function will find the employee from the database
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp)
{
	Statement* st = nullptr; // dynamic variable "st" is declared of nature Statement and assigned to nullptr
	ResultSet* rt = nullptr; // dynamic variable "rt" is declared of nature ResultSet and assigned to nullptr
	int result; // integer type variable "result" is declared

	try //this allows to define a block of code to be tested for errors while it is being tested 
	{
		st = conn->createStatement(); // conn->createStatement() function is called by assigning its value to variable "st"

		rt = st->executeQuery // executeQuery function is called here and sql query is passed in it to display information of employee from table employees joined with table offices, on o.officecode = e.officecode, where employeenumber is the number entered by the user and saved in variable employeeNumber
		("SELECT e.employeenumber, e.lastname, e.firstname, e.email, o.phone, e.extension, e.reportsTo, e.jobTitle, o.city FROM employees e JOIN offices o ON o.officecode = e.officecode WHERE employeenumber = " + to_string(employeeNumber));

		// if statement used here, if the condition used in this statement is valid then enter if loop 
		if (rt->next())
		{
			// information of employee is copied to getInt() and getString() function in a particular sequence
			emp->employeeNumber = rt->getInt(1);
			strcpy(emp->lastName, rt->getString(2).c_str());
			strcpy(emp->firstName, rt->getString(3).c_str());
			strcpy(emp->email, rt->getString(4).c_str());
			strcpy(emp->phone, rt->getString(5).c_str());
			strcpy(emp->extension, rt->getString(6).c_str());
			*emp->reportsTo = rt->getInt(7);
			strcpy(emp->jobTitle, rt->getString(8).c_str());
			strcpy(emp->city, rt->getString(9).c_str());
			result = 1; // value of result is set to 1
		}

		// when the condition of if statement is not valid then enter else statement
		else
		{
			result = 0; // set the value of variable result to safe state that is zero
		}
		conn->terminateStatement(st); // this statement is to terminate the connection
	}
	catch (SQLException& sqlExcp)// this function get any error or message in the code and print them 
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << "\n";// calling getErrorCode() function and getMessage() function with colon between them, it will print any error or message in the output
	}
	return result;// it will return the value of result
}

//Definition of Function displayEmployee
//it will display the information
void displayEmployee(Connection* conn, struct Employee emp)
{
	cout << "\n";// to print a newline
	cout << "-------------- Employee Information -------------";// prompt heading of employee information
	cout << "\n";// print a newline
	cout << "Employee Number: " << emp.employeeNumber; // prompt employee number and print value in emp.employeeNumber
	cout << "\n"; //print a newline
	cout << "Last Name: " << emp.lastName; // prompt last name and print data in emp.lastName
	cout << "\n";//print a newline
	cout << "First Name: " << emp.firstName; // prompt first name and value in emp.firstName
	cout << "\n";//print a newline
	cout << "Email: " << emp.email; // prompt email and print the value in emp.email
	cout << "\n";//print a newline
	cout << "Phone:" << emp.phone; // prompt phone and print value in emp.phone
	cout << "\n";//print a newline
	cout << "Extension: " << emp.extension; // prompt extension and print value in emp.extension
	cout << "\n";//print a newline
	cout << "ReportsTo: " << *emp.reportsTo;//prompt reportsto and print the value in emp.reportsto
	cout << "\n";//print a newline
	cout << "Job Title: " << emp.jobTitle;// prompt Job Title and print value in emp.jobTitle
	cout << "\n";//print a newline
	cout << "City: " << emp.city; // prompt city and print value in emp.city
	cout << "\n";//print a newline
	cout << "\n";//print a newline
}

//Definition of displayAllEmployees
void displayAllEmployees(Connection* conn)
{
	Statement* st = nullptr;// dynamic variable "st" is declared of nature Statement and assigned to nullptr
	ResultSet* rt = nullptr;// dynamic variable "rt" is declared of nature ResultSet and assigned to nullptr

	try //this allows to define a block of code to be tested for errors while it is being tested
	{
		st = conn->createStatement();// conn->createStatement() function is called by assigning its value to variable "st"

		rt = st->executeQuery //executeQuery function is called here and sql query is passed in it to display information of employee from table employees joined with table offices, on o.officecode = e.officecode, where employeenumber is the number entered by the 
		("SELECT employees.employeenumber, employees.firstname ||''|| employees.lastname, employees.email, offices.phone, employees.extension, manager.firstname||''||manager.lastname FROM employees JOIN offices ON offices.officecode = employees.officecode LEFT JOIN employees manager ON manager.employeenumber = employees.reportsto ORDER BY employees.employeenumber");
		// sql query to display information of employee with space in firstname and lastname of employees as well as manager from the table employees joined with table offices and office.officecode = employees.officecode. Also left joined with employess manager where manager.employeenumber = employee.reportsto. Result is oredered by employees.employeenumber
		cout << "\n";// print a newline

		// header to display information of all employees
		cout << "--------------------------------------------------------------------------------------------------------------";
		cout << "\n";
		cout << "E        Employee Name      Email                              Phone             Ext          Manager ";
		cout << "\n";
		cout << "--------------------------------------------------------------------------------------------------------------";
		cout << "\n";

		// enter if the rt->next() function is called
		if (rt->next())
		{
			// do while loop will work unti the condition is valid
			do
			{
				// display all information in proper pattern, sequence, and alignment
				cout.setf(ios::left);// assign left
				cout.width(9); //width is 9
				cout << rt->getInt(1);
				cout.width(19);//width is 19
				cout << rt->getString(2);
				cout.width(35);//width is 35
				cout << rt->getString(3);
				cout.width(18);//width is 18
				cout << rt->getString(4);
				cout.width(13);//width is 13
				cout << rt->getString(5);
				cout.width(17);//width is 17
				cout << rt->getString(6);
				cout.unsetf(ios::left);//assign left
				cout << "\n";
			} while (rt->next());// condition of while loop
			cout << "\n"; //print a newline
		}

		// in case when if condition is not valid enter else statement
		else
		{
			cout << "There is no employees? information to be displayed." << "\n"; // promt that there no data of employees and print a new line
		}
		conn->terminateStatement(st); // this terminate the variable statement(st)
	}
	catch (SQLException& sqlExcp) // this function get any error or message in the code and print them 
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << "\n"; // calling getErrorCode() function and getMessage function with colon between them, it will print any error or message in the output
	}
}
//Definition of function insertEmployee
void insertEmployee(Connection* conn, Employee emp)
{
	int employeeNo; // intger type variable "employeeNo" is declared
	cout << "\nEmployee Number: "; // statement to enter employee number 
	cin >> employeeNo; // entered employee number will be saved in employeeNo

	// enter if statement if findEmployee function is called by passing three values in it
	if (findEmployee(conn, employeeNo, &emp))
	{
		cout << "\nAn employee with the same employee number exists.\n" << endl; // print the statement that employee number exist
	}

	// when condition in if is not valid then enter else statement
	else
	{
		Statement* st = nullptr;// dynamic variable "st" is declared of nature Statement and assigned to nullptr

		try //this allows to define a block of code to be tested for errors while it is being tested
		{
			emp.employeeNumber = employeeNo; // employee number in variable "employeeNo" is saved to "emp.employeeNumber"
			cout << "Last Name: "; // prompt to enter last name of employee
			cin >> emp.lastName;  // name entered by user will be saved in "emp.lastName"
			cout << "First Name: "; // prompt to enter first name
			cin >> emp.firstName;// name entered by user will be saved in "emp.firstName"
			cout << "Email: "; // prompt to enter email
			cin >> emp.email;  // email entered will be saved in "emp.email"
			cout << "extension: "; // prompt to enter extension
			cin >> emp.extension; //// extension entered will be saved in "emp.extension"
			cin.ignore(); // it will skip empty spaces
			cout << "Job Title: "; // prompt to enter job title
			cin.getline(emp.jobTitle, 50); // job title will be saved in "emp.jobtitle" and should be 50 characters long
			cout << "City: "; // prompt to enter city
			cin >> emp.city; //// extension entered will be saved in "emp.city"


			Statement* stmt = conn->createStatement();
			stmt->setSQL("insert into employees (employeenumber, lastname,firstname, email, extension, jobtitle, reportsto, officecode) values(:1, : 2, : 3,: 4, : 5, : 6, : 7, : 8)");
			// sql query to insert information of the user in the databasethat is in employee table
			//stmt->setSQL("insert into offices (officecode, city) values(:8, :9)");
			// sql query to insert information of the user in the databasethat is in office table

		// this statements will set the string to there approprite position in a correct sequence
			stmt->setInt(1, emp.employeeNumber);
			stmt->setString(2, emp.lastName);
			stmt->setString(3, emp.firstName);
			stmt->setString(4, emp.email);
			stmt->setString(5, emp.extension);
			stmt->setString(6, emp.jobTitle);
			stmt->setString(7, "1002");
			stmt->setString(8, "1");
			//stmt->setString(9, emp.city);
			stmt->execute();
			cout << "\nThe new employee is added successfully.\n" << endl; // prompt that the information is added successfully
			//conn->terminateStatement(st); // this terminate the variable statement(st)
		}
		catch (SQLException& sqlExcp) // this function get any error or message in the code and print them 
		{
			cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << "\n"; // calling getErrorCode() function and getMessage function with colon between them, it will print any error or message in the output
		}
	}
}

//Definition of updateEmployee
void updateEmployee(Connection* conn, int employeeNumber)
{
	Employee emp; // a variable "emp" of type Employee is declared

	// enter if statement when the findEmployee function is called with three values passed in it
	if (findEmployee(conn, employeeNumber, &emp))
	{
		Statement* st = nullptr;// dynamic variable "st" is declared of nature Statement and assigned to nullptr

		try //this allows to define a block of code to be tested for errors while it is being tested
		{
			cout << "\nNew Extension: "; // print the exact line
			cin >> emp.extension; // value entered of extension is stored in emp.extension
			Statement* stmt = conn->createStatement(); // dynamic variable "stmt" of type Statement is decalred and initiated to createStatement() function 
			stmt->setSQL("update employees set extension = :1 where employeenumber = :2");
			// sql database query is here to update employee information
			stmt->setString(1, emp.extension); // setString function is called and two values are passed in it 1 ans emp.extension
			stmt->setInt(2, employeeNumber); // setInt function is called and two values are passed 2 and employeeNumber
			stmt->execute(); // execute update function is called here
			cout << "\nThe employee is updated.\n" << endl; // the exact line will be printed with a newline
			//conn->terminateStatement(st); // this terminate the variable statement(st)
		}
		catch (SQLException& sqlExcp) // this function get any error or message in the code and print them 
		{
			cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << "\n"; // calling getErrorCode() function and getMessage function with colon between them, it will print any error or message in the output
		}
	}

}

//Definition of deleteEmployee
void deleteEmployee(Connection* conn, int employeeNumber)
{
	Employee emp; // a variable "emp" of nature Employee is declared 

	// enter if statement only if the condition is valid that is findEmployee function is called eith 3 attributes
	if (findEmployee(conn, employeeNumber, &emp))
	{
		Statement* st = nullptr;// dynamic variable "st" is declared of nature Statement and assigned to nullptr

		try //this allows to define a block of code to be tested for errors while it is being tested
		{
			Statement* stmt = conn->createStatement(); // dynamic variable stmt of nature Statement is declared 
			stmt->setSQL("delete from employees where employeenumber = :1"); // a string is assigned in setSQL fubction
			stmt->setInt(1, employeeNumber); // function setInt is called and two values are passed in that is 1 and employeenumber
			stmt->executeUpdate();  // function executeUpdate is called with no values passed in it
			cout << "\nThe employee is deleted.\n" << endl; // this will be printed as it is with a newline
			//conn->terminateStatement(st); // this terminate the variable statement(st)
		}
		catch (SQLException& sqlExcp) // this function get any error or message in the code and print them 
		{
			cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << "\n"; // calling getErrorCode() function and getMessage function with colon between them, it will print any error or message in the output
		}
	}

	// when condition is not valid then enter else statement
	else
	{
		cout << "\nThe employee does not exist.\n" << endl;// this will be printed as it is with a newline
	}
}

// Main part of the program
int main()
{
	Environment* env = nullptr;// a dynamic variable "env" is declared of type Environment and set to nullptr
	Connection* conn = nullptr;// a dynamic variable "conn" is declared of type Connection and set to nullptr
	string usr = "dbs211_221zb11"; // a string type variable "usr" is declared and initialized to "dbs211_221zb11"
	string pass = "89664512"; // a string type variable "pass" is declared and initialized to "89664512"
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c"; // another string type variable "srv" is declared and initiated to "myoracle12c.senecacollege.ca:1521/oracle12c"

	try //this allows to define a block of code to be tested for errors while it is being tested
	{
		env = Environment::createEnvironment(Environment::DEFAULT);// this statement is to create enivronment where environment is default 
		conn = env->createConnection(usr, pass, srv);// this statement is to create connection with values passed in it 
		cout << "Connection Successful!!" << endl;
		cout << "GROUP 7" << endl << "Mistry Bhavikkumar" << endl << "Patel Karmkumar" << endl << "Patel Hemanginiben" << endl;
		Employee emp{}; // an Employee type variable is declared and set to safe state
		int choice; // integer type variable choice is declared

		// this loop will work until choice is not equl to zero
		do {
			choice = menu(); // menu() function is called and it resultant value is assigned to choice

			// enter if statement only if value of choice is greater than 5 or lesser then zero
			if (choice > 5 || choice < 0)
			{
				cout << "Value entered must lie in between 0 and 5"; // prompt values should be between 0 and 5
				cout << "\n";//print a newline
				cout << "\n";// print a newline
			}
			else if (choice == 0)
			{
				cout << "Good Bye!!";
			}

			// if the value of choice is 1 enter this else if loop
			else if (choice == 1)
			{
				int eNo = getint("Please enter Employee Number to be displayed: ");
				int valAgain = findEmployee(conn, eNo, &emp); // calling function findEmployee by passing three values

				// enter if statement if valAgain is not equal to 0
				if (valAgain != 0)
				{
					displayEmployee(conn, emp);// calling function displayEmployee with three values passed in it
				}

				//if valAgain is zero then enter else statement
				else
				{
					cout << "Employee " << eNo << " does not exist.";// prompt employee soes not exist with entered employee number
					cout << "\n";//print a newline
					cout << "\n";// print a newline
				}
			}

			// if the value of choice is 2 enter this else if statement
			else if (choice == 2)
			{
				displayAllEmployees(conn); // function displayAllemployees is called by passing one value in it
			}

			else if (choice == 3)
			{
				insertEmployee(conn, emp); // function insertEmployeesis called by passing two values
			}
			else if (choice == 4)
			{
				int eNo = getint("Employee Number: "); // function getInt() is called by passing a string and assigned its value to variable "eNo"
				int valAgain = findEmployee(conn, eNo, &emp); // calling function findEmployee by passing three values

				// enter if statement if valAgain is not equal to 0
				if (valAgain != 0) {
					updateEmployee(conn, eNo);// updateEmployee function is called by passing two values conn and eNo
				}
				//if valAgain is zero then enter else statement
				else
				{
					cout << "Employee " << eNo << " does not exist.";// prompt employee soes not exist with entered employee number
					cout << "\n";//print a newline
					cout << "\n";// print a newline
				}
			}
			else if (choice == 5)
			{
				int eNo = getint("Employee Number: "); // function getInt() is called by passing a string and assigned its value to variable "eNo"
				int valAgain = findEmployee(conn, eNo, &emp); // calling function findEmployee by passing three values

				// enter if statement if valAgain is not equal to 0
				if (valAgain != 0) {
					deleteEmployee(conn, eNo);// deleteEmployee function is called by passing two values conn and eNo
				}
				//if valAgain is zero then enter else statement
				else
				{
					cout << "Employee " << eNo << " does not exist.";// prompt employee soes not exist with entered employee number
					cout << "\n";//print a newline
					cout << "\n";// print a newline
				}
			}
		} while (choice != 0);

		env->terminateConnection(conn); // this statement is to terminate the connection
		Environment::terminateEnvironment(env);// this statement will terminate environment

	}
	catch (SQLException& sqlExcp)// this function get any error or message in the code and print them too
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();// calling getErrorCode() function and getMessage function with colon between them, it will print any error or message in the output
	}
	return 0;// return zero
}