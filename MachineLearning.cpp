#include "MachineLearning.hpp"

Classifier::Classifier() {}

Validator::Validator() {}

MachineLearning::MachineLearning() {}
MachineLearning::~MachineLearning() {}

double MachineLearning::evaluation() {return ( ( rand() % 1000 ) + 1) / 10.0;}
void MachineLearning::setFeatureSetLen(unsigned int a){fSetLength = a;}

void MachineLearning::DataFromFile(std::fstream& fs) {
    obj hold;
    std::stringstream input;
    std::string line;
    uint64_t IDincrement = 0;

    while( std::getline(fs, line) ){
        input.str(line); line = "";
        input >> line;
        hold.id = IDincrement++;
        hold.classification = std::stoi(line);
        for(int i = 0; i < this->fSetLength; ++i){
            input >> line;
            hold.data.push_back( std::stod(line) );
        }
        this->dataSet.push_back(hold);
        input.clear(); input.str();
        hold.data.clear();
    }
}

void MachineLearning::feature_search(int8_t choice) {
    double maxAccuracy = 0;

    if(choice == 0 || choice == 1){ // we can combine the algorithms for Foward Select and Backward Elim. using <choice> to flip the required variables
        this->featureSet = std::vector<int8_t> (fSetLength+1, choice);

        maxAccuracy = evaluation();

        if(choice == 0) {
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
            for(unsigned int i = 1; i < this->featureSet.size(); ++i){
                if(this->featureSet[i] == choice){
                    this->featureSet[i] = (choice+1)%2; // if 1 -> flip to 0 ; if 0 -> flip to 1

                    currAccuracy = evaluation();

                    std::cout << "Using feature(s) {" << printFeatures(featureSet) << "} accuracy is " << std::setprecision(3) << currAccuracy << "%\n";

                    if(maxAccuracy < currAccuracy){
                        maxIndex = i;
                        maxAccuracy = currAccuracy;
                    }
                    featureSet[i] = choice; // flip back
                }
            }
            if(maxIndex != 0){
                this->featureSet[maxIndex] = (choice+1)%2;
                std::cout << "\nFeature set {" << printFeatures(featureSet) << "} was best, accuracy is " << std::setprecision(3) << maxAccuracy << "%\n\n";
            }
            else{
                std::cout << "\n(Warning, Accuracy has decreased!)\n";
            }
        }
    }
    else{
        std::cout << "Urban's Algorithm is underconstruction.\n\n";
    }

    if(featureSet.size() > 1){
        std::cout << "Finished search!! The best feature subset is {" << printFeatures(featureSet) << "} which has an accuracy of " << std::setprecision(3) << maxAccuracy << "%\n";
    } else {
        std::cout << "Finished search!! The best feature subset has no features which has an accuracy of " << std::setprecision(3) << maxAccuracy << "%\n";
    }
}

std::string MachineLearning::printFeatures(std::vector<int8_t>& fSet){
    std::string str_fList;
    for(unsigned int i = 1; i < fSet.size(); ++i){
        if(fSet[i] == 1){ str_fList += std::to_string(i) + ',';}
    }

    if(str_fList.size() != 0){
        str_fList.pop_back();
    }

    return str_fList;
}