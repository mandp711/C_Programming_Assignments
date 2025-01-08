#include "cse13s_random.h"
#include "names.h"

#include <stdio.h>

#define MAX_CHIPS 3

int main(void) {

    typedef enum { DOT, LEFT, CENTER, RIGHT } Position;
    const Position die[6] = {
        DOT,
        DOT,
        DOT,
        LEFT,
        CENTER,
        RIGHT,
    };
    int num_players = 3;
    unsigned seed = 4823;
    int player_chips[MAX_PLAYERS];
    for (int i = 0; i < num_players; i++) {
        player_chips[i] = MAX_CHIPS;
    }
    printf("Number of players (3 to 11)? ");
    int scanf_result = scanf("%d", &num_players);

    // Validate the number of players
    if (scanf_result < 1 || num_players < 3 || num_players > MAX_PLAYERS) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
    }
    const char *winner = "";
    cse13s_random_seed(seed);

    for (int i = 0; i < num_players; i++) {
        player_chips[i] = MAX_CHIPS;
    }
    //int roll_sum = 0;
    int found_winner = 0;
    while (found_winner == 0) {

        for (int i = 0; i < num_players; i++) {

            if (player_chips[i] > 0 && (found_winner) != 1) {

                int numberRolls = player_chips[i];

                if (player_chips[i] > 3) {
                    numberRolls = 3;
                }

                for (int j = 0; j < numberRolls; j++) {
                    int roll_num = cse13s_random() % 6;
                    // printf("%s rolled a %d\n", player_name[i], roll_num);
                    switch (die[roll_num]) {
                    case DOT:
                        // printf("%s ", "DOT");
                        break;

                    case LEFT:
                        if (i == num_players - 1) {
                            player_chips[0] += 1;
                            player_chips[i] -= 1;
                        } else {
                            player_chips[i + 1] += 1;
                            player_chips[i] -= 1;
                        }

                        break;
                    case RIGHT:
                        if (i != 0) {
                            player_chips[i - 1] += 1;
                            player_chips[i] -= 1;
                        } else {
                            player_chips[num_players - 1] += 1;
                            player_chips[i] -= 1;
                        }
                        break;

                    case CENTER: player_chips[i] -= 1; break;
                    }
                }
                int count = 0;
                for (int k = 0; k < num_players; k++) {
                    if (player_chips[k] == 0) {
                        count++;
                    }
                }
                if (count == num_players - 1) {
                    for (int k = 0; k < num_players; k++) {
                        if (player_chips[k] > 0) {
                            winner = player_name[k];
                            found_winner += 1;
                            break;
                        }
                    }
                }

                printf("%s", player_name[i]);
                printf(": ends her turn with %d\n", player_chips[i]);
            }
            // if(found_winner){
            //     printf("%s", player_name[i]);
            //     printf(": ends her turn with %d\n", player_chips[i]);
            // }
        }
    }

    printf("%s won!\n", winner);
}
