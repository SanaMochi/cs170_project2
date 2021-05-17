#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

struct obj{
    std::vector<float> data;
};

int evaluation(obj*) {return ( rand() % 1000 ) + 1;}
std::vector<obj>* dataPreprocessing(std::fstream&); 
std::vector<int8_t> feature_search(std::vector<obj>*, int, int8_t); // {0,1,0,1,0,1,0} -> features {1, 3, 5} ; {0,0,1,1,0,0,1} -> features {2,3,6}

int8_t getFeatureAlg(); 
int getFeatureSetLength();

int main() {
    srand(time(NULL));
    std::string file_name;
    std::cout << "Welcome to Urban's Feature Selection Algorithm\n\n";
    int featureSetLength = getFeatureSetLength(); std::cout << std::endl;
    std::cout << "Type in the name of the file to test: ";
    /* --> ask for number of features <-- */
    std::cin >> file_name; std::cout << std::endl;
    
    std::fstream dataFile (file_name.c_str(), std::fstream::in);
    if( dataFile.is_open() ){
        std::cout << ">>Opened " << file_name << std::endl;
        std::vector<obj>* dataSet = dataPreprocessing(dataFile);
        int8_t choice_1 = getFeatureAlg();

        std::vector<int8_t> feature_set = feature_search(dataSet, featureSetLength, choice_1);

        /* ... */

        dataFile.close();
    }
    else{
        std::cout << ">>Cannot find \"" << file_name << "\" in current directory.\n";
    }

    return 0;
}

std::vector<int8_t> feature_search(std::vector<obj>* a, int b, int8_t c) {
    std::cout << ">>Entered Feature Search.\n\n";
    std::vector<int8_t> fSet;
    double maxAccuracy = 0;

    if(c == 0 || c == 1){
        fSet = std::vector<int8_t> (b+1, c);

        maxAccuracy = evaluation(nullptr) / 10.0;
        if(c == 0) {
            std::cout << "Using no features and \"random\" evaluation, accuracy is " << std::setprecision(3) << maxAccuracy << "%\n\n";
        }
        else {
            std::cout << "Using all features and \"random\" evaluation, accuracy is " << std::setprecision(3) << maxAccuracy << "%\n\n";
        }
        std::cout << "Beginning search.\n\n";

        double currAccuracy;
        unsigned int maxIndex = 1;

        while(maxIndex != 0){
            maxIndex = 0;
            for(unsigned int i = 1; i < fSet.size(); ++i){
                if(fSet[i] == c){
                    fSet[i] = (c+1)%2;

                    currAccuracy = evaluation(nullptr) / 10.0;

                    std::cout << "Using feature(s) {";
                    for(unsigned int j = 1; j < fSet.size(); ++j){
                        if(fSet[j] == 1){ std::cout << j << ',';}
                    }
                    std::cout << "\b} accuracy is " << std::setprecision(3) << currAccuracy << "%\n";

                    if(maxAccuracy < currAccuracy){
                        maxIndex = i;
                        maxAccuracy = currAccuracy;
                    }
                    fSet[i] = c;
                }
            }
            if(maxIndex != 0){
                fSet[maxIndex] = (c+1)%2;

                std::cout << "\nFeature set {";
                for(unsigned int j = 1; j < fSet.size(); ++j){
                    if(fSet[j] == 1){ std::cout << j << ',';}
                }
                std::cout << "\b} was best, accuracy is " << std::setprecision(3) << maxAccuracy << "%\n\n";
            }
            else{
                std::cout << "\n(Warning, Accuracy has decreased!)\n";
            }
        }
    }
    else{
        std::cout << "Urban's Algorithm is underconstruction.\n\n";
    }

    if(fSet.size() > 1){
        std::cout << "Finished search!! The best feature subset is {"; 
        for(unsigned int j = 1; j < fSet.size(); ++j){
            if(fSet[j] == 1){ std::cout << j << ',';}
        }
        std::cout << "\b} which has an acurracy of " << std::setprecision(3) << maxAccuracy << "%\n";
    } else {
        std::cout << "Finished search!! The best feature subset has no features which has an acurracy of " << std::setprecision(3) << maxAccuracy << "%\n";
    }
    return fSet;
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


     / --> normalization <-- /

    return dataSet; */
    std::cout << ">>Entered DataProc.\n";
    return nullptr;
}

int8_t getFeatureAlg(){
    std::cin.ignore(INT_MAX, '\n');
    std::cin.clear();
    std::string input;
    int8_t choice = 0;
    std::cout << "Type the number of the algorithm you want to run:\n"
              << "    [1] Forward Selection\n"
              << "    [2] Backward Elimination\n"
              << "    [3] Urban's Homegrown Algorithm\n";
    while(input == ""){
        std::cout << ">>Input your choice: "; std::getline(std::cin, input);
        if(input == "1" || input == "2" || input == "3") {choice = input.at(0) - 49;}
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