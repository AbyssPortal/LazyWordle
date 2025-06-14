#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include "utils.hpp"
#include "wordle.hpp"
#include "wordle_solver.hpp"

int bot_play_wordle(Word hidden_word, Word first_guess);

int cheat_wordle(Word first_guess);

int play_wordle(Word hidden_word);

const char *best_first_guess_location = "best_first_guess.txt";

inline Word get_best_first_guess()
{
    std::ifstream infile(best_first_guess_location);
    Word best_first_guess;
    if (infile)
    {
        std::string guess;
        infile >> guess;
        if (guess.size() == 5)
        {
            best_first_guess = create_word_from_char_ptr(guess.c_str());
            return best_first_guess;
        }
    }
    best_first_guess = find_best_guess(get_results());
    std::ofstream outfile(best_first_guess_location);
    outfile << best_first_guess << std::endl;
    return best_first_guess;
}

int main(int argc, char **argv)
{
    wordle_setup();

    std::cout << "Loaded " << get_words().size() << " words" << std::endl;
    std::cout << "Loaded " << get_results().size() << " possible results" << std::endl;

    std::vector<Word> partition = get_results();
    Word first_guess = get_best_first_guess();
    std::cout << "Pre-calculated first guess: " << first_guess << std::endl;

    if (argc < 2)
    {
        std::cerr << "Usage 1: " << argv[0] << " test" << " [game chance]" << std::endl;
        std::cerr << "Usage 2: " << argv[0] << " solve" << " [hidden]" << std::endl;
        std::cerr << "Usage 3: " << argv[0] << " cheat" << std::endl;
        std::cerr << "Usage 4: " << argv[0] << " recalc_first" << std::endl;
        std::cerr << "Usage 5: " << argv[0] << " play" << std::endl;

        return 1;
    }
    else
    {

        if (std::strcmp(argv[1], "test") == 0)
        {
            if (argc < 3)
            {
                std::cerr << "Please provide the chance to play." << std::endl;
                return 1;
            }
            double chance_to_play = std::stod(argv[2]);
            srand(time(nullptr));
            int total_guesses = 0;
            int total_games = 0;
            int worst_game = 0;
            for (Word hidden_word : get_results())
            {
                if (rand() % 10000 >= chance_to_play * 10000)
                {
                    continue; // Skip this word based on the chance
                }
                std::cout << "Hidden word: " << hidden_word << std::endl;

                int guesses = bot_play_wordle(hidden_word, first_guess);

                total_guesses += guesses;
                total_games++;
                if (guesses > worst_game)
                {
                    worst_game = guesses;
                }
            }
            std::cout << "Average guesses per game: " << (static_cast<double>(total_guesses) / total_games) << std::endl;
            std::cout << "Worst game: " << worst_game << " guesses." << std::endl;
        }
        else if (std::strcmp(argv[1], "solve") == 0)
        {
            if (argc < 3)
            {
                std::cerr << "Please provide the hidden word." << std::endl;
                return 1;
            }
            Word hidden_word = create_word_from_char_ptr(argv[2]);
            bot_play_wordle(hidden_word, first_guess);
        }
        else if (std::strcmp(argv[1], "cheat") == 0)
        {
            while (true)
            {
                cheat_wordle(first_guess);
            }
        }
        else if (std::strcmp(argv[1], "recalc_first") == 0)
        {
            first_guess = find_best_guess(get_results());
            std::cout << "Recalculated first guess: " << first_guess << std::endl;
            std::ofstream outfile(best_first_guess_location, std::ios::trunc);
            outfile << first_guess << std::endl;
            outfile.close();
        }
        else if (std::strcmp(argv[1], "play") == 0)
        {
            srand(time(nullptr));

            play_wordle(get_results()[rand() % get_results().size()]);
        }
        else
        {
            std::cerr << "Unknown command: " << argv[1] << std::endl;
            return 1;
        }
    }
}

int play_wordle(Word hidden_word)
{
    for (int i = 0; i < 6; i++)
    {
        std::cout << "Guess #" << i + 1 << ": ";
        std::string guess_str = "";
        std::cin >> guess_str;

        while (guess_str.size() != WORD_SIZE)
        {
            std::cout << "Invalid guess length. Please enter a 5-letter word." << std::endl;
            std::cin >> guess_str;
        }

        Word guess = create_word_from_char_ptr(guess_str.c_str());

        uint colors = find_colors(hidden_word, guess);
        for (int j = WORD_SIZE - 1; j >= 0; j--)
        {
            switch (colors / pow(3, j))
            {
            case 0:
            {
                std::cout << guess[WORD_SIZE - j - 1]; // Gray
            }
            break;
            case 1:
            {
                print_color(std::cout, guess[WORD_SIZE - j - 1], "33"); // Yellow
            }
            break;
            case 2:
            {
                print_color(std::cout, guess[WORD_SIZE - j - 1], "32"); // Green
            }
            break;
            }
            colors %= pow(3,j);
        }
        std::cout << std::endl;
        if (guess == hidden_word)
        {
            std::cout << "Congratulations! You've guessed the word!" << std::endl;
            return i + 1;
        }
    }

    std::cout << "Sorry, you've used all your guesses. The word was: " << hidden_word << std::endl;


    return 6;
}

int bot_play_wordle(Word hidden_word, Word first_guess)
{
    std::vector<Word> partition = get_results();
    for (int i = 0; i < 10; i++)
    {

        Word best_guess;
        if (i == 0)
            best_guess = first_guess; // Use the first guess provided
        else
            best_guess = find_best_guess(partition);

        std::cout << "Guess #" << i + 1 << ": " << best_guess << std::endl;

        if (best_guess == hidden_word)
        {
            return i + 1; // Return the number of guesses taken
        }

        apply_guess(partition, best_guess, find_colors(hidden_word, best_guess));

        std::cout << "Remaining words: " << partition.size() << std::endl;

        if (partition.empty())
        {
            std::cout << "No more possible results left!" << std::endl;
            return 10; // Failure
        }
    }
    return 10;
}

int cheat_wordle(Word first_guess)
{
    std::vector<Word> partition = get_results();
    for (int i = 0; i < 10; i++)
    {

        Word best_guess;
        if (i == 0)
            best_guess = first_guess; // Use the first guess provided
        else
            best_guess = find_best_guess(partition);

        std::cout << "Guess #" << i + 1 << ": " << best_guess << std::endl;

        std::cout << "What colors did you get? (0 for gray, 1 for yellow, 2 for green): ";
        uint guess_colors = -1;
        while (guess_colors >= COLORINGS_COUNT)
        {
            guess_colors = get_coloring_from_input(std::cin);
        }
        if (guess_colors == COLORINGS_COUNT - 1)
        {
            std::cout << "Congratulations, you cheater!" << std::endl;
            return i + 1;
        }

        apply_guess(partition, best_guess, guess_colors);

        std::cout << "Remaining words: " << partition.size() << std::endl;

        if (partition.empty())
        {
            std::cout << "No more possible results left!" << std::endl;
            return 10; // Failure
        }
    }
    return 10;
}
