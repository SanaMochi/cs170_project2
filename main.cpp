#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

struct obj{
    std::vector<float> data;
};

int evaluation(obj*) {return ( rand() % 1000 ) + 1;}
std::vector<obj>* dataPreprocessing(std::fstream&); 
char* feature_search(std::vector<obj>*, char); // {0,1,0,1,0,1,0} -> features {1, 3, 5} ; {0,0,1,1,0,0,1} -> features {2,3,6}

char getFeatureAlg(); 
int getFeatureSetLength();

int main() {
    std::string file_name;
    std::cout << "Welcome to Urban's Feature Selection Algorithm\n\n";
    int featureSetLength = getFeatureSetLength(); std::cout << std::endl;
    std::cout << "Type in the name of the file to test: ";
    /* --> ask for number of features <-- */
    std::cin >> file_name; std::cout << std::endl;
    
    std::fstream dataFile (file_name.c_str(), std::fstream::in);
    if( true ){ //if( dataFile.is_open() ){
        std::cout << ">>Opened " << file_name << std::endl;
        std::vector<obj>* dataSet = dataPreprocessing(dataFile);
        char choice_1 = getFeatureAlg();

        char* feature_set = feature_search(dataSet, choice_1);

        /* ... */

        //dataFile.close();
    }
    else{
        std::cout << ">>Cannot find \"" << file_name << "\" in current directory.\n";
    }

    return 0;
}

char* feature_search(std::vector<obj>*, char) {
    std::cout << ">>Entered Feature Search.\n";
    return nullptr;
}

std::vector<obj>* dataPreprocessing(std::fstream& fs) {
    /* std::vector<obj>* dataSet;
    obj hold;
    std::stringstream input;
    std::string line;

    while( !fs.eof() ){
        std::getline(fs, line);
        input.str(line); line = "";

        while(input >> line){
            hold.data.push_back( std::stof(line) );
        }

        dataSet->push_back(hold);
        input.clear(); input.str();
        hold.data.clear();
    }


     /* --> normalization <-- /

    return dataSet; */
    std::cout << ">>Entered DataProc.\n";
    return nullptr;
}

char getFeatureAlg(){
    std::cin.ignore(INT_MAX, '\n');
    std::cin.clear();
    std::string input;
    char choice = 0;
    std::cout << "Type the number of the algorithm you want to run:\n"
              << "    [1] Forward Selection\n"
              << "    [2] Backward Elimination\n"
              << "    [3] Urban's Homegrown Algorithm\n";
    while(input == ""){
        std::cout << ">>Input your choice: "; std::getline(std::cin, input);
        if(input == "1" || input == "2" || input == "3") {choice = input.at(0) - 1;}
        else{
            std::cout << ">>SELECT PROPER INPUT\n";
            input = "";
        }
    }
    return choice;
}

int getFeatureSetLength() {
    std::string input;

    while(input == ""){
        std::cout << "Please enter the total number of features: ";
        std::cin >> input;
        for(unsigned int i = 0; i < input.size(); ++i){
            if(!isdigit(input[i])){
                std::cout << ">>SELECT PROPER INPUT\n";
                input = "";
            }
        }
    }

    return stoi(input);
}