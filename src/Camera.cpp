#include "Camera.h"

//Alan Duong, 03/31/19
//This is a wrapper for ofCamera to help do screenshake.

View::View()
{
	punchPos = ofVec2f(0.0f, 0.0f);
}

void View::posViewPunch(ofVec2f _punchPos)
{
	if (_punchPos.lengthSquared() > punchPos.lengthSquared())
	{
		punchPos = _punchPos;
	}
}

void View::update()
{
	//reset punch pos
	//punchPos.x = approach(punchPos.x, 0, (punchPos.x) * 0.1);
	//punchPos.y = approach(punchPos.y, 0, (punchPos.y) * 0.1);
	punchPos += (-punchPos) * 0.1;

	cam.setPosition(punchPos.x, punchPos.y, 1000.0f);
}

ofVec2f View::getTotalOffset()
{
	return punchPos;
}
