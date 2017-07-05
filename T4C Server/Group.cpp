// Group.cpp: implementation of the Group class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "Group.h"
#include "Character.h"
#include "Players.h"
#include "TFC_MAIN.h"
#include "Format.h"
#include <algorithm>
#include <iterator>
using namespace std;

#define MIN_LEVEL   1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Group::Group( Character *lpTheGroupLeader ) : lpGroupLeader( lpTheGroupLeader )
{    
    boAutoShare = true;

    // Add leader to group.
    cGroupMembers.insert( lpGroupLeader );
}

Group::~Group()
{

}


// static ////////////////////////////////////////////////////////////////////////////////
Group *Group::CreateGroup
//////////////////////////////////////////////////////////////////////////////////////////
// Creates an instance of a group and returns it.
// 
(
 Character *lpLeader // The group creator.
)
// Return: Group, a pointer to the group instance.
//////////////////////////////////////////////////////////////////////////////////////////
{
    Group *lpInstance = NULL;

    // A leader cannot already be in a group.
    ASSERT( lpLeader->GetGroup() == NULL );
    
    // If leader isn't in a group and is higher than lvl 5.
    if( lpLeader->GetGroup() == NULL && lpLeader->GetLevel() >= MIN_LEVEL ){
        // Create a new group.
        lpInstance = new Group( lpLeader );

        // Assign the newly created group to the leader.
        lpLeader->SetGroup( lpInstance );

        // Update the group members (with only the leader in the group.).
        lpInstance->SendGroupMembers( lpLeader );
    }    

    return lpInstance;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::DistributeKillXP
//////////////////////////////////////////////////////////////////////////////////////////
// Distributes an amount of 'kill XP' amongst a group
// 
(
 Character *lpKiller,   // Group member who did the kill.
 __int64 hyXP           // The XP to distribute.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoLock cLock( this );

    vector< Character * > vParty;
    
    // Get the in-range group members.
    GetRangeGroupMembers( lpKiller, vParty );

    // If there are members in range.
    if( vParty.size() > 0 ){
        // First determine the kill XP bonus.
        {
            double dblPercentBonus = 1;

            // For each additional member, add 50% bonus.
            dblPercentBonus += ( vParty.size() - 1 ) * .5;

            // Max the bonus to 300%
            if( dblPercentBonus > 3 ){
                dblPercentBonus = 3;
            }

            // Boost XP share by the bonus.
            hyXP = static_cast< __int64 >( hyXP * dblPercentBonus );

            // Divide bonused XP equally amongst all party members.
            hyXP = hyXP / vParty.size();
        }
        
        // Find the highest level member.
        DWORD dwHighestLevel = 0;
        {
            // Scroll through all party members.
            vector< Character *>::iterator i;
            for( i = vParty.begin(); i != vParty.end(); i++ ){
                // If this member has a higher level.
                if( (*i)->GetLevel() > dwHighestLevel ){
                    // Update highest level.
                    dwHighestLevel = (*i)->GetLevel();
                }
            }
        }

        // Scroll through all party members to distribute XP share.
        vector< Character *>::iterator i;
        for( i = vParty.begin(); i != vParty.end(); i++ ){
            Character *lpMember = (*i);

            // Determine the range size between XP segments. For each 25 levels chuncks, increase range by 4.
            DWORD dwRangeSize = ( lpMember->GetLevel() / 25 + 1 ) * 4;
            
            // Determine how many segment ranges there are between this member's level 
            // and the highest level member.
            DWORD dwSegments = ( dwHighestLevel - lpMember->GetLevel() ) / dwRangeSize;
            
            // No penalty by default.
            double dblLevelRangePenalty = 1;
            
            // XP share has no penalty by default.
            __int64 hyXPshare = hyXP;

            // If the player is too far from highest level.
            if( dwSegments > 0 ){
                // Minimum penalty is 0.5
                dblLevelRangePenalty = 0.5;

                // For each segments over 1.
                DWORD dwInc = 0;
                for( dwInc = 1; dwInc < dwSegments; dwInc++ ){
                    // Increase this penatly by 5.
                    dblLevelRangePenalty /= 5;
                }

                // Deal the XP penalty.
                hyXPshare = static_cast< __int64 >( hyXPshare * dblLevelRangePenalty );
            }

            // Give XP to this member.
            lpMember->SetXP( lpMember->GetXP() + hyXPshare );

            // If group member is a GOD_DEVELOPPER
            Players *lpPlayer = static_cast< Character *>( lpMember )->GetPlayer();            
            if( lpPlayer != NULL && lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                // Send debugging information.
                TFormat format;
                lpMember->SendSystemMessage(
                    format(
                        "Gained %I64u group xp.",
                        hyXPshare
                    )
                );
            }

            // Train this member.
            lpMember->TrainUnit();
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void Group::DistributeKillGold
//////////////////////////////////////////////////////////////////////////////////////////
// Distributes gold amongst a group if auto-share is enabled. Otherwise give all the gold
// to the killer.
// 
(
 Character *lpKiller, // The killer.
 DWORD dwGold         // The gold earned by the kill.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    // If auto-share is ON.
    if( boAutoShare ){
        // Distribute gold in party.
        DistributeGold( lpKiller, dwGold );
    }else{
        // Otherwise give everything to the killer.
        lpKiller->SetGold( lpKiller->GetGold() + dwGold );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::DistributeGold
//////////////////////////////////////////////////////////////////////////////////////////
// Shares an amount of gold taken from the owner's inventory, equally amongst all
// in-range group members. This function does not remove the gold from the giver.
// 
(
 Character *lpGiver, // Player sharing gold.
 DWORD dwGold        // The quantity of gold to share.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    vector< Character *> vMembers;
    
    // Retreive in-range group members.
    GetRangeGroupMembers( lpGiver, vMembers );
    
    // If there are group members within range.
    if( vMembers.size() > 0 ){
        // Determine each share of the gold.
        DWORD dwGoldShare = dwGold / vMembers.size();

        // Scroll through all in-range members.
        vector< Character *>::iterator i;
        for( i = vMembers.begin(); i != vMembers.end(); i++ ){
            // Give them all their share of gold.
            (*i)->SetGold( (*i)->GetGold() + dwGoldShare, FALSE );

            char buf[ 1024 ];
            sprintf( buf, _STR( 7507, (*i)->GetLang() ), dwGoldShare );
            
            (*i)->SendSystemMessage( buf );

        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Group::Invite
//////////////////////////////////////////////////////////////////////////////////////////
// Invites a player into a group (puts it on an invitation list)
// 
(
 Character *lpSource,   // The source of the invitation.
 Character *lpCharacter // The character to invite.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );

    // If the character is already in a group.
    // and this group isn't the source's group.
    if( lpCharacter->GetGroup() != NULL && lpCharacter->GetGroup() != lpSource->GetGroup() ){

        lpSource->SendSystemMessage( _STR( 7262, lpSource->GetLang() ) );

        return false;
    }

    // If character is under level 5.
    if( lpCharacter->GetLevel() < MIN_LEVEL ){

        lpSource->SendSystemMessage( _STR( 7263, lpSource->GetLang() ) );

        return false;
    }

    // If the source of the invitation is not the leader.
    if( lpSource != lpGroupLeader ){

        lpSource->SendSystemMessage( _STR( 7264, lpSource->GetLang() ) );

        return false;
    }

    // If the character is already in the group.
    if( cGroupMembers.find( lpCharacter ) != cGroupMembers.end() ){

        lpSource->SendSystemMessage( _STR( 7265, lpSource->GetLang() ) );

        return false;
    }

    if( cGroupMembers.size() + cInviteList.size() >= 8 ){
        lpSource->SendSystemMessage( _STR( 7267, lpSource->GetLang() ) );
        
        return false;
    }

    if( !lpCharacter->CanInvite() ){
        lpSource->SendSystemMessage( _STR( 10493, lpSource->GetLang() ) );
        
        return false;
    }

    // If the character could be inserted into the invite list (isn't already in the invite list).
    if( cInviteList.insert( lpCharacter ).second ){        
        // Set the character's group.
        lpCharacter->SetGroup( this );

        // Send invitation notice!
        TFCPacket sending;
        
        sending << (RQ_SIZE)RQ_GroupInvite;
        sending << (long)lpGroupLeader->GetID();
        sending << (CString &)lpGroupLeader->GetName( _DEFAULT_LNG );
        
        lpCharacter->SendPlayerMessage( sending );

        // Send an invite list update to all group members.
        UpdateInviteListing();

        return true;
    }

    lpSource->SendSystemMessage( _STR( 7266, lpSource->GetLang() ) );

    return false;
}


//////////////////////////////////////////////////////////////////////////////////////////
void Group::Dismiss
//////////////////////////////////////////////////////////////////////////////////////////
// Dismisses a character from the group. After a call to this function, the group might
// become invalid.
// 
(
 Character *lpCharacter // The character to dismiss.
)
//////////////////////////////////////////////////////////////////////////////////////////
{      

	// If the leader leaves the group.and there is only one left in group, 
	// delete (disband) the group
    if( lpCharacter == lpGroupLeader && cGroupMembers.size() <= 2){        

		{ // Autolock scope
			CAutoLock cLock( this );

			// Send a disband notification to all users.
			SendDisbandNotification();

			// Scroll through all group members.
			set< Character *>::iterator i;
			for( i = cGroupMembers.begin(); i != cGroupMembers.end(); i++ ){
				// Set their group to nil.
				(*i)->SetGroup( NULL );
			}

			// Scroll through all invited members.
			for( i = cInviteList.begin(); i != cInviteList.end(); i++ ){
				// Set their group to nil.
				(*i)->SetGroup( NULL );
			}
		} //Autolock scope

		lpCharacter->SetGroup( NULL );

		// Delete this group from memory.
		delete this;

		// Return immediatly, group now invalid.
		return;

    }
	// If not disbanding, just remove the member!
	else { 
		{ // Autolock scope
			CAutoLock cLock( this );

			// Try to find the character in the group members.
			set< Character *>::iterator i = cGroupMembers.find( lpCharacter );

	        // If player was found in the group members.
		    if( i != cGroupMembers.end() ){

				// Send a GroupLeave packet to dismissed member
				TFCPacket sending;
				sending << (RQ_SIZE)RQ_GroupLeave;
    
				(*i)->SendPlayerMessage( sending );

				// Remove it from the group.
				cGroupMembers.erase( i );

				// If the leaving member is the leader, move the leadership to the first group member available
				if ( lpCharacter == lpGroupLeader ) {
					i = cGroupMembers.begin();
					lpGroupLeader = (*i);
				}

	            // Notify the other members.
		        UpdateGroupListing();

	        }else{

				// Try to find it in the invite list.
				set< Character *>::iterator j = cInviteList.find( lpCharacter );

				// If the player was found in the invite list.
				if( j != cInviteList.end() ){


					TFormat format;

					lpGroupLeader->SendSystemMessage( 
						format(
							_STR( 7685, lpGroupLeader->GetLang() ),
							(LPCTSTR)(*j)->GetName( _DEFAULT_LNG )
						)
					);

					// Remove it from there.
					cInviteList.erase( j );

					// Notify the other members.
					UpdateInviteListing();

				}
			}
		} // Autolock scope

   
        // Set the character's group to nil.
        lpCharacter->SetGroup( NULL );

        // If there is now only one member (the leader).
        if( cGroupMembers.size() == 1 && cInviteList.size() == 0 ){

            // Dismiss the leader (disband the group).
            Dismiss( lpGroupLeader );

        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::Dismiss
//////////////////////////////////////////////////////////////////////////////////////////
// Dismisses a group member according to its dynamic ID. After a call to this function,
// this group might become invalid.
// 
(
 DWORD dwID // The character ID to dismiss.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    Character *lpCharacter = NULL;
    
    // For auto-lock scoping
    {        
        CAutoLock cLock( this );
        
        // Find the character in the current group members.
        set< Character * >::iterator i;
        
        // While the search isn't finished and we don't have a character.
        i = cGroupMembers.begin(); 
        while( i != cGroupMembers.end() && lpCharacter == NULL ){
            // If the IDs correspond.
            if( (*i)->GetID() == dwID ){
                // We have a character!
                lpCharacter = *i;
            }
            i++;
        }

        // If the character was not found in the group members.
        if( lpCharacter == NULL ){
            // Search the invite list.
            i = cInviteList.begin();
            while( i != cInviteList.end() && lpCharacter == NULL ){
                // If the IDs correspond.
                if( (*i)->GetID() == dwID ){
                    // We have a character!
                    lpCharacter = *i;
                }
                i++;
            }
        }
    }
    // If, in the end, a character was found.
    if( lpCharacter != NULL ){

        // Dismiss it. (This function checks for leader dismissal etc.)
        Dismiss( lpCharacter );
        
        // Return immediatly, group might now be invalid.
        return;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Group::Join
//////////////////////////////////////////////////////////////////////////////////////////
//  Joins a character to the group. Character must first have been invited.
// 
(
 Character *lpCharacter // The character who joins.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );


    // Try to find the player in the invite list.
    set< Character *>::iterator i = cInviteList.find( lpCharacter );

    // If the user could not be found in the invite list.
    if( i == cInviteList.end() ){
        return false;
    }

    // If player joins and is in the invite list, it should NOT be in the group members.!
    ASSERT( cGroupMembers.find( lpCharacter ) != cGroupMembers.end() );

    // Remove it from the invite list.
    cInviteList.erase( i );

    bool boReturn = false;

    // If the character could be added to the group members.
    if( cGroupMembers.insert( lpCharacter ).second ){
        // Character was successfully added to the group members.
        boReturn = true;
    }   

    // Update both invite and member list.
    UpdateGroupListing();
    UpdateInviteListing();

    return boReturn;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Group::IsGroupMember
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines if a character is a member of this group.
// 
(
 Character *lpCharacter // The given character.
)
// Return: bool, true if this character is a member of this group.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Simply try to find the character in the group.
    return( cGroupMembers.find( lpCharacter ) != cGroupMembers.end() );
}

// Accessors
//////////////////////////////////////////////////////////////////////////////////////////
void Group::GetGroupMembers
//////////////////////////////////////////////////////////////////////////////////////////
// Accessor function, fetches the list of all group members.
// 
(
 vector< Character * > &vMembers // The container which will hold all group members.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );

    // Copy all group members into vector.
    std::copy( cGroupMembers.begin(), cGroupMembers.end(), back_inserter( vMembers ) );   
}

//////////////////////////////////////////////////////////////////////////////////////////
Character *Group::GetLeader( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the group leader.
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoLock cLock( this );
    return lpGroupLeader;
}


// Private
//////////////////////////////////////////////////////////////////////////////////////////
inline bool PosInRange
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if two positions are in range of each other.
// 
(
 WorldPos wlRight,  // First position
 WorldPos wlLeft    // Second position
)
// Return: inline bool, true if positions are in range, false otherwise.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return( ::abs( wlRight.X - wlLeft.X ) <= 20 && ::abs( wlRight.Y - wlLeft.Y ) <= 20 );
}
                  
//////////////////////////////////////////////////////////////////////////////////////////
void Group::GetRangeGroupMembers
//////////////////////////////////////////////////////////////////////////////////////////
// Determines all player who are in range of the central player.
// 
(
 Character *lpCentralMember,    // The player in the center.
 vector< Character *> &vMembers // The container which will contain all party members.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoLock cLock( this );
    // Scroll through all group members.
    set< Character *>::iterator i;
    for( i = cGroupMembers.begin(); i != cGroupMembers.end(); i++ ){
        // If the central character and this group members are in visual range.
        if( PosInRange( (*i)->GetWL(), lpCentralMember->GetWL() ) ){
            // Add the member to the list of in-range members.
            vMembers.push_back( *i );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::UpdateGroupListing( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends the list of all characters in the group to all members.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    // Scroll through all group members.
    set< Character *>::iterator i;
    for( i = cGroupMembers.begin(); i != cGroupMembers.end(); i++ ){
        // Send group members to this member.
        SendGroupMembers( *i );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::UpdateInviteListing( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends the list of all invited players in the group.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Do nothing for this version. (invitation list isn't used by client)
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::SendDisbandNotification( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends a disband notification to all members in a group.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    // Scroll through all group members.
    set< Character *>::iterator i;
    for( i = cGroupMembers.begin(); i != cGroupMembers.end(); i++ ){
        TFCPacket sending;
        
        sending << (RQ_SIZE)RQ_NotifyGroupDisband;

        (*i)->SendPlayerMessage( sending );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::operator delete
//////////////////////////////////////////////////////////////////////////////////////////
//  Private deletion member. Only groups can delete themselves.
// 
(
 void *lpData // The data to free.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Call normal delete operator.
    ::delete lpData;
}


//////////////////////////////////////////////////////////////////////////////////////////
void Group::SendGroupMembers
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends the list of group members to the target.
// 
(
 Character *target // The character to send the group members to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );

    TFCPacket sending;

    sending << (RQ_SIZE)RQ_UpdateGroupMembers;
    sending << (char)( boAutoShare ? 1 : 0 );
    sending << (short)cGroupMembers.size();

    set< Character *>::iterator i;
    for( i = cGroupMembers.begin(); i != cGroupMembers.end(); i++ ){

        sending << (long)(*i)->GetID();     // Send the player's ID.        
        sending << (short)(*i)->GetLevel(); // Send the player's level.
        
        // Avoid a divide-by-0
        if( (*i)->GetMaxHP() == 0 ){
            sending << (short)0;
        }else{                    
            sending << (short)( (*i)->GetHP() * 100 / (*i)->GetMaxHP() ); // Send the HP percentage.
        }
       
        sending << (char)( (*i) == lpGroupLeader );          // If the player is the leader.                
        sending << (CString &)(*i)->GetName( _DEFAULT_LNG ); // Send the player's name.
    }

    target->SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::SendHpUpdate
//////////////////////////////////////////////////////////////////////////////////////////
//  Send an update to all group members that your character changed HP.
// 
(
 Character *source // The character whose hp changed.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    set< Character *>::iterator i;
    for( i = cGroupMembers.begin(); i != cGroupMembers.end(); i++ ){
        TFCPacket sending;

        sending << (RQ_SIZE)RQ_UpdateGroupMemberHp;
        sending << (long)source->GetID();   // Player's ID
        // Avoid a divide-by-0
        if( source->GetMaxHP() == 0 ){
            sending << (short)0;
        }else{                    
            sending << (short)( source->GetHP() * 100 / source->GetMaxHP() ); // Send the HP percentage.
        }

        (*i)->SendPlayerMessage( sending );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Group::ToggleAutoSplit
//////////////////////////////////////////////////////////////////////////////////////////
//  Toggles auto-splitting
//
(
 bool newState
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );

    boAutoShare = newState;

    // Send an autosplit packet to all users.
    set< Character *>::iterator i;
    for( i = cGroupMembers.begin(); i != cGroupMembers.end(); i++ ){
        TFCPacket sending;
        
        sending << (RQ_SIZE)RQ_GroupToggleAutoSplit;
        sending << (char)( boAutoShare ? 1 : 0 );

        (*i)->SendPlayerMessage( sending );
    }    
}