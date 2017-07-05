// Book.cpp: implementation of the Book class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Book.h"

#include "..\TFCPacket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Book::Book()
{

}

Book::~Book()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Using a book causes it to display its text, therefore it has a very special OnUse function..
void Book::OnUse( UNIT_FUNC_PROTOTYPE ){
	ObjectStructure::OnUse( UNIT_FUNC_PARAM );

	DWORD &itemUsed = *(DWORD *)( valueOUT );

	// Displays its super text! .. how ..
	if(!text.csText.IsEmpty()){
		// medium happens to be the unit that used the book.
		// If it's a PC, then we make the PC read what the book has to say!!
		if(medium->GetType() == U_PC){
			Character *charPlayer;
			// A PC handles message bizzarly, but this message returns the Character structure fine.
			charPlayer = static_cast<Character *>( medium );			

			// Then get the player structure behind the character
			Players *plPlayer = charPlayer->GetPlayer();
			if(plPlayer){
				itemUsed = TRUE;
				// Then access the player's mailbox
				// Lock the player to avoid thread conflicts (this shouldn't cause a hang..)
				plPlayer->Lock();
				
				TFCPacket sending;
				// And do the forbidden, access the player's message inside the DLL and send one.
				sending << (RQ_SIZE)RQ_IndirectTalk;
				sending << (long)self->GetID();
				sending << (char)25;
				sending << (short)text.csText.GetLength();
				sending << (CString)text.csText;
								
				plPlayer->self->SendPlayerMessage( sending );
				
				// Unlocks the player
				plPlayer->Unlock();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
ObjectStructure *Book::CreateObject( void ){
	return new Book;
}