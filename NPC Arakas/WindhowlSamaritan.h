#include "NPCStructure.h"

#ifndef __WINDHOWL_SAMARITAN_H
#define __WINDHOWL_SAMARITAN_H

class WindhowlSamaritan : public NPCstructure{
public:   
    WindhowlSamaritan();
   ~WindhowlSamaritan();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   //void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
