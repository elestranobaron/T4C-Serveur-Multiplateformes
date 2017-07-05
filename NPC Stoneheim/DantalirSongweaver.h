#include "NPCStructure.h"

#ifndef __DANTALIRSONGWEAVER_H
#define __DANTALIRSONGWEAVER_H

class DantalirSongweaver : public NPCstructure{
public:   
	DantalirSongweaver();
	~DantalirSongweaver();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
  
};

#endif
