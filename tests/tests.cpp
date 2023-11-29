#include <gtest/gtest.h>
#include <vector>
#include "../src/parser.h"
#include "../src/applier.h"

TEST(ParserCheck, ResultCheck) {
  std::vector<std::tuple<std::string, char, int>> regexps = {
    {"a", 'a', 1},              //  a
    {"ba.", 'b', 1},            //  ba
    {"ac*+", 'c', INF},         //  c* + a
    {"1a*+bc.c+*.", 'a', INF},  //  (a* + 1)(bc + c)*
    {"11.b*a..", 'a', 1},       //  11b*a
    {"ba.aaa..+", 'a', 3},      //  ba + aaa
    {"b1a+.b.", 'b', 2}         //  b(1 + a)b

  };

  for (const auto & [regexp, letter, expected] : regexps) {
    TRegExpParser parser(regexp);
    Applier applier(letter);
    Result actual_res = parser.ParseAndGetResult<Applier, Result>(applier);
    int actual = std::max(actual_res.max_all, actual_res.max_prefix);
    ASSERT_EQ(actual, expected);
  }
}

TEST(ParserCheck, IncorrectInputCheck) {
  std::vector<std::tuple<std::string, char, std::string>> regexps = {
    {"r", 'a', "Got unknown symbol r"},
    {"*", 'a', "No operand for *"},
    {"ab.+", 'a', "Not enough operands for +"},
    {"aa*", 'a', "Missing operation"}
  };

  for (const auto & [regexp, letter, expected_exception] : regexps) {
    TRegExpParser parser(regexp);
    Applier applier(letter);
    try {
      parser.ParseAndGetResult<Applier, Result>(applier);
    } catch(const std::exception& e) {
      EXPECT_EQ(e.what(), expected_exception);
    }
  }
}
