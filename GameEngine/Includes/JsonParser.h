#pragma once

#include "MapInfos.h"
#include "../JsonCpp/json.h"

#include <fstream>
#include <algorithm>

// Map related field names & attributes
#define MAP_NAME_ATTRIBUTE				"name"
#define MAP_SIZE_ATTRIBUTE				"size"
#define MAP_TILE_LIST_ATTRIBUTE			"tileList"
#define MAP_HEATZONE_LIST_ATTRIBUTE		"heatZonesList"
#define MAP_AUDIO_ATTRIBUTE				"audio"
#define MAP_COORD_X						"coordx"
#define MAP_COORD_Y						"coordy"

// Settings related field names & attributes
#define SETTINGS_RESOLUTION		"resolution"
#define SETTINGS_KEYS_MAPPING	"keys_mapping"
#define SETTINGS_VOLUME			"volume"
#define SETTINGS_FULLSCREEN		"fullscreen"
#define SETTINGS_FPS			"fps"

enum FileType
{
	MAP,
	SETTINGS,
	LEVELS
};

class JsonParser 
{
private:
	std::string					_filePath;
	Json::Value					_fileContent;
	std::vector<std::string>	_fieldNames;
	FileType					_fileType;

public:

	JsonParser();
	JsonParser(std::string);
	~JsonParser();

	// Function parsing the Json file
	void parseFile(FileType fileType);

	std::map<std::string, std::string>	getFileContent();
	void	defineFileFieldNames();

	// Check if field names are all set (name, size, tilelist)
	bool checkFieldNamesExistence();

	// Debug function
	void getFilenameFromConsole();

	// Setters and Getters
	void setFilePath(std::string);
	std::string getFilePath() const;

	// Map related functions variables
	MapInfos	parseMap();
	void		parseMapSize(std::string mapSize, MapInfos	&map);

	// Settings related functions


	// Levels order related functions
};