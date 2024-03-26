#include "tokenize.h"
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <vector>
#include <algorithm>

//////////////////////////////////////////////////////
/////////////// Vector Member Functions //////////////
//////////////////////////////////////////////////////

// Constructor: create the vector of strings and push an empty string into the first index so that our tokens correspond with the words, i.e, first word inserted is token 1 instead of 0
Vector::Vector(){
    array = new std::vector<std::string>;
    array->push_back("");
}

// Destructor: simply delete the array, no need to do anything else
Vector::~Vector(){
    delete array;
}

//////////////////////////////////////////////////////
/////////////// HashMap Member Functions /////////////
//////////////////////////////////////////////////////

// Constructor: initialize the public and private variables and create the table of passed size
HashMap::HashMap(unsigned int &input_size){
    
    size_m = input_size;
    table = new std::list<std::pair<std::string, int>> [size_m];
    
    key_value_pairs = 0;
    load_factor = 0.0;
    
}

// Destructor: delete the table which is an array of linked lists thus using []
HashMap::~HashMap(){
    delete[] table;
}

// Hash function as provided in manual
unsigned HashMap::hash(const std::string & str) {
    unsigned ans = 0;
    for (auto it = str.begin(); it != str.end(); ++it)
    ans = ans * 29 + *it;
    return ans % size_m;
}


bool HashMap::hashmap_insert(std::string &key, unsigned int &token){

    // Find the hash value(index) in our hashmap which corresponds to a linked list
    unsigned int hash_value = hash(key);

    // Itterate through the pairs at that linked list checking if the word already exists
    // Pass by reference minimizing time complexity
    for (auto &pair : table[hash_value]){
        if (pair.first == key){
            return false;
        }
    }

    // If the word does not exist, then push a pair of the word and corresponding token at the front of the linked list at its appropriate index (external chaining)
    table[hash_value].push_front(std::make_pair(key, token));

    // Updating the load factor using stact_cast so that the precision is accurate
    key_value_pairs++;
    load_factor = static_cast<double>(key_value_pairs) / static_cast<double>(size_m);
    return true;
}

int HashMap::hashmap_search(std::string &word){

    // Find the hash value(index) in our hashmap which corresponds to a linked list
    unsigned int hash_value = hash(word);
    
    // Itterate through the pairs at that linked list checking if the word exists, if so return the associated token
    // Pass by reference minimizing time complexity
    for (auto &pair : table[hash_value]){
        if (pair.first == word){
            return pair.second;
        }
    }
    
    // If the word is not in our hashmap return -1, as stated in the lab manual
    return -1;
}

void HashMap::hashmap_expand(){

    // Maintain the old size and update the size of our new table
    unsigned int old_size = size_m;
    size_m = size_m * 2;

    // Create a new table which will be double the size of our previous table
    std::list<std::pair<std::string,int>> *new_table;
    new_table = new std::list<std::pair<std::string,int>> [size_m];

    // Itterate through all the indices and pairs of our old table and rehash them into our new table
    for (unsigned int index = 0; index < old_size; index++){
        for (auto& pair : table[index]){
            unsigned int hash_value = hash(pair.first);
            new_table[hash_value].push_front(std::make_pair(pair.first, pair.second));
        }
    }

    // Delete the old table and set our table to the newly created table
    delete[] table;
    table = new_table;
    new_table = nullptr;
}

std::string HashMap::hashmap_print(unsigned int &k){

    // Initialize an empty array and check if the specified index is out of bounds
    std::string output;
    if (k >= size_m){return output;}

    // Itterate through all the pairs at that index adding the words to the output followed by an empty space
    std::string &output_all = output;
    for (auto pair : table[k]){
        output_all += pair.first + " ";
    }

    return output_all;
}


//////////////////////////////////////////////////////
/////////////// Dictionary Member Functions //////////
//////////////////////////////////////////////////////

// Constructor: initializing to nullptrs as they will be set in create
Dictionary::Dictionary(){
    dictionary_hashmap = nullptr;
    dictionary_vector = nullptr;
}

// Destructor: call the appropriate function destructors
Dictionary::~Dictionary(){
    delete dictionary_hashmap;
    delete dictionary_vector;
}

// Call the appropriate function constructors
void Dictionary::create(unsigned int &size){

    dictionary_hashmap = new HashMap(size);
    dictionary_vector = new Vector();
}

bool Dictionary::insert(std::string& word){

    // Check if the word contains non_alphabetic characters
    if (!std::all_of(word.begin(), word.end(), ::isalpha)) {
        return false;
    }

    // Initialize our token variable since the function is pass by reference
    // The token is the last element in our array, since we added an empty string, we do not need to subtract by 1
    unsigned int token = dictionary_vector->array->size();
    
    // Check if the load factor has been exceeded before insertion
    if (dictionary_hashmap->load_factor >= 0.8){dictionary_hashmap->hashmap_expand();}

    // Insert the word into the hashmap, if unable to, if statement will be false
    if (dictionary_hashmap->hashmap_insert(word, token)){

        // Insert the word into the vector
        dictionary_vector->array->push_back(word);
        
        return true;
    }

    else{return false;}
}

// To return the token, simply call the search function
int Dictionary::tok(std::string &word){
    return dictionary_hashmap->hashmap_search(word);
}

// To return the word, return the word at the specified token which corresponds to the index in our vector
std::string Dictionary::ret(unsigned int &token){

    // First check if the specified token is out of bounds
    if (token >= dictionary_vector->array->size()){return "N/A";}
    return dictionary_vector->array->at(token);
}

// Print the words at provided index using the helper hashmap function
std::string Dictionary::print(unsigned int &k){
    return dictionary_hashmap->hashmap_print(k);
}

