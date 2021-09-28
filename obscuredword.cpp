#include "obscuredword.h"

#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace hangman {

namespace {

std::string Obscure(const std::string& word) {
  std::string obs{""};

  for (char c : word) {
    if (std::isalpha(c)) {
      obs += '_';
    } else {
      obs += c;
    }
  }

  return obs;
}

}  // namespace

ObscuredWord::ObscuredWord(const std::string& word)
    : word_(word), print_(Obscure(word)) {}

ObscuredWord::GuessResult ObscuredWord::Guess(char c) {
  c = std::tolower(c);

  if (!std::isalpha(c)) {
    return kInvalid;
  }

  if (guesses_[c]) {
    return kRepeat;
  } else {
    GuessResult result = kIncorrect;

    for (std::size_t i = 0; i < word_.size(); i++) {
      if (word_[i] == c) {
        print_[i] = c;
        result = kCorrect;
      }
    }

    guesses_[c] = true;

    return result;
  }
}

bool ObscuredWord::Done() const {
  for (char c : print_) {
    if (c == '_') {
      return false;
    }
  }

  return true;
}

std::ostream& operator<<(std::ostream& os, const ObscuredWord& word) {
  std::ostringstream ss;
  ss.flags(os.flags());
  ss.imbue(os.getloc());

  ss << word.print_;

  os << ss.str();
  return os;
}

}  // namespace hangman
