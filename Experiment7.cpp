#include<iostream>
#include<vector>

using namespace std;

int main() {
    cout << "Pushdown for accepting a string with more number of a's than b" << endl;
    string input;
    cout << "Enter the string containing 'a' and 'b' only: ";
    cin >> input;
    vector<char> stack;
    stack.push_back('z');
    int top =0;
    while(!input.empty()) {
        cout << "Stack contents(down to top) : ";
        for(char c: stack)
            cout << c << " ";
        if(stack[top] == 'z') {
            stack.push_back(input.front());
            top++;
        }
        else if(stack[top] == 'a') {
            if(input.front() == 'a') {
                stack.push_back(input.front());
                top++;
            }
            else {
                stack.pop_back();
                top--;
            }
        }
        else if(stack[top] == 'b') {
            if(input.front() == 'b') {
                stack.push_back(input.front());
                top++;
            }
            else {
                stack.pop_back();
                top--;
            }
        }
        input.erase(input.begin());
        cout << "\n\nString : " << input << endl;
    }
    if(stack[top] == 'a')
        cout << "\nString is accpeted\n";
    else   
        cout << "\nString is not accpeted\n";
    return 0;
}