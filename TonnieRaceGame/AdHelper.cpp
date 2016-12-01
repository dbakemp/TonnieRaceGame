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
	//bool alive = true;
	//while (alive) {
	//	Json::Value root;   // will contains the root value after parsing.
	//	Json::Reader reader;
	//	std::ifstream test("ads\\ad.json", std::ifstream::binary);
	//	bool parsingSuccessful = reader.parse(test, root, false);
	//	if (!parsingSuccessful)
	//	{
	//		// report to the user the failure and their locations in the document.
	//		std::cout << reader.getFormattedErrorMessages()
	//			<< "\n";
	//	}

	//	std::string encoding = root.get("encoding", "UTF-8").asString();
	//	std::cout << encoding << "\n";
	//	alive = false;

	//	Json::Value::Members r = root.getMemberNames();
	//	
	//	std::cout << root[0]["Title"].asString();
	//}

	std::ifstream ifs("ads\\ad.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj); // reader can also read strings
	//std::cout << "Title: " << obj["Title"].asString() << std::endl;
	//std::cout << "Year: " << obj["Date"].asUInt() << std::endl;
	const Json::Value& characters = obj["Ads"]; // array of characters
	for (int i = 0; i < characters.size(); i++) {
		//std::cout << "    Title: " << characters[i]["Title"].asString();
		//std::cout << " URL: " << characters[i]["URL"].asString();
		//std::cout << " ImageURL: " << characters[i]["ImageURL"].asString();
		//std::cout << " Description: " << characters[i]["Description"].asString();
		//std::cout << " IsActive: " << characters[i]["IsActive"].asString();
		//std::cout << std::endl;
		CDebugLogger::PrintDebug("AD Framework: Fetching with Title: " + characters[i]["Title"].asString() + " and URL: " + characters[i]["ImageURL"].asString());

		//fetchAd(characters[i]["Title"].asString(), characters[i]["ImageURL"].asString());
	}
}

void AdHelper::fetchJSON()
{
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

	//char *url = "http://www.timvanbeers.nl/ad.json";
	char *url = "http://timmeehh.xyz/index.php?page=api&sub=ads";
	//char outfilename[FILENAME_MAX] = "C:\Users\Tim\Desktop\Desktop\School\bbb.png";
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

void AdHelper::fetchAd(std::string adTitle, std::string adURL)
{
	CURL *curl;
	FILE *fp;
	CURLcode res;

	FILE *file;
	int file_exists;
	std::string test = "ads\\" + adURL;
	const char * filename = test.c_str();


	/*first check if the file exists...*/
	file = fopen(filename, "r");
	if (file == NULL) file_exists = 0;
	else { file_exists = 1; fclose(file); }

	/*...then open it in the appropriate way*/
	if (file_exists == 1)
	{
		//printf("file exists!\n");
		file = fopen(filename, "r+b");
	}
	else
	{
		//printf("file does not exist!\n");
		file = fopen(filename, "w+b");
	}

	if (file != NULL)
	{
		//printf("file opened succesfully!\n");
		fclose(file);
	}

	std::string urlString = "http://www.timvanbeers.nl/" + adURL;
	char *url = (char*)urlString.c_str();
	//char outfilename[FILENAME_MAX] = "C:\Users\Tim\Desktop\Desktop\School\bbb.png";
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
		CDebugLogger::PrintDebug("AD Framework: Ad image sucesfully written with filename: " + adURL);
	}
}

AdHelper::~AdHelper()
{
}
