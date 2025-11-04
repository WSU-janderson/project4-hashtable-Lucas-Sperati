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
    srand(time(nullptr));
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

//uses offsets to probe the table checking for full buckets
size_t HashTable::probeFull(size_t keySum) {
    //gets the initCapacity
    size_t initCapacityVar = this->initCapacity;
    //i to avoid infinite loops
    size_t i = 0;
    //runs for however long initCapacityVar is
    while (i < initCapacityVar) {
        //gets the bucket
        size_t bucket = (keySum + offsets[i]) % initCapacityVar;
        //if the bucket is normal then it returns that bucket
        if (vectorTable[bucket].bucketStatus == bucketStatusEnum::Normal) {
            return bucket;
        }
        i++;
    }//returns initCapacityVar if nothing is found
    return initCapacityVar;
}


//Inserts a new key-value pair into the table. Duplicate keys are
//not allowed. The method should return true if the insertion was successful.
//If the insert was unsuccessful, such as when a duplicate is
//attempted to be inserted, the method should return false.
bool HashTable::insert(std::string key, size_t value) {
    if (alpha() >= 0.5) {
        //backs up the old vector by setting the table, offsets, keys, and initial
        //capacity to old variables
        std::vector<HashTableBucket> oldList = vectorTable;
        std::vector<size_t> oldOffsets = offsets;
        std::vector<std::string> oldKeys = this->keys();
        size_t oldInitCapacity = initCapacity;

        //increases the size of the table by 2
        initCapacity = initCapacity * 2;
        //clears the old vectorTable
        vectorTable.clear();
        //resizes the vector table to the new size
        vectorTable.resize(initCapacity);
        //clears the offsets
        offsets.clear();
        //sets bucket count back to 0
        bucketCount = 0;


        //makes a newNums vector with the initCapacity
        std::vector<size_t> newNums(initCapacity);
        //adds numbers to the new size to newNums
        for (size_t i = 0; i < initCapacity; i++) {
            newNums[i] = i;
        }
        //randomly adds the new numbers to offsets and then removes the newNums vector
        for (size_t i = 0; i < initCapacity; i++) {
            size_t numberVar = rand() % newNums.size();
            offsets.push_back(newNums[numberVar]);
            newNums.erase(newNums.begin() + numberVar);
        }

        //runs the hash for the new table
        for (const std::string& key : oldKeys) {//O(n^3)
            size_t keySum = 0;
            for (int j = 0; j < key.size(); j++) {
                //key[j] takes the character of key at j and adds its value to keySum
                keySum += key[j];
            }

            //this for loop gets the old bucket with that key
            for (size_t i = 0; i < oldInitCapacity; i++) {//o(n^2)
                size_t address = (keySum + oldOffsets[i]) % oldInitCapacity;
                HashTableBucket& bucket = oldList[address];
                if (bucket.key == key) {
                    //adds the bucket to the new vector
                    //uses j since i is used
                    for (size_t j = 0; j < initCapacity; j++) { //o(n)
                        size_t addressNew = (keySum + offsets[j]) % initCapacity;
                        HashTableBucket& newBucket = vectorTable[addressNew];
                        //double checks to make sure the bucket is empty
                        if (newBucket.isEmpty()) {
                            newBucket.load(bucket.key, bucket.value);
                            bucketCount++;
                            break;
                        }
                    }//breaks once it gets done with key twice and goes back to the for each key loop
                    break;
                }
            }
        }
    }

    //changes made to insert from when it was fucked:
    //changed the rand offset function. I'm pretty sure it was originally randomly adding and removing elements so it would
    //never end.
    //The offset vector was accidentally resizing to the new length and then pushing back values afterward which made it too big
    //got that from watching youtube videos and decided to change, forgot to push between changing the rand and changing the
    //offset vector. I don't know which solved the infinite loop but I have 8 minutes left to turn this in so I don't have
    //time to test it.


    size_t keySum = 0;
    //for loop to get the hash of the key using the characters
    for (int j = 0; j < key.size(); j++) {
        //key[j] takes the character of key at j and adds its value to keySum
        keySum += key[j];
    }
    //variable to keep track of initCapacity and probe with it
    size_t initCapacityVar = this->initCapacity;
    //for loop that probes through the vector. It gets a bucket, checks if its
    //normal since it would have valid data and if the key matches the inserted key
    for (size_t i = 0; i < initCapacityVar; i++) {
        //gets the address using the offsets
        size_t address = (keySum + offsets[i]) % initCapacityVar;
        //gets that bucket and adds it to the variable bucket
        HashTableBucket& bucket = vectorTable[address];

        //if the status of that bucket is normal and the keys are the same it returns false
        if (bucket.bucketStatus == bucketStatusEnum::Normal && bucket.key == key) {
            return false;
        }
        //else if the bucket is empty it loads the key and the value and returns true, and it increases
        //bucketCount by one
        if (bucket.isEmpty()) {
            bucket.load(key, value);
            bucketCount = bucketCount + 1; // track how many key-value pairs exist
            return true;
        }
    }
    return false;
}

//If the key is in the table, remove will "erase" the key-value
//pair from the table. Marks a bucket as empty-after-remove
bool HashTable::remove(std::string key) {
    size_t keySum = 0;
    //for loop to get the hash of the key using the characters
    for (int j = 0; j < key.size(); j++) {//O(n)
        //key[j] takes the character of key at j and adds its value to keySum
        keySum += key[j];
    }
    //variable for the initCapacity
    size_t initCapacityVar = this->initCapacity;
    //checks if there is a full bucket in the vector, if there isn't it returns false
    size_t bucketTest = probeFull(keySum);
    if (bucketTest == initCapacityVar) {
        return false;
    }

    //if there is a full bucket then it will probe for the key
    for (size_t i = 0; i < initCapacityVar; i++) { //O(n)
        //gets bucket stuff for probing
        size_t address = (keySum + offsets[i]) % initCapacity;
        HashTableBucket& bucket = vectorTable[address];

        //if the bucket is normal and the key matches
        if (bucket.bucketStatus == bucketStatusEnum::Normal && bucket.key == key) {
            //sets the key to null
            bucket.key = "";
            //sets the value to 0
            bucket.value = 0;
            //sets the status to EAR
            bucket.bucketStatus = bucketStatusEnum::EmptyAfterRemoval;
            //decreases the bucket count by one
            bucketCount = bucketCount - 1;
            //if it works it returns true
            return true;
        }
    }
    //if the key is never found then it returns false
    return false;
}

//returns true if the key is in the table and false if the key
//is not in the table
bool HashTable::contains(const std::string& key) const {
    size_t keySum = 0;
    //for loop to get the hash of the key using the characters
    for (int j = 0; j < key.size(); j++) {
        //key[j] takes the character of key at j and adds its value to keySum
        keySum += key[j];
    }
    //variable for the initCapacity
    size_t initCapacityVar = this->initCapacity;

    //same ol same ol for probing.
    for (size_t i = 0; i < initCapacityVar; i++) {
        size_t address = (keySum + offsets[i]) % initCapacityVar;
        const HashTableBucket& bucket = vectorTable[address];
        //if the bucket is normal and the keys are the same then it returns true
        if (bucket.bucketStatus == bucketStatusEnum::Normal && bucket.key == key) {
            return true;
        }
    }
    //returns false if the bucket is not found
    return false;
}

//if the key is found in the table, will return the value
//associated with that key. If the key is not in the table, will
//return nullopt. The find method returns an optional<int>.
//basically same code from contains
std::optional<int> HashTable::get(const string& key) const {
    size_t keySum = 0;
    //for loop to get the hash of the key using the characters
    for (int j = 0; j < key.size(); j++) {
        //key[j] takes the character of key at j and adds its value to keySum
        keySum += key[j];
    }
    //variable for the initCapacity
    size_t initCapacityVar = this->initCapacity;

    //same ol same ol for probing.
    for (size_t i = 0; i < initCapacityVar; i++) {
        size_t address = (keySum + offsets[i]) % initCapacityVar;
        const HashTableBucket& bucket = vectorTable[address];
        //if the bucket is normal and the keys are the same then it returns true
        if (bucket.bucketStatus == bucketStatusEnum::Normal && bucket.key == key) {
            return bucket.value;
        }
    }
    //returns false if the bucket is not found
    return nullopt;
}


//access values in the map using a familiar syntax.
//for ex. int idNum = hashTable["james]"
//unlike get the bracker operator returns a reference to the value,
//which allows assignment:
//hashTable["James"] = 1234;
//If the key is not in the table, returning a valid reference is
//impossible. Do not need to address attempts to
//access keys not in the table inside the bracket operator method.
//stole code from get to make this
size_t& HashTable::operator[](const string& key) {
    size_t keySum = 0;
    //for loop to get the hash of the key using the characters
    for (int j = 0; j < key.size(); j++) {
        //key[j] takes the character of key at j and adds its value to keySum
        keySum += key[j];
    }
    //variable for the initCapacity
    size_t initCapacityVar = this->initCapacity;

    //same ol same ol for probing.
    for (size_t i = 0; i < initCapacityVar; i++) {
        size_t address = (keySum + offsets[i]) % initCapacityVar;
        HashTableBucket& bucket = vectorTable[address];
        //if the bucket is normal and the keys are the same then it returns true
        if (bucket.bucketStatus == bucketStatusEnum::Normal && bucket.key == key) {
            return bucket.value;
        }
    }

}


//key returns a std::vector with all of the keys currently in the table.
//The length of the vector should be the same as the size of the hash
//table
std::vector<string> HashTable::keys() const {
    //makes a temp vector of keys
    std::vector<string> keys;
    for (size_t i = 0; i < initCapacity; i++) {
        //adds each bucket to the bucket variable
        const HashTableBucket& bucket = vectorTable[i];
        //if the bucket is normal then it adds the key to the keys vector
        if (bucket.bucketStatus == bucketStatusEnum::Normal) {
            keys.push_back(bucket.key);
        }
    }
    //finally returns the key
    return keys;
}

//use cast to avoid integer division
//ex. static_cast<double>(num)
//the time complexity for this method must be O(1)
//when this reaches or exceeds 0.5 it should double
//the size of the vector
double HashTable::alpha() const {
    //gets the bucketCount and initCapacity and sets them to variables using static_cast
    //and the divides them to get the alpha value and returns alpha
    double alpha = 0;
    double bucketCountVar = static_cast<double>(bucketCount);
    double capacityVar = static_cast<double>(initCapacity);
    alpha = bucketCountVar / capacityVar;
    return alpha;
}

//capacity returns how many buckets in total are in the hash table.
//The time complexity for this must be O(1)
size_t HashTable::capacity() const {
    return initCapacity;
}

//Size returns how many key-value pairs are in the hash table
//Time complexity must be O(1)
size_t HashTable::size() const {
    return bucketCount;
}

//---------------------------------------------------------

//default constructor sets bucket type to ESS
HashTableBucket::HashTableBucket() {
    bucketStatus = bucketStatusEnum::EmptySinceStart;
    key = "";
    value = 0;
}

//parameterized constructor that initializes the key and value
//and sets the bucket type to normal
HashTableBucket::HashTableBucket(string key, int value) {
    bucketStatus = bucketStatusEnum::Normal;
    this->key = key;
    this->value = value;
}

//Loads the key-value pair into the bucket, which should then
//also mark the bucket as normal
void HashTableBucket::load(string key, int value) {
    bucketStatus = bucketStatusEnum::Normal;
    this->key = key;
    this->value = value;
}

//returns whether the bucket is empty, regardless of if has had
//data placed in it or not
bool HashTableBucket::isEmpty() const {
    //if the bucket is ESS or EAR then returns true, else returns false
    if (bucketStatus == bucketStatusEnum::EmptySinceStart || bucketStatus == bucketStatusEnum::EmptyAfterRemoval) {
        return true;
    }
    else {
        return false;
    }
}