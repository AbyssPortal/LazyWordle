
#pragma once

#include <array>
#include <string>
#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

#include "utils.hpp"


constexpr uint WORD_SIZE = 5; // Wordle words are 5 letters long
constexpr uint COLORINGS_COUNT = pow(3, WORD_SIZE);
typedef std::array<char, WORD_SIZE> Word;

typedef std::conditional_t<log(2, COLORINGS_COUNT) <=  8, uint_fast8_t,
                    std::conditional_t<log(2, COLORINGS_COUNT) <= 16, uint_fast16_t,
                    std::conditional_t<log(2, COLORINGS_COUNT) <= 32, uint_fast32_t,
                    uint_fast64_t >>> coloring_t;

extern char _binary_words_txt_start;
extern char _binary_words_txt_end;
extern char _binary_results_txt_start;
extern char _binary_results_txt_end;

const std::vector<Word> &get_words();
const std::vector<Word> &get_results();

void wordle_setup();

void load_word_list(std::vector<Word> &words, const char *string, const char* end);

Word create_word_from_char_ptr(const char *word_str);

std::ostream &operator<<(std::ostream &os, const Word &word);

coloring_t find_colors(Word result, Word guess);

coloring_t get_coloring_from_input(std::istream &is);
