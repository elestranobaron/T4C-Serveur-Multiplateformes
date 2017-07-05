// MonsignorDamien.h: interface for the MonsignorDamien class.
//
//////////////////////////////////////////////////////////////////////

#include "NPCStructure.h"

#ifndef __MonsignorDamien_H
#define __MonsignorDamien_H

class MonsignorDamien : public NPCstructure{
public:   
    MonsignorDamien();
   ~MonsignorDamien();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );	
};

#endif
