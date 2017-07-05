/******************************************************************************
 *
 * file: Guilds.h
 * description: Guild specifications for The 4th Coming
 * author: Desboys
 * 
 *****************************************************************************/

#ifndef __GUILDS_H__
#define __GUILDS_H__
#include <string>
#include <vector>
#include "Character.h"
#include "Lock.h"
class Guilds {
private:
	int Gold;
	std::string Name;
	Character *Leader;
	std::vector<Character *> Members;
	int NumberOfMembers;
	CLock GLock;
public:
	Guilds();
	Guilds(std::string GName,int GGold,int GNumber);
	~Guilds();
	std::string GetName() const { return Name; }
	void SetName(std::string NewName) { Name = NewName; }
	Character *GetLeader() const { return Leader; }
	void SetLeader(Character *NewLeader) { Leader = NewLeader; }
	int GetNumberOfMembers const { return NumberOfMembers; }
    void RemoveMember(Character *WhoDid,Character *OldMember);
	void AddMember(Character *WhoDid,Character *NewMember);
	void PromoteMember(Character *WhoDid,Character *Promoted);
	void Invite(Character *WhoDid,Character *Invited);
};
#endif