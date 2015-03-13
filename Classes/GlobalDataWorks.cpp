#include "GlobalDataWorks.h"

USING_NS_CC;

GlobalDataWorks* GlobalDataWorks::m_globalData = NULL;
int GlobalDataWorks::m_score = 0;


GlobalDataWorks* GlobalDataWorks::getInstance()
{
	
	if (m_globalData == nullptr)
	{
		m_globalData = GlobalDataWorks::create();
	}
	return m_globalData;

}

bool GlobalDataWorks::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	return true;
}