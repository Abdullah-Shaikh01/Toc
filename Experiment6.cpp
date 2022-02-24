#include<bits/stdc++.h>
using namespace std;

int main() {
    string str[10];
    cout<<"Enter unit and null free productions only!!!"<<endl;
    cout<<"Enter the productions:\n  Use \"->\" for production \n  Use \"/\" for OR Example A->A*B/a \n  Use \'^\' for null \n  And press 0 to exit"<<endl;
    int i=0;
    // do {
    //     getline(cin,str[i]);
    //     i++;
    // }while(str[i-1] != "0");
    // i -= 2;

            //hardcoded values
            str[0] = "S->AB";
            str[1] = "A->BS";
            str[2] = "B->SA/a";
            i=2;
            cout<<"The productions are :" << endl;
            for(int j=0;j<=i;j++)
                cout << str[j] << endl;
    //removing terminal symbols
    map<char, string> newProductions;
    for(int j=0; j<=i; j++) {      
        string production = str[j];
        for(int k=3; k<production.size(); k++ ) {
            if(islower(production[k])) {
                if( (production[k-1] != '/' && production[k-1] != '>') || (k+1 != production.size() && production[k+1] != '/') ) {
                    if(newProductions.find(production[k]) == newProductions.end()) {
                        string newPro;
                        string s(1, ('X' + newProductions.size()));
                        newPro += s + "->" + production[k];
                        newProductions.insert({production[k], newPro});
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
        str[j] = production;
    }

    // cout<<"\nAfter removing terminal productions: "<<endl;
    // for(int j=0; j<=i; j++)
    //     cout<<str[j]<<endl;

    //convert to CNF
    map<string, string> newP;
    for(int j=0; j<=i; j++) {      
        string production = str[j];
        int right = 4;
        for(int left=2; left<production.size(); right=left+2) {
            while(right != production.size() && production[right] != '/') 
                right++;

            if (right - left > 3) {
                string key = production.substr(left+2, right-left-2);
                if (newP.find(key) == newP.end()) {
                    string s(1, ('L' + newP.size()));
                    string newPro = s + "->" + key;
                    newP.insert({key, newPro});
                    production.replace(left+2, right-left-2, newPro,0,1);
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
    //Eliminating > and left recursions
    int temp = i;
    for(int j=0; j<=temp; j++) {
        string production = str[j];
        int left = indexing[production[0]];
        int ii=0;
        int k=3;
        do {
            if(!islower(production[k])) {
                while(left > indexing[production[k]]) {
                    int temp = 0;
                    while(str[temp][0] != production[k])
                        temp++;
                    string substitute = str[temp].substr(3);
                    int last = k+1;
                    while(last != production.size() && production[last] != '/')
                        last++;
                    string s = production.substr(k+1, last-k-1);

                    int a = substitute.find('/');
                    while(a != -1) {
                        substitute.insert(a,s);
                        a = substitute.find('/', a+s.size()+1);
                    }
                    substitute.append(s);
                    production.replace(k, last-k, substitute);
                    //k += substitute.size() -2; 
                    if(islower(production[k]))
                        break;
                }
                if(!islower(production[k]) && left == indexing[production[k]]) {
                    int last = k+1;
                    while(last != production.size() && production[last] != '/')
                        last++;
                    string sub = production.substr(k, last-k);
                    production.erase(k, last-k+1);
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
                    s += "->" + sub + s + "/" + sub;
                    i++;
                    str[i] = s;
                }
            }
            k = production.find('/', k) + 1;
        }while(k != 0);
        str[j] = production;
    }
    
    cout<<"\nAfter removing left recursions: "<<endl;
    for(int j=0; j<=i; j++)
        cout<<str[j]<<endl;

    //Convert to GNF
    for(int j=0; j<=i; j++) {
        string production = str[j];
        int k=3;
        do {
            while(!islower(production[k])) {
                int temp = 0;
                while(str[temp][0] != production[k])
                    temp++;
                string substitute = str[temp].substr(3);
                int last = k+1;
                while(last != production.size() && production[last] != '/')
                    last++;
                string s = production.substr(k+1, last-k-1);
                int a = substitute.find('/');
                while(a != -1) {
                    substitute.insert(a,s);
                    a = substitute.find('/', a+s.size()+1);
                }
                substitute.append(s);
                production.replace(k, last-k, substitute);
            }
            k = production.find('/', k) + 1;
        }while(k != 0);
        str[j] = production;
    }

    cout<<"\nGNF Form: "<<endl;
    for(int j=0; j<=i; j++)
        cout<<str[j]<<endl;
    return 0;
}