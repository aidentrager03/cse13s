#include "names.h"

#include <stdio.h>
#include <stdlib.h>
typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;

const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main(void) {
    // Declaration of num_players
    int num_players;

    printf("Number of players (2 to 10)? ");
    int scanf_result = scanf("%d", &num_players);
    if (scanf_result < 1 || num_players < 2 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        num_players = 2;
    }

    unsigned seed = 2023;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);
    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
    }

    int win = 0;
    int turn = 0;
    int roll = 10;
    int i = 0;
#define SEED seed
    srandom(SEED);
    int scores[num_players];
    for (int j = 0; j < num_players; j += 1) {
        scores[j] = 0;
    }
    int amount_gained = 0;

    while (win == 0) {
        i = 0;
        while (i < num_players) {
            turn = 0;
            printf("%s\n", player_name[i]);
            while (turn == 0) {
                roll = random() % 7;
                switch (pig[roll]) {
                case SIDE:
                    turn = 1;
                    amount_gained = 0;
                    scores[i] += amount_gained;
                    printf(" rolls %d, has %d\n", amount_gained, scores[i]);
                    break;
                case RAZORBACK:
                    amount_gained = 10;
                    scores[i] += amount_gained;
                    printf(" rolls %d, has %d\n", amount_gained, scores[i]);
                    break;
                case TROTTER:
                    amount_gained = 10;
                    scores[i] += amount_gained;
                    printf(" rolls %d, has %d\n", amount_gained, scores[i]);
                    break;
                case SNOUTER:
                    amount_gained = 15;
                    scores[i] += amount_gained;
                    printf(" rolls %d, has %d\n", amount_gained, scores[i]);
                    break;
                case JOWLER:
                    amount_gained = 5;
                    scores[i] += amount_gained;
                    printf(" rolls %d, has %d\n", amount_gained, scores[i]);
                    break;
                }
                if (scores[i] >= 100) {
                    printf("%s Won!\n", player_name[i]);
                    i = 11;
                    win = 1;
                    turn = 1;
                }
            }
            i += 1;
        }
    }

    return 0;
}
