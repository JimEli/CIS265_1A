/*************************************************************************
* Title: (CIS265_1A) Tax Computation
* File: main.c
* Author: James Eli
* Date: 8/25/2017
*
* Write a program that asks a user to enter a dollars-and-cents amount,
* then displays the amount with 5% tax added:
* Enter an amount: 100.00
* With tax added: $105.00
*
* The basic functionality of the program is contained in the following 
* three lines: 
*   scanf("%7s", input);
*   sscanf(input, "%f", &amount)
*   printf("With tax added: $%0.2f\n", amount * TAX_MULTIPLIER);
* The remaing portion of the program simply deals with input validation.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options and/or Eclipse GCC 5.3.0.
*  (2) No attempt was made to reject values input in scientific notation.
*  (3) MSC program uses secure versions of scanf and sscanf. 
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   08/25/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constant definitions.
#define TAX_MULTIPLIER         1.05f    // Tax multiplier (float).
#define MIN_AMOUNT             0.0f     // Min input value (float).
#define MAX_AMOUNT             9999.99f // Max input value (float).
#define MAXIMUM_INPUT_ATTEMPTS 3        // Max acceptable number of user input attempts before failing.

// Program starts here.
int main(void) {
	char input[9];                         // Holds user input as string.
	float amount;                          // Converted string value of user input.
	int attempts = MAXIMUM_INPUT_ATTEMPTS; // Input attempt counter.

#ifdef __GNUC__
	// Required to make eclipse console output work properly.
	setvbuf(stdout, NULL, _IONBF, 0);
	fflush(stdout);
#endif

	assert(attempts > 0); // Assert attempts valid non-zero, positive number.

	// Attempt only so many inputs.
	while (attempts--) {
		// Prompt and grab user input.
		fputs("Enter an amount: ", stdout);
		if (!fgets(input, sizeof input, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(input, '\n')) {
			// input too long, eat remainder.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			// Catch special case of null input.
			if (strlen(input) <= 1)
				continue;

			// Attempt to convert from string to float, and validate.
#ifdef __GNUC__
			if (sscanf(input, "%f", &amount)) {
#elif _MSC_VER
			if (sscanf_s(input, "%f", &amount)) {
#endif
				if (amount >= MIN_AMOUNT && amount <= MAX_AMOUNT) {
					fprintf(stdout, "With tax added: $%0.2f\n", amount * TAX_MULTIPLIER);
					break; // Exit.
				}
				else
					fprintf(stdout, "Value entered is outside allowable range (%0.2f - %0.2f)\n", MIN_AMOUNT, MAX_AMOUNT);
			}
			else
				fputs("Invalid input.\n", stdout);
		}
	}
}

