#pragma once
#include "AVLNode.h"
#include <iostream>
#include <vector>
class AVLNode;
class Person;

class AVLTree
{
    private:
        AVLNode* Root;
    public:
        AVLTree();
        ~AVLTree();

        AVLNode* LeftRotate(AVLNode* x);
        AVLNode* RightRotate(AVLNode* x);

        AVLNode* InsertbyComp(std::tuple <Person*,float> key, AVLNode* parent = nullptr);
        AVLNode* InsertbyComp(AVLNode* node, std::tuple <Person*,float> key, AVLNode* parent = nullptr);

        AVLNode* SearchbyComp(float searched);
        AVLNode* SearchbyComp(AVLNode* node, float searched);
        
        AVLNode* InsertbyId(std::tuple <Person*,float> key, AVLNode* parent = nullptr);
        AVLNode* InsertbyId(AVLNode* node, std::tuple <Person*,float> key, AVLNode* parent = nullptr);

        AVLNode* SearchbyId(Person* searched);
        AVLNode* SearchbyId(AVLNode* node, Person* searched);

        void DeletebyComp(float valuetodelete);
        void DeletebyComp(AVLNode* node, float valuetodelete);

        AVLNode* Balance(AVLNode* node);
        
        AVLNode* GetRoot();
        void SetRoot(AVLNode* node);

        void ReversedInorder(int& count);
        void ReversedInorder(AVLNode* node, int& count);

        std::vector<std::tuple <Person*,float>> ReversedInorderVector();
        std::vector<std::tuple <Person*,float>> ReversedInorderVector(AVLNode* node, std::vector<std::tuple <Person*,float>>& list);
};