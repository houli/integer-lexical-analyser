#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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

struct LexState {
  State currentState;
  Input currentInput;
  char currentChar;
  vector<int> encounteredDigits;
  int sign;
  bool isDec;
  bool isHex;
  string errorString;
};

struct Transition {
  State nextState;
  void (*transitionFunction)(LexState*);
};
