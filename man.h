#ifndef HANGMAN_MAN_H
#define HANGMAN_MAN_H

#include <iostream>

namespace hangman {

class Man {
 public:
  Man() : deadness_(0){};

  bool Dead() const;

  Man& operator++();

  friend std::ostream& operator<<(std::ostream& os, const Man& man);

 private:
  std::size_t deadness_;
};

// std::ostream& operator<<(std::ostream& os, const Man& man);

}  // namespace hangman

#endif  // HANGMAN_MAN_H
