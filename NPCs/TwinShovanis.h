#include "NPCStructure.h"

#ifndef __TWINSHOVANIS_H
#define __TWINSHOVANIS_H

class TwinShovanis : public NPCstructure{
public:   
        TwinShovanis();
       ~TwinShovanis();

   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
