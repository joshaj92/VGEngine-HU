#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

struct Parent
{
	int A;
	int B;
};
struct Positions
{
	int startposA;
	int startposB;
	int finalposA;
	int finalposB;
	int currposA;
	int currposB;
	int pathposA;
	int pathposB;
};
struct GNode
{
	int A, B;
	int pos;
	int Hval;
	int Gval;
	int Fval;
	bool parented;
	Parent par;
	string pathed;
	char met;
};
void Initialize(GNode Block[][4]);
Positions SetUp(int startposA, int startposB, int finalposA, int finalposB, GNode Block[][4]); 
void GetHval(int startposA, int startposB, int finalposA, int finalposB, GNode Block[][4]);
Positions GetFGval(int startposA, int startposB, int finalposA, int finalposB, GNode Block[][4]);
void SetPath(int startposA, int startposB, int finalposA, int finalposB, int currposA, int currposB, GNode Block[][4]);
void Show(GNode Block[][4]);

int main()
{
	//Variales
	Positions pos;
	int hval = 0;;
	int gval = 0;;
	int fval = 0;;
	int currpos;
	int currposA = -1;
	int currposB = -1;
	int startposA = -1;
	int startposB = -1;
	int finalposA = -1;
	int finalposB = -1;	
	GNode Block[4][4];
	
	Initialize(Block);
	Show(Block); //Display
	//Set Up Positions of Blocks, starting point, and final point
	pos = SetUp(startposA, startposB, finalposA,  finalposB, Block);
	startposA = pos.startposA;
	startposB = pos.startposB;  
	finalposA = pos.finalposA;
	finalposB = pos.finalposB;
	
	GetHval( startposA,  startposB,  finalposA,  finalposB,  Block);//Set Up H-values	
	Show(Block); //Display
	system("pause");

	//Set up F an G values
	pos = GetFGval( startposA,  startposB,  finalposA,  finalposB,  Block);
	currposA = pos.currposA;
	currposB = pos.currposB;
	system("pause");
	
	SetPath( startposA,  startposB,  finalposA,  finalposB, currposA, currposB, Block); //Define Path	
	Show(Block); //Display

	return 0;
}

void Initialize(GNode Block[][4])
{
	Block[0][0].met = '-';
	Block[0][1].met = '-';
	Block[0][2].met = '-';
	Block[0][3].met = '-';
	Block[1][0].met = '-';
	Block[1][1].met = '-';
	Block[1][2].met = '-';
	Block[1][3].met = '-';
	Block[2][0].met = '-';
	Block[2][1].met = '-';
	Block[2][2].met = '-';
	Block[2][3].met = '-';
	Block[3][0].met = '-';
	Block[3][1].met = '-';
	Block[3][2].met = '-';
	Block[3][3].met = '-';
	
	Block[0][0].pathed = "-----";
	Block[0][1].pathed = "-----";
	Block[0][2].pathed = "-----";
	Block[0][3].pathed = "-----";
	Block[1][0].pathed = "-----";
	Block[1][1].pathed = "-----";
	Block[1][2].pathed = "-----";
	Block[1][3].pathed = "-----";
	Block[2][0].pathed = "-----";
	Block[2][1].pathed = "-----";
	Block[2][2].pathed = "-----";
	Block[2][3].pathed = "-----";
	Block[3][0].pathed = "-----";
	Block[3][1].pathed = "-----";
	Block[3][2].pathed = "-----";
	Block[3][3].pathed = "-----";
	
	Block[0][0].Fval = 0;
	Block[0][1].Fval = 0;
	Block[0][2].Fval = 0;
	Block[0][3].Fval = 0;
	Block[1][0].Fval = 0;
	Block[1][1].Fval = 0;
	Block[1][2].Fval = 0;
	Block[1][3].Fval = 0;
	Block[2][0].Fval = 0;
	Block[2][1].Fval = 0;
	Block[2][2].Fval = 0;
	Block[2][3].Fval = 0;
	Block[3][0].Fval = 0;
	Block[3][1].Fval = 0;
	Block[3][2].Fval = 0;
	Block[3][3].Fval = 0;
	
	Block[0][0].Gval = 0;
	Block[0][1].Gval = 0;
	Block[0][2].Gval = 0;
	Block[0][3].Gval = 0;
	Block[1][0].Gval = 0;
	Block[1][1].Gval = 0;
	Block[1][2].Gval = 0;
	Block[1][3].Gval = 0;
	Block[2][0].Gval = 0;
	Block[2][1].Gval = 0;
	Block[2][2].Gval = 0;
	Block[2][3].Gval = 0;
	Block[3][0].Gval = 0;
	Block[3][1].Gval = 0;
	Block[3][2].Gval = 0;
	Block[3][3].Gval = 0;
	
	Block[0][0].parented = false;
	Block[0][1].parented = false;
	Block[0][2].parented = false;
	Block[0][3].parented = false;
	Block[1][0].parented = false;
	Block[1][1].parented = false;
	Block[1][2].parented = false;
	Block[1][3].parented = false;
	Block[2][0].parented = false;
	Block[2][1].parented = false;
	Block[2][2].parented = false;
	Block[2][3].parented = false;
	Block[3][0].parented = false;
	Block[3][1].parented = false;
	Block[3][2].parented = false;
	Block[3][3].parented = false;
}
Positions SetUp(int startposA, int startposB, int finalposA, int finalposB, GNode Block[][4])
{
	Positions pos;
	int i;
	int j;
	int obst;
	int spotA;
	int spotB;

	cout << "Enter amount of blocks: ";
	cin >> obst;
	cout << "Enter Positions of Blocked Spots" << endl;
	i = 0;
	while (i < obst)
	{
		cout << i + 1 << ". A: ";
		cin >> spotA;
		cout << i + 1 << ". B: ";
		cin >> spotB;
		Block[spotA - 1][spotB - 1].met = 'x';
		Block[spotA - 1][spotB - 1].pathed = "BLOCK";
		Block[spotA - 1][spotB - 1].Fval = -99;
		Block[spotA - 1][spotB - 1].par.A = -1;
		Block[spotA - 1][spotB - 1].par.B = -1;
		i++;
	}
	cout << endl;
	cout << "Start Position A: "; 
	cin >> startposB;
	cout << "Start Position B: "; 
	cin >> startposA;
	cout << "Final Position A: ";
	cin >> finalposB;
	cout << "Final Position B: ";
	cin >> finalposA;
	
	startposA--;
	startposB--;
	finalposA--;
	finalposB--;
	Block[startposA][startposB].pathed = "START";
	Block[finalposA][finalposB].pathed = "-END-";
	pos.startposA = startposA;
	pos.startposB = startposB;
	pos.finalposA = finalposA;
	pos.finalposB = finalposB;

	return pos;
}
void GetHval(int startposA, int startposB, int finalposA, int finalposB, GNode Block[][4])
{
	int hval = 0;
	int Test[4][4];
	Test[0][0] = 0;
	Test[0][1] = 0;
	Test[0][2] = 0;
	Test[0][3] = 0;
	Test[1][0] = 0;
	Test[1][1] = 0;
	Test[1][2] = 0;
	Test[1][3] = 0;
	Test[2][0] = 0;
	Test[2][1] = 0;
	Test[2][2] = 0;
	Test[2][3] = 0;
	Test[3][0] = 0;
	Test[3][1] = 0;
	Test[3][2] = 0;
	Test[3][3] = 0;
	int i = 0;
	int j = 0;
	cout << "-----1----2----3----4---" << endl << endl;
	cout << "1 | " << Test[0][0] << " | " << Test[0][1] << " | " << Test[0][2] << " | " << Test[0][3] << " |" << endl;
	cout << "-----------------" << endl;
	cout << "2 | " << Test[1][0] << " | " << Test[1][1] << " | " << Test[1][2] << " | " << Test[1][3] << " |" << endl;
	cout << "-----------------" << endl;
	cout << "3 | " << Test[2][0] << " | " << Test[2][1] << " | " << Test[2][2] << " | " << Test[2][3] << " |" << endl;
	cout << "-----------------" << endl;
	cout << "4 | " << Test[3][0] << " | " << Test[3][1] << " | " << Test[3][2] << " | " << Test[3][3] << " |" << endl;  
	cout << "---------------------" << endl;

	Test[startposB - 1][startposA - 1] = 1;
	Test[finalposB - 1][finalposA - 1] = 2;
	
	cout << "----1---2---3---4--" << endl << endl;
	cout << "1 | " << Test[0][0] << " | " << Test[0][1] << " | " << Test[0][2] << " | " << Test[0][3] << " |" << endl;
	cout << "-----------------" << endl;
	cout << "2 | " << Test[1][0] << " | " << Test[1][1] << " | " << Test[1][2] << " | " << Test[1][3] << " |" << endl;
	cout << "-----------------" << endl;
	cout << "3 | " << Test[2][0] << " | " << Test[2][1] << " | " << Test[2][2] << " | " << Test[2][3] << " |" << endl;
	cout << "-----------------" << endl;
	cout << "4 | " << Test[3][0] << " | " << Test[3][1] << " | " << Test[3][2] << " | " << Test[3][3] << " |" << endl;  
	cout << "--------------------" << endl << endl;

	startposA = 0;
	startposB = 0;

	cout << "CurrentPosA: " << startposB << endl;
	cout << "CurrentPosB: " << startposA << endl;

	int nodes = 0;
	int startA = 0;;
	int startB = 0;;
	int finalA = 0;;
	int finalB = 0;;
	while (nodes < 19)
	{
		startA = startposA;
		startB = startposB;
		while ((startposB != finalposB) || (startposA != finalposA))
		{
			hval++;
			
			if (startposB < finalposB)
			{
				if (startposB < 4)
				{
					startposB++;
					Test[startposB][startposA] = 1;
				}
			}
			else if (startposB > finalposB)
			{
				if (startposB >= 0)
				{
					startposB--;
					Test[startposB][startposA] = 1;
				}
			}
			else
			{
				if ((startposA < finalposA))
				{
					if (startposA < 4)
					{
						startposA++;
						Test[startposB][startposA] = 1;
					}
				}
				else if ((startposA > finalposA))
				{
					if (startposA >= 0)
					{
						startposA--;
						Test[startposB][startposA] = 1;
					}
				}
			}
		}
		Test[0][0] = 0;
		Test[0][1] = 0;
		Test[0][2] = 0;
		Test[0][3] = 0;
		Test[1][0] = 0;
		Test[1][1] = 0;
		Test[1][2] = 0;
		Test[1][3] = 0;
		Test[2][0] = 0;
		Test[2][1] = 0;
		Test[2][2] = 0;
		Test[2][3] = 0;
		Test[3][0] = 0;
		Test[3][1] = 0;
		Test[3][2] = 0;
		Test[3][3] = 0;
		startposA = startA;
		startposB = startB;
		if (startposA < 4 && startposB < 4)
		{
			Block[startposA][startposB].Hval = hval;
		}
		hval = 0;
		if (startposA == 4)
		{
			startposB++;
			startposA = 0;
		}
		else
		{
			startposA++;
		}
		nodes++;
	}
	cout << endl;
	cout << "-----1----2----3----4--" << endl << endl;
	cout << "1 | " << Block[0][0].Hval << " | " << Block[0][1].Hval << " | " << Block[0][2].Hval << " | " << Block[0][3].Hval << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "2 | " << Block[1][0].Hval << " | " << Block[1][1].Hval << " | " << Block[1][2].Hval << " | " << Block[1][3].Hval << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "3 | " << Block[2][0].Hval << " | " << Block[2][1].Hval << " | " << Block[2][2].Hval << " | " << Block[2][3].Hval << " |" << endl;
	cout << "-----------------------" << endl;
	cout << "4 | " << Block[3][0].Hval << " | " << Block[3][1].Hval << " | " << Block[3][2].Hval << " | " << Block[3][3].Hval << " |" << endl;  
	cout << "-----------------------" << endl << endl;
	
}
Positions GetFGval(int startposA, int startposB, int finalposA, int finalposB, GNode Block[][4])
{
	Positions pos;
	int currposA = startposA;
	int currposB = startposB;
	
	Block[currposA][currposB].par.A = currposA;
	Block[currposA][currposB].par.B = currposB;
	
	int i = 0;
	int j = 0;
	int cA = 0;
	int cB = 0;
	int xhval;
	int xA[8];
	int xB[8];
	int A[8];
	int B[8];
	int index = 0;
	int shortest = 999;
	int Gswitch = 0;

	while (!(currposA == finalposA && currposB == finalposB))
	{
		cout << "Current Position: " << currposA+1 << ", " << currposB+1 << endl;
		Block[currposA][currposB].met = 'c';
		
		A[0] = currposA - 0;
		A[1] = currposA + 1;
		A[2] = currposA + 1;
		A[3] = currposA + 1;
		A[4] = currposA + 0;
		A[5] = currposA - 1;
		A[6] = currposA - 1;
		A[7] = currposA - 1;

		B[0] = currposB - 1;
		B[1] = currposB - 1;
		B[2] = currposB + 0;
		B[3] = currposB + 1;
		B[4] = currposB + 1;
		B[5] = currposB + 1;
		B[6] = currposB - 0;
		B[7] = currposB - 1;
		
		cout << "1. " << A[0] + 1 << ", " << B[0] + 1 << endl;
		cout << "2. " << A[1] + 1 << ", " << B[1] + 1 << endl;
		cout << "3. " << A[2] + 1 << ", " << B[2] + 1 << endl;
		cout << "4. " << A[3] + 1 << ", " << B[3] + 1 << endl;
		cout << "5. " << A[4] + 1 << ", " << B[4] + 1 << endl;
		cout << "6. " << A[5] + 1 << ", " << B[5] + 1 << endl;
		cout << "7. " << A[6] + 1 << ", " << B[6] + 1 << endl;
		cout << "8. " << A[7] + 1 << ", " << B[7] + 1 << endl;

		index = 0;
		Gswitch = 0;
		while (index < 8)
		{
			if ((A[index] >= 0) && (A[index] < 4) && (B[index] >= 0) && (B[index] < 4) && (Block[A[index]][B[index]].met != 'c') && (Block[A[index]][B[index]].met != 'o') && (Block[A[index]][B[index]].met != 'x') && !Block[A[index]][B[index]].parented)
			{
				//Set Up G-values
				if (Gswitch == 0)
				{
					Block[A[index]][B[index]].Gval = Block[currposA][currposB].Gval + 10;
					Gswitch = 1;
				}
				else if (Gswitch == 1)
				{
					Block[A[index]][B[index]].Gval = Block[currposA][currposB].Gval + 14;
					Gswitch = 0;
				}
				//Set Up F-Values
				Block[A[index]][B[index]].Fval = Block[A[index]][B[index]].Gval + Block[A[index]][B[index]].Hval;	
				//Set Open Status
				Block[A[index]][B[index]].met = 'o';
				//Set Up Parent
				if (Block[currposA][currposB].met == 'x')
				{
					i = 0;
					xA[0] = A[index] - 0;
					xA[1] = A[index] + 1;
					xA[2] = A[index] + 1;
					xA[3] = A[index] + 1;
					xA[4] = A[index] + 0;
					xA[5] = A[index] - 1;
					xA[6] = A[index] - 1;
					xA[7] = A[index] - 1;
					xB[0] = B[index] - 1;
					xB[1] = B[index] - 1;
					xB[2] = B[index] + 0;
					xB[3] = B[index] + 1;
					xB[4] = B[index] + 1;
					xB[5] = B[index] + 1;
					xB[6] = B[index] - 0;
					xB[7] = B[index] - 1;
					while (i < 8)
					{
						if ((xA[i] >= 0) && (xA[i] < 4) && (xB[i] >= 0) && (xB[i] < 4))
						{
							system("pause");
							if (Block[xA[i]][xB[i]].met == 'c')
							{
								Block[A[index]][B[index]].par.A = xA[i];
								Block[A[index]][B[index]].par.B = xB[i];
								Block[A[index]][B[index]].parented = true;
							}
							i++;
						}
						else
						{
							i++;
						}
					}
				}
				else
				{
					Block[A[index]][B[index]].par.A = currposA;
					Block[A[index]][B[index]].par.B = currposB;
					Block[A[index]][B[index]].parented = true;
				}
			}
			index++;
		}
		
		//Search for the shortest in the open list
		cA = 0;
		cB = 0;
		index = 0;
		shortest = 999;
		while (index < 19)
		{
			if (cA == 4)
			{	cA = 0;
				cB++;	}
			else
			{	cA++;	}

			if ((Block[cA][cB].met == 'o') && (shortest > Block[cA][cB].Fval))
			{
				shortest = Block[cA][cB].Fval;
				cout << "Short Guy:" << shortest << endl;
				currposA = cA;
				currposB = cB;
				index++;
			}
			else
			{
				index++;
			}
		}

		cout <<"Shortest: " << shortest << ": " << currposA + 1 << ", " << currposB + 1 << endl;
		cout << endl;
		cout << "----1---2---3---4--" << endl << endl;
		cout << "  |" << Block[0][0].Hval << "    |" << Block[0][1].Hval << "    |" << Block[0][2].Hval << "    |" << Block[0][3].Hval << "    |" << endl;
		cout << "1 |  " << Block[0][0].met << "  |  " << Block[0][1].met << "  |  " << Block[0][2].met << "  |  " << Block[0][3].met << "  |" << endl;
		cout << "  |   " << Block[0][0].Fval << "|   " << Block[0][1].Fval << "|   " << Block[0][2].Fval << "|   " << Block[0][3].Fval << "|" << endl;
		cout << "-------------------" << endl << endl;
		cout << "  |" << Block[1][0].Hval << "    |" << Block[1][1].Hval << "    |" << Block[1][2].Hval << "    |" << Block[1][3].Hval << "    |" << endl;
		cout << "2 |  " << Block[1][0].met << "  |  " << Block[1][1].met << "  |  " << Block[1][2].met << "  |  " << Block[1][3].met << "  |" << endl;
		cout << "  |   " << Block[1][0].Fval << "|   " << Block[1][1].Fval << "|   " << Block[1][2].Fval << "|   " << Block[1][3].Fval << "|" << endl;
		cout << "-------------------" << endl << endl;
		cout << "  |" << Block[2][0].Hval << "    |" << Block[2][1].Hval << "    |" << Block[2][2].Hval << "    |" << Block[2][3].Hval << "    |" << endl;
		cout << "3 |  " << Block[2][0].met << "  |  " << Block[2][1].met << "  |  " << Block[2][2].met << "  |  " << Block[2][3].met << "  |" << endl;
		cout << "  |   " << Block[2][0].Fval << "|   " << Block[2][1].Fval << "|   " << Block[2][2].Fval << "|   " << Block[2][3].Fval << "|" << endl;
		cout << "-------------------" << endl << endl;
		cout << "  |" << Block[3][0].Hval << "    |" << Block[3][1].Hval << "    |" << Block[3][2].Hval << "    |" << Block[3][3].Hval << "    |" << endl;
		cout << "4 |  " << Block[3][0].met << "  |  " << Block[3][1].met << "  |  " << Block[3][2].met << "  |  " << Block[3][3].met << "  |" << endl;
		cout << "  |   " << Block[3][0].Fval << "|   " << Block[3][1].Fval << "|   " << Block[3][2].Fval << "|   " << Block[3][3].Fval << "|" << endl; 
		cout << "-------------------" << endl << endl;
		if ((currposA == finalposA) && (currposB == finalposB))
		{
			cout << "FOUND!" << endl;
		}
	}
	Block[currposA][currposB].met = 'c';
	pos.currposA = currposA;
	pos.currposB = currposB;
	return pos;
}
void SetPath(int startposA, int startposB, int finalposA, int finalposB, int currposA, int currposB, GNode Block[][4])
{
	int i = 0;
	int pathposA = startposA;
	int pathposB = startposB;
	int xA[8];
	int xB[8];
	int A[8];
	int B[8];
	int index = 0;

	while (!(currposA == pathposA && currposB == pathposB))
	{
		Block[currposA][currposB].pathed = "FPATH";
		currposA = Block[currposA][currposB].par.A;
		currposB = Block[currposA][currposB].par.B;
		if (Block[currposA][currposB].met == 'x')
		{
			i = 0;
			xA[0] = A[index] - 0;
			xA[1] = A[index] + 1;
			xA[2] = A[index] + 1;
			xA[3] = A[index] + 1;
			xA[4] = A[index] + 0;
			xA[5] = A[index] - 1;
			xA[6] = A[index] - 1;
			xA[7] = A[index] - 1;
			xB[0] = B[index] - 1;
			xB[1] = B[index] - 1;
			xB[2] = B[index] + 0;
			xB[3] = B[index] + 1;
			xB[4] = B[index] + 1;
			xB[5] = B[index] + 1;
			xB[6] = B[index] - 0;
			xB[7] = B[index] - 1;
			while (i < 8)
			{
				if ((xA[i] >= 0) && (xA[i] < 4) && (xB[i] >= 0) && (xB[i] < 4))
				{
					system("pause");
					if (Block[xA[i]][xB[i]].met == 'c')
					{
						Block[A[index]][B[index]].par.A = xA[i];
						Block[A[index]][B[index]].par.B = xB[i];
						Block[A[index]][B[index]].parented = true;
					}
					i++;
				}
				else
				{
					i++;
				}
			}
		}
		cout << endl;
		cout << "----1---2---3---4--" << endl << endl;
		cout << "  |" << Block[0][0].Hval << "    |" << Block[0][1].Hval << "    |" << Block[0][2].Hval << "    |" << Block[0][3].Hval << "    |" << endl;
		cout << "1 |" << Block[0][0].pathed << "|" << Block[0][1].pathed << "|" << Block[0][2].pathed << "|" << Block[0][3].pathed << "|" << endl;
		cout << "  |   " << Block[0][0].Fval << "|   " << Block[0][1].Fval << "|   " << Block[0][2].Fval << "|   " << Block[0][3].Fval << "|" << endl;
		cout << "-------------------" << endl << endl;
		cout << "  |" << Block[1][0].Hval << "    |" << Block[1][1].Hval << "    |" << Block[1][2].Hval << "    |" << Block[1][3].Hval << "    |" << endl;
		cout << "2 |" << Block[1][0].pathed << "|" << Block[1][1].pathed << "|" << Block[1][2].pathed << "|" << Block[1][3].pathed << "|" << endl;
		cout << "  |   " << Block[1][0].Fval << "|   " << Block[1][1].Fval << "|   " << Block[1][2].Fval << "|   " << Block[1][3].Fval << "|" << endl;
		cout << "-------------------" << endl << endl;
		cout << "  |" << Block[2][0].Hval << "    |" << Block[2][1].Hval << "    |" << Block[2][2].Hval << "    |" << Block[2][3].Hval << "    |" << endl;
		cout << "3 |" << Block[2][0].pathed << "|" << Block[2][1].pathed << "|" << Block[2][2].pathed << "|" << Block[2][3].pathed << "|" << endl;
		cout << "  |   " << Block[2][0].Fval << "|   " << Block[2][1].Fval << "|   " << Block[2][2].Fval << "|   " << Block[2][3].Fval << "|" << endl;
		cout << "-------------------" << endl << endl;
		cout << "  |" << Block[3][0].Hval << "    |" << Block[3][1].Hval << "    |" << Block[3][2].Hval << "    |" << Block[3][3].Hval << "    |" << endl;
		cout << "4 |" << Block[3][0].pathed << "|" << Block[3][1].pathed << "|" << Block[3][2].pathed << "|" << Block[3][3].pathed << "|" << endl;
		cout << "  |   " << Block[3][0].Fval << "|   " << Block[3][1].Fval << "|   " << Block[3][2].Fval << "|   " << Block[3][3].Fval << "|" << endl; 
		cout << "-------------------" << endl << endl;
		cout << "ParentA: " << Block[currposA][currposB].par.A << endl;
		cout << "ParentB: " << Block[currposA][currposB].par.B << endl;
		Block[currposA][currposB].pathed = "NEXTD";
		if (currposA == pathposA && currposB == pathposB)
		{
			cout << "Path Done!" << endl;
		}
		cout << endl;
	}
	Block[currposA][currposB].pathed = "FPATH";
	currposA = Block[currposA][currposB].par.A;
	currposB = Block[currposA][currposB].par.B;
	cout << "ParentA: " << Block[currposA][currposB].par.A << endl;
	cout << "ParentB: " << Block[currposA][currposB].par.B << endl;
}
void Show(GNode Block[][4])
{
	cout << endl;
	cout << "-----1----2----3----4--" << endl << endl;
	cout << "  |" << Block[0][0].Hval << "    |" << Block[0][1].Hval << "    |" << Block[0][2].Hval << "    |" << Block[0][3].Hval << "    |" << endl;
	cout << "1 |" << Block[0][0].pathed << "|" << Block[0][1].pathed << "|" << Block[0][2].pathed << "|" << Block[0][3].pathed << "|" << endl;
	cout << "  |   " << Block[0][0].Fval << "|   " << Block[0][1].Fval << "|   " << Block[0][2].Fval << "|   " << Block[0][3].Fval << "|" << endl;
	cout << "-----------------------" << endl << endl;
	cout << "  |" << Block[1][0].Hval << "    |" << Block[1][1].Hval << "    |" << Block[1][2].Hval << "    |" << Block[1][3].Hval << "    |" << endl;
	cout << "2 |" << Block[1][0].pathed << "|" << Block[1][1].pathed << "|" << Block[1][2].pathed << "|" << Block[1][3].pathed << "|" << endl;
	cout << "  |   " << Block[1][0].Fval << "|   " << Block[1][1].Fval << "|   " << Block[1][2].Fval << "|   " << Block[1][3].Fval << "|" << endl;
	cout << "-----------------------" << endl << endl;
	cout << "  |" << Block[2][0].Hval << "    |" << Block[2][1].Hval << "    |" << Block[2][2].Hval << "    |" << Block[2][3].Hval << "    |" << endl;
	cout << "3 |" << Block[2][0].pathed << "|" << Block[2][1].pathed << "|" << Block[2][2].pathed << "|" << Block[2][3].pathed << "|" << endl;
	cout << "  |   " << Block[2][0].Fval << "|   " << Block[2][1].Fval << "|   " << Block[2][2].Fval << "|   " << Block[2][3].Fval << "|" << endl;
	cout << "-----------------------" << endl << endl;
	cout << "  |" << Block[3][0].Hval << "    |" << Block[3][1].Hval << "    |" << Block[3][2].Hval << "    |" << Block[3][3].Hval << "    |" << endl;
	cout << "4 |" << Block[3][0].pathed << "|" << Block[3][1].pathed << "|" << Block[3][2].pathed << "|" << Block[3][3].pathed << "|" << endl;
	cout << "  |   " << Block[3][0].Fval << "|   " << Block[3][1].Fval << "|   " << Block[3][2].Fval << "|   " << Block[3][3].Fval << "|" << endl; 
	cout << "-----------------------" << endl << endl;
}
