#if !defined(AFX_INITDBSPELLREQUIREMENTS_H__0576D198_26F1_11D2_83B2_00E02922FA40__INCLUDED_)
#define AFX_INITDBSPELLREQUIREMENTS_H__0576D198_26F1_11D2_83B2_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InitDBSpellRequirements.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// InitDBSpellRequirements DAO recordset

class InitDBSpellRequirements : public CDaoRecordset
{
public:
	InitDBSpellRequirements(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(InitDBSpellRequirements)

// Field/Param Data
	//{{AFX_FIELD(InitDBSpellRequirements, CDaoRecordset)
	long	m_ID;
	long	m_SpellID;
	long	m_RequiredSpellID;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InitDBSpellRequirements)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITDBSPELLREQUIREMENTS_H__0576D198_26F1_11D2_83B2_00E02922FA40__INCLUDED_)
