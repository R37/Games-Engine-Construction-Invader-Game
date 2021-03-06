#pragma once
#include "HAPI_lib.h"
using namespace HAPISPACE;
#include <unordered_map>

class Sprite;

class Visulisation
{
	private:
		int m_screenWidth = 1024;
		int m_screenHeight = 768;
		BYTE* m_screen{ nullptr };
		std::unordered_map<std::string, Sprite*> m_spriteMap;
	public:
		~Visulisation();

		bool Initialise();

		bool CreateSprite(const std::string& spriteName, const std::string& filename);

		void RenderClippedSprite(const std::string& spriteName, float posX, float posY);
		void Visulisation::RenderBackgroundSprite(const std::string& spriteName, float posX, float posY);
		Visulisation() = default;
		void ClearScreen();
		int GetScreenWidth() const { return m_screenWidth; }
		int GetScreenHeight() const { return m_screenHeight; }

		float GetTextureWidth(const std::string& SpriteName);
		float GetTextureHeight(const std::string& SpriteName);
};

