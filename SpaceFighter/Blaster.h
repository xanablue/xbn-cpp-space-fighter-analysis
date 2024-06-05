
#pragma once

#include "Weapon.h"

/** @brief Represents a blaster weapon that can be fired by a game object. */
class Blaster : public Weapon
{

public:

	/** @brief Instantiate a blaster object.
		@param isActive A flag to determine if the weapon is active. */
	Blaster(const bool isActive) : Weapon(isActive) { }
	virtual ~Blaster() { }

	/** @brief Update the blaster.
		@param pGameTime Timing values including time since last update. */
	virtual void Update(const GameTime *pGameTime)
	{
		if (m_cooldown > 0) m_cooldown -= pGameTime->GetTimeElapsed();
	}

	/** @brief Check if the blaster is ready to fire.
		@return True if the blaster is ready to fire. */
	virtual bool CanFire() const { return m_cooldown <= 0; }

	/** @brief Reset the cooldown of the blaster. */
	virtual void ResetCooldown() { m_cooldown = 0; }

	/** @brief Get the number of seconds the blaster must wait between shots.
		@return The number of seconds the blaster must wait between shots. */
	virtual float GetCooldownSeconds() { return m_cooldownSeconds; }

	/** @brief Set the number of seconds the blaster must wait between shots.
		@param seconds The number of seconds the blaster must wait between shots. */
	virtual void SetCooldownSeconds(const float seconds) { m_cooldownSeconds = seconds; }

	/** @brief Fire the blaster.
		@param triggerType The type of trigger that fired the weapon.
		@remark If the triggerType doesn't match that of the Blaster, the command will be ignored. */
	virtual void Fire(TriggerType triggerType)
	{
		if (!IsActive()) return;
		if (!CanFire()) return;
		if (!triggerType.Contains(GetTriggerType())) return;

		Projectile *pProjectile = GetProjectile();
		if (!pProjectile) return;
		
		AudioSample* pAudio = GetFireSound();
		if (pAudio) pAudio->Play();

		pProjectile->Activate(GetPosition(), IsAttachedToPlayer());
		m_cooldown = m_cooldownSeconds;
	}


private:

	float m_cooldown = 0;
	float m_cooldownSeconds = 0.35;


};