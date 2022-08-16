// TestHelpers.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TestHelpers.h"


// This is an example of an exported variable
TESTHELPERS_API int nTestHelpers=0;

// This is an example of an exported function.
TESTHELPERS_API int fnTestHelpers(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see TestHelpers.h for the class definition
CTestHelpers::CTestHelpers()
{
	return;
}
