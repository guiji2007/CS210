#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210StarterPY");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210StarterPY");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210StarterPY");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


int main()
{
	int userInput;
	string groceryItem;
	string datfile = "frequency.dat";
	ifstream inFS;
	ofstream outFS;
	int itemFreq;
	
	CallProcedure("DisplayMenu");
	cin >> userInput;
	if (userInput == 1) {
		CallProcedure("PrintGrocery");
	}
	else if (userInput == 2) {
		cout << "Enter to item to check its frequency" << endl;
		cin >> groceryItem;
		cout << callIntFunc("PrintGroceryItem", groceryItem) << endl;
	}
	else if (userInput == 3) {
		CallProcedure("WriteFrequencyFile");
		

		vector<string> itemList;	// create a vector to store city name
		vector<int> frequencyList;		// create a vector to store fahrenheit temperature
		
		// open the dat file
		inFS.open("frequency.dat");

		if (!inFS.is_open()) {//test if the txt file is open or not
			cout << "Could not open file frequency.dat." << endl;
		}

		inFS >> groceryItem;	// read the city first
		inFS >> itemFreq;	// read the temperature second

		while (!inFS.fail()) { // while-loop to read through the txt file
			itemList.push_back(groceryItem);	// push_back the city to the vector
			frequencyList.push_back(itemFreq);	// push_back the temperature to the vector
			inFS >> groceryItem;	
			inFS >> itemFreq;	
		}
		inFS.close();

		// for-loop to convert the F temperature to C temperature
		// store the C temperature to store in cTmpList
		unsigned i;
		for (i = 0; i < itemList.size(); ++i) {
			cout <<itemList.at(i)<<" ";
			for (int j = 0; j < frequencyList.at(i); ++j) {
				cout << '#';
			}
			cout << endl;
		}

		outFS.close();


	return 0;


	}

	
	
	




}
