#include "../item.hpp"

#include <iostream>
#include <json/value.h>

char URL[] = "https://wttr.in/athens+greece?format=j1";
char DOWNLOAD_LOCATION[] = "/tmp/weather.json";

class Weather : public Item
{
public:
    Weather(int update_interval, bool has_event_handler, bool needs_internet, 
			bool has_clicked);
    int SetValue();
    void Clicked(int button);

private:
	// Download Json file
	bool DownloadFile(char* url, char* location);

	// Parse Json file.
    int GetTime(std::string date_time);
    void RemoveFirstAndLastCharacter(std::string &str);
    int GetMaxChanceOfRain(Json::Value &weather);
    std::string GetTemp(Json::Value &weather);
    std::string GetWeatherCondition(Json::Value &weather);
};
