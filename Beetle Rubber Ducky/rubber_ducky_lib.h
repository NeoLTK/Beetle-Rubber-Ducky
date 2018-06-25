#ifndef Rubber_Ducky_H
#define Rubber_Ducky_H

#include "Keyboard.h"

class Rubber_Ducky {
  public:
    void init();
    void finish();

    void longerDelay();
    void shortDelay();
    void setLongTime(int);
        
    void writeText(String);
    void writeText(String, bool);
    void push(uint8_t); 

    void keyCombination(uint8_t, uint8_t, uint8_t, uint8_t);
    void keyCombination(uint8_t, uint8_t, uint8_t);
    void keyCombination(uint8_t, uint8_t);

    void altCombination(uint8_t);
    void shiftCombination(uint8_t);
    void guiCombination(uint8_t);
    void ctrlCombination(uint8_t);

    Rubber_Ducky();

    void Run(String, bool);
    void Run(String);
    
    void openCommandPrompt(boolean, bool);
    void openCommandPrompt(bool);
    void openCommandPrompt();
    
    void powershellRun(String, bool);
    
    void acceptWindowsSmartScreen();
    void hideWindow();
    void paste();
    void cut();
    void copy();
    void changeKeyboardLayout();
    void showDesktop();
    
  private:
    int shortTime = 2;
    int longTime = 100; // shotTime * longTime = longerDelay();
    int initTime = 3500;
      
    
};

#endif 
