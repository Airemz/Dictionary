#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>

//dynamic array where indices are tokens corresponding to words
class Vector{

    public:
        std::vector<std::string> *array;
    
    Vector();
    ~Vector();

};

// Transform word to hashvalue and store in dynamic array of linked lists
class HashMap {

    private:
        
        //bool empty_dictionary;
        unsigned int size_m;
        unsigned int key_value_pairs;
        
        std::list<std::pair<std::string,int>> *table;


    public:
        HashMap(unsigned int input_size);
        ~HashMap();
        double load_factor;
        
        unsigned hash(const std::string & str);
        bool hashmap_insert(std::string key, unsigned int token);
        int hashmap_search(std::string word);
        void hashmap_expand();
        std::string hashmap_print(unsigned int k);
    
        // print for(pair item: T[hash value])
        // if (item.first == word)

    // [ "" | w1 | w2 |   |   |   ] asssume size == number of elements

};

class Dictionary{

    private:

        HashMap *dictionary_hashmap;
        Vector *dictionary_vector;
        
    // insert using both hashtable and vector
    // insert hashmap(word, v.size()) // v.size is the potential index/token for the word to be inserted
        
    public:
    
        Dictionary();
        ~Dictionary();

        
        void create(unsigned int size);
        bool insert(std::string word);
        int tok(std::string word);
        std::string ret(unsigned int token);
        int tok_all(std::string multiple_words);
        std::string ret_all(unsigned int multiple_tokens);
        std::string print (unsigned int k);



};
