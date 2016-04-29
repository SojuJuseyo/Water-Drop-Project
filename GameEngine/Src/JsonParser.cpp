#include "../Includes/JsonParser.h"

JsonParser::JsonParser()
{

}

JsonParser::JsonParser(std::string _filePath)
{
	this->filePath = _filePath;
}

JsonParser::~JsonParser()
{

}

// Function parsing the Json file and setting the map variables
int JsonParser::parseFile()
{
	std::ifstream	fileStream(this->filePath);
	Json::Reader	jsonReader;
	Json::Value		jsonObject;
	Json::Value		tileListObject;

	// Parse the stream and fill the jsonObject with the values
	if (!jsonReader.parse(fileStream, jsonObject))
	{
		std::cout << "Can't find the map. Please check the path." << std::endl;
		return (-1);
	}
	// Check that the name of the map, its size and its tilelist are correctly set
	if (this->checkFieldNamesExistence(jsonObject) == false)
	{
		std::cout << "Map corrupted. All the required fields are not present. Please correct the map or recreate it." << std::endl;
		return (-1);
	}

	this->map.setMapName(jsonObject[MAPNAMEATTRIBUTE].asString());
	// Parse the size string (format : X/Y) and split it in two integers
	this->parseMapSize(jsonObject[MAPSIZEATTRIBUTE].asString());

	this->map.setMapAudioFile(jsonObject[MAPAUDIOATTRIBUTE].asString());

	tileListObject = jsonObject[MAPTILELISTATTRIBUTE];
	// Get a vector of sprites used
	std::vector<std::string> spritesUsed = tileListObject.getMemberNames();
	std::list<std::pair<std::string, std::list<Tile *>>> mapTileList;

	// C++11 foreach
	for (std::string sprite : spritesUsed)
	{
		std::list<Tile *> selectedSpriteTileList;
		Json::Value selectedSpriteTileListObject = tileListObject[sprite];
		Json::Value::iterator itr = selectedSpriteTileListObject.begin();

		// Iterate through the list of tiles using a given sprite
		for (Json::ValueIterator itr = selectedSpriteTileListObject.begin(); itr != selectedSpriteTileListObject.end(); itr++)
		{
			Tile *newTile = new Tile();
			Json::Value itrValue = (*itr);

			newTile->setPosX(itrValue[MAPCOORDX].asFloat());
			newTile->setPosY(itrValue[MAPCOORDY].asFloat());
			
			selectedSpriteTileList.push_back(newTile);
		}

		std::pair<std::string, std::list<Tile *>> spriteTileListPair;
		spriteTileListPair = std::make_pair(sprite, selectedSpriteTileList);
		mapTileList.push_back(spriteTileListPair);
	}

	this->map.setMapTileList(mapTileList);

	std::cout << "Map successfully loaded." << std::endl;
	
	return (0);
}

// Check if field names are all set (name, size, tilelist)
bool JsonParser::checkFieldNamesExistence(Json::Value jsonObject)
{
	std::vector<std::string> fieldNames = jsonObject.getMemberNames();
	std::vector<std::string> defineFieldNames = { MAPNAMEATTRIBUTE, MAPSIZEATTRIBUTE, MAPTILELISTATTRIBUTE, MAPAUDIOATTRIBUTE };

	std::sort(fieldNames.begin(), fieldNames.end());
	std::sort(defineFieldNames.begin(), defineFieldNames.end());
	if (fieldNames == defineFieldNames)
		return (true);
	return (false);
}

// Parse the size string (format : X/Y) and split it in two integers
void JsonParser::parseMapSize(std::string mapSize)
{
	// I have no idea what this is doing but as strtok is deprecating I have to use the black magic function strtok_s
	// using a black magic variable as last parameter
	char* next_token[1] = {};
	int mapSizeX = 0, mapSizeY = 0;
	
	char *word = strtok_s(&mapSize[0], "/", &next_token[0]);
	this->map.setMapWidth((float)atoi(word));

	word = strtok_s(NULL, "/", &next_token[0]);
	this->map.setMapHeight((float)atoi(word));
}

// Debug function asking for the path of the map
void JsonParser::getFilenameFromConsole()
{
	std::string filePath;

	std::cout << "Please enter the path of the map :" << std::endl;
	std::cin >> filePath;

	while (!std::ifstream(filePath))
	{
		std::cout << "Invalid path." << std::endl;
		std::cin >> filePath;
	}

	this->setFilePath(filePath);
}

////////////////////////////////
// Setters and getters
////////////////////////////////

void JsonParser::setFilePath(std::string _filePath)
{
	this->filePath = _filePath;
}

std::string JsonParser::getFilePath() const
{
	return (this->filePath);
}

void JsonParser::setMap(MapInfos _map)
{
	this->map = _map;
}

MapInfos JsonParser::getMap() const
{
	return (this->map);
}