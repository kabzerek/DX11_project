#ifndef _RAGDOLLCLASS_
#define _RAGDOLLCLASS_

#include "ModelClass.h"

#include <btBulletDynamicsCommon.h>

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

private:
	bool Initialize(aiVector3D, aiVector3D, btScalar, btScalar, btScalar, btScalar, int);

	ModelClass* m_model;
	btRigidBody*[] m_rigidBodys;
	//std::vector<btRigidBody*> m_rigidBodys;
	btCollisionShape*[] m_collisionShapes;
	//std::vector<btCollisionShape*> m_collisionShapes;
	"bone"*[] m_bones;

	int m_shaderType;
};

#endif
