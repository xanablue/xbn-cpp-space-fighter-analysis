#pragma once

#include "KatanaEngine.h"

using namespace KatanaEngine;

/** @brief The main menu screen for the game. */
class MainMenuScreen : public MenuScreen
{

public:

	/** @brief Instantiate a main menu screen object. */
	MainMenuScreen();
	virtual ~MainMenuScreen() { }

	/** @brief Load the content for the screen.
		@param pResourceManager A pointer to the game's resource manager. */
	virtual void LoadContent(ResourceManager *pResourceManager);
	
	/** @brief Unload the content for the screen. */
	virtual void Update(const GameTime *pGameTime);

	/** @brief Render the screen.
		@param pSpriteBatch The game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch *pSpriteBatch);

	/** @brief Set the flag to quit the game, so the game will exit when screen fades out. */
	virtual void SetQuittingGame() { m_isQuittingGame = true; }

	/** @brief Check if the game is quitting.
		@return True if the game is quitting. */
	virtual bool IsQuittingGame() { return m_isQuittingGame; }


private:
	
	Texture *m_pTexture = nullptr;

	Vector2 m_texturePosition;

	bool m_isQuittingGame = false;

};