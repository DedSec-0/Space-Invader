#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

//Global Variables
bool GameOver = false;		//Check whether game is over or not
int ManX = 30;				//Sets the position of the player on X axis on the map
const int ManY = 22;		//Sets the position of the player on Y axis on the map
int Score = 0;				//Record the Score Earned By a player

//Main Functions
void Draw();
void DrawShips(int Ships[], int DestroyedShips[], bool &Go, int Health, int y);
void DrawBullets(int Ships[], int DestroyedShips[], int Arr[][20], int Bullets, int &Bullets1, int &Ship, bool &Go);
void Moving(int bullets[][20], int &BulletsNum, int &Bullets1);
void Build_Clear(int i, int y);
void ShipsFire(int Ships[], int Arr[][10], int &Limit, bool &check, int &Health, int x1, int x2);

//ExtraFunctions
void gotoxy(int x, int y);
void hidecursor();
void DrawRocket();
int MakeMenu1();
int MakeMenu2();

void main()
{
	int option = 0;           //For Menu 1
	int option1 = 0;			//For Menu 2

	while (option != 3)
	{
		//Refilling
		int bullets[2][20] = { 0 };                   //Store x and y axis of bullets fired by player
		int ShipBullets[2][10] = { 0 };					//Store x and y axis of bullets fired by Space Ships
		int Ships[15] = { 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11 };		//Stores X and Y axis of Destroyed Space Ships
		int DestroyedShips[15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };			//Stores Amount of Destroyed Space Ships for each X axis
		int Health = 100;			//Stored Health of the player
		int x1 = 15, x2 = 24;		//Decreasing the Range of Fired Bullets from SpaceShips Frequently
		int BulletsNum = 0;			//Record Amount of bullets Fired in a single magazine
		int Bullets1 = 0;			//Record Total Amount of bullets Fired
		int Ship = 0;				//Recording Total Amount of Destroyed Ships
		int Difficulty = 0;			//Saves the difficulty level for user
		int ShipMove = 4;			//Push all the ships below after few Seconds
		int Limit = 1;				//Record Amount of bullets fired by ships and get 0 after 10 fires
		float fire = 0;				//Delay the Firing Time of ships
		float count = 0;			//Delay the Decreasing of range of x1 and x2
		float count1 = 0;			//Delay the Movement time of the ships
		bool Go = false;			//Give Signal if the Space Ship is destroyed
		bool check = true;			//Controls the randomly generation of bullets from ships
		bool Won = false;			//Check whether player is won or lose
		Score = 0;
		option = MakeMenu1();
		if (option == 1 || option == 2)
		{
			option1 = MakeMenu2();
			switch (option1)
			{
			case 1: Difficulty = 0; break;
			case 2: Difficulty = 2; break;
			case 3: Difficulty = 4; break;
			default:
				gotoxy(0, 0);
				cout << "Wrong option Selected... Easy Level Will start by Default" << endl;
				system("pause");
				break;
			}

			hidecursor();
			GameOver = false;
			Draw();
			while (!GameOver)
			{
				DrawShips(Ships, DestroyedShips, Go, Health, ShipMove);
				DrawBullets(Ships, DestroyedShips, bullets, BulletsNum, Bullets1, Ship, Go);
				Moving(bullets, BulletsNum, Bullets1);
				Sleep(50);

				for (int i = 1; i < 13; i++)
				{
					GameOver = true;
					Won = true;
					if (Ships[i] > 5 + ShipMove || Ships[0] > 6 + ShipMove || Ships[14] > 6 + ShipMove)
					{
						GameOver = false;
						Won = false;
						break;
					}
				}
				if (count >= 5)
				{
					if (x1 > 1)
						x1--;
					if (x2 < 31)
						x2++;
					count = 0;
				}
				if (count1 >= 10 - Difficulty)
				{
					Build_Clear(1, ShipMove);
					ShipMove++;
					if (ShipMove+8 == ManY)
						GameOver = true;

					for (int i = 0; i < 15; i++)
					{
						Ships[i]++;
					}
					count1 = 0;
				}
				if (fire >= 5 - Difficulty && Limit < 10)
				{
					Limit++;
					check = true;
					fire = 0;
				}
				ShipsFire(Ships, ShipBullets, Limit, check, Health, x1, x2);
				fire += 0.1;
				count += 0.1;
				count1 += 0.1;
			}
			system("cls");
			gotoxy(26, 0);
			if (Won)
				cout << "GAME OVER !!!... Well Played :)";
			else
				cout << "GAME OVER !!!... Better Luck Next Time :)";
		}
		else if (option != 3)
		{
			gotoxy(26, 0);
			cout << "Wrong Input !!!!....                                 ";
			option = 0;
		}
	}

	system("cls");
	cout << "Quitting . . . ." << endl;
	system("pause");
}

void Draw()
{
	system("cls");
	cout << "                            Space Invader" << endl << endl << endl;
	cout << "##################################################################" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "#                                                                #" << endl;
	cout << "##################################################################" << endl;

	gotoxy(ManX, ManY);
	cout << "W";

	system("color 0a");
}

void DrawBullets(int Ships[], int DestroyedShips[], int Arr[][20], int Bullets, int &Bullets1, int &Ship, bool &Go)
{
	for (int i = 0; i < Bullets; i++)
	{
		if (Bullets < 20)
		{
			if (Arr[1][i] > 0)
				Arr[1][i]--;
			if (Arr[1][i] < 21 && Arr[1][i] >= Ships[ManX - 24])
			{
				gotoxy(Arr[0][i], Arr[1][i] + 1);
				cout << " ";
				Go = true;
			}
			if (Arr[1][i] > Ships[ManX - 24])
			{
				gotoxy(Arr[0][i], Arr[1][i]);
				cout << "O";
			}
			if (Ships[ManX - 24] == Arr[1][i] && Ship < Bullets1  && Ships[ManX - 24] > 4)
			{
				DestroyedShips[ManX - 24]++;
				Ships[ManX - 24] -= 1;
				Ship++;
				Score++;
			}
		}
		else
		{
			if (Arr[1][i] < 21 && Arr[1][i] > 3)
			{
				gotoxy(Arr[0][i], Arr[1][i]);
				cout << " ";

				if (Arr[1][i] < 22)
					Arr[1][i] += 2;

				else if (Arr[1][i] == 22)
					Arr[1][i] = 3;
			}
		}
	}
}

void Moving(int bullets[][20], int &BulletsNum, int &Bullets1)
{
	char key;

	if (_kbhit() != 0)
	{
		key = _getch();
		switch (key)
		{
		case 'a':
			gotoxy(ManX, ManY);
			cout << " ";
			ManX--;
			if (ManX <= 23)
				ManX = 38;
			gotoxy(ManX, ManY);
			cout << "W";
			break;

		case 'd':
			gotoxy(ManX, ManY);
			cout << " ";
			ManX++;
			if (ManX >= 39)
				ManX = 24;
			gotoxy(ManX, ManY);
			cout << "W";
			break;

		case 'f':
			if (BulletsNum == 20)
			{
				gotoxy(68, 16);
				cout << "Reload !!!";
				break;
			}
			bullets[0][BulletsNum] = ManX;
			bullets[1][BulletsNum] = ManY;
			BulletsNum++;
			Bullets1++;
			break;

		case 'r':
			BulletsNum = 0;
			for (int i = 0; i < 10; i++)
			{
				gotoxy(68 + i, 16);
				cout << " ";
			}
		default:
			break;
		}
	}
}

void DrawShips(int Ships[], int DestroyedShips[], bool &Go, int Health, int y)
{
	bool flag = false;

	gotoxy(0, 1);
	cout << "Your Score: " << Score << endl << endl;
	gotoxy(78, 10);
	cout << " ";
	gotoxy(67, 10);
	cout << "Health: " << Health << "%";

	Build_Clear(0, y);
	if (Go)
	{
		for (int k = 0; k < 15; k++)
		{
			for (int z = 0; z < DestroyedShips[k]; z++)
			{
				gotoxy(24 + k, (Ships[k]) + (z + 2));
				cout << " ";
			}
		}
	}
}

void Build_Clear(int i, int y)
{
	int AxisY = 1;
	int x = 31;
	int AxisX = 0;
	int Num = 1;

	if (i == 0)
	{

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < AxisY; j++, AxisX += 2)
			{
				gotoxy(x + AxisX, y + AxisY);
				cout << "@";
			}

			AxisY++;
			Num += 2;
			AxisX -= Num;
		}
	}
	else if (i == 1)
	{
		for (int i = 0; i < 5 + y; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				gotoxy(24 + j, 4 + i);
				cout << " ";
			}
		}
	}
}

void ShipsFire(int Ships[], int Arr[][10], int &Limit, bool &check, int &Health, int x1, int x2)
{
	int y = 0;
	int Exclude[7] = { 1, 3, 5, 7, 9, 11, 13 };
	bool flag = true;

	if (check)
	{
		srand(time(NULL));
		Arr[0][Limit - 1] = rand() % x1 + x2;
		y = rand() % 15;

		for (int i = 0; i < 7; i++)
		{
			if (y == Exclude[i])
			{
				y++;
				break;
			}
		}
		Arr[1][Limit - 1] = Ships[y];
	}

	for (int i = 0; i < Limit; i++)
	{
		if (Arr[1][i] < ManY && Arr[1][i] + 1 > Ships[y])
		{
			gotoxy(Arr[0][i], Arr[1][i]);
			cout << " ";
		}
		if (Arr[1][i] < ManY - 1)
		{
			gotoxy(Arr[0][i], Arr[1][i] + 1);
			cout << "o";
		}
		if (ManY == Arr[1][i] + 1 && ManX == Arr[0][i])
		{
			Health -= 25;
			if (Health <= 0)
			{
				GameOver = true;
				break;
			}
		}
		if (Arr[1][i] < ManY)
			Arr[1][i]++;
	}


	if (Arr[1][9] == ManY)
	{
		Limit = 0;
		for (int i = 0; i < 10; i++)
		{
			Arr[1][i] = Ships[ManX - 24] + i;
		}
	}
	check = false;

}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void DrawRocket()
{
	cout << "         \ ______			" << endl;
	cout << "      ###[==_____>			" << endl;
	cout << "        /_/     			" << endl;
	cout << "                 \ \ _______	" << endl;
	cout << "               ###[==_____>	" << endl;
	cout << "                  /_/		" << endl;
}

int MakeMenu1()
{
	const int y = 2;
	int o = 0;
	system("color 1f");

	gotoxy(25, y);
	cout << "Welcome to Space Invader Game" << endl << endl;
	gotoxy(25, y + 2);
	cout << "************************************" << endl;
	gotoxy(25, y + 3);
	cout << "* 1. Launch your rocket	    *" << endl;
	gotoxy(25, y + 4);
	cout << "* 2. Launch Rocket Again	    *" << endl;
	gotoxy(25, y + 5);
	cout << "* 3. Quit:			    *" << endl;
	gotoxy(25, y + 6);
	cout << "************************************" << endl;

	DrawRocket();
	gotoxy(36, y + 5);
	cin >> o;

	return o;
}

int MakeMenu2()
{
	const int y = 2;
	int o = 0;
	system("cls");

	gotoxy(25, y + 2);
	cout << "********************" << endl;
	gotoxy(25, y + 3);
	cout << "* 1. Easy	    *" << endl;
	gotoxy(25, y + 4);
	cout << "* 2. Medium	    *" << endl;
	gotoxy(25, y + 5);
	cout << "* 3. Hard	    *" << endl;
	gotoxy(25, y + 6);
	cout << "********************" << endl;

	DrawRocket();
	gotoxy(36, y + 5);
	cin >> o;

	return o;
}