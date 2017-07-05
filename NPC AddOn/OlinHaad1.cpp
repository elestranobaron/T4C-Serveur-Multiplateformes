#pragma hdrstop
#include "OlinHaad1.h"

OlinHaad1::OlinHaad1()
{}

OlinHaad1::~OlinHaad1()
{}

extern NPCstructure::NPC OlinHaad1NPC;

void OlinHaad1::Create( ){
	npc = OlinHaad1NPC;
	SET_NPC_NAME( "[12758]Olin Haad");
	npc.InitialPos.X = 2973;
	npc.InitialPos.Y = 1346;
	npc.InitialPos.world = 0;
}

void OlinHaad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OlinHaad1::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Fight = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 2)
	Conversation
	INTL( 12458, "I do not talk to rats. Leave now before I turn you into one of my undead servants!")
	BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 4)
	IF(CheckFlag(__FLAG_ADDON_NUMBER_OF_OLIN_HAAD_GUARDS_KILLED) > 19)
		Conversation
		INTL( 12459, "So you're the worthless bug my men have been talking about. You do not look all that "
		"dangerous to me. Are you really special like they say you are? I doubt it... You don't look "
		"like the type that will \"fight\" in exchange for what you are \"seeking\".")
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 3)
	ELSE
		Conversation
		INTL( 12460, "I do not talk to rats. You are fortunate that I am in a good mood today, as I will let you go.")
		IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 2)
			GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 3)
		ENDIF
		BREAK
	ENDIF
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12461, "I am pleased to see that you have survived this little ordeal. I had to make certain that "
	"you are indeed what \"they\" say you are.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
	Conversation
	INTL( 12462, "I already told you... tell the high priest to give me what was promised or I won't stop until the "
	"entire town is ground to dust!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 23)
	Conversation
	INTL( 12463, "Well? Do you have the stone? No? Then I have nothing to discuss with you, unless of course you wish "
	"to become an undead...")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 23)
	Conversation
	INTL( 12464, "Well well, the prodigal child returns. I trust you enjoyed your visit to the temple of Corruption? "
	"I learned that you met with an associate of mine... a man that went by the name of \"Nomad\".")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 36)
	Conversation
	INTL( 12465, "So, you survived my guards... Begone now, you insect! Tell your priest that I will take his miserable "
	"life if he continues to deny me the Heartstone!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 36)
	Conversation
	INTL( 12466, "Ha ha ha! So now you know what I want, pawn. You're but a fool to think that you can make a difference. "
	"I will dispose of you the same way disposed of the high priest's wife. You're nothing but a weakling, "
	"a miserable excuse for a puppet! I \"dare\" you to stop me if you can... ha ha ha!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 37)
	Conversation
	INTL( 12467, "Ha ha ha! That was quite amusing if I do say so myself. So now you know that I am \"invincible\"!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 38)
	Conversation
	INTL( 12468, "Get out of my sight! I told you before, tell the high priest to reveal the location of the temple of "
	"Lothar to me or I will kill everyone in his miserable little town!")
ELSE
	Conversation
	INTL( 12469, "I told you... I'm INVINCIBLE!!! Ahahahahahahahahhaha!")
ENDIF

Command(INTL( 4045, "FIGHT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 3)
	Conversation
	INTL( 12470, "That is what I was told to do, but I was duped. Don't worry, I will not do the \"same\" to you. It is "
	"just what we call the big picture.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command2(INTL( 12472, "SEEK"), INTL( 12473, "SAME"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 3)
	Conversation
	INTL( 12474, "Are you not the one sent by the king? The New Breed of Altheans, the ones who carry in their blood "
	"the rage of those who have fallen? But I am getting ahead of myself. I would like to see what you "
	"are made of. What do you say? Will you fight to get the answers you seek?")
	SetYesNo(Fight)
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

YES(Fight)
	Conversation
	INTL( 12475, "Wonderful! Here we go... oh, did I mention it was to the death? Hahaha!")
	TELEPORT(1825, 2550, 1)
	BREAK
NO(Fight)
	Conversation
	INTL( 12476, "I have no time to waste on you... guards! Dispose of him!")
	TELEPORT(1825, 2550, 1)
	BREAK
YesNoELSE(Fight)
	Conversation
	INTL( 12476, "I have no time to waste on you... guards! Dispose of him!")
	TELEPORT(1825, 2550, 1)
	BREAK

Command(INTL( 12477, "THEY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12478, "The Council of the Eight. No one knows exactly who they are, but it can't be good seeing as they "
	"intervene only in matters concerning the \"Harbinger\".")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 4194, "HARBINGER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12479, "The Harbinger of Death. The god that is mentioned in the \"prophecy\" of the Fourth Coming.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12064, "PROPHECY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12480, "It is said that Death will one day plant into the world the \"Seeds\" of Decay. Once fully grown, these "
	"seeds will harvest Life and shape the land in preparation for \"His\" arrival.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12481, "HIS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12482, "Why, the Harbinger, of course.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12483, "SEEDS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12484, "Each of these seeds will contain the rage of the dead races that were destroyed in the name of pride. "
	"The Council of the Eight believes that \"you\" are such a seed.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command2(INTL( 8710, "YOU"), INTL( 12485, "ME"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12486, "You are what we call the \"New\" \"Breed\". In your veins flows the blood of the elves, the orks and "
	"the dwarves of the past.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

CmdAND(INTL( 12487, "NEW"), INTL( 12488, "BREED"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12489, "Interesting story, don't you think? Now then, I believe that I have \"answered\" all your questions.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 691, "UNDEAD"))
INTL( 12490, "I can never have enough undead at my service.")

Command(INTL( 5994, "ANSWER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 4)
	Conversation
	INTL( 12491, "Why did I tell you all this? The answer is quite simple actually. I did it for revenge. Knowledge is "
	"power, my friend... remember that. Now, I want you to do something for me. Tell that damned high priest "
	"in the Temple of Lighthaven, Gunthar, to give me what I was promised or I will not leave until all the "
	"people of this town become part of my staff of undead! Now, if you will excuse me, I have things to do.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 5)
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 11802, "NOMAD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 23)
	Conversation
	INTL( 12492, "The fool thought the Heartstone to be a mere piece of rock, while it is much more than that... Huh? What is "
	"that you carry? A \"Darkstone\"? This is not what I am looking for. This stone has no value to me whatsoever.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12493, "DARKSTONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 23)
	Conversation
	INTL( 12494, "Oh, I understand now. The priest sent you here to hurt me with that, did he? Hah! Go tell your priest that "
	"I will take his miserable life if he still insists on denying me the \"Heartstone\".")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12187, "HEARTSTONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 23)
	Conversation
	INTL( 12495, "You do not know what the Heartstone is? You should ask your high priest, as he knows more about it that "
	"anyone else. But beware, even though he is a priest of Artherk, he schemes and \"lies\" more than Ogrimar "
	"himself.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12496, "LIES"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 23)
	Conversation
	INTL( 12497, "Enough of this... guards! Dispose of him and send his remains to the priest! Maybe that will change his mind.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 24)
	CastSpellTarget(__SPELL_OLIN_HAAD_TELEPORT_2)
	SUMMON("Olin Haad Private Guard", 2962, 1348)
	SUMMON("Olin Haad Private Guard", 2962, 1348)
	SUMMON("Olin Haad Private Guard", 2962, 1348)
	BREAK
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12498, "DARE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 36)
	Conversation
	INTL( 12499, "I will crush you like an ant!")
	CastSpellTarget(__SPELL_OLIN_HAAD_TELEPORT_3)
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 10498, "INVINCIBLE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 37)
	Conversation
	INTL( 12500, "In my veins flows the power of my lord Gluriurl. He has chosen me to be the \"Herald\" of my master "
	"Makrsh P'Tangh.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12501, "HERALD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 37)
	Conversation
	INTL( 12502, "Centuries ago, my master created a group comprised of the most powerful archmages of Althea. This group, "
	"which you know as the Obsidian Conclave, was to find a way to \"destroy\" everything that was dear to the "
	"gods.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12503, "DESTROY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 37)
	Conversation
	INTL( 12504, "They wreaked havoc everywhere they went. One day, when the Obsidian Conclave was conquering the island of "
	"Stoneheim, we dragons intervened and it was at that moment that I first found a dark stone. I later learned "
	"that it was the Heart of a god named Gluriurl. At the time I did not know what it was, but it was not long "
	"before I started to hear the \"soothing\" \"voice\".")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

CmdAND(INTL( 12505, "SOOTH"), INTL( 12506, "VOICE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 37)
	Conversation
	INTL( 12507, "My lord Gluriurl was talking to me. He said that I had been chosen to serve the Obsidian Conclave under "
	"Makrsh P'Tangh, and that in my master I would find the strength to conquer those who have "
	"forsaken us. He also told me that in time, once I have gathered all his \"remains\", I would be the one "
	"to wake him from his slumber.")
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 12508, "REMAIN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 37)
	Conversation
	INTL( 12509, "I now have his skull, his ribcage and his heart! Do not be surprised, the Darkstone you have in your "
	"possession is the Heart of Artherk, not Gluriurl. All I need to do is find a way inside the temple "
	"of Lothar to get my lord's essence. Now, begone and for the last time, tell your high priest Gunthar "
	"that I will not hesitate to slay everyone in this town if he doesn't tell me where the entrance to the "
	"temple is located!")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 38)
ELSE
	Conversation
	INTL( 12471, "Do not waste my time with useless banter.")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12510, "I am known as Olin Haad.")

Command2(INTL( 11925, "OLIN"), INTL( 11926, "HAAD"))
INTL( 7109, "Yes, that's me.")

Command(INTL( 489, "WORK"))
INTL( 12511, "I don't see how this is any business of yours.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12512, "Leaving so soon? Such a pity.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 1791, "I don't know.")
ELSE
	Conversation
	INTL( 12513, "I'm not sure what you mean by that.")
ENDIF

EndTalk
}





