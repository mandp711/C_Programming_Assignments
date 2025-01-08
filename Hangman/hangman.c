#include "hangman_helpers.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Secret hangman
    (void) argc;
    // Silence unused parameter warning

    // Retrieve the secret phrase from command-line arguments
    const char *secret_phrase = argv[1];
    char hidden_phrase[len_of_string(secret_phrase) + 1];

    // Convert the secret phrase to underscores
    return_phrase(secret_phrase, hidden_phrase);

    // Check if the secret phrase is valid
    if (!is_valid_secret(secret_phrase)) {
        return 1;
    }

    int wrong_attempts = 0;
    bool incorrect_guesses[26] = { false };
    bool all_guesses[26] = { false };

    // Main game loop
    while (check_for_underscore(hidden_phrase) && wrong_attempts < LOSING_MISTAKE) {
        // Print hangman art and current status
        printf("%s\n", arts[wrong_attempts]);
        printf("    Phrase: %s\n", hidden_phrase);
        printf("Eliminated: ");

        // Print eliminated characters
        for (char c = 'a'; c <= 'z'; c++) {
            if (incorrect_guesses[c - 'a']) {
                printf("%c", c);
            }
        }
        printf("\n\n");

        char guessed_char;

        // Loop until the guessed letter is valid
        do {
            guessed_char = read_letter();
        } while (all_guesses[guessed_char - 'a'] || !is_lowercase_letter(guessed_char));

        // Check if the guessed letter is correct
        if (string_contains_character(secret_phrase, guessed_char)) {
            switch_guessed_chars(secret_phrase, hidden_phrase, guessed_char);
        } else {
            wrong_attempts += 1;
            incorrect_guesses[guessed_char - 'a'] = true;
        }
        all_guesses[guessed_char - 'a'] = true;
    }

    // Print final status
    printf("%s\n", arts[wrong_attempts]);
    printf("    Phrase: %s\n", hidden_phrase);
    printf("Eliminated: ");
    for (char c = 'a'; c <= 'z'; c++) {
        if (incorrect_guesses[c - 'a']) {
            printf("%c", c);
        }
    }
    printf("\n");

    // Print game result
    if (!check_for_underscore(hidden_phrase)) {
        printf("\nYou win! The secret phrase was: %s\n", secret_phrase);
    } else {
        printf("\nYou lose! The secret phrase was: %s\n", secret_phrase);
    }
    return 0;
}
