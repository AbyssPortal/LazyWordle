
#pragma once

#include <array>
#include <string>
#include <limits>
#include "utils.hpp"
#include <iostream>
#include <vector>
#include <fstream>

constexpr uint WORD_SIZE = 5; // Wordle words are 5 letters long
constexpr uint COLORINGS_COUNT = pow(3, WORD_SIZE);
typedef std::array<char, WORD_SIZE> Word;

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

uint find_colors(Word result, Word guess);

int get_coloring_from_input(std::istream &is);
