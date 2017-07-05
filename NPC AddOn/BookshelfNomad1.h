#include <NPCStructure.h>

#ifndef __BOOKSHELFNOMAD1_H
#define __BOOKSHELFNOMAD1_H

class BookshelfNomad1 : public NPCstructure{
public:   
   BookshelfNomad1();
   ~BookshelfNomad1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif