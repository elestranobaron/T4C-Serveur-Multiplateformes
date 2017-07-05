#include "NPCStructure.h"

#ifndef __DARANATROCITY_H
#define __DARANATROCITY_H

class DaranAtrocity: public NPCstructure{
public:    
    DaranAtrocity();
   ~DaranAtrocity();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

    
};														  


#endif

