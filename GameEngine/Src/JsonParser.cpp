#include "JsonParser.h"

namespace Moo
{
	JsonParser::JsonParser()
	{

	}

	JsonParser::JsonParser(std::string filePath)
	{
		this->_filePath = filePath;
	}

	JsonParser::~JsonParser()
	{

	}

	// Function parsing the Json file and setting the map variables
	void	JsonParser::parseFile(FileType fileType)
	{
		std::ifstream	fileStream(this->_filePath);
		Json::Reader	jsonReader;

		this->_fileType = fileType;
		this->defineFileFieldNames();
		// Parse the stream and fill the jsonObject with the values
		if (!jsonReader.parse(fileStream, _fileContent))
			throw std::string("Can't find the file. Please check the path.");

		// Check that the field names of this type of file are present
		if (checkFieldNamesExistence() == false)
			throw std::string("File corrupted. All the required fields are not present. Please correct the file or recreate it.");
	}

	void	JsonParser::defineFileFieldNames()
	{
		if (this->_fileType == FileType::MAP)
			_fieldNames = { MAP_NAME_ATTRIBUTE, MAP_SIZE_ATTRIBUTE, MAP_TILE_LIST_ATTRIBUTE, MAP_AUDIO_ATTRIBUTE, MAP_HEATZONE_LIST_ATTRIBUTE };
		else if (this->_fileType == FileType::SETTINGS)
			_fieldNames = { SETTINGS_RESOLUTION, SETTINGS_KEYS_MAPPING, SETTINGS_VOLUME, SETTINGS_FULLSCREEN, SETTINGS_FPS };
	}

	// Function parsing the Json file and setting the map variables
	MapInfos JsonParser::parseMap()
	{
		Json::Value		tileListObject;
		MapInfos		map;

		map.setMapName(_fileContent[MAP_NAME_ATTRIBUTE].asString());
		// Parse the size string (format : X/Y) and split it in two integers
		parseMapSize(_fileContent[MAP_SIZE_ATTRIBUTE].asString(), map);

		map.setMapAudioFile(_fileContent[MAP_AUDIO_ATTRIBUTE].asString());

		tileListObject = _fileContent[MAP_TILE_LIST_ATTRIBUTE];
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

				newTile->setPosX(itrValue[MAP_COORD_X].asFloat());
				newTile->setPosY(itrValue[MAP_COORD_Y].asFloat());

				selectedSpriteTileList.push_back(newTile);
			}

			std::pair<std::string, std::list<Tile *>> spriteTileListPair;
			spriteTileListPair = std::make_pair(sprite, selectedSpriteTileList);
			mapTileList.push_back(spriteTileListPair);
		}

		map.setMapTileList(mapTileList);

		std::cout << "Map successfully loaded." << std::endl;

		return (map);
	}

	Settings	JsonParser::getSettingsFileContent()
	{
		std::map<std::string, std::string>		fileContent;
		std::map<Keyboard::Key, std::string>	keyMapping;


		for (std::string fieldName : _fieldNames)
			if (fieldName == SETTINGS_KEYS_MAPPING)
				;
			else
				fileContent[fieldName] = _fileContent[fieldName].asString();

		Settings settings(fileContent);
		settings.setKeysMapping(keyMapping);

		return (settings);
	}

	// Check if field names are all set (name, size, tilelist)
	bool	JsonParser::checkFieldNamesExistence()
	{
		std::vector<std::string> fieldNames = _fileContent.getMemberNames();
		std::sort(fieldNames.begin(), fieldNames.end());
		std::sort(_fieldNames.begin(), _fieldNames.end());
		if (fieldNames == _fieldNames)
			return (true);
		return (false);
	}

	// Parse the size string (format : X/Y) and split it in two integers
	void JsonParser::parseMapSize(std::string mapSize, MapInfos	&map)
	{
		// I have no idea what this is doing but as strtok is deprecating I have to use the black magic function strtok_s
		// using a black magic variable as last parameter
		char* next_token[1] = {};
		int mapSizeX = 0, mapSizeY = 0;

		char *word = strtok_s(&mapSize[0], "/", &next_token[0]);
		map.setMapWidth((float)atoi(word));

		word = strtok_s(NULL, "/", &next_token[0]);
		map.setMapHeight((float)atoi(word));
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

	void JsonParser::setFilePath(std::string filePath)
	{
		this->_filePath = filePath;
	}

	std::string JsonParser::getFilePath() const
	{
		return (this->_filePath);
	}

	void	JsonParser::saveSettings(Settings &settings, std::string fileName) const
	{
		std::ofstream		file_id;
		Json::StyledWriter	writer;
		Json::Value			value;

		value[SETTINGS_RESOLUTION] = settings.getResolutionString();
		value[SETTINGS_KEYS_MAPPING] = "tmp";
		value[SETTINGS_VOLUME] = settings.getVolumeString();
		value[SETTINGS_FULLSCREEN] = settings.getIsFullscreenString();
		value[SETTINGS_FPS] = settings.getFpsString();

		file_id.open(fileName);
		file_id << writer.write(value);
		file_id.close();
		std::cout << "Saved the content of the Settings class to file: " << fileName << std::endl;
	}
}