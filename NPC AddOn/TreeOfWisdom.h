#include "NPCStructure.h"

#ifndef __TREEOFWISDOM_H
#define __TREEOFWISDOM_H

class TreeOfWisdom : public NPCstructure{
public:
	TreeOfWisdom();
	~TreeOfWisdom();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked ( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif