#include "transition_functions.h"

Input characterToInputClass(char c) {
  switch (c) {
    case '0':
      return ZERO;

    case '1': case '2': case '3': case '4': case '5': case '6': case '7':
      return ONE_T0_SEVEN;

    case '8': case '9':
      return EIGHT_TO_NINE;

    case '-': case '+':
      return SIGN;

    case 'a': case 'c': case 'd': case 'e': case 'f':
      return HEX_ACDEF;

    case 'b':
      return B;

    case 'h':
      return H;

    case '\0':
      return END;

    default:
      return INVALID;
  }
}

LexState* initialiseLexState(string s) {
  LexState* state = new LexState;
  state->currentState = START;
  state->currentInput = characterToInputClass(s[0]);
  state->currentChar = s[0];
  state->sign = 1;
  state->isDec = false;
  state->isHex = false;
  return state;
}

string stringToLexicalToken(string s) {
  string copy = s;
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  s += '\0';
  LexState* state = initialiseLexState(s);

  for (auto it = s.begin(); it != s.end(); ++it) {
    if (state->currentState == REJECT) {
      break;
    }
    state->currentInput = characterToInputClass(*it);
    state->currentChar = *it;
    Transition transition = TRANSITION_TABLE[state->currentState][state->currentInput];

    if (transition.transitionFunction != NULL) {
      transition.transitionFunction(state);
    }

    state->currentState = transition.nextState;
  }

  // Take our encountered digits and state and calculate the value
  int val = 0;

  delete state;
  return "Lexeme(" + copy + ") -> Lexical Token (" + to_string(val) + ")";
}

int main(int argc, const char* argv[]) {
  for (int i = 1; i < argc; i++) {
    cout << stringToLexicalToken(string(argv[i])) << "\n";
  }

  array<string, 5> inputs = {{"179", "-2803", "-0", "4BC9h", "172371B"}};

  for (auto it = inputs.begin(); it != inputs.end(); ++it) {
    cout << stringToLexicalToken(*it) << "\n";
  }

  return 0;
}
