
#pragma once

#include "KatanaEngine.h"

using namespace KatanaEngine;

class Level;

/** @brief The gameplay screen for the Space Fighter Game.
	It is responsible for creating and loading levels.
	@see Level
	@see Screen
*/
class GameplayScreen : public Screen
{

public:

	/** @brief Instantiate a gameplay screen object.
		@param levelIndex The index of the level to load. */
	GameplayScreen(const int levelIndex = 0);
	virtual ~GameplayScreen() { }

	/** @brief Load the content for the screen.
		@param pResourceManager A pointer to the game's resource manager. */
	virtual void LoadContent(ResourceManager *pResourceManager);

	/** @brief Handle input for the screen.
		@param pInput The current input state. */
	virtual void HandleInput(const InputState *pInput);

	/** @brief Update the screen.
		@param pGameTime Timing values including time since last update. */
	virtual void Update(const GameTime *pGameTime);

	/** @brief Render the screen.
		@param pSpriteBatch The game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch *pSpriteBatch);

	/** @brief Load a specific level.
		@param levelIndex The index of the level to load. */
	virtual void LoadLevel(const int levelIndex);


private:

	int m_levelIndex = 0;

	Level *m_pLevel = nullptr;

	ResourceManager *m_pResourceManager = nullptr;

};
