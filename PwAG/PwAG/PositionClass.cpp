////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PositionClass.h"


PositionClass::PositionClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_forwardSpeed	 = 0.0f;
	m_backwardSpeed  = 0.0f;
	m_leftwardSpeed  = 0.0f;
	m_rightwardSpeed = 0.0f;
	m_upwardSpeed    = 0.0f;
	m_downwardSpeed  = 0.0f;

	m_turnRate = 0.2f;

	//m_leftTurnSpeed  = 0.0f;
	//m_rightTurnSpeed = 0.0f;
	//m_lookUpSpeed    = 0.0f;
	//m_lookDownSpeed  = 0.0f;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}


void PositionClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}


void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}


void PositionClass::MoveForward(bool keydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if(m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if(m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radiansY = m_rotationY * 0.0174532925f;
	float radiansX = m_rotationX * 0.0174532925f;

	// Update the position.
	float z = cosf(radiansX) * cosf(radiansY);
	float y = -sinf(radiansX);
	float x = cosf(radiansX) * sinf(radiansY);

	m_positionX += x * m_forwardSpeed;
	m_positionY += y * m_forwardSpeed;
	m_positionZ += z * m_forwardSpeed;
	
	return;
}


void PositionClass::MoveBackward(bool keydown)
{
	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_backwardSpeed += m_frameTime * 0.001f;

		if(m_backwardSpeed > (m_frameTime * 0.03f))
		{
			m_backwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.0007f;
		
		if(m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radiansY = m_rotationY * 0.0174532925f;
	float radiansX = m_rotationX * 0.0174532925f;

	// Update the position.
	float z = cosf(radiansX) * cosf(radiansY);
	float y = -sinf(radiansX);
	float x = cosf(radiansX) * sinf(radiansY);

	m_positionX -= x * m_backwardSpeed;
	m_positionY -= y * m_backwardSpeed;
	m_positionZ -= z * m_backwardSpeed;

	return;
}

void PositionClass::MoveLeftward(bool keydown)
{
	// leftdate the leftward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftwardSpeed += m_frameTime * 0.003f;

		if(m_leftwardSpeed > (m_frameTime * 0.03f))
		{
			m_leftwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_leftwardSpeed -= m_frameTime * 0.002f;

		if(m_leftwardSpeed < 0.0f)
		{
			m_leftwardSpeed = 0.0f;
		}
	}

	float rot = m_rotationY - 90;
	if(rot < 0)
		rot = 360 + rot;

	// Convert degrees to radians.
	float radiansY = rot * 0.0174532925f;
	float radiansX = m_rotationX * 0.0174532925f;

	// Update the position.
	float cosfx = cosf(radiansX);
	if (cosfx > 0.0f)
		cosfx = 1.0f;
	else if (cosfx < 0.0f)
		cosfx = -1.0f;
	else
		cosfx = 0.0f;

	float z = cosfx * cosf(radiansY);
	float x = cosfx * sinf(radiansY);

	m_positionX += x * m_leftwardSpeed;
	m_positionZ += z * m_leftwardSpeed;

	return;
}

void PositionClass::MoveRightward(bool keydown)
{
	// rightdate the rightward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_rightwardSpeed += m_frameTime * 0.003f;

		if(m_rightwardSpeed > (m_frameTime * 0.03f))
		{
			m_rightwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_rightwardSpeed -= m_frameTime * 0.002f;

		if(m_rightwardSpeed < 0.0f)
		{
			m_rightwardSpeed = 0.0f;
		}
	}

	float rot = m_rotationY - 90;
	if(rot < 0)
		rot = 360 + rot;

	// Convert degrees to radians.
	float radiansY = rot * 0.0174532925f;
	float radiansX = m_rotationX * 0.0174532925f;

	// Update the position.
	float cosfx = cosf(radiansX);
	if (cosfx > 0.0f)
		cosfx = 1.0f;
	else if (cosfx < 0.0f)
		cosfx = -1.0f;
	else
		cosfx = 0.0f;

	float z = cosfx * cosf(radiansY);
	float x = cosfx * sinf(radiansY);

	m_positionX -= x * m_rightwardSpeed;
	m_positionZ -= z * m_rightwardSpeed;

	return;
}

void PositionClass::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_upwardSpeed += m_frameTime * 0.003f;

		if(m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.002f;

		if(m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += m_upwardSpeed;

	return;
}

void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if(m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.002f;

		if(m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= m_downwardSpeed;

	return;
}

void PositionClass::Turn(bool keyDown, int deltaX, int deltaY)
{
	float m_YTurnSpeed = 0.0f;
	float m_XTurnSpeed = 0.0f;

	if(keyDown)
	{
		m_YTurnSpeed = m_turnRate * (float)deltaX;
		m_XTurnSpeed = m_turnRate * (float)deltaY;
	}

	m_rotationY += m_YTurnSpeed;
	m_rotationX += m_XTurnSpeed;

	if(m_rotationY < 0.0f)
		m_rotationY = 360.0f + m_rotationY;
	if(m_rotationY > 360.0f)
		m_rotationY -= 360.0f;
	if(m_rotationX < 0.0f)
		m_rotationX = 360.0f + m_rotationX;
	if(m_rotationX > 360.0f)
		m_rotationX -= 360.0f;
}

void PositionClass::GetSpeed(float& fs, float& bs, float& ls, float& rs)
{
	fs = m_forwardSpeed;
	bs = m_backwardSpeed;
	ls = m_leftwardSpeed;
	rs = m_rightwardSpeed;
	return;
}

//void PositionClass::TurnLeft(bool keydown)
//{
//	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
//	if(keydown)
//	{
//		m_leftTurnSpeed += m_frameTime * 0.01f;
//
//		if(m_leftTurnSpeed > (m_frameTime * 0.15f))
//		{
//			m_leftTurnSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_leftTurnSpeed -= m_frameTime* 0.005f;
//
//		if(m_leftTurnSpeed < 0.0f)
//		{
//			m_leftTurnSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationY -= m_leftTurnSpeed;
//
//	// Keep the rotation in the 0 to 360 range.
//	if(m_rotationY < 0.0f)
//	{
//		m_rotationY += 360.0f;
//	}
//
//	return;
//}
//
//
//void PositionClass::TurnRight(bool keydown)
//{
//	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
//	if(keydown)
//	{
//		m_rightTurnSpeed += m_frameTime * 0.01f;
//
//		if(m_rightTurnSpeed > (m_frameTime * 0.15f))
//		{
//			m_rightTurnSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_rightTurnSpeed -= m_frameTime* 0.005f;
//
//		if(m_rightTurnSpeed < 0.0f)
//		{
//			m_rightTurnSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationY += m_rightTurnSpeed;
//
//	// Keep the rotation in the 0 to 360 range.
//	if(m_rotationY > 360.0f)
//	{
//		m_rotationY -= 360.0f;
//	}
//
//	return;
//}
//
//
//void PositionClass::LookUpward(bool keydown)
//{
//	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
//	if(keydown)
//	{
//		m_lookUpSpeed += m_frameTime * 0.01f;
//
//		if(m_lookUpSpeed > (m_frameTime * 0.15f))
//		{
//			m_lookUpSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_lookUpSpeed -= m_frameTime* 0.005f;
//
//		if(m_lookUpSpeed < 0.0f)
//		{
//			m_lookUpSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationX -= m_lookUpSpeed;
//
//	// Keep the rotation maximum 90 degrees.
//	if(m_rotationX > 90.0f)
//	{
//		m_rotationX = 90.0f;
//	}
//
//	return;
//}
//
//
//void PositionClass::LookDownward(bool keydown)
//{
//	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
//	if(keydown)
//	{
//		m_lookDownSpeed += m_frameTime * 0.01f;
//
//		if(m_lookDownSpeed > (m_frameTime * 0.15f))
//		{
//			m_lookDownSpeed = m_frameTime * 0.15f;
//		}
//	}
//	else
//	{
//		m_lookDownSpeed -= m_frameTime* 0.005f;
//
//		if(m_lookDownSpeed < 0.0f)
//		{
//			m_lookDownSpeed = 0.0f;
//		}
//	}
//
//	// Update the rotation.
//	m_rotationX += m_lookDownSpeed;
//
//	// Keep the rotation maximum 90 degrees.
//	if(m_rotationX < -90.0f)
//	{
//		m_rotationX = -90.0f;
//	}
//
//	return;
//}