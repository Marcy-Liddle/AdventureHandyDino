#include "Character.h"

void Character::worldCollision(GameObject& collider)
{
	sf::FloatRect entityCollider = getCollisionBox();
	sf::FloatRect wallBounds = collider.getCollisionBox();
	auto overlap = entityCollider.findIntersection(wallBounds);
	if (!overlap) return; // if there is no overlap, then leave.
	if (overlap->size.x < overlap->size.y)
	{
		// taller than wide -> collision is side-on
		if (entityCollider.position.x < wallBounds.position.x)
			move({ -overlap->size.x, 0 });
		else
			move({ overlap->size.x, 0 });
	}
	else
	{
		if (entityCollider.position.y < wallBounds.position.y)
		{
			// We are above the wall (Landing)
			move({ 0, -overlap->size.y });
			m_velocity.y = 0;       // Stop falling

		}
		else
		{
			// We hit the ceiling (Bonk)
			move({ 0, overlap->size.y });
			m_velocity.y = 0;       // Stop moving up
		}
	}
}

void Character::invincibiltyFrames( float dt)
{
	m_invulnerableTimer -= dt;

	if (m_invulnerableTimer <= 0)
	{
		m_invulnerableTimer = INVINCIBILITY_TIME;
		m_isInvincible = false;
		
	}
}

