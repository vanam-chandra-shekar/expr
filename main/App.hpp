#pragma once
#include <string>

#include "Parser.hpp"
#include "vm.hpp"

class App
{

public:
  static void runPromt();
  static void run(const std::string& src);
  static void error(int pos , const std::string_view& mssg);
  static void error(Token token , const std::string_view& mssg);

private:
  static bool hadError;

  static vm Vm;
  static Parser parser;
  static void report(int pos ,const std::string_view& where ,const std::string_view&  mssg);


};