#include "game.h"

/*Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
game *make_game(int rows, int cols) {
  // Dynamically allocate memory for game and cells (DO NOT modify this)
  game *mygame = malloc(sizeof(game));
  mygame->cells = malloc(rows * cols * sizeof(cell));

  // Initialize all other variables in game struct
  mygame->rows = rows;
  mygame->cols = cols;
  mygame->score = 0;

  // Initialize all cells to -1
  for (int i = 0; i < rows * cols; i++) {
    mygame->cells[i] = -1;
  }

  return mygame;
}

/*Given a game structure that is passed by reference, change the
  game structure to have the given number of rows and columns. Initialize
  the score and all elements in the cells to -1. Make sure that any
  memory previously allocated is not lost in this function.
*/
void remake_game(game **_cur_game_ptr, int new_rows, int new_cols) {
  /*Frees dynamically allocated memory used by cells in previous game,
   then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
  free((*_cur_game_ptr)->cells);
  (*_cur_game_ptr)->cells = malloc(new_rows * new_cols * sizeof(cell));

  // Re-initialize all other variables in game struct
  (*_cur_game_ptr)->rows = new_rows;
  (*_cur_game_ptr)->cols = new_cols;
  (*_cur_game_ptr)->score = 0;

  // Initialize all cells to -1
  for (int i = 0; i < new_rows * new_cols; i++) {
    (*_cur_game_ptr)->cells[i] = -1;
  }

  return;
}

/*Deallocate any memory acquired with malloc associated with the given game
 instance. This includes any substructures the game data structure contains.
 Do not modify this function.*/
void destroy_game(game *cur_game) {
  free(cur_game->cells);
  free(cur_game);
  cur_game = NULL;
  return;
}

/*Given a game, a row, and a column, return a pointer to the corresponding
  cell on the game. (See game.h for game data structure specification)
  This function should be handy for accessing game cells. Return NULL
  if the row and col coordinates do not exist.
*/
cell *get_cell(game *cur_game, int row, int col) {
  if (row > cur_game->rows || col > cur_game->cols) {
    return NULL;
  }
  return &cur_game->cells[row * cur_game->cols + col];
}

/* Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
int move_w(game *cur_game) {
  // Define and Initialize variables
  int col, row, k;

  // Variable to determine if board has been changed
  int changed = 0;

  // Loop through rows and cols of board
  for (col = 0; col < cur_game->cols; col++) {
    for (row = 0; row < cur_game->rows; row++) {
      // Merging logic for cells
      // If cell is non blank carry out merging process
      if (cur_game->cells[row * cur_game->cols + col] != -1) {
        // Find next non-blank cell
        for (k = row + 1; k < cur_game->rows; k++) {
          // If cells are equal, merge and update score
          if (cur_game->cells[k * cur_game->cols + col] != -1) {
            if (cur_game->cells[k * cur_game->cols + col] ==
                cur_game->cells[row * cur_game->cols + col]) {
              cur_game->cells[row * cur_game->cols + col] *= 2;
              cur_game->score += cur_game->cells[row * cur_game->cols + col];
              cur_game->cells[k * cur_game->cols + col] = -1;
              changed = 1;
              break;
            } else {
              break;
            }
          }
        }
      }
      // Shifting logic for cells
      // If cell is blank then move next non-blank cell into current cell
      else {
        for (k = row + 1; k < cur_game->rows; k++) {
          if (cur_game->cells[k * cur_game->cols + col] != -1) {
            cur_game->cells[row * cur_game->cols + col] =
                cur_game->cells[k * cur_game->cols + col];
            cur_game->cells[k * cur_game->cols + col] = -1;
            changed = 1;
            row--;
            break;
          }
        }
      }
    }
  }
  return changed;
};

/* Slides all of the tiles in cur_game down. If a tile matches with the
   one below it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
int move_s(game *cur_game) {
  // Define and Initialize variables
  int col, row, k;

  // Variable to determine if board has been changed
  int changed = 0;

  // Loop through rows and cols of board
  for (col = 0; col < cur_game->cols; col++) {
    for (row = cur_game->rows - 1; row >= 0; row--) {
      // Merging logic for cells
      // If cell is non blank carry out merging process
      if (cur_game->cells[row * cur_game->cols + col] != -1) {
        // Find next non-blank cell
        for (k = row - 1; k >= 0; k--) {
          // If cells are equal, merge and update score
          if (cur_game->cells[k * cur_game->cols + col] != -1) {
            if (cur_game->cells[k * cur_game->cols + col] ==
                cur_game->cells[row * cur_game->cols + col]) {
              cur_game->cells[row * cur_game->cols + col] *= 2;
              cur_game->score += cur_game->cells[row * cur_game->cols + col];
              cur_game->cells[k * cur_game->cols + col] = -1;
              changed = 1;
              break;
            } else {
              break;
            }
          }
        }
      }
      // Shifting logic for cells
      // If cell is blank then move next non-blank cell into current cell
      else {
        for (k = row - 1; k >= 0; k--) {
          if (cur_game->cells[k * cur_game->cols + col] != -1) {
            cur_game->cells[row * cur_game->cols + col] =
                cur_game->cells[k * cur_game->cols + col];
            cur_game->cells[k * cur_game->cols + col] = -1;
            changed = 1;
            row++;
            break;
          }
        }
      }
    }
  }
  // Return value based on whether board was changed
  return changed;
};

/* Slides all of the tiles in cur_game left. If a tile matches with the
   one left of it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
int move_a(game *cur_game) {
  // Define and Initialize variables
  int row, col, k;

  // Variable to determine if board has been changed
  int changed = 0;

  // Loop through rows and cols of board
  for (row = 0; row < cur_game->rows; row++) {
    for (col = 0; col < cur_game->cols; col++) {
      // Merging logic for cells
      // If cell is non blank carry out merging process
      if (cur_game->cells[row * cur_game->cols + col] != -1) {
        // Find next non-blank cell
        for (k = col + 1; k < cur_game->cols; k++) {
          // If cells are equal, merge and update score
          if (cur_game->cells[row * cur_game->cols + k] != -1) {
            if (cur_game->cells[row * cur_game->cols + k] ==
                cur_game->cells[row * cur_game->cols + col]) {
              cur_game->cells[row * cur_game->cols + col] *= 2;
              cur_game->score += cur_game->cells[row * cur_game->cols + col];
              cur_game->cells[row * cur_game->cols + k] = -1;
              changed = 1;
              break;
            } else {
              break;
            }
          }
        }
      }
      // Shifting logic for cells
      // If cell is blank then move next non-blank cell into current cell
      else {
        for (k = col + 1; k < cur_game->cols; k++) {
          if (cur_game->cells[row * cur_game->cols + k] != -1) {
            cur_game->cells[row * cur_game->cols + col] =
                cur_game->cells[row * cur_game->cols + k];
            cur_game->cells[row * cur_game->cols + k] = -1;
            changed = 1;
            col--;
            break;
          }
        }
      }
    }
  }
  // Return value based on whether board was changed
  return changed;
};

/* Slides all of the tiles in cur_game right. If a tile matches with the
   one right of it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
int move_d(game *cur_game) {
  // Define and Initialize variables
  int row, col, k;

  // Variable to determine if board has been changed
  int changed = 0;

  // Loop through rows and cols of board
  for (row = 0; row < cur_game->rows; row++) {
    for (col = cur_game->cols - 1; col >= 0; col--) {
      // Merging logic for cells
      // If cell is non blank carry out merging process
      if (cur_game->cells[row * cur_game->cols + col] != -1) {
        // Find next non-blank cell
        for (k = col - 1; k >= 0; k--) {
          // If cells are equal, merge and update score
          if (cur_game->cells[row * cur_game->cols + k] != -1) {
            if (cur_game->cells[row * cur_game->cols + k] ==
                cur_game->cells[row * cur_game->cols + col]) {
              cur_game->cells[row * cur_game->cols + col] *= 2;
              cur_game->score += cur_game->cells[row * cur_game->cols + col];
              cur_game->cells[row * cur_game->cols + k] = -1;
              changed = 1;
              break;
            } else {
              break;
            }
          }
        }
      }
      // Shifting logic for cells
      // If cell is blank then move next non-blank cell into current cell
      else {
        for (k = col - 1; k >= 0; k--) {
          if (cur_game->cells[row * cur_game->cols + k] != -1) {
            cur_game->cells[row * cur_game->cols + col] =
                cur_game->cells[row * cur_game->cols + k];
            cur_game->cells[row * cur_game->cols + k] = -1;
            changed = 1;
            col++;
            break;
          }
        }
      }
    }
  }
  // Return value based on whether board was changed
  return changed;
}

/* Given the current game check if there are any legal moves on the board.
  There are no legal moves if sliding in any direction will not cause the game
  to change. Return 1 if there are possible legal moves, 0 if there are none.
 */
int legal_move_check(game *cur_game) {
  // YOUR CODE STARTS HERE
  int row, col;

  // Looping through rows and columns of board
  for (col = 0; col < cur_game->cols; col++) {
    for (row = 0; row < cur_game->rows; row++) {
      // Checking for any empty cells
      if (cur_game->cells[row * cur_game->cols + col] == -1){
        return 1;
      }
      // Checking for matching cells above and below current cell
      if (row > 0 && row < cur_game->rows){
        if (cur_game->cells[row * cur_game->cols + col] == cur_game->cells[(row+1) * cur_game->cols + col]){
          return 1;
        }
        else if (cur_game->cells[row * cur_game->cols + col] == cur_game->cells[(row-1) * cur_game->cols + col]){
          return 1;
        }
      }
      // Checking for matching cells left and right of current cell
      if (row > 0 && row < cur_game->rows){
        if (cur_game->cells[row * cur_game->cols + col] == cur_game->cells[row * cur_game->cols + (col+1)]){
          return 1;
        }
        else if (cur_game->cells[row * cur_game->cols + col] == cur_game->cells[row * cur_game->cols + (col-1)]){
          return 1;
        }
      }
    }
  }
  return 0;
}

/* code below is provided and should not be changed */

void rand_new_tile(game *cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols)
 * to get a random value between 0 and (rows*cols)-1.
 */
{

  cell *cell_ptr;
  cell_ptr = cur_game->cells;

  if (cell_ptr == NULL) {
    printf("Bad Cell Pointer.\n");
    exit(0);
  }

  // check for an empty cell
  int emptycheck = 0;
  int i;

  for (i = 0; i < ((cur_game->rows) * (cur_game->cols)); i++) {
    if ((*cell_ptr) == -1) {
      emptycheck = 1;
      break;
    }
    cell_ptr += 1;
  }
  if (emptycheck == 0) {
    printf(
        "Error: Trying to insert into no a board with no empty cell. The "
        "function rand_new_tile() should only be called after tiles have "
        "succesfully moved, meaning there should be at least 1 open spot.\n");
    exit(0);
  }

  int ind, row, col;
  int num;
  do {
    ind = rand() % ((cur_game->rows) * (cur_game->cols));
    col = ind % (cur_game->cols);
    row = ind / cur_game->cols;
  } while (*get_cell(cur_game, row, col) != -1);
  //*get_cell(cur_game, row, col) = 2;
  num = rand() % 20;
  if (num <= 1) {
    *get_cell(cur_game, row, col) = 4; // 1/10th chance
  } else {
    *get_cell(cur_game, row, col) = 2; // 9/10th chance
  }
}

int print_game(game *cur_game) {
  cell *cell_ptr;
  cell_ptr = cur_game->cells;

  int rows = cur_game->rows;
  int cols = cur_game->cols;
  int i, j;

  printf("\n\n\nscore:%d\n", cur_game->score);

  printf("\u2554"); // topleft box char
  for (i = 0; i < cols * 5; i++)
    printf("\u2550"); // top box char
  printf("\u2557\n"); // top right char

  for (i = 0; i < rows; i++) {
    printf("\u2551"); // side box char
    for (j = 0; j < cols; j++) {
      if ((*cell_ptr) == -1) { // print asterisks
        printf(" **  ");
      } else {
        switch (*cell_ptr) { // print colored text
        case 2:
          printf("\x1b[1;31m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 4:
          printf("\x1b[1;32m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 8:
          printf("\x1b[1;33m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 16:
          printf("\x1b[1;34m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 32:
          printf("\x1b[1;35m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 64:
          printf("\x1b[1;36m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 128:
          printf("\x1b[31m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 256:
          printf("\x1b[32m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 512:
          printf("\x1b[33m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 1024:
          printf("\x1b[34m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 2048:
          printf("\x1b[35m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 4096:
          printf("\x1b[36m%04d\x1b[0m ", (*cell_ptr));
          break;
        case 8192:
          printf("\x1b[31m%04d\x1b[0m ", (*cell_ptr));
          break;
        default:
          printf("  X  ");
        }
      }
      cell_ptr++;
    }
    printf("\u2551\n"); // print right wall and newline
  }

  printf("\u255A"); // print bottom left char
  for (i = 0; i < cols * 5; i++)
    printf("\u2550"); // bottom char
  printf("\u255D\n"); // bottom right char

  return 0;
}

// returns 1 if legal move is possible after
// input is processed
int process_turn(const char input_char, game *cur_game) {
  int rows, cols;
  char buf[200];
  char garbage[2];
  int move_success = 0;

  switch (input_char) {
  case 'w':
    move_success = move_w(cur_game);
    break;
  case 'a':
    move_success = move_a(cur_game);
    break;
  case 's':
    move_success = move_s(cur_game);
    break;
  case 'd':
    move_success = move_d(cur_game);
    break;
  case 'q':
    destroy_game(cur_game);
    printf("\nQuitting..\n");
    return 0;
    break;
  case 'n':
  // get row and col input for new game
  dim_prompt:
    printf("NEW GAME: Enter dimensions (rows columns):");
    while (NULL == fgets(buf, 200, stdin)) {
      printf("\nProgram Terminated.\n");
      return 0;
    }

    if (2 != sscanf(buf, "%d%d%1s", &rows, &cols, garbage) || rows < 0 ||
        cols < 0) {
      printf("Invalid dimensions.\n");
      goto dim_prompt;
    }

    remake_game(&cur_game, rows, cols);

    move_success = 1;

  default: // any other input
    printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
  }

  if (move_success ==
      1) { // if movement happened, insert new tile and print the game.
    rand_new_tile(cur_game);
    print_game(cur_game);
  }

  if (legal_move_check(cur_game) ==
      0) { // check if the newly spawned tile results in game over.
    printf("Game Over!\n");
    return 0;
  }
  return 1;
}
