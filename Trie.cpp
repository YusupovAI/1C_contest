#include "Trie.h"
#include <stdexcept>

Trie::Node::Node(char parent_symbol, position parent) : parent_symbol_(parent_symbol), parent_(parent), next_() {}

size_t Trie::Size() const {
  return size_;
}

bool Trie::IsEmpty() const {
  return Size() == 0;
}

size_t Trie::Begin() const {
  return 0;
}

typename Trie::position Trie::GoTo(position current, char symbol) {
  if (current >= tree_.size()) {
    return -1;
  }
  auto iter = tree_[current].next_.find(symbol);
  if (iter == tree_[current].next_.end()) {
    return -1;
  }
  return iter->second;
}

typename Trie::position Trie::GoToAdd(position current, char symbol) {
  if (tree_[current].next_[symbol] == 0) {
    tree_[current].next_[symbol] = tree_.size();
    tree_.emplace_back(symbol, current);
  }
  return tree_[current].next_[symbol];
}

Trie::Trie() {
  tree_.emplace_back('\0', -1);
}


void Trie::Add(std::string_view word) {
  position current = Begin();
  for (auto symbol:word) {
    current = GoToAdd(current, symbol);
  }
  ++tree_[current].ended_;
  tree_[current].max_ended_ = std::max(tree_[current].max_ended_, tree_[current].ended_);
  UpdateOnPath(current);
}

void Trie::UpdateOnPath(position current) {
  while (tree_[current].parent_ != -1) {
    auto parent = tree_[current].parent_;
    tree_[parent].max_ended_ = std::max(tree_[current].max_ended_, tree_[parent].max_ended_);
    current = parent;
  }
} 

std::pair<char, typename Trie::position> Trie::GetMaxChild(position current) const {
  for (auto [symbol, child]:tree_[current].next_) {
    if (tree_[child].max_ended_  == tree_[current].max_ended_) {
      return {symbol, child};
    }
  }
  throw std::logic_error("Can't find max child of the leaf");
}

const std::map<char, typename Trie::position>& Trie::GetChilds(position current) const {
  return tree_.at(current).next_;
}

char Trie::GetParentSymbol(position current) const {
  return tree_.at(current).parent_symbol_;
}


std::string Trie::GetMostPopularEnding(position current) const {
  if (tree_.size() <= current) {
    return {};
  }
  std::string result;
  while (tree_[current].max_ended_ != tree_[current].ended_) {
    auto [sym, child] = GetMaxChild(current);
    result.push_back(sym);
    current = child;
  }
  return result;
}