#include <iostream>
#include <sstream>
#include <string>

#pragma region PRINT
template <typename T>
static void PrintStuff(T valueZero)
{
	std::cout << valueZero << "\n";
}
#pragma endregion

enum StatusEnum
{
	NEVER_USED, OCCUPIED, TOMBSTONE
};

class HashTable
{
public:
	struct Entry
	{
		std::string Data;
		unsigned int Status = NEVER_USED;

	};

	static const int Size = 26;
public:
	HashTable() = default;

	void Add(const std::string& entryString)
	{
		bool exists = Find(entryString);

		if (exists) return;

		int insertIndex = GetInsertIndex(entryString);
		Entries[insertIndex].Data = entryString;
		Entries[insertIndex].Status = OCCUPIED;
	}
	void Delete(const std::string& entryString)
	{
		int index;
		bool exists = Find(entryString, &index);

		if (!exists) return;
	
		Entries[index].Status = TOMBSTONE;
	}
private:
	int GetIndex(const std::string& entryString)
	{
		return entryString.back() - 'a';
	}

	bool Find(const std::string& entryString, int* outIndex = nullptr)
	{
		int index = GetIndex(entryString);

		while (true)
		{
			if (Entries[index].Data == entryString)
			{  
				if(outIndex) *outIndex = index;

				return true;
			}

			if (Entries[index].Status == NEVER_USED)
				return false;

			index = (index + 1) % Size;
		}

		return false;
	}


	bool GetInsertIndex(const std::string& entryString)
	{
		int index = GetIndex(entryString);

		while (true)
		{
			if (Entries[index].Status == OCCUPIED
				|| Entries[index].Status == TOMBSTONE)
				return index;

			index = (index + 1) % Size;
		}

		return false;
	}

public:
	void Print()
	{
		for (int i = 0; i < Size; i++)
			if(Entries[i].Status == OCCUPIED)
			   PrintStuff(Entries[i].Data + "(" + std::to_string(Entries[i].Status) + ")");
	}
private:
	Entry Entries[Size];
};

int main()
{
	std::string input;
	getline(std::cin, input);

	HashTable hashTable;

	std::stringstream ss(input);
	while (ss.good())
	{
		std::string token;
		ss >> token;

		PrintStuff(token);

		std::string entryString = &token[1];
		if (token[0] == 'A')
			hashTable.Add(entryString);
		else if (token[0] == 'D')
			hashTable.Delete(entryString);
	}

	hashTable.Print();

}