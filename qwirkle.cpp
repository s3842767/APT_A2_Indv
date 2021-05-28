// Nabil Rusafee s3842767
// Enhancements Implemented:
//  + Added Help command to gameplay
//  + Fixed Invalid Input bug from group submission
//  + Fixed segfault upon quit game from group submission
//  + Added Colour to Tiles
//  + Fixed and improved gameplay and endgame

#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"
#include "Player.h"
#include "GameEngine.h"
#include "Types.h"

#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <iterator>
#include <algorithm>

#define EXIT_SUCCESS 0



void newGame();
void gameSession(GameEngine* gameEngine);
void printState(GameEngine* gameEngine);
void printCredits();
std::string getInput();
bool checkUppercase(std::string input);
void loadTile(std::string input, Board* board);
void loadHand(std::string input, LinkedList* hand);
void loadBag(std::string input, Tilebag* bag);
void loadGame(std::string filename);
bool help(std::string choice);

std::istream& safeGetline(std::istream& is, std::string& t);



// Returns int base on the choice player made
int parseCommand(GameEngine* gameEngine, std::string command, int round);

GameEngine *gameEngine;


int main(void)
{
    std::string input;
    std::cout << "Welcome to Quirkle!\n"<< std::endl
              << "--------------------" << std::endl;
    do {
        input = "";
        std::cout << "Menu" << std::endl
                  << "----" << std::endl
                  << std::endl
                  << "1. New Game" << std::endl
                  << "2. Load Game" << std::endl
                  << "3. Credits (Show Student Information)" << std::endl
                  << "4. Quit Game" << std::endl;

        input = getInput();

        if (input == "1") {
            newGame();
        } else if (input == "2") {
           std::cout << "Please enter the name of the file: "<< std::endl;
           std::string filename = getInput();
           loadGame(filename);
        } else if (input == "3") {
            printCredits();
        } else if (input == "4"){
           std::cout << "Goodbye!" << std::endl;
           exit(0);
        } else if (!std::cin.eof()){
            std::cout << "Please enter a valid option:"<< std::endl << std::endl;
        }
    } while (input != "4" && !std::cin.eof());\

    std::cout << "Goodbye!" << std::endl;
    
    return EXIT_SUCCESS;
}

std::string getInput() {
    std::cin.clear();
    std::string choice;
    std::cout << "> ";

    std::getline(std::cin, choice);
    while (std::cin.eof())
    {
        std::cout << "\nGoodbye";
        exit(0);
    }
    std::cout << std::endl;
    return choice;
}

bool checkUppercase(std::string input){
   bool isUpper = true;
   if (input.length() != 0 && input != " "){
      for (unsigned int i=0; i<input.length(); i++){
         if (!isupper(input[i])){
             isUpper = false;
         }
      }
   } else {
      isUpper = false;
   }
   if (!isUpper){
       std::cout << "Please enter a valid response:"<< std::endl;
   }
   return isUpper;
 
}

void newGame() {
    std::string player1Name = "";
    std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
    do{player1Name = getInput();}
    while (!checkUppercase(player1Name));
   

    std::string player2Name = "";
    std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
    do{player2Name = getInput();}
    while (!checkUppercase(player2Name));

    gameEngine = new GameEngine(player1Name, player2Name);
    std::cout << "Let's Play!" << std::endl;

    gameSession(gameEngine);
}


void gameSession(GameEngine* gameEngine)
{
   int round = 1;
   bool ignore = false;
   int choice = CHOICE_INVALID;
   std::string command = "";
   printState(gameEngine);

   while(choice != CHOICE_QUIT && choice != GAME_END)
   {
      do
      {
         ignore = false;
         command = getInput();
         choice = parseCommand(gameEngine, command, round);
         if(choice != CHOICE_QUIT)
         {
            printState(gameEngine);
            if(choice == CHOICE_HELP)
            {
               help(HELP_DEFAULT);
               choice = CHOICE_HELP;
            }
            if(choice == CHOICE_COMMAND)
            {
               help(HELP_COMMANDS);
               choice = CHOICE_HELP;
            }
            if(choice == CHOICE_RULES)
            {
               help(HELP_RULES);
               choice = CHOICE_HELP;
            }

            if(choice == CHOICE_PLACE)
            {
               gameEngine->getCurrentPlayer()->addPoint();
            }
            
            if(gameEngine->isGameEnd())
               choice = GAME_END;

            if(choice == CHOICE_PLACE)
            {
               if(ignore == false && gameEngine->getCurrentPlayerInt() == 0)
               {
                  std::cout << "Changin players..." << std::endl;
                  gameEngine->setCurrentPlayerInt(1);
                  gameEngine->setOtherPlayerInt(0);
                  printState(gameEngine);
                  ignore = true;
               }
               if(ignore == false && gameEngine->getCurrentPlayerInt() == 1)
               {
                  std::cout << "Changin players..." << std::endl;
                  gameEngine->setCurrentPlayerInt(0);
                  gameEngine->setOtherPlayerInt(1);
                  printState(gameEngine);
               }
               round++;
            }
         }
      }
      while(choice == CHOICE_INVALID || choice == CHOICE_PLACE || choice == CHOICE_HELP);
      
      if(choice != CHOICE_QUIT && choice != GAME_END)
      {
         printState(gameEngine);
         do
         {
            std::cout << "> ";
            std::cin >> command;
            if(gameEngine->isGameEnd())
               choice = GAME_END;
         } 
         while (choice == CHOICE_INVALID);
      }
   }

   if(choice == GAME_END)
      gameEngine->printEndResult();

   // Line below will only execute if choice == CHOICE_INVALID || GAME_END
   std::cout << "Goodbye" << std::endl;
   std::cout << std::endl;
}


void printState(GameEngine* gameEngine)
{
   std::cout << gameEngine->getCurrentPlayer()->getName() << ", it's your turn" << std::endl;
   std::cout << "Score for " << gameEngine->getCurrentPlayer()->getName() << ": " << gameEngine->getCurrentPlayer()->getScore() << std::endl;
   std::cout << "Score for " << gameEngine->getOtherPlayer()->getName() << ": " << gameEngine->getOtherPlayer()->getScore() << std::endl;
   gameEngine->getBoard()->printBoard();
   std::cout << std::endl;

   std::cout << "Your hand is" << std::endl;
   std::cout <<  gameEngine->getCurrentPlayer()->printTilesOnHand() << std:: endl;
   std::cout << std::endl;
}

int parseCommand(GameEngine* gameEngine, std::string command, int round)
{

   int returnVal = CHOICE_INVALID;
   
   std::vector<std::string> commands;
   int wordIter = 0;
   
   std::stringstream stream(command);

   std::string word;

   commands.clear();
   
   while (stream >> word)
   {
      commands.push_back(word);
   }

   if(commands[wordIter] == ACTION_HELP)
   {
      if(commands.size() > 1)
      {
         wordIter++;
         if(commands[wordIter] == HELP_COMMANDS)
         {
            return CHOICE_COMMAND;
         }
         if(commands[wordIter] == HELP_RULES)
         {
            return CHOICE_RULES;
         }         
      }
      return CHOICE_HELP;
   }


   // Can use == as we're using std::string, not c-style strings
   if(commands[wordIter] == ACTION_PLACE)
   {
      wordIter++;
      std::string tiles = commands[wordIter];

      wordIter++;
      word = commands[wordIter]; // reuse variable

      if(word == "at")
      {
         wordIter++;
         std::string location = commands[wordIter];
         if(round > 1)
         {
            if(!gameEngine->isLegalPos(tiles, location))
            {
               std::cout << "Not a Legal Position!" << std::endl;
               returnVal = CHOICE_INVALID;
            }
            else
            {
               Tile* tile = gameEngine->getCurrentPlayer()->getTile(tiles);

               if(tile == nullptr)
               {
                  returnVal = CHOICE_INVALID;
               }
               if(tile != nullptr)
               {
                  gameEngine->place(*(gameEngine->getCurrentPlayer()), tile, location);
                  gameEngine->replaceTileOnHand();
                  returnVal = CHOICE_PLACE;
               }
            }
         }
         if(round == 1)
         {
            Tile* tile = gameEngine->getCurrentPlayer()->getTile(tiles);

            gameEngine->place(*(gameEngine->getCurrentPlayer()), tile, location);
            gameEngine->replaceTileOnHand();
            returnVal = CHOICE_PLACE;
         }
      }
      
   }
   else if(commands[wordIter] == ACTION_REPLACE)
   {
      wordIter++;
      std::string tile = commands[wordIter];

      if(gameEngine->getCurrentPlayer()->checkTileOnHand(tile))
         {
            Tile* repTile = gameEngine->getCurrentPlayer()->getTile(tile);
            gameEngine->replaceTileOnHand();
            delete repTile;
            returnVal = CHOICE_PLACE;
         }
   }
   else if(word == ACTION_QUIT || std::cin.eof())
   {
      returnVal = CHOICE_QUIT;
   }
   else
   {
      std::cout << "Invalid Input" << std::endl;
      returnVal = CHOICE_INVALID;
   }

   return returnVal;
}

bool help(std::string choice)
{
   if(choice == HELP_COMMANDS)
   {
      std::cout << "To Place a tile:" << std::endl
                << "'place [TILE] at [COORDINATE]'" << std::endl
                << std::endl
                << "To replace a tile in your hand:" << std::endl
                << "'replace [TILE]'" << std::endl
                << std::endl
                << "To quit game:" << std::endl
                << "'quit'" << std::endl
                << std::endl;
                return 0;
   }
   if(choice == HELP_RULES)
   {
      std::cout << "How to play qwirkle:" << std::endl
                << "-------------------- " << std::endl
                << "The objective for qwirkle is to make lines of tiles with the same" << std::endl
                << "shape or colour. At the start of the game, each player is given a hand of" << std::endl
                << "6 random tiles that they can place on the board." << std::endl
                << "Players must create lines with their tiles" << std::endl
                << "'quit'" << std::endl
                << std::endl;
                return 0;
   }
   std::cout << "Help commands:" << std::endl
                   << "'help commands' - view commands" << std::endl
                   << "'help rules' - view qwirkle rules" << std::endl
                   << std::endl;
   return 0;
}


// This function would work similarly to std::getline, but will 
// remove special characters like '\r' in case a file uses it (i.e. Windows)
// code source: https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

   bool breakLoop = false;

   while(!breakLoop)
   {
      int c = sb->sbumpc();

      if(c == '\n')
         breakLoop = true;
      else if(c == '\r')
      {
         if(sb->sgetc() == '\n')
            sb->sbumpc();
         breakLoop = true;
      }
      else if(c == std::streambuf::traits_type::eof())
      {
         if(t.empty())
            is.setstate(std::ios::eofbit);
         breakLoop = true;
      }
      else
         t += (char)c;
   }

   return is;
}


void printCredits() {
    std::cout   << "------------------" << std::endl << std::endl
                << "Ian Romito Descham" << std::endl
                << "s3665571" << std::endl
                << "s3665571@student.rmit.edu.au" << std::endl 
                << std::endl
                << "Nabil Rusafee" << std::endl
                << "s3842767" << std::endl
                << "s3842767@student.rmit.edu.au" << std::endl 
                << std::endl
                << "Sophia Nguyen" << std::endl
                << "s3707659" << std::endl
                << "s3707659@student.rmit.edu.au" << std::endl 
                << std::endl
                << "Zijian Wang" << std::endl
                << "s3608290" << std::endl
                << "s3608290@student.rmit.edu.au" << std::endl 
                << std::endl;
}

// Expected: no spaces inbetween values and comma delimited
void loadTile(std::string input, Board* board)
{
    std::istringstream iss(input);
    std::string token;
    std::string token2;

    std::string tileCode, pos;

    char colFirst, colSecond, row;
    int colNum, rowNum = 0;
    Colour colour = 'Z';
    Shape shape = 0;

    int i = 0;
    while(std::getline(iss, token, ','))
    {
        std::istringstream buffer(token);
        while(std::getline(buffer, token2, '@'))
        {
            if(i == 0)
            {
                tileCode = token2;

                colour = token2.at(0);
                shape = token2.at(1) - '0';

                i++;
            }
            else if(i == 1)
            {
                pos = token2;

                colFirst = pos.at(1);
                colSecond = '0';

                // Find the second digit if applicable
                if(pos.length() == 3)
                    colSecond = pos.at(2);

                row = pos.at(0);

               // Get row in integer/number
               int currRow = 'A';
               rowNum = 0; // initialize rowNum
               while(currRow != row)
               {
                  rowNum++;
                  currRow++;
               }

                // this should convert character to integer 
                // (source: https://stackoverflow.com/questions/439573/how-to-convert-a-single-char-into-an-int)
                colNum = colFirst - '0';

                if(colSecond != '0')
                {
                    // Convert, then multiply colSecond by 10 so it becomes second digit
                    colNum += (colSecond - '0')*10;
                }

                i++;
            }
            else if(i == 2)
            {
                Coordinate coor(rowNum, colNum);
                board->addTileToBoard(&coor, new Tile(colour, shape));
                i = 0;
            }
        }
            
    }
}

// Expected: no spaces inbetween values and comma delimited
void loadHand(std::string input, LinkedList* hand)
{
   std::istringstream iss(input);
   std::string token;

   while(std::getline(iss, token, ','))
   {
      std::istringstream buffer(token);
      hand->addFront(new Tile(token.at(0), token.at(1) - '0'));
   }
}

// Expected: no spaces inbetween values and comma delimited
void loadBag(std::string input, Tilebag* bag)
{
   std::istringstream iss(input);
   std::string token;

   while(std::getline(iss, token, ','))
   {
      std::istringstream buffer(token);
      bag->add(new Tile(token.at(0), token.at(1) - '0'));
   }
}

// Expected: correct file format, board size is assumed fixed 26 x 26
void loadGame(std::string filename){

    // std::ifstream file; 
    // file.open(filename);

    // std::string line;

    // if (file){
    //     while(getline(file, line)){
    //         players[PLAYER1]->setName(line);
    //         players[PLAYER1]->setScore(std::stoi(line));

    //     }
    // }

    // file.close();

   std::string buffer;
   std::ifstream infile(filename);
   // while(std::getline(infile, buffer))
   //     std::cout << buffer << std::endl;
   
   // If file don't exist
   if(!infile.fail())
   {
      // Create player 1
      safeGetline(infile, buffer);
      Player* player1 = new Player(buffer);

      // Load player 1 score
      safeGetline(infile, buffer);
      player1->setScore(std::stoi(buffer));
      
      // Load player 1 hand
      safeGetline(infile, buffer);
      LinkedList* player1Hand = new LinkedList();
      loadHand(buffer, player1Hand);
      player1->setHand(player1Hand);
      // delete player1Hand;

      // Create player 2
      safeGetline(infile, buffer);
      Player* player2 = new Player(buffer);

      // Load player 2 score
      safeGetline(infile, buffer);
      player2->setScore(std::stoi(buffer));
      
      // Load player 2 hand
      safeGetline(infile, buffer);
      LinkedList* player2Hand = new LinkedList();
      loadHand(buffer, player2Hand);
      player2->setHand(player2Hand);
      // delete player1Hand;

      // Load board size
      safeGetline(infile, buffer);
      // Do nothing as board is assumed 26 x 26 in size

      // Load board tiles
      safeGetline(infile, buffer);
      Board* board = new Board();
      loadTile(buffer, board);

      // Load bag tiles
      safeGetline(infile, buffer);
      Tilebag* bag = new Tilebag();
      loadBag(buffer, bag);

      GameEngine* engine = new GameEngine(player1, player2, board, bag);

      safeGetline(infile, buffer);
      // std::string yes = (buffer == player1->getName()) ? "YES" : "NO";
      // std::cout << buffer << "," << player1->getName() << "," << yes << std::endl;

      // Comparison failed might be caused by leftover whitespace,
      // i.e. '\n' is removed, but no '\r'
      if(buffer == player1->getName())
         engine->setCurrentPlayer(PLAYER1);
      else 
         engine->setCurrentPlayer(PLAYER2);

      infile.close();

      gameSession(engine);

      delete engine;
   }
   else
      infile.close();
}
