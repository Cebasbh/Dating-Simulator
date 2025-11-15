#include "WeightNode.h"

int WeightNode::Count = 1;

WeightNode::WeightNode(){
}

WeightNode::WeightNode(float weight, bool isroot)
{
    Value = 0;
    Weight = weight;
    Childs = {};
    Id = Count;
    IsRoot = isroot;
    Count++;
}

WeightNode::~WeightNode() {
}

void WeightNode::AddChild(WeightNode* child){
    Childs.push_back(child);
}

void WeightNode::CalculateResults(float input){
    if (Value == 0){
        Value = input * Weight;
    }
    else{
        Value = Value + input * Weight;
    }

    for (WeightNode* child : Childs) {
        if (!Childs.empty()){
            child->CalculateResults(Value);
        }
    }

    if (!Childs.empty()){
            Value = 0;
    }
}

float WeightNode::GetValue(){
    return Value;
}
float WeightNode::GetWeight(){
    return Weight;
}
void WeightNode::ResetValue(){
    Value = 0;
}
bool WeightNode::GetIsRoot(){
    return IsRoot;
}
int WeightNode::GetId(){
    return Id;
}
std::vector<WeightNode*> WeightNode::GetChilds(){
    return Childs;
}