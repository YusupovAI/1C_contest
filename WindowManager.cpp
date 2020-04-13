#include "WindowManager.h"

WindowManager::WindowManager() {
  initscr();
  cbreak();
  noecho();
  main_window_ = newwin(30, 128, 0, 0);
  scrollok(main_window_, TRUE);
}

std::string WindowManager::GetWord() {
  std::string result;
  char sym;
  while (1) {
    sym = getch();
    waddch(main_window_, sym);
    wrefresh(main_window_);
    if (isspace(sym)) {
      return result;
    }
    result.push_back(sym);
  }
}

std::string WindowManager::GetLine() {
  std::string result;
  char sym;
  while (1) {
    sym = getch();
    waddch(main_window_, sym);
    wrefresh(main_window_);
    if (sym == '\n') {
      return result;
    }
    result.push_back(sym);
  }
}

WindowManager::~WindowManager() {
  endwin();
}

char WindowManager::GetCharacter() {
  char sym = wgetch(main_window_);
  if (sym != '\t') {
    waddch(main_window_, sym);
    wrefresh(main_window_);
  }
  return sym;
}

void WindowManager::PutString(std::string_view word) {
  for (auto symbol:word) {
    waddch(main_window_, symbol);
  }
  wrefresh(main_window_);
}

void WindowManager::PutCharacter(char sym) {
  waddch(main_window_, sym);
  wrefresh(main_window_);
}