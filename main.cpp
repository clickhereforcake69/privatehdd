#include <iostream>
#include <string.h>
#include <fstream>
#include "sha1.cpp"
using namespace std;

//this is wacc and theres probably a shorter/faster way to do this but it works

bool firstrunn(){
    bool ret;
    ifstream in;
    string wack;
    int pos;
    in.open("cred.txt");
    getline(in, wack);
    wack = wack.substr(wack.find(":")+1);

    if(wack == "false"){
        ret = false;
    }
    else{
        ret = true;
    }
    return ret;
}

string newpass(const string pass){
    SHA1 checksum;
    checksum.update(pass);
    const string hash = checksum.final();
    return hash;
}

bool login(string user, string pass){
    bool isright = false;
    char y;
    string use = "";
    string pas = "";
    cout << "Login username:\n";
    cin >> use;
    cout << "Login password:\n";
    cin >> pas;
    pas = newpass(pas);
    if(pass == pas && use == user){
        isright = true;
    }else{
        isright = false;
    }
    return isright;
}

int main(){
    bool firstrun = firstrunn();
    string userin;
    string passin;
    string tempin;
    string creds = "";

    if(firstrun){
        ofstream out;
        cout << "Create a username:\n";
        cin >> userin;
        cout << "Create a password:\n";
        cin >> passin;
        passin = newpass(passin);
        tempin = userin + "]" + passin;
        out.open("cred.txt");
        out << tempin << ":false" << endl;   
        out.close();
    }

    string temp = "";
    ifstream in;
    in.open("cred.txt");
    getline(in, temp);
    size_t pos = temp.find(':');
    string usern = temp.substr(0,temp.find("]"));
    string passw = temp.substr(temp.find("]") + 1, temp.find(":") - (temp.find("]") + 1));
    in.close();

    if(login(usern, passw)){
        int numin;
        cout << "1: show\n2: hide" << endl;
        cin >> numin;
        if(numin == 1){
            system("show.bat");
        }
        if(numin == 2){
            system("hide.bat");
        }

    }
    else{
        cout << "gay";
    }
}