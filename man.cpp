#include "man.h"

#include <iostream>
#include <sstream>
#include <string>

namespace hangman {

namespace {

const std::size_t kMaxDeadness = 7;

}

bool Man::Dead() const { return deadness_ == kMaxDeadness; }

Man& Man::operator++() {
  if (deadness_ < kMaxDeadness) {
    ++deadness_;
  }

  return *this;
}

/* Man:
 *  ┌────┐
 *  │    ┆
 *  │    O
 *  │   ─┼─
 *  │    │
 *  │   / \
 * ─┴───────
 */

std::ostream& operator<<(std::ostream& os, const Man& man) {
  std::ostringstream ss;
  ss.flags(os.flags());
  ss.imbue(os.getloc());

  ss << "  ┌────┐\n";
  ss << "  │    ┆\n";
  ss << "  │    " << (man.deadness_ >= 1 ? "O" : "") << '\n';
  ss << "  │   ";

  if (man.deadness_ >= 3) {
    ss << "─";
  } else {
    ss << " ";
  }

  if (man.deadness_ == 2) {
    ss << "│";
  } else if (man.deadness_ == 3) {
    ss << "┤";
  } else if (man.deadness_ >= 4) {
    ss << "┼";
  }

  if (man.deadness_ >= 4) {
    ss << "─";
  }

  ss << '\n';
  ss << "  │    " << (man.deadness_ >= 5 ? "│" : "") << '\n';
  ss << "  │   ";

  if (man.deadness_ >= 6) ss << "/";
  if (man.deadness_ >= 7) ss << " \\";

  ss << '\n';
  ss << " ─┴───────";

  os << ss.str();

  return os;
}

}  // namespace hangman
