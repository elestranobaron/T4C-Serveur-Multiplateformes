#include "NPCStructure.h"

#ifndef __HEADHUNTERWAJPOOTHIN_H
#define __HEADHUNTERWAJPOOTHIN_H

class HeadhunterWajpoothin : public NPCstructure{
public:   
    HeadhunterWajpoothin();
   ~HeadhunterWajpoothin();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    
};

#endif
