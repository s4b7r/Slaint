/*
 * main.cpp
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#include "comhead.h"

// Forward Deklaration
void processArgs(int argc, char *argv[]);
void printHelp();

int main(int argc, char *argv[])
{
	if( argc > 1 )
	{
		processArgs(argc, argv);
	}
	GP_DBG->debug("main: The Beginning");
	GP_DBG->debug("main: Processed given arguments");
	GP_DBG->debug("main: Start Logic");
	GP_LOGIC->run();
	GP_DBG->debug("main: Logic ended");
	GP_DBG->debug("main: The End");

	return 0;
}

void processArgs(int argc, char *argv[])
{
	int pos = 1;
	while( pos < argc )
	{
		if( !strcmp(argv[pos], "-d") )
		{
			GP_DBG->setDebugLevel(HighDebug);
			GP_DBG->setLogToFile(false);
			pos++;
		}
		else
		{
			printHelp();
		}
	}
}

void printHelp()
{
	printf("Slaint [options]\n");
	printf("\t--help\tShow this help text\n");
	printf("\t-d\tStart in developer's debugger mode\n");
	//printf("\n");
	//printf("\n");
	//printf("\n");
	//printf("\n");
	//printf("\n");
	//printf("\n");

	//Dummy:
	//printf("\n");

	exit(0);
}
