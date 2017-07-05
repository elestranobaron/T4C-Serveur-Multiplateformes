#include "NPCStructure.h"

#ifndef __WITCHDOCTORKWARLGLOTH_H
#define __WITCHDOCTORKWARLGLOTH_H

class WitchDoctorKwarlgloth : public NPCstructure{
public:   
    WitchDoctorKwarlgloth();
   ~WitchDoctorKwarlgloth();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
	 	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

    
};

#endif
