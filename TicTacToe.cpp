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

void CPUgame(Player &P){
    char board[3][3] = {};

}
char evaluate(char board[][3], int choice);
void mainMenu();
void Play();
void PvP();
void PvCPU();
void newGame(Player &, Player &);
void outputBoard(char board[][3], Player P1, Player P2);

void outputBoard(char board[][3], Player P1, Player P2)
{
    system("clear");
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
    system("clear");
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
    system("clear");
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
    system("clear");
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
    system("clear");
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