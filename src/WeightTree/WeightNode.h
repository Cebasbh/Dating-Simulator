#pragma once
#include <string>
#include <vector>
   
class WeightNode
{
    protected:
        static int Count;
        int Id; 
        float Weight;
        std::vector<WeightNode*> Childs;
        float Value;
        bool IsRoot;
    public:
        WeightNode();
        WeightNode(float weight, bool isroot);
        ~WeightNode();
        void AddChild(WeightNode* child);
        void CalculateResults(float input);
        float GetValue();
        float GetWeight();
        void ResetValue();
        bool GetIsRoot();
        int GetId();
        std::vector<WeightNode*> GetChilds();
};