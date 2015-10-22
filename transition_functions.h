#include "states_inputs.h"

int digitToInt(char digit) {
  if (digit >= 'a' && digit <= 'f') {
    return (digit - 'a') + 10;
  } else {
    return digit - '0';
  }
}

void setSign(LexState* state) {
  if (state->currentChar == '+') {
    state->sign = 1;
  } else {
    state->sign = -1;
  }
}

void addEncounteredDigit(LexState* state) {
  int digit = digitToInt(state->currentChar);
  state->encounteredDigits.push_back(digit);
}

void addEncounteredDigitAndB(LexState* state) {
  state->encounteredDigits.push_back(digitToInt('b'));
  addEncounteredDigit(state);
}

void acceptHex(LexState* state) {
  state->isHex = true;
}

void acceptDec(LexState* state) {
  state->isDec = true;
}

void reject(LexState* state) {
  printf("Implement Reject\n");
}

// Transition table where row is accessed by state and column accessed by input type
array<array<Transition, 8>, 10> TRANSITION_TABLE = {{
  {{ {LEADING_ZERO, NULL}, {OCT_HEX_DEC, addEncounteredDigit}, {HEX_DEC, addEncounteredDigit}, {SAW_SIGN, setSign}, {HEX, addEncounteredDigit}, {HEX, addEncounteredDigit}, {REJECT, reject}, {REJECT, reject} }},
  {{ {SIGN_LEADING_ZERO, NULL}, {DECIMAL, addEncounteredDigit}, {DECIMAL, addEncounteredDigit}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject} }},
  {{ {DECIMAL, addEncounteredDigit}, {DECIMAL, addEncounteredDigit}, {DECIMAL, addEncounteredDigit}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {ACCEPT, acceptDec} }},
  {{ {OCT_HEX_DEC, addEncounteredDigit}, {OCT_HEX_DEC, addEncounteredDigit}, {HEX_DEC, addEncounteredDigit}, {REJECT, reject}, {HEX, addEncounteredDigit}, {SAW_B, NULL}, {SAW_H, NULL}, {ACCEPT, acceptDec} }},
  {{ {HEX_DEC, addEncounteredDigit}, {HEX_DEC, addEncounteredDigit}, {HEX_DEC, addEncounteredDigit}, {REJECT, reject}, {HEX, addEncounteredDigit}, {HEX, addEncounteredDigit}, {SAW_H, NULL}, {ACCEPT, acceptDec} }},
  {{ {HEX, addEncounteredDigit}, {HEX, addEncounteredDigit}, {HEX, addEncounteredDigit}, {REJECT, reject}, {HEX, addEncounteredDigit}, {HEX, addEncounteredDigit}, {SAW_H, NULL}, {REJECT, reject} }},
  {{ {HEX, addEncounteredDigitAndB}, {HEX, addEncounteredDigitAndB}, {HEX, addEncounteredDigitAndB}, {REJECT, reject}, {HEX, addEncounteredDigitAndB}, {HEX, addEncounteredDigitAndB}, {SAW_H, NULL}, {ACCEPT, NULL} }},
  {{ {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {ACCEPT, acceptHex} }},
  {{ {LEADING_ZERO, NULL}, {OCT_HEX_DEC, addEncounteredDigit}, {HEX_DEC, addEncounteredDigit}, {REJECT, reject}, {SAW_B, NULL}, {SAW_H, NULL}, {ACCEPT, acceptDec} }},
  {{ {SIGN_LEADING_ZERO, NULL}, {DECIMAL, addEncounteredDigit}, {DECIMAL, addEncounteredDigit}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {REJECT, reject}, {ACCEPT, acceptDec} }}
}};