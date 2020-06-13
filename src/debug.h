/*
 * debug.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef DEBUG_H_
#define DEBUG_H_

enum DebugLevel
{
	None = 0,
	Critical,
	Error,
	Warning,
	Info,
	Debug,
	HighDebug
};

class CDebug : public TSingleton<CDebug>
{

public:
	CDebug();
	~CDebug();

	void setDebugLevel(DebugLevel debugLevel) { m_dbgLvl = debugLevel; }
	void crit(const char *msg, ...);
	void err(const char *msg, ...);
	void warn(const char *msg, ...);
	void info(const char *msg, ...);
	void debug(const char *msg, ...);
	void hidbg(const char *msg, ...);
	void setLogToFile(bool flag);
	bool isActive(DebugLevel debugLevel) { return debugLevel <= m_dbgLvl; }

private:
	void printDebug(DebugLevel debugLevel, const char *msg, va_list args);

	bool m_logToFile;
	FILE *m_pLogFile;
	DebugLevel m_dbgLvl;


};

#endif /* DEBUG_H_ */
