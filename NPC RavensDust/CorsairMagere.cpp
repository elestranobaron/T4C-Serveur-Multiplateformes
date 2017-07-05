#pragma hdrstop
#include "CorsairMagere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CorsairMagere::CorsairMagere()
{}

CorsairMagere::~CorsairMagere()
{}

extern NPCstructure::NPC CorsairTheowaldNPC;
 
void CorsairMagere::Create(){
        npc = CorsairTheowaldNPC;
        SET_NPC_NAME( "[2938]Corsair Leodwald" );
        npc.InitialPos.X = 1615;
        npc.InitialPos.Y = 2635;
        npc.InitialPos.world = 0;
}

void CorsairMagere::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 4601, "What? What do you want friend? We've got \"work\" to do.")

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4602, "I am Leodwald but I ask of my men to call me Corsair Leodwald.")

Command(INTL( 4603, "CORSAIR LEODWALD"))
INTL( 4604, "Ah! You're a swift learner.")

Command(INTL( 4420, "LEOWALD"))
INTL( 4605, "Not Leowald you hammerhead! It's Corsair Leodwald!")

Command(INTL( 2707, "PIRATE"))
INTL( 4606, "We do not encounter many pirates these days. Mainly because our fleet "
"is not \"suitable\" to sail right now.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 4607, "As I have said, I am Corsair Leodwald and my duty is to lead the royal "
"fleet of our *ugh* \"Majesty\".")

Command(INTL( 4608, "SUITABLE"))
INTL( 4609, "Aye, \"King\" \"Theodore\" does not want to invest gold pieces for the "
"restoration of our old vessels.")

Command2(INTL( 754, "THEODORE"),INTL( 3990, "MAJESTY"))
INTL( 4610, "King Theodore is unworthy of the royal throne but I will serve him no "
"matter the circumstances.")

Command(INTL( 753, "GOLDMOON"))
INTL( 4611, "The kingdom of Goldmoon is ruled so-to-speak by \"King\" \"Theodore\".")

Command(INTL( 2705, "HAROCK"))
INTL( 4612, "Count on Harock Harr for exagerating everything.") 

Command(INTL( 4613, "BRADOCK"))
INTL( 4614, "I think he's \"Harock\" \"Harr\"'s younger brother.")

Command2(INTL( 4615, "HAR"),INTL( 4616, "PARROT"))
INTL( 4617, "I am not of the har-har generation. Oh, I almost forgot... I hate parrots!")

Command(INTL( 1581, "SHADEEN"))
INTL( 4618, "Ah, now *there's* a lovely lass! All curves and spunk, just like I like 'em wenches! "
"I hear she's the reason why that moron Monsignore Damien fell from grace in the church. "
"She told me all about how she framed him, and that was pretty shrewd, let me tell you. "
"If you ever meet that idiot Damien, you just ask him about \"Shadeen\".")

Command(INTL( 4422, "IRONLEG"))
INTL( 4619, "Captain Ironleg taught me everything I know. He does not deserve all "
"the credits however. I have trained myself day and night to become the "
"man I am. I am proud today to say that my swordsman skills are unmatched in "
"all \"Raven's\" \"Dust\". ")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 4620, "Raven's Dust has many dangerous reefs surrounding it. Our boats often "
"get damaged by them. Some of our crewmen are not very much experienced.")

Command(INTL( 914, "WEAPON"))
INTL( 4621, "I usually carry a cutlass and a small dagger. You never know what could "
"happen in these troubled times.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4622, "You're unworthy to speak to me. Out of my sight at once!") BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 4623, "Fine! I have work to do.") BREAK

Default
INTL( 4624, "How the hell should I know about that?")

EndTalk
}