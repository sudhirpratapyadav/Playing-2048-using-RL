#include "gamePlay.h"
#include "float.h"
#include <stdio.h>

#define ROW_LENGTH 104976
const int tuple1[17] = { 0, 4, 8, 12, 0, 1, 2, 3, 0, 1, 2, 4, 5, 6, 8, 9, 10 };
const int tuple2[17] = { 1, 5, 9, 13, 4, 5, 6, 7, 1, 2, 3, 5, 6, 7, 9, 10, 11 };
const int tuple3[17] = { 2, 6, 10, 14, 8, 9, 10, 11, 5, 6, 7, 9, 10, 11, 13, 14, 15 };
const int tuple4[18] = { 3, 7, 11, 15, 12, 13, 14, 15, 4, 5, 6, 8, 9, 10, 12, 13, 14 };

double getValueOfBoard(int *BOARD, double *WEIGHTS)
{
	int t_BOARD[16];
	for (int i = 0; i < 16; i++)
	{
		switch (BOARD[i])
		{
		case 0: t_BOARD[i] = 0;
			break;
		case 2: t_BOARD[i] = 1;
			break;
		case 4: t_BOARD[i] = 2;
			break;
		case 8: t_BOARD[i] = 3;
			break;
		case 16: t_BOARD[i] = 4;
			break;
		case 32: t_BOARD[i] = 5;
			break;
		case 64: t_BOARD[i] = 6;
			break;
		case 128: t_BOARD[i] = 7;
			break;
		case 256: t_BOARD[i] = 8;
			break;
		case 512: t_BOARD[i] = 9;
			break;
		case 1024: t_BOARD[i] = 10;
			break;
		case 2048: t_BOARD[i] = 11;
			break;
		case 4096: t_BOARD[i] = 12;
			break;
		case 8192: t_BOARD[i] = 13;
			break;
		case 16384: t_BOARD[i] = 14;
			break;
		case 32768: t_BOARD[i] = 15;
			break;
		case 65536: t_BOARD[i] = 16;
			break;
		case 131072: t_BOARD[i] = 17;
			break;
		}
	}
	
	int ind = 0;
	double val = 0;
	for (int i = 0; i < 17; i++)
	{
		ind = ROW_LENGTH*i + t_BOARD[tuple1[i]] * 1 + t_BOARD[tuple2[i]] * 15 + t_BOARD[tuple3[i]] * 225 + t_BOARD[tuple4[i]] * 3375;
		val = val + WEIGHTS[ind];
	}
	return val;
}

void updateWeights(int *BOARD, double del_weight, double *WEIGHTS)
{
	int t_BOARD[16];
	for (int i = 0; i < 16; i++)
	{
		switch (BOARD[i])
		{
		case 0: t_BOARD[i] = 0;
			break;
		case 2: t_BOARD[i] = 1;
			break;
		case 4: t_BOARD[i] = 2;
			break;
		case 8: t_BOARD[i] = 3;
			break;
		case 16: t_BOARD[i] = 4;
			break;
		case 32: t_BOARD[i] = 5;
			break;
		case 64: t_BOARD[i] = 6;
			break;
		case 128: t_BOARD[i] = 7;
			break;
		case 256: t_BOARD[i] = 8;
			break;
		case 512: t_BOARD[i] = 9;
			break;
		case 1024: t_BOARD[i] = 10;
			break;
		case 2048: t_BOARD[i] = 11;
			break;
		case 4096: t_BOARD[i] = 12;
			break;
		case 8192: t_BOARD[i] = 13;
			break;
		case 16384: t_BOARD[i] = 14;
			break;
		case 32768: t_BOARD[i] = 15;
			break;
		case 65536: t_BOARD[i] = 16;
			break;
		case 131072: t_BOARD[i] = 17;
			break;
		}
	}
	int ind = 0;
	for (int i = 0; i < 17; i++)
	{
		ind = ROW_LENGTH*i + t_BOARD[tuple1[i]] * 1 + t_BOARD[tuple2[i]] * 15 + t_BOARD[tuple3[i]] * 225 + t_BOARD[tuple4[i]] * 3375;
		WEIGHTS[ind] = WEIGHTS[ind] + del_weight;
	}
}

void learnEvaluation(int *BOARD, int reward, int *BOARD_NEW_STATE, double *WEIGHTS)
{
	double alpha = 0.005;
	double del_weight = alpha*(reward + getValueOfBoard(BOARD_NEW_STATE, WEIGHTS) - getValueOfBoard(BOARD, WEIGHTS));
	updateWeights(BOARD, del_weight, WEIGHTS);
}

unsigned int getBestMove(int *BOARD, double *WEIGHTS)
{
	int t_BOARD[16] = {};
	double exp[4] = {};
	for (int m = 0; m < 4; m++)
	{
		for (int k = 0; k < 16; k++)
		{
			t_BOARD[k] = BOARD[k];
		}
		int sc = boardMove(t_BOARD, m + 1);

		bool moved = false;
		for (int k = 0; k < 16; k++)
		{
			if (BOARD[k] != t_BOARD[k])
			{
				moved = true;
				break;
			}
		}
		if (!moved)
		{
			exp[m] = -DBL_MAX;

		}
		else
		{
			int free_n = 0;

			exp[m] = 0;
			for (int i = 0; i < 16; i++)
			{
				if (t_BOARD[i] == 0)
				{
					t_BOARD[i] = 2;
					double v1 = getValueOfBoard(t_BOARD, WEIGHTS);
					exp[m] = exp[m] + 0.9*v1;
					//printf("i%d", i);

					t_BOARD[i] = 4;
					double v2 = getValueOfBoard(t_BOARD, WEIGHTS);
					exp[m] = exp[m] + 0.1*v2;
					t_BOARD[i] = 0;
					free_n++;

					/*
					if (m==3)
					printf("%f\t%f\t",v1,v2);
					*/
				}
			}

			//if (m==3)
			//printf("\n%d\t%f\n",free_n,exp[m]);

			exp[m] = exp[m] / free_n + sc;
		}

	}
	
	int best_move = 1;
	double max_exp = exp[0];
	for (int i = 1; i < 4; i++)
	{
		if (exp[i] >= max_exp)
		{
			max_exp = exp[i];
			best_move = i + 1;
		}
	}
	return best_move;
}