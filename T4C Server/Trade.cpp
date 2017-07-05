/*
Trade.cpp
Implementation file for the Trade System.
Its designed to handle all issues related to give Character class support for Trade

Originally Written by Carlos Lima (carlos@dialsoft.com)
for Dialsoft (http://www.dialsoft.com)
*/

#include "stdafx.h"
#include "Trade.h"
#include "T4CLog.h"
#include "Objects.h"
#include "Character.h"
#include "ItemContainer.h"
#include "TFC_MAIN.h"
#include "ObjectListing.h"

// Static variable declaration
CLock TradeMgr2::m_TradeLock; // The lock used to synchronize trade calls

/*
 * Constructor!
 */
TradeMgr2::TradeMgr2(Character &ownerCharacter) : m_ThisCharacter(ownerCharacter), mOtherTrade(NULL), 
m_Status(Status::TS_Invalid), m_StatusCharacter(Status::EditingItems),
m_Container(new ItemContainer()) {};

/*
 * Destructor!
 */
TradeMgr2::~TradeMgr2() {
	Cancel();
	delete m_Container;
}


//void TradeMgr2::SetOwnerCharacter(Character *thisCharacter) {
/*	if (m_ThisCharacter != NULL) { // Cant initialize more than once
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			"Tried to set TradeMgr-owner twice. First-set: %s Second-try: %s",
			m_ThisCharacter->GetName(_DEFAULT_LNG),
			thisCharacter->GetName(_DEFAULT_LNG)
		LOG_
		throw logic_error("Tried to set TradeMgr-owner twice");
	}
	m_ThisCharacter = thisCharacter;
}
*/
void TradeMgr2::CheckInitialization() {
/*	if (m_ThisCharacter == NULL) {
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			"Calling TradeMgr functions before initializing the owner of this instance."
		LOG_
		throw logic_error("TradeMgr function called before owner initialization.");
	}
*/}

TradeMgr2::ErrorCodes::Request
TradeMgr2::Request(TradeMgr2 &pInvitedTradeMgr) {
//	CheckInitialization();
	if (&pInvitedTradeMgr == this) return ErrorCodes::InvalidParameters;

	{ // autolock scoping..
		Character &invitedCharacter = pInvitedTradeMgr.m_ThisCharacter;
		BOOL	InvitorIsTrading				= false,
				TargetIsTrading					= false, 
				InvitorIsAlreadyInvitingTarget	= false,
				InvitorIsInvitingSomeoneElse	= false,
				TargetIsWaitingAcceptance		= false;

		CAutoLock __autolock(&m_TradeLock);

		// Are they in range?
		BOOL charactersAreCloseEnough = m_ThisCharacter.GetWL().AreInRange(invitedCharacter.GetWL(), 3);//BLBLBL 10=>3
		if (charactersAreCloseEnough == FALSE) {
			// Cant allow to trade unless they are closer to each other
			return ErrorCodes::NotCloseEnoughForTrade;
		}

		//BLBLBL : ajout d'un système de detection de colisions entre 2 joueurs qui veulent trade.
	    //BEGIN collision detection in trades:

		// Return if there is a wall or any building between players
		{
			WorldPos tempPos;
			WorldMap *wlWorld = TFCMAIN::GetWorld( m_ThisCharacter.GetWL().world );
			Unit *lpCollisionUnit = NULL;
			if (wlWorld->GetCollisionPos( m_ThisCharacter.GetWL(), invitedCharacter.GetWL(), &tempPos, &lpCollisionUnit, false, false )) {
				return ErrorCodes::NotCloseEnoughForTrade;		
			}
		}

		
		/*WorldPos blockPos = { 0, 0, 0 };
		WorldPos wlInitierPos = m_ThisCharacter.GetWL();
		WorldPos wlInvitedPos = invitedCharacter.GetWL();
		Unit *collideUnit = NULL;

		if( wlWorld->GetCollisionPos( wlInitierPos, wlInvitedPos, &blockPos, &collideUnit ) ){
        		// If the target unit isn't the target and the block pos isn't the target pos.
			if( collideUnit != Target && ( blockPos.X != wlTarPos.X || blockPos.Y != wlTarPos.Y ) )
				return ErrorCodes::NotCloseEnoughForTrade;
		}
		//END collision detection in trades
*/


		// Check if the request is valid (requestor must meet requeriments)
		if (m_Status != Status::TS_Invalid) {
			if (m_Status == Status::TS_Trading) {
				// Cannot invite while in middle of a trade!
				InvitorIsTrading = true;
			} else if (mOtherTrade == &pInvitedTradeMgr) {
				// Cannot invite more than once..
				InvitorIsAlreadyInvitingTarget = true;
			} else {
				// Invitor is inviting someone else..
				InvitorIsInvitingSomeoneElse = true;
			}
		}


		// Check if the target character can be invited (must meet requeriments)
		if (pInvitedTradeMgr.m_Status != Status::TS_Invalid) {
			if (pInvitedTradeMgr.m_Status == Status::TS_Trading) {
				// Cannot invite while in middle of a trade!
				TargetIsTrading = true;
			} else if (pInvitedTradeMgr.mOtherTrade == this) {
				// User is waiting my acceptance!
				TargetIsWaitingAcceptance = true;
			}
		}

		// Decide what to do =)
		if ( InvitorIsTrading || TargetIsTrading || InvitorIsAlreadyInvitingTarget ) {
			// Invite not allowed for some reason, return the appropriated error
			if (InvitorIsTrading) {
				return ErrorCodes::InvitorIsTrading;
			} else if (TargetIsTrading) {
				return ErrorCodes::TargetIsTrading;
			} else if (InvitorIsAlreadyInvitingTarget) {
				return ErrorCodes::InvitorIsAlreadyInvitingTarget;
			} else {
				//Unexpected, crash!
				_LOG_DEBUG
					LOG_CRIT_ERRORS,
					"TradeMgr::Request() unhandled error code. Crashing at line %i",
					__LINE__
				LOG_
				throw logic_error("TradeMgr::Request() unhandled error code.");
			}
		} else {
			// Request to invite allowed!

			if (InvitorIsInvitingSomeoneElse) { // Cancel any other invite made before to others
				Cancel();
			}

			if ( TargetIsWaitingAcceptance ) {
				// Start trading..
				mOtherTrade = &pInvitedTradeMgr;
				SetTradeStatus(TradeMgr2::Status::TS_Trading);
				SetCharacterStatus(Status::EditingItems);
				mOtherTrade->SetCharacterStatus(Status::EditingItems);

				// Reset containers (make sure it starts clean!)
				m_Container->ResetContainer();
				mOtherTrade->m_Container->ResetContainer();
				// Set container's sizes
				m_Container->SetMaxWeight( invitedCharacter.GetFreeWeight() );
				pInvitedTradeMgr.m_Container->SetMaxWeight( m_ThisCharacter.GetFreeWeight() );

				// Must notify both!
				EventTradeStarted(pInvitedTradeMgr);
				pInvitedTradeMgr.EventTradeStarted(*this);
				return ErrorCodes::TradeStarted;
			} else {
				// Invite target for a trade!
				mOtherTrade = &pInvitedTradeMgr;
				SetTradeStatus(Status::TS_Inviting);
				// Must notify other!
				pInvitedTradeMgr.EventInviteReceived(*this);
				EventInviteSent(pInvitedTradeMgr);
				return ErrorCodes::InviteDone;
			}
		}
	}
}

TradeMgr2::ErrorCodes::Cancel
TradeMgr2::Cancel() {
	CheckInitialization();
	CAutoLock __autolock(&m_TradeLock);

	if (m_Status == Status::TS_Invalid) return ErrorCodes::NoTradeToCancel;

	if (m_Status == Status::TS_Inviting) { // Cancel an invite..
		ResetTradeData();
		return ErrorCodes::InviteCancelled;
	} else if (m_Status == Status::TS_Trading) { // Cancel a running trade..
		//DEVOLVER OS ITEMS!
		PutItemsFromTradeToBackpack(); // return the items to the backpack
		mOtherTrade->PutItemsFromTradeToBackpack(); // return the items to the backpack

		EventTradeCanceled();
		mOtherTrade->EventTradeCanceled();
		
		mOtherTrade->ResetTradeData();
		ResetTradeData();

		return ErrorCodes::TradeCancelled;
	} else {
		// Unexpected! Crash!
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			"TradeMgr::Cancel() unhandled trade status. Crashing at line %i",
			__LINE__
		LOG_
		throw logic_error("TradeMgr::Cancel() unhandled trade status.");
	}
}

TradeMgr2::ErrorCodes::Cancel
TradeMgr2::CancelDisturbed()
{
	if (m_Status == Status::TS_Trading) {
		return Cancel();
	}
	return ErrorCodes::NoTradeToCancel;
}

TradeMgr2::ErrorCodes::Finish
TradeMgr2::Finish() {
	CheckInitialization();
	CAutoLock __autolock(&m_TradeLock);

	if (m_Status == Status::TS_Invalid) return ErrorCodes::NoTradeToFinish;
	if (m_Status == Status::TS_Inviting) { // Cant finish an invite
		return ErrorCodes::CantFinishAnInvite;
	} else if (m_Status == Status::TS_Trading) { // Its a running trade..
		if (m_StatusCharacter == mOtherTrade->m_StatusCharacter && m_StatusCharacter == TradeMgr2::Status::Confirmed) { // Both chars status is "Confirmed"
			//Do item switching!
			ItemContainer *tmpContainer = mOtherTrade->m_Container;
			mOtherTrade->m_Container = m_Container;
			m_Container = tmpContainer;

			CString logMyItems, logOtherItems;

			PutItemsFromTradeToBackpack(&logMyItems);
			mOtherTrade->PutItemsFromTradeToBackpack(&logOtherItems);

			LogTradeFinish(logMyItems, logOtherItems);

			PacketSendTradeFullContents();
			mOtherTrade->PacketSendTradeFullContents();

			EventTradeFinished();
			mOtherTrade->EventTradeFinished();

			mOtherTrade->ResetTradeData();
			ResetTradeData();
			return ErrorCodes::TradeFinished;
		} else {
			return ErrorCodes::CantFinishImproperCharacterStatus;
		}
	} else {
		// Unexpected! Crash!
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			"TradeMgr::Finish() unhandled trade status. Crashing at line %i",
			__LINE__
		LOG_
		throw logic_error("TradeMgr::Finish() unhandled trade status.");
	}
}

void TradeMgr2::LogTradeFinish(const CString &pMyItems, const CString &pOtherItems)
{
    _LOG_ITEMS
        LOG_MISC_1,
		"Finished a trade between characters [ %s ] and [ %s ]",
		m_ThisCharacter.GetName(),
		mOtherTrade->m_ThisCharacter.GetName()
    LOG_
    _LOG_ITEMS
        LOG_MISC_1,
		"\tCharacter %s received: %s",
		m_ThisCharacter.GetName(),
		pMyItems
    LOG_
    _LOG_ITEMS
        LOG_MISC_1,
		"\tCharacter %s received: %s",
		mOtherTrade->m_ThisCharacter.GetName(),
		pOtherItems
    LOG_
}

TradeMgr2::ErrorCodes::ClearItemsFromTrade
TradeMgr2::ClearItemsFromTrade()
{
	CheckInitialization();
	CAutoLock __autolock(&m_TradeLock);

	if (m_Status == Status::TS_Invalid) return ErrorCodes::NoTradeToClear;

	SetCharacterStatus(Status::EditingItems);
	
	PutItemsFromTradeToBackpack();
	PacketSendTradeFullContents();
	mOtherTrade->PacketSendTradeContents(AC_OTHER);
	return ErrorCodes::TradeCleared;
}

TradeMgr2::ErrorCodes::AddItem
TradeMgr2::AddItemToTrade(Objects *obj) {
	CheckInitialization();
	CAutoLock __autolock(&m_TradeLock);

	// Only accept valid trades under "Trading" status
	if (m_Status != Status::TS_Trading) return ErrorCodes::TradeInvalidForItemAdding;

	CString objDesc;
	objDesc.Format("%s x%i", obj->GetName(m_ThisCharacter.GetLang()), obj->GetQty());
	SetCharacterStatus(Status::EditingItems);
	if (m_Container->Put(obj) == TRUE) {
		// Send the contents updates to both characters involved
		PacketSendTradeContents(AC_MYSELF);
		mOtherTrade->PacketSendTradeContents(AC_OTHER);
		// Send the backpack updates :)
		m_ThisCharacter.SendBackpackContentPacket();

		// Notify clients the item was added
		EventItemAdded(AC_MYSELF, objDesc);
		mOtherTrade->EventItemAdded(AC_OTHER, objDesc);
		return ErrorCodes::ItemAdded;
	} else {
		return ErrorCodes::ItemCantBeAdded;
	}

}

TradeMgr2::ErrorCodes::RemoveItem
TradeMgr2::RemoveItemFromTrade(DWORD itemID, DWORD itemQty, Objects *&removedObj) {
	CheckInitialization();
	CAutoLock __autolock(&m_TradeLock);

	// Only accept valid trades under "Trading" status
	if (m_Status != Status::TS_Trading) return ErrorCodes::TradeInvalidForItemRemoving;

	SetCharacterStatus(Status::EditingItems);
	Objects *droppedObj = m_Container->Take(itemID, itemQty);
	if (droppedObj != NULL) {
		removedObj = droppedObj;
		PacketSendTradeContents(AC_MYSELF);
		mOtherTrade->PacketSendTradeContents(AC_OTHER);

		CString objDesc;
		objDesc.Format("%s x%i", droppedObj->GetName(m_ThisCharacter.GetLang()), droppedObj->GetQty());

		// Notify clients the item was removed
		EventItemRemoved(AC_MYSELF, objDesc);
		mOtherTrade->EventItemRemoved(AC_OTHER, objDesc);
		return ErrorCodes::ItemRemoved;
	} else {
		return ErrorCodes::ItemCantBeRemoved;
	}
}

TradeMgr2::ErrorCodes::IsTradeValid
TradeMgr2::IsTradeValid(void) {
	CheckInitialization();
	CAutoLock __autolock(&m_TradeLock);

	if (m_Status == Status::TS_Invalid) return ErrorCodes::InvalidTrade;
	if (m_Status == Status::TS_Inviting) return ErrorCodes::IsInviting;
	if (m_Status == Status::TS_Trading) return ErrorCodes::IsTrading;

	// Unexpected! Crash!
	_LOG_DEBUG
		LOG_CRIT_ERRORS,
		"TradeMgr::IsTradeValid() unhandled trade status. Crashing at line %i",
		__LINE__
	LOG_
	throw logic_error("TradeMgr::IsTradeValid() unhandled trade status.");
}

void TradeMgr2::PutItemsFromTradeToBackpack(CString *pItemNamesLog) {

	Objects *obj = NULL;
	// Lets check for logging only once
	if (pItemNamesLog != NULL) {
		// Logging enabled, drop output to pItemNamesLog
		*pItemNamesLog = "";
		CString temp;
		while (obj = m_Container->TakeTop()) {
			temp.Format("%s x%i, ", obj->GetName( _DEFAULT_LNG ), obj->GetQty());
			*pItemNamesLog += temp;
			if (obj->GetStaticReference() == (UINT)__OBJ_GOLD) {
				m_ThisCharacter.SetGold( m_ThisCharacter.GetGold() + obj->GetQty(), false );
			} else {
				m_ThisCharacter.AddToBackpack(obj);
			}
		}
	} else {
		// Logging disabled. Simple move items
		while (obj = m_Container->TakeTop()) {
			if (obj->GetStaticReference() == (UINT)__OBJ_GOLD) {
				m_ThisCharacter.SetGold( m_ThisCharacter.GetGold() + obj->GetQty(), false );
			} else {
				m_ThisCharacter.AddToBackpack(obj);
			}
		}
	}

}

TradeMgr2::ErrorCodes::SetCharacterStatus
TradeMgr2::SetCharacterStatus(TradeMgr2::Status::CharacterStatus newStatus) {
	CheckInitialization();
	CAutoLock __autolock(&m_TradeLock);

	if (m_Status == Status::TS_Invalid) return TradeMgr2::ErrorCodes::NoTradeToSetCharacterStatus;

	// Check to see if the new status is valid?
	if (m_StatusCharacter == newStatus) {
		// Its the same status, no change required
		return ErrorCodes::CharacterStatusSet;
	} else if (m_StatusCharacter == Status::EditingItems) {
		// The only change allowed for someone "EditingItems" is "Ready"
		if (newStatus != Status::Ready) {
			// Well if its trying to set to something else
			return ErrorCodes::CharacterStatusInvalid;
		}
	} else if (newStatus == Status::Confirmed) {
		// Going to status "Confirmed" is only allowed after the other player has set
		// his status to "Ready" or "Confirmed"
		if ( mOtherTrade->m_StatusCharacter == Status::Confirmed ) {
			// If the other has already confirmed
			// having both confirmed means we can complete the trade
			m_StatusCharacter = Status::Confirmed;
			m_ThisCharacter.TradeFinish();
			return ErrorCodes::CharacterStatusSetAndTradeFinished;
		}
		else if (mOtherTrade->m_StatusCharacter != Status::Ready && mOtherTrade->m_StatusCharacter != Status::Confirmed) {
			// Trying to set status to confirmed while other is still
			// editing items is not allowed
			return ErrorCodes::CharacterStatusInvalid;
		}
	}

	if (newStatus == Status::EditingItems && m_StatusCharacter != newStatus ) {
		// If player going back from any status to EditingItems, change 
		// the other status to Editing too, thus requering other to 
		// confirm again, avoiding abuse
		mOtherTrade->m_StatusCharacter = newStatus;
	}
	m_StatusCharacter = newStatus;
	EventTradeStatusChanged(AC_MYSELF, newStatus);
	mOtherTrade->EventTradeStatusChanged(AC_OTHER, newStatus);

	return TradeMgr2::ErrorCodes::CharacterStatusSet;
}


CLock*
TradeMgr2::GetCLock() {
	return &m_TradeLock;
}

TradeMgr2::ErrorCodes::SetTradeStatus
TradeMgr2::SetTradeStatus(TradeMgr2::Status::TradeStatus newStatus) {
	CheckInitialization();

	if (m_Status == Status::TS_Trading && newStatus != Status::TS_Trading) {
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			"At TradeMgr2::SetStatus -> Trying to set status back from Trading to Inviting"
		LOG_
		throw new logic_error("At TradeMgr2::SetStatus -> Trying to set status back from Trading to Inviting");
	}
	if (m_Status != Status::TS_Trading && newStatus == Status::TS_Trading) {
//		m_Container = new ItemContainer(); // Initialize containers
//		mOtherTrade->m_Container = new ItemContainer();
		m_Container->ResetContainer();
		mOtherTrade->m_Container->ResetContainer();
		mOtherTrade->m_Status = Status::TS_Trading; // If the new status is 'Trading', both characters must have it set to 'Trading'
	}
	m_Status = newStatus;
	return TradeMgr2::ErrorCodes::TradeStatusSet;
}

void TradeMgr2::EventInviteReceived(TradeMgr2 &pInvitor)
{
	PacketSendInviteReceived(pInvitor);

	CString tmp;
	tmp.Format(_STR(12948, m_ThisCharacter.GetLang()), pInvitor.m_ThisCharacter.GetName());
	TradeSendInfoMessage(tmp);
}

void TradeMgr2::EventTradeStarted(TradeMgr2 &otherParty)
{
	PacketSendTradeStarted( otherParty );

	CString tmp;
	tmp.Format(_STR(12926, m_ThisCharacter.GetLang()), otherParty.m_ThisCharacter.GetName());
	TradeSendInfoMessage(tmp);

/*		CString message;
		message.Format("A trade between you and %s just started!", otherParty->GetName(_DEFAULT_LNG));
		m_ThisCharacter->SendSystemMessage(message);
*/	
}

void TradeMgr2::EventTradeCanceled()
{
	PacketSendTradeContents(AC_MYSELF); // send an updated content info (cleared)
	PacketSendTradeContents(AC_OTHER); // send an updated content info (cleared)
	m_ThisCharacter.SendBackpackContentPacket(); // send an updated backpack
	PacketSendTradeCanceled();
	TradeSendInfoMessage(12929);

/*	CString message;
	message.Format("Trade canceled");
	m_ThisCharacter->SendSystemMessage(message);
*/}
void TradeMgr2::EventTradeFinished()
{
	PacketSendTradeFinished();
	TradeSendInfoMessage(12933);
/*	CString message;
	message.Format("Trade finished.");
	m_ThisCharacter->SendSystemMessage(message);
*/}
void TradeMgr2::EventTradeStatusChanged(TradeMgr2::AffectedCharacter pWhoChanged, TradeMgr2::Status::CharacterStatus pNewStatus)
{
	PacketSendTradeStatus();
	CString tmp;
	int statusStringID;

	switch (pNewStatus) {
	case Status::EditingItems:{ statusStringID = 12953; } break;
	case Status::Ready:{ statusStringID = 12954; } break;
	case Status::Confirmed:{ statusStringID = 12955; } break;
	}

	if (pWhoChanged == AC_MYSELF) {
		tmp.Format(_STR(12949, m_ThisCharacter.GetLang()), _STR(statusStringID, m_ThisCharacter.GetLang()));
		TradeSendInfoMessage(tmp);
	} else if (pWhoChanged == AC_OTHER) {
		tmp.Format(_STR(12950, m_ThisCharacter.GetLang()), _STR(statusStringID, m_ThisCharacter.GetLang()));
		TradeSendInfoMessage(tmp);
	}
/*	CString message;
	message.Format("Other party's status changed!");
	m_ThisCharacter->SendSystemMessage(message);
*/}
void TradeMgr2::EventInviteSent(TradeMgr2 &pInvited)
{
	CString tmp;
	tmp.Format(_STR(12925, m_ThisCharacter.GetLang()), pInvited.m_ThisCharacter.GetName());
	TradeSendInfoMessage(tmp);

/*		CString message;
		message.Format("You just asked %s to trade with you!", invited->GetName(_DEFAULT_LNG));
		m_ThisCharacter->SendSystemMessage(message);
*/
}


void TradeMgr2::PacketSendInviteReceived(TradeMgr2 &pInvitor)
{
	Character *invitorCharacter = &(pInvitor.m_ThisCharacter);
	WorldPos pos = invitorCharacter->GetWL();
	TFCPacket packet;
	packet << (RQ_SIZE)RQ_TradeInvite;
	packet << invitorCharacter->GetName();
	packet << (long) invitorCharacter->GetID();
	packet << (short) pos.X;
	packet << (short) pos.Y;
	m_ThisCharacter.SendPlayerMessage(packet);
}

void TradeMgr2::PacketSendTradeStarted(TradeMgr2 &pInvitor)
{
//	if (pInvitor == NULL) return;
	TFCPacket packet;
	packet << (RQ_SIZE)RQ_TradeStarted;
	packet << pInvitor.m_ThisCharacter.GetName();
	m_ThisCharacter.SendPlayerMessage(packet);
}
void TradeMgr2::PacketSendTradeCanceled()
{
	TFCPacket packet;
	packet << (RQ_SIZE)RQ_TradeCancel;
	m_ThisCharacter.SendPlayerMessage(packet);
}
void TradeMgr2::PacketSendTradeStatus()
{
/*	Status::CharacterStatus myStatus, otherStatus;
	if (m_Trade->m_CharacterOne == m_ThisCharacter) {
		myStatus = m_Trade->m_StatusCharacterOne;
		otherStatus = m_Trade->m_StatusCharacterTwo;
	} else if (m_Trade->m_CharacterTwo == m_ThisCharacter) {
		myStatus = m_Trade->m_StatusCharacterTwo;
		otherStatus = m_Trade->m_StatusCharacterOne;
	} else {
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
			"At TradeMgr2::PacketSendTradeStatus() -> Character passed isnt one of the two involved in trade"
		LOG_
		throw new invalid_argument("At TradeMgr2::PacketSendTradeStatus() -> Character passed isnt one of the two involved in trade");
	}
*/
	TFCPacket packet;
	packet << (RQ_SIZE)RQ_TradeSetStatus;
	packet << (short)m_StatusCharacter;
	packet << (short)(mOtherTrade->m_StatusCharacter);
	m_ThisCharacter.SendPlayerMessage(packet);
}
void TradeMgr2::PacketSendTradeContents(AffectedCharacter pSourceChar)
{
	CAutoLock __autolock(&m_TradeLock);
	// If its not a valid trade with status = "Trading", there is nothing to send
	if (m_Status != Status::TS_Trading) return;

	TFCPacket packet;
	packet << (RQ_SIZE)RQ_TradeContents;
	packet << (short)pSourceChar;
	if (pSourceChar == AC_MYSELF) {
		m_Container->GetPacket(packet);
	} else if (pSourceChar == AC_OTHER) {
		mOtherTrade->m_Container->GetPacket(packet);
	}
	m_ThisCharacter.SendPlayerMessage(packet);
}

void TradeMgr2::PacketSendTradeFullContents()
{
	CAutoLock __autolock(&m_TradeLock);
	PacketSendTradeContents(AC_MYSELF); // update contents of my side on the trade
	PacketSendTradeContents(AC_OTHER); // update contents of the other side on the trade
	m_ThisCharacter.SendBackpackContentPacket(); // update contents of my backpack :)
}

void TradeMgr2::PacketSendTradeFinished()
{
	TFCPacket packet;
	packet << (RQ_SIZE)RQ_TradeFinish;
	m_ThisCharacter.SendPlayerMessage(packet);
}

BOOL TradeMgr2::GetItemName(DWORD pItemID, CString &pItemName, WORD pLanguageID)
{
	CAutoLock __autolock(&m_TradeLock);
	if (m_Status != Status::TS_Trading) return FALSE; // If we are not in middle of a trade, just leave :)

	return m_Container->GetItemName(pItemID, pItemName, pLanguageID);
}

BOOL TradeMgr2::GetItemNameFromOther(DWORD pItemID, CString &pItemName, WORD pLanguageID)
{
	CAutoLock __autolock(&m_TradeLock);
	if (m_Status != Status::TS_Trading) return FALSE; // If we are not in middle of a trade, just leave :)

	return mOtherTrade->m_Container->GetItemName(pItemID, pItemName, pLanguageID);
}

unsigned int TradeMgr2::GetFreeWeight()
{
	CAutoLock __autolock(&m_TradeLock);
	if (m_Status != Status::TS_Trading) return 0;
	return m_Container->GetFreeWeight();
}

void TradeMgr2::EventItemAdded(TradeMgr2::AffectedCharacter pWhoAdded, CString pItemDescription)
{
	CString temp;
	if (pWhoAdded == AC_MYSELF) {
		temp.Format(_STR(12939, m_ThisCharacter.GetLang()), pItemDescription);
	} else {
		temp.Format(_STR(12938, m_ThisCharacter.GetLang()), pItemDescription);
	}
	TradeSendInfoMessage(temp);
}

void TradeMgr2::EventItemRemoved(TradeMgr2::AffectedCharacter pWhoAdded, CString pItemDescription)
{
	CString temp;
	if (pWhoAdded == AC_MYSELF) {
		temp.Format(_STR(12941, m_ThisCharacter.GetLang()), pItemDescription);
	} else {
		temp.Format(_STR(12940, m_ThisCharacter.GetLang()), pItemDescription);
	}
	TradeSendInfoMessage(temp);
}

void TradeMgr2::ResetTradeData()
{
	m_Status = Status::TS_Invalid;
	m_StatusCharacter = Status::EditingItems;
	mOtherTrade = NULL;
	m_Container->ResetContainer();
}

ItemContainer* TradeMgr2::GetItemContainer()
{
	return m_Container;
}

void TradeMgr2::TradeSendInfoMessage(DWORD pID)
{
	WORD lang = m_ThisCharacter.GetLang();
	m_ThisCharacter.SendInfoMessage((CString)_STR(12922, lang) + _STR(pID, lang), CO_TRADECOLOR);
}
void TradeMgr2::TradeSendInfoMessage(const CString &pMessage)
{
	WORD lang = m_ThisCharacter.GetLang();
	m_ThisCharacter.SendInfoMessage((CString)_STR(12922, lang) + pMessage, CO_TRADECOLOR);
}
