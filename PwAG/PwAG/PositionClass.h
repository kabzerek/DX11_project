////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void GetPosition(float&, float&, float&);
	void GetRotation(float&, float&, float&);

	void GetSpeed(float&, float&, float&, float&);

	void SetFrameTime(float);

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveLeftward(bool);
	void MoveRightward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void Turn(bool, int, int);
	//void TurnLeft(bool);
	//void TurnRight(bool);
	//void LookUpward(bool);
	//void LookDownward(bool);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_leftwardSpeed, m_rightwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	//float m_leftTurnSpeed, m_rightTurnSpeed;
	//float m_lookUpSpeed, m_lookDownSpeed;
	float m_turnRate;
};

#endif