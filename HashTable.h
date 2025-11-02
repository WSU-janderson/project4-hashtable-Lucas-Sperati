/**
 * HashTable.h
 */
#include <optional>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

class HashTable {
    public:
    size_t initCapacity;
    string key;
    size_t value;

    //parameterized constructor
    HashTable(size_t initCapacity = 8);

    bool insert(std::string key, size_t value);

    bool remove(std::string key);

    bool contains(std::string& key) const;


};

class hashTableBucket {
    public:
};