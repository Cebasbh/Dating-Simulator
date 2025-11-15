#include "HashTable.h"

HashTable::HashTable (int size){
    Size = size;
    Nkeys = 0;
    Bins = new HashEntry* [Size];
    for (int i = 0; i < Size; ++i)
        Bins[i] = nullptr;
}

HashTable::~HashTable(){
}

int HashTable::HashFunction(std::string key){
    int hash = 0;
    for (size_t i = 0; i < key.length(); ++i) {
        hash = (hash * 31 + key[i]) % Size;
    }
    return hash;
}
void HashTable::Rehash(){
    HashEntry** OldTable = Bins;
    int oldSize = Size;
    Size = Size * 2;
    Nkeys = 0;
    Bins = new HashEntry* [Size];
    for (int i = 0; i < Size; ++i){
        Bins[i] = nullptr;
    }
    int Count = 0;

    for (int i = 0; i < oldSize; i++) {
        if (OldTable[i] != nullptr && !OldTable[i]->GetIsDeleted()) {
            Insert(OldTable[i]->GetKey(), OldTable[i]->GetValue());
        }
    }
    
    delete[] OldTable;
}
bool HashTable::Insert(std::string key, Person* value){
    if (!value){
        return false;
    }
    int index = HashFunction(key);
    int count = 0;
    while (Bins[index] != nullptr && !Bins[index]->GetIsDeleted() && Bins[index]->GetKey() != key) {
        index = (index + 1) % Size;
        count++;
    }
    if (count == Size){
        return false;
    }
    if (Bins[index] == nullptr || Bins[index]->GetIsDeleted()) {
        delete Bins[index];
        Bins[index] = new HashEntry(key, value);
        Nkeys++;
    } else {
        Bins[index]->SetValue(value);
    }
    if (1.0 * Nkeys / Size >= 0.7f) {
        Rehash();
    }
    return true;
}    

Person* HashTable::Search(std::string key){
    int index = HashFunction(key);
    int count = 0;
    
    while (Bins[index] != nullptr && count < Size) {
        if (!Bins[index]->GetIsDeleted() && Bins[index]->GetKey() == key) {
            return Bins[index]->GetValue();
        }
        index = (index + 1) % Size;
        count++;
    }
    return nullptr; 
}

bool HashTable::Remove(std::string key) {
    int index = HashFunction(key);
    int count = 0;
    while (Bins[index] != nullptr && count < Size) {
        if (!Bins[index]->GetIsDeleted() && Bins[index]->GetKey() == key) {
            Bins[index]->SetIsDeleted(true);
            Nkeys--;
            return true;
        }
        index = (index + 1) % Size;
        count++;
    }
    return false;
}

void HashTable::Display(){
    for (int i = 0; i < Size; ++i) {
        std::cout << "[" << i << "]: ";
        if (Bins[i] == nullptr) {
            std::cout << "null";
        } else if (Bins[i]->GetIsDeleted()) {
            std::cout << "deleted";
        } else {
            std::cout << "(" << Bins[i]->GetKey() << ", " << Bins[i]->GetValue()->GetName() << ")";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
};
int HashTable::GetSize(){
    return Size;
}
int HashTable::GetNkeys(){
    return Nkeys;
}
HashEntry** HashTable::GetBins(){
    return Bins;
}
