#include <iostream>
#include <array>
#include <string>

#include "intlex.h"

using namespace std;

string string_to_lexeme(string s) {
  return "Lexeme(" + s + ") -> Lexical Token ()";
}

int main(int argc, const char* argv[]) {
  array<string, 5> inputs = {{"179", "-2803", "-0", "4BC9h", "172371B"}};

  for (auto it = inputs.begin(); it != inputs.end(); ++it) {
    cout << string_to_lexeme(*it) << "\n";
  }
  cout << "\n";

  return 0;
}
