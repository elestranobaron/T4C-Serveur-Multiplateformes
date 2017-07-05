#include <NPCStructure.h>

#ifndef __BOOKSHELFNOMAD2_H
#define __BOOKSHELFNOMAD2_H

class BookshelfNomad2 : public NPCstructure{
public:   
   BookshelfNomad2();
   ~BookshelfNomad2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
   void OnAttacked( UNIT_FUNC_PROTOTYPE );
   void OnInitialise( UNIT_FUNC_PROTOTYPE );

};

#endif