
#pragma once

#include "Ship.h"

/** brief Represents the player's ship. */
class PlayerShip : public Ship
{

public:

	/** @brief Creates a new instance of PlayerShip. */
	PlayerShip() { }
	virtual ~PlayerShip() { }

	/** @brief Loads the content for the player ship.
		@param pResourceManager A pointer to the game's resource manager. */
	virtual void LoadContent(ResourceManager *pResourceManager);

	/** @brief Updates the player ship.
		@param pGameTime A pointer to the game time object. */
	virtual void Update(const GameTime *pGameTime);

	/** @brief Draws the player ship.
		@param pSpriteBatch A pointer to the game's sprite batch. */
	virtual void Draw(SpriteBatch *pSpriteBatch);

	/** @brief Handles input for the player ship.
		@param pInput A pointer to the current input state. */
	virtual void HandleInput(const InputState *pInput);

	/** @brief Initializes the player ship.
		@param pLevel A pointer to the current level.
		@param startPosition The starting position of the player ship. */
	virtual void Initialize(Level *pLevel, Vector2 &startPosition);

	/** @brief Gets the half dimensions of the player ship.
		@return Returns the half dimensions of the player ship. */
	virtual Vector2 GetHalfDimensions() const;

	/** @brief Sets the desired direction of the player ship, based on input.
		@param direction The desired direction. */
	virtual void SetDesiredDirection(const Vector2 direction) { m_desiredDirection.Set(direction); }

	/** @brief Gets the string representation of the player ship.
		@return Returns the string "Player Ship". */
	virtual std::string ToString() const { return "Player Ship"; }

	/** @brief Gets the collision type of the player ship.
		@return Returns the collision type of the player ship. */
	virtual CollisionType GetCollisionType() const { return (CollisionType::Player | CollisionType::Ship); }

	/** @brief Prevents the player ship from moving off the screen.
		@param isConfined True to confine the player ship to the screen, false otherwise. */
	virtual void ConfineToScreen(const bool isConfined = true) { m_isConfinedToScreen = isConfined; }


protected:

	/** @brief Sets the responsiveness of the player ship.
		@param responsiveness The responsiveness of the player ship. */
	virtual void SetResponsiveness(const float responsiveness);

	/** @brief Gets the responsiveness of the player ship.
		@return Returns the responsiveness of the player ship. */
	virtual float GetResponsiveness() const { return m_responsiveness; }

	/** @brief Gets the desired direction of the player ship.
		@return Returns the desired direction of the player ship. */
	virtual Vector2 GetDesiredDirection() const { return m_desiredDirection; }


private:

	Vector2 m_desiredDirection;
	Vector2 m_velocity;

	float m_responsiveness = 0;

	bool m_isConfinedToScreen = false;

	Texture *m_pTexture = nullptr;

};