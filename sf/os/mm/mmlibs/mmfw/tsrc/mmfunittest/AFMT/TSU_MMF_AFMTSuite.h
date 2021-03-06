// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// This contains CTestSuite_MMF_AFMT 
// 
//

#ifndef __TSU_MMF_AFMT_SUITE_H_
#define __TSU_MMF_AFMT_SUITE_H_

#include <testframework.h>

class CTestStep_MMF_AFMT;

class  CTestSuite_MMF_AFMT : public CTestSuite
{
public:	
	void InitialiseL( void );
	virtual ~CTestSuite_MMF_AFMT();
	void AddTestStepL( CTestStep_MMF_AFMT *ptrTestStep );
	TPtrC GetVersion( void );

};


#endif /* TSU_MMF_AFMT_SUITE_H_ */

