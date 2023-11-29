#include <iostream>
#include <cstring>
 
#include "parser.h"
#include "applier.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    throw std::runtime_error("Incorrect number of arguments");
  }
  RegExp regexp = argv[1];
 
  if (strlen(argv[2]) != 1) {
    throw std::runtime_error("Second argument is not a letter");
  }
  char letter = argv[2][0];
 
  TRegExpParser parser(regexp);
  Applier applier(letter);
  Result res = parser.ParseAndGetResult<Applier, Result>(applier);

  if (std::max(res.max_prefix, res.max_all) == INF) 
    std::cout << "INF\n";
  else
    std::cout << std::max(res.max_prefix, res.max_all) << '\n';
 }