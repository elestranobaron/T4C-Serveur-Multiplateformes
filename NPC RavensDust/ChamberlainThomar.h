// ChamberlainThomar.h: interface for the ChamberlainThomar class.
//
//////////////////////////////////////////////////////////////////////

#include "NPCstructure.h"

class ChamberlainThomar : public NPCstructure  
{
public:
	ChamberlainThomar();
	virtual ~ChamberlainThomar();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};
