#include "NPCStructure.h"

class Theopold : public NPCstructure{
public:   
    Theopold();
   ~Theopold();
    void Create( void );
    void OnTalk( UNIT_FUNC_PROTOTYPE );
};
