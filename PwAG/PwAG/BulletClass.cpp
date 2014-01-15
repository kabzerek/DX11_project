#include "BulletClass.h"


BulletClass::BulletClass(void)
{
	//m_broadphase = 0;
	//m_collisionConfiguration = 0;
	//m_dispatcher = 0;
	//m_solver = 0;
	m_dynamicsWorld = 0;
}


BulletClass::~BulletClass(void)
{
}

bool BulletClass::Initialize(void)
{
	// Build the broadphase
	btBroadphaseInterface* m_broadphase = new btDbvtBroadphase();
	if(!m_broadphase)
		return false;

    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* m_collisionConfiguration = new btDefaultCollisionConfiguration();
	if(!m_collisionConfiguration)
		return false;
    btCollisionDispatcher* m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	if(!m_dispatcher)
		return false;

    // The actual physics solver
    btSequentialImpulseConstraintSolver* m_solver = new btSequentialImpulseConstraintSolver;
	if(!m_solver)
		return false;

    // The world.
    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	if(!m_dynamicsWorld)
		return false;

    m_dynamicsWorld->setGravity(btVector3(0,-10,0));

	return true;
}

void BulletClass::Shutdown(void)
{
	if(m_dynamicsWorld)
		delete m_dynamicsWorld;
	m_dynamicsWorld = 0;

	//if(m_solver)
	//	delete m_solver;
	//m_solver = 0;

	//if(m_dispatcher)
	//	delete m_dispatcher;
	//m_dispatcher = 0;

	//if(m_collisionConfiguration)
	//	delete m_collisionConfiguration;
	//m_collisionConfiguration = 0;

	//if(m_broadphase)
	//	delete m_broadphase;
	//m_broadphase = 0;
}
