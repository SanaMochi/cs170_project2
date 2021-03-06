#ifndef MACHINELEARNING_HPP
#define MACHINELEARNING_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <queue>
#include <map>

#include "timer.hpp"

struct obj {
    uint32_t id;
    uint32_t classification;
    std::vector<double> data;
};

class Classifier {
    public:
        Classifier(unsigned int K = 0, unsigned int numNN = 1); //K -> K means size ; numNN -> set the number of nearest Neighbors
        void Train(std::vector<obj>& trSet); //set trainingSet to point to Machine Learning's dataSet
        uint32_t Test(uint32_t test_obj_index); //returns classification
        void setK(unsigned int); //change K size -- K default to 0 (in essence acts like 1)
        unsigned int getK();
        void setNumNN(unsigned int); //set max number of Nearest Neighbors to check -- numNN default to 1
        unsigned int getNumNN();
        void setFeatureSet(std::vector<int8_t>& fSet); //set featureSet to passed in fSet
        // VVV For when there are no features enabled in the Feature Set VVV
        double commonClassPercentage(); //returns the ratio of the most common class to the total data set
        size_t size();
    private:
        unsigned int numNearestNeighbors;
        unsigned int k_Size; //number of objs reserved from dataSet to be used for testing
        std::vector<obj>* trainingSet; //pointer to dataSet - assuming that dataSet does not change //Should classifier have this instead of ML?
        //std::vector<obj> dataSet;
        std::vector<int8_t> featureSet;
};

class Validator {
    public:
        double validate(std::vector<int8_t>& fSet, Classifier&);
        void setDataSet(std::vector<obj>& dSet);
    private:
        std::vector<obj>* dataSet;
};

class MachineLearning {
    public:
        MachineLearning();
        ~MachineLearning();
        void loadDataFromFile(std::fstream&);
        void feature_search(int8_t);
        void setFeatureSetLen(unsigned int);
        void printDataSetToFile(const std::string&);
        void normalize();
        size_t dataSet_size();
        void attachTimer(timer&);
        std::string time();
        void plot(std::string str = "");
    private:
        double evaluation();
        Classifier Clas;
        Validator Vali;
        std::string printFeatures(std::vector<int8_t>&);
        std::vector<int8_t> featureSet;
        unsigned int fSetLength;
        std::vector<obj> dataSet;
        timer* t = nullptr;
};

#endif