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

}

QteSystem::~QteSystem()
{

}

void QteSystem::trigger(const std::string& qteName)
{
	assert(false);
}

void QteSystem::forceFinish()
{

}
