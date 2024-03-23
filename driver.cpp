// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "tokenize.h"

//./spellcheck.out < inputs/test01.in > my_outputs/mtest01.out
// Add -g to cxxflags in make file
//valgrind --leak-check=full --show-leak-kinds=all ./spellcheck.out <inputs/test03.in 

// see istringstream to parse inputs

int main(){

    Dictionary *unnecesarily_heavy_book = new Dictionary;

    while (true){

        // load not working + comments + static cast 

        // Receive User input
        std::string user_input, command, parameter;
        std::getline(std::cin, user_input);
        std::istringstream iss(user_input);
        iss >> command >> parameter;
        
        // Call appropriate functions based on input

        // Load: Open given file and extract words until end. Output success after.
        if (command == "create") {

            unnecesarily_heavy_book->create(std::stoi(parameter));
            std::cout << "success" << std::endl;
        }

        // Exit: calls clear function, then call the destructor to delete the root
        else if (command == "insert") {

            if(unnecesarily_heavy_book->insert(parameter)){

                unnecesarily_heavy_book->insert(parameter);
                std::cout << "success" << std::endl;
            } 
            
            else{std::cout << "failure" << std::endl;}

        }

        // 
        else if (command == "load") {
            std::ifstream file(parameter);
            bool flag;

            std::string word;
            while (file >> word){
                if(unnecesarily_heavy_book->insert(word)){flag = true;}
                unnecesarily_heavy_book->insert(word);
            }
            
            if (flag == true){std::cout << "success" << std::endl;}
            else{std::cout << "failure" << std::endl;}
        }

        // Clear: delete all the words in the trie,
        else if (command == "tok") {
            std::cout << unnecesarily_heavy_book->tok(parameter) << std::endl;
        }

        // Insert: extract the word from input and add the word to the tree if possible
        else if (command == "ret") {
            std::cout << unnecesarily_heavy_book->ret(std::stoi(parameter)) << std::endl;
        }

        // Prefix: extract word and check how many words its a prefix for
        else if (command == "tok_all") {
            std::cout << unnecesarily_heavy_book->tok(parameter) << " ";

            while (iss >> parameter){
                std::cout << unnecesarily_heavy_book->tok(parameter) << " ";
            }

            std::cout << std::endl;
        }

        // Erase: extract word from input and delete it from the trie reccursivly
        else if (command == "ret_all") {
            std::cout << unnecesarily_heavy_book->ret(std::stoi(parameter)) << " ";

            while (iss >> parameter){
                std::cout << unnecesarily_heavy_book->ret(std::stoi(parameter)) << " ";
            }

            std::cout << std::endl;
        }

        // Print: prints all words in the trie
        else if (command == "print") {
            if (!unnecesarily_heavy_book->print(std::stoi(parameter)).empty()){
                std::cout << unnecesarily_heavy_book->print(std::stoi(parameter)) << std::endl;
            }
        }

        // Spellcheck: will try correcting a given word with a word in a trie if possible
        else if (command == "exit") {
            delete unnecesarily_heavy_book;
            return 0;
        }
    }
}