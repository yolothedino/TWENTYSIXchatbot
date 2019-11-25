/*
 * ICT1002 (C Language) Group Project, AY19 Trimester 1.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
 
 
/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chatbot";
	
}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";
	
}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {
	
	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_help(inv[0]))
		return chatbot_do_help(inc, inv, response, n);
	else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {
	
	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;
	
}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {
	 
	snprintf(response, n, "Goodbye!");
	 
	return 1;
	 
}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {
	
	/* to be implemented */
	return compare_token(intent, "load") == 0;
	
}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	FILE* fp;
	if (inv[1] == NULL) {
		snprintf(response, n, "Invalid - Please enter in the format of \"load <filename.ini>\"");
		return 0;
	}
	else {
		//char *filename = "C:\\Users\\Unknown51\\Desktop\\ICT 1002\\ICT1002_Group Project Assignment_AY2019_T1_Skeleton\\ICT1002_Group Project Assignment_AY2019_T1_Skeleton\\base.txt";
		fp = fopen(inv[1], "r");
		//fp = fopen(filename, "r");
		if (fp == NULL) { 
			snprintf(response, n, "file not found. Be sure to enter .ini after the filename."); 
		}
		else {
			int count = knowledge_read(fp);
			snprintf(response, n, "read %d response from %s", count, inv[1]);
			fclose(fp);
		}
		return 0;
	}
	 
}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {
	
	/* to be implemented */
	return compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 || compare_token(intent, "who") == 0;	
}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
// check if number of words greater than 1
	if (inc > 1) 
	{
		char tempbuf[MAX_INPUT];
		// check if the intent is what/where/who
		if (compare_token(inv[0], "what") == 0 || compare_token(inv[0], "where") == 0 || compare_token(inv[0], "who") == 0)
		{
			// check if the 2nd space is is/are
			if (compare_token(inv[1], "is") == 0 || compare_token(inv[1], "are") == 0)
			{
				// take inputs after is/are as entities
				char catbuf[MAX_INPUT] = "";

				for (int i = 2; i < inc; i++)
				{
					if (strcmp(catbuf, "") == 0)
					{
						strcpy(catbuf, inv[i]);
					}
					else
					{
						sprintf(catbuf, "%s %s", catbuf, inv[i]);
					}
				}

				// check for entity in linked list
				//if 'knowledge' is already inside, print the knowledge
				if (knowledge_get(inv[0], catbuf, response, n) == KB_OK)
				{
					printresponse(inv[0], catbuf, response, n);	
				}

				//knowledge not inside - i.e bot is dumb
				//make bot slightly less dumb by having it ask for the answer
				else if (knowledge_get(inv[0], catbuf, response, n) == KB_NOTFOUND)
				{
					printf("%s: I dont know %s. %s is %s?\n", chatbot_botname(), catbuf, inv[0], catbuf);
					printf("%s:", chatbot_username());
					fgets(tempbuf, n, stdin);	//tempbuf = the answer to the question. supplied by the user

					//check if the user pressed enter instead of entering an answer
					//effectively, there is no answer.
					if (tempbuf[0] == '\n' || tempbuf[0] == ' ')
					{

						snprintf(response, n, "I do not understand your answer. Please try again!");
						return 0;
					}
					else
					{
						snprintf(response, n, "Thank you");
						return (knowledge_put(inv[0], catbuf, tempbuf));
					}

				}

				else if (knowledge_get(inv[0], catbuf, response, n) == KB_INVALID)
				{
					snprintf(response, n, "I dont see a question. Please ask again");

					return 0;
				}
			}

			// check if the the 2nd position does not have is/are
			else if (compare_token(inv[1], "is") != 0 || compare_token(inv[1], "are") != 0)
			{
				// take inputs after intent as entities
				char catbuf[MAX_INPUT] = "";
				for (int i = 1; i < inc; i++)
				{
					if (strcmp(catbuf, "") == 0)
					{
						strcpy(catbuf, inv[i]);
					}
					else
					{
						sprintf(catbuf, "%s %s", catbuf, inv[i]);
					}
				}
				// check for entity in linked list
				if (knowledge_get(inv[0], catbuf, response, n) == KB_OK)
				{
					printresponse(inv[0], catbuf, response, n);
				}
				else if (knowledge_get(inv[0], catbuf, response, n) == KB_NOTFOUND)
				{
					printf("%s: I dont know %s. %s is %s?\n", chatbot_botname(), catbuf, inv[0], catbuf);
					printf("%s:", chatbot_username());
					fgets(tempbuf, n, stdin);

					if (tempbuf[0] == '\n')
					{
						snprintf(response, n, "Please teach me something");
						return 0;
					}
					else
					{
						snprintf(response, n, "Thank you");
						return (knowledge_put(inv[0], catbuf, tempbuf));
					}
				}
				else if (knowledge_get(inv[0], catbuf, response, n) == KB_INVALID)
				{
					snprintf(response, n, "I dont see a question. Please ask again");
					return 0;
				}
			}
		}
	}
	else
	{
		snprintf(response, n, "I do not understand your question");
	}
	return 0;
}

/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {
	
	/* to be implemented */
	return compare_token(intent, "reset") == 0;
	
}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	knowledge_reset();
	snprintf(response, n, "Knowledge's base has been reset");
	return 0;
	 
}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {
	
	/* to be implemented */
	return compare_token(intent, "save") == 0;
}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char* inv[], char* response, int n) {

	/* to be implemented */
	int i = 1;
	FILE* fp;
	if (inv[1] == NULL) {
		snprintf(response, n, "Invalid - Please enter in the format of \"save <filename.ini>\"");
		return 0;
	}
	else {
		//checks if its save to if it is move the inv up by 1
		if (compare_token(inv[1], "to") == 0) { i++; }
		fp = fopen(inv[i], "w+");
		if (fp == NULL) { snprintf(response, n, "file not found. Be sure to enter .ini after the filename."); }
		else {
			knowledge_write(fp);
			snprintf(response, n, "My knowledge has been saved to %s.", inv[i]);
		}
		fclose(fp);
	}
	return 0;

}
 
 
/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent) {
	
	/* to be implemented */
	return compare_token(intent, "joke") == 0 || compare_token(intent, "hi") == 0 || compare_token(intent, "hello") == 0
		|| compare_token(intent, "cat") == 0 || compare_token(intent, "marco") == 0;
 
}	


/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {
	
	/* to be implemented */
	
	if (compare_token(inv[0], "joke") == 0 )
	{
		snprintf(response, n, "This is the best joke I know.\nJimmy: Dad, I'm hungry. \nDad: Hi hungry, I'm Dad.");
		return 0;
	}

	if (compare_token(inv[0], "hello") == 0 || compare_token(inv[0], "hi") == 0)
	{
		snprintf(response, n, "Hello!");	
		return 0;
	}

	if (compare_token(inv[0], "cat") == 0)
	{
		snprintf(response, n, "meow!");
		return 0;
	}

	if (compare_token(inv[0], "marco") == 0)
	{
		snprintf(response, n, "polo");
		return 0;
	}

	else
	{
		snprintf(response, n, "hoho i dont get it");
		return 0;
	}

	return 0;
	
}
  

/*
 * ADDITIONAL FUNCTION
 * let's users access the list of basic commands by typing 'help'
 * determines if the intent is 'help'
 */
int chatbot_is_help(const char* intent) {

	/* to be implemented */
	return compare_token(intent, "help") == 0;

}


/*
 * ADDITIONAL FUNCTION
 * Respond to 'help'
 *
 * displays list of commands (with the exception of smalltalk)
 */
int chatbot_do_help(int inc, char* inv[], char* response, int n) {

	/* to be implemented */

	if (compare_token(inv[0], "help") == 0)
	{
		printf("Chatbot: This is the list of available commands and their functionalities.\n");
		printf("===============================================================================\n");
		printf("\"exit\" - Exit the program.\n");
		printf("\"what/who/where <query>\" - Ask the chatbot a what/who/where question.\n");
		printf("\"load\" - Load knowledge to the bot from an ini file.\n");
		printf("\"save\" - Save a bot's current knowledge to an ini file.\n");
		printf("\"reset\" - Resets a bot's current knowledge.\n");
		printf("===============================================================================\n");
		//more if needed

		snprintf(response, n, "How may I help you?");
		
		return 0;
	}


	return 0;

}