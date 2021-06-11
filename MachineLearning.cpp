#include "MachineLearning.hpp"

//===CLASSIFIER===========================================================================================

//--For-Classifier's-Test()--------------------------------------------
struct objEuc_Pair {
    objEuc_Pair(obj* a, long double b) : data_Obj(a), euc(b) {}
    obj* data_Obj;
    long double euc;
};
class objEuc_Compare {
    public:
        bool operator() (const objEuc_Pair& lhs, const objEuc_Pair& rhs) {
            return lhs.euc < rhs.euc;
        }
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Classifier::Classifier(unsigned int K, unsigned int numNN) : k_Size(K), numNearestNeighbors(numNN) {
    this->trainingSet = nullptr;
}
void Classifier::setK(unsigned int num) {this->k_Size = num;}
unsigned int Classifier::getK() {return this->k_Size;}
void Classifier::setNumNN(unsigned int num) {this->numNearestNeighbors = num;}
unsigned int Classifier::getNumNN() {return this->numNearestNeighbors;}
void Classifier::setFeatureSet(std::vector<int8_t>& fSet) {this->featureSet = fSet;}
size_t Classifier::size(){return this->trainingSet->size();}
void Classifier::Train(std::vector<obj>& trSet) {this->trainingSet = &trSet;}
uint32_t Classifier::Test(uint32_t test_obj_index = 0) { //pain
    uint32_t classification = 0;
    std::priority_queue<long double, std::vector<objEuc_Pair>, objEuc_Compare> nearestNeighbors;
    long double euclidianDistance;

    if(this->trainingSet->size()){
        for(size_t ObjIndex = 0; ObjIndex < this->trainingSet->size(); ++ObjIndex){
            euclidianDistance = 0;
            if(ObjIndex < test_obj_index || ObjIndex > test_obj_index + k_Size){
                for(size_t fIndex = 1; fIndex < this->featureSet.size(); ++fIndex){
                    if(this->featureSet[fIndex] == 1){
                        euclidianDistance += std::pow( this->trainingSet->at(test_obj_index).data[fIndex-1] - this->trainingSet->at(ObjIndex).data[fIndex-1] , 2 ); 
                    }
                }
                euclidianDistance = std::sqrt( euclidianDistance );

                nearestNeighbors.push( objEuc_Pair( &this->trainingSet->at(ObjIndex), euclidianDistance) );
                if(nearestNeighbors.size() > numNearestNeighbors){
                    nearestNeighbors.pop();
                }
            }
        }
        std::map<uint32_t, size_t> classCounter;
        classCounter.insert( std::pair<uint32_t, size_t>(0, 0));
        for(unsigned int i = 0; i < nearestNeighbors.size(); ++i){
            size_t currIndex = nearestNeighbors.top().data_Obj->classification;
            if(classCounter.insert( std::pair<uint32_t, size_t>(currIndex, 1) ).second == false){
                ++classCounter.at(currIndex);
            }
            if(classCounter[classification] < classCounter[currIndex]){
                classification = currIndex;
            }
        }
    }

    return classification;
}
double Classifier::commonClassPercentage() {
    double ccRatio = 0;
    size_t dataSet_SIZE = this->trainingSet->size();
    
    if(dataSet_SIZE > 0) {

        std::map<int32_t, size_t> classCounter;
        uint32_t classification = 0;
        obj* currObj = nullptr;
        for(size_t i = 0; i < dataSet_SIZE; ++i){
            currObj = &trainingSet->at(i);
            if(classCounter.insert( std::pair<int32_t, size_t>(currObj->classification, 1) ).second == false){
                ++classCounter.at(currObj->classification);
            }
            if(classCounter[classification] < classCounter[currObj->classification]){
                classification = currObj->classification;
            }
        }


        ccRatio = (1.0 * classCounter[classification]) / dataSet_SIZE;
    }

    return ccRatio;
}


//===VALIDATOR============================================================================================

double Validator::validate(std::vector<int8_t>& fSet, Classifier& clas) {
    double acc = 0;
    size_t numTestCorrect = 0;

    bool hasFeatures = false;
    for(size_t i = 1; i < fSet.size(); ++i){
        if(fSet[i] == 1){
            hasFeatures = true;
            break;
        }
    }

    if(!hasFeatures){
        acc = clas.commonClassPercentage();
    }
    else{
        clas.setFeatureSet(fSet);
        for(uint32_t i = 0; i < clas.size(); ++i){
            uint32_t holdClass = clas.Test(i);
            if(this->dataSet->at(i).classification == holdClass){
                ++numTestCorrect;
            }
        }
        acc = ( 1.0 * numTestCorrect) / clas.size();
    }

    return acc * 100;
}
void Validator::setDataSet(std::vector<obj>& dSet) {this->dataSet = &dSet;}

//===MACHINE=LEARNING=====================================================================================
MachineLearning::MachineLearning() {}
MachineLearning::~MachineLearning() {}

double MachineLearning::evaluation() {return ( ( rand() % 1000 ) + 1) / 10.0;}
void MachineLearning::setFeatureSetLen(unsigned int a){fSetLength = a;}
size_t MachineLearning::dataSet_size(){return this->dataSet.size();}
void MachineLearning::attachTimer(timer& t){this->t = &t;}
std::string MachineLearning::time(){
    if(this->t){ 
        return this->t->time();
    }
    return "";
}

void MachineLearning::loadDataFromFile(std::fstream& fs) {
    obj hold;
    std::stringstream input;
    std::string line;
    uint32_t IDincrement = 0;

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

void MachineLearning::normalize() {
    long double mean, variance, stdDev;

    // [(x - x*) / stdDev_x*]

    for(unsigned int f_i = 0; f_i < this->fSetLength; ++f_i){
        mean = 0;
        for(uint32_t obj_i = 0; obj_i < this->dataSet.size(); ++obj_i){
            mean += this->dataSet[obj_i].data[f_i];
        }
        mean = mean / this->dataSet.size();

        variance = 0;
        for(uint32_t obj_i = 0; obj_i < this->dataSet.size(); ++obj_i){
            variance += std::pow(this->dataSet[obj_i].data[f_i] - mean, 2);
        }
        variance = variance / this->dataSet.size();

        stdDev = std::sqrt( variance );
        for(uint32_t obj_i = 0; obj_i < this->dataSet.size(); ++obj_i){
            this->dataSet[obj_i].data[f_i] = (this->dataSet[obj_i].data[f_i] - mean) / stdDev;
        }
    }
}

void MachineLearning::feature_search(int8_t choice) {
    this->Clas.Train(this->dataSet);
    this->Vali.setDataSet(this->dataSet);
    double maxAccuracy = 0;

    if(choice == 0 || choice == 1){ // we can combine the algorithms for Foward Select and Backward Elim. using <choice> to flip the required variables
        this->featureSet = std::vector<int8_t> (fSetLength+1, choice);

        maxAccuracy = Vali.validate(this->featureSet, this->Clas);

        
        if(choice == 0) {
            std::cout << time() << "Using no features and most-common-classification evaluation, accuracy is " << std::setprecision(3) << maxAccuracy << "%\n\n";
        }
        else {
            std::cout << time() << "Using all features and leave-" << this->Clas.getK()+1 << "-out evaluation, accuracy is " << std::setprecision(3) << maxAccuracy << "%\n\n";
        }
        std::cout << time() << "Beginning search\n"
                            << "\t    >> K-Clustering size: " << this->Clas.getK() + 1 << "\n"
                            << "\t    >> Number of Nearest Neighbors: " << this->Clas.getNumNN() << "\n\n";

        double currAccuracy;
        unsigned int maxIndex = 1;

        while(maxIndex != 0){
            maxIndex = 0;
            for(unsigned int i = 1; i < this->featureSet.size(); ++i){
                if(this->featureSet[i] == choice){
                    this->featureSet[i] = (choice+1)%2; // if 1 -> flip to 0 ; if 0 -> flip to 1

                    currAccuracy = Vali.validate(this->featureSet, this->Clas);

                    std::cout << time() << "Using feature(s) {" << printFeatures(featureSet) << "} accuracy is " << std::setprecision(3) << currAccuracy << "%\n";

                    if(maxAccuracy <= currAccuracy){
                        maxIndex = i;
                        maxAccuracy = currAccuracy;
                    }
                    featureSet[i] = choice; // flip back
                }
            }
            if(maxIndex != 0){
                this->featureSet[maxIndex] = (choice+1)%2;
                std::cout << std::endl << time() << "Feature set {" << printFeatures(featureSet) << "} was best, accuracy is " << std::setprecision(3) << maxAccuracy << "%\n\n";
            }
            else{
                std::cout << std::endl << time() << "(Warning, Accuracy has decreased!)\n";
            }
        }
    }
    else{
        std::cout << "Urban's Algorithm is underconstruction.\n\n";
    }

    if(featureSet.size() > 1){
        std::cout << time() << "Finished search!! The best feature subset is {" << printFeatures(featureSet) << "} which has an accuracy of " << std::setprecision(3) << maxAccuracy << "%\n";
    } else {
        std::cout << time() << "Finished search!! The best feature subset has no features which has an accuracy of " << std::setprecision(3) << maxAccuracy << "%\n";
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

void MachineLearning::printDataSetToFile(const std::string& str){
    std::ofstream oF (str.c_str(), std::ofstream::out);

    if( oF.is_open() ){
        for(uint32_t obj_i = 0; obj_i < this->dataSet.size(); ++obj_i){
            oF << '(' << this->dataSet[obj_i].id << ") [" << this->dataSet[obj_i].classification << "] ";
            oF.precision(7);
            for(unsigned int f_i = 0; f_i < this->fSetLength; ++f_i){
                oF << std::scientific <<  this->dataSet[obj_i].data[f_i] << " ";
            }
            oF << std::endl;
        }

        oF.close();
    }
    else{
        std::cout << "Could not print to file.\n";
    }
}

void MachineLearning::plot(std::string str) {
    std::vector<int> hold;
    for(unsigned i = 1; i < featureSet.size(); ++i){
        if(this->featureSet[i]){
            hold.push_back(i);
        }
    }

    if(hold.size() == 2){
        std::ofstream of1 ("class1.csv");
        std::ofstream of2 ("class2.csv");
        if(of1.is_open() && of2.is_open()){
            of1 << "featureONE" << ',' << "featureTWO" << std::endl;
            of2 << "featureONE" << ',' << "featureTWO" << std::endl;
            for(size_t i = 0; i < this->dataSet.size(); ++i){
                auto currObj = this->dataSet[i];
                if(currObj.classification == 1){
                    of1 << currObj.data[hold[0]-1] << ',' << currObj.data[hold[1]-1] << std::endl;
                } else {
                    of2 << currObj.data[hold[0]-1] << ',' << currObj.data[hold[1]-1] << std::endl;
                }
            }
            of1.close();
            of2.close();
            std::string command = "py printPlot.py " + std::to_string(hold[0]) + ' ' + std::to_string(hold[1]) + ' ' + str;
            system(command.c_str());
        }
    }
}