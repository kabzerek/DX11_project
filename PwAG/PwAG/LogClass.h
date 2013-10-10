#ifndef _LOGCLASS_H_
#define _LOGCLASS_H_

#include <string>
#include <fstream>

class LogClass
{
private:
	std::fstream m_logFile;

public:
	static LogClass& GetInstance(void)
	{
		static LogClass m_Instance;
		return m_Instance;
	}

	void Print(std::string text)
	{
		m_logFile << text << std::endl;
	}

	void Shutdown(void)
	{
		m_logFile.close();
	}

private:
	LogClass(void)
	{
		m_logFile.open("log.txt", std::ios::out);
	}
	LogClass(const LogClass&);
	LogClass& operator=(const LogClass&);
	~LogClass(void) {}
};

#endif


