const int INF = 1e9;
 
struct Result {
  int max_prefix;  // max prefix for words a*(a+b+c)(a+b+c)*
  int max_all;  // max prefix for words a*
  bool can_be_empty;
  Result(int maxp, int maxa, bool empty) : max_prefix(maxp), max_all(maxa), can_be_empty(empty) {}
}; 
 
struct Applier {
  char letter;
 
  Applier(char c) : letter(c) {}
 
  Result apply(char c) { return Result(c == letter, c == letter, c == '1'); }
  Result apply(char c, Result x) { return Result(x.max_prefix, (x.max_all > 0) * INF, true); }
  Result apply(char c, Result x, Result y) {
    if (c == '+') {
      return Result(std::max(x.max_prefix,y.max_prefix),
                    std::max(x.max_all, y.max_all),
                    x.can_be_empty || y.can_be_empty);
    }
    return Result(std::max(x.can_be_empty * y.max_prefix, std::max(x.max_prefix, (x.max_all != 0) * (x.max_all + y.max_prefix))),
                  std::max(x.can_be_empty * y.max_all, std::max(y.can_be_empty * x.max_all, (x.max_all > 0 && y.max_all > 0) * std::min(INF,(x.max_all + y.max_all)))),
                  x.can_be_empty * y.can_be_empty);
  }
};
