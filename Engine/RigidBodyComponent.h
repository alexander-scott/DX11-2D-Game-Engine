#pragma once

#include "IComponent.h"
#include "IUpdateable.h"
#include "IMessageable.h"

class RigidBodyComponent : public IComponent, public IMessageable
{
public:
	RigidBodyComponent(float staticF, float dynamicF, float rest);
	~RigidBodyComponent();

	virtual void RecieveMessage(IMessage& message) override;

	void ApplyForce(const Vec2& f);
	void ApplyImpulse(const Vec2& impulse, const Vec2& contactVector);

	void SetStatic();
	void LockRotation() { _rotationLocked = true; }

#pragma region Getters and Setters

	Mat2 GetOrientationMatrix() { return rigidbodyData.orientationMatrix; }
	void SetOrientationMatrix(Mat2 mat) { rigidbodyData.orientationMatrix = mat; }

	Vec2 GetVelocity() { return rigidbodyData.velocity; }
	void SetVelocity(Vec2 vel) { rigidbodyData.velocity = vel; }

	float GetAngularVelocity() { return rigidbodyData.angularVelocity; }
	void SetAngularVelocity(float vel) { rigidbodyData.angularVelocity = vel; }

	float GetTorque() { return rigidbodyData.torque; }
	void SetTorque(float torq) { rigidbodyData.torque = torq; }

	Vec2 GetForce() { return rigidbodyData.force; }
	void SetForce(Vec2 forc) { rigidbodyData.force = forc; }

	float GetIntertia() { return rigidbodyData.intertia; }
	void SetIntertia(float intert) { rigidbodyData.intertia = intert; }

	float GetInverseIntertia() { return rigidbodyData.inverseInertia; }
	void SetInverseIntertia(float intert) { rigidbodyData.inverseInertia = intert; }

	float GetMass() { return rigidbodyData.mass; }
	void SetMass(float m) { rigidbodyData.mass = m; }

	float GetInverseMass() { return rigidbodyData.inverseMass; }
	void SetInverseMass(float im) { rigidbodyData.inverseMass = im; }

	float GetStaticFriction() { return rigidbodyData.staticFriction; }
	void SetStaticFriction(float frict) { rigidbodyData.staticFriction = frict; }

	float GetDynamicFriction() { return rigidbodyData.dynamicFriction; }
	void SetDynamicFriction(float frict) { rigidbodyData.dynamicFriction = frict; }

	float GetRestitution() { return rigidbodyData.restitution; }
	void SetRestitution(float rest) { rigidbodyData.restitution = rest; }

	void SetGrounded(bool grounded) { _grounded = grounded; }
	bool GetGrounded() { return _grounded; }

	bool RotationLocked() {	return _rotationLocked;	}

#pragma endregion

private:
	RigidBodyData rigidbodyData = RigidBodyData(Vec2(0, 0), 0, 0, Vec2(0, 0), 0, 0, 0);
	bool				_rotationLocked;
	bool				_grounded;
};

