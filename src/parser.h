#include <string>
#include <stack>
#include <iostream>

#define RegExp std::string

class TRegExpParser {
 public:
  TRegExpParser(const RegExp& regexp) : regexp(regexp) {}

  template <typename TApplier, typename TResult>
  TResult ParseAndGetResult(TApplier applier) {
    std::stack<TResult> stack;
    for (size_t i = 0; i < regexp.size(); ++i) {
      if (('a' <= regexp[i] && regexp[i] <= 'c') || regexp[i] == '1') {
        stack.push(applier.apply(regexp[i]));
        continue;
      }

      if (regexp[i] == '*') {
        if (stack.size() == 0)
          throw std::runtime_error("No operand for *");

        TResult top = stack.top();
        stack.pop();
        stack.push(applier.apply(regexp[i], top));
        continue;
      }
      if (regexp[i] == '+' || regexp[i] == '.'){
        if (stack.size() < 2) {
          std::string error_message = "Not enough operands for ";
          error_message += regexp[i];
          throw std::runtime_error(error_message);
        }

        TResult top1 = stack.top();
        stack.pop();
        TResult top2 = stack.top();
        stack.pop();
        stack.push(applier.apply(regexp[i], top2, top1));
        continue;
      }
      std::string error_message = "Got unknown symbol ";
      error_message +=  + regexp[i];
      throw std::runtime_error(error_message);
    }
    if (stack.size() != 1) throw std::runtime_error("Missing operation");
    return stack.top();
  }


 private:
  RegExp regexp;
};