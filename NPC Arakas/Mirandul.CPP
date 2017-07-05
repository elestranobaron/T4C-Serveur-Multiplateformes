#pragma hdrstop
#include "Mirandul.H"

Mirandul::Mirandul()
{}

Mirandul::~Mirandul()
{}

extern NPCstructure::NPC Male_Brigand;

void Mirandul::Create( void )
{
	npc = ( Male_Brigand );
	SET_NPC_NAME( "[2904]Mirandul" );
	npc.InitialPos.X = 2193; // Brigand Camp
	npc.InitialPos.Y = 1234;
	npc.InitialPos.world = 0;
}

void Mirandul::OnTalk( UNIT_FUNC_PROTOTYPE )

{
InitTalk

Begin INTL( 963, "Hmpft! Have you learned to \"fly\" or what!?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 964, "Mirandul, the fastest \"thief\" who ever lived.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 965, "I make sure that nobody steals the treasures we get.")

Command(INTL( 523, "ANNABELLE"))
INTL( 665, "I heard a rumor that she is much older than what she appears to be.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 966, "FLY"))
INTL( 967, "Not long ago, I had flying boots. They were very useful, but I had to give "
"them away to save my life. I think they were forever lost in the ocean.")

Command(INTL( 968, "FAST"))
INTL( 969, "You will never be as fast as I was.")

Command(INTL( 970, "THIEF"))
INTL( 971, "I am not a thief anymore, but a brigand. I know I do not look very fast "
"now, but you would be surprised of my feats four years ago.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 972, "As if I care.")
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 974, "Uh? I really don't have a clue what you're talking about.")

EndTalk
}
