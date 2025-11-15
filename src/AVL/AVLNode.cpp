#include "AVLNode.h"

AVLNode::AVLNode(std::tuple <Person*,float> key){
    Key = key;
    Left = nullptr;
    Right = nullptr;
    Parent = nullptr;
    Height = 0;
    Balance = 0;
}

AVLNode::~AVLNode() {
}
std::tuple <Person*,float> AVLNode::GetKey(){
    return Key;
}
void AVLNode::SetKey(float NewKey){
    std::get<1>(Key) = NewKey;
}
void AVLNode::SetKey(std::tuple <Person*,float> NewKey){
    Key = NewKey;
}
AVLNode* AVLNode::GetLeft(){
    return Left;
}
void AVLNode::SetLeft(AVLNode* NewLeft){
    Left = NewLeft;
}
AVLNode* AVLNode::GetRight(){
    return Right;
}
void AVLNode::SetRight(AVLNode* NewRight){
    Right = NewRight;
}
AVLNode* AVLNode::GetParent(){
    return Parent;
}
void AVLNode::SetParent(AVLNode* NewParent){
    Parent = NewParent;
}
int AVLNode::GetHeight(){
    return Height;
}
int AVLNode::GetBalance(){
    return Balance;
}

void AVLNode::UpdateHeight() {
    int LeftHeight;
    int RightHeight;

    if (Left != nullptr) {
        LeftHeight = Left->GetHeight();
    } else {
        LeftHeight = -1;
    }

    if (Right != nullptr) {
        RightHeight = Right->GetHeight();
    } else {
        RightHeight = -1;
    }

    Height = std::max(LeftHeight, RightHeight) + 1;
}

void AVLNode::UpdateBalance() {
    int LeftHeight;
    int RightHeight;

    if (Left != nullptr) {
        LeftHeight = Left->GetHeight();
    } else {
        LeftHeight = -1;
    }

    if (Right != nullptr) {
        RightHeight = Right->GetHeight();
    } else {
        RightHeight = -1;
    }

    Balance = LeftHeight - RightHeight;
}