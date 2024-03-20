// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "tokenize.h"

//./spellcheck.out < inputs/test01.in > my_outputs/mtest01.out
// Add -g to cxxflags in make file
//valgrind --leak-check=full --show-leak-kinds=all ./spellcheck.out <inputs/test03.in 

int main(){

   while (true){

        // Receive User input
        std::string user_input = "";
        std::getline (std::cin,user_input);
        
        // Call appropriate functions based on input

        // Load: Open given file and extract words until end. Output success after.
        if (user_input.find("load") != std::string::npos) {
           

            std::cout << "success" << std::endl;
        }

        // Exit: calls clear function, then call the destructor to delete the root
        else if (user_input.find("exit") != std::string::npos) {
            
        }

        // Empty: checks if the trie is empty
        else if (user_input.find("empty") != std::string::npos) {
          
        }

        // Clear: delete all the words in the trie,
        else if (user_input.find("clear") != std::string::npos) {
          
        }

        // Insert: extract the word from input and add the word to the tree if possible
        else if (user_input[0] == 'i') {
            std::string paramater = user_input.substr(2);
            
        }

        // Prefix: extract word and check how many words its a prefix for
        else if (user_input[0] == 'c') {
            std::string paramater = user_input.substr(2);

        }

        // Erase: extract word from input and delete it from the trie reccursivly
        else if (user_input[0] == 'e') {
            std::string paramater = user_input.substr(2);
       
            
        }

        // Print: prints all words in the trie
        else if (user_input[0] == 'p') {

        }

        // Spellcheck: will try correcting a given word with a word in a trie if possible
        else if (user_input.find("spellcheck") != std::string::npos) {
            std::string paramater = user_input.substr(user_input.find(' ') + 1);
     
        }

        // Size: outputs number of words in the trie
        else if (user_input.find("size") != std::string::npos) {
     
        }
    }
}