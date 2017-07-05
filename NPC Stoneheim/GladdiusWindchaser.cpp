#pragma hdrstop
#include "GladdiusWindchaser.h"

GladdiusWindchaser::GladdiusWindchaser()
{}

GladdiusWindchaser::~GladdiusWindchaser()
{}

extern NPCstructure::NPC GladdiusWindchaserNPC;

void GladdiusWindchaser::Create( ){
	npc = GladdiusWindchaserNPC;
   SET_NPC_NAME(   "[10854]Gladdius Windchaser" );
	npc.InitialPos.X = 935;
	npc.InitialPos.Y = 975;
	npc.InitialPos.world = 0;
}

void GladdiusWindchaser::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 8233, "You are addressing the mighty Gladdius, Windchaser of the Bata clan!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8234, "I have told you before, my name is Gladdius.")

Command(INTL( 8017, "GLADDIUS"))
INTL( 8235, "Yes, I am Gladdius! What do you want from me?")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 8236, "I have no idea what you want, but as long as you keep your nose clean and stay out of "
"our affairs, you're okay with me. I'm busy enough keeping an eye on that \"Zion\" \"Thunderheart\" "
"fellow without having to worry about you strangers.")

Command2(INTL( 8001, "ZION"),INTL( 8002, "THUNDERHEART"))
INTL( 8237, "Careful what you do or say around him. He's a tricky fellow, very ambitious and dangerous. "
"We don't have anything on him, but we'll get him yet. Meanwhile, stay away from him or "
"bad things may happen to you. Don't say I didn't warn you!")

Command2(INTL( 8005, "KYATHOS"),INTL( 8006, "SHATTERSKULL"))
INTL( 8238, "He's another guard, like me. Don't get in our way, we have big fish to take care of.")

Command2(INTL( 8009, "THOR"),INTL( 8010, "GLAREFIRE"))
INTL( 8239, "He's a manasmith. If you want special armors, he's the one you should talk to. Not all his "
"armors might fit you, though, but some of his weapons might be more your size.")

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
INTL( 8240, "He's a little weak by Centaur standards, but he's got a good heart and he worships Artherk. "
"He may not look like much, but I wouldn't underestimate him if I were you. Without his influence, "
"we Centaurs would probably be at each other's throats. He's very wise, that's for sure.")

Command2(INTL( 8046, "MALACHAI"),INTL( 8047, "FATEBRINGER"))
INTL( 8241, "He's a manaweaver. There's about one manaweaver for every one hundred Centaurs, so that's pretty rare. "
"I'm told he keeps to himself and does very powerful items at very high cost.")

Command2(INTL( 1072, "KING"),INTL( 7998, "GRAVESOUL"))
INTL( 8242, "King Aedenas Gravesoul is a strong and honorable king. We're all very loyal to him... except \"Zion\" "
"\"Thunderheart\", of course.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8243, "I stand guard here to protect the town.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8244, "Say one more word and you'll feel the edge of my sword!") BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8245, "Goodbye then.") BREAK

Default
INTL( 8246, "You speak strange words, traveler. I cannot understand any of them.")

EndTalk
}