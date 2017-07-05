#include "System.h"

#include <windows.h>
#include <cstdlib>

std::string System::GetMachineName()
{
        char machine_name[ MAX_COMPUTERNAME_LENGTH +1 ];
        unsigned long name_size = MAX_COMPUTERNAME_LENGTH +1;
        if (GetComputerName( machine_name, &name_size ))
			return machine_name;
		else
			return "Unamed Machine";
}

std::string System::GetProgramPath()
{
	char path[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char filename[_MAX_FNAME];
	char ext[_MAX_EXT];
	unsigned long loop = GetModuleFileName( GetModuleHandle( NULL ), path, _MAX_PATH );
	path[loop] = '\0';
	_splitpath(path,drive,dir,filename,ext);
	std::string programpath(drive);
	return programpath+dir;
}

std::string System::MakePath(const char *path)
{
	int path_length = strlen(path);
	std::string pathstr(GetProgramPath());
	char absPath[_MAX_PATH];
	if (NULL != _fullpath(absPath,path,_MAX_PATH))
	{
		pathstr = absPath;
	}
	if (pathstr[pathstr.length() -1] != '\\')
		pathstr += '\\';
	return pathstr;
}
