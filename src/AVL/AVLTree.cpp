#include "AVLTree.h"

AVLTree::AVLTree(){
    Root = nullptr;
}
AVLTree:: ~AVLTree(){
}

AVLNode* AVLTree::LeftRotate(AVLNode* PadreporBajar) {
    AVLNode* HijoporSubir = PadreporBajar->GetRight();
    PadreporBajar->SetRight(HijoporSubir->GetLeft());

    if (HijoporSubir->GetLeft() != nullptr)
        HijoporSubir->GetLeft()->SetParent(PadreporBajar);

    HijoporSubir->SetParent(PadreporBajar->GetParent());

    if (PadreporBajar->GetParent() == nullptr)
        Root = HijoporSubir;
    else if (PadreporBajar == PadreporBajar->GetParent()->GetLeft())
        PadreporBajar->GetParent()->SetLeft(HijoporSubir);
    else
        PadreporBajar->GetParent()->SetRight(HijoporSubir);

    HijoporSubir->SetLeft(PadreporBajar);
    PadreporBajar->SetParent(HijoporSubir);
    
    PadreporBajar->UpdateHeight();
    HijoporSubir->UpdateHeight();
    return HijoporSubir;
}

AVLNode* AVLTree::RightRotate(AVLNode* PadreporBajar) {
    AVLNode* HijoporSubir = PadreporBajar->GetLeft();
    PadreporBajar->SetLeft(HijoporSubir->GetRight());
    if (HijoporSubir->GetRight() != nullptr)
        HijoporSubir->GetRight()->SetParent(PadreporBajar);

    HijoporSubir->SetParent(PadreporBajar->GetParent());

    if (PadreporBajar->GetParent() == nullptr)
        Root = HijoporSubir;
    else if (PadreporBajar == PadreporBajar->GetParent()->GetRight())
        PadreporBajar->GetParent()->SetRight(HijoporSubir);
    else
        PadreporBajar->GetParent()->SetLeft(HijoporSubir); 

    HijoporSubir->SetRight(PadreporBajar);
    PadreporBajar->SetParent(HijoporSubir);

    PadreporBajar->UpdateHeight();
    HijoporSubir->UpdateHeight();
    return HijoporSubir;
}

AVLNode* AVLTree::InsertbyComp(std::tuple <Person*,float> key, AVLNode* parent){
    return InsertbyComp(Root, key, parent);
}
AVLNode* AVLTree::InsertbyComp(AVLNode* node, std::tuple <Person*,float> key, AVLNode* parent){
    if (!node) {
        AVLNode* NewNode = new AVLNode(key);
        NewNode->SetParent(parent);
        return NewNode;
    }
    
    if (std::get<1>(key) < std::get<1>(node->GetKey()))
        node->SetLeft(InsertbyComp(node->GetLeft(), key, node));
    else if (std::get<1>(key) >= std::get<1>(node->GetKey()))
        node->SetRight(InsertbyComp(node->GetRight(), key, node));
    else
        return node;
    return Balance(node);
}
AVLNode* AVLTree::SearchbyComp(float searched){
    return SearchbyComp(Root, searched);
}
AVLNode* AVLTree::SearchbyComp(AVLNode* node, float searched){
    if (!node){ 
        return nullptr;
    }
    if (std::get<1>(node->GetKey()) == searched){
        return node;
    }
    else if (std::get<1>(node->GetKey()) > searched){
        return SearchbyComp(node->GetLeft(), searched);
    }
    else if (std::get<1>(node->GetKey()) < searched){
        return SearchbyComp(node->GetRight(), searched);
    }
    return nullptr;
}

AVLNode* AVLTree::InsertbyId(std::tuple <Person*,float> key, AVLNode* parent){
    return InsertbyId(Root, key, parent);
}
AVLNode* AVLTree::InsertbyId(AVLNode* node, std::tuple <Person*,float> key, AVLNode* parent){
    if (!node) {
        AVLNode* NewNode = new AVLNode(key);
        NewNode->SetParent(parent);
        return NewNode;
    }
    
    if (std::get<0>(key)->GetId() < std::get<0>(node->GetKey())->GetId())
        node->SetLeft(InsertbyId(node->GetLeft(), key, node));
    else if (std::get<0>(key)->GetId() >= std::get<0>(node->GetKey())->GetId())
        node->SetRight(InsertbyId(node->GetRight(), key, node));
    else
        return node;
    return Balance(node);
}
AVLNode* AVLTree::SearchbyId(Person* searched){
    return SearchbyId(Root, searched);
}
AVLNode* AVLTree::SearchbyId(AVLNode* node, Person* searched){
    if (!node){ 
        return nullptr;
    }
    if (std::get<0>(node->GetKey())->GetId() == searched->GetId()){
        return node;
    }
    else if (std::get<0>(node->GetKey())->GetId() > searched->GetId()){
        return SearchbyId(node->GetLeft(), searched);
    }
    else if (std::get<0>(node->GetKey())->GetId() < searched->GetId()){
        return SearchbyId(node->GetRight(), searched);
    }
    return nullptr;
}

void AVLTree::DeletebyComp(float valuetodelete){
    return DeletebyComp(Root, valuetodelete);
}
void AVLTree::DeletebyComp(AVLNode* node, float valuetodelete){
    AVLNode* nodetodelete = SearchbyComp(node, valuetodelete);
    if (!nodetodelete){
        return;
    }
    if (nodetodelete->GetLeft() == nullptr && nodetodelete->GetRight() == nullptr){
        if (nodetodelete->GetParent() != nullptr) {
            if (nodetodelete->GetParent()->GetLeft() == nodetodelete){
                nodetodelete->GetParent()->SetLeft(nullptr);
            }
            else{
                nodetodelete->GetParent()->SetRight(nullptr);
            }
        }
        else{
            Root = nullptr;
        }
        nodetodelete->SetParent(nullptr);
        return;
    }
    else if(nodetodelete->GetLeft() == nullptr){
        AVLNode* temp = nodetodelete->GetRight();
        if (nodetodelete->GetParent() != nullptr) {
            if (nodetodelete->GetParent()->GetLeft() == nodetodelete){
                nodetodelete->GetParent()->SetLeft(temp);
            }
            else{
                nodetodelete->GetParent()->SetRight(temp);
            }
        }
        else{
            Root = temp;
        }
        temp->SetParent(nodetodelete->GetParent());
        nodetodelete->SetParent(nullptr);
        return;
    }
    else if (nodetodelete->GetRight() == nullptr){
        AVLNode* temp = nodetodelete->GetLeft();
        if (nodetodelete->GetParent() != nullptr) {
            if (nodetodelete->GetParent()->GetLeft() == nodetodelete){
                nodetodelete->GetParent()->SetLeft(temp);
            }
            else{
                nodetodelete->GetParent()->SetRight(temp);
            }
        }
        else{
            Root = temp;
        }
        temp->SetParent(nodetodelete->GetParent());
        nodetodelete->SetParent(nullptr);
        return;
    }
    else{
        AVLNode* current = nodetodelete->GetRight();
        while (current->GetLeft() != nullptr){
            current = current->GetLeft();
        }
        nodetodelete->SetKey(current->GetKey());
        DeletebyComp(nodetodelete->GetRight(), std::get<1>(nodetodelete->GetKey()));
        return;
    }

    AVLNode* temp = nodetodelete->GetParent();
    while (temp != nullptr) {

        AVLNode* balanced = Balance(temp);
        
        if (balanced->GetParent() == nullptr)
            Root = balanced;

        temp = balanced->GetParent();
    }
    return;
}
AVLNode* AVLTree::Balance(AVLNode* node){
    node->UpdateHeight();
    node->UpdateBalance();
    if (!node) {
        return nullptr;
    }
    int balance = node->GetBalance();

    if (balance > 1 && node->GetLeft()->GetBalance() >= 0) {
        return RightRotate(node);
    }

    if (balance < -1 && node->GetRight()->GetBalance() <= 0) {
        return LeftRotate(node);
    }

    if (balance > 1 && node->GetLeft()->GetBalance() < 0) {
        node->SetLeft(LeftRotate(node->GetLeft()));
        return RightRotate(node);
    }

    if (balance < -1 && node->GetRight()->GetBalance() > 0) {
        node->SetRight(RightRotate(node->GetRight()));
        return LeftRotate(node);
    }
    return node;
}

AVLNode* AVLTree::GetRoot(){
    return Root;
}

void AVLTree::SetRoot(AVLNode* node){
    Root = node; 
}

void AVLTree::ReversedInorder(int& count){
    ReversedInorder(Root,count);
}
void AVLTree::ReversedInorder(AVLNode* node, int& count){
    if (!node){
        return;
    } 
    ReversedInorder(node->GetRight(), count);
    std::cout << (count++) << "º "<<std::get<0>(node->GetKey())->GetName() << " Match%: "<<std::get<1>(node->GetKey()) << "\n";
    ReversedInorder(node->GetLeft(), count);
}

std::vector<std::tuple <Person*,float>> AVLTree::ReversedInorderVector(){
    std::vector<std::tuple <Person*,float>> list;
    return ReversedInorderVector(Root,list);
}
std::vector<std::tuple <Person*,float>> AVLTree::ReversedInorderVector(AVLNode* node, std::vector<std::tuple <Person*,float>>& list){
    if (!node){
        return list;
    } 
    ReversedInorderVector(node->GetRight(),list);
    list.push_back(node->GetKey());
    ReversedInorderVector(node->GetLeft(),list);
    return list;
}