#include "NPCStructure.h"

#ifndef __THORGLAREFIRE_H
#define __THORGLAREFIRE_H

class ThorGlarefire : public NPCstructure{
public:   
    ThorGlarefire();
   ~ThorGlarefire();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif
