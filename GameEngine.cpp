#include "GameEngine.h"
#include <string>
#include <sstream>


GameEngine::GameEngine(std::string player1Name, std::string player2Name)
{
    this->players[PLAYER1] = new Player(player1Name);
    this->players[PLAYER2] = new Player(player2Name);
    this->currentPlayer = PLAYER1;
    this->otherPlayer = PLAYER2;

    tilebag->shuffle();

    this->players[PLAYER1]->setHand(new LinkedList());
    this->players[PLAYER2]->setHand(new LinkedList());

    for (int index =0; index < NO_PLAYERS; index++){
        for(int counter =0; counter < NO_TILES_IN_HAND; counter++){
            std::cout << counter << std::endl;
            players[index]->addTileToHand((tilebag->getTile()));
        }
            
    }
    for (int i = 0; i < NO_PLAYERS; i++){
        std::cout << players[i]->printTilesOnHand() << std::endl;
    }

    
    board->printBoard();

  

}

GameEngine::GameEngine(Player* player1, Player* player2, Board* board, Tilebag* bag)
{
    this->players[PLAYER1] = player1;
    this->players[PLAYER2] = player2;
    this->board = board;
    this->tilebag = bag;
}

GameEngine::~GameEngine(){
    for (int i =0; i<NO_PLAYERS; i++){
        delete players[i];
    }
    delete this->tilebag;
    delete this->board;
}

void GameEngine::place(Player& player, Tile* tile, std::string pos)
{
    convertStringPosToInt(pos);
    if(pos.size() == 2)
    {
        Coordinate* coords = new Coordinate(y, x);
        bool chkCond = board->addTileToBoard(coords, tile);
        if(chkCond == false)
        {
            std::cout << "Coordinate already Occupied" << std::endl;
        }
        delete coords;
    }
    
}

void GameEngine::convertStringPosToInt(std::string pos)
{
    // std::stringstream lc;
    // lc << pos[1];
    // lc >> x; // converts number to int

    // starting and maximum character position for x
    const int xStart = 1;
    const int xMaxEnd = 2;

    // convert substring to integer, 
    // partial source: https://stackoverflow.com/questions/6383880/getting-stringstream-to-read-from-character-a-to-b-in-a-string
    x = std::stoi(pos.substr(xStart, xMaxEnd-xStart+1));

    char c = pos.at(0); // converts letter to char, which is then assigned its corresponding int
    int alCount = 0;
    for(char i = 'A'; i <= 'Z'; i++)
    {
        if(i == c)
        {
            y = alCount;
        }
        alCount++;
    }
    
}

bool GameEngine::isLegalPos(std::string tile, std::string location)
{   
    bool isLegal = true;   
    
    char row = location.at(FIRST_CHAR);
    int col = std::stoi(location.substr(SECOND_CHAR, location.length()));

    char tileColour= tile.at(FIRST_CHAR) - 0;
    int tileShape = tile.at(SECOND_CHAR)-0;


    if(board->getTileAtPos(row, col) != nullptr || location.length() != 2 || location.length() != 3){
        isLegal = false;
    }



    
    //checks tile above has at least one similar element and is not the same
    if (board->getTileAtPos(row -1, col) != nullptr){
        if ((board->getTileAtPos(row - 1, col)->getColour() != tileColour && board->getTileAtPos(row - 1, col)->getShape() != tileShape) || 
        (board->getTileAtPos(row - 1, col)->getColour() == tileColour && board->getTileAtPos(row -1, col)->getShape() == tileShape)){
            isLegal = false; 
        }   
    }

     //checks tile underneath has at least one similar element and is not the same
    if (board->getTileAtPos(row + 1, col) != nullptr){
        if ((board->getTileAtPos(row + 1, col)->getColour() != tileColour && board->getTileAtPos(row + 1, col)->getShape() != tileShape) || 
        (board->getTileAtPos(row + 1, col)->getColour() == tileColour && board->getTileAtPos(row + 1, col)->getShape() == tileShape)){
            isLegal = false; 
        }   
    }

    //checks tile to the left has at least one similar element and is not the same
    if (board->getTileAtPos(row, col - 1) != nullptr){
        if ((board->getTileAtPos(row, col - 1)->getColour() != tileColour && board->getTileAtPos(row, col -1)->getShape() != tileShape) || 
        (board->getTileAtPos(row, col -1)->getColour() == tileColour && board->getTileAtPos(row, col -1)->getShape() == tileShape)){
            isLegal = false; 
        }   
    }

    //checks tile to the right has at least one similar element and is not the same
    if (board->getTileAtPos(row, col + 1) != nullptr){
        if ((board->getTileAtPos(row, col + 1)->getColour() != tileColour && board->getTileAtPos(row, col + 1)->getShape() != tileShape) || 
        (board->getTileAtPos(row, col + 1)->getColour() == tileColour && board->getTileAtPos(row, col + 1)->getShape() == tileShape)){
            isLegal = false; 
        }   
    }

    return isLegal;
}

void GameEngine::replaceTileOnHand()
{
    getCurrentPlayer()->addTileToHand(tilebag->getTile());
}


bool GameEngine::isGameEnd() const
{
    bool end = false;

    if(this->tilebag->getSize() == 0
        && this->players[PLAYER1]->getHand()->getSize() == 0
        && this->players[PLAYER2]->getHand()->getSize() == 0)
    {
        end = true;
    }

    return end;
}

void GameEngine::printEndResult()
{
    std::cout   << "Game over" << std::endl;
    std::cout   << "Score for " << this->players[PLAYER1]->getName() << ": "
                << this->players[PLAYER1]->getScore() << std::endl;
    std::cout   << "Score for " << this->players[PLAYER2]->getName() << ": "
                << this->players[PLAYER1]->getScore() << std::endl;
    
    if(this->players[PLAYER1]->getScore() > this->players[PLAYER2]->getScore())
        std::cout << "Player " << this->players[PLAYER1]->getName() << " won!";
    else if(this->players[PLAYER2]->getScore() > this->players[PLAYER1]->getScore())
        std::cout << "Player " << this->players[PLAYER2]->getName() << " won!";
    else
        std::cout << "Tie!";

    std::cout << std::endl;
}

Board* GameEngine::getBoard(){
    return board;
}

Player* GameEngine::getPlayer(int player){
    return players[player];
}

Player* GameEngine::getCurrentPlayer(){
    return players[currentPlayer];
}

Player* GameEngine::getOtherPlayer(){
    return players[otherPlayer];
}


void GameEngine::setCurrentPlayer(int nextPlayer){
    currentPlayer = nextPlayer;
    otherPlayer = (currentPlayer == 1) ? 0 : 1;
}

void GameEngine::loadGame(std::string filename){


    std::ifstream file; 
    file.open(filename);

    std::string line;

    if (file){
        while(getline(file, line)){
            players[PLAYER1]->setName(line);
            players[PLAYER1]->setScore(std::stoi(line));

        }
    }

    file.close();

}

void GameEngine::saveGame(std::string filename) {
    //writes in name, score and hand of each player
    std::ofstream file;
    file.open(filename);
    std::string output= "";
    
    for (unsigned int index = 0; index < (sizeof(players)/sizeof(*players)); index++){
        file << players[index]->getName() << "\n" << players[index]->getScore() << "\n";
        for (unsigned int counter = 0; counter< players[index]->getHand()->getSize(); counter++){
            file << players[index]->getHand()->get(counter)->getColour() << players[index]->getHand()->get(counter)->getShape();
        }
    }

    //writes in dimensions of board: width,height 
    file << SIZE_ROW << "," << SIZE_COL << std::endl;

    //lists all tiles in tilebag
    for (unsigned int index = 0; index < tilebag->getSize(); index++){
        file << tilebag->get(index)->getColour() << tilebag->get(index)->getShape();
    }
  
  
    file << players[currentPlayer]->getName();

    file.close();


}

