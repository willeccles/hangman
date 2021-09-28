#include "words.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace hangman {

namespace {

std::string& ToLower(std::string& str) {
  for (auto& c : str) {
    c = std::tolower(c);
  }
  return str;
}

bool IsValid(const std::string_view word) {
  std::size_t alphacount{0};

  for (char c : word) {
    if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'') {
      return false;
    } else if (std::isalpha(c)) {
      ++alphacount;
    }
  }

  return alphacount > 0;
}

}  // namespace

WordList::WordList() noexcept : ok_(false) {}

WordList::WordList(const std::string& filepath) { ok_ = Open(filepath); }

bool WordList::Open(const std::string& filepath) {
  std::ifstream infile(filepath);
  if (!infile) {
    ok_ = false;
    return false;
  }

  std::string line;
  while (std::getline(infile, line)) {
    if (line[line.size() - 1] == '\r') {
      line.erase(line.size() - 1);
    }

    if (IsValid(line)) {
      words_.push_back(ToLower(line));
    }
  }

  ok_ = true;
  return true;
}

bool WordList::Ok() const { return ok_; }

std::size_t WordList::Count() const { return words_.size(); }

const std::string& WordList::Random() const {
  if (!ok_ || words_.size() == 0) {
    throw std::out_of_range("word list is empty");
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<std::size_t> dist(0, words_.size() - 1);

  return words_[dist(gen)];
}

}  // namespace hangman
