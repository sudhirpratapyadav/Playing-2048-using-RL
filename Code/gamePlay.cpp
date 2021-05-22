#include <stdio.h>
#include <random>

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> val_rand(1, 10);

bool boardTranslate(int *BOARD,int move)
{
	/*
	move direction
	1 UP
	2 DOWN
	3 LEFT
	4 RIGHT
	*/
	int nBoard[16] = {};
	if (move == 1)
	{
		int ind[4] = {};
		for (int i = 0; i < 4; i++)
		{
			if (BOARD[i * 4] != 0)
			{
				nBoard[ind[0] * 4] = BOARD[i * 4];
				ind[0] = ind[0] + 1;
			}
			if (BOARD[i * 4 + 1] != 0)
			{
				nBoard[ind[1] * 4 + 1] = BOARD[i * 4 + 1];
				ind[1] = ind[1] + 1;
			}
			if (BOARD[i * 4 + 2] != 0)
			{
				nBoard[ind[2] * 4 + 2] = BOARD[i * 4 + 2];
				ind[2] = ind[2] + 1;
			}
			if (BOARD[i * 4 + 3] != 0)
			{
				nBoard[ind[3] * 4 + 3] = BOARD[i * 4 + 3];
				ind[3] = ind[3] + 1;
			}
		}
	}
	else if (move == 2)
	{
		int ind[4] = { 3, 3, 3, 3 };
		for (int i = 3; i >= 0; i--)
		{
			if (BOARD[i * 4] != 0)
			{
				nBoard[ind[0] * 4] = BOARD[i * 4];
				ind[0] = ind[0] - 1;
			}
			if (BOARD[i * 4 + 1] != 0)
			{
				nBoard[ind[1] * 4 + 1] = BOARD[i * 4 + 1];
				ind[1] = ind[1] - 1;
			}
			if (BOARD[i * 4 + 2] != 0)
			{
				nBoard[ind[2] * 4 + 2] = BOARD[i * 4 + 2];
				ind[2] = ind[2] - 1;
			}
			if (BOARD[i * 4 + 3] != 0)
			{
				nBoard[ind[3] * 4 + 3] = BOARD[i * 4 + 3];
				ind[3] = ind[3] - 1;
			}
		}
	}
	else if (move == 3)
	{
		int ind[4] = {};
		for (int i = 0; i < 4; i++)
		{
			if (BOARD[i] != 0)
			{
				nBoard[ind[0]] = BOARD[i];
				ind[0] = ind[0] + 1;
			}
			if (BOARD[i + 4] != 0)
			{
				nBoard[ind[1] + 4] = BOARD[i + 4];
				ind[1] = ind[1] + 1;
			}
			if (BOARD[i + 8] != 0)
			{
				nBoard[ind[2] + 8] = BOARD[i + 8];
				ind[2] = ind[2] + 1;
			}
			if (BOARD[i + 12] != 0)
			{
				nBoard[ind[3] + 12] = BOARD[i + 12];
				ind[3] = ind[3] + 1;
			}
		}
	}
	else if (move == 4)
	{
		int ind[4] = { 3, 3, 3, 3 };
		for (int i = 3; i >= 0; i--)
		{
			if (BOARD[i] != 0)
			{
				nBoard[ind[0]] = BOARD[i];
				ind[0] = ind[0] - 1;
			}
			if (BOARD[i + 4] != 0)
			{
				nBoard[ind[1] + 4] = BOARD[i + 4];
				ind[1] = ind[1] - 1;
			}
			if (BOARD[i + 8] != 0)
			{
				nBoard[ind[2] + 8] = BOARD[i + 8];
				ind[2] = ind[2] - 1;
			}
			if (BOARD[i + 12] != 0)
			{
				nBoard[ind[3] + 12] = BOARD[i + 12];
				ind[3] = ind[3] - 1;
			}
		}
	}
	bool changed = false;
	for (int i = 0; i < 16; i++)
	{
		if (BOARD[i] != nBoard[i])
		{
			changed = true;
		}
		BOARD[i] = nBoard[i];
	}
	return changed;
}

int boardMove(int *BOARD, int move)
{
	int score = 0;
	bool changed = boardTranslate(BOARD, move);
	if (move == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (BOARD[i] == BOARD[i + 4])
			{
				if (BOARD[i + 8] == BOARD[i + 12])
				{
					BOARD[i] = BOARD[i] * 2;
					BOARD[i + 4] = BOARD[i + 8] * 2;
					BOARD[i + 8] = 0;
					BOARD[i + 12] = 0;
					score = score + BOARD[i] + BOARD[i + 4];
				}
				else
				{
					BOARD[i] = BOARD[i] * 2;
					BOARD[i + 4] = BOARD[i + 8];
					BOARD[i + 8] = BOARD[i + 12];
					BOARD[i + 12] = 0;
					score = score + BOARD[i];
				}
			}
			else if (BOARD[i + 4] == BOARD[i + 8])
			{
				BOARD[i + 4] = BOARD[i + 4] * 2;
				BOARD[i + 8] = BOARD[i + 12];
				BOARD[i + 12] = 0;
				score = score + BOARD[i + 4];
			}
			else if (BOARD[i + 8] == BOARD[i + 12])
			{
				BOARD[i + 8] = BOARD[i + 8] * 2;
				BOARD[i + 12] = 0;
				score = score + BOARD[i + 8];
			}
		}
	}
	else if (move == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			if (BOARD[i + 12] == BOARD[i + 8])
			{
				if (BOARD[i + 4] == BOARD[i])
				{
					BOARD[i + 12] = BOARD[i + 12] * 2;
					BOARD[i + 8] = BOARD[i + 4] * 2;
					BOARD[i + 4] = 0;
					BOARD[i] = 0;
					score = score + BOARD[i + 8] + BOARD[i + 12];
				}
				else
				{
					BOARD[i + 12] = BOARD[i + 12] * 2;
					BOARD[i + 8] = BOARD[i + 4];
					BOARD[i + 4] = BOARD[i];
					BOARD[i] = 0;
					score = score + BOARD[i + 12];
				}
			}
			else if (BOARD[i + 8] == BOARD[i + 4])
			{
				BOARD[i + 8] = BOARD[i + 4] * 2;
				BOARD[i + 4] = BOARD[i];
				BOARD[i] = 0;
				score = score + BOARD[i + 8];
			}
			else if (BOARD[i + 4] == BOARD[i])
			{
				BOARD[i + 4] = BOARD[i] * 2;
				BOARD[i] = 0;
				score = score + BOARD[i + 4];
			}
		}
	}
	else if (move == 3)
	{
		for (int i = 0; i < 16; i = i + 4)
		{
			if (BOARD[i] == BOARD[i + 1])
			{
				if (BOARD[i + 2] == BOARD[i + 3])
				{
					BOARD[i] = BOARD[i] * 2;
					BOARD[i + 1] = BOARD[i + 2] * 2;
					BOARD[i + 2] = 0;
					BOARD[i + 3] = 0;
					score = score + BOARD[i] + BOARD[i + 1];
				}
				else
				{
					BOARD[i] = BOARD[i] * 2;
					BOARD[i + 1] = BOARD[i + 2];
					BOARD[i + 2] = BOARD[i + 3];
					BOARD[i + 3] = 0;
					score = score + BOARD[i];
				}
			}
			else if (BOARD[i + 1] == BOARD[i + 2])
			{
				BOARD[i + 1] = BOARD[i + 1] * 2;
				BOARD[i + 2] = BOARD[i + 3];
				BOARD[i + 3] = 0;
				score = score + BOARD[i + 1];
			}
			else if (BOARD[i + 2] == BOARD[i + 3])
			{
				BOARD[i + 2] = BOARD[i + 2] * 2;
				BOARD[i + 3] = 0;
				score = score + BOARD[i + 2];
			}
		}
	}
	else if (move == 4)
	{
		for (int i = 0; i < 16; i = i + 4)
		{
			if (BOARD[i + 3] == BOARD[i + 2])
			{
				if (BOARD[i + 1] == BOARD[i])
				{
					BOARD[i + 3] = BOARD[i + 3] * 2;
					BOARD[i + 2] = BOARD[i + 1] * 2;
					BOARD[i + 1] = 0;
					BOARD[i] = 0;
					score = score + BOARD[i + 2] + BOARD[i + 3];
				}
				else
				{
					BOARD[i + 3] = BOARD[i + 3] * 2;
					BOARD[i + 2] = BOARD[i + 1];
					BOARD[i + 1] = BOARD[i];
					BOARD[i] = 0;
					score = score + BOARD[i + 3];
				}
			}
			else if (BOARD[i + 2] == BOARD[i + 1])
			{
				BOARD[i + 2] = BOARD[i + 1] * 2;
				BOARD[i + 1] = BOARD[i];
				BOARD[i] = 0;
				score = score + BOARD[i + 2];
			}
			else if (BOARD[i + 1] == BOARD[i])
			{
				BOARD[i + 1] = BOARD[i] * 2;
				BOARD[i] = 0;
				score = score + BOARD[i + 1];
			}
		}
	}
	if (score == 0 && !changed)
	{
		score = -1;
	}
	return score;
}

void createTile(int *BOARD)
{
	int count_z = 0;
	for (int i = 0; i < 16; i++)
	{
		if (BOARD[i] == 0)
			count_z++;
	}
	if (count_z > 0)
	{
		if (count_z > 1)
		{
			int ind = 0;
			std::uniform_int_distribution<int> uni(1, count_z);
			auto random_integer = uni(rng);
			count_z = random_integer;
			for (int i = 0; i < 16; i++)
			{
				if (BOARD[i] == 0)
				{
					count_z--;
					if (count_z == 0)
					{
						ind = i;
						break;
					}
				}
			}
			random_integer = val_rand(rng);
			if (random_integer == 5)
				BOARD[ind] = 4;
			else
				BOARD[ind] = 2;
		}
		else
		{
			int ind = 0;
			for (int i = 0; i < 16; i++)
			{
				if (BOARD[i] == 0)
				{
					ind = i;
					break;
				}
			}
			auto random_integer = val_rand(rng);
			if (random_integer == 5)
				BOARD[ind] = 4;
			else
				BOARD[ind] = 2;
		}

	}
}



bool isGameOver(int *BOARD)
{
	for (int i = 0; i < 16; i++)
	{
		if (BOARD[i] == 0)
		{
			return false;
		}
		else
		{
			int c = i % 4;
			int r = i / 4;
			if (c < 3)
			{
				if (BOARD[i] == BOARD[i + 1])
					return false;
			}
			if (r < 3)
			{
				if (BOARD[i] == BOARD[i + 4])
					return false;
			}
		}
	}
	return true;
}

void initializeBoard(int *BOARD)
{
	for (int i = 0; i < 16; i++)
	{
		BOARD[i] = 0;
	}
	createTile(BOARD);
	createTile(BOARD);
}


void printBoard(int *BOARD)
{
	for (int i = 0; i < 16; i++)
	{
		if (i % 4 == 0)
			printf("\n");
		printf("%u\t", BOARD[i]);
	}
	printf("\n");
}