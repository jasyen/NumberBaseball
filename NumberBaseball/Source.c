#include <stdio.h>
#include <stdlib.h> 
#include<time.h> 

#define LINESIZE 1024
#define NUMBER_OF_GUESSES 3
#define STRIKES_TO_END 3

int numStrikes;
int numBalls;
int numOuts;
int resultStrikes;
int resultBalls;
int resultOuts;
int n1;
int n2;
int n3;
int random1;
int random2;
int random3;

void Init() {
	numStrikes = 0;
	numBalls = 0;
	numOuts = 0;
	resultStrikes = 0;
	resultBalls = 0;
	resultOuts = 0;
	printf("Init\n");
}

void Update() {
	char line[LINESIZE];

	resultStrikes = 0;
	resultBalls = 0;
	resultOuts = 0;

	while (1) {
		printf("Please enter your %d numbers:\n", NUMBER_OF_GUESSES);
		if (!fgets(line, LINESIZE, stdin)) /* if we fail to read a line */
		{
			clearerr(stdin);
			break;
		}
		if (sscanf_s(line, "%d %d %d", &n1, &n2, &n3) == NUMBER_OF_GUESSES && (n1 != n2 && n1 != n3 && n2 != n3))
		{
			/* Use current time as seed for random generator */
			srand(time(0));
			/* Generates random number between 0 and 9 */
			random1 = rand() % 10;
			do
			{
				random2 = rand() % 10;
			} while (random2 == random1);
			do
			{
				random3 = rand() % 10;
			} while (random3 == random1 || random3 == random2);
			
			if (n1 == random1)
			{
				numStrikes++;
				resultStrikes++;
			}
			else if (n1 == random2 || n1 == random3)
			{
				numBalls++;
				resultBalls++;
			}
			else
			{
				numOuts++;
				resultOuts++;
			}

			if (n2 == random2)
			{
				numStrikes++;
				resultStrikes++;
			}
			else if (n2 == random1 || n2 == random3)
			{
				numBalls++;
				resultBalls++;
			}
			else
			{
				numOuts++;
				resultOuts++;
			}

			if (n3 == random3)
			{
				numStrikes++;
				resultStrikes++;
			}
			else if (n3 == random1 || n3 == random2)
			{
				numBalls++;
				resultBalls++;
			}
			else
			{
				numOuts++;
				resultOuts++;
			}
			
			break;
		}
		else 
		{
			fprintf(stderr, "You must enter %d unique numbers between 0 and 9, seperated by a space.\n", NUMBER_OF_GUESSES);
		}
	}
}

void Render() {
	printf("CPU's numbers:\t%d %d %d\n", random1, random2, random3);
	printf("Your numbers:\t%d %d %d\n", n1, n2, n3);
	printf("Result:\t%d Strike, %d Ball, %d Out\n", resultStrikes, resultBalls, resultOuts);
	printf("Total:\t%d Strike, %d Ball, %d Out\n", numStrikes, numBalls, numOuts);
	if (numStrikes == STRIKES_TO_END)
	{
		printf("You've gotten %d strikes. You win! \nEnding game...\n", STRIKES_TO_END);

	}
	
}

void Release() {
	printf("Release\nPress enter to exit...");
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