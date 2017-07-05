#include "NPCStructure.h"

#ifndef __BALDRICSILVERKNIFE_H
#define __BALDRICSILVERKNIFE_H

class BaldricSilverknife : public NPCstructure{
public:   
    BaldricSilverknife();
   ~BaldricSilverknife();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
