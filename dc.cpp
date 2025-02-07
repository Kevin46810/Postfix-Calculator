//My code
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "stack.h"

void PrintMenu();
void PrintTop(Stack<int> &stack);
void DeleteTop(Stack<int> &stack);
void PrintStack(Stack<int> &stack);
void ClearStack(Stack<int> &stack);
void DuplicateTop(Stack<int> &stack);
void ReverseOrder(Stack<int> &stack);
void Add(Stack<int> &stack);
void Subtract(Stack<int> &stack);
void Multiply(Stack<int> &stack);
void Divide(Stack<int> &stack);
void Remainder(Stack<int> &stack);
void ConvertNegative(Stack<int> &stack, string &array, int &i);
void ConvertToInt(Stack<int> &stack, string &array, int &i);

const int MAX_CAPACITY = 100;

int main() {

	//Declare variables
	string calc;
	Stack<int> stack(MAX_CAPACITY);
	PrintMenu(); //Provides input options for the user, not including integers or operators

	cout << "Enter your input below (CTRL-D to stop input).  Max capacity is " << MAX_CAPACITY << "." << endl;

	do {
		try {
			getline(cin, calc); //Takes user input and accepts white spaces as part of the string

			//Loops through and reads the inputted string to determine what to execute
			for (int i = 0; i < calc.length(); i++) {
				if (isdigit(calc[i])) { //if character is an int
					ConvertToInt(stack, calc, i);

					//i index refers to the item after the integer's last digit. 
					//The for loop increments i a second time after the iteration ends, thus skipping the non-int.
					//Decrementing i fixes this issue 
					i--;
				}
				else { //Reads through non-integer characters to determine proper execution
					switch(toupper(calc[i])) {
					case 'P' : PrintTop(stack); break; //Prints top item in stack
					case 'N' : DeleteTop(stack); break; //Prints top item in stack and deletes it
					case 'F' : PrintStack(stack); break; //Prints all items in stack line-by-line
					case 'C' : ClearStack(stack); break; //Deletes all items in stack
					case 'D' : DuplicateTop(stack); break; //Duplicates the top item and pushes the duplicate into the stack
					case 'R' : ReverseOrder(stack); break; //Switches the order of the top two items
					case '+' : Add(stack); break; //Pops the top two items, adds them together, and pushes their sum
					case '-' : Subtract(stack); break; //Pops the top two items, subtracts them (2nd topmost - topmost, and pushes their difference
					case '*' : Multiply(stack); break; //Pops the top two items, multiplies them together, and pushes the product
					case '/' : Divide(stack); break; //Pops the top two items, divides them together (2nd topmost / topmost), and pushes their quotient
					//Pops the top two items, divides them together (2nd topmost % topmost), and pushes their remainder
					//If the dividend is less than the divisor, it pushes the dividend
					case '%' : Remainder(stack); break; 

					case '_' : ConvertNegative(stack, calc, i); break; //Converts integer in front of the _ to its negative
					case ' ' : break; //No operation for white spaces
					default  : cout << "Invalid input." << endl; //Informs the user if they've entered an unknown input
					}
				}
			}
		}
		//Catch statements get executed if there's an error in the stack
		//Program continues to run
		catch (DataError e) { 
			cout << "Invalid input." << endl;
		}
		catch (Underflow e) { 
			cout << "Stack empty." << endl;
		}
		catch (Overflow e) {
			cout << "Stack full." << endl;
		}
		catch (DivisionByZero e) {
			cout << "Division by zero error. Stack unchanged." << endl;
		}
	}

	while (cin);
	cout << "End of program." << endl;
}

void PrintMenu() {

	cout << "\n     Letter Commands         " << endl;
	cout << "-------------------------------" << endl;
	cout << "    p - print top" << endl;
	cout << "    n - delete top" << endl;
	cout << "    f - print stack" << endl;
	cout << "    c - clear stack" << endl;
	cout << "    d - duplicate top" << endl;
	cout << "    r - reverse order" << endl;
	cout << "-------------------------------\n" << endl;
}

void PrintTop (Stack<int> &stack) {

	cout << stack.top() << endl;
}

void DeleteTop(Stack<int> &stack) {

	try {
		cout << stack.top();//Prints top before deleting
		stack.pop();
	}
	catch (Underflow e) {
		cout << "No top to pop." << endl;
	}
}
void PrintStack(Stack<int> &stack) {

	Stack<int> temp = stack;

	while (!temp.isEmpty()) { //Copy of stack pops until all items have been printed
		cout << temp.top() << endl;
		temp.pop();
	}

}

void ClearStack (Stack<int> &stack) {

	try {
		stack.makeEmpty();
	}
	catch (Underflow e) {
		cout << "Stack already empty." << endl;
	}
}

void DuplicateTop (Stack<int> &stack) {

	try {
		stack.push(stack.top());
	}
	catch (Underflow e) {
		cout << "Stack empty." << endl;
	}
}

void ReverseOrder (Stack<int> &stack) {

	try {

		int temp1 = stack.top();
		stack.pop();
		int temp2 = stack.top();
		stack.pop();
		stack.push(temp1);
		stack.push(temp2);
	}

	catch (Underflow e) { //Thrown when trying to reverse 0 or 1 items
		cout << "Illegal pop. Stack now empty." << endl;
	}
}
void Add(Stack<int> &stack) {

	try {
		int num1 = stack.top();
		stack.pop();
		int num2 = stack.top();
		stack.pop();
		stack.push(num2 + num1);
	}

	catch (Underflow e) { //Thrown when postfix expression is invalid
		cout << "Illegal pop. Stack now empty." << endl;
	} 
}

void Subtract(Stack<int> &stack) {

	try {
		int num1 = stack.top();
		stack.pop();
		int num2 = stack.top();
		stack.pop();

		stack.push(num2 - num1);
	}

	catch (Underflow e) { //Thrown when postfix expression is invalid
		cout << "Illegal pop. Stack now empty." << endl;
	}
}

void Multiply(Stack<int> &stack) {

	try {
		int num1 = stack.top();
		stack.pop();
		int num2 = stack.top();
		stack.pop();

		stack.push(num2 * num1);
	}

	catch (Underflow e) { //Thrown when postfix expression is invalid
		cout << "Illegal pop. Stack now empty." << endl;
	}
}

void Divide(Stack<int> &stack) {

	try {
		int num1 = stack.top();
		stack.pop();
		int num2 = stack.top();
		stack.pop();

		if (num1 == 0) { //Revert stack to as before and do not divide if divisor is 0
			stack.push(num2);
			stack.push(num1);
			throw DivisionByZero();
		}

		stack.push(num2 / num1);

	}
	catch (Underflow e) { //Thrown when postfix expression is invalid
		cout << "Illegal pop. Stack now empty." << endl;
	}

	catch (DivisionByZero e) {
		cout << "Division by zero error. Stack unchanged." << endl;
	}
}

void Remainder(Stack<int> &stack) {

	try {
		int num1 = stack.top();
		stack.pop();
		int num2 = stack.top();
		stack.pop();

		if (num1 == 0) { //Revert stack to as before and do not divide if divisor is 0
			stack.push(num2);
			stack.push(num1);
			throw DivisionByZero();
		}

		stack.push(num2 % num1);

	}
	catch (Underflow e) { //Thrown when postfix expression is invalid
		cout << "Illegal pop. Stack now empty." << endl;
	} 
	catch (DivisionByZero e) {
		cout << "Division by zero error. Stack unchanged." << endl;
	}
}

void ConvertNegative(Stack<int> &stack, string &array, int &i) {

	string num;

	if (!isdigit(array[i+1]) || array.length() < 2) { //Restarts input if '_' is not in front of an integer
		i = array.length();
		cout << "Your '_' is not in front of an integer.  Please try again." << endl;
		return;
	}
	for (int j = i + 1; isdigit(array[j]); j++) {
		num += array[j]; //Append the string if it's a multi-digit integer
		i++; //Increment the index in the main for-loop
	}

	int newNum = atoi(num.c_str()); //Convert char array to int
	newNum = newNum - (newNum * 2); //Make int its negative version
	stack.push(newNum); 

}

void ConvertToInt(Stack<int> &stack, string &array, int &i) {

	string num;

	for (int j = i; isdigit(array[j]); j++) {
		num += array[j]; //Append the string if it's a multi-digit integer 
		i++; //Increment the index in the main for-loop
	}

	int newNum = atoi(num.c_str()); //Convert char array to int
	stack.push(newNum);


}
