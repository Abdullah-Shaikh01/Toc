#include<bits/stdc++.h>
#include "header.h"
using namespace std;

int main() {
    string str[10];
    int i = takeProductions(str);
    EliminateNUll(str, i);
    EliminateUnit(str, i);

    //removing terminal symbols
    map<char, string> newProductions;
    for(int j=0; j<=i; j++) {      
        string production = str[j];
        cout << "Production = " << production << endl;
        for(int k=3; k<production.size(); k++ ) {
            //if(islower(production[k])) {
            if(!isupper(production[k]) && production[k] != '/') {
                if( (production[k-1] != '/' && production[k-1] != '>') || (k+1 != production.size() && production[k+1] != '/') ) {
                    cout << "Found terminal "<< production[k] << endl;
                    if(newProductions.find(production[k]) == newProductions.end()) {
                        string newPro;
                        string s(1, ('X' + newProductions.size()));
                        newPro += s + "->" + production[k];
                        newProductions.insert({production[k], newPro});
                        cout << newPro << endl;
                        production[k] = newPro[0];
                        auto itr = newProductions.find(production[k]);
                        str[++i] = newPro;
                    }
                    else {
                        production[k] = newProductions[production[k]][0];
                    }
                }
            }
        }
        cout << "Production = " << production << endl;
        str[j] = production;
    }

    cout<<"\nAfter removing terminal productions: "<<endl;
    for(int j=0; j<=i; j++)
        cout<<str[j]<<endl;

    //convert to CNF
    map<string, string> newP;
    for(int j=0; j<=i; j++) {      
        string production = str[j];
        int right = 4;
        for(int left=2; left<production.size(); right=left+2) {
        cout << "Production = " << production << endl;
            cout << production[right] << endl;
            while(right != production.size() && production[right] != '/') {
                cout << production[right] << endl;
                right++;
            }
            cout << "left = " << left << "right = " << right << endl;
            if (right - left > 3) {
                string key = production.substr(left+2, right-left-2);
                cout<< "key = " << key << endl;
                if (newP.find(key) == newP.end()) {
                    string s(1, ('L' + newP.size()));
                    string newPro = s + "->" + key;
                    newP.insert({key, newPro});
                    production.replace(left+2, right-left-2, newPro,0,1);
                    cout<< "newPro = " << newPro << endl;
                    i++;
                    str[i] = newPro;
                }
                else {
                    production.replace(left+2, right-left-2, newP[key],0,1);
                }
            }
            if(islower(production[left+1]))
                left--;
            left = left+3;
        }
        str[j] = production;
    }

    cout<<"\nAfter converting to CNF: "<<endl;
    for(int j=0; j<=i; j++)
        cout<<str[j]<<endl;

    //indexing Non terminals
    map<char, int> indexing;
    int index = 1;
    for(int j=0; j<=i; j++) {
        for(int k=0; k<str[j].size(); k++) {
            if(isupper(str[j][k])) {
                if (indexing.find(str[j][k]) == indexing.end()) 
                    indexing.insert({str[j][k], index++});
            }
        }
    }
    for(auto itr = indexing.begin(); itr != indexing.end(); itr++)
        cout << itr->first << " : " << itr->second << endl; 

    //Eliminating > and left recursions
    int temp = i;
    for(int j=0; j<=temp; j++) {
        string production = str[j];
        cout << "Production = " << production << endl;
        int left = indexing[production[0]];
        int ii=0;
        int k=3;
        do {
            cout << "k = " << k <<"left = " << left <<" char = "<< production[k];
            if(isupper(production[k])) {
                cout << " right = "<< indexing[production[k]]<< endl;
                while(left > indexing[production[k]]) {
                    cout << "Production = " << production << endl;
                    int temp = 0;
                    while(str[temp][0] != production[k])
                        temp++;
                    cout << "Found substitution = " << str[temp] << endl;
                    string substitute = str[temp].substr(3);
                    cout << "Found substitution = " << substitute << endl;
                    int last = k+1;
                    while(last != production.size() && production[last] != '/')
                        last++;
                    string s = production.substr(k+1, last-k-1);
                    cout << "string to be added = " << s;
                    cout << "string to be substituted = " << production.substr(k, last-k);

                    int a = substitute.find('/');
                    while(a != -1) {
                        substitute.insert(a,s);
                        a = substitute.find('/', a+s.size()+1);
                    }
                    substitute.append(s);
                    cout << "Found substitution = " << substitute << endl;
                    production.replace(k, last-k, substitute);
                    cout << "Production = " << production << endl;
                    //k += substitute.size() -2; 
                    cout << "k = " << k <<"left = " << left <<" char = "<< production[k];
                    if(islower(production[k]))
                        break;
                }
                if(!islower(production[k]) && left == indexing[production[k]]) {
                    cout << "Same Production = " << production << endl;
                    int last = k+1;
                    while(last != production.size() && production[last] != '/')
                        last++;
                    //string sub = production.substr(k, last-k);
                    string sub = production.substr(k+1, last-k);
                    if(last == production.size())
                        k--;
                    cout << "k = " << k <<"left = " << left <<" char = "<< production[k];
                    cout << "k = " << k <<"left = " << left <<" sub = "<< sub;
                    production.erase(k, last-k+1);
                    cout << "Production = " << production << endl;
                    string s(1, 'E'+ii);
                    ii++;
                    string mainSub = production.substr(3);
                    int a = mainSub.find('/');
                    while(a != -1) {
                        mainSub.insert(a,s);
                        a = mainSub.find('/', a+s.size()+1);
                    }
                    mainSub.append(s);
                    production.push_back('/');
                    production.append(mainSub);
                    cout << "Production = " << production << endl;
                    s += "->" + sub + s + "/" + sub;
                    cout<< "newPro = " << s << endl;
                    i++;
                    str[i] = s;
                }
            }
            k = production.find('/', k) + 1;
        }while(k != 0);
        cout << "j = " << j << " str[j] = " << str[j] << " pro = " << production << endl;
        str[j] = production;
    }
    
    cout<<"\nAfter removing left recursions: "<<endl;
    for(int j=0; j<=i; j++)
        cout<<str[j]<<endl;
    //Convert to GNF
    cout << "i = " << i << endl;
    for(int j=0; j<=i; j++) {
        string production = str[j];
        cout << "Production = " << production << endl;
        int k=3;
        bool changed =false;
        do {
            while(!islower(production[k])) {
                int temp = 0;
                while(str[temp][0] != production[k])
                    temp++;
                string substitute = str[temp].substr(3);
                cout << "Found substitution = " << substitute << endl;
                int last = k+1;
                while(last != production.size() && production[last] != '/')
                    last++;
                string s = production.substr(k+1, last-k-1);
                cout << "string to be added = " << s<<endl;
                cout << "string to be substituted = " << production.substr(k, last-k)<<endl;
                int a = substitute.find('/');
                while(a != -1) {
                    substitute.insert(a,s);
                    a = substitute.find('/', a+s.size()+1);
                }
                substitute.append(s);
                cout << "Found substitution = " << substitute << endl;
                production.replace(k, last-k, substitute);
                cout << "Production = " << production << endl;
                //bool changed = true;
            }
            k = production.find('/', k) + 1;
        }while(k != 0);
        str[j] = production;
        //if(changed) j--;
    }

    cout<<"\nGNF Form: "<<endl;
    for(int j=0; j<=i; j++)
        cout<<str[j]<<endl;
    return 0;
}