#pragma once

#include "MapInfos.h"
#include "Settings.h"
#include "../JsonCpp/json.h"

#include <fstream>
#include <algorithm>

enum FileType
{
	MAP,
	SETTINGS,
	LEVELS
};

namespace Moo
{
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

		void	saveSettings(Settings &, std::string) const;

		// Function parsing the Json file
		void parseFile(FileType fileType);

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
		Settings	getSettingsFileContent();

		// Levels order related functions
	};
}