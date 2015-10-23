#include "action_functions.h"

/* Take a character and convert it to its value in the Input enum */
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

/* Create a number from a vector of digit components with a given base */
int vectorToNumber(vector<int> v, int base) {
  int sum = 0;
  for (auto num = v.begin(); num != v.end(); ++num) {
    sum *= base;
    sum += *num;
  }

  return sum;
}

/* Determine if a decimal number will overflow */
bool willOverflowDecimal(LexState* state) {
  // Quick exit when there are too many digits or the number of digits is fine
  if (state->digits.size() < 10) {
    return false;
  } else if (state->digits.size() > 10) {
    return true;
  }

  string decimalString = "";

  // Build a string from the digits we saw
  for (auto digit = state->digits.begin(); digit != state->digits.end(); ++digit) {
    decimalString += *digit + '0';
  }

  // If negative compare against the larger value -2^32, if positive compare to 2^32 - 1
  if (state->sign == -1) {
    return decimalString.compare("2147483648") > 0;
  } else {
    return decimalString.compare("2147483647") > 0;
  }
}

/* Take an input string and either return an error or its Lexical Token and integer value */
string stringToLexicalToken(string s) {
  string copy = s;

  // Lowercase our input string to simplify character comparisons later
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  // Add a null terminator to signify end of input
  s += '\0';

  // Initialise a new state object which encapsulates our processing machine state
  LexState* state = new LexState(s[0]);

  string lexemeString = "Lexeme(" + copy + ") -> ";
  string errorString = lexemeString + "ERROR: ";

  for (auto character = s.begin(); character != s.end(); ++character) {
    // Finish when we are in a reject state
    if (state->currentState == REJECT) {
      break;
    }
    Input currentInput = characterToInputClass(*character);
    state->currentChar = *character;

    if (currentInput == INVALID) {
      // Catch invalid characters entered
      return errorString + "Invalid character encountered";
    }

    // Index into the transition table to find the next state and action to perform
    Transition transition = TRANSITION_TABLE[state->currentState][currentInput];

    // Perform an action if we have to
    if (transition.action != NULL) {
      transition.action(state);
    }

    // Transition to next state
    state->currentState = transition.nextState;
  }

  // Return our error
  if (state->currentState == REJECT) {
    return errorString + state->errorString;
  }

  int base;
  string type;
  if (state->isHex) {
    if (state->digits.size() > 8) {
      // Hex has overflowed if there are more than 8 digits
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
      // Octal overflow if more than 11 digits or 11 digits and the first digit is greater than 3
      return errorString + "Overflowed octal";
    }
    base = 8;
    type = "Octal";
  }

  // Calculate our integer value taking sign into account
  int result = vectorToNumber(state->digits, base) * state->sign;

  // Clean up our state object
  delete state;
  return lexemeString + "Lexical Token(" + type + " Constant, " + to_string(result) + ")";
}

int main(int argc, const char* argv[]) {
  // Read in tests from command line
  for (int i = 1; i < argc; i++) {
    cout << stringToLexicalToken(string(argv[i])) << "\n";
  }

  // Predefined tests
  array<string, 7> inputs = {{"179", "-2803", "-0", "4BC9h", "172371B", "BB", "-000001"}};

  for (auto input = inputs.begin(); input != inputs.end(); ++input) {
    cout << stringToLexicalToken(*input) << "\n";
  }

  return 0;
}
