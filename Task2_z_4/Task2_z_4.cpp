/**
*@file Task2_z_7
*@brief solution (C++ code) of Task2.7 GL 
* (4.З клавіатури ввести набір структур у формі  <Ключ>, <Дані>. Відсортувати введені записи за зростанням ключів.
* У відсортований масив ввести 2 нових записи так, щоб зберегти загальну впорядкованість масиву. Роздрукувати результуючий масив.)
*
*Copyright 2014 by Roman Bojko
*
*/

#include <iostream>
#include <iomanip>
#define N 3
#define C 2
#define MAX_VALUE_SIZE 128

using namespace std;

/* Structure represents key-value pair (max value size is MAX_VALUE_SIZE in bytes) */
struct KeyValuePair
{
	unsigned long key;
	char value[MAX_VALUE_SIZE];
};

/* Checks if key is already in array */
bool hasKey(KeyValuePair *data, int count, unsigned long key);

void inputData(KeyValuePair *data, int count);
void printData(KeyValuePair *data, int count);

/* Sort data array by key field */
void sortByKey(KeyValuePair *data, int count);

/* Insert new data in array (array has to be sorted and have free space for new entry) */
void insertData(KeyValuePair *data, int count, KeyValuePair *newEntry);

int main()
{
	KeyValuePair data[N + C] = {0};

	inputData(data, N);
	sortByKey(data, N);

	KeyValuePair temp;
	unsigned long key = 0;
	int n = 0;
	while(n < C)
	{
		cout << "Input new key-value pair: " <<endl;

		cout << "Key: ";
		cin >> key;

		if(hasKey(data, N + n, key))
		{
			cout << "Key \"" << key << "\" has been already taken, enter again" << endl;
			continue;
		}
		temp.key = key;

		cout << "Value: ";
		cin >> temp.value;

		insertData(data, N + n, &temp);

		n++;
	}

	printData(data, N + C);
	system("pause");
	return 0;
}

bool hasKey(KeyValuePair *data, int count, unsigned long key)
{
	for(int i = 0; i < count; i++)
	{
		if(data[i].key == key)
			return true;
	}

	return false;
}

void inputData(KeyValuePair *data, int count)
{	
	if(count <= 0)
		return;

	int n = 0;
	unsigned long key = 0;

	cout << "Enter key and bound value:" << endl;
	while(n < count)
	{
		cout << "Key: ";
		cin >> key;
		if(hasKey(data, count, key))
		{
			cout << "Key \"" << key << "\" has been already taken, enter again" << endl;
			continue;
		}
		data[n].key = key;

		cout << "Value: ";
		cin >> data[n].value;

		n++;
	}
}

void printData(KeyValuePair *data, int count)
{
	for(int i = 0; i < count; i++)
	{
		cout << endl << "Key: " << data[i].key << endl;
		cout << "Value: " << data[i].value << endl;
	}
}

void sortByKey(KeyValuePair *data, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(data[i].key < data[j].key)
			{
				KeyValuePair temp = data[j];
				data[j] = data[i];
				data[i] = temp;
			}
		}
	}
}

void insertData(KeyValuePair *data, int count, KeyValuePair *newEntry)
{
	for(int i = 0; i < count; i++)
	{
		if(data[i].key > newEntry->key)
		{
			// shift remaining data right
			for(int j = count; j > i; j--)
				data[j] = data[j - 1];

			// insert new entry
			data[i] = *newEntry;
			return;
		}
	}

	data[count] = *newEntry;
}