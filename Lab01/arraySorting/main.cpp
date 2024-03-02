#include <iostream>

using std::cout;
using std::cin;

void PrintArray(int* arr, unsigned size);
int* CreateRandomArray(unsigned size);
void CountingSort(int* arrayToSort, unsigned size);
void MergeSort(int* arr, int left, int right);
const int STORAGE_MAX_SIZE = 100;
void Merge(int* arr, int left, int right);

bool IsSorted(int* arr, unsigned size);

int main()
{
	// тест для сортування підрахунком
	
	/*for (unsigned attempt = 0; attempt < 30; ++attempt)
	{
		int size = 20; 
		int* arr = CreateRandomArray(size);
		CountingSort(arr, size);
		cout << "Array " << attempt + 1 << " is sorted: ";
		cout << std::boolalpha << IsSorted(arr, size);
		cout << std::endl;
		delete[] arr;
	}

	system("pause");

	const int countSortingArraySize = 20;
	int* countSortingArray = CreateRandomArray(countSortingArraySize);
	cout << "Array: ";
	PrintArray(countSortingArray, countSortingArraySize);
	CountingSort(countSortingArray, countSortingArraySize);
	cout << "Sorted array: ";
	PrintArray(countSortingArray, countSortingArraySize);
	cout << std::boolalpha << "Is sorted: " << IsSorted(countSortingArray, countSortingArraySize);
	cout << std::endl;*/


	// тест для сортування злиттям

	/*const int mergeSortingArraySize = 20;
	int* mergeSortingArray = CreateRandomArray(mergeSortingArraySize);
	cout << "Array: ";
	PrintArray(mergeSortingArray, mergeSortingArraySize);
	MergeSort(mergeSortingArray, 0, mergeSortingArraySize - 1);
	cout << "Sorted array: ";
	PrintArray(mergeSortingArray, mergeSortingArraySize);
	cout << std::boolalpha << IsSorted(mergeSortingArray, mergeSortingArraySize) << std::endl;

	system("pause");

	// тест для сортування злиттям 20 масивів
	for (int attempt = 0; attempt < 30; ++attempt)
	{
		int size = 20;
		int* arr = CreateRandomArray(size);
		MergeSort(arr, 0, size-1);
		cout << "Array " << attempt + 1 << " is sorted: ";
		cout << std::boolalpha << IsSorted(arr, size);
		cout << std::endl;
		delete[] arr;
	}*/

	// IsSorted()

	/*int SortedArray[] = { 1, 2, 3, 4, 5 };
	int UnsortedArray[] = { 2, 3, 1, 5, 4 };

	cout << "Array: ";
	PrintArray(SortedArray, 5);
	cout << "IsSorted(): " << std::boolalpha << IsSorted(SortedArray, 5);

	cout << std::endl;

	cout << "Array: ";
	PrintArray(UnsortedArray, 5);
	cout << "IsSorted(): " << std::boolalpha << IsSorted(UnsortedArray, 5);

	cout << std::endl;*/

	system("pause");
	return 0;
}

void PrintArray(int* arr, unsigned size)
{
	for (unsigned i = 0; i < size; ++i)
	{
		cout << arr[i] << ' ';
	}
	cout << '\n';
}

// створюється масив від 0 до 99
int* CreateRandomArray(unsigned size)
{
	int* arr = new int[size];
	for (unsigned i = 0; i < size; ++i)
	{
		arr[i] = (std::rand() % 100);
	}
	return arr;
}

void CountingSort(int* arrayToSort, unsigned size)
{
	//шукаємо найбільше значення
	unsigned maxValue = arrayToSort[0];
	for (unsigned i = 0; i < size; ++i)
	{
		if (maxValue < arrayToSort[i])
		{
			maxValue = arrayToSort[i];
		}
	}
	// створення масиву у яку будемо записувати підраховані елементи
	int countTableSize = maxValue + 1;
	int* countTable = new int[countTableSize];
	for (unsigned i = 0; i < countTableSize; ++i)
	{
		countTable[i] = 0;
	}
	for (unsigned i = 0; i < size; ++i)
	{
		// збільшити на одиничку кількість входження елемента оригінального масиву в масиві countTable
		countTable[arrayToSort[i]] += 1;
	}
	int countTableIndex = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		while (countTable[countTableIndex] == 0 and countTableIndex < countTableSize)
		{
			++countTableIndex;
		}
		arrayToSort[i] = countTableIndex;
		countTable[countTableIndex] -= 1;
	}
}

// функція що відповідає за злиття двох підмасивів
void Merge(int* arr, int begin, int end)
{
	int leftArrayIndex = begin;
	int middle = static_cast<int>((begin + end) * 0.5);
	int rightArrayIndex = middle + 1;
	int storage[STORAGE_MAX_SIZE];
	int storageCurrentIndex = 0;
	// [1, 4, 7] [2, 9, 10] -> storage[1, 2, 4, 7]
	while (leftArrayIndex <= middle and rightArrayIndex <= end)
	{
		if (arr[leftArrayIndex] <= arr[rightArrayIndex])
		{
			storage[storageCurrentIndex] = arr[leftArrayIndex];
			++leftArrayIndex;
		}
		else 
		{
			storage[storageCurrentIndex] = arr[rightArrayIndex];
			++rightArrayIndex;
		}
		++storageCurrentIndex;
	}
	// storage[1, 2, 4, 7] -> storage[1, 2, 4, 7]
	while (leftArrayIndex <= middle)
	{
		storage[storageCurrentIndex] = arr[leftArrayIndex];
		++leftArrayIndex;
		++storageCurrentIndex;
	}
	// storage[1, 2, 4, 7] -> storage[1, 2, 4, 7, 9, 10]
	while (rightArrayIndex <= end)
	{
		storage[storageCurrentIndex] = arr[rightArrayIndex];
		++rightArrayIndex;
		++storageCurrentIndex;
	}
	for (int i = 0; i < storageCurrentIndex; ++i)
	{
		arr[begin + i] = storage[i];
	}
}

// функція яка розбиватиме масив на підмасиви
void MergeSort(int* arr, int left, int right)
{
	if (left < right)
	{
		int middle = static_cast<int>((right + left) * 0.5);
		if (left + 1 == right)
		{
			if (arr[left] > arr[right])
			{
				int temp = arr[left];
				arr[left] = arr[right];
				arr[right] = temp;
			}
		}
		else
		{
			MergeSort(arr, left, middle);
			MergeSort(arr, middle + 1, right);
			Merge(arr, left, right);
		}
	}
}

bool IsSorted(int* arr, unsigned size)
{
	for (unsigned i = 0; i < size - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			return false;
		}
	}
	return true;
}