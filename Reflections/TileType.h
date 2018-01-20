#pragma once
#include <map>
#include "Textured.h"

namespace reflections {

	//Enum containing the types of tiles. These also effectively function as ID.
	enum TypeName {
		GRASS,			//0		Block of grass
		LAVA,			//1		Block of lava
		WATER,			//2		Block of water
		STONE,			//3		Block of stone
		STONE_LEDGE,	//4		Slab of stone
		FAN,			//5		Fan blowing air upwards
		FLAG,			//6		Flag to end the level
		DIRT,			//7		Dirt block
		GRASS_PATH,		//8		Grass slab
		ROCK,			//9		Big rock blocking the way
		HILL,			//10	Big square grass/dirt hill blocking the way
		LAVA_VENT,		//11	Tiny vulcano that blows players upward.
		LANTERN,		//12	Tall lantern pole (No collision).
		THISTLE,		//13	Tall plant blocking the way. Damages entities on contact.
	};

	//TileType is a class that contains info about a specific type of tile. Think texture, size and other type specific info.
	class TileType : public Textured {
	private:
		TypeName type;
		int id;
		int width;
		int height;
		bool solid;
		double hitBoxW;
		double hitBoxH;
		static std::map<int, TileType*> registry;

		//Private constructor so only init can create tileTypes.
		TileType(int id, int textureID, bool solid, int width, int height, double hitBoxW, double hitBoxH);
		TileType(int id, int textureID, bool solid, int width, int height);
	public:

		//Destructor
		~TileType();

		//Getters
		int getID();
		int getWidth();
		int getHeight();
		bool isSolid();
		TypeName getTypeName();
		double hitBoxWidth();
		double hitBoxHeight();

		//Static
		static bool init();
		static void destroy();
		static TileType * typeFromID(int id);
		static void updateTextureData();
	};
}