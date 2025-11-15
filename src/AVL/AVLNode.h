#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "Person/Person.h"

class AVLTree;
class Person;

class AVLNode
{
    private:
        std::tuple <Person*,float> Key;
        AVLNode* Left;
        AVLNode* Right;
        AVLNode* Parent;
        int Height;
        int Balance;
    public:
        AVLNode(std::tuple <Person*,float> key);
        ~AVLNode();
        std::tuple <Person*,float> GetKey();
        void SetKey(float NewValue);
        void SetKey(std::tuple <Person*,float> NewKey);
        AVLNode* GetLeft();
        void SetLeft(AVLNode* NewLeft);
        AVLNode* GetRight();
        void SetRight(AVLNode* NewRight);
        AVLNode* GetParent();
        void SetParent(AVLNode* NewParent);
        int GetHeight();
        void UpdateHeight();
        int GetBalance();
        void UpdateBalance();
};