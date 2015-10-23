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
  char currentChar;
  vector<int> digits;
  int sign;
  bool isDec;
  bool isHex;
  string errorString;

  LexState(char start) {
    currentState = START;
    currentChar = start;
    sign = 1;
    isDec = false;
    isHex = false;
  }
};

struct Transition {
  State nextState;
  void (*action)(LexState*);
};
