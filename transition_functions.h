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

void pushDigit(LexState* state) {
  int digit = digitToInt(state->currentChar);
  state->digits.push_back(digit);
}

void pushDigitAndB(LexState* state) {
  state->digits.push_back(digitToInt('b'));
  pushDigit(state);
}

void acceptHex(LexState* state) {
  state->isHex = true;
}

void acceptDec(LexState* state) {
  state->isDec = true;
}

void rejectSign(LexState* state) {
  state->errorString = "Sign not in first position";
}

void rejectSignOnly(LexState* state) {
  state->errorString = "Sign provided but no decimal constant";
}

void rejectAfterH(LexState* state) {
  state->errorString = "Character encountered after ending h/H";
}

void rejectHexInDecimal(LexState* state) {
  state->errorString = "Hex digit in decimal constant";
}

void rejectUnterminatedHex(LexState* state) {
  state->errorString = "Hex constant without h/H terminator";
}

void rejectHInDecimal(LexState* state) {
  state->errorString = "Terminator h/H in decimal constant";
}

void rejectHAtStart(LexState* state) {
  state->errorString = "Terminator h/H at beginning of string";
}

void rejectEmpty(LexState* state) {
  state->errorString = "Empty string is invalid";
}

// Transition table where row is accessed by state and column accessed by input type
array<array<Transition, 8>, 10> TRANSITION_TABLE = {{
  /* */
  {{ {LEADING_ZERO, NULL}, {OCT_HEX_DEC, pushDigit}, {HEX_DEC, pushDigit}, {SAW_SIGN, setSign}, {HEX, pushDigit}, {HEX, pushDigit}, {REJECT, rejectHAtStart}, {REJECT, rejectEmpty} }},
  {{ {SIGN_LEADING_ZERO, NULL}, {DECIMAL, pushDigit}, {DECIMAL, pushDigit}, {REJECT, rejectSign}, {REJECT, rejectHexInDecimal}, {REJECT, rejectHexInDecimal}, {REJECT, rejectHInDecimal}, {REJECT, rejectSignOnly} }},
  {{ {DECIMAL, pushDigit}, {DECIMAL, pushDigit}, {DECIMAL, pushDigit}, {REJECT, rejectSign}, {REJECT, rejectHexInDecimal}, {REJECT, rejectHexInDecimal}, {REJECT, rejectHInDecimal}, {ACCEPT, acceptDec} }},
  {{ {OCT_HEX_DEC, pushDigit}, {OCT_HEX_DEC, pushDigit}, {HEX_DEC, pushDigit}, {REJECT, rejectSign}, {HEX, pushDigit}, {SAW_B, NULL}, {SAW_H, NULL}, {ACCEPT, acceptDec} }},
  {{ {HEX_DEC, pushDigit}, {HEX_DEC, pushDigit}, {HEX_DEC, pushDigit}, {REJECT, rejectSign}, {HEX, pushDigit}, {HEX, pushDigit}, {SAW_H, NULL}, {ACCEPT, acceptDec} }},
  {{ {HEX, pushDigit}, {HEX, pushDigit}, {HEX, pushDigit}, {REJECT, rejectSign}, {HEX, pushDigit}, {HEX, pushDigit}, {SAW_H, NULL}, {REJECT, rejectUnterminatedHex} }},
  {{ {HEX, pushDigitAndB}, {HEX, pushDigitAndB}, {HEX, pushDigitAndB}, {REJECT, rejectSign}, {HEX, pushDigitAndB}, {HEX, pushDigitAndB}, {SAW_H, NULL}, {ACCEPT, NULL} }},
  {{ {REJECT, rejectAfterH}, {REJECT, rejectAfterH}, {REJECT, rejectAfterH}, {REJECT, rejectSign}, {REJECT, rejectAfterH}, {REJECT, rejectAfterH}, {REJECT, rejectAfterH}, {ACCEPT, acceptHex} }},
  {{ {LEADING_ZERO, NULL}, {OCT_HEX_DEC, pushDigit}, {HEX_DEC, pushDigit}, {REJECT, rejectSign}, {SAW_B, NULL}, {SAW_H, NULL}, {ACCEPT, acceptDec} }},
  {{ {SIGN_LEADING_ZERO, NULL}, {DECIMAL, pushDigit}, {DECIMAL, pushDigit}, {REJECT, rejectSign}, {REJECT, rejectHexInDecimal}, {REJECT, rejectHexInDecimal}, {REJECT, rejectHexInDecimal}, {ACCEPT, acceptDec} }}
}};