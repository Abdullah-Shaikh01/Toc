#include<bits/stdc++.h>
using namespace std;

// Returns true if all the characters in s are nullable variables
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

// Returns true if the production option is already present in the prodcution
bool isPresent(string s, string sub) {
    int found = 0;
    while(s.find(sub, found) != string::npos) {
        found = s.find(sub, found);
        if( (found == 0 || s[found-1] == '|') && (found + sub.size() == s.size() || s[found + sub.size()] == '|') ) 
            return true; 
        found++;
    }
    return false;
}

void EliminateNUll(vector<string> &str) {
    cout<<"\nEliminating null productions..."<<endl;

    // find nullable variables
    vector<char> nullable_variables; 
    nullable_variables.push_back('^');
    bool changed = true;

    while(changed) {
        changed = false;
        // loop over each production 
        for(int i=str.size()-1; i>=0; i--) {
            string production = str[i];
            // from each production start with third character (RHS starts here)
            for(int k=3; k<production.size(); ) {
                // point right to the next '|' 
                int right = production.find('|', k);

                // if there are no '/' remaining point right to the end of production
                if(right == -1)
                    right = production.size();
                
                // if all variables in that prodcution part are in nullable variables vector    
                if(allNull(production.substr(k, right-k), nullable_variables)) {
                    // Take the variable from LHS and convert to string so that its easy to check
                    string s(1, production[0]);
                    // vector<int>::iterator it = find(v1.begin(), v1.end(), element);
                    if(!allNull(s, nullable_variables)) {
                        nullable_variables.push_back(production[0]);
                        
                        // Remove '^' from the production
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
            str[i] = production;
        }
    }

    // Remove '^' from the nullable variables vector
    nullable_variables.erase(nullable_variables.begin());
    cout<< "\tNullable variables are: " ;
    for(char c: nullable_variables)
        cout << c << " ";

    for(int i=0; i<str.size(); i++) {
        string production = str[i];
        // For each character in production
        for(int i = 3; i<production.size(); i++) {
            for(int j=0; j<nullable_variables.size(); j++) {
                // Check wether the current vector is null variable
                if( production[i] == nullable_variables[j] ) {
                    // Left will point to the left of the partial production and right to its right
                    int left = i-1, right = i+1;
                    while(production[left] != '>' && production[left] != '|')
                        left--;
                    while(right != production.size() && production[right] != '|')
                        right++;

                    // If it's more than one alphabet (beacuse if its one we don't need to do anything)
                    if ( right - left > 2) {
                        // Take that partial production
                        string sub = production.substr(left+1, right-left-1);
                        // Remove the current character(null variable) to which i was pointing 
                        sub.erase(sub.begin() + (i-left-1));
                        // Check here whether the sub is already present
                        if(!isPresent(production.substr(3), sub)) {
                            sub = "|" + sub; 
                            // Insert to the right of partial production
                            production.insert(right, sub);
                        }
                    }
                }
            }
        }
        str[i] = production;
    }
    cout<<"\n\nAfter removing null productions"<<endl;
    for(int j=0; j<str.size(); j++)
        cout<<str[j]<<endl;
}

int main() {
    vector<string> productions;
    
    cout<<"Enter the productions:\n  Use '->' for production \n  Use '|' for OR Example A->A*B|a \n  Use '^' for null \n  And press 0 to exit"<<endl;
    while(1) {
        string str;
        getline(cin,str);
        if(str == "0") 
            break;
        productions.push_back(str);
    }
    
    // productions.push_back("S->TFa|Fa");
    // productions.push_back("T->Ta|^");
    // productions.push_back("F->Q|QF");
    // productions.push_back("Q->a|^");

    // productions.push_back("S->ABCd");
    // productions.push_back("A->BC");
    // productions.push_back("B->bB|^");
    // productions.push_back("C->cC|^");

    // productions.push_back("S->AB");
    // productions.push_back("A->aAA|^");
    // productions.push_back("B->bBB|^");
		
    // productions.push_back("S->a|Ab|aBa");
    // productions.push_back("A->b|^");
    // productions.push_back("B->b|A");
    EliminateNUll(productions);
    return 0;
}