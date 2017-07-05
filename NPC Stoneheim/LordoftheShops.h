#include "NPCStructure.h"

#ifndef __LORDOFTHESHOPS_H
#define __LORDOFTHESHOPS_H

class LordoftheShops: public NPCstructure{
public:   
   LordoftheShops();
   ~LordoftheShops();
   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif
