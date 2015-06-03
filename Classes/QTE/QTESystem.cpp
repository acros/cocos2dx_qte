#include "QTESystem.h"

QteSystem* QteSystem::sInstance = nullptr;

QteSystem* QteSystem::getInstance()
{
	assert(sInstance != nullptr);
	return sInstance;
}

void QteSystem::create()
{
	assert(sInstance == nullptr);
	sInstance = new QteSystem();
}

void QteSystem::destroy()
{
	if (sInstance != nullptr)
		delete sInstance;
}

QteSystem::QteSystem() :mActive(false)
{
	initWithFile();
}

QteSystem::~QteSystem()
{

}

void QteSystem::trigger(const std::string& qteName)
{
	assert(!mActive);

	mActive = true;


}

void QteSystem::forceFinish()
{
	//Force to end QTE
/*	finish();*/
}

void QteSystem::initWithFile()
{
	assert(m_QTEmap.empty());

}

void QteSystem::finish()
{

}
