#include<bits/stdc++.h>
using namespace std;

int mealy(string str) {
    int count= 0;
    int state = 1;
    string output = "    ";
    string st_output = "q1";
    for(int i=0; i<str.size(); i++) {
        if(state == 1) {
            if(str[i] == 'a') {
                state = 2;
                output+="0";
                } 
            else {
                output+="0";
                state=1;
            }
        }
        else if(state == 2) {
            if(str[i] == 'b') {
                    output+="0";
                    state = 3;
            }
            else {
                output+="0";
                state = 2;
            }
        }
        else if(state == 3) {
            if(str[i] == 'b') {
                output+="1";
                state = 4;
                count++;
            }
            else {
                output+="0";
                state =2;
            }
        }
        else {
            if(str[i] == 'a') {
                state=2;
                output+="0";
            }
            else {
                state=1;
                output+="0";
            }
        }  
        output += "      ";
        st_output += "--";
        st_output += str[i];
        st_output +=  "--q" + to_string(state);
    } 
    cout<<"The input states are: "<<st_output<<endl;
    cout<<"\nThe output string is: "<<output<<endl;

    return count;

}

int main() {
    string str;
    cout<<"Enter the string to count occurence of 'abb': ";
    cin>> str;
    int count = mealy(str);
    cout<<"Number of occurences of 'abb' is: "<<count<<endl;
    if(count == 0)
        cout<<"String rejected"<<endl;
    else
        cout<<"String accepted";
    return 0;
}