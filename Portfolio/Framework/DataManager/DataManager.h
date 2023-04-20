#pragma once
class DataManager
{
private:
	DataManager();
	~DataManager();
public:
	static DataManager* Get() {
		if (instance == nullptr) {
			instance = new DataManager();
		}

		return instance;
	}

	void Delete() {
		delete instance;
	}

	void DataRead(string fileName);
	vector<SaveInfo*> MapRead(string fileName);
	void MapWrite(string fileName, vector<SaveInfo*> saveList);
private:
	static DataManager* instance;
};

