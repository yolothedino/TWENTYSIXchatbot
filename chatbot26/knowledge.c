/*
 * ICT1002 (C Language) Group Project, AY19 Trimester 1.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * knowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */
#define _CRT_SECURE_NO_WARNINGS 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

typedef struct node {
	char entity[MAX_ENTITY];
	char response[MAX_RESPONSE];
	struct node* next;
} item;

item* whenheader = NULL;
item* whereheader = NULL;
item* whoheader = NULL;
item* whatheader = NULL;
item* whyheader = NULL;
item* howheader = NULL;


//checks if the item exist in the link list
item* checkifexist(char* entity, item* head, char* response)
{
	item *cursor = head;
	item *found = NULL;
	while (cursor != NULL) {
		int result = strcmp(cursor->entity, entity);
		if (result == 0) {
			strcpy(cursor->response, response);
			found = cursor;
			break;
		}
		//Go to the next item in list
		cursor = cursor->next;
	}
	return found;
}
item* create(char* entity, item* next, char* response)
{
	//make a new node
	item* new_node = (item*)malloc(sizeof(item));
	//checks if the new node is make if not it be null
	if (new_node == NULL)
	{
		printf("Error creating a new node.\n");
		//to end the program if it fails to make a node
		exit(0);
	}
	//copy the entered string into the new node
	strcpy(new_node->entity, entity);
	//sets the node to point to the next one in this case Null
	strcpy(new_node->response, response);
	new_node->next = NULL;
	return new_node;
}
//makes the first node of the list
item* firstnode(item* head, char* data, char* response)
{
	//make a node for the list
	item* new_node = create(data, head, response);
	//set it as the head of the list
	head = new_node;
	return head;
}
item* append(item* head, char* data, char* response)
{
	// create the head of the link list if no head is found
	if (head == NULL) {
		head = firstnode(head, data, response);
		return head;
	}
	/* go to the last node */
	item* test = checkifexist(data, head, response);
	if (test == NULL) {
		item* cursor = head;
		while (cursor->next != NULL)
			cursor = cursor->next;
		/* create a new node */
		item* new_node = create(data, NULL, response);
		//sets the current node to point to the next one on the list
		cursor->next = new_node;
	}
	return head;
}
// find if there is a response for the given intent and entity
item* findinlinkedlist(item* listhead, const char* entity, int n)
{
	item* temp = listhead;
	//check if list is empty
	if (temp == NULL)
	{
		return NULL;
	}
	else
	{
		while (temp->next != NULL)
		{
			// if the entity matches return the expected response
			if (compare_token(entity, temp->entity) == 0)
			{
				item* returnvalue = (item*)malloc(sizeof(item));
				memcpy(returnvalue->entity, temp->entity, MAX_ENTITY);
				memcpy(returnvalue->response, temp->response, n);
				return returnvalue;
			}
			else
			{
				temp = temp->next;
			}
		}
		// check the last node
		if (temp->next == NULL)
		{
			if (compare_token(entity, temp->entity) == 0)
			{
				item* returnvalue = (item*)malloc(sizeof(item));
				memcpy(returnvalue->entity, temp->entity, MAX_ENTITY);
				memcpy(returnvalue->response, temp->response, n);
				return returnvalue;
			}
			else
			{
				//The node is not found. Returns NULL.
				return NULL;
			}
		}
	}
}
// create a new node
item* createnewnode(const char* entity, const char* response)
{
	item* new_node = (item*)malloc(sizeof(item));
	strcpy(new_node->entity, entity);
	strcpy(new_node->response, response);
	new_node->next = NULL;
	return new_node;
}
// Add items into the node
item* insertnode(item* listhead, item* newnode)
{
	// check if first node empty
	if (listhead == NULL)
	{
		return newnode;
	}
	// if there is a 2nd node
	else if (listhead->next != NULL)
	{
		item* temp = listhead;
		while (temp->next != NULL)
		{
			if (strcmp(temp->entity, newnode->entity) == 0)
			{
				strcpy(temp->response, newnode->response);
				return listhead;
			}
			else
			{
				newnode->next = listhead;
				return newnode;
			}
			temp = temp->next;
		}
	}
	// if theres 2nd node null
	else if (listhead->next == NULL)
	{
		// if the entities are the same replace head response with new response
		if (strcmp((listhead->entity), newnode->entity) == 0)
		{
			return newnode;
		}
		else
		{
			listhead->next = newnode;
			newnode->next = NULL;
			return listhead;
		}
	}
}
// to print the response of the selected linked list
void printresponse(const char* intent, const char* entity, char* response, int n)
{
	item* temp = NULL;
	// compare to check intent
	if (compare_token(intent, "what") == 0)
	{
		// temp will be the node that is holding the node of the matched answer. If null means node not found.
		temp = findinlinkedlist(whatheader, entity, n);
		if ((temp->response)[strlen(temp->response) - 1] == '\n')
		{
			//strip \n from response
			temp->response[strlen(temp->response) - 1] = '\0';
		}
		//return response buffer with the response
		snprintf(response, n, "%s", temp->response);
	}
	else if (compare_token(intent, "where") == 0)
	{
		temp = findinlinkedlist(whereheader, entity, n);
		if ((temp->response)[strlen(temp->response) - 1] == '\n')
		{
			temp->response[strlen(temp->response) - 1] = '\0';
		}
		snprintf(response, n, "%s", temp->response);
	}
	else if (compare_token(intent, "who") == 0)
	{
		temp = findinlinkedlist(whoheader, entity, n);
		if ((temp->response)[strlen(temp->response) - 1] == '\n')
		{
			temp->response[strlen(temp->response) - 1] = '\0';
		}
		snprintf(response, n, "%s", temp->response);
	}
}
/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {

	/* to be implemented*/
	item* temp = NULL;
	// compare to check intent
	if (compare_token(intent, "when") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through what linked list
			temp = findinlinkedlist(whenheader, entity, n);
		}
	}
	else if (compare_token(intent, "where") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through where linked list
			temp = findinlinkedlist(whereheader, entity, n);
		}
	}
	else if (compare_token(intent, "who") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(whoheader, entity, n);
		}
	}
	else if (compare_token(intent, "what") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(whatheader, entity, n);
		}
	}
	else if (compare_token(intent, "why") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(whyheader, entity, n);
		}
	}
	else if (compare_token(intent, "how") == 0)
	{
		if (entity == NULL)
		{
			return KB_INVALID;
		}
		else
		{
			//loop through who linked list
			temp = findinlinkedlist(howheader, entity, n);
		}
	}
	else
	{
		// ans is invalid
		return KB_INVALID;
	}
	// if temp is still NULL after the checks, then it is not found in the knowledge List
	if (temp == NULL)
	{
		// ans is not found
		return KB_NOTFOUND;
	}
	else
	{
		//ans is found
		return KB_OK;
	}
}
/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {
	
	/* to be implemented */
	// compare to check intent
	if (compare_token(intent, "when") == 0)
	{
		item* newnode = createnewnode(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whenheader = insertnode(whenheader, newnode);
			return KB_OK;
		}
	}
	else if (compare_token(intent, "where") == 0)
	{
		item* newnode = createnewnode(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whereheader = insertnode(whereheader, newnode);
			return KB_OK;
		}
	}
	else if (compare_token(intent, "who") == 0)
	{
		item* newnode = createnewnode(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whoheader = insertnode(whoheader, newnode);
			return KB_OK;
		}
	}
	else if (compare_token(intent, "what") == 0)
	{
		item* newnode = createnewnode(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whatheader = insertnode(whatheader, newnode);
			return KB_OK;
		}
	}
	else if (compare_token(intent, "why") == 0)
	{
		item* newnode = createnewnode(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			whyheader = insertnode(whyheader, newnode);
			return KB_OK;
		}
	}
	else if (compare_token(intent, "how") == 0)
	{
		item* newnode = createnewnode(entity, response);
		// check if newnode is null then return error
		if (newnode == NULL)
		{
			return KB_NOMEM;
		}
		else
		{
			howheader = insertnode(howheader, newnode);
			return KB_OK;
		}
	}
	else
	{
		// if when,where,who,what,why and how are not met, return invalid.
		return KB_INVALID;
	}
}

/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE* f) {

	/* to be implemented */
}
		
/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	
	/* to be implemented */
	item* tmp;
	//emptys and free the list from memory
	/*
	int* list[] = { whenheader,whereheader,whoheader,whatheader,whyheader,howheader };
	list[0] = whenheader;
	list[1] = whereheader;
	list[2] = whoheader;
	list[3] = whatheader;
	list[4] = whyheader;
	list[5] = howheader;
	for (int i = 0; i < (sizeof(list) /sizeof(list[0])); i++) {
		printf("%d) Address: %s\n", i, list[0]);
		for (int ii = 0; ii < list[i]; ii++) {
			tmp = list[i]->next;
			free(list[i]);
			list[i] = tmp;
		}
	}
	*/
	
	while (whenheader != NULL)
	{
		tmp = whenheader->next;
		free(whenheader);
		whenheader = tmp;
	}
	while (whereheader != NULL)
	{
		tmp = whereheader->next;
		free(whereheader);
		whereheader = tmp;
	}
	while (whoheader != NULL)
	{
		tmp = whoheader->next;
		free(whoheader);
		whoheader = tmp;
	}
	while (whatheader != NULL)
	{
		tmp = whatheader->next;
		free(whatheader);
		whatheader = tmp;
	}
	while (whyheader != NULL)
	{
		tmp = whyheader->next;
		free(whyheader);
		whyheader = tmp;
	}
	while (howheader != NULL)
	{
		tmp = howheader->next;
		free(howheader);
		howheader = tmp;
	}
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {
	item* tmp = NULL;

	// Save under [when]
	if (whenheader != NULL) {
		tmp = whenheader;
		fwrite("[when]\n", 7, 1, f);
		fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
		fwrite("=", 1, 1, f);
		fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		while (tmp->next != NULL) {
			tmp = tmp->next;
			fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
			fwrite("=", 1, 1, f);
			fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		}
		fwrite("\n", 1, 1, f);
	}
	
	// Save under [where]
	if (whereheader != NULL) {
		tmp = whereheader;
		fwrite("[where]\n", 8, 1, f);
		fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
		fwrite("=", 1, 1, f);
		fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		while (tmp->next != NULL) {
			tmp = tmp->next;
			fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
			fwrite("=", 1, 1, f);
			fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		}
		fwrite("\n", 1, 1, f);
	}

	// Save under [who]
	if (whoheader != NULL) {
		tmp = whoheader;
		fwrite("[who]\n", 6, 1, f);
		fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
		fwrite("=", 1, 1, f);
		fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		while (tmp->next != NULL) {
			tmp = tmp->next;
			fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
			fwrite("=", 1, 1, f);
			fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
			printf("PRINTED PRINTED PRINTED");
		}
		fwrite("\n", 1, 1, f);
	}

	// Save under [what]
	if (whatheader != NULL) {
		tmp = whatheader;
		fwrite("[what]\n", 7, 1, f);
		fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
		fwrite("=", 1, 1, f);
		fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		while (tmp->next != NULL) {
			tmp = tmp->next;
			fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
			fwrite("=", 1, 1, f);
			fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		}
		fwrite("\n", 1, 1, f);
	}

	// Save under [why]
	if (whyheader != NULL) {
		tmp = whyheader;
		fwrite("[why]\n", 6, 1, f);
		fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
		fwrite("=", 1, 1, f);
		fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		while (tmp->next != NULL) {
			tmp = tmp->next;
			fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
			fwrite("=", 1, 1, f);
			fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		}
		fwrite("\n", 1, 1, f);
	}

	// Save under [how]
	if (howheader != NULL) {
		tmp = howheader;
		fwrite("[how]\n", 6, 1, f);
		fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
		fwrite("=", 1, 1, f);
		fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		while (tmp->next != NULL) {
			tmp = tmp->next;
			fwrite(tmp->entity, sizeof(char) * strlen(tmp->entity), 1, f);
			fwrite("=", 1, 1, f);
			fwrite(tmp->response, sizeof(char) * strlen(tmp->response), 1, f);
		}
		fwrite("\n", 1, 1, f);
	}

}