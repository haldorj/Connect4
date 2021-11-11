#include "game.h"

int playerturn = 1;
int position = 0;
int const columns = 7;
int const rows = 6;
char playerID = 'X';
char choice;
std::string playerOneName;
std::string playerTwoName;
const std::string ai_name = "AI";
int playerOneScore = 0;
int playerTwoScore = 0;
int ai_choice = 0;
std::string buff;
std::fstream myfile("data.txt", std::ios::in | std::ios::app | std::ios::out);//read + write
//scores are written onto txt file in the project folder, and deleted when a new game is started.

//How the AI works:
//When possible, the games AI blocks the player if the player can connect 4.
//Otherwise the AI Places its pieces randomly.

char board[rows][columns] = {
{ '*', '*', '*', '*', '*', '*', '*' },
{ '*', '*', '*', '*', '*', '*', '*' },
{ '*', '*', '*', '*', '*', '*', '*' },
{ '*', '*', '*', '*', '*', '*', '*' },
{ '*', '*', '*', '*', '*', '*', '*' },
{ '*', '*', '*', '*', '*', '*', '*' }
};

void start_screen()
{
    myfile.open("data.txt", std::ofstream::out | std::ofstream::trunc); //deletes previous contents.
    myfile.close();
	std::cout << "Welcome to:" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "***********" << std::endl;
	std::cout << "CONNECT 4" << std::endl;
	std::cout << "***********" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "Player 1) X" << std::endl;
	std::cout << "Player 2) O" << std::endl;
	std::cout << " " << std::endl;
    display_board();
	std::cout << " " << std::endl;
	std::cout << "Press [ENTER]	to continue." << std::endl;

    std::cin.clear();
    std::cin.ignore();
	
}
void enter_names() {
    std::cout << "Player 1 please enter your name." << std::endl;
    std::cin >> playerOneName;
    std::cout << "Player 2 please enter your name." << std::endl;
    std::cout << "(You can play against the AI if you type 'AI'.)." << std::endl;
    std::cin >> playerTwoName;

    if (playerTwoName == ai_name) {
        std::cout << playerOneName << " has chosen to play against the AI." << std::endl;
        Sleep(2000);
    }
    std::cout << std::endl;
    std::cout << "Starting the game";
    for (int i = 0; i < 3; i++) {
        std::cout << ".";
        Sleep(1000);
    } std::cout << std::endl;
    system("CLS");
    std::cout << playerOneName << " VS. " << playerTwoName << std::endl;
    std::cout << std::endl;
    display_board();

}
bool is_winner()
{
    bool winner = false;
    //vertical win
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] != '*'
                && board[i][j] == board[i - 1][j]
                && board[i][j] == board[i - 2][j]
                && board[i][j] == board[i - 3][j]) {
                winner = true;
            }
        }
    }
    //horizontal win
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != '*'
                && board[i][j] == board[i][j + 1]
                && board[i][j] == board[i][j + 2]
                && board[i][j] == board[i][j + 3]) {
                winner = true;
            }
        }
    }
    //ascending diagonal win (NE)
    for (int i = 4; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != '*'
                && board[i][j] == board[i - 1][j + 1]
                && board[i][j] == board[i - 2][j + 2]
                && board[i][j] == board[i - 3][j + 3]) {
                winner = true;
            }
        }
    }
    //descending diagonal win (NW)
    for (int i = 4; i < 6; i++) {
        for (int j = 3; j < 7; j++) {
            if (board[i][j] != '*'
                && board[i][j] == board[i - 1][j - 1]
                && board[i][j] == board[i - 2][j - 2]
                && board[i][j] == board[i - 3][j - 3]) {
                winner = true;
            }
        }
    }
    return winner;
}
bool filled_board()
{
    bool filled = true;
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (board[i][j] == '*') {
                    filled = false;
                }
            }
        } return filled;
    }
}
void display_board()
{
    std::cout << "1 2 3 4 5 6 7" << std::endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << board[i][j] << " ";
		}
        std::cout << std::endl;
	}
}
void setpos()
{
    if (playerTwoName == ai_name && playerturn != 1) {
        update_board_ai();
    }
    if (playerturn == 1) {
        std::cout << playerOneName << " enter : 1-7" << std::endl;
    }
    if (playerTwoName != ai_name && playerturn != 1) {
        std::cout << playerTwoName << " enter : 1-7" << std::endl;
    }

    while (!(std::cin >> position)) {
        std::cout << "Please enter a valid number between 1-7." << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }

    while (position < 1 || position > 7) {
        std::cout << "You cant put your piece there." << std::endl;
        std::cout << "Try again." << std::endl;
        std::cout << "Player " << playerturn << "s turn." << std::endl;
        std::cout << "Please enter a valid number between 1-7." << std::endl;
        std::cin >> position;
        std::cout << std::endl;
    }

    while (board[0][ position - 1] != '*') {
        std::cout << "You cant put your piece there." << std::endl;
        std::cout << "Try again." << std::endl;
        std::cout << "Player " << playerturn << "s turn." << std::endl;
        std::cout << "Please enter a valid number between 1-7." << std::endl;
        std::cin >> position;
        std::cout << std::endl;
    }
}
void update_board()
{
    int i = 5;
    int turn = 0;

    do
    {
        if (board[i][position-1] != 'X' && board[i][position - 1] != 'O')
        {
            board[i][position - 1] = playerID;
            turn = 1;
        }
        else
            --i;
    } while (turn != 1);
    system("CLS");
}
void update_board_ai() {
    int i = 5;
    int turn = 0;
    if (playerTwoName == ai_name && playerturn != 1) {
        do
        {
            if (board[0][ai_choice - 1] != '*') {
                ai_choice = (rand() % 7) + 1;
            }
            if (board[i][ai_choice - 1] != 'X' && board[i][ai_choice - 1] != 'O')
            {
                board[i][ai_choice - 1] = playerID;
                turn = 1;
            }
            else
                --i;
        } while (turn != 1);
    }
    std::cout << "AI is making a move.." << std::endl;
    Sleep(1500);
    system("CLS");
    change_player();
}
void change_player()
{
    if (playerturn == 1) {
        playerID = 'O';
        playerturn++;
    }
    else if (playerTwoName == ai_name){
        playerID = 'X';
        playerturn--;
        display_board();
        if (is_winner()) {
            ai_win();
        }
    }
    else if (playerTwoName != ai_name) {
        playerID = 'X';
        playerturn--;
    }
}
void take_turn()
{
    while (!is_winner() && !filled_board()) {
        game_ai();
        setpos();
        update_board();
        change_player();
        display_board();
    }
    game_end();
}
void game_end()
{
    if (is_winner() && playerturn != 1) {
        std::cout << playerOneName << " won! Congratulations!" << std::endl;
        playerOneScore++;
        save_to_file();
    }
    else if (is_winner() && playerturn == 1) {
        std::cout << playerTwoName << " won! Congratulations!" << std::endl;
        playerTwoScore++;
        save_to_file();
    }
    else if (filled_board()) {
        std::cout << "It is a tie!" << std::endl;
    }
}
void ai_win()
{
    std::cout << "The AI won." << std::endl;
    std::cout << "Better luck next time." << std::endl;
    playerTwoScore++;
    save_to_file();
}
void play_again()
{
    std::cout << "Do you want to play again?" << std::endl;
    std::cout << "Press Y for yes" << std::endl;
    std::cout << "Press N for no" << std::endl;
    std::cin >> choice;
    switch (choice) {
        {
    case 'Y': case 'y':
        system("CLS");
        reset_board();
        break;
    case 'N': case 'n':
        system("CLS");
        std::cout << "Quitting program..." << std::endl;
        std::cout << "Thanks for playing!" << std::endl;
        exit(0);
        break;
    default:
        std::cout << "Invalid input." << std::endl;
        play_again();
        }
    }
}
void reset_board()
{
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                board[i][j] = '*';
            }
        }
    }
    is_winner();
    display_board();
    take_turn();
}
void save_to_file()
{
    myfile.open("data.txt", std::ofstream::out | std::ofstream::trunc); //deletes previous contents.
    myfile.close();
    myfile.open("data.txt", std::ios::in | std::ios::app | std::ios::out); //opens file for read + write.
    myfile << playerOneName << " has won " << playerOneScore << " times." << std::endl;
    myfile << playerTwoName << " has won " << playerTwoScore << " times." << std::endl;
    myfile.clear();
    myfile.seekg(0);
    myfile.sync();
    while (getline(myfile, buff)) {
        std::cout << buff << std::endl;
    }
    myfile.clear();
    myfile.seekg(0);
    myfile.close();
    play_again();
}
void game_ai()
{
    if (playerTwoName == ai_name) {

        ai_choice = (rand() % 7) + 1;

        //blocking vertical win.
        for (int i = 3; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] == 'X'
                    && board[i][j] == board[i - 1][j]
                    && board[i][j] == board[i - 2][j]
                    && board[i - 3][j] == '*')
                {
                    ai_choice = j + 1;
                }
            }
        }
        //blocking horizontal win 1
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]
                    && board[i][j + 3] == '*' && board[i + 1][j + 3] != '*') {
                    ai_choice = j + 4;
                }
            }
        }
        //blocking horizontal win 2
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 3]
                    && board[i][j + 2] == '*' && board[i + 1][j + 2] != '*') {
                    ai_choice = j + 3;
                }
            }
        }
        //blocking horizontal win 3
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3]
                    && board[i][j + 1] == '*' && board[i + 1][j + 1] != '*') {
                    ai_choice = j + 2;
                }
            }
        }
        //blocking horizontal win 4
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == '*' && board[i][j + 1] == 'X' && board[i][j + 1] == board[i][j + 2] && board[i][j + 1] == board[i][j + 3]
                    && board[i + 1][j] != '*') {
                    ai_choice = j + 1;
                }
            }
        }
        //blocking ascending diagonal win 1
        for (int i = 4; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i-1][j + 1] && board[i][j] == board[i-2][j + 2]
                    && board[i - 3][j + 3] == '*' && board[i - 2][j + 3] != '*') {
                    ai_choice = j + 4;
                }
            }
        }
        //blocking ascending diagonal win 2
        for (int i = 4; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i + 3][j + 3]
                    && board[i - 2][j + 2] == '*' && board[i - 1][j + 2] != '*') {
                    ai_choice = j + 3;
                }
            }
        }
        //blocking ascending diagonal win 3
        for (int i = 4; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3]
                    && board[i - 1][j + 1] == '*' && board[i][j + 1] != '*') {
                    ai_choice = j + 2;
                }
            }
        }
        //blocking ascending diagonal win 4
        for (int i = 4; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == '*' && board[i - 1][j + 1] == 'X' && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 1][j + 1] == board[i - 3][j + 3]
                    && board[i + 1][j] != '*') {
                    ai_choice = j + 1;
                }
            }
        }
        //blocking descending diagonal win 1
        for (int i = 4; i < 6; i++) {
            for (int j = 3; j < 7; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2]
                    && board[i - 3][j - 3] == '*' && board[i - 2][j - 3] != '*') {
                    ai_choice = 1;
                }
            }
        }
        //blocking descending diagonal win 2
        for (int i = 4; i < 6; i++) {
            for (int j = 3; j < 7; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 3][j - 3]
                    && board[i - 2][j - 2] == '*' && board[i - 1][j - 2] != '*') {
                    ai_choice = 2;
                }
            }
        }
        //blocking descending diagonal win 3
        for (int i = 4; i < 6; i++) {
            for (int j = 3; j < 7; j++) {
                if (board[i][j] == 'X' && board[i][j] == board[i - 2][j - 2] && board[i][j] == board[i - 3][j - 3]
                    && board[i - 1][j - 1] == '*' && board[i][j - 1] != '*') {
                    ai_choice = 3;
                }
            }
        }
        //blocking descending diagonal win 4
        for (int i = 4; i < 6; i++) {
            for (int j = 3; j < 7; j++) {
                if (board[i][j] == '*' && board[i - 1][j - 1] == 'X' && board[i - 1][j - 1] == board[i - 2][j - 2] && board[i - 1][j - 1] == board[i - 3][j - 3]
                    && board[i + 1][j] != '*') {
                    ai_choice = 4;
                }
            }
        }
    }
}