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
#include <string.h>
#include <stdbool.h>


// Creating a struct to hold the flight information, including destination, date, and fare.
struct FlightInfo {
	char *destination;
	char *date;
	float flightFare;

};

// Creating a struct to hold the flight information and pointers to the next and previous flights in the list.
struct FlightNode {
	struct FlightInfo info;
	struct FlightNode *next;
	struct FlightNode *prev;
};

// Function prototypes
struct FlightNode* createFlightNode(struct FlightInfo flightInfo);
struct FlightInfo getFlightInfo();
void insertSortedFare(struct FlightNode** sortedHead, struct FlightNode* newNode, struct FlightNode** fareTail);
void insertSortedDest(struct FlightNode** sortedHead, struct FlightNode* newNode, struct FlightNode** destTail);
	struct FlightInfo getDestAndDate();
struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date);
float editFare(struct FlightNode* flightNode);
void deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail);
void PrintList(struct FlightNode* head);
void freeMemory(struct FlightNode* head);

int main(void) {
	struct FlightNode* fareHead = NULL;
	struct FlightNode* destHead = NULL;

	struct FlightNode* fareTail = NULL;
	struct FlightNode* destTail = NULL;
	
	while (1) {
		
		// Getting flight information from the user
		struct FlightInfo flightInfo = getFlightInfo();

		// Stop getting input if the user enters an invalid destination or date
		if (flightInfo.destination == NULL || flightInfo.date == NULL) {
			break;
		}

		// Creating new FlightNodes with the user input
		struct FlightNode* fareNode = createFlightNode(flightInfo);
		struct FlightNode* destNode = createFlightNode(flightInfo);
			
		// Inserting the new node into the sorted list based on fare
		insertSortedFare(&fareHead, fareNode, &fareTail);

		// Inserting the new node into the sorted list based on destination
		insertSortedDest(&destHead, destNode, &destTail);

		printf("\n");


	}
	
	// Traversing the fare-sorted and destination-sorted lists and printing the flight information
	PrintList(fareHead);
	printf("\n");
	PrintList(destHead);


	printf("\n");
	printf("Enter the destination and date of the flight you want to edit:\n");
	// Using getDestAndDate() to get a destination and date from the user
	struct FlightInfo findInfo = getDestAndDate();

	// Finding the flight in both lists based on user input
	struct FlightNode* destFoundFlight = findFlight(destHead, findInfo.destination, findInfo.date);
	struct FlightNode* fareFoundFlight = findFlight(fareHead, findInfo.destination, findInfo.date);

	if (destFoundFlight == NULL) {
		return 0;
	}

	printf("\n");

	// Prompting the user to edit the fare of the found flight
	float updatedFare = 0;
	updatedFare= editFare(destFoundFlight);

	// If the fare is unchanged, the user is informed and the function is returned without doing anything.
	if (updatedFare == destFoundFlight->info.flightFare) {
		printf("New fare is the same as the existing fare. No changes made.");
		return;
	}
	// If the fare is changed, the current flightNode is deleted, and a new node is created and inserted into the fare-sorted linked list
	else {

		// Updating the fare in the destination-sorted list
		destFoundFlight->info.flightFare = updatedFare;

		//Updating the fare in the fare-sorted list
		fareFoundFlight->info.flightFare = updatedFare;

		deleteNode(fareFoundFlight, &fareHead, &fareTail);

		insertSortedFare(&fareHead, fareFoundFlight, &fareTail);
		printf("Flight fare updated.\n");
		printf("\n");

	}

	// Traversing the fare-sorted and destination-sorted lists and printing the flight information
	PrintList(fareHead);
	printf("\n");
	PrintList(destHead);

	// freeing all allocated memory for the linked lists
	freeMemory(fareHead);
	freeMemory(destHead);
	return 0;
}

// METHOD : PrintList()
// DESCRIPTION: 
//      This function traverses a list based on the head pointer and prints the flight information.
// PARAMETERS:
//     struct FlightNode* head: A pointer to the head of the list
// RETURNS:
//		None.
void PrintList(struct FlightNode* head) {
	struct FlightNode* current = head;

	// Iterating through the list and printing the flight info for each node
	while (current != NULL) {
		printf("%-15s %-10s %-.2f\n", current->info.destination, current->info.date, current->info.flightFare);
		current = current->next;
	}
}

// METHOD : createFlightNode()
// DESCRIPTION: 
//      This function creates a new FlightNode struct, using info from a FlightInfo struct.
// PARAMETERS:
//     struct FlightInfo flightInfo: A struct containing user input for the flight information.
// RETURNS:
//		struct FlightNode* newNode : A struct containing flight information and pointers to the next and previous flights.
struct FlightNode* createFlightNode(struct FlightInfo flightInfo) {

	// Allocating memory for the new FlightNode
	struct FlightNode* newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));
	if (newNode == NULL) {
		printf("Memory allocation failed.\n");
		return NULL;
	}

	// Ensuring each node in list has its own unique copy of the flight information, instead of pointing to the same memory location.
	newNode->info.flightFare = flightInfo.flightFare;

	newNode->info.destination = malloc(strlen(flightInfo.destination) + 1);
	strcpy(newNode->info.destination, flightInfo.destination);

	newNode->info.date = malloc(strlen(flightInfo.date) + 1);
	strcpy(newNode->info.date, flightInfo.date);

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
		return inputInfo;
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
		return inputInfo;
	}

	// Storing the date input
	strcpy(inputInfo.date, buffer);



	// Asking the user for the FARE
	printf("Enter flight fare: \n");
	scanf("%f", &inputInfo.flightFare);

	// Clear the newline character 
	getchar(); 

	return inputInfo;

}

// METHOD : insertSortedFare()
// DESCRIPTION: 
//      This function inserts a new FlightNode into a sorted doubly linked list based on the flight fare.
// PARAMETERS:
//     struct FlightNode** sortedHead: A pointer to the head of the list
//     struct FlightNode* newNode: A pointer to the new node to be inserted
//	   struct FlightNode** fareTail: A pointer to the tail of the list
// RETURNS:
// 	   None.
void insertSortedFare(struct FlightNode** sortedHead, struct FlightNode* newNode, struct FlightNode** fareTail) {

	// If the sorted list is empty, the new node becomes the head
	if (*sortedHead == NULL) {

		// Update the head and tail pointer if the list was empty
		*sortedHead= newNode;
		*fareTail = newNode; 
		return;
	}

	// if the new node's fare is less than the head's fare, it is inserted at the beginning
	if (newNode->info.flightFare < (*sortedHead)->info.flightFare) {
		newNode->next = *sortedHead;
		(*sortedHead)->prev = newNode;
		*sortedHead = newNode;
		return;
	}
	else
	{
		// If the new node's fare is larger or equal to the head's fare, the list is traversed
		// to find the appropriate position
		struct FlightNode* current = *sortedHead;

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

		// Update the tail pointer if the new node is inserted at the end
		if (newNode->next == NULL) {
			*fareTail = newNode; 
		}
	}
}


// METHOD : insertSortedDest()
// DESCRIPTION: 
//      This function inserts a new FlightNode into a sorted doubly linked list based on the flight destination.
// PARAMETERS:
//     struct FlightNode** sortedHead: A pointer to the head of the list
//     struct FlightNode* newNode: A pointer to the new node to be inserted
//	   struct FlightNode** fareTail: A pointer to the tail of the list
// RETURNS:
//		None.
void insertSortedDest(struct FlightNode** sortedHead, struct FlightNode* newNode, struct FlightNode** destTail) {

	// If the sorted list is empty, the new node becomes the head
	if (*sortedHead == NULL) {
		// Update the head and tail pointer if the list was empty
		*sortedHead = newNode;
		*destTail = newNode;
		return;
	}


	// if the new node's destination is alphabetically lower than the head's destination, it is inserted at the beginning
	if(strcmp(newNode->info.destination, (*sortedHead)->info.destination) < 0) {
		newNode->next = *sortedHead;
		(*sortedHead)->prev = newNode;
		*sortedHead = newNode;
		return;
	}
	else
	{
		// If the new node's destination is alphabetically higher or equal to the head's destination,
		// the list is traversed to find the appropriate position
		struct FlightNode* current = *sortedHead;

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

		// Update the tail pointer if the new node is inserted at the end
		if (newNode->next == NULL) {
			*destTail = newNode;
		}
	}
}

// METHOD : getDestAndDate()
// DESCRIPTION: 
//      This function traverses asks the user for input only for flight destination and date, returning a flight info struct
//		with the information.
// PARAMETERS:
//     None.
// RETURNS:
//     struct FlightInfo inputInfo: A struct containing the user input for destination and date.
struct FlightInfo getDestAndDate() {
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
		inputInfo.destination = NULL;
		inputInfo.date = NULL;
		return inputInfo;
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
		inputInfo.destination = NULL;
		inputInfo.date = NULL;
		return inputInfo;
	}

	// Storing the date input
	strcpy(inputInfo.date, buffer);

	//Setting flight fare to 0 as it is not necessary for this function
	inputInfo.flightFare = 0.0;

	return inputInfo;


}

// METHOD : findFlight()
// DESCRIPTION: 
//      This function traverses a list based on the head pointer and returns a pointer to the FlightNode with 
//      the matching destination and date. If no match is found, NULL will be returned.
// PARAMETERS:
//     struct FlightNode* head: A pointer to the head of the list
//	   char *destination:  A string containing the destination to be searched for
//     char *date: A string containing the date to be searched for
// RETURNS:
// 	struct FlightNode* : A pointer to the FlightNode with the matching destination and date, or NULL if no match is found.
struct FlightNode* findFlight(struct FlightNode* head, char *destination, char *date) {

	// Traversing the list to find a flight with the specified destination and date
	struct FlightNode* current = head;
	while (current != NULL) {

		// If the destination and date match, the current node is returned
		if (strcmp(current->info.destination, destination) == 0 && strcmp(current->info.date, date) == 0) {
			return current;
		}
		// Otherwise the loop continues to the next node in the list
		else { 
			current = current->next; 
		}
		
	}

	printf("Flight not found.\n");
	// If a match can't be found, NULL is returned.
	return NULL;
	
}

// METHOD : editFare()
// DESCRIPTION: 
//      This function allows the user to edit the fare of a specific flight.
// PARAMETERS:
//     struct FlightNode* flightNode: A pointer to the flight node whose fare is to be edited
// RETURNS:
// 	   float newFare: The updated fare of the flight.
float editFare(struct FlightNode* flightNode) {

	// Printing the fare of the flight before editing
	printf("%-.2f\n", flightNode->info.flightFare);

	// Asking the user for the FARE
	printf("Enter new flight fare: \n");

	float newFare;
	scanf("%f", &newFare);

	// Clear the newline character 
	getchar();

	return newFare;
	
}

// METHOD : deleteNode()
// DESCRIPTION: 
//      This function deletes the input FlightNode from the linked list
// PARAMETERS:
//     struct FlightNode* node: A pointer to the node to be deleted
//	   struct FlightNode** head: A pointer to the head of the list
//     struct FlightNode** tail: A pointer to the tail of the list
// RETURNS:
//		None.
void deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail) {

	struct FlightNode* current = *head;
	bool deleted = false;
	

	
	if (node == NULL) {
		return;
	}
	while (deleted != true) {
		// Deleting the head
		if (node == *head) {
			*head = node->next;
			if (*head != NULL) {
				(*head)->prev = NULL;
			}
			deleted = true;
			break;
		}
		else {
			node->prev->next = node->next;
			deleted = true;
			break;
		}

		// Deleting the tail 
		if (node == *tail) {
			*tail = node->prev;
			if (*tail != NULL) {
				(*tail)->next = NULL;
			}
			deleted = true;
			break;
		}
		else {
			node->next->prev = node->prev;
			deleted = true;
			break;
		}

	}

	// Detaching node completely
	node->next = NULL;
	node->prev = NULL;
}


// METHOD : freeMemory()
// DESCRIPTION: 
//      This function frees all the memory allocated in the doublylinked list
// PARAMETERS:
//	   struct FlightNode* head: A pointer to the head of the list
// RETURNS:
//		None.
void freeMemory(struct FlightNode* head) {

	//Clearing the memory for FlightNode structs
	struct FlightNode* currentNode = head;
	//struct FlightInfo* currentInfo;
	struct FlightNode* tempNode;

	while (currentNode != NULL) {
		tempNode = currentNode->next;
		
		// Clearing all allocated memory for the FlightInfo struct within the FlightNode
		if (currentNode->info.destination != NULL) {
			free(currentNode->info.destination);
		}

		if (currentNode->info.date != NULL) {
			free(currentNode->info.date);
		}

		// freeing the current node
		free(currentNode);

		// Moving to the next node
		currentNode = tempNode;
	}
}

