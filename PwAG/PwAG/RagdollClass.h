#ifndef _RAGDOLLCLASS_
#define _RAGDOLLCLASS_

#include "ModelClass.h"

#include <btBulletDynamicsCommon.h>
#include <assimp\scene.h>

#include <vector>

#define BIT(x) (1<<(x))

#define num_bones 21
#define num_joints 20

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif

class RagdollClass
{
public:
	enum bones
	{
		Head = 0,
		Neck,
		Spine2,
		Spine1,
		Spine0,

		RArm0,
		RArm1,
		RArm2,
		RHand,

		LArm0,
		LArm1,
		LArm2,
		LHand,

		RLeg0,
		RLeg1,
		RLeg2,
		RFoot,

		LLeg0,
		LLeg1,
		LLeg2,
		LFoot
	};

	enum joints
	{
		Head_to_Neck = 0,
		Neck_to_Spine2,
		Spine2_to_Spine1,
		Spine1_to_Spine0,
		Spine1_to_RArm0,
		Spine1_to_LArm0,
		Spine0_to_RLeg0,
		Spine0_to_LLeg0,

		RArm0_to_RArm1,
		RArm1_to_RArm2,
		RArm2_to_RHand,

		LArm0_to_LArm1,
		LArm1_to_LArm2,
		LArm2_to_LHand,

		RLeg0_to_RLeg1,
		RLeg1_to_RLeg2,
		RLeg2_to_RFoot,

		LLeg0_to_LLeg1,
		LLeg1_to_LLeg2,
		LLeg2_to_LFoot
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
	btTypedConstraint** m_joints;

	int m_shaderType;

private:
	bool Initialize(int bone,
					btScalar size_x,
					btScalar size_y,
					btScalar size_z,
					aiVector3D position, btScalar offset_x, btScalar offset_y, btScalar offset_z,
					aiVector3D rotation, 
					btScalar mass, 
					btScalar inertia_x, btScalar inertia_y, btScalar inertia_z);

	btCollisionShape** m_collisionShapes;
	aiBone** m_bones;
};

#endif
