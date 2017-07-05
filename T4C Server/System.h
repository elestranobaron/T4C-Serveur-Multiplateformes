/**
 * This file contains system-dependant data access methods.
 */
#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

class System
{
public:
	static std::string GetMachineName();
	static std::string GetProgramPath();
	static std::string MakePath(const char *path);
};

#endif
