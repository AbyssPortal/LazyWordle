#pragma once

#include <algorithm>

#include "wordle.hpp"


Word find_best_guess(const std::vector<Word> &partition);

void apply_guess(std::vector<Word> &partition, Word guess, coloring_t guess_colors);




