#ifndef MACHINELEARNING_HPP
#define MACHINELEARNING_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>

struct obj {
    uint32_t id;
    uint32_t classification;
    std::vector<double> data;
};

class Classifier {
    public:
        Classifier(unsigned int K, unsigned int numNN); //K -> K means size ; Root -> set of identies to ignore and the K objs right after them
        void Train(std::vector<obj>& trSet); 
        uint32_t Test(uint32_t test_obj_index); //returns classification
        void setK(unsigned int); //change K size
        void setNumNN(unsigned int); //set max number of Nearest Neighbors to check
    private:
        unsigned int numNearestNeighbors;
        unsigned int k_Size; //number of objs reserved from dataSet to be used for testing
        std::vector<obj>* trainingSet; //pointer to dataSet - assuming that dataSet does not change //Should classifier have this instead of ML?
        //std::vector<obj> dataSet;
};

class Validator {
    public:
        double validate(std::vector<int8_t>& fSet);
};

class MachineLearning {
    public:
        MachineLearning();
        ~MachineLearning();
        void DataFromFile(std::fstream&);
        void feature_search(int8_t);
        void setFeatureSetLen(unsigned int);
        void printDataSetToFile(const std::string&);
    private:
        double evaluation();
        void normalizeData();
        Classifier Clas;
        Validator Vali;
        std::string printFeatures(std::vector<int8_t>&);
        std::vector<int8_t> featureSet;
        unsigned int fSetLength;
        std::vector<obj> dataSet;
};

#endif