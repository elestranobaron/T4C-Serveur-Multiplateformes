#include "NPCStructure.h"

class Brother2 : public NPCstructure{
public:   
    Brother2();
   ~Brother2();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};
