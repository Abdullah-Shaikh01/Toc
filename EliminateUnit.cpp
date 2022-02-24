#include<bits/stdc++.h>
using namespace std;

bool  isPresent(string s, string sub) {
    int found = 0;
    while(s.find(sub, found) != string::npos) {
        found = s.find(sub, found);
        if( (found == 0 || s[found-1] == '/') && (found + sub.size() == s.size() || s[found + sub.size()] == '/') ) 
            return true; 
        found++;
    }
    return false;
}

int main() {
    string str[10];
    cout<<"Enter the productions:\n  Use \"->\" for production \n  Use \"/\" for OR Example A->A*B/a \n  Use \'^\' for null \n  And press 0 to exit"<<endl;
    int i=0;
    // do {
    //     getline(cin,str[i]);
    //     i++;
    // }while(str[i-1] != "0");
    // i -= 2;
            
            //hardcoded values
            str[0] = "S->TFa/Fa";
            str[1] = "T->Ta/^";
            str[2] = "F->Q/QF";
            str[3] = "Q->a/^";
            i=3;
    
    int temp =i;
    cout<<"eliminating null production..."<<endl;

    //find nullable variables
    vector<char> nullable_variables; 
    int null_index = 0;
    for(; i>=0;i--) {
        string production = str[i];
        cout<<"string "<<i<< " is"<<production<<endl;
        //int inputSize = str[i].size();
        for(int j=0; j<production.size(); j++ ) {
            if(production[j] == '^') {
                cout<<"found "<<production[j]<<endl;
                nullable_variables.push_back(production[0]);
                cout<<"variable "<<null_index+1<<" = "<<nullable_variables[null_index]<<endl;
                //remove null
                str[i].erase(str[i].begin()+j);
                str[i].erase(str[i].begin()+(j-1));
            }
        }
    }

    i = temp;
    for(int j=0; i>=0;i--) { 
        string production = str[i];
        if(str[i][0] != nullable_variables[j]) {
            for(char c: nullable_variables) {
                string s(1, c);
                if(isPresent(production.substr(3), s)) {
                    nullable_variables.push_back(production[0]);
                }
            }
        }
        j++;
    }
    cout<<"Null variables are: ";
    for(int i=0; i<nullable_variables.size(); i++) {
        cout<<nullable_variables[i]<<" ";
    }
    
    //before inserting a production call a function which checks if it is already present or not 
    //use str.find("string") function and some logic from unit production
    for(i = temp; i >= 0; i-- ) {
        string production = str[i];
        cout<<"\nProduction "<<i<< " is"<<production<<endl;
        // int productionSize = production.size();
        for(int j=0; j<nullable_variables.size(); j++) {
            cout << "variable  = " << nullable_variables[j] << endl;
            for(int i = 3; i<production.size(); i++) {
                cout << "i = " << i << " char = " << production[i] << endl;
                if( production[i] == nullable_variables[j] ) {
                    cout << "Character is = " << production[i] << endl;
                    int pos = i;
                    
                    cout << "Pos = " << pos <<endl;
                    int left = pos-1, right = pos+1;
                    while(production[left] != '>' && production[left] != '/')
                        left--;
                    while(right != production.size() && production[right] != '/')
                        right++;
                    if ( right - left > 2) {
                        cout << "Left = " << left << "Right = " << right << endl;
                        cout << "production = " << production << endl;
                        string sub = production.substr(left+1, right-left-1);
                        cout << "Sub = " << sub << endl;
                        sub.erase(sub.begin() + (pos-left-1));
                        cout << "Sub = " << sub << endl;
                        // Check here whether the duplicate is present
                        if(!isPresent(production.substr(3), sub)) {
                            sub = "/" + sub; 
                            production.insert(right, sub);
                            j = 0;
                            cout << "production = " << production << endl;
                        }
                        cout << "Already present" << endl;
                    }
                }
            }
        }
        str[i] = production;
    }
    cout<<"\n\n\nAfter removing null productions"<<endl;
    cout<<endl;
    for(int i=0;i<=temp;i++)
        cout<<str[i]<<endl;
    i = temp;
    cout<<"eliminating unit production..."<<endl;
    for(; i>=0;i--) {
        string production = str[i];
        cout<<"string "<<i<< " is"<<production<<endl;
        // int inputSize = str[i].size();
        for(int j=0; j<production.size(); j++ ) {
            if(production[j] == '>' || production[j] == '/') {
                // cout<<"found "<<production[j]<<endl;
                if(j+2 == production.size() || production[j+2] == '/') {
                    // cout<<"found one "<<endl;
                    if(isupper(production[j+1])) { //use is Upper
                        // cout<<"found upper "<<production[j+1]<<endl;
                        if (production[0] == production[j+1]) { //if recursion then ignore
                            cout<<"found "<<production[j+1]<<endl;
                            if(j+2 == production.size() )
                                production.erase(j);
                            else if( j == 3) 
                                production.erase(j+1, 2);
                            else 
                                production.erase(j, 3);
                                cout<<"string "<<i<< " is"<<production<<endl;
                        }
                        else {
                            int k= temp;
                            while(str[k][0] != production[j+1]) 
                                k--;
                            
                            cout<<"found "<<str[k][0]<<endl;
                            
                            production.replace(j+1,1,str[k],3); //replace unit with its production
                            cout<<"string "<<i<< " is"<<production<<endl;
                        }
                    }
                }
                cout<<"j = "<<j<<"size = "<<production.size()<<endl;
            }
        }
        str[i] = production;
    }    
    cout<<"\n\n\nAfter removing unit productions"<<endl;
    cout<<endl;
    for(int i=0;i<=temp;i++)
        cout<<str[i]<<endl;
    return 0;
}