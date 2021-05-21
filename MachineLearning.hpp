#ifndef MACHINELEARNING_HPP
#define MACHINELEARNING_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

struct obj{
    uint64_t id;
    uint64_t classification;
    std::vector<double> data;
};

class Classifier {
    public:
        Classifier();
        void Train();
        uint64_t Test();

        /* Some way to store the testing data */
};

class Validator {
    public:
        Validator();
};

class MachineLearning {
    public:
        MachineLearning();
        ~MachineLearning();
        void DataFromFile(std::fstream&);
        void feature_search(int8_t);
        void setFeatureSetLen(unsigned int);
    private:
        double evaluation();
        void normalizeData();
        Classifier* Clas;
        Validator* Vali;
        std::string printFeatures(std::vector<int8_t>&);
        std::vector<int8_t> featureSet;
        unsigned int fSetLength;
        std::vector<obj> dataSet;
};

#endif