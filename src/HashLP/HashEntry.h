#pragma once
#include <string>
#include <vector>
#include "Person/Person.h"

class HashEntry{
    private:
        std::string Key;
        Person* Value;
        bool IsDeleted;
    public:
        HashEntry(std::string k, Person* person);
        ~HashEntry();
        std::string GetKey();
        void SetValue(Person* newvalue);
        Person* GetValue();
        void SetIsDeleted(bool newstate);
        bool GetIsDeleted();
};