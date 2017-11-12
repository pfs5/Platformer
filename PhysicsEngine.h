#pragma once
#include "GameObject.h"

#include <vector>

class GameObject;

namespace Physics {
	struct Collider {
		Collider() : isActive(true) {};
		float x;
		float y;
		float width;
		float height;
	
		bool isActive;

		GameObject* gameObject;
	};

	class PhysicsEngine {
		std::vector<Collider*> m_staticColliders;
		std::vector<Collider*> m_dynamicColliders;
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void update(float _dt);

		/// <summary>
		///		Adds game object into the physics engine. Activates collisions.
		/// </summary>
		void addGameObject(GameObject& _o);
	};
}
