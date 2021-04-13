#pragma once
#include "pch.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "external/SDL2_gfx/SDL2_gfxPrimitives.h"

class LTexture
{
public:
	// Initialize
	LTexture();

	// Destroy
	~LTexture();

	// Copy constructor
	LTexture(const LTexture& other) {
		mTexture = other.mTexture;
		mWidth = other.mWidth;
		mHeight = other.mHeight;
	}

	LTexture& operator=(LTexture const& other) {
		mTexture = other.mTexture;
		mWidth = other.mWidth;
		mHeight = other.mHeight;
		return *this;
	}

	void Cleanup();

	// Load image at specified path
	bool loadFromFile(std::string path);

	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont);

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	
	// Set blending mode
	void setBlendMode(SDL_BlendMode blending);

	// Set Alpha
	void setAlpha(Uint8 alpha);

	// Render texture at given point
	void render(int x, int y, double scale = 1.0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Get image dimensions
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

private:
	// Actual hardware texture
	SDL_Texture* mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};