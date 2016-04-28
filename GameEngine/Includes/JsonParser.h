#pragma once

#include "../Includes/MapInfos.h"
#include "JsonCpp/json.h"

#include <fstream>
#include <algorithm>

#define MAPNAMEATTRIBUTE "name"
#define MAPSIZEATTRIBUTE "size"
#define MAPTILELISTATTRIBUTE "tileList"
#define MAPAUDIOATTRIBUTE "audio"
#define MAPCOORDX "coordx"
#define MAPCOORDY "coordy"

class JsonParser 
{

private:

	// The path of the Json file to parse
	std::string filePath;

	// Informations of the map
	MapInfos map;

public:

	JsonParser();
	JsonParser(std::string);
	~JsonParser();

	// Function parsing the Json file and setting the map variables
	int parseFile();
	// Check if field names are all set (name, size, tilelist)
	bool JsonParser::checkFieldNamesExistence(Json::Value);
	// Parse the map size string
	void JsonParser::parseMapSize(std::string mapSize);

	// Debug function
	void JsonParser::getFilenameFromConsole();

	// Setters and Getters
	void setFilePath(std::string);
	std::string getFilePath() const;

	void setMap(MapInfos);
	MapInfos getMap() const;

};