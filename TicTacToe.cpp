#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

struct Player
{
    string name = "\0";
    int score = 0;
};

char evaluate(char board[][3], int choice);
void mainMenu();
void Play();
void PvP();
void PvCPU();
void newGame(Player &, Player &);
void outputBoard(char board[][3], Player P1, Player P2);
void CPUgame(Player &P);
int CPUcheck_Easy(char board[][3]);
int CPUcheck_Medium(char board[][3]);
int CPUcheck_Hard(char board[][3], int choice);

void CPUgame(Player &P)
{
    Player CPU;
    CPU.name = "CPU";

    cout << "\n\n\n\n";
    cout << "Plz select the difficulty Level :)\n";
    cout << "1.Easy\n";
    cout << "2.Medium\n";
    cout << "3.Hard\n";
    int difficulty;
    do
    {
        cout << "Enter your choice : ";
        cin >> difficulty;
        if (difficulty <= 0 || difficulty > 3)
        {
            cout << "Select a Correct Option\n";
        }
    } while (difficulty <= 0 || difficulty > 3);

    bool playAgain = true;
    while (playAgain)
    {
        char board[3][3] = {};

        bool cont = true;
        for (int i = 0; i < 5 && cont; i++)
        {
            outputBoard(board, P, CPU);
            cout << "\n\n\n";
            int choice;
            do
            {
                cout << "Enter the box Number you want (ij): ";
                cin >> choice;
                if (choice % 10 < 0 || choice % 10 >= 3 || choice / 10 < 0 || choice % 10 >= 3 || board[choice / 10][choice % 10] != '\0')
                {
                    cout << "Enter the correct input\n";
                }
            } while (choice % 10 < 0 || choice % 10 >= 3 || choice / 10 < 0 || choice % 10 >= 3 || board[choice / 10][choice % 10] != '\0');

            board[choice / 10][choice % 10] = 'A';

            if (evaluate(board, choice) != 'A')
            {
                int CPUchoice = ((difficulty == 1) ? CPUcheck_Easy(board) : ((difficulty == 2)? CPUcheck_Medium(board) : CPUcheck_Hard(board, choice)));
                board[CPUchoice / 10][CPUchoice % 10] = 'B';
                if (evaluate(board, CPUchoice) == 'B')
                {
                    cont = false;
                    CPU.score++;
                    outputBoard(board, P, CPU);
                    cout << "CPU won the Game";
                    cout << endl;
                }
            }
            else
            {
                cont = false;
                P.score++;
                outputBoard(board, P, CPU);
                cout << P.name << " won the game";
                cout << endl;
            }
            if (i == 4){
                outputBoard(board, P, CPU);
                cout << "Draw";
            }
        }
        cout << "Play Again ? (y/n) : ";
        char input;
        cin >> input;
        if (input != 'y')
        {
            playAgain = false;
        }
    }
}

int CPUcheck_Hard(char board[][3], int choice){
    int Possible[3] = {};
    int counter = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (board[i][i] == board[j][j] && board[i][i] != '\0' && board[3 - i - j][3 - i - j] == '\0')
            {
                if (board[i][i] == 'B')
                {
                    return ((3 - i - j) * 10 + (3 - i - j));
                }
                Possible[counter++] = ((3 - i - j) * 10 + (3 - i - j));
            }
            if (board[i][2 - i] == board[j][2 - j] && board[i][2 - i] != '\0' && board[3 - i - j][2 - 3 + i + j] == '\0')
            {
                if (board[i][2 - i] == 'B')
                {
                    return ((3 - i - j) * 10 + (2 - 3 + i + j));
                }
                Possible[counter++] = ((3 - i - j) * 10 + (2 - 3 + i + j));
            }
        }
    }
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {

                if (board[i][k] == board[j][k] && board[i][k] != '\0' && board[3 - i - j][k] == '\0') // for checking possbile along length
                {
                    if (board[i][k] == 'B')
                    {
                        return ((3 - i - j) * 10 + k);
                    }
                    Possible[counter] = ((3 - i - j) * 10 + k);
                }

                if (board[k][i] == board[k][j] && board[k][i] != '\0' && board[k][3 - i - j] == '\0') // for checking possible along height
                {
                    if (board[k][i] == 'B')
                    {
                        return (k * 10 + 3 - i - j);
                    }
                    Possible[counter] = (k * 10 + 3 - i - j);
                }
            }
        }
    }

    static int CPUfirst;
    static int PlayerFirst = -1;
    int empty;
    if (PlayerFirst == -1){
        PlayerFirst = choice;
    }

    if (Possible[0] == '\0'){
        int turns = 0;
        for (int i = 0; i < 9; i++){
            if (board[i /3][i % 3] != '\0'){
                turns++;
            }
            empty = (i / 3) * 10 + i % 3;
        }

        if (turns == 1){
            if (choice == 11){
                CPUfirst = 00;
                return 00;
            }
            if ((choice / 10 !=  1) && (choice % 10 != 1)) {
                CPUfirst = 11;
                return 11;
                //return ((2 - (choice / 10)) * 10 + (2 - choice % 10));
            }
            CPUfirst = 11;
            return 11;
        }
        if (turns == 3){
            if (PlayerFirst == 11){
                return 02;
            }
            if (CPUfirst / 10 != 1 && CPUfirst % 10 != 1) {
                if (board[1][1] != '\0'){
                    return (CPUfirst - (CPUfirst % 10) + (3 - CPUfirst % 10));
                }
                return 11;
            }
            if (board[(PlayerFirst + 9) / 10][(PlayerFirst + 9) % 10] == 'A' || board[(PlayerFirst - 9) / 10][(PlayerFirst - 9) % 10] == 'A'){
                int ret;
                ((board[2][1] == 'A')? (ret = 0): (ret = 22));
                return ret;
            }
            if (((((PlayerFirst + 11) / 10) < 3) && (((PlayerFirst + 11) % 10) < 3) && board[(PlayerFirst + 11) / 10][(PlayerFirst + 11) % 10] == 'A' )||( (((PlayerFirst + 11) / 10) >= 0) && (((PlayerFirst + 11) % 10) >= 0) && board[(PlayerFirst - 11) / 10][(PlayerFirst - 11) % 10] == 'A')){
                int ret;
                ((board[2][1] == 'A')? (ret = 2): (ret = 20));
                return ret;
            }
        }
        return empty;
    }
    return Possible[0];
    
}

int CPUcheck_Medium(char board[][3])
{
    int Possible[3] = {};
    int counter = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (board[i][i] == board[j][j] && board[i][i] != '\0' && board[3 - i - j][3 - i - j] == '\0')
            {
                if (board[i][i] == 'B')
                {
                    return ((3 - i - j) * 10 + (3 - i - j));
                }
                Possible[counter++] = ((3 - i - j) * 10 + (3 - i - j));
            }
            if (board[i][2 - i] == board[j][2 - j] && board[i][2 - i] != '\0' && board[3 - i - j][2 - 3 + i + j] == '\0')
            {
                if (board[i][2 - i] == 'B')
                {
                    return ((3 - i - j) * 10 + (2 - 3 + i + j));
                }
                Possible[counter++] = ((3 - i - j) * 10 + (2 - 3 + i + j));
            }
        }
    }
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {

                if (board[i][k] == board[j][k] && board[i][k] != '\0' && board[3 - i - j][k] == '\0') // for checking possbile along length
                {
                    if (board[i][k] == 'B')
                    {
                        return ((3 - i - j) * 10 + k);
                    }
                    Possible[counter] = ((3 - i - j) * 10 + k);
                }

                if (board[k][i] == board[k][j] && board[k][i] != '\0' && board[k][3 - i - j] == '\0') // for checking possible along height
                {
                    if (board[k][i] == 'B')
                    {
                        return (k * 10 + 3 - i - j);
                    }
                    Possible[counter] = (k * 10 + 3 - i - j);
                }
            }
        }
    }
    if (Possible[0] != '\0'){
        return Possible[0];
    }
    if (board[1][1] == '\0')
    {
        return 11;
    }
    if (board[0][0] == '\0')
    {
        return 0;
    }
    if (board[2][2] == '\0')
    {
        return 22;
    }
    if (board[2][0] == '\0')
    {
        return 20;
    }
    if (board[0][2] == '\0')
    {
        return 2;
    }
}

int CPUcheck_Easy(char board[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (board[i][i] == board[j][j] && board[i][i] != '\0' && board[3 - i - j][3 - i - j] == '\0')
            {
                return ((3 - i - j) * 10 + (3 - i - j));
            }
            if (board[i][2 - i] == board[j][2 - j] && board[i][2 - i] != '\0' && board[3 - i - j][2 - 3 + i + j] == '\0')
            {
                return ((3 - i - j) * 10 + (2 - 3 + i + j));
            }
        }
    }
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                if (board[k][i] == board[k][j] && board[k][i] != '\0' && board[k][3 - i - j] == '\0') // for checking possible along height
                {
                    return (k * 10 + 3 - i - j);
                }

                if (board[i][k] == board[j][k] && board[i][k] != '\0' && board[3 - i - j][k] == '\0') // for checking possbile along length
                {
                    return ((3 - i - j) * 10 + k);
                }
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '\0')
            {
                return ((i * 10) + j);
            }
        }
    }
    return 0;
}

void outputBoard(char board[][3], Player P1, Player P2)
{
    //system("clear");
    cout << P1.name << "'s Score : " << P1.score << "\t\t\t" << P2.name << "'s Score : " << P2.score << endl;
    cout << "\t    0\t    1\t    2\n";
    int j, k;
    for (k = 0; k < 3; k++)
    {
        cout << k << "\t|";
        for (j = 0; j < 3; j++)
        {
            if (board[k][j] == 'A')
            {
                cout << "X\t|";
            }
            else if (board[k][j] == 'B')
            {
                cout << "O\t|";
            }
            else
                cout << "\t|";
        }
        cout << endl;
        cout << "\t--------------------------";
        cout << endl;
    }
}

void mainMenu()
{
    //system("clear");
    cout << "Welcome to TicTacToe\n\n\n\n\n";
    cout << "1.Play\n";
    cout << "2.Exit\n\n\n\n\n";

    int choice;
    cout << "Enter your Choice : ";
    cin >> choice;

    if (choice == 1)
    {
        Play();
    }
    else if (choice != 2)
    {
        cout << "Enter correct Input \n";
    }
}

void Play()
{
    //system("clear");
    cout << "Welcome to Play Game\n\n\n\n\n\n";
    cout << "1.PvP\n";
    cout << "2.PvCPU\n\n\n\n";

    int choice;
    cout << "Enter Your Choice : ";
    cin >> choice;

    do
    {
        if (choice == 1)
        {
            PvP();
        }
        else if (choice == 2)
        {
            PvCPU();
        }
        else
        {
            cout << "Enter Correct Input\n";
        }
    } while (choice != 1 && choice != 2);
}

void PvP()
{
    //system("clear");
    cout << "Welcome to Player vs Player mode\n";
    cout << "Enter the name of the Player 1 : ";
    Player P1, P2;
    cin.ignore();
    getline(cin, P1.name);
    cout << "Enter the name of the Player 2 : ";
    getline(cin, P2.name);
    newGame(P1, P2);
}

void PvCPU()
{
    //system("clear");
    cout << "Welcome to Player vs CPU mode \n";
    Player P;
    cout << "Enter the name of the Player : ";
    cin.ignore();
    getline(cin, P.name);

    CPUgame(P);
}

void newGame(Player &P1, Player &P2)
{
    bool playAgain = true;
    while (playAgain)
    {

        char board[3][3] = {};
        bool cont = true;
        for (int i = 0; cont && i < 9; i++)
        {
            outputBoard(board, P1, P2);
            if (i % 2 == 0)
            {
                cout << P1.name << "'s Turn \n";
            }
            else
            {
                cout << P2.name << "'s Turn \n";
            }
            int choice;
            do
            {
                cout << "Enter the box Number you want (ij): ";
                cin >> choice;
                if (choice % 10 < 0 || choice % 10 >= 3 || choice / 10 < 0 || choice % 10 >= 3 || board[choice / 10][choice % 10] != '\0')
                {
                    cout << "Enter the correct input\n";
                }
            } while (choice % 10 < 0 || choice % 10 >= 3 || choice / 10 < 0 || choice % 10 >= 3 || board[choice / 10][choice % 10] != '\0');
            if (i % 2 == 0)
            {
                board[choice / 10][choice % 10] = 'A';
            }
            else
            {
                board[choice / 10][choice % 10] = 'B';
            }

            if (evaluate(board, choice) == 'A')
            {
                P1.score++;
                outputBoard(board, P1, P2);
                cout << P1.name << "wins" << endl;
                cont = false;
            }
            else if (evaluate(board, choice) == 'B')
            {
                P2.score++;
                outputBoard(board, P1, P2);
                cout << P2.name << "wins" << endl;
                cont = false;
            }
            else if (i == 8)
            {
                outputBoard(board, P1, P2);
                cout << "Draw\n";
            }
        }
        cout << "Rematch ? (y/n) : ";
        char choice;
        cin >> choice;
        if (choice != 'y')
        {
            playAgain = false;
        }
    }
}

char evaluate(char board[][3], int choice)
{
    bool row_ = true, col_ = true;
    bool diag = true, antiDiag = true;
    for (int i = 1; i < 3; i++)
    {

        if (board[choice / 10][i] != board[choice / 10][0])
        {
            row_ = false;
        }
        if (board[i][choice % 10] != board[0][choice % 10])
        {
            col_ = false;
        }
        if (board[0][0] != board[i][i])
        {
            diag = false;
        }
        if (board[i][2 - i] != board[0][2])
        {
            antiDiag = false;
        }
    }
    if (row_)
    {
        return board[choice / 10][0];
    }
    if (col_)
    {
        return board[0][choice % 10];
    }
    if (diag || antiDiag)
    {
        return board[1][1];
    }
    return 'C';
}

int main()
{
    mainMenu();
    cout << endl
         << "Thank you For Playing" << endl;
    return 0;
}