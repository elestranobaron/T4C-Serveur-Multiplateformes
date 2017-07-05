#include "NPCStructure.h"

#ifndef __GUILDLEADERETHAN_H
#define __GUILDLEADERETHAN_H

class GuildLeaderEthan : public NPCstructure{
public:
	GuildLeaderEthan();
	~GuildLeaderEthan();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif