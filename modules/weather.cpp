#include "weather.hpp"

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <fstream>
#include <json/json.h>
#include <fmt/core.h>

using std::string;
using std::ostringstream;

char URL[] = "https://wttr.in/levadia+greece?format=j1";
char DOWNLOAD_LOCATION[] = "/tmp/weather.json";


Weather::Weather(int update_interval, int signal, bool has_event_handler, bool needs_internet)
    : Item(update_interval, signal, has_event_handler, needs_internet) {}

int Weather::SetValue()
{
    DownloadFile(URL, DOWNLOAD_LOCATION);

    std::ifstream test_file("/tmp/weather.json", std::ifstream::binary);

    Json::Value weather;
    test_file >> weather;

    int rain_chance = GetMaxChanceOfRain(weather);

    string temp = GetTemp(weather);

    string weather_condition = GetWeatherCondition(weather);

    string old_value = value_;

    if (rain_chance == 0)
    {
        value_ = fmt::format("{} 🌡️{}°C", weather_condition, temp);
    }

    else
    {
        value_ = fmt::format("{} 🌡️{}°C ☔{}%",
                weather_condition, temp, rain_chance);
    }

    return value_ != old_value;
}

// Download Json file.
static size_t WriteData(void* ptr, size_t size, size_t nmemb, void* stream)
{
    size_t written = fwrite(ptr, size, nmemb, static_cast<FILE*>(stream));
    return written;
}

bool Weather::DownloadFile(char* url, char* location)
{
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if(res) return 1;

    bool retval = false;

    // Download the file using curl library into DownloadCURL folder
    if(CURL* curl = curl_easy_init())
    {
        if(FILE* fp = fopen(location, "wb")) 
        {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
            curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L); // corp. proxies etc.

            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);
            if(!res) retval = true;

            fclose(fp);
        }

        curl_easy_cleanup(curl);
    } 

    curl_global_cleanup();

    return retval;
}


// Parse Json file.
int Weather::GetTime(string date_time)
{
    char hour[3];
    char am_pm[3];

    for (int i = 0; i < (int)date_time.size(); i++)
    {
        if (date_time[i] == ' ')
        {
            hour[0] = date_time[i + 1];
            hour[1] = date_time[i + 2];
            hour[2] = '\0';

            am_pm[0] = date_time[i + 7];
            am_pm[1] = date_time[i + 8];
            am_pm[2] = '\0';

            break;
        }
    }

    int hour_int = atoi(hour);



    if (!strcmp(am_pm, "PM"))
    {
		if (hour_int < 12)
		{
        	hour_int += 12;
		}

    }

    else if (!strcmp(am_pm, "AM"))
	{
		if (hour_int == 12)
		{
			hour_int = 0;
		}
	}

    return hour_int;
}

void Weather::RemoveFirstAndLastCharacter(string &str)
{
    str.pop_back();
    str.erase(str.begin());
}

int Weather::GetMaxChanceOfRain(Json::Value &weather)
{
    ostringstream date_time;

    date_time << weather["current_condition"][0]["localObsDateTime"];

    int time = GetTime(date_time.str());

    // We only want to get the chance of rain from the upcoming hours.
    int min_time = time / 3; 

    int max_chance = -1;

    for (int i = min_time; i < 8; i++)
    {
        ostringstream chance_of_rain_stream;
        chance_of_rain_stream << weather["weather"][0]["hourly"][i]["chanceofrain"];

        string chance_of_rain_str = chance_of_rain_stream.str();

        // Remove first and last character.
        // They are the characters "".
        RemoveFirstAndLastCharacter(chance_of_rain_str);

        int chance_of_rain_int = stoi(chance_of_rain_str);

        if (chance_of_rain_int > max_chance)
        {
            max_chance = chance_of_rain_int;
        }
    }

    return max_chance;

}

string Weather::GetTemp(Json::Value &weather)
{
    ostringstream temp_stream;
    temp_stream << weather["current_condition"][0]["FeelsLikeC"];

    string temp_str = temp_stream.str();

    RemoveFirstAndLastCharacter(temp_str);

    return temp_str;
}

string Weather::GetWeatherCondition(Json::Value &weather)
{
    ostringstream weather_condition_stream;

    weather_condition_stream << weather["current_condition"][0]["weatherDesc"][0]["value"];

    string weather_condition_str = weather_condition_stream.str();

    // Return a different emoji for every possible weather condition.
    // Use extra " at the beggining and the end.

    if (weather_condition_str == "\"Cloudy\""   ||
        weather_condition_str == "\"Overcast\""  )
    {
        return string("☁️");
    }

    if (weather_condition_str == "\"Mist\""			|| 
        weather_condition_str == "\"Fog\""  		||
        weather_condition_str == "\"Freezing fog\""  )
    {
        return string("🌫");
    }

    else if (weather_condition_str == "\"Sunny\"")
    {
        return string("☀️");
    }

    else if (weather_condition_str == "\"Partly cloudy\"")
    {
        return string("⛅️");
    }

    else if (weather_condition_str == "\"Patchy light rain with thunder\""		||
             weather_condition_str == "\"Thundery outbreaks possible\"" 		||
             weather_condition_str == "\"Blizzard\"" 							||
             weather_condition_str == "\"Patchy light rain with thunder\"" 		||
             weather_condition_str == "\"Moderate or heavy rain with thunder\"" ||
             weather_condition_str == "\"Patchy light snow with thunder\""       ) 
    {
        return string("⛈️");
    }

    else if (weather_condition_str == "\"Clear\"")
    {
        return string("🌕");
    }

    else if (weather_condition_str == "\"Patchy rain possible\"" 				||
             weather_condition_str == "\"Light rain shower\"" 					|| 
             weather_condition_str == "\"Patchy sleet possible\"" 				||
             weather_condition_str == "\"Patchy freezing drizzle possible\""	||
             weather_condition_str == "\"Patchy light drizzle\""				||
             weather_condition_str == "\"Light drizzle\""						||
             weather_condition_str == "\"Freezing drizzle\""					||
             weather_condition_str == "\"Heavy freezing drizzle\""				||
             weather_condition_str == "\"Patchy light rain\""					||
             weather_condition_str == "\"Light rain\""							||
             weather_condition_str == "\"Moderate rain at times\""				||
             weather_condition_str == "\"Moderate rain\""						||
             weather_condition_str == "\"Heavy rain at times\""					||
             weather_condition_str == "\"Heavy rain\""							||
             weather_condition_str == "\"Light freezing rain\""					||
             weather_condition_str == "\"Moderate or heavy freezing rain\""		||
             weather_condition_str == "\"Light sleet\""							||
             weather_condition_str == "\"Moderate or heavy sleet\""				||
             weather_condition_str == "\"Light rain shower\""					||
             weather_condition_str == "\"Moderate or heavy rain shower\""		||
             weather_condition_str == "\"Torrential rain shower\""				||
             weather_condition_str == "\"Light sleet showers\""					||
             weather_condition_str == "\"Moderate or heavy sleet showers\""		 )
    {
        return string("🌧️");
    }

    else if (weather_condition_str == "\"Patchy snow possible\"" ||
             weather_condition_str == "\"Patchy light snow\""    ||
             weather_condition_str == "\"Patchy moderate snow\"" ||
             weather_condition_str == "\"Patchy heavy snow\""    ||
             weather_condition_str == "\"Light snow showers\""    )
    {
        return string("🌨️");
    }

    else if (weather_condition_str == "\"Blowing snow\"" 						||
             weather_condition_str == "\"Moderate snow\"" 						||
             weather_condition_str == "\"Heavy snow\""    						||
             weather_condition_str == "\"Ice pellets\""    						||
             weather_condition_str == "\"Moderate or heavy snow showers\""    	||
             weather_condition_str == "\"Moderate or heavy snow with thunder\""	 )
    {
        return string("❄️");
    }

    else 
    {
        return string("⛔");
    }
}
