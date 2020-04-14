#include "WindowManager.h"

WindowManager::WindowManager() {
  initscr();
  cbreak();
  noecho();
  main_window_ = newwin(height_, width_, 0, 0);
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
  int y, x;
  getyx(main_window_, y, x);
  for (auto symbol:word) {
    waddch(main_window_, symbol);
  }
  wrefresh(main_window_);
  int new_y, new_x;
  getyx(main_window_, new_y, new_x);
  while (new_y != y) {
    length_.push_back(width_);
    --new_y;
  }
}

void WindowManager::PutCharacter(char sym) {
  int y, x;
  getyx(main_window_, y, x);
  waddch(main_window_, sym);
  wrefresh(main_window_);
  int new_y, new_x;
  getyx(main_window_, new_y, new_x);
  if (y != new_y) {
    length_.push_back(x + 1);
  }
}

void WindowManager::StepBack(int& y, int& x) {
  --x;
  if (x < 0) {
    --y;
    x = length_.back() - 1;
    length_.pop_back();
  }
}

void WindowManager::RemoveLast(size_t cnt) {
  if (cnt == 0) {
    return;
  }
  int x, y;
  getyx(main_window_, y, x);
  StepBack(y, x);
  for (size_t i = 0; i < cnt; ++i) {
    mvwdelch(main_window_, y, x);
    StepBack(y, x);
    if (y < 0) {
      return;
    }
  }
}