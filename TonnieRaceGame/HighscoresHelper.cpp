#define _CRT_SECURE_NO_DEPRECATE
#include "HighscoresHelper.h"
#include "CDebugLogger.h"

#include <fstream>
#include <curl/curl.h>


HighscoresHelper::HighscoresHelper()
{
}

size_t writeData(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void HighscoresHelper::getHighscore(int level)
{
	CDebugLogger::PrintDebug("Getting Highscore!");
	CURL *curl;
	FILE *fp;
	CURLcode res;

	FILE *file;
	int file_exists;

	std::string t = "highscores\\";
	t.append(std::to_string(level));
	t.append(".json");

	const char * filename = t.c_str();

	/*first check if the file exists...*/
	file = fopen(filename, "r");
	if (file == NULL) file_exists = 0;
	else { file_exists = 1; fclose(file); }

	/*...then open it in the appropriate way*/
	if (file_exists == 1)
	{
		CDebugLogger::PrintDebug("Highscore file exists");
		file = fopen(filename, "r+b");
	}
	else
	{
		CDebugLogger::PrintDebug("Highscore file does not exist");
		file = fopen(filename, "w+b");
	}

	if (file != NULL)
	{
		CDebugLogger::PrintDebug("Hihgscore file sucesfully opened");
		fclose(file);
	}

	std::string urlString = "http://localhost/marketing/index.php?page=api&sub=highscores&action=read&level=";
	urlString.append(std::to_string(level));

	char *url = (char*)urlString.c_str();
	//char outfilename[FILENAME_MAX] = "C:\Users\Tim\Desktop\Desktop\School\bbb.png";
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(filename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		fclose(fp);
		CDebugLogger::PrintDebug("Highscore file succesfully written");
	}
}

HighscoresHelper::~HighscoresHelper()
{
}
