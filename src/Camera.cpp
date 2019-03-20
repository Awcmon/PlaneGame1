#include "Camera.h"

View::View()
{
	punchPos = ofVec2f(0.0f, 0.0f);
}

void View::posViewPunch(ofVec2f pos)
{
	punchPos = pos;
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