#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int num_seed, num_player;
  printf("Random seed: ");
  scanf("%d", &num_seed);
  printf("How many players? ");
  scanf("%d", &num_player);
  // Test whether the user input is correct
  if (num_player < 2 || num_player > 10) {
    printf("Invalid: Number of Players should between 2 and 10 (include)!\n");
    return 0;
  }

  typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
  faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

  const char *names[] = { "Whoopi", "Dale", "Rosie", "Jimmie", "Barbara",
    "Kyle", "Raven", "Tony", "Jenny", "Clint" };

  // Initialize the money of players and the balance in pot
  int money[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
  int pot_balance = 0;
  // create the random by using seed
  srand(num_seed);

  // Set the origin position to 0 which means the first player
  int pos = 0;
  int winner;

  // While result is true, then the loop will stop
  bool result = false;
  while (result == false) {
    // Check the money in player's account, if no money, then pass
    if (money[pos] != 0) {
      printf("%s rolls...", names[pos]);

      // Get the position of left and right players
      // It has three different situation since we need to consider edge case
      // When current pos is first player, the left should be last one
      // When current pos is last player, the right should be first one
      int left_pos, right_pos;
      if (pos == 0) {
        right_pos = pos + 1;
        left_pos = num_player - 1;
      } else if (pos == (num_player - 1)) {
        right_pos = 0;
        left_pos = pos - 1;
      } else {
        right_pos = pos + 1;
        left_pos = pos - 1;
      }

      // Get the number of dice, typically it will equal to the money
      // If the money bigger than 3, the player will have only 3 dice
      int num_dice = money[pos];
      if (num_dice >= 3) {
        num_dice = 3;
      }

      // Run the for loop, the time of loops will equal to num of dice
      for (int i = 0; i < num_dice; i++) {
        // Generate a pseudo random and limits it from 0 to 5
        int dice = rand();
        dice = dice % 6;
        faces current_die = die[dice];

        // Do the exact operation when the die get different face
        if (current_die == LEFT) {
          money[pos]--;
          money[left_pos]++;
          printf(" gives $1 to %s", names[left_pos]);
        } else if (current_die == RIGHT) {
          money[pos]--;
          money[right_pos]++;
          printf(" gives $1 to %s", names[right_pos]);
        } else if (current_die == CENTER) {
          money[pos]--;
          pot_balance++;
          printf(" puts $1 in the pot");
        } else if (current_die == PASS) {
          printf(" gets a pass");
        }

        // After each roll, we need to check whether winner is generated
        // Run the for loop, the time of loops will equal to num of player
        // If any one's money add balance in pot equals to total amount
        // Then the winner will generate.
        //
        // Sum: The sum of specific player's money with balance in pot
        // winner: when winner is generated, it will store its position
        // result: when winner is generated, it will be true
        for (int o = 0; o < num_player; o++) {
          int Sum = pot_balance + money[o];
          if (Sum == (3 * num_player)) {
            result = true;
            winner = o;
          }
        }
      }
      printf("\n");
    }
    // After each player finish his/her game, pos will be next player
    // There are 2 different situations due to edge case
    // When the position points last player, next player should be first one
    if (pos == num_player - 1) {
      pos = 0;
    } else {
      pos++;
    }
  }

  printf("%s wins the $%d pot with $%d left in the bank!\n", names[winner],
      pot_balance, money[winner]);
  return 0;
}
