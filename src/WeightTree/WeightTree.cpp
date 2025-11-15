#include "WeightTree.h"
WeightTree::WeightTree()
{
    Nodes = {};
}

WeightTree::~WeightTree() {
}

void WeightTree::AddNode(float weight, std::vector<int> parents){
    WeightNode* newnode;
    if (parents.empty()){
        newnode = new WeightNode(weight, true);
    }
    else{
        newnode = new WeightNode(weight, false);
    }
    Nodes.push_back(newnode);
    for (WeightNode* node : Nodes) {
        for (int parent : parents){
            if (node->GetId() == parent){
                node->AddChild(newnode);
            }
        }
    }
}

float WeightTree::CalculateFinalValue(std::vector<int> Data){
    int index = 0;
    for (WeightNode* node : Nodes){
        if(node->GetIsRoot()){
            node->CalculateResults(Data[index]);
            index++;
        }
    }
    for (WeightNode* node : Nodes){
        if (node->GetChilds().empty()){
            float result = node->GetValue();
            node->ResetValue();
            return result;
        }
    }
    return 0;
}