#include "Framework.h"
#include "DataManager.h"


DataManager* DataManager::instance = nullptr;
DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

void DataManager::DataRead(string fileName)
{
	ifstream file(fileName);
	UINT type;
	file >> type;
	int num;
	file >> num;
	int idx = 0;
	while (idx < num) {
		string key;
		file >> key;
		Vector2 size;
		file >> size.x;
		file >> size.y;
		Vector2 frame;
		file >> frame.x;
		file >> frame.y;
		string _path;
		wstring path;
		file >> _path;
		path.assign(_path.begin(), _path.end());
		IMAGE_MANAGER->Add(key, path, size, frame, MAGENTA);
		idx++;
		
		if (file.eof()) {
			return;
		}
	}
	file >> type;
	file >> num;
	idx = 0;
	while (idx < num) {
		string key;
		file >> key;
		Vector2 size;
		file >> size.x;
		file >> size.y;
		Vector2 frame;
		file >> frame.x;
		file >> frame.y;
		string _path;
		wstring path;
		file >> _path;
		path.assign(_path.begin(), _path.end());
		IMAGE_MANAGER->Add(key, path, size, frame, MAGENTA);
		idx++;

		if (file.eof()) {
			return;
		}
	}

	file >> type;
	file >> num;
	idx = 0;
	while (idx < num) {
		string key;
		file >> key;
		Vector2 size;
		file >> size.x;
		file >> size.y;
		Vector2 frame;
		file >> frame.x;
		file >> frame.y;
		string _path;
		wstring path;
		file >> _path;
		path.assign(_path.begin(), _path.end());
		IMAGE_MANAGER->Add(key, path, size, frame, MAGENTA);
		idx++;

		if (file.eof()) {
			return;
		}
	}
}

vector<SaveInfo*> DataManager::MapRead(string fileName)
{
	vector<SaveInfo*> loadList;
	ifstream inSave("SaveFile/" + fileName);
	if (!inSave) {
		return loadList;
	}
	int num = 0;
	inSave >> num;
	int idx = 0;
	while (idx<num) {
		SaveInfo* temp = new SaveInfo;
		inSave >> temp->type;
		inSave >> temp->code;
		inSave >> temp->pos.x;
		inSave >> temp->pos.y;
		loadList.push_back(temp);
		idx++;
	}
	inSave.close();
	return loadList;
}

void DataManager::MapWrite(string fileName, vector<SaveInfo*> saveList)
{
	ofstream outSave("SaveFile/" + fileName);
	outSave << saveList.size() << '\n';
	
	for (SaveInfo* idx : saveList) {
		outSave << idx->type<<'\t';
		outSave << ((idx->code))<<'\t';
		outSave << (idx->pos.x)<<'\t';
		outSave << (idx->pos.y)<<'\n';
		delete idx;
	}

	outSave.close();

}





