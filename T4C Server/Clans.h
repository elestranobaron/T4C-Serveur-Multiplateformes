// Clans.h: interface for the Clans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLANS_H__A7D17DE3_1349_11D1_BCE6_00E029058623__INCLUDED_)
#define AFX_CLANS_H__A7D17DE3_1349_11D1_BCE6_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DynamicFlags.h"
#include "VDList.h"

class Clans  
{
public:
	Clans();
	virtual ~Clans();

	void Create();

	// [-100, 0] % of being aggressive to
	// [0, 100] % of being friendly with
	char MutualRelation(WORD clan, DWORD ID);

	// Sets the relation between a player and this clan
	void SetPlayerRelation(DWORD ID,  char AgressivnessPercentage);
	// Sets the relation between a clan and this clan
	void SetClanRelation(WORD clan, char AgressivnessPercentage);

	// Resets all relations with a player (player died?)
	void ResetAllRelationsWith(DWORD ID);

	static WORD GetNumberOfClans();
	static void SetNumberOfClans(WORD newNumberOfClans);
	static Clans *InitClans( void );


private:
	DynamicFlags MemorizedPlayers;
	static WORD NumberOfClans;
	char *MemorizedClans;
};

#endif // !defined(AFX_CLANS_H__A7D17DE3_1349_11D1_BCE6_00E029058623__INCLUDED_)
