#include "HashEntry.h"

HashEntry::HashEntry(std::string k, Person* person) {
    Key = k;
    Value= person;
    IsDeleted = false;
}
HashEntry::~HashEntry(){
}
std::string HashEntry::GetKey(){
    return Key;
}
void HashEntry::SetValue(Person* newvalue){
    Value = newvalue;
}
Person* HashEntry::GetValue(){
    return Value;
}
void HashEntry::SetIsDeleted(bool newstate){
    IsDeleted = newstate;
}
bool HashEntry::GetIsDeleted(){
    return IsDeleted;
}