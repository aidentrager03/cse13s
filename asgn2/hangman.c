#include "hangman_helpers.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("wrong number of arguments\n");
        fprintf(stderr, "usage: %s <secret_phrase>\n", argv[0]);
        printf("if the secret is multiple words, you must quote it\n");
        return 1;
    }

    const char *secret = argv[1];
    char eliminated[MAX_LENGTH] = "";
    char correct_guesses[MAX_LENGTH] = ""; // Store correct guesses
    int mistakes = 0;
    bool clear = true;

    // Validate secret
    if (!validate_secret(secret)) {
        // the secret phrase must contain only lowercase letters, spaces, hyphens, and apostrophes
        return 1;
    }

    size_t remaining_letters = 0;
    for (size_t z = strlen(secret); z > 0; z--) {
        if (('a' <= secret[z - 1] && secret[z - 1] <= 'z')) {
            remaining_letters++;
        }
    }

    char guessed[MAX_LENGTH] = ""; // Store guessed letters
    size_t eliminated_length = 0;

    while (mistakes < LOSING_MISTAKE) {
        // Print game state
        if (clear) {
            print_game_state(secret, eliminated, mistakes, correct_guesses);
        }
        // Prompt for a letter
        printf("Guess a letter: ");
        char guess = read_letter();

        // Check if the letter has already been guessed and is a valid character
        if (string_contains_character(guessed, guess) || !(('a' <= guess && guess <= 'z'))) {
            clear = false;
            continue; // Skip the rest of the loop iteration
        }
        clear = true;
        guessed[strlen(guessed)] = guess;
        guessed[strlen(guessed)] = '\0';

        // Check if the letter is in the secret
        const char *secret_ptr = secret; // Create a separate pointer
        size_t letter_occurrences = 0; // Count occurrences of the guessed letter

        while (*secret_ptr != '\0') {
            if (*secret_ptr == guess) {
                remaining_letters--;
                letter_occurrences++;
            }
            secret_ptr++;
        }

        if (letter_occurrences == 0) {
            mistakes++;
            size_t i = 0;
            while (i < eliminated_length && eliminated[i] < guess) {
                i++;
            }
            for (size_t j = eliminated_length; j > i; j--) {
                eliminated[j] = eliminated[j - 1];
            }
            eliminated[i] = guess; // Insert the new character at the correct alphabetical position
            eliminated_length++;
            eliminated[eliminated_length] = '\0';
        } else {
            // Similar operation for 'correct_guesses'
            size_t i = 0;
            while (i < strlen(correct_guesses) && correct_guesses[i] < guess) {
                i++;
            }
            for (size_t j = strlen(correct_guesses); j > i; j--) {
                correct_guesses[j] = correct_guesses[j - 1];
            }
            correct_guesses[i]
                = guess; // Insert the new character at the correct alphabetical position
            correct_guesses[strlen(correct_guesses) + 1] = '\0';
        }

        // Check if the player has won
        if (remaining_letters == 0) {
            print_game_state(secret, eliminated, mistakes, correct_guesses);
            printf("You win! The secret phrase was: %s\n", secret);

            // Exit the program as the player has won
            return 0;
        }
    }

    // Player loses
    if (mistakes == LOSING_MISTAKE) {
        print_game_state(secret, eliminated, mistakes, correct_guesses);
        printf("You lose! The secret phrase was: %s\n", secret);
    }

    return 0;
}
