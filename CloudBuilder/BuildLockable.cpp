#include "BuildLockable.h"



BuildLockable::BuildLockable() :
	mLocked(false)
{
}


BuildLockable::~BuildLockable()
{
}

void BuildLockable::lock()
{
	mLocked = true;
}

void BuildLockable::unlock()
{
	mLocked = false;
}

bool BuildLockable::isLocked()
{
	return mLocked;
}
