// *******************************************************************************************
// ***                                                                                     ***
//      File Name: Hive.h
//      Project:   TFC Server
//      Plateform: Windows NT 4.0 Workstation/Server
//      Creation:  15/6/1998
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         15/6/1998       1.0       FL             Initial developpement
//
//      Description
//          This class handles monster repopping. Using the Unit interface to instantiate
//      larvae into the world.
// ***                                                                                     ***
//	*******************************************************************************************
// ***           Copyright (c) 1997-1998 Virtual Dreams. All rights reserved.              ***


#if !defined(AFX_Hive_H__60753E28_0459_11D2_8341_00E02922FA40__INCLUDED_)
#define AFX_Hive_H__60753E28_0459_11D2_8341_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Unit.h"

typedef struct _LARVA{
	WORD  wMonsterID;	// Monster emerging from larva.
} LARVA, *LPLARVA;

class Hive : public Unit  
{
public:
	Hive();

	// Creates the larvae group.
	void Create( WORD wMinEmergeTime, WORD wMaxEmergeTime, WORD wMaxChildren, WORD wEmergenceRange );

	// Adds a larva to the group.
	void AddLarva( LPLARVA lpLarva );

	// Queries if any larva should emerge.
	void QueryPopup( void );

	// Decreases the monster count
	void DecreaseMonsterCount( void );

    int attacked(LPATTACK_STRUCTURE strike, Unit *Mechant){ return 0; };

    // Hives cannot be vaporized.
    void VaporizeUnit( void ){};

private:
    virtual ~Hive();

	inline void PopupMonster( WORD wMonsterID );

	TemplateList < LARVA > tlLarvae;	// Larvae in larvae group.

	WORD  wMinEmergeTime;
	WORD  wMaxEmergeTime;
	WORD  wMaxChildren;
	WORD  wEmergenceRange;

	WORD  wCurrentChildrenCount;
	DWORD dwCurrentEmergeTime;
};

#endif // !defined(AFX_Hive_H__60753E28_0459_11D2_8341_00E02922FA40__INCLUDED_)
