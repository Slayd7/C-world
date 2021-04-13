#pragma once
#include <vector>
#include <map>
#include <string>
#include "LTexture.h"
#include "Tile.h"
#include "external/pugixml-1.10/src/pugixml.hpp" // XML parser
#include "Defs.h"



class AssetManager
{
public:
	int getTextureId(std::string name);
	int getFontId(std::string name);

	LTexture* getTexture(int id);
	LTexture* newTextTexture(std::string text, std::string font, int fontsize, SDL_Color textColor);

	TTF_Font* getFont(int id, int size);

	TileRef* getTileRefByName(std::string name) { return TileLib[TileIdMap.at(name)]; };
	TileRef* getTilebyId(int id) { return TileLib[id]; };

	LTexture* GetNumberFromPool(int num, int size);
	
	bool init();
	AssetManager() {};
	~AssetManager() {};


private:
	bool importResources();
	bool importTextures();
	bool importAllAudio();

	bool importTexture(std::string name, std::string path);
	bool importAudio(std::string name, std::string path);

	bool generateTiles();
	bool generateTile(std::string name, LTexture* tx, Vector2D p, float cost);

	std::vector<LTexture> Textures;
	LTexture* numberpool[FONTSIZES][10];
	std::vector<std::vector<TTF_Font*>> Fonts;
	std::map<std::string, int> textureIds;
	std::map<std::string, int> fontIds;
	std::vector<TileRef*> TileLib;
	std::map<std::string, int> TileIdMap;
	int numTiles = 0;
};
