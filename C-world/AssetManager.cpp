#include "pch.h"
#include "AssetManager.h"

LTexture tmpTex;

int AssetManager::getTextureId(std::string name) {
	int id = -1;
	if (textureIds.find(name) != textureIds.end())
	{
		id = textureIds.find(name)->second;
	}
	return id;	
}

int AssetManager::getFontId(std::string name) {
	int id = -1;
	if (fontIds.find(name) != fontIds.end()) {
		id = fontIds.find(name)->second;
	}
	return id;
}

LTexture* AssetManager::getTexture(int id) {
	return &Textures.at(id);
}

LTexture* AssetManager::newTextTexture(std::string text, std::string font, int fontsize, SDL_Color textColor)
{
	int id = getFontId(font);
	if (id == -1)
	{
		return NULL;
	}
	LTexture* tex = new LTexture();
	if (fontsize >= FONTSIZES) {
		printf("Font size invalid! Sizes: 0-%i\n", FONTSIZES);
		return NULL;
	}
	tex->loadFromRenderedText(text, textColor, getFont(id, fontsize));
	return tex != NULL ? tex : NULL;
}

TTF_Font* AssetManager::getFont(int id, int size = 0)
{
	return Fonts.at(id).at(size);
}

bool AssetManager::init()
{
	bool success;
	success = importResources();
	if (success) success = generateTiles();
	return success;
}

bool AssetManager::importResources()
{
	bool success;
	success = importTextures() & importAllAudio();
	return success;
}

bool AssetManager::importTextures()
{
	bool success = true;

	pugi::xml_document doc;

	std::string fname = RESOURCES_FOLDER + std::string("import.xml");
	char* c = const_cast<char*>(fname.c_str());
	pugi::xml_parse_result result = doc.load_file(c);

	if (result) {
		for (pugi::xml_node_iterator it = doc.begin(); it != doc.end(); ++it)
		{
			std::string n = it->name();
			if (n.compare("sprites") == 0) {
				// SPRITES
				int idx = 0;

				for (pugi::xml_node child : it->children()) {
					std::string m = child.name();
					if (m.compare("tiles") == 0) {
						// TILES
						for (pugi::xml_node t : child.children()) {

							std::string name = "";
							std::string loc = "sprites";

							for (pugi::xml_attribute ait : t.attributes()) {
								std::string l = ait.name();
								if (l.compare("name") == 0) {
									name = ait.value();
								}
								else if (l.compare("location") == 0) {
									loc.append(ait.value());
								}
							}

							tmpTex = *new LTexture();
							tmpTex.loadFromFile(RESOURCES_FOLDER + loc);
							Textures.push_back(tmpTex);
							//Textures[idx].loadFromFile(RESOURCES_FOLDER + loc);
							textureIds[name] = idx;
							idx++;
						}
					}
					else if (m.compare("actors") == 0) {
						// ACTORS
						for (pugi::xml_node t : child.children()) {

							std::string name = "";
							std::string loc = "sprites";

							for (pugi::xml_attribute ait : t.attributes()) {
								std::string l = ait.name();
								if (l.compare("name") == 0) {
									name = ait.value();
								}
								else if (l.compare("location") == 0) {
									loc.append(ait.value());
								}
							}

							Textures.push_back(*new LTexture());
							Textures[idx].loadFromFile(RESOURCES_FOLDER + loc);
							textureIds[name] = idx;
							idx++;
					}
					}
					else if (m.compare("buildings") == 0) {
						// BUILDINGS
						// NEEDS FIXING, currently not loading
						for (pugi::xml_node t : child.children()) {

							std::string name = "";
							std::string loc = "sprites";

							for (pugi::xml_attribute ait : t.attributes()) {
								std::string l = ait.name();
								if (l.compare("name") == 0) {
									name = ait.value();
								}
								else if (l.compare("location") == 0) {
									loc.append(ait.value());
								}
							}

						//	LTexture* tex = new LTexture();
							//tex->loadFromFile(RESOURCES_FOLDER + loc);
							//Textures.push_back(*tex);
							//textureIds[name] = idx;
							idx++;
						}
					}
				}
			}

			else if (n.compare("fonts") == 0) {
				int idx = 0;
				for (pugi::xml_node t : it->children()) {

					std::string name = "";
					std::string loc = RESOURCES_FOLDER;

					for (pugi::xml_attribute ait : t.attributes()) {
						std::string l = ait.name();
						if (l.compare("name") == 0) {
							name = ait.value();
						}
						else if (l.compare("location") == 0) {
							loc.append(ait.value());
						}
					}

					char* c = const_cast<char*>(loc.c_str());
					std::vector<TTF_Font*> fonts;
					for (int i = 0; i < FONTSIZES; i++) {
						TTF_Font* font = TTF_OpenFont(c, FONTSIZE[i]);
						if (font == NULL)
						{
							success = false;
							break;
						}
						else {
							fonts.push_back(font);
						}
					}

					Fonts.push_back(fonts);
					fontIds[name] = idx;

					idx++;
				}
			}


		}
	}
	else {
		printf("Failed to load!\n");
		success = false;
	}



	return success;

}
bool AssetManager::importAllAudio()
{
	return true;
}

bool AssetManager::importTexture(std::string name, std::string path)
{
	bool success = true;
	LTexture* tex = new LTexture();
	if (!tex->loadFromFile(path))
	{
		printf("importTexture failed");
		success = false;
	}
	else
		Textures.push_back( *tex  );
	return success;
}

bool AssetManager::importAudio(std::string name, std::string path)
{
	printf("importAudio not implemented!");
	return false;
}

bool AssetManager::generateTiles()
{
	bool success = true;
	LTexture* tx = getTexture(getTextureId("forest"));
	
	generateTile("sand_grass_corner_tl", tx, Vector2D(0, 0), 1.5);
	generateTile("sand_grass_top", tx, Vector2D(1, 0), 1.5);
	generateTile("sand_grass_corner_tr", tx, Vector2D(2, 0), 1.5);
	generateTile("sand_grass_left", tx, Vector2D(0, 1), 1.5);
	generateTile("grass", tx, Vector2D(1, 1), 1.0);
	generateTile("sand_grass_right", tx, Vector2D(2, 1), 1.5);
	generateTile("sand_grass_corner_bl", tx, Vector2D(0, 2), 1.5);
	generateTile("sand_grass_bottom", tx, Vector2D(1, 2), 1.5);
	generateTile("sand_grass_corner_br", tx, Vector2D(2, 2), 1.5);

	generateTile("water", tx, Vector2D(4, 4), INFINITY);
	generateTile("sand", tx, Vector2D(4, 1), 1.5);
	
	return success;
}

bool AssetManager::generateTile(std::string name, LTexture* tx, Vector2D p, float cost) {

	TileRef* t = new TileRef(numTiles, tx, p, cost);
	TileLib.push_back(t);

	TileIdMap[name] = numTiles;

	numTiles++;
	return true;
}

LTexture* AssetManager::GetNumberFromPool(int num, int size)
{
	if (numberpool[size][num] == nullptr)
	{
		SDL_Color drawColor = SDL_Color{ UI_COLOR_UINT_TO_RGBA(UI_TEXTPRIMARYCOLOR) };
		TTF_Font* font = getFont(getFontId("basic"), size);

		numberpool[size][num] = new LTexture();
		numberpool[size][num]->loadFromRenderedText(std::to_string(num), drawColor, font);
	}
	return numberpool[size][num];
}