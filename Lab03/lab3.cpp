#include <iostream>
#include <string>
#include <stack>

using namespace std;

int prec(char c){
	int p;
	if(c == '*' || c == '/'){
		p = 3;
	}
	else if(c == '+' || c == '-'){
		p = 2;	
	}
	else if (c == '('){
		p = 1;
	}
	cout << p;
	return p;
}

void infix_postfix(string s){
	stack <char> ops;
	int str_length = 0; //used to index loop
	str_length = s.length(); //Careful: will not return expected value
				 //with multi-bit characters included
	int i = 0; //index

	//start algorithm
	while (i <= str_length){
		//if not a operator => is operand
		if (s[i] != '*' || '/' || '+' || '-' || '(' || ')'){
			cout << s[i]; //print operand
			i++; 
		} 
		else 
			if (s[i] == '('){
				ops.push(s[i]); //push operator onto stack
				i++;
			}
			else if(s[i] == ')'){
				while (!ops.empty() && ops.top() != '('){
					cout << ops.top();
					ops.pop();
				}
				if(!ops.empty()){
					ops.pop();
					i++;
				}
				else {
					cout << "\n"; 
					cout << "Error, no matching ( \n";
					i++;
				}
			}
			else if(ops.empty() || prec(ops.top())<prec(s[i])){
				ops.push(s[i]);
				i++;
			}
			else if(prec(ops.top()) >= prec(s[i])){
				while (!ops.empty() && prec(ops.top()) >= 
					prec(s[i]))
				{
					cout << ops.top();
					ops.pop();
				}
				ops.push(s[i]);
				i++;
			}
			//else check for errors
	}
	while(!ops.empty()){
		cout << ops.top();
		ops.pop();
	}
}

int main(){
	char a = '*';
	prec(a);
	cout << endl;
	string b = "a+b-c";
	infix_postfix(b);

	return 0;
}
