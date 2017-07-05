//////////////////////////////////////////////////////////////////////
// Menark.cpp: implementation of the Menark class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include <complex>
#include "Menark.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Menark::Menark()
{}

Menark::~Menark()
{}

extern NPCstructure::NPC Mage;

void Menark::Create( ){
    npc = Mage;
        SET_NPC_NAME( "[2966]Menark" );
    npc.InitialPos.X = 1387;//2862;//1342;
    npc.InitialPos.Y = 2397;//125;//2383;
        npc.InitialPos.world = 0;//4;//0;
}

void Menark::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT THREAT = 1;
CONSTANT STUDY = 2;
CONSTANT HINT = 3;
CONSTANT PAY = 4;
CONSTANT HOURGLASS = 5;

InitTalk

Begin
""
IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) == CheckFlag(__FLAG_SHADEEN_PLAYER_B)) && (CheckFlag(__FLAG_SHADEEN_PLAYER_B) !=0))
        Conversation
        INTL( 5422, "So, you're the one who's just robbed the bank, eh? I do not speak with thieves!")
        BREAK
ELSEIF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
        Conversation
        INTL( 5423, "Ahh, another \"visitor\"!")
ELSE
        Conversation
        INTL( 5424, "Greetings, what may I do for you?")
ENDIF

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5425, "My name is Menark.")

Command(INTL( 5276, "MENARK"))
INTL( 4024, "That is my name.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 5426, "I am what you might call a chronicler. \"Jeremiah\" and I have been charged with the "
"never-ending task of gathering knowledge from all over the world and keeping \"records\" "
"of his \"journeys\" here.")

Command2(INTL( 5427, "CHRONICLES OF DOOM"),INTL( 5428, "CHRONICLE OF DOOM"))
""
IF (CheckFlag(__FLAG_SHADEEN_PLAYER_A) != 0)
        IF (USER_GENDER == GENDER_MALE)
                Conversation
                INTL( 5429, "Who told you about the Chronicles of Doom? Shadeen... I see! I assume she sent you here to try "
                "to get it from me, right? Are you actually threatening me, boy?")
                SetYesNo(THREAT)
        ELSE
                Conversation
                INTL( 5430, "Who told you about the Chronicles of Doom? Shadeen... I see! I assume she sent you here to try "
                "to get it from me, right? Are you actually threatening me, girl?")
                SetYesNo(THREAT)
        ENDIF
ELSE
        Conversation
        INTL( 5431, "I'm sorry, I don't know what you are talking about.")
ENDIF

YES(THREAT)
IF (CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED_BY) == CheckFlag(__FLAG_SHADEEN_PLAYER_A) )
    IF(CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) > CurrentRound)
        Conversation
        INTL( 5432, "GUARDS! GUARDS! ... .. Ack!!! Where the hell are the guards when you need them?! "
        "All right, you win, thief! Take the \"Chronicles\" \"of\" \"Doom\" and leave me be!")
        GiveFlag(__FLAG_SHADEEN_PLAYER_A, 16) // PLAYER_A has been marked with '16'.
        GiveFlag(__QUEST_SEEK_SHADEEN,5)
        GiveItem(__OBJ_CHRONICLES_OF_DOOM)
    ELSE
        IF (USER_GENDER == GENDER_MALE)
                Conversation
                INTL( 13032, "You were TOO SLOW. Say hello to the rats on my behalf. GUARDS!! Arrest this man immediately!")
                TELEPORT( 194,2360, 1)
                BREAK
        ELSE
                Conversation
                INTL( 13033, "You were TOO SLOW. Say hello to the rats on my behalf. GUARDS!! Arrest this woman immediately!")
                TELEPORT( 194,2360, 1)
                BREAK
        ENDIF
    ENDIF
ELSE
        IF (USER_GENDER == GENDER_MALE)
                Conversation
                INTL( 5433, "This isn't nice. Say hello to the rats on my behalf. GUARDS!! Arrest this man immediately!")
                TELEPORT( 194,2360, 1)
                BREAK
        ELSE
                Conversation
                INTL( 5434, "This isn't nice. Say hello to the rats on my behalf. GUARDS!! Arrest this woman immediately!")
                TELEPORT( 194,2360, 1)
                BREAK
        ENDIF
ENDIF

NO(THREAT)
Conversation
INTL( 5435, "Good. You'll live longer if you do not threaten people.")

YesNoELSE(THREAT)
Conversation
INTL( 5436, "I say again, are you threatening me?")
SetYesNo(THREAT)

Command(INTL( 3918, "VISITOR"))
""
IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
        Conversation
        INTL( 5437, "I have had many visitors lately, but the one that was just here struck me as "
        "being rather \"odd\".")
ELSE
        Conversation
        INTL( 5431, "I'm sorry, I don't know what you are talking about.")
ENDIF

// MENARK_WANTS_A_POTION
// 1 = Light healing potion
// 2 = Mana elixir
// 3 = Scroll of recall
// 4 = Potion of fury
// 5 = Flask of crystal water

CmdAND(INTL( 10111, "HOURGLASS"),INTL( 10112, "ESSENCE"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1)
        IF (CheckFlag(__MENARK_WANTS_A_POTION) == 0)
                ;int iPotionMenark = rnd.roll(dice(1,5));
                GiveFlag(__MENARK_WANTS_A_POTION, iPotionMenark)
        ENDIF
        Conversation
        INTL( 10127, "So, you need an Hourglass of Essence, eh?")
        SWITCH(CheckFlag(__MENARK_WANTS_A_POTION))
                CASE(1)
                        Conversation
                        INTL( 10128, " Very well, then. I'd be willing to give you one in return for a "
                        "light healing potion.")
                        IF (CheckItem(__OBJ_LIGHT_HEALING_POTION) >= 1)
                                Conversation
                                INTL( 10129, " Ah, I see that you already have a light healing potion in your possession. "
                                "Would you want to trade it for one of my hourglasses?")
                                SetYesNo(HOURGLASS)
                        ENDIF
                ENDCASE
                CASE(2)
                        Conversation
                        INTL( 10130, " Very well, then. I'd be willing to give you one in return for a mana elixir.")
                        IF (CheckItem(__OBJ_MANA_ELIXIR) >= 1)
                                Conversation
                                INTL( 10131, " Ah, I see that you already have a mana elixir in your possession. "
                                "Would you want to trade it for one of my hourglasses?")
                                SetYesNo(HOURGLASS)
                        ENDIF
                ENDCASE
                CASE(3)
                        Conversation
                        INTL( 10132, " Very well, then. I'd be willing to give you one in return for a scroll of recall.")
                        IF (CheckItem(__OBJ_SCROLL_OF_RECALL) >= 1)
                                Conversation
                                INTL( 10133, " Ah, I see that you already have a scroll of recall in your possession. "
                                "Would you want to trade it for one of my hourglasses?")
                                SetYesNo(HOURGLASS)
                        ENDIF
                ENDCASE
                CASE(4)
                        Conversation
                        INTL( 10134, " Very well, then. I'd be willing to give you one in return for a potion of fury.")
                        IF (CheckItem(__OBJ_POTION_OF_FURY) >= 1)
                                Conversation
                                INTL( 10135, " Ah, I see that you already have a potion of fury in your possession. "
                                "Would you want to trade it for one of my hourglasses?")
                                SetYesNo(HOURGLASS)
                        ENDIF
                ENDCASE
                CASE(5)
                        Conversation
                        INTL( 10446, " Very well, then. I'd be willing to give you one in return for a flask of crystal water.")
                        IF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 1)
                                Conversation
                                INTL( 10136, " Ah, I see that you already have a flask of crystal water in your possession. "
                                "Would you want to trade it for one of my hourglasses?")
                                SetYesNo(HOURGLASS)
                        ENDIF
                ENDCASE
                OTHERWISE
         PRIVATE_SYSTEM_MESSAGE(INTL( 10137, "[ERROR MENARK1.0] This text should not appear. If you see it, please report it to Vircom."))
                ENDCASE
        ENDSWITCH
ELSE
        Conversation
        INTL( 10138, "I do not deem you worthy of having one of these, unless you become a Lightbringer of Artherk.")
ENDIF

YES(HOURGLASS)
SWITCH(CheckFlag(__MENARK_WANTS_A_POTION))
        CASE(1)
                IF (CheckItem(__OBJ_LIGHT_HEALING_POTION) >= 1)
                        TakeItem(__OBJ_LIGHT_HEALING_POTION)
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10139, "You give a light healing potion to Menark."))
                        Conversation
                        INTL( 10140, "Thank you.")
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10141, "Menark gives you an Hourglass of Essence."))
                        RemFlag(__MENARK_WANTS_A_POTION)
                        GiveItem(__OBJ_HOURGLASS_OF_ESSENCE)
                ELSE
                        Conversation
                        INTL( 10142, "Sorry, I cannot be fooled that easily.")
                        BREAK
                ENDIF
        ENDCASE
        CASE(2)
                IF (CheckItem(__OBJ_MANA_ELIXIR) >= 1)
                        TakeItem(__OBJ_MANA_ELIXIR)
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10143, "You give a mana elixir to Menark."))
                        Conversation
                        INTL( 10140, "Thank you.")
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10141, "Menark gives you an Hourglass of Essence."))
                        RemFlag(__MENARK_WANTS_A_POTION)
                        GiveItem(__OBJ_HOURGLASS_OF_ESSENCE)
                ELSE
                        Conversation
                        INTL( 10142, "Sorry, I cannot be fooled that easily.")
                        BREAK
                ENDIF
        ENDCASE
        CASE(3)
                IF (CheckItem(__OBJ_SCROLL_OF_RECALL) >= 1)
                        TakeItem(__OBJ_SCROLL_OF_RECALL)
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10144, "You give a scroll of recall to Menark."))
                        Conversation
                        INTL( 10140, "Thank you.")
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10141, "Menark gives you an Hourglass of Essence."))
                        RemFlag(__MENARK_WANTS_A_POTION)
                        GiveItem(__OBJ_HOURGLASS_OF_ESSENCE)
                ELSE
                        Conversation
                        INTL( 10142, "Sorry, I cannot be fooled that easily.")
                        BREAK
                ENDIF
        ENDCASE
        CASE(4)
                IF (CheckItem(__OBJ_POTION_OF_FURY) >= 1)
                        TakeItem(__OBJ_POTION_OF_FURY)
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10145, "You give a potion of fury to Menark."))
                        Conversation
                        INTL( 10140, "Thank you.")
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10141, "Menark gives you an Hourglass of Essence."))
                        RemFlag(__MENARK_WANTS_A_POTION)
                        GiveItem(__OBJ_HOURGLASS_OF_ESSENCE)
                ELSE
                        Conversation
                        INTL( 10142, "Sorry, I cannot be fooled that easily.")
                        BREAK
                ENDIF
        ENDCASE
        CASE(5)
                IF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 1)
                        TakeItem(__OBJ_FLASK_OF_CRYSTAL_WATER)
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10146, "You give a flask of crystal water to Menark."))
                        Conversation
                        INTL( 10140, "Thank you.")
                        PRIVATE_SYSTEM_MESSAGE(INTL( 10141, "Menark gives you an Hourglass of Essence."))
                        RemFlag(__MENARK_WANTS_A_POTION)
                        GiveItem(__OBJ_HOURGLASS_OF_ESSENCE)
                ELSE
                        Conversation
                        INTL( 10142, "Sorry, I cannot be fooled that easily.")
                        BREAK
                ENDIF
        ENDCASE
ENDSWITCH

NO(HOURGLASS)
        Conversation
        INTL( 8220, "Come back if you ever change your mind.")

YesNoELSE(HOURGLASS)
        Conversation
        INTL( 10147, "Well, do you want to the trade or not?")
        SetYesNo(HOURGLASS)

Command(INTL( 5438, "ODD"))
""
IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
        Conversation
        INTL( 5439, "I'm affraid I must get back to my writing so I can't really help you with that. Why don't "
        "you just ask around? You might get more information with the other townsfolk.")
ELSE
        Conversation
        INTL( 5431, "I'm sorry, I don't know what you are talking about.")
ENDIF

Command(INTL( 5272, "JEREMIAH"))
INTL( 5440, "He's a charming fellow to tell you the truth, but don't tell him I said that!")

Command(INTL( 5280, "RECORD"))
INTL( 5441, "We keep records of all knowledge so that others might one day look through these pages "
"and learn about the many different parts of the world.")

Command(INTL( 5442, "JOURNEY"))
INTL( 5443, "Jeremiah has very poor handwriting and so gets to do most of the travelling. Even though "
"I am accustomed to living indoors, I still long to go outside. Still, I dare "
"not travel where mummies and skeletons are living. I have heard that "
"they feast upon the warm blood of humans. If you could bring me "
"some mummy's bandages and a skeleton bone, perhaps I could "
"\"study\" these beings.")

Command(INTL( 5444, "STUDY"))
""
IF ((CheckItem(__OBJ_SKELETON_BONE) >= 1) && (CheckItem(__OBJ_MUMMY_BANDAGES) >= 1))
        Conversation
        INTL( 5445, "You've found a skeleton bone and some mummy's bandages? Do you "
        "want to give them to me so that I can study the undead's "
        "mysterious nature?")
        SetYesNo(STUDY)
ELSE
        Conversation
        INTL( 5446, "I need some mummy's bandages and a skeleton bone to be able to "
        "craft a charm for my journeys.")
ENDIF

YES(STUDY)
        IF ((CheckItem(__OBJ_SKELETON_BONE) >= 1) && (CheckItem(__OBJ_MUMMY_BANDAGES) >= 1))
                ;int nExpReward = 7500;
                Conversation
                INTL( 5447, "Ahhh. Thank you...  I see already some looong nights studying "
                "this. Here, I give you this potion of serious healing and some "
                "gold pieces for your troubles.")
                Conversation
                FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
                GiveXP(nExpReward)
                GiveItem(__OBJ_SERIOUS_HEALING_POTION)
                GiveGold(rnd.roll(dice(2,1500)))
                TakeItem(__OBJ_SKELETON_BONE)
                TakeItem(__OBJ_MUMMY_BANDAGES)
        ELSE
                Conversation
                INTL( 5448, "I need some mummy's bandages and a skeleton bone to be able to "
                "craft a charm for my journeys.")
        ENDIF
NO(STUDY)
        Conversation
        INTL( 5449, "Ah. Oh well!")
YesNoELSE(STUDY)
        Conversation
        INTL( 5450, "Pardon? Was that a yes or a no?")
        SetYesNo(STUDY)

Command(INTL( 5279, "BOOKS"))
INTL( 5451, "Why yes, I suppose you could call them books too.")

//////////////////////////////////////////////////////////////////////
//
// RIDDLES HINTS
//
//////////////////////////////////////////////////////////////////////
//
// NECESSARY FLAGS
//
// __QUEST_RIDDLES_HINTS
//   0: No hints given
//   1+: Number of hints given
//
//////////////////////////////////////////////////////////////////////
//
// Riddle 1: What is the center of balance? (the letter a)
// Riddle 2: What happens once in a minute, twice in a moment, once during weekdays but never during weekends, and never, ever during a hundred thousand years? (the letter m)
// Riddle 3: What sphynxes employ, the players enjoy. (riddles)
// Riddle 4: AYAMS TOKEER ANNEED SOMELP (i am stuck and need some help)
// Riddle 5: One where none or two should be, seeking out purity in the king's tree. What am I? (unicorn)
// Riddle 6: I am worse than death, dead men eat me, if you eat me you'll die. (nothing)
//
//////////////////////////////////////////////////////////////////////
//
// COST OF HINTS:
//
// 10000 * exp(__QUEST_RIDDLES_HINTS,2)
//
//////////////////////////////////////////////////////////////////////

CmdAND(INTL( 6126, "RIDDLE"),INTL( 4275, "HINT"))
""
IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) >= 6) // User already done the riddles?
        Conversation
        INTL( 7136, "You already have all the answers, you do not need me to give you hints.")
ELSE // User is in process of doing the riddles.
        Conversation
        INTL( 7137, "A hint? You need a hint for a riddle?")
        SetYesNo(HINT)
ENDIF

YES(HINT) // User wants a hint.
        int nPrice = 10000 * pow(CheckFlag(__QUEST_RIDDLES_HINTS)+1, 2.f);
        Conversation
        FORMAT(INTL( 7138, "Very well. It will cost you %u gold pieces. Will you pay?"), nPrice)
        SetYesNo(PAY)

NO(HINT) // User doesn't want a hint.
        Conversation
        INTL( 7139, "Very well. You may return if you ever have the means to pay me for the hints I will provide. "
        "My knowledge does not come cheap, but it is helpful and accurate.")

YesNoELSE(HINT) // User didn't answer by "yes" or "no."
        Conversation
        INTL( 7140, "I will not take that for an answer. Yes or no?")
        SetYesNo(HINT)

YES(PAY) // User ready to pay nPrice GPs for the hint.
    int nPrice = 10000 * pow(CheckFlag(__QUEST_RIDDLES_HINTS)+1, 2.f);
        IF (Gold < nPrice) // User doesn't have the gold to pay
                Conversation
                INTL( 7141, "I'm sorry, but you don't have that kind of money. Perhaps later?")
        ELSE
                TakeGold(nPrice)
                GiveFlag(__QUEST_RIDDLES_HINTS,CheckFlag(__QUEST_RIDDLES_HINTS)+1)
                SWITCH(CheckFlag(__QUEST_THEOPOLD_RIDDLES))
                        CASE(0) // Hint for Riddle 1
                                Conversation
                                INTL( 7142, "Perhaps you should not care so much about the *meaning* of the word. Perhaps "
                                "you should focus your thoughts on the word *itself*...")
                        ENDCASE
                        CASE(1) // Hint for Riddle 2
                                Conversation
                                INTL( 7143, "If you did the Dead King's First Riddle right, this one should be easy. It's "
                                "the same thing. Focus on the words, not the meaning.")
                        ENDCASE
                        CASE(2) // Hint for Riddle 3
                                Conversation
                                INTL( 7144, "Oh, come *on*!! This is the easiest of them all! The answer is in the question. "
                                "What do you think you've been answering all this time?")
                        ENDCASE
                        CASE(3) // Hint for Riddle 4
                                Conversation
                                INTL( 7145, "Sometimes, saying things out loud is the best way to figure them out.")
                        ENDCASE
                        CASE(4) // Hint for Riddle 5
                                Conversation
                                INTL( 7146, "One where none of two should be... Methinks that's arms, legs or, hmmm, horns, "
                                "I guess. Yes, probably horns. And purity... that's an important word, too.")
                        ENDCASE
                        CASE(5) // Hint for Riddle 6
                                Conversation
                                INTL( 7147, "Nothing comes to mind, here. You figure out the rest. *chuckle*")
                        ENDCASE
                ENDSWITCH
        ENDIF

NO(PAY) // User doesn't want to pay that amount.
        Conversation
        INTL( 1646, "As you wish.")

YesNoELSE(PAY) // User didn't answer by "yes" or "no."
        Conversation
        INTL( 7148, "I wish you'd answer by a \"yes\" or a \"no\".")
        SetYesNo(PAY)

Command(INTL( 6126, "RIDDLE"))
INTL( 7149, "I am the one true master of all riddles! If you need help with some, just ask me for \"riddle\" "
"\"hints\" and I'll see what I can do. I must warn you, however, my help comes with a price. I "
"haven't spent the last few decades learning riddles to just *give* away the answers!")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 1622, "Farewell, my friend.") BREAK

Default
INTL( 5431, "I'm sorry, I don't know what you are talking about.")

EndTalk

}