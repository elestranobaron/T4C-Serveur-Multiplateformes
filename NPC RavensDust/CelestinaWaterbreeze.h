#include "NPCStructure.h"

#ifndef __CELESTINAWATERBREEZE_H
#define __CELESTINAWATERBREEZE_H
     
class CelestinaWaterbreeze : public NPCstructure{
public:   
	CelestinaWaterbreeze();
	~CelestinaWaterbreeze();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE ); 
};

#endif
