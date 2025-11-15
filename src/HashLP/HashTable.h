#pragma once
#include <iostream>
#include <string>
#include "HashEntry.h"

class HashTable {
private:
    HashEntry** Bins; 
    int Size;
    int Nkeys;
    int HashFunction(std::string key);
public:
    HashTable(int size = 5);
    ~HashTable();
    void Rehash();
    bool Insert(std::string key, Person* value);
    Person* Search(std::string key);
    bool Remove(std::string key);
    void Display();

    int GetSize();
    int GetNkeys();
    HashEntry** GetBins();
};