#ifndef HANGMAN_WORDS_H
#define HANGMAN_WORDS_H

#include <string>
#include <vector>

namespace hangman {

class WordList {
 public:
  WordList() noexcept;

  explicit WordList(const std::string& filepath);

  bool Open(const std::string& filepath);

  bool Ok() const;

  operator bool() const { return Ok(); }

  std::size_t Count() const;

  const std::string& Random() const;

  const std::string& operator()() const { return Random(); }

 private:
  bool ok_;
  std::vector<std::string> words_;
};

}  // namespace hangman

#endif  // HANGMAN_WORDS_H
