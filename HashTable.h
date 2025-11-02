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

    optional<int> get(const string& key) const;

    int& operator[](const string& key);

    vector<string> keys() const;

    double alpha() const;

    size_t capacity() const;

    size_t size() const;

    friend ostream& operator<<(ostream& os, const HashTable& hashtable) {

    }
};

class HashTableBucket {
    public:

    HashTableBucket();
    HashTableBucket(string key, int value);

    void load(string key, int value);

    bool isEmpty() const;


    friend ostream& operator<<(ostream& os, const HashTableBucket& hashtable) {

    }
};