
#include "wordle_solver.hpp"

Word find_best_guess(const std::vector<Word> &partition)
{
    Word best_guess;
    int best_score = std::numeric_limits<int>::max();
    for (Word guess : get_words())
    {
        // std::cout << "Evaluating guess: " << guess << std::endl;
        int color_histogram[COLORINGS_COUNT] = {0};
        // evil number hack. we're using 3*3*3*3*3 options
        // to represent WORD_SIZE digit base 3 numbers, where the digits correspond to the wordle colors

        for (const Word &result : partition)
        {

            color_histogram[find_colors(result, guess)]++;
        }

        int score = 2 * max(color_histogram, COLORINGS_COUNT);
        if (find(partition.begin(), partition.end(), guess) != partition.end())
        {
            score -= 1; // If we can choose a word in the partition and it's
            // as good as the best one outside the partition, we do
        }

        if (score < best_score)
        {
            best_score = score;
            best_guess = guess;
            // std::cout << "New best guess: " << best_guess << " with score: " << best_score << std::endl;
        }
    }
    return best_guess;
}

void apply_guess(std::vector<Word> &partition, Word guess, uint guess_colors)
{
    std::vector<Word> new_partition;
    for (Word result : partition)
    {
        if (find_colors(result, guess) == guess_colors)
        {
            new_partition.push_back(result);
        }
    }
    partition = std::move(new_partition);
}