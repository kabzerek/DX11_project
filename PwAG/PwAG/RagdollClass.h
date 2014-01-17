#ifndef _RAGDOLLCLASS_
#define _RAGDOLLCLASS_

#include "ModelClass.h"

#include <btBulletDynamicsCommon.h>
#include <assimp\scene.h>

#include <vector>

#define num_bones 21

class RagdollClass
{
public:
	enum bones
	{
		Head = 0,
		Neck = 1,
		Spine2 = 2,
		Spine1 = 3,
		Spine0 = 4,

		RArm0 = 5,
		RArm1 = 6,
		RArm2 = 7,
		RHand = 8,

		LArm0 = 9,
		LArm1 = 10,
		LArm2 = 11,
		LHand = 12,

		RLeg0 = 13,
		RLeg1 = 14,
		RLeg2 = 15,
		RFoot = 16,

		LLeg0 = 17,
		LLeg1 = 18,
		LLeg2 = 19,
		LFoot = 20
	};

public:
	RagdollClass(void);
	RagdollClass(const RagdollClass&);
	~RagdollClass(void);

	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*, aiVector3D, aiVector3D, std::string, int);
	void Shutdown();

	void Update();

public:
	ModelClass* m_model;
	btRigidBody** m_rigidBodys;

	int m_shaderType;

private:
	bool Initialize(int bone,
					btScalar size_x,
					btScalar size_y,
					btScalar size_z,
					aiVector3D position, aiVector3D rotation, 
					btScalar mass, 
					btScalar inertia_x, btScalar inertia_y, btScalar inertia_z);

	btCollisionShape** m_collisionShapes;
	aiBone** m_bones;
};

#endif
