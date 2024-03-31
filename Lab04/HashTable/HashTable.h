#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>

template<typename ValueType>
class HashTable 
{
private:
    unsigned numberOfBuckets;
    struct Node 
    {
        Node* next;
        ValueType value;
        std::string key;
        Node() 
            : value(ValueType()), next(nullptr), key("") 
        {
        }
        Node(ValueType val, const std::string& k) 
            : value(val), next(nullptr), key(k) 
        {
        }
    };
    using List = Node*;
    List* hashTable;
    unsigned HashFunction(const std::string& key) const 
    {
        unsigned result = 0;
        for (char c : key) 
        {
            result += c;
        }
        return result % numberOfBuckets;
    }
public:
    HashTable() 
        : numberOfBuckets(5), hashTable(new List[5]) 
    {
        for (unsigned i = 0; i < numberOfBuckets; ++i) 
        {
            hashTable[i] = nullptr;
        }
    }
    HashTable(unsigned buckets) 
        : numberOfBuckets(buckets), hashTable(new List[buckets]) 
    {
        for (unsigned i = 0; i < numberOfBuckets; ++i) 
        {
            hashTable[i] = nullptr;
        }
    }
    HashTable(const HashTable& other) 
        : numberOfBuckets(other.numberOfBuckets) 
    {
        hashTable = new List[numberOfBuckets];
        for (unsigned i = 0; i < numberOfBuckets; ++i)
        {
            if (other.hashTable[i] == nullptr)
            {
                hashTable[i] = nullptr;
            }
            else
            {
                Node* hash = new Node();
                Node* thisHashTable = hash;
                Node* otherHashTable = other.hashTable[i];
                while (otherHashTable != nullptr)
                {
                    thisHashTable->next = new Node(otherHashTable->value, otherHashTable->key);
                    otherHashTable = otherHashTable->next;
                    thisHashTable = thisHashTable->next;
                }
                hashTable[i] = hash->next;
                delete hash;
            }
        }
    }
    HashTable& Add(const std::string& key, const ValueType& value) 
    {
        unsigned hashCode = HashFunction(key);
        if (hashTable[hashCode] == nullptr) 
        {
            hashTable[hashCode] = new Node(value, key);
        }
        else 
        {
            List addHere = hashTable[hashCode];
            while (addHere->next != nullptr && addHere->key != key) 
            {
                addHere = addHere->next;
            }
            if (addHere->key == key) 
            {
                throw std::runtime_error("Hash table already has this key");
            }
            addHere->next = new Node(value, key);
        }
        return *this;
    }
    void PrintTable() const 
    {
        for (unsigned i = 0; i < numberOfBuckets; ++i) 
        {
            List curr = hashTable[i];
            while (curr != nullptr) 
            {
                std::cout << std::setw(5) << "[" + std::to_string(HashFunction(curr->key)) + "]" << std::setw(20) << curr->key << std::setw(20) << curr->value << std::endl;
                curr = curr->next;
            }
        }
    }
    bool Has(const std::string& key) const 
    {
        unsigned hashCode = HashFunction(key);
        List correctList = hashTable[hashCode];
        while (correctList != nullptr) 
        {
            if (correctList->key == key) 
            {
                return true;
            }
            correctList = correctList->next;
        }
        return false;
    }
    ValueType& operator[](const std::string& key) 
    {
        unsigned hashCode = HashFunction(key);
        List correctList = hashTable[hashCode];
        while (correctList != nullptr) 
        {
            if (correctList->key == key) 
            {
                return correctList->value;
            }
            correctList = correctList->next;
        }
        throw std::runtime_error("Hash table has no such value");
    }
    ~HashTable() 
    {
        for (unsigned i = 0; i < numberOfBuckets; ++i) 
        {
            List current = hashTable[i];
            while (current != nullptr) 
            {
                List temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] hashTable;
    }
    void Resize(unsigned newNumberOfBuckets)
    {
        List* newHashTable = new List[newNumberOfBuckets];
        for (unsigned i = 0; i < newNumberOfBuckets; ++i)
        {
            newHashTable[i] = nullptr;
        }
        unsigned oldNumberOfBackets = numberOfBuckets;
        numberOfBuckets = newNumberOfBuckets;
        for (unsigned i = 0; i < oldNumberOfBackets; ++i)
        {
            Node* currRow = hashTable[i];
            // we have to add current row
            while (currRow != nullptr)
            {
                // add here
                if (newHashTable[HashFunction(currRow->key)] == nullptr)
                {
                    newHashTable[HashFunction(currRow->key)] = new Node(currRow->value, currRow->key);
                }
                else
                {
                    Node* curr = newHashTable[HashFunction(currRow->key)];
                    while (curr->next != nullptr)
                    {
                        curr = curr->next;
                    }
                    curr->next = new Node(currRow->value, currRow->key);
                }
                currRow = currRow->next;
            }
        }
        for (unsigned i = 0; i < oldNumberOfBackets; ++i)
        {
            List current = hashTable[i];
            while (current != nullptr)
            {
                List temp = current;
                current = current->next;
                delete temp;
            }
        }
        hashTable = newHashTable;
    }
    void Remove(const std::string& key)
    {
        Node* curr = hashTable[HashFunction(key)];
        while (curr != nullptr)
        {
            if (curr->key == key && hashTable[HashFunction(key)] == curr)
            {
                // first 
                hashTable[HashFunction(key)] = hashTable[HashFunction(key)]->next;
                delete curr;
                return;
            }
            else if (curr->next != nullptr && curr->next->key == key)
            {
                Node* victim = curr->next;
                curr->next = curr->next->next;
                delete victim;
                return;
            }
            curr = curr->next;
        }
        throw(std::runtime_error("HashTable has no such value"));
    }
    bool IsEmpty()
    {
        for (unsigned i = 0; i < numberOfBuckets; ++i)
        {
            if (hashTable[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }
};
