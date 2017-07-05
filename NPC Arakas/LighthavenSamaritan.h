#include "NPCStructure.h"

#ifndef __LIGHTHAVEN_SAMARITAN_H
#define __LIGHTHAVEN_SAMARITAN_H

class LighthavenSamaritan : public NPCstructure{
public:   
    LighthavenSamaritan();
   ~LighthavenSamaritan();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   //void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif