#include "wordle.hpp"

void load_word_list(std::vector<Word> &words, const char *string, const char* end)
{
    words.clear();
    const char *start = string;
    while (start < end)
    {
        if (*start == '\0')
        {
            start++;
            continue; // Skip empty strings
        }
        Word word = create_word_from_char_ptr(start);
        start += WORD_SIZE + 1; // Move to the next word
        words.push_back(word);
    }
}

std::vector<Word> words;
std::vector<Word> results;
bool done_setup = false;

void load_wordle_words()
{
    load_word_list(words, &_binary_words_txt_start, &_binary_words_txt_end);
    if (words.empty())
    {
        std::cerr << "No words loaded from words.txt" << std::endl;
    }
}

void load_wordle_results()
{
    load_word_list(results, &_binary_results_txt_start, &_binary_results_txt_end);
    if (words.empty())
    {
        std::cerr << "No words loaded from possible_results.txt" << std::endl;
    }
}

void wordle_setup()
{
    if (done_setup)
    {
        return;
    }
    load_wordle_words();
    load_wordle_results();
    done_setup = true;
}

uint find_colors(Word result, Word guess)
{
    bool used[WORD_SIZE] = {false};
    bool green[WORD_SIZE] = {false};
    bool yellow[WORD_SIZE] = {false};
    for (size_t i = 0; i < WORD_SIZE; ++i)
    {

        if (guess[i] == result[i])
        {
            green[i] = true;
            used[i] = true;
        }
    }
    for (size_t i = 0; i < WORD_SIZE; ++i)
    {
        if (green[i])
            continue;
        for (size_t j = 0; j < WORD_SIZE; ++j)
        {
            if (used[j])
                continue;

            if (guess[i] == result[j])
            {
                yellow[i] = true;
                used[j] = true;
                break;
            }
        }
    }

    uint word_colors = 0;
    for (size_t i = 0; i < WORD_SIZE; ++i)
    {
        word_colors *= 3;
        if (green[i])
        {
            word_colors += 2;
        }
        else if (yellow[i])
        {
            word_colors += 1;
        }
    }

    if (word_colors >= COLORINGS_COUNT)
    {
        std::cerr << COLORINGS_COUNT << std::endl;
        std::cerr << "Error: Color value exceeds expected range." << std::endl;
        std::cerr << "Result: " << result << ", Guess: " << guess << std::endl;
    }

    return word_colors;
}


int get_coloring_from_input(std::istream &is)
{
    std::string input;
    is >> input;

    if (input.size() != WORD_SIZE)
    {
        std::cerr << "Invalid input length. Expected " << WORD_SIZE << " characters." << std::endl;
        return -1; // Error code for invalid input
    }

    int color_value = 0;
    for (size_t i = 0; i < WORD_SIZE; ++i)
    {
        char c = input[i];
        if (c < '0' || c > '2')
        {
            std::cerr << "Invalid character '" << c << "' at position " << i << ". Expected '0', '1', or '2'." << std::endl;
            return -1; // Error code for invalid character
        }
        color_value = color_value * 3 + (c - '0');
    }
    return color_value;
}

std::ostream &operator<<(std::ostream &os, const Word &word)
{
    for (const auto &letter : word)
    {
        os << letter;
    }
    return os;
}

Word create_word_from_char_ptr(const char *word_str)
{
    Word word;
    for (size_t i = 0; i < WORD_SIZE; ++i)
    {
        if (word_str[i] == '\0')
        {
            std::cerr << "Error: Word string is shorter than expected." << std::endl;
            return word;
        }
        word[i] = to_upper(word_str[i]);
    }
    return word;
}

const std::vector<Word> &get_words()
{
    if (!done_setup)
    {
        wordle_setup();
    }
    return words;
}
const std::vector<Word> &get_results()
{
    if (!done_setup)
    {
        wordle_setup();
    }
    return results;
}