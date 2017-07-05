// PrincessDelilan.h: interface for the Princess Delilah class.
//
//////////////////////////////////////////////////////////////////////

#include "NPCstructure.h"

class PrincessDelilah : public NPCstructure  
{
public:
	PrincessDelilah();
	virtual ~PrincessDelilah();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};


