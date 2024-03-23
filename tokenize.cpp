#include "tokenize.h"
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <vector>
#include <regex>

Vector::Vector(){
    array = new std::vector<std::string>;
    array->push_back("");
}

Vector::~Vector(){
    std::vector<std::string>().swap(*array);
}

HashMap::HashMap(unsigned int input_size){
    
    size_m = input_size;
    table = new std::list<std::pair<std::string, int>> [size_m];
    
    key_value_pairs = 0;
    load_factor = 0;
    
}

HashMap::~HashMap(){
    delete[] table;
}

unsigned HashMap::hash(const std::string & str) {
    unsigned ans = 0;
    for (auto it = str.begin(); it != str.end(); ++it)
    ans = ans * 29 + *it;
    return ans % size_m;
}

bool HashMap::hashmap_insert(std::string key, unsigned int token){
     
    unsigned int hash_value = hash(key);

    for (auto pair : table[hash_value]){
        if (pair.first == key){
            return false;
        }
    }

    table[hash_value].push_back(std::make_pair(key, token));
    key_value_pairs++;
    load_factor = key_value_pairs/size_m;
    return true;
}


int HashMap::hashmap_search(std::string word){
    unsigned int hash_value = hash(word);
    
    for (auto pair : table[hash_value]){
        if (pair.first == word){
            return pair.second;
        }
    }
    
    return -1;
}

void HashMap::hashmap_expand(){

    unsigned int old_size = size_m;
    size_m = size_m * 2;
    std::list<std::pair<std::string,int>> *old_table = table;
    table = new std::list<std::pair<std::string,int>> [size_m];

    for (unsigned int index = 0; index < old_size; index++){
        for (auto pair : old_table[index]){
            unsigned int hash_value = hash(pair.first);
            table[hash_value].push_back(std::make_pair(pair.first, pair.second));
        }
    }

    delete[] old_table;
    old_table = nullptr;
    
}

std::string HashMap::hashmap_print(unsigned int k){

    std::string output;
    if (k >= size_m){return output;}

    for (auto pair : table[k]){
        output += pair.first + " ";
    }

    return output;

}

Dictionary::Dictionary(){
    dictionary_hashmap = nullptr;
    dictionary_vector = nullptr;
}

Dictionary::~Dictionary(){
    delete dictionary_hashmap;
    delete dictionary_vector;
}

void Dictionary::create(unsigned int size){

    dictionary_hashmap = new HashMap(size);
    dictionary_vector = new Vector();
    
}

bool Dictionary::insert(std::string word){
    if(!std::regex_match(word, std::regex("^[A-Za-z]+$"))){
        return false;
    }
    
    else if (dictionary_hashmap->hashmap_insert(word, dictionary_vector->array->size())){
        dictionary_hashmap->hashmap_insert(word, dictionary_vector->array->size());
        dictionary_vector->array->push_back(word);
        if (dictionary_hashmap->load_factor >= 0.8){dictionary_hashmap->hashmap_expand();}

        
        return true;
    }

    else{return false;}
}

int Dictionary::tok(std::string word){
    return dictionary_hashmap->hashmap_search(word);
}

std::string Dictionary::ret(unsigned int token){
    if (token >= dictionary_vector->array->size()){return "N/A";}
    return dictionary_vector->array->at(token);
}

std::string Dictionary::print (unsigned int k){
    return dictionary_hashmap->hashmap_print(k);
}

