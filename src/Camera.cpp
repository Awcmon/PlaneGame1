#include "Camera.h"

void Camera::posViewPunch(ofVec2f pos)
{
	punchPos = pos;
}

void Camera::update()
{
	//reset punch pos
	punchPos.x = approach(punchPos.x, 0, (punchPos.x) * 0.1);
}
