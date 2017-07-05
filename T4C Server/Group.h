// *******************************************************************************************
// ***                                                                                     ***
//      File Name: Group.h
//      Project:   T4C Server
//      Plateform: Windows NT
//      Creation:  27/4/1999
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         27/4/1999       1.0       FL             Initial developpement
//
//      Description
//          This class implements groups for group play features.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_GROUP_H__2BEF7B41_FCC5_11D2_84F1_00E02922FA40__INCLUDED_)
#define AFX_GROUP_H__2BEF7B41_FCC5_11D2_84F1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <set>
#include <vector>
#include "Lock.h"

#pragma warning( disable : 4786 )

class Character;
class EXPORT Group : public CLock
{
public:
	virtual ~Group();

    static  Group *CreateGroup( Character *lpLeader );

    void    DistributeKillXP( Character *lpKiller, int hyXP ); //__int64
    void    DistributeKillGold( Character *lpKiller, DWORD dwGold );

    void    DistributeGold( Character *lpGiver, DWORD dwGold );

    bool    Invite ( Character *lpSource, Character *lpCharacter );
    void    Dismiss( Character *lpCharacter );
    void    Dismiss( DWORD dwID );
    bool    Join   ( Character *lpCharacter );

    bool    IsGroupMember( Character *lpCharacter );

    void       GetGroupMembers( std::vector< Character * > &vMembers );
    Character *GetLeader( void );

    void    SendGroupMembers( Character *receiver );

    void    SendHpUpdate( Character *source );

    void    UpdateGroupListing( void );

    void    ToggleAutoSplit( bool newState );

private:
    // Private functions
    void    GetRangeGroupMembers( Character *lpCentralMember, std::vector< Character * > &vMembers );
    
    void    UpdateInviteListing( void );
    void    SendDisbandNotification( void );

	Group( Character *lpGroupLeader );
    void operator delete( void *lpData );

    // Attributes
    Character *            lpGroupLeader;

    std::set< Character *> cGroupMembers;
    std::set< Character *> cInviteList;
    bool                   boAutoShare;
};

#endif // !defined(AFX_GROUP_H__2BEF7B41_FCC5_11D2_84F1_00E02922FA40__INCLUDED_)
