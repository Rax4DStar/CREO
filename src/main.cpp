#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string> 
#include <utility>
#include <vector>

#include "Lexer.hpp"
#include "Token.hpp"

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cerr<<"Usage: "<<argv[0]<< "<source_file.si>\n";
        return 1;
    }

    const std::string filename=argv[1];
    std::ifstream inputFile(filename);

    if(!inputFile.is_open()){
        std::cerr << "Error: Could not read '"<<filename<<"'.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer<<inputFile.rdbuf();

    if (inputFile.bad()){
        std::cerr << "Error: Could not read '"<<filename<<"'.\n";
        return 1;
    }

    try{
        Lexer lexer(buffer.str());
        const std::vector<Token> tokens = lexer.tokenise();

        for(const Token& token : tokens){
            std::cout << token.line << ':' << token.column << "  " << token.type << "  '" << token.lexeme << "'\n";

        }

    } catch(const std::exception& error){
        std::cerr << "Lexer error: " << error.what() << '\n';
        return 1;
    }
    return 0;

}