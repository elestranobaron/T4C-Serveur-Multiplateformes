#include "stdafx.h"

DWORD __declspec( dllexport ) GetRunTime(){
    static INT initialTime = GetTickCount(); // steph ajout de INT
    return GetTickCount() - initialTime;
}