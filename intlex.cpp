#include "intlex.h"

// Transition table where row is accessed by state and column accessed by input type
array<array<Transition, 8>, 10> transitionTable = {{
  {{ {LEADING_ZERO, blah}, {OCT_HEX_DEC, blah}, {HEX_DEC, blah}, {SAW_SIGN, blah}, {HEX, blah}, {HEX, blah}, {REJECT, blah}, {REJECT, blah} }},
  {{ {SIGN_LEADING_ZERO, blah}, {DECIMAL, blah}, {DECIMAL, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah} }},
  {{ {DECIMAL, blah}, {DECIMAL, blah}, {DECIMAL, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {ACCEPT, blah} }},
  {{ {OCT_HEX_DEC, blah}, {OCT_HEX_DEC, blah}, {HEX_DEC, blah}, {REJECT, blah}, {HEX, blah}, {SAW_B, blah}, {SAW_H, blah}, {ACCEPT, blah} }},
  {{ {HEX_DEC, blah}, {HEX_DEC, blah}, {HEX_DEC, blah}, {REJECT, blah}, {HEX, blah}, {HEX, blah}, {SAW_H, blah}, {ACCEPT, blah} }},
  {{ {HEX, blah}, {HEX, blah}, {HEX, blah}, {REJECT, blah}, {HEX, blah}, {HEX, blah}, {SAW_H, blah}, {REJECT, blah} }},
  {{ {HEX, blah}, {HEX, blah}, {HEX, blah}, {REJECT, blah}, {HEX, blah}, {HEX, blah}, {SAW_H, blah}, {ACCEPT, blah} }},
  {{ {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {ACCEPT, blah} }},
  {{ {LEADING_ZERO, blah}, {OCT_HEX_DEC, blah}, {HEX_DEC, blah}, {REJECT, blah}, {SAW_B, blah}, {SAW_H, blah}, {ACCEPT, blah} }},
  {{ {SIGN_LEADING_ZERO, blah}, {DECIMAL, blah}, {DECIMAL, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {REJECT, blah}, {ACCEPT, blah} }}
}};

string stringToLexeme(string s) {
  return "Lexeme(" + s + ") -> Lexical Token ()";
}

int main(int argc, const char* argv[]) {
  array<string, 5> inputs = {{"179", "-2803", "-0", "4BC9h", "172371B"}};

  for (auto it = inputs.begin(); it != inputs.end(); ++it) {
    cout << stringToLexeme(*it) << "\n";
  }
  cout << "\n";

  return 0;
}
