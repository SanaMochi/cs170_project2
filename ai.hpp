#ifndef AI_HPP
#define AI_HPP

#include <vector>

struct obj {
    std::vector<float> data;
};

class Ai {
    public:
        Ai(){}
        ~Ai(){}
        float evaluation();
        std::vector<obj*>* dataPreprocessing();
        char* feature_search();
    private:
        int* feature_set;
        std::vector<obj*> dataSet;
};

#endif