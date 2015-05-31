// Class: CSE 330
// Term: Spring 2015
// Instructor: George M. Georgiou
// Name(s): Aaron Chamberlain & Richard Morones
// Lab 3
// Title:: Infix to postfix expression converstion

#include<iostream>
#include<stack>
#include<string>
 
using namespace std;
 
// Function to convert Infix expression to postfix 
string infix_postfix(string expression);
 
// Function to verify whether an operator has higher precedence over other
bool check_precedence(char operator1, char operator2);
 
// Function to verify whether a character is operator symbol or not. 
bool is_operator(char c);
 
// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not. 
bool is_operand(char c);
 
int main() 
{
	string expression; 
	cout<<"Enter Expression \n";
	getline(cin,expression);
	string postfix = infix_postfix(expression);
	cout<<"Output = "<<postfix<<"\n";
}
 
// Function to evaluate Postfix expression and return output
string infix_postfix(string expression)
{
	// Declaring a Stack from Standard template library in C++.
	stack<char> s;
	string postfix = ""; // Initialize postfix as empty string.
	for(int i = 0;i< expression.length();i++) {
 
		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		if(is_operator(expression[i])) 
		{
			while(!s.empty() && s.top() != '(' && check_precedence(s.top(),expression[i]))
			{
				postfix+= s.top();
				s.pop();
			}
			s.push(expression[i]);
		}
		// Else if character is an operand
		else if(is_operand(expression[i]))
		{
			postfix +=expression[i];
		}
 
		else if (expression[i] == '(') 
		{
			s.push(expression[i]);
		}
 
		else if(expression[i] == ')') 
		{
			while(!s.empty() && s.top() !=  '(') {
				postfix += s.top();
				s.pop();
			}
			s.pop();
		}
		}

	while(!s.empty()) {
		postfix += s.top();
		s.pop();
 
	
	}
 
	return postfix;
}
	

	
// Function to verify whether a character is english letter or numeric digit. 
// We are assuming in this solution that operand will be a single character
bool is_operand(char C) 
{
	if(C == '+') return false;
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}
 
// Function to verify whether a character is operator symbol or not. 
bool is_operator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/')
		return true;
	else
		return false;
}
 
// Function to get weight of an operator. An operator with higher weight will have higher precedence. 
int precedence(char op)
{
	int p; 
	switch(op)
	{
	case '+':
	case '-':
		p = 2;
	case '*':
	case '/':
		p = 3;
	case '(':
		p = 1;
	}
	return p;
}
 
// Function to perform an operation and return output. 
bool check_precedence(char op1, char op2)
{
	int op1Weight = precedence(op1);
	int op2Weight = precedence(op2);
 
	// If operators have equal precedence, return true if they are left associative. 
	// return false, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	if(op1Weight == op2Weight)
	{
		return true;
	}
	if (op1Weight > op2Weight){
		return true;
	}
	else return false;
}