#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace lexer
{

  std::vector<token> tokenize(std::string file_path)
  {
    std::ifstream file(file_path);
    std::string buffer((std::istreambuf_iterator<char>(file)),
      std::istreambuf_iterator<char>());

    std::cout << buffer << std::endl;
    return {};
  }

}