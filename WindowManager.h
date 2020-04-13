#pragma once

#include <curses.h>
#include <string>

class WindowManager {
 public:
  WindowManager();

  std::string GetLine();

  std::string GetWord();

  void PutString(std::string_view);

  void PutCharacter(char sym);

  char GetCharacter();

  ~WindowManager();

 private:
  WINDOW* main_window_;
};