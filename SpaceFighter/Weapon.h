
#pragma once

#include "KatanaEngine.h"
#include "Projectile.h"
#include "TriggerType.h"

using namespace KatanaEngine;

/** @brief Base class for all weapons that can be fired by a game object. */
class Weapon : public IAttachment
{

public:

	/** @brief Instantiate a weapon object.
		@param isActive A flag to determine if the weapon is active. */
	Weapon(const std::string &key, bool isAttachedToPlayer = true, bool isActive = true, TriggerType triggerType = TriggerType::Primary)
	{
		m_key = key;
		m_isAttachedToPlayer = isAttachedToPlayer;
		m_isActive = isActive;
		SetTriggerType(triggerType);
	}
	virtual ~Weapon() { }

	/** @brief Update the weapon.
		@param pGameTime Timing values including time since last update. */
	virtual void Update(const GameTime& gameTime) { };

	/** @brief Render the weapon.
		@param spriteBatch A reference to the game's sprite batch, used for rendering.
		@remark Generally, this is not used, but can be overridden by derived classes if you want to render the weapon. */
	virtual void Draw(SpriteBatch& spriteBatch) { };

	/** @brief Attempt to fire the weapon.
		@param triggerType The type of trigger that fired the weapon.
		@remark The weapon will only fire if it is active, and may not fire if it is on cooldown.
		*/
	virtual void Fire(TriggerType triggerType) = 0;

	///** @brief Set the game object that the weapon is attached to.
	//	@param pGameObject A pointer to the game object. */
	//virtual void SetGameObject(GameObject *pGameObject) { m_pGameObject = pGameObject; }

	///** @brief Set the offset of the weapon from the game object's position.
	//	@param offset The offset of the weapon. */
	//virtual void SetOffset(Vector2 offset) { m_offset = offset; }

	/** @brief Set the type of trigger that can fire the weapon.
		@param triggerType The type of trigger.
		@remark This is to help decouple the weapon from the input system. */
	virtual void SetTriggerType(TriggerType triggerType) { m_triggerType = triggerType; }

	/** @brief Set the pool of projectiles that the weapon can fire.
		@param pProjectiles A pointer to the projectile pool.
		@see GetProjectile */
	virtual void SetProjectilePool(std::vector<Projectile *> *pProjectiles) { m_pProjectiles = pProjectiles; }

	/** @brief Activate the weapon. */
	virtual void Activate() { m_isActive = true; }

	/** @brief Deactivate the weapon. */
	virtual void Dectivate() { m_isActive = false; }

	/** @brief Determine if the weapon is active.
		@return True if the weapon is active. */
	virtual bool IsActive() const { return m_isActive && m_pGameObject->IsActive(); }

	/** @brief Set the sound that will be played when the weapon is fired.
		@param pSound A pointer to the audio sample. */
	virtual void SetFireSound(AudioSample* pSound) { m_pFireSound = pSound; }

	/** @brief Get the sound that will be played when the weapon is fired.
		@return A pointer to the audio sample. */
	virtual AudioSample* GetFireSound() { return m_pFireSound; }

	/** @brief Determine if the weapon is attached to the player.
		@return True if the weapon is attached to the player. */
	virtual bool IsAttachedToPlayer() const { return m_isAttachedToPlayer; }

	/** @brief Attach the weapon to a game object.
		@param pAttachable A pointer to the attachable game object.
		@param position The offset position of the weapon relative to the game object. */
	virtual void AttachTo(IAttachable* pAttachable, Vector2& position) {
		m_pGameObject = dynamic_cast<GameObject*>(pAttachable);
		m_offset = position;
	}


	virtual std::string GetKey() const { return m_key; }

	virtual std::string GetAttachmentType() const { return "Weapon"; }


protected:

	/** @brief Get the game object that the weapon is attached to.
		@return A pointer to the game object. */
	virtual TriggerType GetTriggerType() const { return m_triggerType; }

	/** @brief Get the screen position of the weapon.
		@return The screen position of the weapon. */
	virtual Vector2 GetPosition() const { return m_pGameObject->GetPosition() + m_offset; }

	/** @brief Get a projectile from the pool.
		@return A pointer to a projectile.
		@remark This helps us avoid instantiating projectiles while the level is running. */
	virtual Projectile *GetProjectile()
	{
		for (Projectile *pProjectile : *m_pProjectiles)
		{
			if (!pProjectile->IsActive()) return pProjectile;
		}

		return nullptr;
	}


private:

	bool m_isActive = true;
	bool m_isAttachedToPlayer = true;

	std::string m_key;

	GameObject *m_pGameObject = nullptr;

	Vector2 m_offset;

	TriggerType m_triggerType = TriggerType::Primary;

	std::vector<Projectile *> *m_pProjectiles;

	AudioSample* m_pFireSound = nullptr;

};

