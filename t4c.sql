CREATE TABLE `boosts` (
  `BoostsID` int(11) NOT NULL auto_increment,
  `OwnerID` int(11) default NULL,
  `BaseOwnerID` int(11) default NULL,
  `BoostID` int(11) default NULL,
  `Stat` int(11) default NULL,
  `Boost` char(50) default NULL,
  PRIMARY KEY  (`BoostsID`)
)
 ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE `bounties` (
  `BountiesID` int(11) NOT NULL auto_increment,
  `BountyInEffect` char(50) default NULL,
  `GoldAmount` int(11) default '0',
  `BountyType` char(50) default NULL,
  PRIMARY KEY  (`BountiesID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE `bounty` (
  `BountryID` int(11) NOT NULL auto_increment,
  `PlayerName` char(50) default NULL,
  `BountyInEffect` char(50) default NULL,
  PRIMARY KEY  (`BountryID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE `effects` (
  `EffectsID` int(11) NOT NULL auto_increment,
  `OwnerID` int(11) default NULL,
  `BaseOwnerID` int(11) default NULL,
  `EffectID` int(11) default NULL,
  `EffectType` int(11) default NULL,
  `Timer` int(11) default NULL,
  `EffectData` char(50) default NULL,
  `TotalDuration` int(11) default NULL,
  `BindedSpellID` int(11) default NULL,
  `BindedFlagID` int(11) default NULL,
  PRIMARY KEY  (`EffectsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE `flags` (
  `FlagsID` int(11) NOT NULL auto_increment,
  `OwnerID` int(11) default NULL,
  `BaseOwnerID` int(11) default NULL,
  `FlagID` int(11) default NULL,
  `FlagValue` int(11) default NULL,
  `DynamicFlag` tinyint(4) default NULL,
  PRIMARY KEY  (`FlagsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

CREATE TABLE `guildboard` (
  `GuildBoardID` int(11) NOT NULL auto_increment,
  `PlayerName` varchar(20) default NULL,
  `Guild` varchar(30) default NULL,
  `Rank` varchar(20) default NULL,
  `Message` longtext,
  `Date` datetime default NULL,
  `GuildURL` varchar(50) default NULL,
  PRIMARY KEY  (`GuildBoardID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE `messagedispatch` (
  `RecipientID` int(11) NOT NULL default '0',
  `MessageID` int(11) default NULL,
  PRIMARY KEY  (`RecipientID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `offlinemessages` (
  `MessageID` int(11) NOT NULL default '0',
  `Sender` char(50) default NULL,
  `ReaderCount` int(11) default NULL,
  `Subject` char(50) default NULL,
  `Message` char(255) default NULL,
  `DeletionDate` datetime default NULL,
  PRIMARY KEY  (`MessageID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `onlineusers` (
  `MachineName` char(50) NOT NULL default '',
  `AccountName` char(50) default NULL,
  `PlayerName` char(50) default NULL,
  `FlagBitPosition` int(11) default '0',
  `IPaddr` char(16) default NULL,
  PRIMARY KEY  (`MachineName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `playeritems` (
  `ItemsID` int(11) NOT NULL auto_increment,
  `ObjID` int(11) default NULL,
  `OwnerID` int(11) default NULL,
  `EquipPos` smallint(6) default NULL,
  `ObjType` char(50) default NULL,
  `Qty` int(11) default NULL,
  PRIMARY KEY  (`ItemsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

CREATE TABLE `chestitems` ( 
`ItemsID` int(11) NOT NULL auto_increment, 
`ObjID` int(11) default NULL, 
`OwnerID` int(11) default NULL, 
`EquipPos` smallint(6) default NULL, 
`ObjType` char(50) default NULL, 
`Qty` int(11) default NULL, 
PRIMARY KEY (`ItemsID`) 
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

CREATE TABLE `playerskills` (
  `PlayerSkillsID` int(11) NOT NULL auto_increment,
  `OwnerID` int(11) default NULL,
  `SkillID` int(11) default NULL,
  `SkillPnts` int(11) default NULL,
  PRIMARY KEY  (`PlayerSkillsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE `playerspells` (
  `PlayerSpellsID` int(11) NOT NULL auto_increment,
  `OwnerID` int(11) default NULL,
  `SpellID` int(11) default NULL,
  `SpellPnts` int(11) default NULL,
  PRIMARY KEY  (`PlayerSpellsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=49 ;

CREATE TABLE `playingcharacters` (
  `UserID` int(11) NOT NULL default '0',
  `PlayerName` char(50) default NULL,
  `AccountName` char(50) default NULL,
  `wlX` int(11) default NULL,
  `wlY` int(11) default NULL,
  `wlWorld` int(11) default NULL,
  `nClass` int(11) default NULL,
  `CurrentHP` int(11) default NULL,
  `MaxHP` int(11) default NULL,
  `CurrentMana` int(11) default NULL,
  `MaxMana` int(11) default NULL,
  `Strength` int(11) default NULL,
  `Endurance` int(11) default NULL,
  `Agility` int(11) default NULL,
  `Intelligence` int(11) default NULL,
  `WillPower` int(11) default NULL,
  `Wisdom` int(11) default NULL,
  `Luck` int(11) default NULL,
  `CurrentLevel` int(11) default NULL,
  `AttackSkill` int(11) default NULL,
  `DodgeSkill` int(11) default NULL,
  `Gold` int(11) default NULL,
  `Appearance` int(11) default NULL,
  `Corpse` int(11) default NULL,
  `XP` double default NULL,
  `StatPnts` int(11) default NULL,
  `SkillPnts` int(11) default NULL,
  `Karma` int(11) default NULL,
  `Gender` int(11) default NULL,
  `guildnumberz` int(11) default '0',
  `ListingTitle` char(255) default NULL,
  `ListingMisc` char(255) default NULL,
  `SS` char(3) default NULL,
  `OVO` char(3) default NULL,
  `GvG` char(3) default NULL,
  `Impeach` char(3) default NULL,
  `GuildURL` char(50) default NULL,
  `HideLevel` char(50) default NULL,
  `Bounty` int(11) default '0',
  `BountyPlacer` char(50) default NULL,
  `GuildRank` char(50) default NULL,
  `GuildName` char(50) default NULL,
  `MoveExhaust` int(11) default NULL,
  `MentalExhaust` int(11) default NULL,
  `AttackExhaust` int(11) default NULL,
  PRIMARY KEY  (`UserID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `t4cusers` (
  `ID` int(11) NOT NULL auto_increment,
  `Account` char(50) default NULL,
  `Password` char(50) default NULL,
  `Account_type` char(50) default NULL,
  `Expired` char(50) default NULL,
  `FullName` char(50) default NULL,
  `Email` char(50) default NULL,
  `CreationDate` datetime default NULL,
  `RevisionDate` datetime default NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

CREATE TABLE `userflagids` (
  `UserFLagsID` int(11) NOT NULL auto_increment,
  `FlagBitPosition` int(11) default NULL,
  `FlagDescription` char(50) default NULL,
  PRIMARY KEY  (`UserFLagsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=40 ;

INSERT INTO `userflagids` VALUES (1, 0, 'Doesn''t block.');
INSERT INTO `userflagids` VALUES (2, 1, 'Doesn''t attract monsters.');
INSERT INTO `userflagids` VALUES (3, 2, 'Can teleport.');
INSERT INTO `userflagids` VALUES (4, 3, 'Can teleport a user.');
INSERT INTO `userflagids` VALUES (5, 4, 'Can zap a user.');
INSERT INTO `userflagids` VALUES (6, 5, 'Can squelch a user.');
INSERT INTO `userflagids` VALUES (7, 6, 'Can remove a user''s shouts.');
INSERT INTO `userflagids` VALUES (8, 7, 'Can summon monsters.');
INSERT INTO `userflagids` VALUES (9, 8, 'Can summon items.');
INSERT INTO `userflagids` VALUES (10, 9, 'Can set a user''s flag.');
INSERT INTO `userflagids` VALUES (11, 11, 'Can edit a user''s stats.');
INSERT INTO `userflagids` VALUES (12, 12, 'Can edit a user''s hit points.');
INSERT INTO `userflagids` VALUES (13, 13, 'Can edit a user''s mana or faith.');
INSERT INTO `userflagids` VALUES (14, 14, 'Can edit a user''s xp or level.');
INSERT INTO `userflagids` VALUES (15, 15, 'Can edit a user''s name.');
INSERT INTO `userflagids` VALUES (16, 16, 'Can edit a user''s appearance or binded corpse.');
INSERT INTO `userflagids` VALUES (17, 17, 'Can edit a user''s spells.');
INSERT INTO `userflagids` VALUES (18, 18, 'Can edit a user''s skills.');
INSERT INTO `userflagids` VALUES (19, 19, 'Can edit a user''s backpack.');
INSERT INTO `userflagids` VALUES (20, 21, 'Can view a user''s stats, hp, mana, faith or xp.');
INSERT INTO `userflagids` VALUES (21, 22, 'Can view a user''s backpack.');
INSERT INTO `userflagids` VALUES (22, 23, 'Can view a user''s spells.');
INSERT INTO `userflagids` VALUES (23, 24, 'Can view a user''s skills.');
INSERT INTO `userflagids` VALUES (24, 25, 'Can view a user''s appearance or binded corpse.');
INSERT INTO `userflagids` VALUES (25, 26, 'Can lockout a player.');
INSERT INTO `userflagids` VALUES (26, 27, 'Can slay a player. ( normal death ).');
INSERT INTO `userflagids` VALUES (27, 28, 'Can copy a user.');
INSERT INTO `userflagids` VALUES (28, 29, 'Can emulate a monster.');
INSERT INTO `userflagids` VALUES (29, 30, 'Invincible.');
INSERT INTO `userflagids` VALUES (30, 31, 'Developper/debugger.');
INSERT INTO `userflagids` VALUES (31, 32, 'Can shutdown server.');
INSERT INTO `userflagids` VALUES (32, 33, 'Can see true account names.');
INSERT INTO `userflagids` VALUES (33, 10000, 'User locked out.');
INSERT INTO `userflagids` VALUES (34, 10001, 'User squelched.');
INSERT INTO `userflagids` VALUES (35, 10002, 'User cannot shout.');
INSERT INTO `userflagids` VALUES (36, 10003, 'User not in userlisting');
INSERT INTO `userflagids` VALUES (37, 36, 'User is invisible');
INSERT INTO `userflagids` VALUES (38, 10, 'can give keys');
INSERT INTO `userflagids` VALUES (39, 10004, 'PvP Off');

CREATE TABLE `userflags` (
  `UserFlagsID` int(11) NOT NULL auto_increment,
  `AccountName` char(50) default NULL,
  `FlagBitPosition` int(11) default NULL,
  PRIMARY KEY  (`UserFlagsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

CREATE TABLE `userskillsids` (
  `ID` int(11) NOT NULL auto_increment,
  `SkillID` int(11) default '0',
  `SkillName` char(50) default NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=14 ;

INSERT INTO `userskillsids` VALUES (1, 35, 'Archery');
INSERT INTO `userskillsids` VALUES (2, 1, 'Stun Blow');
INSERT INTO `userskillsids` VALUES (3, 4, 'First Aid');
INSERT INTO `userskillsids` VALUES (4, 8, 'Parry');
INSERT INTO `userskillsids` VALUES (5, 9, 'Meditate');
INSERT INTO `userskillsids` VALUES (6, 14, 'Hide');
INSERT INTO `userskillsids` VALUES (7, 15, 'Rob');
INSERT INTO `userskillsids` VALUES (8, 16, 'Sneak');
INSERT INTO `userskillsids` VALUES (9, 17, 'Search');
INSERT INTO `userskillsids` VALUES (10, 26, 'Pick Lock');
INSERT INTO `userskillsids` VALUES (11, 27, 'Armor Penetration');
INSERT INTO `userskillsids` VALUES (12, 28, 'Peek');
INSERT INTO `userskillsids` VALUES (13, 29, 'Rapid Healing');

CREATE TABLE `ranking` (
  `ID` int(11) NOT NULL auto_increment,
  `p` varchar(20) default NULL,
  `plus` int(11) default '0',
  `minus` int(11) default '0',
  `w` int(11) default '0',
  `t` int(11) default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;

CREATE TABLE `ranking_history` (
  `ID` int(11) NOT NULL auto_increment,
  `p1` varchar(20) default NULL,
  `p2` varchar(20) default NULL,
  `l1` int(11) default '0',
  `s1` int(11) default '0',
  `l2` int(11) default '0',
  `s2` int(11) default '0',
  `id1` int(11) default '0',
  `id2` int(11) default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;

CREATE TABLE `chestitems` (
`ItemsID` int(11) NOT NULL auto_increment,
`ObjID` int(11) default NULL,
`OwnerID` int(11) default NULL,
`EquipPos` smallint(6) default NULL,
`ObjType` char(50) default NULL,
`Qty` int(11) default NULL,
PRIMARY KEY (`ItemsID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;