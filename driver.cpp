// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "tokenize.h"

// For testing:
//./tokenize.out < inputs/test01.in > my_outputs/mtest01.out
// Add -g to cxxflags in make file
//valgrind --leak-check=full --show-leak-kinds=all ./tokenize.out <inputs/test03.in 
//valgrind --leak-check=full --show-leak-kinds=all ./tokenize.out 

int main(){

    // Create the dictionary class which creates a nullptr hashmap and vector
    Dictionary *unnecesarily_heavy_book = new Dictionary;

    // infinite loop until exit function call
    while (true){

        // Receive User input and seperate ino command and parameter
        std::string user_input, command, parameter;
        std::getline(std::cin, user_input);
        std::istringstream iss(user_input);
        iss >> command >> parameter;

        // Create: create a hashmap of given size, will also create a new vector class of arbitrary size
        if (command == "create") {
            // Convert the parameter into an integer and pass into function by reference
            unsigned int size = std::stoi(parameter);
            unnecesarily_heavy_book->create(size);
            std::cout << "success" << std::endl;
        }

        // Insert: insert a word into the hashmap and vector classes
        else if (command == "insert") {

            // Insert a word and output success, if unable to insert a word the function will return false and failure will be outputted instead
            if(unnecesarily_heavy_book->insert(parameter)){std::cout << "success" << std::endl;} 
            
            else{std::cout << "failure" << std::endl;}

        }

        // Load: Open given file and extract words last whitespace, cout success a word was inserted, else failure
        else if (command == "load") {

            // Initialize variables for parsing through file and a flag which will check if a word was inserted into the hashmap
            std::ifstream file(parameter);
            bool flag = false;
            std::string word;

            // Itterate through all words in the file, if any words were inserted, update the flag
            while (file >> word){if (unnecesarily_heavy_book->insert(word)){flag = true;}}
            
            // Close the file so other files can be read
            file.close();

            // Check if any words were inserted and output accordingly
            if (flag == true){std::cout << "success" << std::endl;}
            else{std::cout << "failure" << std::endl;}
        }

        // Tok: return the token associated with given word.
        else if (command == "tok") {
            std::cout << unnecesarily_heavy_book->tok(parameter) << std::endl;
        }

        // Ret: return the word associated with given token. Must conver the string to integer first and pass by reference
        else if (command == "ret") {
            unsigned int token = std::stoi(parameter);
            std::cout << unnecesarily_heavy_book->ret(token) << std::endl;
        }

        // Tok_all: return the tokens associated with given words.
        else if (command == "tok_all") {

            // Accounting for the first given parameter
            std::cout << unnecesarily_heavy_book->tok(parameter) << " ";

            while (iss >> parameter){
                
                // output all tokens with spaces inbetween 
                std::cout << unnecesarily_heavy_book->tok(parameter) << " ";
            }

            // end the line for next function call
            std::cout << std::endl;
        }

        // Tok_all: return the words associated with given tokens.
        else if (command == "ret_all") {

            // Accounting for the first given parameter
            unsigned int token = std::stoi(parameter);
            std::cout << unnecesarily_heavy_book->ret(token) << " ";

            while (iss >> parameter){

                // output all words with spaces inbetween, converting to integer first since the function is pass by reference
                unsigned int token = std::stoi(parameter);
                std::cout << unnecesarily_heavy_book->ret(token) << " ";
            }
            
            // end the line for next function call
            std::cout << std::endl;
        }

        // Print: prints all words in the given hashmap index
        else if (command == "print") {

            // Convert the string to int first since the function is pass by reference
            unsigned int index_k = std::stoi(parameter);

            // If there are no words at given index, do nothing
            if (!unnecesarily_heavy_book->print(index_k).empty()){
                std::cout << unnecesarily_heavy_book->print(index_k) << std::endl;
            }
        }

        // Exit: call the dictionary destructor and return 0
        else if (command == "exit") {
            delete unnecesarily_heavy_book;
            unnecesarily_heavy_book = nullptr;
            return 0;
        }
    }
}