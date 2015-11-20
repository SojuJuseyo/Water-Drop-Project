#include "JsonParser.h"

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
		return (-1);
	// Check that the name of the map, its size and its tilelist are correctly set
	if (this->checkFieldNamesExistence(jsonObject) == false)
		return (-1);

	this->map.setMapName(jsonObject[MAPNAMEATTRIBUTE].asString());
	// Parse the size string (format : X/Y) and split it in two integers
	this->parseMapSize(jsonObject[MAPSIZEATTRIBUTE].asString());

	tileListObject = jsonObject[MAPTILELISTATTRIBUTE];
	// Get a vector of color used
	std::vector<std::string> colorsUsed = tileListObject.getMemberNames();
	std::list<std::pair<std::string, std::list<Tile *>>> mapTileList;

	// C++11 foreach
	for (std::string color : colorsUsed)
	{
		std::list<Tile *> selectedColorTileList;
		Json::Value selectedColorTileListObject = tileListObject[color];
		Json::Value::iterator itr = selectedColorTileListObject.begin();

		// Iterate through the list of tiles in a given color
		for (Json::ValueIterator itr = selectedColorTileListObject.begin(); itr != selectedColorTileListObject.end(); itr++)
		{
			Tile *newTile = new Tile();
			Json::Value itrValue = (*itr);

			newTile->setPosX(itrValue[MAPCOORDX].asFloat());
			newTile->setPosY(itrValue[MAPCOORDY].asFloat());
			
			selectedColorTileList.push_back(newTile);
		}

		std::pair<std::string, std::list<Tile *>> colorTileListPair;
		colorTileListPair = std::make_pair(color, selectedColorTileList);
		mapTileList.push_back(colorTileListPair);
	}

	this->map.setMapTileList(mapTileList);

	return (0);
}

// Check if field names are all set (name, size, tilelist)
bool JsonParser::checkFieldNamesExistence(Json::Value jsonObject)
{
	std::vector<std::string> fieldNames = jsonObject.getMemberNames();
	std::vector<std::string> defineFieldNames = { MAPNAMEATTRIBUTE, MAPSIZEATTRIBUTE, MAPTILELISTATTRIBUTE };

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