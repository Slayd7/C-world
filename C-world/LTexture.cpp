#include "pch.h"
#include "LTexture.h"
#include "GameEngine.h"

bool LTexture::loadFromFile(std::string path)
{
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		printf("Unable to load image %s! SDL_image error: %s\n", path.c_str(), IMG_GetError());
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFf, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(GameEngine::Renderer(), loadedSurface);
		if (newTexture == NULL)
			printf("Unable to create texture from %s! SDL error: %s\n", path.c_str(), SDL_GetError());
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(GameEngine::Renderer(), textSurface);
		if (mTexture == NULL)
			printf("Unable to create texture from rendered text! SDL error: %s\n", SDL_GetError());
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//free();
}

void LTexture::Cleanup()
{
	free();
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, double scale, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (mTexture == NULL) return;
	SDL_Rect renderQuad = { x  , y , mWidth * scale, mHeight * scale};

	if (clip != NULL)
	{
		renderQuad.w = (clip->w * scale);
		renderQuad.h = (clip->h * scale);
	}
 	int ret = SDL_RenderCopyEx(GameEngine::Renderer(), mTexture, clip, &renderQuad, angle, center, flip);
	
	if (ret == -1)
		printf("render failed: %s\n", SDL_GetError());
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}