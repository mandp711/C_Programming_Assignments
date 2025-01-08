#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    return ((c >= 'a') && (c <= 'z'));
}
char read_letter(void) {
    char c;
    printf("Guess a letter: ");
    c = (char) getchar();
    getchar();
    return c;
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

bool is_valid_secret(const char *secret) {
    int length = 0;
    while (*secret != '\0') {
        if (!is_lowercase_letter(*secret) && *secret != ' ' && *secret != '\'' && *secret != '-') {
            printf("invalid character: '%c'\n", *secret);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
        secret++;
        length++;
        if (length > 256) {
            printf("the secret phrase is over 256 characters\n");
            return false;
        }
    }
    return true;
}

int len_of_string(const char *secret) {
    int count = 0;
    while (*secret != '\0') {
        secret++;
        count++;
    }

    return count;
}

void return_phrase(const char *word, char *output) {
    int i = 0;
    while (word[i] != '\0') {
        if (word[i] == ' ' || word[i] == '\'' || word[i] == '-') {
            output[i] = word[i];
        } else {
            output[i] = '_';
        }
        i++;
    }
    output[i] = '\0';
}

void switch_guessed_chars(const char *word, char *unknown_word, char c) {
    int i = 0;

    for (i = 0; i <= len_of_string(unknown_word); i++) {
        if (word[i] == c) {
            unknown_word[i] = c;
        }
    }
}

bool check_for_underscore(char *word) {
    while (*word != '\0') {
        if (*word == '_') {
            return true;
        }
        word++;
    }
    return false;
}
