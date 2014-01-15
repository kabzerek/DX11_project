#ifndef _BULLETCLASS_H_
#define _BULLETCLASS_H_

#include <btBulletDynamicsCommon.h>

class BulletClass
{
public:
	BulletClass(void);
	BulletClass(const BulletClass&);
	~BulletClass(void);

	bool Initialize();
	void Shutdown();

private:

public:
	btDiscreteDynamicsWorld* m_dynamicsWorld;

private:
	//btBroadphaseInterface* m_broadphase;

	//btDefaultCollisionConfiguration* m_collisionConfiguration;
	//btCollisionDispatcher* m_dispatcher;

	//btSequentialImpulseConstraintSolver* m_solver;
};

#endif
