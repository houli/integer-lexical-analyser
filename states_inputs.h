#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// The state enum encapsulates the current state of the FSM
enum State {
  START,
  SAW_SIGN,
  DECIMAL,
  OCT_HEX_DEC,
  HEX_DEC,
  HEX,
  SAW_B,
  SAW_H,
  LEADING_ZERO,
  SIGN_LEADING_ZERO,
  ACCEPT,
  REJECT
};

// The input enum encapsulates the current input type of the current character
enum Input {
  ZERO,
  ONE_T0_SEVEN,
  EIGHT_TO_NINE,
  SIGN,
  HEX_ACDEF,
  B,
  H,
  END,
  INVALID
};

// Our lexical analyser state object that is used in the action functions
struct LexState {
  State currentState;
  char currentChar;
  vector<int> digits;
  int sign;
  bool isDec;
  bool isHex;
  string errorString;

  // Constructor for our lexical analyser state
  LexState(char start) {
    currentState = START;
    currentChar = start;
    sign = 1;
    isDec = false;
    isHex = false;
  }
};

/*
* The transition struct stores the next state of the machine as well as the
* action function that should take place at that transition
*/
struct Transition {
  State nextState;
  void (*action)(LexState*);
};
