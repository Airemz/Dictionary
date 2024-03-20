#include <iostream>
#include <string>
#include <vector>

class TokensToWords{

    
    std::vector<int> resizable_array;

};

class HashTable {

    private:
        
        bool empty_dictionary;

    public:
        HashTable(int m);
        ~HashTable();

        unsigned hash(const std::string & str);



};
