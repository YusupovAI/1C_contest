#pragma once

#include <cstddef>
#include <string_view>
#include <map>
#include <vector>
#include <utility>

class Trie {
 public:
  Trie();

  using position = size_t;

  void Add(std::string_view word);

  position Begin() const;

  bool IsEmpty() const;

  size_t Size() const;

  bool IsEnd(position) const;

  const std::map<char, position>& GetChilds(position) const;

  std::pair<char, position> GetMaxChild(position) const;

  char GetParentSymbol(position) const;

  position GoTo(position, char);

  std::string GetMostPopularEnding(position) const;

 private:
  struct Node {
    position parent_;
    std::map<char, position> next_{};
    char parent_symbol_;
    size_t ended_{0};
    size_t max_ended_{0};
    Node(char parent_symbol, position parent);
  };

  void UpdateOnPath(position);

  position GoToAdd(position, char);

  size_t size_;
  std::vector<Node> tree_;
};