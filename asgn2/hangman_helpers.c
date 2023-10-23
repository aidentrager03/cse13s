#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    } else {
        return false;
    }
}

bool validate_secret(const char *secret) {
    if (strlen(secret) > 256) {
        printf("Secret is too long (max 256 characters).\n");
        return false;
    }
    while (*secret != '\0') {
        if (!is_lowercase_letter(*secret) && *secret != ' ' && *secret != '\'' && *secret != '-') {
            printf("invalid character: '%c'\n", *secret);
            return false;
        }

        secret++;
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    while (*s != '\0') {
        if (*s == c) {
            return true;
        }
        s++;
    }
    return false;
}

char read_letter(void) {
    int input;
    int actual;
    while ((input = getchar()) != '\n') {
        actual = input;
    }
    char input_char = (char) actual;
    return input_char;
}

void print_game_state(
    const char *phrase, const char *eliminated, int mistakes, const char *correct_guesses) {
    printf("%s", CLEAR_SCREEN);

    // Print gallows
    if (mistakes < LOSING_MISTAKE) {
        printf("%s", arts[mistakes]);
    } else {
        printf("%s", arts[LOSING_MISTAKE]);
    }

    // Print phrase
    printf("Phrase: ");
    while (*phrase != '\0') {
        if (string_contains_character(punctuation, *phrase)
            || string_contains_character(correct_guesses, *phrase)) {
            printf("%c", *phrase);
        } else if (*phrase == ' ') {
            printf(" "); // Display spaces in the phrase
        } else {
            printf("_");
        }
        phrase++;
    }

    // Print eliminated letters
    printf("\nEliminated: %s\n\n", eliminated);
}
