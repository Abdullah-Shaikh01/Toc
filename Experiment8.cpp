#include<iostream>
#include<vector>

using namespace std;

int main() {
    cout<<"Turing machine that accepts palindrome\n\tstring should contain a and b only \n\tnull is denoted by 0"<<endl;
    string tape;
    cout<<"Enter the string: ";
    cin>>tape;
    tape = "0" + tape + "0";

    int head =0;
    int state = 0;
    cout << "Tape: " << tape <<endl;
    cout << "state = " << state << " head = " << head << endl << endl;
    while(state != -1 && state != 7) {
        if(state == 0) {
            head++;
            state = 1;
        }
        else if(state == 1) {
            if(tape[head] == 'a') {
                tape[head] = '0';
                head++;
                state = 2;
            }
            else if(tape[head] == 'b') {
                tape[head] = '0';
                head++;
                state = 4;
            }
            else {
                state = 7;
            }
        }
        else if(state == 2) {
            while(tape[head] != '0')
                head++;
            state = 3;
            head--;
        }
        else if(state == 4) {
            while(tape[head] != '0')
                head++;
            state = 5;
            head--;
        }
        else if(state == 3) {
            if(tape[head] == 'a') {
                tape[head] = '0';
                head--;
                state = 6;
            }
            else if(tape[head] == 'b') {
                state = -1;
            }
            else {
                state = 7;
            }
        }
        else if(state == 5) {
            if(tape[head] == 'b') {
                tape[head] = '0';
                head--;
                state = 6;
            }
            else if(tape[head] == 'a') {
                state = -1;
            }
            else {
                state = 7;
            }
        }
        else {
            while(tape[head] != '0')
                head--;
            state = 1;
            head++;
        }
        cout << "Tape: " << tape <<endl;
        cout << "state = " << state << " head = " << head << endl << endl;
    }
    if(state == 7) 
        cout << "The string is palindrome";
    else 
        cout << "The string is not palindrome";
    return 0;
}