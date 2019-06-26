#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}
/* Defining all the static members outside class  according to rule in C++*/
// initialize all static variables to default values
Game::GameState Game::gameState;
bool Game::gameOver=false;
int Game::panel[4][4];
Player* Game::player=nullptr;

void Game::initGame()   // initilized basics of game
{
    srand(time(0));     // seed value of time in srand function to generate clock based random number
    gameState=GameState::PLAYING;   // game state changed to PLAYING
    rlutil::setConsoleTitle("2048 Game Console Version");   // set console title, using rlutil header file
    rlutil::hidecursor();     // hides the cursor

}
void Game::startGame()  // handles the game
{
    initGame(); // firstly initialize Game
    while(gameState!=GameState::QUIT)   // run game till we are not QUITing.
    {
        rlutil::cls();  // clear screen
        showGameTitle();  showMenu();   // show game title and main menu
        char menuChoice;    // to store user choice for main menu
        do
        {
            menuChoice=takeGameInput();   // take input user choice
            switch(menuChoice)  // handle user choice for various menu options
            {
                case '3':   // case EXIT
                    gameState=GameState::QUIT;  // indicate Game Quit Status
                    break;
                case '1':       // case PLAY
                    gamePlay();     // Start new GamePlay
                    _getch();   // wait for a keyboard key to be pressed
                    break;
                case '2':   // case HIGH SCORE
                    showHighScoreTable();   // show high score table
                    _getch();   // wait for a key
                    break;
            }
        }while(menuChoice<'1' || menuChoice>'3');   // continue take input till correct choice is made
    }
}

void Game::showGameTitle()  // shows the game title
{
    rlutil::setColor(rlutil::COLORS::WHITE);   // set text color
    /* Display the 2048 Game Title */
    std::cout<<"\n";
    std::cout<<"\t  ##########        ########              ##        ########         \n";
    std::cout<<"\t #############     ##########           ####       ##      ##        \n";
    std::cout<<"\t           ###    ##        ##        ##  ##      ##        ##       \n";
    std::cout<<"\t         ###      ##        ##       ##   ##       ##      ##        \n";
    std::cout<<"\t       ###        ##        ##     ##     ##        ########         \n";
    std::cout<<"\t     ###          ##        ##    #############    ##      ##        \n";
    std::cout<<"\t    ###           ##        ##   ##############   ##        ##       \n";
    std::cout<<"\t   ###            ##        ##            ##       ##      ##        \n";
    std::cout<<"\t  ###########      ##########             ##        ##    ##         \n";
    std::cout<<"\t #############      ########              ##         ######          \n\n\n";
    rlutil::setColor(Utilities::defaultTextColor);  // reset text color to default
}

void Game::showMenu()   // shows the main menu
{
    // show the menu using print function in Utility with extra options of formating output, refer Utilities Class
    Utilities::print("\t\t\t    -----+ MAIN MENU +-----\n",true,rlutil::COLORS::LIGHTRED,0);
    Utilities::print("\t\t\t         1. PLAY GAME ",true,rlutil::COLORS::LIGHTGREEN,0);
    Utilities::print("\t\t\t         2. HIGH SCORES ",true,rlutil::COLORS::LIGHTGREEN,0);
    Utilities::print("\t\t\t         3. QUIT ",true,rlutil::COLORS::LIGHTGREEN,0);
    Utilities::print("\n\t\t\t      ( Enter Your Choice )       ",true,rlutil::COLORS::LIGHTBLUE,Utilities::defaultDelay);
}

void Game::gamePlay()   // handles the new GamePlay
{
    rlutil::cls();  // clear the screen
    resetGame();    // reset game for a fresh GamePlay
    gameLoop();     // run game loop which handles all game things
}

void Game::gameLoop()   // continuesly runs the game
{
    while(!gameOver && !checkWin()) // continue game till GameOver or user Wins the Game
    {
        showGamePlayPanel();    // show the GamePlay Panel
        char actionKey; // for user response for Gameplay Action
        do
        {
            actionKey=takeGameInput();  // take user action
            actionKey=toupper(actionKey);// convert the character to uppercase for ease of handling
        }while(actionKey!='W' && actionKey!='S' && actionKey!='A' && actionKey!='D' && actionKey!='X');   // continue to read till incorrect action choosen
        handleGameInput(actionKey);     // handles the user action in GamePlay
    }
    rlutil::cls();  // clear the screen
    if(gameOver)    // if Game Over for Player
    {
        // display the message
        Utilities::print("\n\t\tGame Over, Better Luck Next Time...",true,rlutil::COLORS::LIGHTRED,Utilities::defaultDelay);
    }
    else    // else if Player Wins the Game
    {
        // display the message
        Utilities::print("\n\t\tYou WON the Game...",true,rlutil::COLORS::LIGHTGREEN,Utilities::defaultDelay);
        rlutil::msleep(500);
        Utilities::print("\n\t\tPlease Provide us with Your Name [max 29 characters]: ",false,rlutil::COLORS::WHITE,Utilities::defaultDelay);
        char name[30];  gets(name); // take Players name input
        player->setPlayerName(name);    // set players name

        // show details of player to screen
        std::cout<<"\n\n\t\t PLAYER DETAILS \n";
        std::cout<<"\n\t\t Name : "<<player->getPlayerName();   // show his name
        std::cout<<"\n\t\t Score : "<<player->getPlayerScore(); // show his score
        // prompt for uploading data to file
        Utilities::print("\n\n\t\t Uploading Player Details",false);
        Utilities::print("...",true,Utilities::defaultTextColor,Utilities::defaultDelay*10);
        uploadWinnerData(); // upload the Plyers Data to File of High Scores
        Utilities::print("\n\t\t Done.",true,rlutil::COLORS::LIGHTGREEN,0);
    }
    delete player; player=nullptr;  // relase heap memory allocated for Player, and let player pointer point to nullptr
}
void Game::showGamePlayPanel()  // shows Game Panel
{
    rlutil::cls();  // clear the screen
    Utilities::print("\t\t\t    -----+ GAME PLAY +-----",true,rlutil::COLORS::LIGHTRED,0);  // show GamePlay title
    rlutil::setColor(rlutil::COLORS::GREY);
    std::cout<<"\n\t\t\t  +-----+-----+-----+-----+";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  +-----+-----+-----+-----+";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  +-----+-----+-----+-----+";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  +-----+-----+-----+-----+";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  |     |     |     |     |";
    std::cout<<"\n\t\t\t  +-----+-----+-----+-----+";

    rlutil::setColor(Utilities::defaultTextColor);  // restore default color
    const int xInit=30,yInit=5,gapHoriz=6,gapVert=4;    // positions for displaying panel values
    // display the panel values to screen
    for(int i=0;i<4;i++)
    {
        int y=yInit+i*gapVert;  // select the row
        for(int j=0;j<4;j++)
        {
            int x=xInit+j*gapHoriz; // select the column
            rlutil::locate(x,y);    // move cursor to given coordinate on Console
            if(panel[i][j]==-1) // if the tile is empty (indicated using -1), print SPACE
            {
                std::cout<<" ";
            }
            else
            {
                std::cout<<panel[i][j]; // print panel values
            }
        }
    }
    // print the instructions for CONTROLS
    rlutil::locate(65,5);  std::cout<<"- CONTROLS -";
    rlutil::setColor(rlutil::COLORS::YELLOW);
    rlutil::locate(65,8);  std::cout<<"UP    :  W";     rlutil::locate(65,10);  std::cout<<"DOWN  :  S";
    rlutil::locate(65,12);  std::cout<<"LEFT  :  A";   rlutil::locate(65,14);  std::cout<<"RIGHT :  D";
    rlutil::setColor(rlutil::COLORS::LIGHTRED);
    rlutil::locate(65,17);  std::cout<<"EXIT  :  X";
    rlutil::setColor(Utilities::defaultTextColor);  // reset default color
    // display Score of Player
    Utilities::print("\n\n\n\n\n\n\n\n \t\t\t\t  SCORE : "+std::to_string(player->getPlayerScore()),true,rlutil::COLORS::LIGHTGREEN,0);
}

char Game::takeGameInput()  // takes single character
{
    return (char)_getch();
}
void Game::handleGameInput(const char& actionKey)  // handles the GamePlay input for players actions
{
    switch(actionKey)   // switch for the input actions
    {
        case 'X':
            gameOver=true; return;
            break;
        case 'W':   // W for UP Action, calls the corresponding function
            actionUp();
            break;
        case 'S':   // S for DOWN Action, calls the corresponding function
            actionDown();
            break;
        case 'A':
            actionLeft();   // A for LEFT Action, calls the corresponding function
            break;
        case 'D':
            actionRight();  // D for RIGHT Action, calls the corresponding function
            break;
    }
    gameOver=checkGameOver();   // check for game over condition, indicate same in gameOver flag variable
    if(!gameOver && !checkWin())    // if game is ON
    {
        fillRandomTile();   // fill a random tile in panel
    }

}
void Game::actionUp()   // handles up action
{
    unsigned long int scoreAdd=0;   // score to be added to final score
    for(int j=0;j<4;j++)    // traverse the panel column wise
    {
        for(int i=0;i<4;i++)       // select the column
        {
            if(panel[i][j]!=-1) // if the tile is not empty
            {
                int k=0;
                for(k=0;k<=i;k++)  if(panel[k][j]==-1) break;   // find the empty tile to be filled after action

                if(k<=i)    // if empty tile found
                {
                    panel[k][j]=panel[i][j];  panel[i][j]=-1;   // move the tile
                    // check for the tile merging condition
                    if(k-1>=0)  // to avoid accesing invalid index
                    {
                        if(panel[k-1][j]==panel[k][j])  // if values at adjacent tiles are same, merge them
                        {
                            panel[k-1][j]+=panel[k][j];
                            scoreAdd=panel[k-1][j]; // increse score
                            panel[k][j]=-1;
                        }
                    }
                }
                else if(i-1>=0) // if not empty tile found
                {
                    if(panel[i][j]==panel[i-1][j])  // check for the adjacent tile merging condition
                    {
                        panel[i-1][j]+=panel[i][j];
                        scoreAdd=panel[i-1][j]; // increase score
                        panel[i][j]=-1;
                    }
                }
            }
        }
    }
    player->addToPlayerScore(scoreAdd); // add the score to total score
}
void Game::actionDown()
{
    // logic almost same as of UP action
    unsigned long int scoreAdd=0;
    for(int j=0;j<4;j++)
    {
        for(int i=3;i>=0;i--)
        {
            if(panel[i][j]!=-1)
            {
                int k=0;
                for(k=3;k>=i;k--)  if(panel[k][j]==-1) break;

                if(k>=i)
                {
                    panel[k][j]=panel[i][j];  panel[i][j]=-1;
                    if(k+1<=3)
                    {
                        if(panel[k+1][j]==panel[k][j])
                        {
                            panel[k+1][j]+=panel[k][j];
                            scoreAdd=panel[k+1][j];
                            panel[k][j]=-1;
                        }
                    }
                }
                else if(i+1<=3)
                {
                    if(panel[i][j]==panel[i+1][j])
                    {
                        panel[i+1][j]+=panel[i][j];
                        scoreAdd=panel[i+1][j];
                        panel[i][j]=-1;
                    }
                }
            }
        }
    }
    player->addToPlayerScore(scoreAdd);
}
void Game::actionLeft()
{
    // logic almost same as of UP action
    unsigned long int scoreAdd=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(panel[i][j]!=-1)
            {
                int k=0;
                for(k=0;k<=j;k++)  if(panel[i][k]==-1) break;

                if(k<=j)
                {
                    panel[i][k]=panel[i][j];  panel[i][j]=-1;
                    if(k-1>=0)
                    {
                        if(panel[i][k-1]==panel[i][k])
                        {
                            panel[i][k-1]+=panel[i][k];
                            scoreAdd=panel[i][k-1];
                            panel[i][k]=-1;
                        }
                    }
                }
                else if(j-1>=0)
                {
                    if(panel[i][j]==panel[i][j-1])
                    {
                        panel[i][j-1]+=panel[i][j];
                        scoreAdd=panel[i][j-1];
                        panel[i][j]=-1;
                    }
                }
            }
        }
    }
    player->addToPlayerScore(scoreAdd);
}
void Game::actionRight()
{
    // logic almost same as of UP action
    unsigned long int scoreAdd=0;
    for(int i=0;i<4;i++)
    {
        for(int j=3;j>=0;j--)
        {
            if(panel[i][j]!=-1)
            {
                int k=0;
                for(k=3;k>=j;k--)  if(panel[i][k]==-1) break;

                if(k>=j)
                {
                    panel[i][k]=panel[i][j];  panel[i][j]=-1;
                    if(k+1<=3)
                    {
                        if(panel[i][k+1]==panel[i][k])
                        {
                            panel[i][k+1]+=panel[i][k];
                            scoreAdd=panel[i][k+1];
                            panel[i][k]=-1;
                        }
                    }
                }
                else if(j+1<=3)
                {
                    if(panel[i][j]==panel[i][j+1])
                    {
                        panel[i][j+1]+=panel[i][j];
                        scoreAdd=panel[i][j+1];
                        panel[i][j]=-1;
                    }
                }
            }
        }
    }
    player->addToPlayerScore(scoreAdd);
}

void Game::fillRandomTile() // fills the random tile in panel
{
    int tileNum=Utilities::getRandomNumber(1,getEmptyTiles());  // get random tile among empty tiles to fill
    int possibleValues[]={2,4}; // possible values for tile
    // go through the panel matrix
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(panel[i][j]==-1) // if tile is empty, tileNum reduces
            {
                tileNum--;
                if(tileNum==0)  // when tileNum reaches 0, fill that tile
                {
                    try
                    {
                        int index=Utilities::getRandomNumber(0,1);  // random index
                        if(index<0 || index>1) throw "Invalid Index Accesed";
                        panel[i][j]=possibleValues[index];  // fill with either 2 or 4
                    }
                    catch(const char* error)
                    {
                        panel[i][j]=2;  // fill with 2
                        Debugger::handleException(error);
                    }
                }
            }
        }
    }
}

int Game::getEmptyTiles()   // return total number of empty tiles in panel
{
    int tilesCount=0;   // counter
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(panel[i][j]==-1)  tilesCount++;  // if tile is empty, count it
        }
    }
    return tilesCount;  // return the counter
}
void Game::resetGame()  // resets the game for Fresh New GamePlay
{
    // change all fields to default
    gameOver=false;
    if(player!=nullptr) delete player;  // if memory not released, relased it for Player Object
    try
    {
        player=new Player();    // allocate memory for new Player
    }
    catch(const std::bad_alloc& err)    // catch bad allocation error
    {
        Debugger::handleException(err.what(),true);
    }
    catch(...)  // catch for anymous error
    {
        Debugger::handleException("UNDEFINED ERROR",true);
    }

    // make all the tiles in panel empty
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            panel[i][j]=-1;

    fillRandomTile(); fillRandomTile(); // fill two random tile in the begining of GamePlay
}
bool Game::checkWin()   // returns if Player Wins the game
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(panel[i][j]>=2048) return true;  // if any of tile is >=2048, player wins the game, return TRUE
    return false;   // if not then return FALSE
}
bool Game::checkGameOver()  // returns if Game is Over or not
{
    int leftMoves=getEmptyTiles();  // count the empty tiles
    return leftMoves<=0;    // if no more empty tiles, then indicate game over
}
void Game::uploadWinnerData()   // uploads Players data to file
{
    const char* fileName="hightscore_data.txt"; // file name used to store records
    bool isLast=true;   // flag to indicate if position of new record is last or not, special case
    Player currPlayer;  // Object of Player Class to store Current Reading Records
    std::ifstream fin;  std::ofstream fout;
    try
    {
        fin.open(fileName);  // open the records file for reading
        if(!fin) throw 3;   // ErrorCode 3 indicated No Such File Exist
        fout.open("temp.txt"); // create a temperory file to copy records sorted on basis of score
        if(!fout) throw -1; // ErrorCode -1 indicated unable to create new file
    }
    catch(int errCode)
    {
        if(errCode==-1)  Debugger::handleException("Unable to Create File temp.txt",true);
        else if(errCode==3)
        {
            std::ofstream f(fileName); // create file
            f.close();  // de-link the file from object f
            fin.open(fileName); // attach the newly created file to fin object
        }
    }

    while(!fin.eof())   // continue reading records till file ends
    {
        fin.read((char*)&currPlayer,sizeof(Player));    // read record from file
        if(currPlayer.getPlayerScore()<=player->getPlayerScore())   // if new score is more than the score of record
        {
            fout.write((char*)player,sizeof(Player));   // copy new record
            fout.write((char*)&currPlayer,sizeof(Player));  // after than copy the record read from file
            isLast=false; //indicate record inserted, and not last record
            break;  // break the loop
        }
        else    // otherwise continue copying records from file to temp.txt
        {
            fout.write((char*)&currPlayer,sizeof(Player));
        }
    }
    if(isLast)  // special case, if record is last, write it to file at last
    {
        fout.write((char*)player,sizeof(Player));
    }
    else if(!fin.eof()) // if record has been inserted in middle
    {
        while(!fin.eof())   // continue copying the remaining records from file
        {
            fin.read((char*)&currPlayer,sizeof(Player));    // read record
            fout.write((char*)&currPlayer,sizeof(Player));  // write record
        }
    }
    fin.close(); fout.close();  // close both the files
    try     // handle all exception regarding deleting and renaming files
    {
        std::remove(fileName);  // delete the old records file
        std::rename("temp.txt",fileName);   // rename temp.txt, and make this new high score saving file
    }
    catch(...)
    {
        Debugger::handleException("Error in Deleting/Renaming Files");
    }
}
void Game::showHighScoreTable() // shows the records from file in table
{
    rlutil::cls();  // clear the screen
    // format the output
    Utilities::print("\n\n\t\t   ---+ HIGH SCORES +--- ",true,rlutil::COLORS::LIGHTBLUE,0);
    std::cout<<"\n\n\t\t";
    std::cout.setf(std::ios::left);
    std::cout<<std::setw(7)<<"SR";  std::cout<<std::setw(30)<<"NAME";  std::cout<<std::setw(20)<<"SCORE ";
    std::cout<<"\n\t      ---------------------------------------------------\n";

    // read records from high score file, and print them on screen
    const char* fileName="hightscore_data.txt";
    std::ifstream fin;
    try
    {
        fin.open(fileName);    // open file in reading mode
        if(!fin) throw "Unable to Open file hightscore_data.txt, File do not exists";
    }
    catch(const char* errMessage)
    {
        Debugger::handleException(errMessage);
    }
    int serialNo=1; // seriea number of record
    while(!fin.eof())   // read till end of file
    {
        Player currPlayerData;  // to store Player Record
        fin.read((char*)&currPlayerData,sizeof(Player));    // read record
        std::cout<<"\n\t\t";
        if(currPlayerData.getPlayerScore()>0)   // if Player Score is valid
        {
            // print all the datails of Player with serial number indicating Rank
            std::cout<<std::setw(7)<<serialNo++;
            std::cout<<std::setw(30)<<currPlayerData.getPlayerName();
            std::cout<<std::setw(20)<<currPlayerData.getPlayerScore();
        }
    }

    fin.close();    // close the file
}
