#include <iostream>
#include <cctype>
using namespace std; 

bool passLength(string a){
    if(a.length()>=8){
        return true;
    }
    else {
        return false;
    }
}
bool isUpper(string a){
    for (char c: a)
    {
        if(isupper((unsigned char)c)){
            return true;
        }
    }
    return false;
}
bool isLower(string a){
    for(char c : a){
        if(islower((unsigned char)c)){
            return true;
        }
    }
    return false;
}
bool isDigit(string a){
    for(char c : a){
        if(isdigit((unsigned char)c)){
            return true;
        }
    }
    return false;
}
bool isSpecSym(string a){
    for(char c : a){
        if(!isalnum((unsigned char)c)){
            return true;
        }
    }
    return false;
}
int main(){
    string password;

    while(true){
        int strength = 0;
        cout<<"Enter Password: ";
        cin>>password;
        if(passLength(password)) strength++;
        if(isUpper(password)) strength++;
        if(isLower(password)) strength++;
        if(isDigit(password)) strength++;
        if(isSpecSym(password)) strength++;
        switch(strength){
            case 0:
            case 1:
            case 2:
                cout<<"Weak password\n";
                continue;
            case 3:
            case 4:
                cout<<"Medium password\n";
                break;
            case 5:
                cout<<"Strong password\n";
                break;
        }
        if(strength == 5) {
        break;
    }
    }
}