#include "stdafx.h"


Sync::Sync(void)
{
	InitializeCriticalSection(&m_csA);
	InitializeCriticalSection(&m_csB);
}

Sync::~Sync(void)
{
	DeleteCriticalSection(&m_csA);
	DeleteCriticalSection(&m_csB);
}

void Sync::AccessFirstResource(void)
{
	EnterCriticalSection(&m_csA);
}

void Sync::AccessSecondResource(void)
{
	EnterCriticalSection(&m_csB);
}

void Sync::ReleaseFirstResource(void)
{
	LeaveCriticalSection(&m_csA);
}

void Sync::ReleaseSecondResource(void)
{
	LeaveCriticalSection(&m_csB);
}