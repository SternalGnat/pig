// pig.cpp
// Michael Murr-Conley, CISP 360
// 08/24/21

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void programGreeting();
void getPlayerNames(string &playerOneFirst, string &playerOneLast, string &playerOneFull);
int playerMenu();
// Specification A1 - D6() function
int d6();
int userTurn(int &userGrandScore, string playerOneFull, bool &gameWon);
int compTurn(int &compGrandScore);
int highScoreOnHeap(int compGrandScore, int humanGrandScore);
int randomNumber();

int main()
{
    srand(time(NULL));
    string playerOneFirst;
    string playerOneLast;
    string playerOneFullName;
    string winner = "N/A";
    bool gameWon = false;
    int userGrandScore = 0;
    int compGrandScore = 0;
    int hiScore = 0;

    //program greeting function
    programGreeting();
    //collects player name from the user
    getPlayerNames(playerOneFirst, playerOneLast, playerOneFullName);
    
    //game logic for playing pig
    while(gameWon == false)
    {
        userTurn(userGrandScore, playerOneFullName, gameWon);
        if(userGrandScore >=100)
        {
            gameWon = true;
            winner = playerOneFullName;
        }
        else       {
            compTurn(compGrandScore);
            if(compGrandScore >=100)
            {
                gameWon = true;
                winner = "computer";
            }
        }
    }
    //once bool gameWon has been made true, this switches the game over screen
    if(gameWon == true)
    {
        cout << "Game Over" << endl;
        cout << "The winner is " << winner << endl;
        // Specification B4 – Display High Score
        hiScore = highScoreOnHeap(compGrandScore, userGrandScore);
        cout << "With the high score of: " << hiScore << endl;
        //cout << playerOneFullName << "'s score: " <<  userGrandScore << endl;
        //cout << "Computer's score: " << compGrandScore << endl;
        
    }
}

void programGreeting()
{
    cout << "PIG GAME\n";
    cout << "=============================================================\n";
    cout << "This program allows you to play a dice game against a computer\n";
    cout << "When its your turn - you roll a die!\n";
    cout << "If the number rolled is 1, you lose your turn!\n";
    cout << "If you roll 2-6 that number is added to your total score\n";
    cout << "Code written by: Michael Murr-Conley\n";
    //Specification B2 - Display Due Date
    cout << "Date assignment due: August 29th, 2021\n";
    cout << "==============================================================\n";
    cout << "Press any button start the game:";
    cin.get();
    cin.clear();
    cin.ignore(100, '\n');
    cout << endl;
    cout << endl;
}
// Specification C2 - Student Name
void getPlayerNames(string &playerOneFirst,string &playerOneLast,string &playerOneFull)
{
    cout << "Enter player ones first name:" << endl;
    cin >> playerOneFirst;
    cout << "Enter player ones last name:" << endl;
    cin >> playerOneLast;
    playerOneFull = playerOneFirst + " " + playerOneLast;
}
// Specification C3 - Numeric Menu
// Specification C4 - Bulletproof Menu
int playerMenu()
{
    int menuChoice;
    int error;
        do
        {
            cout << "Please use the number keys to select one of the following options\n";
            cout << "1. Roll\n";
            cout << "2. Hold\n";
            cout << "3. Quit game\n";
            error = 0;
            cin >> menuChoice;
            if (cin.fail() || (menuChoice != 1 && menuChoice !=2 && menuChoice !=3))
            {
                cout << "Error, invalid input, please enter only 1, 2, or 3 ";
                cout << endl;
                error = 1;
                cin.clear();
                cin.ignore(80, '\n');
            }
        }while(error == 1);
    return menuChoice;
}
// Specification C1 - Fixed Seed
// Specification A1 - D6() function
int d6()
{
    int roll;
    roll = (int)(rand()%6)+1;
    return roll;
}
//function for user turn - function loops until 1 is rolled or player chooses to hold/quit
int userTurn(int &userGrandScore, string playerOneFull, bool &gameWon)
{
    cout << playerOneFull << "'s current score is:" << userGrandScore << endl;
    int menuChoice;
    int turnScore = 0;
    int roll = 0;
    
    menuChoice = playerMenu();
    while(menuChoice == 1 && gameWon == false)
    {
        roll = d6();
        if(roll == 1)
        {
            cout << "You rolled a 1, " <<endl;
            cout << "rolling 1 resets your turn score to 0" << endl;
            cout << endl;
            turnScore = 0;
            break;
            
        }
        else
        {
            turnScore += roll;
            // Specification B1 - Display Turn Stats
            cout << playerOneFull << " rolled an " << roll << endl;
            cout << "Score for this turn is now: " << turnScore << endl;
            menuChoice = playerMenu();
        }
    }
    if(menuChoice == 2 && gameWon == false)
    {
        userGrandScore = userGrandScore + turnScore;
        cout << "You hold, your grand score is now: " << userGrandScore << endl;
        cout << endl;
        return userGrandScore;
    }
    else if(menuChoice == 3 && gameWon == false)
    {
        gameWon = true;
        return gameWon;
        
    }
    
    return userGrandScore;
}
//function for computer turn, 50% chance of computer holding or playing
int compTurn(int &compGrandScore)
{
    int roll = 0;
    int compTurnScore = 0;
    bool hold = false;
    cout << "Computers current score is:" << compGrandScore << endl;
    roll = d6();
    
    while(hold == false)
    {
    if(roll == 1 || roll == 2 || roll == 3)
    {
        cout << "The computer decided to hold" << endl;
        compGrandScore = compTurnScore + compGrandScore;
        cout << "The computer's grand score is now " << compGrandScore << endl;
        cout << endl;
        hold = true;
    }
    else if(roll == 4 || roll == 5 || roll == 6)
    {
        roll = d6();
        if(roll == 1)
        {
            cout << "The computer rolled a 1, resetting its score" << endl;
            cout << endl;
            compTurnScore = 0;
            break;
        }
        else
        {
            compTurnScore = roll + compTurnScore;
            cout << "The computer rolled a " << roll << endl;
            cout << "The computer's turn total is now " << compTurnScore << endl;
            cout << endl;
        }
        
    }
    }
    return compGrandScore;
}
// Specification B3 - Hi Score on Heap
//function to store game's highscore on the heap, function deletes variable highscore when finished
int highScoreOnHeap(int compGrandScore, int humanGrandScore)

{
    int *highScore;
        highScore = new int;
        *highScore = 0;
        ++* highScore;
    if(compGrandScore > humanGrandScore)
    {
        *highScore = compGrandScore;
    }
    else
    {
        *highScore = humanGrandScore;
    }
    return *highScore;
    
}
// Specification A2 - RandomNumber() function
//function made to meet all A specifications, doesnt contribute to game
int randomNumber()
{
    int lo = 1;
    int hi = 100;
    srand(time(NULL));
    int num = (rand() % (hi - lo + 1)) + lo;
    // Specification A3 - Protect RandomNumber() input
    if (lo != (int)lo || hi != int(hi))
    {
    return -1;
    }
    // Specification A4 - Protect RandomNumber() output
    if(num > 100)
    {
    return -2;
    }
    return num;
}
