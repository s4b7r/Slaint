/*
 * debug.cpp
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#include "comhead.h"


CDebug::CDebug()
{
	// Default Debuglevel setzen
	m_dbgLvl = G_DEF_DBG_LVL;
	// Logfile öffnen
	m_pLogFile = fopen("slaint.log", "a");
	m_logToFile = G_DEF_DBG_LOGTOFILE;
}

CDebug::~CDebug()
{
	// Letzter Flush ins Logfile und schließen
	fflush(m_pLogFile);
	fclose(m_pLogFile);
}

void CDebug::setLogToFile(bool flag)
{
	m_logToFile = flag;
}

void CDebug::printDebug(DebugLevel debugLevel, const char *msg, va_list args)
{
	if( debugLevel <= m_dbgLvl )
	{

		// Zeilenumbruch an Nachricht anhängen
		// Symbolik davor setzen
		char *newMsg = (char*) malloc(strlen(msg) + 7);
		newMsg[0] = 0;
		switch (debugLevel)
		{
		case None:
			strcat(newMsg, "?!?!?");
		case Critical:
			strcat(newMsg, "[!!] ");
			break;
		case Error:
			strcat(newMsg, "[!]  ");
			break;
		case Warning:
			strcat(newMsg, "[W]  ");
			break;
		case Info:
			strcat(newMsg, "     ");
			break;
		case Debug:
			strcat(newMsg, "(:)  ");
			break;
		case HighDebug:
			strcat(newMsg, "(::) ");
			break;
		}
		strcat(newMsg, msg);
		strcat(newMsg, "\n");

		// Konsolenausgabe
		vprintf(newMsg, args);

		// Dateiausgabe
		if( m_logToFile )
		{
			vfprintf(m_pLogFile, newMsg, args);
			fflush(m_pLogFile);
		}

		free(newMsg);

	}
}

void CDebug::crit(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	printDebug(Critical, msg, args);
	va_end(args);
}

void CDebug::err(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	printDebug(Error, msg, args);
	va_end(args);
}

void CDebug::warn(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	printDebug(Warning, msg, args);
	va_end(args);
}

void CDebug::info(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	printDebug(Info, msg, args);
	va_end(args);
}

void CDebug::debug(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	printDebug(Debug, msg, args);
	va_end(args);
}

void CDebug::hidbg(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	printDebug(HighDebug, msg, args);
	va_end(args);
}
