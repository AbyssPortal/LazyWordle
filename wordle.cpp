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

coloring_t find_colors(Word result, Word guess)
{
    coloring_t word_colors = 0;
    for (size_t i = 0; i < WORD_SIZE; ++i)
    {
        word_colors *= 3; // Shift left by 1 base-3 digit

        if (guess[i] == result[i])
        {
            result[i] = '#'; // Mark as matched
            word_colors += 2;
        } else {
            for (uint j = 0; j < WORD_SIZE; ++j)
            {
                if (guess[i] == result[j])
                {
                    word_colors += 1;
                    result[j] = '#'; // Mark as matched
                    break; // Found a match, no need to check further
                }
            }
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


coloring_t get_coloring_from_input(std::istream &is)
{
    
    std::string input;
    is >> input;

    if (input.size() != WORD_SIZE)
    {
        std::cerr << "Invalid input length. Expected " << WORD_SIZE << " characters." << std::endl;
        return -1; // Error code for invalid input
    }

    coloring_t color_value = 0;
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