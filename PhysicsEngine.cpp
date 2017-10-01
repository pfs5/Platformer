#include "stdafx.h"
#include <cmath>
#include <iostream>
#include "PhysicsEngine.h"
#include "Util.h"

namespace Physics {
	PhysicsEngine::PhysicsEngine() {
	}


	PhysicsEngine::~PhysicsEngine() {
	}

	void PhysicsEngine::PhysicsEngine::update(float _dt) {
		// Collision detection
		for (int i = 0; i < m_dynamicColliders.size(); ++i) {
			for (int j = 0; j < m_staticColliders.size(); ++j) {
				Collider *collDyn = m_dynamicColliders[i];
				Collider *collStat = m_staticColliders[j];

				// x axis collision
				float diffX_1 = collDyn->x - (collStat->x + collStat->width);
				float diffX_2 = collStat->x - (collDyn->x + collDyn->width);

				int collisionDirectionX = (diffX_1 > diffX_2) ? -1 : 1;
				float collisionDepthX = (collisionDirectionX < 0) ? diffX_1 : diffX_2;

				// y axis collision
				float diffY_1 = collDyn->y - (collStat->y + collStat->height);
				float diffY_2 = collStat->y - (collDyn->y + collDyn->height);

				int collisionDirectionY = (diffY_1 > diffY_2) ? -1 : 1;
				float collisionDepthY = (collisionDirectionY < 0) ? diffY_1 : diffY_2;

				// Resolve collision
				if (collisionDepthX < 0.f && collisionDepthY < 0.f) {
					float xDisplacement = (collisionDepthX > collisionDepthY) ? collisionDepthX * collisionDirectionX : 0.f;
					float yDisplacement = (collisionDepthX > collisionDepthY) ? 0.f : collisionDepthY * collisionDirectionY;
					collDyn->gameObject->collisionImpulse(sf::Vector2f(xDisplacement, yDisplacement));
				}
			}
		}
	}

	void PhysicsEngine::PhysicsEngine::addGameObject(GameObject & _o) {
		if (_o.getCollider() != nullptr) {
			if (_o.isStatic()) {
				m_staticColliders.push_back(_o.getCollider());
			}
			else {
				m_dynamicColliders.push_back(_o.getCollider());
			}
		}
	}
}