#include <ctime>
#include <iostream>
using namespace std;

//Board
const int Rows = 8;
const int Columns = 8;

int NPCBoard[Rows][Columns];

int PlayerBoard[Rows][Columns];

//Ships
int MaxShips = 10;

/*Guide:
0 - no ship
1 - ship
2 - sunk ship
3 - guess
4 - nearby
*/

void ClearBoard()
{
	for (int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Columns; c++)
		{
			NPCBoard[r][c] = 0;
		}
	}
}

//I tried to abstract this by passing through (int BoardName[Rows][Columns) but it did not work
void DisplayNPCBoard()
{
	for (int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Columns; c++)
		{
			cout << NPCBoard[r][c] << " ";
		}
		cout << endl;
	}
}

void DisplayPlayerBoard()
{
	for (int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Columns; c++)
		{
			cout << PlayerBoard[r][c] << " ";
		}
		cout << endl;
	}
}

void SetBoardRandomly()
{
	int s = 0;
	while (s < MaxShips)
	{
		int x = rand() % Rows;
		int y = rand() % Columns;
		if (NPCBoard[x][y] != 1)
		{
			s++;
			NPCBoard[x][y] = 1;
		}
	}
}

bool Guess(int x, int y)
{
	if (NPCBoard[x][y] == 1)//If position has a ship
	{
		NPCBoard[x][y] = 2;//Set that ship to sunk
		PlayerBoard[x][y] = 2;//Sunk
		return true;//Hit
	}
	else
	{
		PlayerBoard[x][y] = 3;//Guess
	}
	return false;//Miss
}


bool CheckSurrounding(int x, int y) //2,2
{
	int InitalX = x;
	int InitalY = y;
	bool Found = false;
	if (NPCBoard[x - 1][y] == 1) //Left
	{
		Found = true;
		x -= 1;//1,2
	}
	if (NPCBoard[x][y - 1] == 1) //Left Top
	{
		Found = true;
		y -= 1;//1,1
	}
	if (NPCBoard[x + 1][y] == 1) //Top
	{
		Found = true;
		x += 1;//2,1
	}
	if (NPCBoard[x + 1][y] == 1) //Top Right
	{
		Found = true;
		x += 1;//3,1
	}
	if (NPCBoard[x][y + 1] == 1) //Right
	{
		Found = true;
		y += 1;//3,2
	}
	if (NPCBoard[x][y + 1] == 1) //Right Bottom
	{
		Found = true;
		y += 1;//3,3
	}
	if (NPCBoard[x - 1][y] == 1) //Bottom
	{
		Found = true;
		x -= 1;//2,3
	}
	if (NPCBoard[x - 1][y] == 1) //Bottom Left
	{
		Found = true;
		x -= 1;//1,3
	}

	if (Found == true) //set the surrounding to 4 to signal nearby
	{
		NPCBoard[x - 1][y] = 4; //1,2
		NPCBoard[x][y - 1] = 4; //1,1
		NPCBoard[x + 1][y] = 4; //2,1
		NPCBoard[x + 1][y] = 4; //3,1
		NPCBoard[x][y + 1] = 4; //3,2
		NPCBoard[x][y + 1] = 4; //3,3
		NPCBoard[x - 1][y] = 4; //2,3
		NPCBoard[x - 1][y] = 4; //1,3
	}

	return Found;
}

int NumberOfShipsLeft()
{
	int NumberOfShips = 0;
	for (int r = 0; r < Rows; r++)
	{
		for (int c = 0; c < Columns; c++)
		{
			if (NPCBoard[r][c] == 1)
			{
				NumberOfShips++;
			}
		}
	}
	return NumberOfShips;
}


bool SeeGuideAgain()
{
	bool SeeAgain = false;
	char input;
	cout << "Would you like to see the guide again Y or N?"; cin >> input;
	if (tolower(input) == 'y')
	{
		SeeAgain = true;
	}
	return SeeAgain;
}

void PrintGuide()
{
	//Guide
	cout << "Guide:\n0 - unknown\n1 - ship\n2 - sunk ship\n3 - guess\n4 - nearby" << endl;
}

int main()
{
	srand(time(NULL));
	ClearBoard();
	SetBoardRandomly();

	cout << "Welcome to Battleship!\nthere are " << MaxShips << " ships" << endl;

	PrintGuide();

	int guessX, guessY;
	while (NumberOfShipsLeft() != 0)
	{
		cout << "Where would you like to guess a ships is located? "; cin >> guessX >> guessY;
		if (Guess(guessX, guessY))
		{
			cout << "You hit a ship!\nThat ship is now sunk\nThere are now " << NumberOfShipsLeft() << " left" << endl;
		}
		else
		{
			if (CheckSurrounding(guessX, guessY))
			{
				cout << "You missed, but there is a ship nearby...\nThere are still " << NumberOfShipsLeft() << " left" << endl;
			}
			else
			{
				cout << "You missed :(\nThere are still " << NumberOfShipsLeft() << " left" << endl;
			}

		}
		cout << "\n_______________\n" << endl;
		DisplayPlayerBoard();
		cout << "________________\n" << endl;
		if (SeeGuideAgain() == true) {
			PrintGuide();
		}

	}
	cout << "You have found all the ships and completed the game!\nThank you for playing :)" << endl;
	DisplayNPCBoard();
	system("pause");
	return 0;
}