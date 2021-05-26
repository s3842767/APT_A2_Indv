#define ACTION_PLACE    "place"
#define ACTION_REPLACE  "replace"
#define ACTION_SAVE     "save"
#define ACTION_QUIT     "quit"
#define ACTION_HELP     "help"

// int returned by the parseCommand function
#define CHOICE_PLACE 10
#define CHOICE_REPLACE 20
#define CHOICE_SAVE 30
#define CHOICE_QUIT 40
#define CHOICE_INVALID 50
#define CHOICE_COMMAND 60
#define CHOICE_RULES 70
#define CHOICE_HELP 80
#define GAME_END 1001

#define HELP_RULES      "rules"
#define HELP_COMMANDS   "commands"

#define PLAYER_HAND         6
#define NO_PLAYERS          2
#define NO_TILES_IN_HAND    6
#define COLOURS_SIZE        6
#define SHAPES_SIZE         6
#define TILE_DUPLICATION    2
#define GRID_LENGTH         26
#define FIRST_CHAR          0
#define SECOND_CHAR         1

#define TRED    "\u001b[31m"
#define TORANGE "\u001b[33m"
#define TYELLOW "\u001b[33;1m"
#define TGREEN  "\u001b[32m"
#define TBLUE   "\u001b[34m"
#define TPURPLE "\u001b[35m"
#define TWHITE "\u001b[37m"