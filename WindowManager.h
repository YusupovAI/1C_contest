#pragma once

#include <curses.h>
#include <string>
#include <vector>

class WindowManager {
 public:
  WindowManager();

  std::string GetLine();

  std::string GetWord();

  void PutString(std::string_view);

  void PutCharacter(char sym);

  char GetCharacter();

  ~WindowManager();

  void RemoveLast(size_t cnt = 1);

  void StepBack(int& y, int& x);

 private:
  size_t width_{128};
  size_t height_{30};

  WINDOW* main_window_;

  std::vector<size_t> length_;
};