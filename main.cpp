#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include "Trie.h"
#include "WindowManager.h"

enum Commands {
  ADD, 
  TYPE,
  NONE
};

static const std::vector<std::string> commands = {"Add:", "Type:"};

Commands GetCommand(std::string_view line) {
  for (size_t i = 0; i < commands.size(); ++i) {
    if (line.substr(0, commands[i].size()) == commands[i]) {
      return Commands(i);
    }
  }
  return NONE;
}

int main(int argc, char* argv[]) {
  Trie trie;
  std::string current;
  WindowManager window;
  while (1) {
    current.clear();
    current = window.GetLine();
    auto command = GetCommand(current);
    if (command == NONE) {
      window.PutString("Invalid arugment\n");
      continue;
    }
    current.clear();
    if (command == ADD) {
      current = window.GetLine();
      std::istringstream line(current);
      std::string word;
      while (line >> word) {
        trie.Add(word);
      }
      continue;
    }
    auto position = trie.Begin();
    char sym;
    while (1) {
      sym = window.GetCharacter();
      if (sym == '\t') {
        auto result = trie.GetMostPopularEnding(position);
        auto len = result.size();
        window.PutString(result);
        sym = window.GetCharacter();
        if (sym != '\t') {
          window.PutCharacter('\n');
        }
        current += result;
        continue;
      }
      if (sym == '\n') {
        break;
      }
      current.push_back(sym);
      position = trie.GoTo(position, sym);
    }
  }
}