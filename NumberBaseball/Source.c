#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#define LINESIZE (1024)
#define NUMBER_OF_GUESSES (3)
#define STRIKES_TO_END (3)

int numStrikes;
int numBalls;
int numOuts;
/* results are for feedback to the user after each inning */
int resultStrikes;
int resultBalls;
int resultOuts;
/* numInnings is the total number of innings */
int numInnings;
/* currentInning is the inning we are currently on. Used to accurately determine strikes. */
int currentInning;

int userNumbers[NUMBER_OF_GUESSES];
int randomNumbers[NUMBER_OF_GUESSES];


void Init() {
	currentInning = 0;
	numInnings = 0;
	numStrikes = 0;
	numBalls = 0;
	numOuts = 0;
	resultStrikes = 0;
	resultBalls = 0;
	resultOuts = 0;
}

void evaluateGuesses() {
	size_t i;
	size_t j;

	for (i = 0; i < NUMBER_OF_GUESSES; i++)
	{
		if (userNumbers[i] == randomNumbers[i])
		{
			numStrikes++;
			resultStrikes++;
			numInnings++;
		}
		else
		{
			for (j = 0; j < NUMBER_OF_GUESSES; j++)
			{
				if (userNumbers[i] == randomNumbers[j])
				{
					numBalls++;
					resultBalls++;
					numInnings++;
					break;
				}
			}
		}

		if (currentInning == numInnings)
		{
			numOuts++;
			resultOuts++;
			numInnings++;
		}
		currentInning++;
	}
}

void Update() {
	char line[LINESIZE];

	resultStrikes = 0;
	resultBalls = 0;
	resultOuts = 0;

	while (1) 
	{
		printf("Please enter your %d numbers:\n", NUMBER_OF_GUESSES);
		if (!fgets(line, LINESIZE, stdin)) /* if we fail to read a line */
		{
			clearerr(stdin);
			break;
		}
		if (sscanf_s(line, "%d %d %d", &userNumbers[0], &userNumbers[1], &userNumbers[2]) == NUMBER_OF_GUESSES && (userNumbers[0] != userNumbers[1] && userNumbers[0] != userNumbers[2] && userNumbers[1] != userNumbers[2]))
		{
			/* Use current time as seed for random generator */
			srand((unsigned int) time(0));
			/* Generates random number between 0 and 9 */
			
			do
			{
				randomNumbers[0] = rand() % 10;
				randomNumbers[1] = rand() % 10;
				randomNumbers[2] = rand() % 10;
			} while (randomNumbers[1] == randomNumbers[0] || randomNumbers[2] == randomNumbers[0] || randomNumbers[2] == randomNumbers[1]);
			
			evaluateGuesses();

			break;
		}
		else 
		{
			fprintf(stderr, "You must enter %d unique numbers between 0 and 9, seperated by a space.\n", NUMBER_OF_GUESSES);
		}
	}
}

void Render() {
	printf("CPU's numbers:\t%d %d %d\n", randomNumbers[0], randomNumbers[1], randomNumbers[2]);
	printf("Your numbers:\t%d %d %d\n", userNumbers[0], userNumbers[1], userNumbers[2]);
	printf("Result:\t%d Strike, %d Ball, %d Out\n", resultStrikes, resultBalls, resultOuts);
	printf("Total:\t%d Strike, %d Ball, %d Out\n", numStrikes, numBalls, numOuts);
	if (numStrikes >= STRIKES_TO_END)
	{
		printf("You've gotten %d strikes. You win! \n", STRIKES_TO_END);

	}
	
}

void Release() {
	getchar();
}

int main(void) {
	Init();
	while (1) 
	{
		Update();
		Render();
		if (numStrikes == STRIKES_TO_END)
		{
			break;
		}
	}
	Release();
	return 0;
}
