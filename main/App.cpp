#include <iostream>
#include <vector>

#include "App.hpp"
#include "Chunk.hpp"
#include "Scanner.hpp"
#include "Token.hpp"
#ifdef DEBUG
#include "debug.hpp"
#endif

bool App::hadError = false;
vm App::Vm;
Parser App::parser;

void App::runPromt()
{
    std::string line;

    std::cout<<"> ";
    while (std::getline(std::cin , line))
    {
        hadError = false;
        run(line);
        std::cout<<"> ";
    }
    
}

void App::run(const std::string &src) {

    Scanner scanner(src);
    std::vector<Token> tokens = std::move(scanner.scanTokens());
    if(hadError) return;
    Chunk code;

    parser.parse(code, tokens);
    code.writeChunk(OP_PRINT);

#ifdef DEBUG
        disassembleChunk(code , "main");
#endif

    Vm.interpret(code);

}

void App::report(int pos, const std::string_view &where,const std::string_view &mssg) {

    std::cout<<"[Error] pos: "<<pos<<" "<<where<<" "<<mssg<<"\n";
    hadError = true;

}

void App::error(int pos, const std::string_view &mssg) {
    report(pos , "" , mssg);
}

void App::error(Token token, const std::string_view &mssg) {
    if(token.mtype == TEOF)
    {
        report(token.mpos , "'at end'" , mssg);
    }
    else
    {
        report(token.mpos , "at '" +token.mlexeam+"'" , mssg);
    }
}
