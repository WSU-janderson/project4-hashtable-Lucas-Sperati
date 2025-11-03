/**
 * HashTable.cpp
 */

#include "HashTable.h"
#include <iostream>
#include <exception>
#include <filesystem>
#include <vector>


using namespace std;


//constructor. sets the vectorTable to the initCapacity
//and sets bucket count to 0
HashTable::HashTable(size_t initCapacity) {
    this->initCapacity = initCapacity;
    //vector function that changes the size of the vector to
    //the initCapacity
    vectorTable.resize(initCapacity);
    bucketCount = 0;

    //makes the offsets vector ----
    //makes a tempVector
    std::vector<size_t> tempVector;
    //makes the temp vector however big initCapacity is - 1 since you don't include
    //0 or the capacity
    for (size_t i = 0; i < initCapacity; i++) {
        tempVector.push_back(i);
    }
    //randomly adds all values from the temp vector to offsets and then erases tempVector
    //% tempVector.size() since tempVector gets deleted and won't match the initCapacity
    for (size_t i = 0; i < initCapacity; i++) {
        offsets.push_back(tempVector[rand() % tempVector.size()]);
        tempVector.erase(tempVector.begin() + rand() % tempVector.size());
    }
}

//uses offsets to probe the table checking for empty buckets
size_t HashTable::probeEmpty(size_t keySum) {
    //gets the initCapacity
    size_t initCapacityVar = this->initCapacity;
    //gets the first random bucket
    size_t randomBucket = keySum + offsets[0] % initCapacityVar;
    //checks each other randomBucket until you find one that is empty
     for (size_t i = 1; !this->vectorTable[randomBucket].isEmpty(); i++) {
         //sets the randomBucket to the next offset
        randomBucket = keySum + offsets[i] % initCapacityVar;
    }
    //once found, returns randomBucket
    return randomBucket;
}

//todo
//Inserts a new key-value pair into the table. Duplicate keys are
//not allowed. The method should return true if the insertion was successful.
//If the insert was unsuccessful, such as when a duplicate is
//attempted to be inserted, the method should return false.
bool HashTable::insert(std::string key, size_t value) {
    size_t keySum = 0;
    for (int j = 0; j < key.size(); j++) {
        //key[j] takes the character of key at j and adds its value to keySum
        keySum += key[j];
    }
    size_t address = probeEmpty(keySum);
    HashTableBucket bucket = this->vectorTable[address];
    bucket.load(key, value);
    return true;
}

//If the key is in the table, remove will "erase" the key-value
//pair from the table. Marks a bucket as empty-after-remove
bool HashTable::remove(std::string key) {

}

//returns true if the key is in the table and false if the key
//is not in the table
bool HashTable::contains(std::string& key) const {

}

//if the key is found in the table, will return the value
//associated with that key. If the key is not in the table, will
//return nullopt. The find method returns an optional<int>.
std::optional<int> HashTable::get(const string& key) const {

}

//access values in the map using a familiar syntax.
//for ex. int idNum = hashTable["james]"
//unlike get the bracker operator returns a reference to the value,
//which allows assignment:
//hashTable["James"] = 1234;
//If the key is not in the table, returning a valid reference is
//impossible. Do not need to address attempts to
//access keys not in the table inside the bracket operator method.
int& HashTable::operator[](const string& key) {

}

//todo
//key returns a std::vector with all of the keys currently in the table.
//The length of the vector should be the same as the size of the hash
//table
std::vector<string> HashTable::keys() const {
    std::vector<string> keys;

    for (size_t i = 0; i < initCapacity; i++) {
        if (!vectorTable.empty()) {
            //keys.push_back(vectorTable[i]);
        }
    }
    return keys;
}

//use cast to avoid integer division
//ex. static_cast<double>(num)
//the time complexity for this method must be O(1)
//when this reaches or exceeds 0.5 it should double
//the size of the vector
double HashTable::alpha() const {

}

//capacity returns how many buckets in total are in the hash table.
//The time complexity for this must be O(1)
size_t HashTable::capacity() const {

}

//Size returns how many key-value pairs are in the hash table
//Time complexity must be O(1)
size_t HashTable::size() const {

}

//---------------------------------------------------------

//default constructor sets bucket type to ESS
HashTableBucket::HashTableBucket() {
    bucketStatus = EmptySinceStart;
    key = "";
    value = 0;
}

//parameterized constructor that initializes the key and value
//and sets the bucket type to normal
HashTableBucket::HashTableBucket(string key, int value) {
    bucketStatus = Normal;
    this->key = key;
    this->value = value;
}

//Loads the key-value pair into the bucket, which should then
//also mark the bucket as normal
void HashTableBucket::load(string key, int value) {
    bucketStatus = Normal;
    this->key = key;
    this->value = value;
}

//returns whether the bucket is empty, regardless of if has had
//data placed in it or not
bool HashTableBucket::isEmpty() const {
    //if the bucket is ESS or EAR then returns true, else returns false
    if (bucketStatus == EmptySinceStart || bucketStatus == EmptyAfterRemoval) {
        return true;
    }
    else {
        return false;
    }
}
