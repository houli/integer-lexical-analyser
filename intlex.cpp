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

int vectorSum(vector<int> v, int base) {
  int sum = 0;
  for (auto num = v.begin(); num != v.end(); ++num) {
    sum *= base;
    sum += *num;
  }

  return sum;
}

bool willOverflowDecimal(LexState* state) {
  if (state->digits.size() < 10) {
    return false;
  } else if (state->digits.size() > 10) {
    return true;
  }

  string decimalString = "";

  for (auto digit = state->digits.begin(); digit != state->digits.end(); ++digit) {
    decimalString += *digit + '0';
  }

  if (state->sign == -1) {
    return decimalString.compare("2147483648") > 0;
  } else {
    return decimalString.compare("2147483647") > 0;
  }
}

string stringToLexicalToken(string s) {
  string copy = s;
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  s += '\0';

  LexState* state = new LexState(s[0]);

  string lexemeString = "Lexeme(" + copy + ") -> ";
  string errorString = lexemeString + "ERROR: ";

  for (auto character = s.begin(); character != s.end(); ++character) {
    if (state->currentState == REJECT) {
      break;
    }
    Input currentInput = characterToInputClass(*character);

    if (currentInput == INVALID) {
      return errorString + "Invalid character encountered";
    }

    state->currentChar = *character;
    Transition transition = TRANSITION_TABLE[state->currentState][currentInput];

    if (transition.action != NULL) {
      transition.action(state);
    }

    state->currentState = transition.nextState;
  }

  if (state->currentState == REJECT) {
    return errorString + state->errorString;
  }

  int base;
  string type;
  if (state->isHex) {
    if (state->digits.size() > 8) {
      return errorString + "Overflowed hex";
    }
    base = 16;
    type = "Hexadecimal";
  } else if (state->isDec) {
    if (willOverflowDecimal(state)) {
      return errorString + "Overflowed decimal";
    }
    base = 10;
    type = "Decimal";
  } else {
    if (state->digits.size() > 11 || (state->digits.size() == 11 && state->digits[0] > 3)) {
      return errorString + "Overflowed octal";
    }
    base = 8;
    type = "Octal";
  }

  int result = vectorSum(state->digits, base) * state->sign;

  delete state;
  return lexemeString + "Lexical Token(" + type + " Constant, " + to_string(result) + ")";
}

int main(int argc, const char* argv[]) {
  for (int i = 1; i < argc; i++) {
    cout << stringToLexicalToken(string(argv[i])) << "\n";
  }

  array<string, 7> inputs = {{"179", "-2803", "-0", "4BC9h", "172371B", "BB", "-000001"}};

  for (auto input = inputs.begin(); input != inputs.end(); ++input) {
    cout << stringToLexicalToken(*input) << "\n";
  }

  return 0;
}
