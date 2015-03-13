#ifndef __GLOBAL_DATA_WORKS_H__
#define __GLOBAL_DATA_WORKS_H__

#include "cocos2d.h"

class GlobalDataWorks : public cocos2d::CCNode
{

private:
	static GlobalDataWorks* m_globalData; // constructor
	static int m_score; // value to aqcuire and set

public:
	virtual bool init();
	static GlobalDataWorks* getInstance(); //returns a class instance pointer
	int getScore(){ return m_score; }; //acquire the value from a scene.
	void setScore(int score){ m_score = score; }; //take acquired value and set it as a value in a scene.
	
	// implement the static node method manually
	CREATE_FUNC(GlobalDataWorks)

};


#endif //__GLOBAL_DATA_WORKS_H__