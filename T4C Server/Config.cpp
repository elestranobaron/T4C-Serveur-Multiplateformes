#include "Config.h"
#include <fstream>
#include <iostream>

	Config&
Config::instance()
{
	static Config theInstance;
	return theInstance;
}


	bool
Config::initConfig(const char* cfgFilename)
{
	using namespace std;

	bool    status = true;
	fstream file(cfgFilename, ios::in);

	if (file)
	{
		string line;
		size_t lineNum = 0;

		while (getline(file, line))
		{
			++lineNum;

			stringstream iss(line);
			string       key, equals, value;

			iss >> key >> equals >> value;

			if (!iss.fail())
			{
				myConfig.insert(pair<string, string>(key, value));
			}
			else
			{
				cerr << "Error in configuration file, line " << lineNum << endl;
				status = false;
				break;
			}
		}
	}
	else
	{
		cerr << "Cannot open configuration file " << cfgFilename << endl;
		status = false;
	}

	return status;
}
