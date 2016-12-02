#define _CRT_SECURE_NO_DEPRECATE
#include "AdHelper.h"
#include <iostream>
#include "CDebugLogger.h"
#include <curl/curl.h>
#include <fstream>
#include "json\json.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

AdHelper::AdHelper()
{
	fetchJSON();
	processJSON();
}

void AdHelper::processJSON()
{
	std::ifstream ifs("ads\\ad.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);
	const Json::Value& characters = obj["Ads"]; // array of characters
	for (int i = 0; i < characters.size(); i++) {
		//CDebugLogger::PrintDebug("AD Framework: Fetching with Title: " + characters[i]["Title"].asString() + " and URL: " + characters[i]["ImageURL"].asString() + " and Filename: " + characters[i]["FileName"].asString());


		size_t lastindex = characters[i]["FileName"].asString().find_last_of(".");
		std::string rawname = characters[i]["FileName"].asString().substr(0, lastindex);
		std::string ext = characters[i]["FileName"].asString().substr(lastindex, characters[i]["FileName"].asString().size() - lastindex);
		std::string rightName = rawname + "-right" + ext;
		std::string upName = rawname + "-up" + ext;
		std::string downName = rawname + "-down" + ext;
		size_t lastUrlIndex = characters[i]["ImageURL"].asString().find_last_of("/");
		std::string baseURL = characters[i]["ImageURL"].asString().substr(0, lastUrlIndex);

		fetchAd(characters[i]["Title"].asString(), characters[i]["ImageURL"].asString(), characters[i]["FileName"].asString());
		////Andere richtingen:
		fetchAd(characters[i]["Title"].asString(), baseURL + "/" + rightName, rightName);
		fetchAd(characters[i]["Title"].asString(), baseURL + "/" + upName, upName);
		fetchAd(characters[i]["Title"].asString(), baseURL + "/" + downName, downName);
	}
}

void AdHelper::fetchJSON()
{
	/* Create ads directory if it does not exist */
	CreateDirectory("ads", NULL);

	CDebugLogger::PrintDebug("AD Framework: Start fetching JSON...");
	CURL *curl;
	FILE *fp;
	CURLcode res;

	FILE *file;
	int file_exists;
	const char * filename = "ads\\ad.json";

	/*first check if the file exists...*/
	file = fopen(filename, "r");
	if (file == NULL) file_exists = 0;
	else { file_exists = 1; fclose(file); }

	/*...then open it in the appropriate way*/
	if (file_exists == 1)
	{
		CDebugLogger::PrintDebug("AD Framework: JSON file exists");
		file = fopen(filename, "r+b");
	}
	else
	{
		CDebugLogger::PrintDebug("AD Framework: JSON file does not exist");
		file = fopen(filename, "w+b");
	}

	if (file != NULL)
	{
		CDebugLogger::PrintDebug("AD Framework: JSON file opened succesfully");
		fclose(file);
	}

	char *url = "http://timmeehh.xyz/index.php?page=api&sub=ads";
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(filename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		fclose(fp);
		CDebugLogger::PrintDebug("AD Framework: JSON file opened sucesfully written.");
	}

}

void AdHelper::fetchAd(std::string adTitle, std::string adURL, std::string filename)
{
	CURL *curl;
	FILE *fp;
	CURLcode res;

	FILE *file;
	int file_exists;
	std::string test = "ads\\" + filename;
	const char * filenm = test.c_str();

	/*first check if the file exists...*/
	file = fopen(filenm, "r");
	if (file == NULL) file_exists = 0;
	else { file_exists = 1; fclose(file); }

	/*...then open it in the appropriate way*/
	if (file_exists == 1)
	{
		//printf("file exists!\n");
		file = fopen(filenm, "r+b");
	}
	else
	{
		//printf("file does not exist!\n");
		file = fopen(filenm, "w+b");
	}

	if (file != NULL)
	{
		//printf("file opened succesfully!\n");
		fclose(file);
	}

	std::string urlString = adURL;
	char *url = (char*)urlString.c_str();
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(filenm, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		fclose(fp);
		CDebugLogger::PrintDebug("AD Framework: Ad image sucesfully written with filename: " + filename);
	}
}

AdHelper::~AdHelper()
{
}
