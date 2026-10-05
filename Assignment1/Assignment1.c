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

struct FlightNode {
	struct FlightInfo info;
	struct FlightNode *next;
	struct FlightNode *prev;
};

int main(void) {


	return 0;
}

// METHOD : createFlightNode()
// DESCRIPTION: 
//      This function creates a new FlightNode struct, using info from a FlightInfo struct.
// PARAMETERS:
//     struct FlightInfo flightInfo: A struct containing user input for the flight information.
// RETURNS:
//		struct FlightNode* newNode : A struct containing flight information and pointers to the next and previous flights.
struct FlightNode* createFlightNode(struct FlightInfo flightInfo) {

	struct FlightNode* newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));
	if (newNode == NULL) {
		printf("Memory allocation failed.\n");
		return NULL;
	}
	newNode->info = flightInfo;
	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode;
};


// METHOD : getFlightInfo()
// DESCRIPTION: 
//      This function receives the flight information from the user, returning a struct containing
//		the flight destination, date, and fare.
// PARAMETERS:
//     None.
// RETURNS:
//		struct Flightinfo inputInfo: A struct containing the user input for destination, date and fare.
struct FlightInfo getFlightInfo() {
	
	struct FlightInfo inputInfo;

	// Creating buffer to receive input
	char buffer[100];

	// Asking the user for the DESTINATION
	printf("Enter flight destination: \n");
	fgets(buffer, sizeof(buffer), stdin);

	// Removing the newline character from the input
	buffer[strcspn(buffer, "\n")] = '\0';

	// Stop getting input if the user enters an invalid destination
	if (strcmp(buffer, ".") == 0) {
		inputInfo.destination = NULL;
		return inputInfo;
	}

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

	// Stop getting input if the user enters an invalid date
	if (strcmp(buffer, ".") == 0) {
		inputInfo.date = NULL;
		return inputInfo;
	}

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

// METHOD : insertSortedFare()
// DESCRIPTION: 
//      This function inserts a new FlightNode into a sorted doubly linked list based on the flight fare.
// PARAMETERS:
//     struct FlightNode* sortedHead: A pointer to the head of the list
//     struct FlightNode* newNode: A pointer to the new node to be inserted
// RETURNS:
//		struct FlightNode* sortedHead: A pointer to the head of the sorted list after insertion
struct FlightNode* insertSortedFare(struct FlightNode* sortedHead, struct FlightNode* newNode) {

	// If the sorted list is empty, the new node becomes the head
	if (sortedHead == NULL) {
		return newNode;
	}

	// if the new node's fare is less than the head's fare, it is inserted at the beginning
	if (newNode->info.flightFare < sortedHead->info.flightFare) {
		newNode->next = sortedHead;
		sortedHead->prev = newNode;
		return newNode;
	}
	else
	{
		// If the new node's fare is larger or equal to the head's fare, the list is traversed
		// to find the appropriate position
		struct FlightNode* current = sortedHead;

		while (current->next != NULL && current->next->info.flightFare <= newNode->info.flightFare) {
			current = current->next;
		}

		// Inserting the new node
		newNode->next = current->next;
		newNode->prev = current;

		// If the new node was not inserted at the end, the pointer of the next node is updated to point back to the new node
		if (current->next != NULL) {
			current->next->prev = newNode;
		}

		// Updating the current node's next pointer to point to the new node
		current->next = newNode;
	}

	return sortedHead;
}


// METHOD : insertSortedDest()
// DESCRIPTION: 
//      This function inserts a new FlightNode into a sorted doubly linked list based on the flight destination.
// PARAMETERS:
//     struct FlightNode* sortedHead: A pointer to the head of the list
//     struct FlightNode* newNode: A pointer to the new node to be inserted
// RETURNS:
//		struct FlightNode* sortedHead: A pointer to the head of the sorted list after insertion
struct FlightNode* insertSortedDest(struct FlightNode* sortedHead, struct FlightNode* newNode) {

	// If the sorted list is empty, the new node becomes the head
	if (sortedHead == NULL) {
		return newNode;
	}


	// if the new node's destination is alphabetically lower than the head's destination, it is inserted at the beginning
	if(strcmp(newNode->info.destination, sortedHead->info.destination) < 0) {
		newNode->next = sortedHead;
		sortedHead->prev = newNode;
		return newNode;
	}
	else
	{
		// If the new node's destination is alphabetically higher or equal to the head's destination,
		// the list is traversed to find the appropriate position
		struct FlightNode* current = sortedHead;

		while (current->next != NULL && strcmp(current->next->info.destination, newNode->info.destination) <= 0) {
			current = current->next;
		}

		// Inserting the new node
		newNode->next = current->next;
		newNode->prev = current;

		// If the new node was not inserted at the end, the pointer of the next node is updated to point back to the new node
		if (current->next != NULL) {
			current->next->prev = newNode;
		}

		// Updating the current node's next pointer to point to the new node
		current->next = newNode;
	}

	return sortedHead;
}
