#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "man.h"
#include "obscuredword.h"
#include "words.h"

namespace {

void AltScreenBuf() { (std::cout << "\033[?1049h").flush(); }
void ResetScreenBuf() { (std::cout << "\033[?1049l").flush(); }

void Clear() { std::cout << "\033[2J"; }

// Move cursor to position (1-based, so 1,1 is top left!).
void Cursor(unsigned row, unsigned col) {
  std::printf("\033[%u;%uH", row, col);
}

}  // namespace

void SigHandler(int) { std::exit(0); }

int main(int argc, char** argv) {
  std::ios::sync_with_stdio(true);
  std::cout << std::unitbuf;

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
  Cursor(1, 1);

  hangman::Man man;
  hangman::ObscuredWord word(list());

  std::cout << "Welcome to hangman!\n\n";
  // TODO clean this up
  // TODO do not clear after every entry (causes flickering during updates)
  do {
    char c;

    std::cout << man << "\n\n";
    std::cout << "Your word: " << word << '\n';
    std::cout << "Enter a letter: ";

    std::cin >> c;

    switch (word.Guess(c)) {
      case hangman::ObscuredWord::kCorrect:
        Clear();
        Cursor(1, 1);
        std::cout << "You got it!\n\n";
        break;
      case hangman::ObscuredWord::kIncorrect:
        ++man;
        Clear();
        Cursor(1, 1);
        std::cout << "Sorry, that's not right :(\n\n";
        break;
      case hangman::ObscuredWord::kRepeat:
        Clear();
        Cursor(1, 1);
        std::cout << "You already guessed that!\n\n";
        break;
      case hangman::ObscuredWord::kInvalid:
        Clear();
        Cursor(1, 1);
        std::cout << "Invalid input!\n\n";
        break;
    }
  } while (!man.Dead() && !word.Done());

  Clear();

  ResetScreenBuf();

  // TODO this will not display?
  if (man.Dead()) {
    std::cout << "You lost!\n\n";
  } else {
    std::cout << "You win!\n\n";
  }

  std::cout << man << "\n\n";
  std::cout << "The word was: " << word.Actual() << '\n';

  return 0;
}
