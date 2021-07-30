#ifndef HANGMAN_OBSCUREDWORD_H
#define HANGMAN_OBSCUREDWORD_H

#include <iostream>
#include <map>
#include <string>

namespace hangman {

class ObscuredWord {
 public:
  enum GuessResult {
    kCorrect,
    kIncorrect,
    kRepeat,
    kInvalid,
  };

  explicit ObscuredWord(const std::string& word);

  GuessResult Guess(char c);

  bool Done() const;

  const std::string& Actual() const { return word_; }

  friend std::ostream& operator<<(std::ostream& os, const ObscuredWord& word);

 private:
  std::map<char, bool> guesses_;
  std::string word_;
  std::string print_;
};

}  // namespace hangman

#endif  // HANGMAN_OBSCUREDWORD_H
