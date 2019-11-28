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
#include <curl/curl.h>		//may show error, but doesn't matter
#include <ctype.h>>



char botName[20] = DEFAULT_BOT_NAME;	//fixed at 20. can be changed by the user during runtime/knowledge loading.

 /*Weather stuff*/
struct FtpFile {
	const char* filename;
	FILE* stream;
};

/*Weather stuff*/
static size_t my_fwrite(void* buffer, size_t size, size_t nmemb, void* stream)
{
	struct FtpFile* out = (struct FtpFile*)stream;
	if (!out->stream) {
		/* open file for writing */
		out->stream = fopen(out->filename, "wb");
		if (!out->stream)
			return -1; /* failure, can't open file to write */
	}
	return fwrite(buffer, size, nmemb, out->stream);
}

/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return botName;
	
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
	else if (strlen(inv[0]) > MAX_INTENT)
	{
		snprintf(response, n, "Input too large. Please limit INTENT to length of %d.", MAX_INTENT);
		return 0;
	}
	else if (inc > 1)
	{
		char catbuf[MAX_INPUT] = "";
		for (int i = 1; i < inc; i++)
		{
			if (strcmp(catbuf, "") == 0)
				strcpy(catbuf, inv[i]);
			else
				sprintf(catbuf, "%s %s", catbuf, inv[i]);
		}



		if (strlen(catbuf) > MAX_ENTITY)
		{
			snprintf(response, n, "Input too large. Please limit ENTITY to length of %d.",  MAX_ENTITY);
			return 0;
		}
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
	else if (chatbot_is_open(inv[0]))
		return chatbot_do_open(inc, inv, response, n);
	else if (chatbot_is_weather(inv[0]))
		return chatbot_do_weather(inc, inv, response, n);
	else if (chatbot_is_name(inv[0]))
		return chatbot_do_name(inc, inv, response, n);
	else if (chatbot_is_forget(inv[0]))
		return chatbot_do_forget(inc, inv, response, n);
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
	
	FILE* fp;
	if (inv[1] == NULL) {
		snprintf(response, n, "Invalid - Please enter in the format of \"load <filename.ini>\"");
		return 0;
	}

	char catbuf[MAX_INPUT] = "";
	for (int i = 1; i < inc; i++)
	{
		if (strcmp(catbuf, "") == 0)
			strcpy(catbuf, inv[i]);
		else
			sprintf(catbuf, "%s %s", catbuf, inv[i]);
	}


	fp = fopen(catbuf, "r");
	if (fp == NULL) {
		snprintf(response, n, "Filename \"%s\" not found. Be sure to enter .ini after the file's name. e.g \"MyFileName.ini\".", catbuf);
	}
	else {
		int count = knowledge_read(fp, botName);
		snprintf(response, n, "read total %d knowledge lines from %s", count, catbuf);
		fclose(fp);
	}
	return 0;
	 
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
	
	// check if number of words greater than 1
	if (inc > 1) 
	{
		char tempbuf[MAX_INPUT];
		// check if the intent is what/where/who
		if (compare_token(inv[0], "what") == 0 || compare_token(inv[0], "where") == 0 || compare_token(inv[0], "who") == 0)
		{
			// check if the 2nd word is is/are
			if (compare_token(inv[1], "is") == 0 || compare_token(inv[1], "are") == 0)
			{
				// accounting for is/are, take inputs after those 2 words as entities
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
					fgets(tempbuf, MAX_INPUT, stdin);	//tempbuf = the answer to the question. supplied by the user

					//check if the user pressed enter instead of entering an answer (i.e no answer)
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

			// for cases when there is not is/are
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
	
	for (int i = 0; i < 10; i++)			//sets every character to null
		botName[i] = '\0';

	strcpy(botName, DEFAULT_BOT_NAME);		//resets to default name
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

	char catbuf[MAX_INPUT] = "";
	for (int i = 1; i < inc; i++)
	{
		if (strcmp(catbuf, "") == 0)
			strcpy(catbuf, inv[i]);	//copies next in line words to catbuf, effectively concatenating the string.
		else
			sprintf(catbuf, "%s %s", catbuf, inv[i]);
	}
	
	//if (compare_token(inv[1], "to") == 0) { i++; }		//checks if its save to if it is move the inv up by 1
	fp = fopen(catbuf, "w+");
	if (fp == NULL)
		snprintf(response, n, "Filename \"%s\" not found. Be sure to enter .ini after the file's name. e.g \"MyFileName.ini\".", catbuf);
	else {
		fwrite("[NAME]\n", 7, 1, fp);
		fwrite("name=", 5, 1, fp);
		fwrite(botName, 10, 1, fp);
		fwrite("\n\n", 2, 1, fp);
		knowledge_write(fp);
		snprintf(response, n, "My knowledge has been saved to %s.", catbuf);
	}
	fclose(fp);


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
		|| compare_token(intent, "cat") == 0 || compare_token(intent, "marco") == 0 || compare_token(intent, "dadjoke") == 0;
 
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
		snprintf(response, n, "This is the one joke I know.\nWhat has four legs and can fly?\nTwo birds.");
		return 0;
	}

	if (compare_token(inv[0], "dadjoke") == 0)
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
		snprintf(response, n, "hoho i dont get it");	//will never happen (probably?)
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
		printf("%s: This is the list of available commands and their functionalities.\n", botName);
		printf("===============================================================================\n");
		printf("\"exit/quit\" - Exit the program.\n");
		printf("\"what/who/where <entity>\" - Ask the chatbot a what/who/where question.\n");
		printf("\"load <filename>.ini\" - Load knowledge to the bot from an ini file. This adds on current existing knowledge.\n");
		printf("\"save <filename>.ini\" - Save a chatbot's current knowledge to an ini file.\n");
		printf("\"reset\" - Resets a bot's current knowledge and name.\n");
		printf("=================================OTHER FUNCTIONS===============================\n");
		printf("\"name <newname>\" - Change the chatbot's name.\n");
		printf("\"open\" - Prints out chatbot's current knowledge\n");
		printf("\"forget <intent> <entity>\" - Remove a certain line of the chatbot's knowledge.\n");
		printf("==================================SMALLTALK====================================\n");
		printf("\"hi\" \"hello\" \"cat\" \"joke\" \"dadjoke\" \"marco\" \n");
		printf("===============================================================================\n");


		snprintf(response, n, "How may I help you?");

	}


	return 0;

}

/*
 * ADDITIONAL FUNCTION
 * determines if the intent is 'open'
 */
int chatbot_is_open(const char* intent) {

	/* to be implemented */
	return compare_token(intent, "open") == 0;

}

/*
 * ADDITIONAL FUNCTION
 * Respond to 'open'
 *
 * prints out every line of 'knowledge' of the chatbot
 */
int chatbot_do_open(int inc, char* inv[], char* response, int n) {

	if (knowledge_open() != 0)
		snprintf(response, n, "Chatbot knowledge printed.");
	else
		snprintf(response, n, "Chatbot has no knowledge to show.");
	return 0;

}

/*
 * ADDITIONAL FUNCTION
 * let's users retrieve weather info
 * determines if the intent is 'weather'
 */
int chatbot_is_weather(const char* intent) {

	return compare_token(intent, "weather") == 0;
}

/*
 * ADDITIONAL FUNCTION
 * retrieves and display weather inforamtion of a specific placae determined by user.
 */
int chatbot_do_weather(int inc, char* inv[], char* response, int n) {

	if (inv[1] == NULL)
	{
		snprintf(response, n, "Invalid - Please enter in the format of \"weather singapore\"");
	}
	else
	{
		int fail = 0;
		CURL* curl;
		CURLcode res;
		struct FtpFile ftpfile = {
		  "weather.txt", /* name to store the file as if successful. located in the folder chatbot26 */
		  NULL
		};

		curl_global_init(CURL_GLOBAL_DEFAULT);

		curl = curl_easy_init();
		if (curl) {
			char* city = inv[1];
			char* url = "http://api.openweathermap.org/data/2.5/weather?q=%s\&units=metric&APPID=eb229983d1ff9edbcb657773a8a06001";
			char result[200];
			sprintf(result, url, city);

			curl_easy_setopt(curl, CURLOPT_URL, result);
			/* Define our callback to get called when there's data to be written */
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
			/* Set a pointer to our struct to pass to the callback */
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

			/* Switch on full protocol/debug output */
			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

			res = curl_easy_perform(curl);

			/* always cleanup */
			curl_easy_cleanup(curl);

			if (CURLE_OK != res) {
				/* we failed */
				fail = 1;
				//fprintf(stderr, "curl told us %d\n", res);
			}
			else
			{
				fail = 0;
			}
		}

		if (ftpfile.stream)
			fclose(ftpfile.stream); /* close the local file */

		curl_global_cleanup();

		if (fail == 0)
		{
			FILE* file;
			int c;
			int ischar = 0;
			/*open the file with fopen()*/
			file = fopen("weather.txt", "r");
			if (file == NULL)
			{
				snprintf(response, n, "Could not open weather.txt.\n");
				return 1;
			}
			else
			{
				while ((c = getc(file)) != EOF)
				{
					if (isalnum(c))
					{
						ischar = 1;
						printf("%c", c);
					}
					else if (c == '.' || c == ':' || c == ' ' || c == '_')
					{
						printf("%c", c);
					}
					else if ((ischar == 1) & (c == '"'))
					{

					}
					else if (ischar == 1)
					{
						ischar = 0;
						printf("\n");
					}
				}
				fclose(file);
			}
		}
		else
		{
			snprintf(response, n, "Please check internet connection and try again.\n");
		}
	}
	return 0;
}

/*
 * ADDITIONAL FUNCTION
 * let's users change the bot's name
 * determines if the intent is 'name'
 */
int chatbot_is_name(const char* intent) {

	return compare_token(intent, "name") == 0;

}

/*
 * ADDITIONAL FUNCTION
 * Respond to 'help'
 *
 * displays list of commands (with the exception of smalltalk)
 */
int chatbot_do_name(int inc, char* inv[], char* response, int n) {


	if (inv[1] == NULL)//if (inc < 2)
	{
		snprintf(response, n, "Please enter a name in the format of \"name <newName>\". Whitespaces are not accepted");
		return 0;
	}

	else if (strlen(inv[1]) > 20)		//check if name is within acceptable size (of 20)
	{
		snprintf(response, n, "Name must not exceed 20 characters");
		return 0;					//shuts it down since large names are a no-go
	}

	//inv[1]
	for (int i = 0; i < 10; i++)	//sets every character to null before replacing w/ new name.
		botName[i] = '\0';

	strcpy(botName, inv[1]);

	snprintf(response, n, "My name has been changed. Hi, how may I help you?");

	return 0;

}

/*
 * ADDITIONAL FUNCTION
 * let's users change the bot's name
 * determines if the intent is 'name'
 */
int chatbot_is_forget(const char* intent) {

	return compare_token(intent, "forget") == 0;

}

/*
 * ADDITIONAL FUNCTION
 * Respond to 'forget'
 *
 * displays list of commands (with the exception of smalltalk)
 */
int chatbot_do_forget(int inc, char* inv[], char* response, int n) {

	int forgetResult = -1;

	if (inv[1] == NULL)//nothing else other than 'forget' is entered
	{
		snprintf(response, n, "Please enter something for me to forget. E.g \"what bob\"");
		return 0;
	}

	char catbuf[MAX_INPUT] = "";
	for (int i = 1; i < inc; i++)
	{
		if (strcmp(catbuf, "") == 0)
			strcpy(catbuf, inv[i]);
		else
			sprintf(catbuf, "%s %s", catbuf, inv[i]);
	}

	if (knowledge_forget(catbuf) == 1)		//successfully forgot something
		snprintf(response, n, "I forgot something. Hi, how may I help you?");
	else									//entered phrase did not exist in linked lists. 
		snprintf(response, n, "There is nothing to forget. Remember to enter in the format of e.g \"forget what bob\". How may I help you?");

	return 0;

}