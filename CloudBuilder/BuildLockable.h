#pragma once
class BuildLockable
{
public:
	BuildLockable();
	~BuildLockable();

	virtual void lock();
	virtual void unlock();
	virtual bool isLocked();

protected:
	bool mLocked;
};

