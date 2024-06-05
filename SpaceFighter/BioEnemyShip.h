
#pragma once

#include "EnemyShip.h"

/** @brief Represents an enemy ship that is biological in nature. */
class BioEnemyShip : public EnemyShip
{

public:

	/** @brief Creates a new instance of BioEnemyShip. */
	BioEnemyShip();
	virtual ~BioEnemyShip() { }

	/** @brief Sets the texture that will be used to render the enemy ship.
		@param pTexture A pointer to the texture. */
	virtual void SetTexture(Texture *pTexture) { m_pTexture = pTexture; }

	/** @brief Updates the enemy ship.
		@param pGameTime A pointer to the game time object. */
	virtual void Update(const GameTime *pGameTime);

	/** @brief Draws the enemy ship.
		@param pSpriteBatch A pointer to the game's sprite batch. */
	virtual void Draw(SpriteBatch *pSpriteBatch);


private:

	Texture *m_pTexture = nullptr;

};