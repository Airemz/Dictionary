#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>

// Dynamic array of strings where indices are tokens corresponding to words
class Vector{

    public:
        // Pointer to first element in the vector
        std::vector<std::string> *array;

        // Constructor / Destructor
        Vector();
        ~Vector();

};

// Array of linked lists consisting of pairs of the words and tokens
class HashMap {

    private:
        
        // Useful varaibles when creating, inserting and expanding the hashmap
        unsigned int size_m;
        unsigned int key_value_pairs;
        
        // Pointer to the first element (linked list)
        std::list<std::pair<std::string,int>> *table;


    public:

        // Constructor / Destructor
        HashMap(unsigned int &input_size);
        ~HashMap();

        // Public load factor so our dictionary class can access
        double load_factor;

        // Essential hashmap member functions called by dictionary class
        // Pass by reference to minimize time complexity
        unsigned hash(const std::string & str);
        bool hashmap_insert(std::string &key, unsigned int &token);
        int hashmap_search(std::string &word);
        void hashmap_expand();
        std::string hashmap_print(unsigned int &k);
};

class Dictionary{

    private:
        
        // Pointers to a hashmap and vector class
        HashMap *dictionary_hashmap;
        Vector *dictionary_vector;
        
    public:

        // Constructor / Destructor
        Dictionary();
        ~Dictionary();

        // Member functions called by user commands
        // Pass by reference to minimize time complexity
        void create(unsigned int &size);
        bool insert(std::string &word);
        int tok(std::string &word);
        std::string ret(unsigned int &token);
        std::string print (unsigned int &k);



};
