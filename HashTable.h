/**
 * HashTable.h
 */
#include <optional>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

//the enum class to store the status's of the buckets
enum class bucketStatusEnum {Normal, EmptySinceStart, EmptyAfterRemoval};

class HashTableBucket {

public:
    bucketStatusEnum bucketStatus;
    std::string key;
    size_t value;

    HashTableBucket();
    HashTableBucket(string key, int value);

    void load(string key, int value);

    bool isEmpty() const;

    //Print the bucket's contents
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket) {

    }

};

class HashTable {
private:

    public:
    size_t initCapacity;
    string key;
    //variable for keeping the buckets
    size_t bucketCount;
    //vector for the buckets
    std::vector<HashTableBucket> vectorTable;
    //vector for the random number offsets
    std::vector<size_t> offsets;




    //parameterized constructor
    HashTable(size_t initCapacity = 8);

    bool insert(std::string key, size_t value);

    bool remove(std::string key);

    bool contains(const std::string& key) const;

    optional<int> get(const string& key) const;

    size_t& operator[](const string& key);

    vector<string> keys() const;

    double alpha() const;

    size_t capacity() const;

    size_t size() const;

    size_t probeFull(size_t keySum);

    //prints the contents of our hash table using normal syntax
    //cout <<
    //Should only print buckets which are occupied
    //Each item will print which bucket the item is in
    //Can make a printMe() helper method
    friend ostream& operator<<(ostream& os, const HashTable& hashtable) {
        //sets the keys vector to the bucketList since keys already has the filled buckets
        //clion auto generated it
        std:vector<std::string> bucketList = hashtable.keys();
        //variables for keeping track of the index and value
        size_t valueVar = 0;
        size_t indexVar  = 0;
        for (size_t i = 0; i < bucketList.size(); i++) {
            //gets bucket key
            std::string currentBucket = bucketList[i];


        }
    }
};



