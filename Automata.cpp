#include<iostream>
using namespace std;
bool isValid(string str) {
	int length = str.length();
	if(length<3)		return false;
	cout<<"q0";
	for(int i=0; i<length-3; i++) {
		if(str[i] != 'a' && str[i] != 'b') {
			cout<<endl<<str[i]<<" does not belong to the regular expression"<<endl;
			return false;		}
		cout<<"--"<<str[i]<<"--q0";		}
	if(str[length-3] == 'b' && str[length-2] == 'a' && str[length-1] == 'b') {
		cout<<"q0--b--q1--a--q2--b--q3"<<endl;
		cout<<"q3 is accepting state"<<endl;
		return true;
	}
	else
		cout<<"\nThe string does not ends with bab"<<endl;
	return false;
}
int main() {
	string input;
	cout<<"Enter the string for regular expression (a+b)*bab : ";
	cin>>input;
	if(isValid(input)) 
		cout<<"The expression is valid"<<endl;
	else
		cout<<"The expression is invalid"<<endl;
	return 0;
}
