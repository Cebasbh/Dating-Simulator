#pragma once
#include <string>
#include <vector>
#include "WeightNode.h"

class WeightTree
{
    private:
        std::vector<WeightNode*> Nodes;
    public:
        WeightTree();
        ~WeightTree();
        void AddNode(float weight, std::vector<int> parents);
        float CalculateFinalValue(std::vector<int> Data);
};