#include <csignal>
#include <cstdlib>
#include <iostream>

#include "man.h"
#include "obscuredword.h"
#include "words.h"

namespace {

void AltScreenBuf() { /*std::cout << "\033[?1049h";*/
}
void ResetScreenBuf() { std::cout << "\033[?1049l"; }

void Clear() { std::cout << "\033[2J\033[H"; }

}  // namespace

void SigHandler(int) { std::exit(0); }

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " WORDLIST\n";
    return 1;
  }

  hangman::WordList list(argv[1]);
  if (!list) {
    std::cerr << "error loading word list: " << argv[1] << '\n';
    return 1;
  }

  if (list.Count() == 0) {
    std::cerr << "error: empty list\n";
    return 1;
  }

  std::atexit(ResetScreenBuf);

  std::signal(SIGINT, SigHandler);
  std::signal(SIGTERM, SigHandler);

  AltScreenBuf();
  Clear();

  hangman::Man man;
  hangman::ObscuredWord word(list());

  std::cout << "Welcome to hangman!\n\n";
  do {
    char c;

    std::cout << man << "\n\n";
    std::cout << "Your word: " << word << '\n';
    std::cout << "Enter a letter: ";

    std::cin >> c;

    switch (word.Guess(c)) {
      case hangman::ObscuredWord::kCorrect:
        Clear();
        std::cout << "You got it!\n\n";
        break;
      case hangman::ObscuredWord::kIncorrect:
        ++man;
        Clear();
        std::cout << "Sorry, that's not right :(\n\n";
        break;
      case hangman::ObscuredWord::kRepeat:
        Clear();
        std::cout << "You already guessed that!\n\n";
        break;
      case hangman::ObscuredWord::kInvalid:
        Clear();
        std::cout << "Invalid input!\n\n";
        break;
    }
  } while (!man.Dead() && !word.Done());

  Clear();

  ResetScreenBuf();

  if (man.Dead()) {
    std::cout << "You lost!\n\n";
  } else {
    std::cout << "You win!\n\n";
  }

  std::cout << man << "\n\n";
  std::cout << "The word was: " << word.Actual() << '\n';

  return 0;
}
