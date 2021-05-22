double getValueOfBoard(int *BOARD, double *WEIGHTS);
void updateWeights(int *BOARD, double del_weight, double *WEIGHTS);
void learnEvaluation(int *BOARD, int reward, int *BOARD_NEW_STATE, double *WEIGHTS);
unsigned int getBestMove(int *BOARD, double *WEIGHTS);