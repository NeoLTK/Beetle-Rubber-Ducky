#include "rubber_ducky_lib.h"


/***********************
 *      Utilities      *
 ***********************/

Rubber_Ducky::Rubber_Ducky() {
  return;
}

void Rubber_Ducky::setLongTime(int longTime) {
  this->longTime = longTime;
}

void Rubber_Ducky::init() {
  Keyboard.begin();
  delay(this->initTime);
}

void Rubber_Ducky::finish() {
  Keyboard.end();
}

void Rubber_Ducky::shortDelay() {
  delay(this->shortTime);
}

void Rubber_Ducky::longerDelay() {
  for(int i = 0; i < this->longTime; i++) this->shortDelay();
}

void Rubber_Ducky::writeText(String text, bool enter) {
  Keyboard.print(text);
  if(enter) this->push(KEY_RETURN);
  this->shortDelay();
}

void Rubber_Ducky::writeText(String text) {
  this->writeText(text, false);
}


void Rubber_Ducky::push(uint8_t key) {
  Keyboard.press(key);
  Keyboard.release(key);
  this->shortDelay();
}

/***********************
 *      Libraries      *
 ***********************
 * You may remove the  *
 * unused functions    *
 * before uploading    *
 * the code to the     *
 * arduino             *
 ***********************/

void Rubber_Ducky::keyCombination(uint8_t holdKey, uint8_t targetKey) {
  Keyboard.press(holdKey);
  this->shortDelay();
  Keyboard.press(targetKey);
  this->shortDelay();
  Keyboard.releaseAll();
  this->shortDelay();
}

void Rubber_Ducky::keyCombination(uint8_t holdKey1, uint8_t holdKey2, uint8_t targetKey) {
  Keyboard.press(holdKey1);
  this->shortDelay();
  this->keyCombination(holdKey2, targetKey);
}

void Rubber_Ducky::keyCombination(uint8_t holdKey1, uint8_t holdKey2, uint8_t holdKey3, uint8_t targetKey) {
  Keyboard.press(holdKey1);
  this->shortDelay();
  this->keyCombination(holdKey2, holdKey3, targetKey);
}

void Rubber_Ducky::guiCombination(uint8_t c) {
  this->keyCombination(KEY_LEFT_GUI, c);
}

void Rubber_Ducky::changeKeyboardLayout() {
  this->altCombination(KEY_LEFT_SHIFT);
}

void Rubber_Ducky::Run(String program, bool eng) {
  this->guiCombination('r');
  this->longerDelay();
  if(eng)this->changeKeyboardLayout();
  Keyboard.print(program);
  this->shortDelay();
  this->push(KEY_RETURN);
}

void Rubber_Ducky::Run(String program) {
  this->Run(program, false);
}

void Rubber_Ducky::showDesktop() {
  Rubber_Ducky::guiCombination('d');
}

void Rubber_Ducky::ctrlCombination(uint8_t c) {
 this->keyCombination(KEY_LEFT_CTRL, c);
}

void Rubber_Ducky::paste() {
  this->ctrlCombination('v');
}

void Rubber_Ducky::cut() {
  this->ctrlCombination('x');
}

void Rubber_Ducky::copy() {
   this->ctrlCombination('c');
}

void Rubber_Ducky::altCombination(uint8_t c) {
  this->keyCombination(KEY_LEFT_ALT, c);
}

void Rubber_Ducky::shiftCombination(uint8_t c) {
  this->keyCombination(KEY_LEFT_SHIFT, c);
}


/**
 * Hides a window:
 * Basically it drags a window to the lowest it can be
 * and then repositions the cursor.
 */
void Rubber_Ducky::hideWindow() {
  this->altCombination(' ');
  Keyboard.print(F("M"));
  this->shortDelay();
  Keyboard.press(KEY_DOWN_ARROW);
  // 100 should be enough to guarantee the window is as low as possible
  // also please notice that 100 is not the real number of strokes since
  // some of the strokes are ignored.
  for(int i = 0; i < 10; i++) this->longerDelay();
  Keyboard.release(KEY_DOWN_ARROW);
  // return repositions the cursor back to its original position
  this->push(KEY_RETURN);
}


/**
 * Accepts the windows smart screen to grant admin permissions.
 */
void Rubber_Ducky::acceptWindowsSmartScreen() {
  // Wait untill smart screen shows up
  this->longerDelay();
  this->push(KEY_LEFT_ARROW);
  this->shortDelay();
  Keyboard.print(F(" "));
  this->shortDelay();
}
 
void Rubber_Ducky::openCommandPrompt(boolean admin, bool eng) {
  if (admin) {
    this->guiCombination('x');
    Keyboard.print(F("a"));
    this->acceptWindowsSmartScreen();
  } else {
    this->Run("cmd", eng);
  }
}

void Rubber_Ducky::openCommandPrompt(bool eng) {
  this->openCommandPrompt(false, eng);
}


void Rubber_Ducky::openCommandPrompt(){
  this->openCommandPrompt(false, false);
}

/**
 * It runs one or multiple powershell scripts,
 * to run multiple scripts, separate them with a new line "\n" char.
 */
void Rubber_Ducky::powershellRun(String scripts, bool eng) {
  char delimiter = '\n';
  String finalScript = "powershell -windowstyle hidden ";
  while (scripts.indexOf('\n') > 0) {
    finalScript = finalScript + "(" + scripts.substring(0, scripts.indexOf('\n')) + ") ; ";
    scripts = scripts.substring(scripts.indexOf('\n') + 1);
  }
  finalScript = finalScript + "(" + scripts + ")";
  this->Run(finalScript, eng);
}

