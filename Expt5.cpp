#include<bits/stdc++.h>
using namespace std;

void hello() {
    cout<<"Hello";
}

bool isPresent(string s, string sub) {
    int found = 0;
    while(s.find(sub, found) != string::npos) {
        found = s.find(sub, found);
        if( (found == 0 || s[found-1] == '/') && (found + sub.size() == s.size() || s[found + sub.size()] == '/') ) 
            return true; 
        found++;
    }
    return false;
}

bool allNull(string s, vector<char> variables) {
    bool present;
    for(char c: s) {
        present = false;
        for(char a: variables) {
            if(a==c) {
                present = true;
                break;
            }
        }
        if(!present)
            return false;
    }
    return true;
}
int takeProductions(string str[]) {
    cout<<"Enter the productions:\n  Use \"->\" for production \n  Use \"/\" for OR Example A->A*B/a \n  Use \'^\' for null \n  And press 0 to exit"<<endl;
    int i=0;
    // do {
    //     getline(cin,str[i]);
    //     i++;
    // }while(str[i-1] != "0");
    // i -= 2;
            
            //hardcoded values
            //Example 1
            // str[0] = "S->ABA";
            // str[1] = "A->aA/^";
            // str[2] = "B->bB/^";
            // i=2;

            //Example 2
            // str[0] = "S->TU/V";
            // str[1] = "T->aTb/^";
            // str[2] = "U->cU/^";
            // str[3] = "V->aVc/W";
            // str[4] = "W->bW/^";
            // i=4;

            //Example 3
            // str[0] = "S->TF/Fa/QT";
            // str[1] = "T->Ta/^";
            // str[2] = "Q->a/^";
            // str[3] = "F->QS/QFa";
            // i=3;

            //Example 4
            // str[0] = "S->ZB/AA";
            // str[1] = "A->a/SA";
            // str[2] = "B->b";
            // str[3] = "Z->a";
            // i=3;

            //Example 5
            // str[0] = "S->SS/(S)/a";
            // i=0;

            str[0] = "S->aSbS/bSaS/^";
            i=0;
            return i;
}

void EliminateNUll(string str[], int i) {
    cout<<"\nEliminating null and unit production..."<<endl;
    //find nullable variables
    vector<char> nullable_variables; 
    int temp =i;
    nullable_variables.push_back('^');
    bool changed = true;
    while(changed) {
        changed = false;
        for(int j=i; j>=0; j--) {
            string production = str[j];
            cout << "production = " << production << endl;
            for(int k=3; k<production.size(); ) {
                int right = production.find('/', k);
                if(right == -1)
                    right = production.size();
                cout << "Substirng = " << production.substr(k, right-k) << endl;
                if(allNull(production.substr(k, right-k), nullable_variables)) {
                    string s(1, production[0]);
                    if(!allNull(s, nullable_variables)) {
                        nullable_variables.push_back(production[0]);
                        cout << "Added " << production[0] << endl;;
    //remove the null
                        if(production[k] == '^') {
                            if(k == 3) 
                                production.erase(k,2);
                            else 
                                production.erase(k-1,2);
                        }
                        changed =true;
                    }
                    k=production.size();
                }
                else 
                    k = right+1;
            }
            str[j] = production;
        }
    }
    nullable_variables.erase(nullable_variables.begin());
    cout<< "\tNullable variables are: " ;
    for(char c: nullable_variables)
        cout << c << " ";


    for(i = temp; i >= 0; i-- ) {
        string production = str[i];
        for(int j=0; j<nullable_variables.size(); j++) {
            for(int i = 3; i<production.size(); i++) {
                if( production[i] == nullable_variables[j] ) {
                    int pos = i;
                    int left = pos-1, right = pos+1;
                    while(production[left] != '>' && production[left] != '/')
                        left--;
                    while(right != production.size() && production[right] != '/')
                        right++;
                    if ( right - left > 2) {
                        string sub = production.substr(left+1, right-left-1);
                        sub.erase(sub.begin() + (pos-left-1));
                        // Check here whether the duplicate is present
                        if(!isPresent(production.substr(3), sub)) {
                            sub = "/" + sub; 
                            production.insert(right, sub);
                            j = 0;
                        }
                    }
                }
            }
        }
        str[i] = production;
    }
    cout<<"\n\nAfter removing null productions"<<endl;
    for(int j=0; j<=temp; j++)
        cout<<str[j]<<endl;
}

void EliminateUnit(string str[], int i) {
    cout<<"\n\nEliminating unit production..."<<endl;
    int temp = i;
    for(; i>=0;i--) {      
        string production = str[i];
        for(int j=0; j<production.size(); j++ ) {
            if(production[j] == '>' || production[j] == '/') {
                if(j+2 == production.size() || production[j+2] == '/') {
                    if(isupper(production[j+1])) { //use is Upper
                        if (production[0] == production[j+1]) { //if recursion then ignore
                            if(j+2 == production.size() )
                                production.erase(j);
                            else if( j == 3) 
                                production.erase(j+1, 2);
                            else 
                                production.erase(j, 3);
                        }
                        else {
                            int k= temp;
                            while(str[k][0] != production[j+1]) 
                                k--;
                            production.replace(j+1,1,str[k],3); //replace unit with its production
                        }
                    }
                }
            }
        }
        str[i] = production;
    }
    cout<<"\nAfter removing null and unit productions: "<<endl;
    for(int j=0; j<=temp; j++)
        cout<<str[j]<<endl;
}

// int main() {
// //     string str[10];
// //     int i = takeProductions(str);
    
// //     EliminateNUll(str, i);
    
// //     EliminateUnit(str, i);
//     // map<char, string> newProductions;
//     // char c = 'a';
//     // string newPro;
//     // string s(1, ('X' + newProductions.size()));
//     // newPro += s + "->" + c;
//     // cout << newPro;
//     // newProductions.insert({c, newPro});
//     // cout<< newProductions['a'] << endl;
//     //                             cout<<newProductions['a'][0];
    // string s("He//l/lo");
    // string s1("abd");
    // int j=3;
    // int k=8;
    // while(s.find('/', k) != string::npos) {
    //     k = s.find('/', k);
    //     cout << "K = " << k++ << endl;
    // }
 
//     if(s.find('q') == s.size())
//     cout << "cool" << endl;
//     s.insert()
//    // s.replace(1,2, s1,0, 1);
//     string s = "Hello";
//     s = "a" + s;
//     cout<<s;
//     return 0;
// }