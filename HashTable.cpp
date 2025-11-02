/**
 * HashTable.cpp
 */

#include "HashTable.h"
#include <iostream>
#include <exception>
#include <filesystem>


using namespace std;

//constructor
HashTable::HashTable(size_t initCapacity) {

}

//Inserts a new key-value pair into the table. Duplicate keys are
//not allowed. The method should return true if the insertion was successful.
//If the insert was unsuccessful, such as when a duplicate is
//attempted to be inserted, the method should return false.
bool HashTable::insert(std::string key, size_t value) {

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
//If the key is not in the tavle, returning a valid reference is
//impossible. Do not nneed to address attempts to
//access keys not in the table inside the bracket operator method.
int& HashTable::operator[](const string& key) {

}

//key returns a std::vector with all of the keys currently in the table.
//The length of the vector should be the same as the size of the hash
//table
std::vector<string> HashTable::keys() const {

}

//alpha returns the current suze of the table.
//use cast to avoid integer division
//ex. static_cast<double>(num)
//the time complexity for this method must be O(1)
double HashTable::alpha() const {

}

//capacity returns how many buckets in total are in the hash table.
//The time complexity for this must be O(1)
size_t HashTable::capacity() const {

}

//Suze returns how many key-value pairs are in the hash table
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

}

//returns whether the bucket is empty, regardless of if has had
//data placed in it or not
bool HashTableBucket::isEmpty() const {

}
