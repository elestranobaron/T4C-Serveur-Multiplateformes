#include "NPCStructure.h"

#ifndef __CHRYSEIDAYOLANGDA_H
#define __CHRYSEIDAYOLANGDA_H

class ChryseidaYolangda: public NPCstructure{
public:   
   ChryseidaYolangda();
   ~ChryseidaYolangda();
   void Create( void );
   void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif
