#ifndef _ENGINEOBJECTCLASS_
#define _ENGINEOBJECTCLASS_

#include "ModelClass.h"

#include <btBulletDynamicsCommon.h>

#include <string>

class EngineObjectClass
{
public:
	EngineObjectClass(void);
	~EngineObjectClass(void);

	// for StaticPlane
	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*, aiVector3D, aiVector3D, std::string, btScalar, btScalar, btScalar, btScalar);
	// for Sphere
	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*, aiVector3D, aiVector3D, std::string, btScalar, btScalar, btScalar, btScalar, btScalar);
	// for Capsule (Capsule/CapsuleX/CapsuleZ) and Cone (Cone/ConeX/ConeZ)
	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*, aiVector3D, aiVector3D, std::string, btScalar, btScalar, btScalar, btScalar, btScalar, btScalar);
	// for Box and Cylinder (Cylinder/CylinderX/CylinderZ)
	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*, aiVector3D, aiVector3D, std::string, btScalar, btScalar, btScalar, btScalar, btScalar, btScalar, btScalar);
	void Shutdown();

	void Update();

private:
	bool Initialize(aiVector3D, aiVector3D, btScalar, btScalar, btScalar, btScalar);

public:
	ModelClass* m_model;
	btRigidBody* m_rigidBody;
	btCollisionShape* m_collisionShape;	
};

#endif
