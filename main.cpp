#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "MachineLearning.hpp"

using namespace std;

int8_t getFeatureAlg(); 
int getFeatureSetLength();

int main() {
    srand(time(NULL));
    MachineLearning ML;

    cout << "Welcome to Rudy and Sana's Feature Selection Algorithm\n\n";
    int8_t fSetLen = getFeatureSetLength();
    ML.setFeatureSetLen( fSetLen ); cout << endl;

    string file_name;
    cout << "Type in the name of the file to test: ";
    cin >> file_name; cout << endl;
    
    fstream dataFile (file_name.c_str(), fstream::in);
    if( dataFile.is_open() ){
        ML.DataFromFile(dataFile);
        dataFile.close();

        int8_t choice_1 = getFeatureAlg();
        ML.feature_search(choice_1);

        /* ... */
    }
    else{
        cout << ">>Cannot find or open \"" << file_name << "\" in current directory.\n";
    }

    return 0;
}

int8_t getFeatureAlg(){
    cin.ignore(INT_MAX, '\n');
    cin.clear();
    string input;
    int8_t choice = 0;
    cout << "Type the number of the algorithm you want to run:\n"
              << "    [1] Forward Selection\n"
              << "    [2] Backward Elimination\n";
             // << "    [3] Urban's Homegrown Algorithm\n";
    while(input == ""){
        cout << ">>Input your choice: "; getline(cin, input);
        if(input == "1" || input == "2" /*|| input == "3"*/) {choice = input.at(0) - 49;}
        else{
            cout << ">>SELECT PROPER INPUT\n";
            input = "";
        }
    }
    return choice;
}

int getFeatureSetLength() {
    string input;

    while(input == ""){
        cout << "Please enter the total number of features: ";
        cin >> input;
        for(unsigned int i = 0; i < input.size(); ++i){
            if(!isdigit(input[i])){
                cout << ">>SELECT PROPER INPUT\n";
                input = "";
            }
        }
    }

    return stoi(input);
}