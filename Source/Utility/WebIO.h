// Small FTP and HTTP utility class using WinAPI by momo5502

#pragma once
#include <Windows.h>
#include <Wininet.h>
#include <string>
#include <vector>
#include <map>
#include <shlwapi.h>

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "shlwapi.lib")

class WebIO
{
public:

	typedef std::map<std::string, std::string> Params;

	WebIO();
	WebIO(std::string useragent);
	WebIO(std::string useragent, std::string url);

	~WebIO();

	void SetURL(std::string url);
	void SetCredentials(std::string username, std::string password);

	std::string Post(std::string url, WebIO::Params params);
	std::string Post(std::string url, std::string body);
	std::string Post(WebIO::Params params);
	std::string Post(std::string body);

	std::string Get(std::string url);
	std::string Get();

	// FTP
	bool Connect();
	void Disconnect(); // Not necessary

	bool SetDirectory(std::string directory);
	bool SetRelativeDirectory(std::string directory);
	bool GetDirectory(std::string &directory);
	bool CreateDirectory(std::string directory);
	bool DeleteDirectory(std::string directory);
	bool RenameDirectory(std::string directory, std::string newDir);

	bool ListDirectories(std::string directory, std::vector<std::string> &list);
	bool ListFiles(std::string directory, std::vector<std::string> &list);

	bool DeleteFile(std::string file);
	bool RenameFile(std::string file, std::string newFile);
	bool UploadFile(std::string file, std::string localfile);
	bool DownloadFile(std::string file, std::string localfile);

	bool UploadFileData(std::string file, std::string data);
	bool DownloadFileData(std::string file, std::string &data);

private:

	enum Command
	{
		COMMAND_POST,
		COMMAND_GET,
	};

	struct WebURL
	{
		std::string protocol;
		std::string server;
		std::string document;
		std::string raw;
	};

	bool m_isFTP;
	std::string m_username;
	std::string m_password;

	WebURL m_sUrl;

	HINTERNET m_hSession;
	HINTERNET m_hConnect;
	HINTERNET m_hFile;

	std::string BuildPostBody(WebIO::Params params);

	bool IsSecuredConnection();

	std::string Execute(const char* command, std::string body);

	bool ListElements(std::string directory, std::vector<std::string> &list, bool files);

	void OpenSession(std::string useragent);
	void CloseSession();

	bool OpenConnection();
	void CloseConnection();

	void FormatPath(std::string &path, bool win); /* if (win == true):  / -> \\ */
};