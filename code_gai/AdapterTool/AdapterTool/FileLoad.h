#pragma once
class CFileLoad
{
public:
	CFileLoad();
	~CFileLoad();

public:
	bool Initialize();
	bool LoadFile();

	int GetBXCID();
private:
	bool TransferFile();

};

