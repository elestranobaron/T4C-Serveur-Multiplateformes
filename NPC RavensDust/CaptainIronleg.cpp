/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "CaptainIronleg.H"

CaptainIronleg::CaptainIronleg()
{}

CaptainIronleg::~CaptainIronleg()
{}

extern NPCstructure::NPC Peasant;

void CaptainIronleg::Create( void )
{
      npc = ( Peasant );
      SET_NPC_NAME( "[2934]Captain Ironleg" );  
      npc.InitialPos.X = 1619; 
      npc.InitialPos.Y = 2623;
      npc.InitialPos.world = 0;
}

void CaptainIronleg::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
InitTalk

Begin
INTL( 4416, "Oy laddie! You almost surprised me.")


Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4417, "I am the great Captain Ironleg. In my youth, I have fought pirates and "
"thieves with my unbreakable \"cutlass\". I tell ya, nothing could have "
"stopped me then.")

Command(INTL( 489, "WORK"))
INTL( 4418, "I am too old to sail for adventures nowadays. Instead, I teach the "
"apprentice sailors about the ways of sailing. I am proud to say that "
"I was the teacher of Corsair Leodwald, my best student ever.") 

Command2(INTL( 4419, "CORSAIR"),INTL( 4420, "LEOWALD"))
INTL( 4421, "Corsair Leowald is a very talented young sailor who shall go far "
"on the sea.")

Command(INTL( 4422, "IRONLEG"))
INTL( 4423, "You want to see my iron leg? It's a great piece indeed. Oh, I know, it's "
"a bit rusty but it is still strong enough to support most of my weight. "
"I looted it from the corpse of a pirate I slew with my \"cutlass\".") 

CmdAND(INTL( 4424, "IRON"),INTL( 4425, "LEG"))
INTL( 4426, "You want to see my iron leg? It's a great piece indeed. Oh, I know, it's "
"a bit rusty but it is still good enough. I looted it from the corpse "
"of a pirate I slew with my \"cutlass\".") 

Command(INTL( 4427, "CUTLASS"))
INTL( 4428, "Like I said lad, this cutlass saved my life numerous times. Aye, I even "
"fought sharks with it.")

Command(INTL( 4429, "HARR"))
INTL( 4430, "Harr... I'm not the har-har type ya know laddie!")

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 4431, "I heard you can drown in a desert too. Ha!")

Command(INTL( 4432, "SEA"))
INTL( 4433, "The sea is always hungry. She can eat \"ships\" and their crew all day long.")

Command2(INTL( 1011, "BOAT"),INTL( 4434, "SHIP"))
INTL( 4435, "Ah lad! I see you're interested in boats. Sadly, King Theodore "
"does not think it's that important to keep the vessels in good condition. ")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 4436, "If I'd be younger, I would make you walk the plank into the sea!")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4437, "Farewell lad.") BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1) 
   Conversation
   INTL( 4438, "Now that's something I did not know.")
ELSE
   Conversation
   INTL( 4439, "Perhaps I should give a thought about that.")
ENDIF

EndTalk
}


