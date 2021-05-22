#include <stdio.h>
#include <stdlib.h>
#include "gamePlay.h"
#include "RL.h"
#include <ctime>

#define NUM_WEIGHTS 1784592
#define ROW_LENGTH 50625
#define NUM_GAMES 200000

int main()
{
	int BOARD[16] = {};
	int t_BOARD[16] = {};

	double *WEIGHTS;
	WEIGHTS = (double *)malloc(NUM_WEIGHTS * sizeof(double));




	for (int i = 0; i <NUM_WEIGHTS; i++)
	{
		WEIGHTS[i] = 0;
	}



	printf("Starting to play games \n");
	clock_t startTime = clock();

	int max_tl = 0;
	for (int numg = 0; numg < NUM_GAMES; numg++)
	{
		initializeBoard(BOARD);
		int score = 0;
		while (!isGameOver(BOARD))
		{
			for (int k = 0; k < 16; k++)
			{
				t_BOARD[k] = BOARD[k];
			}
			int move = getBestMove(BOARD, WEIGHTS);
			int sc = boardMove(BOARD, move);

			//Adding New  Tile
			bool moved = false;
			for (int k = 0; k < 16; k++)
			{
				if (BOARD[k] != t_BOARD[k])
				{
					moved = true;
					break;
				}
			}
			if (moved)
			{
				score = score + sc;
				createTile(BOARD);
			}

			//learning Value Fuction
			learnEvaluation(t_BOARD, sc, BOARD, WEIGHTS);
		}
		for (int k = 0; k < 16; k++)
		{
			if (BOARD[k]>max_tl)
			{
				max_tl = BOARD[k];
			}
		}

		if (numg % 1000 == 0)
		{
			printf("%d\t%d\n", numg, max_tl);

			double su = 0;
			double mx = 0;
			double mi = 0;
			int mx_i = 0;
			int max_i = 0;
			int min_i = 0;
			for (int i = 0; i <NUM_WEIGHTS; i++)
			{
				su = su + WEIGHTS[i];
				if (WEIGHTS[i]>0 && (i % ROW_LENGTH>mx_i % ROW_LENGTH))
				{
					mx_i = i;
				}
				if (WEIGHTS[i]>mx)
				{
					mx = WEIGHTS[i];
					max_i = i;
				}
				if (WEIGHTS[i] < mi)
				{
					mi = WEIGHTS[i];
					min_i = i;
				}
			}
			printf("%f\t%f\t%d\t%d\t%d\t%d\t%d", mx, mi, max_i, max_i % ROW_LENGTH, min_i, min_i % ROW_LENGTH, mx_i % ROW_LENGTH);
			printf("\nsum : %f\n\n", su);


		}
	}
	double end1 = double(clock() - startTime) / (double)CLOCKS_PER_SEC;


	double mx = 0;
	double mi = 0;
	int mx_i = 0;
	for (int i = 0; i <NUM_WEIGHTS; i++)
	{
		if (WEIGHTS[i]>0 && (i % ROW_LENGTH>mx_i % ROW_LENGTH))
		{
			mx_i = i;
		}
		if (WEIGHTS[i]>mx)
		{
			mx = WEIGHTS[i];
		}
		if (WEIGHTS[i] < mi)
		{
			mi = WEIGHTS[i];
		}
	}
	printf("\n %f\t%f\t%d", mx, mi, mx_i);
	printf("\n%f\n%u\n", end1, max_tl);

}
