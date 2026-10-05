/*
FILE          : Assignment1.c
PROJECT       : SENG1050 - A01 – SORTED DOUBLY-LINKED LISTS
PROGRAMMER    : Vicky Nyangoma Kamanyire
FIRST VERSION : 2026 - 10 - 05
DESCRIPTION:  This program ...
*/

#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>

struct FlightInfo {
	char *destination;
	char *date;
	float flightFare;

};

int main(void) {

	return 0;
}


// METHOD : getFlightInfo()
// DESCRIPTION: 
//      This method receives the flight information from the user, returning a struct containing
//		the flight destination, date, and fare.
// PARAMETERS:
//     None.
// RETURNS:
//		struct Flightinfo : A struct containing the user input for destination, date and fare.
struct FlightInfo getFlightInfo() {
	
	struct FlightInfo inputInfo;

	// Creating buffer to receive input
	char buffer[100];

	// Asking the user for the DESTINATION
	printf("Enter flight destination: \n");
	fgets(buffer, sizeof(buffer), stdin);

	// Removing the newline character from the input
	buffer[strcspn(buffer, "\n")] = '\0';

	// Ensuring the string is 15 characters long
	buffer[14] = '\0'; 

	// Allocating memory for the destination string
	inputInfo.destination = malloc(strlen(buffer) + 1);
	if (inputInfo.destination == NULL) {
		printf("Memory allocation failed.\n");
		return;
	}

	// Storing the destination input
	strcpy(inputInfo.destination, buffer);



	// Asking the user for the DATE
	printf("Enter flight date (DDMMYYYY): \n");
	fgets(buffer, sizeof(buffer), stdin);

	// Removing the newline character from the input
	buffer[strcspn(buffer, "\n")] = '\0';

	// Ensuring the string is 9 characters long
	buffer[8] = '\0';

	// Allocating memory for the date string
	inputInfo.date = malloc(strlen(buffer) + 1);
	if (inputInfo.date == NULL) {
		printf("Memory allocation failed.\n");
		return;
	}

	// Storing the date input
	strcpy(inputInfo.date, buffer);



	// Asking the user for the FARE
	printf("Enter flight fare: \n");
	scanf("%f", &inputInfo.flightFare);

	return inputInfo;

}