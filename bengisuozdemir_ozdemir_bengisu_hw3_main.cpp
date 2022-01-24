#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
using namespace std;
//Bengisu Ozdemir 26683 CS300-HW3 2021.
template <class Comparable>
void insertionSort(vector <Comparable> & a)
{
	int j;
	for (int p = 1;  p < a.size(); p++)
	{
		Comparable tmp = a[p];
		for (j = p; j > 0 &&  tmp < a[j - 1]; j --)
			a[j] = a[j -1];
		a[j] = tmp;
	}
}
void ToUpper(string & s)
// postcondition: s all lower case     
{
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = toupper(s[k]);
    }
}

string UpperString(const string & s)
{
    string word = s;
    ToUpper(word);
    return word;
}
inline int leftChild( int i )
{
	return 2*i+1;
}
template <class Comparable>
void quickSort(vector<Comparable> & a)
{
	quickSort( a, 0, a.size( ) - 1 );
}
template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
	vector<Comparable> tmpArray( a.size( ) );

	mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}
template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
	int center = ( left + right ) / 2;
	if ( a[ center ] < a[ left ] )
		swap( a[ left ], a[ center ] );
	if ( a[ right ] < a[ left ] )
		swap( a[ left ], a[ right ] );
	if ( a[ right ] < a[ center ] )
		swap( a[ center ], a[ right ] );

	// Place pivot at position right - 1
	swap( a[ center ], a[ right - 1 ] );
	return a[ right - 1 ];
}
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
	}
}
template <class Comparable>
void quickSort( vector<Comparable> & a, 
					int left, int right )
{
	if ( left + 10 <= right )
	{
	Comparable pivot = median3( a, left, right );
	int i = left, j = right - 1;
	for ( ; ; )
	{
		while ( a[ ++i ] < pivot ) { }

		while ( pivot < a[ --j ] ) { }

		if ( i < j )
			swap( a[ i ], a[ j ] );
		else
			break;
	}
	swap( a[ i ], a[ right - 1 ] );   // Restore pivot

	quickSort( a, left, i - 1 );       // Sort small elements
	quickSort( a, i + 1, right );    // Sort large elements
	}
    else  // Do an insertion sort on the subarray
		insertionSort( a, left, right );
}

template <class Comparable>
void mergeSort(vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right )
{
	if ( left < right )
	{
		int center = ( left + right ) / 2;
		mergeSort( a, tmpArray, left, center );
		mergeSort( a, tmpArray, center + 1, right );
		merge( a, tmpArray, left, center + 1, right );
	}
}

template <class Comparable>
void merge(vector<Comparable> & a, vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	// Main loop
	while ( leftPos <= leftEnd && rightPos <= rightEnd )
	{
		if ( a[ leftPos ] <= a[ rightPos ] )
			tmpArray[ tmpPos++ ] = a[ leftPos++ ];
		else
			tmpArray[ tmpPos++ ] = a[ rightPos++ ];
	}

	while ( leftPos <= leftEnd )    // Copy rest of first half
		tmpArray[ tmpPos++ ] = a[ leftPos++ ];

	while ( rightPos <= rightEnd )  // Copy rest of right half
		tmpArray[ tmpPos++ ] = a[ rightPos++ ];

	// Copy tmpArray back
	for ( int i = 0; i < numElements; i++, rightEnd-- )
		a[ rightEnd ] = tmpArray[ rightEnd ];

}

template <class Comparable>
void heapSort(vector<Comparable> & a)
{
// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size() -1; j >0; j--)
	{
  	     swap(a[0], a[j]);    // swap max to the last pos.
          percDown(a, 0, j); // re-form the heap
	}
}
template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
        int child;
        Comparable tmp;
        for (tmp=a[i] ; leftChild(i) < n; i = child )
        {
			child = leftChild(i);
			if ( child != n-1 && a[ child  ] < a[ child+1 ] )
				child++;
			if ( a[child ] > tmp )
				a[i] = a[ child ];
			else
				break;
        } 
        a[ i ] = tmp;
}
template <class Comparable>
vector<int> sequentialSearch(vector<Comparable> list, const Comparable key)
{
	vector<int> indexVector;
	bool changeOfInitial = true;
	int pos = 0;
	while(changeOfInitial)
	{
		bool innerLoop = true;
		if(list[pos] == key)
			indexVector.push_back(pos);
		else if(list[pos][0] == key[0])
		{
			int counter = 0;
			for (int i = 1; i < key.length() && innerLoop; i++)
			{
				if(list[pos][i] == key[i])
					counter ++;
				else
					innerLoop = false;
			}
			if(counter == key.length()-1)
				indexVector.push_back(pos);
			if(pos+1 <= list.size()-1)
				pos++;
			else
				break;
			if(list[pos][0] != key[0])
				changeOfInitial = false;
			
		}
		else
		{
			if(pos+1 <= list.size()-1)
				pos++;
			else
				break;
		}
	}
	return indexVector;
}
template <class Comparable>
void printElements(vector<int> indexList, vector<Comparable> list)
{
	quickSort(indexList);
	for (int i = 0; i < indexList.size(); i++)
	{
		string line = list[indexList[i]];
		int space1 = line.find(" ");
		int space2 = line.find(" ", space1+1);
		string name_surname = line.substr(0, space2);
		string number_city = line.substr(space2,line.length());
		ToUpper(name_surname);
		cout << name_surname << number_city <<endl;
	}
}
template <class Comparable>
vector<int> binarySearch(vector<Comparable> &list, const string& key, int low, int high)
{
	vector<int> indexVector;
    int mid, counter = 0;                       // middle of current range
	if (low > high && indexVector.size() == 0)
		return indexVector;                       //not found, list returned empty
    else
	{
		//if the key is one word we get only name or a part of the name;thus, serach all possible names, else search the whole name
		if(key.find(" ")< 0)
			indexVector.push_back(binarySearchLong(list, key, 0, list.size()));
		else
		{
			mid = (low + high)/2;
			int insideCounter = 0;
			if (list[mid][0] == key[0])       // found key or partial 
			{
				for (int i = 1; i < key.length(); i++)
				{
					if(list[mid][i] == key[i])
						counter ++;
				}
				if(counter == key.length()-1)
				{
					indexVector.push_back(mid);
				bool ifFound = true;
				int tempMid = mid;
				while(ifFound)
				{
					insideCounter = 0;	
					tempMid++;
					if(list[tempMid][0] == key[0])
					{
						for (int j = 1; j < key.length(); j++)
						{
							if(list[tempMid][j] == key[j])
								insideCounter ++;
						}
						if(insideCounter == key.length()-1)
							indexVector.push_back(tempMid);
					}
					else
						ifFound = false;
				}
				while(!ifFound)
				{	
					insideCounter = 0;	
					tempMid--;
					if(list[tempMid][0] == key[0])
					{
						for (int j = 1; j < key.length(); j++)
						{
							if(list[tempMid][j] == key[j])
								insideCounter ++;
						}
						if(insideCounter == key.length()-1)
							indexVector.push_back(tempMid);
					}
					else
						ifFound = true;
					}
				}
			}
			if(list[mid][0] == key[0] && insideCounter+1<=key.length() && list[mid][insideCounter+1] != key[insideCounter])
			{
				bool ifFound = true, Match = true;
				int tempMid = mid;
				while(ifFound && Match)
				{
					int count = 0;
					bool innerLoop = true;
					if(tempMid+1<=list.size()-1)
						tempMid++;
					else
						break;
					if(list[tempMid][0] == key[0])
					{
						for (int j = 1; j < key.length() && innerLoop; j++)
						{
							if(list[tempMid][j] == key[j])
								count ++;
							else
								innerLoop = false;
						}
						if(count == key.length()-1)
							indexVector.push_back(tempMid);
						else if(list[tempMid][0] != key[0])
							Match = false;
						else
							continue;
					}
					else
						ifFound = false;
				}
				tempMid = mid;
				while(!ifFound || !Match)
				{	
					bool innerLoop = true;
					int count = 0;	
					if(tempMid-1>=0)
						tempMid--;
					else
						break;
					if(list[tempMid][0] == key[0])
					{
						for (int j = 1; j < key.length() && innerLoop; j++)
						{
							if(list[tempMid][j] == key[j])
								count ++;
							else
								innerLoop = false;
						}
						if(count == key.length()-1)
							indexVector.push_back(tempMid);
						else if(list[tempMid][0] != key[0])
							Match = true;
						else
							continue;
					}
					else
						ifFound = true;	
				}
			}
			else if (list[mid][0] < key[0])   // key in upper half
				return binarySearch(list, key, mid+1, high);
				
			else if(list[mid][0] > key[0])
				return binarySearch(list, key, low, mid-1);
		
		}
	}
	return indexVector;
}
template <class Comparable>
int binarySearchLong(vector<Comparable> &list, const string& key, int low, int high)
{
	if (low > high)
		return -1;
	else
	{
		int mid = (low + high)/2;
		if(list[mid] == key)
			return mid;
		else if(list[mid] < key)
			return binarySearchLong(list, key, mid+1, high);
		else if(list[mid] > key)
			return binarySearchLong(list, key, low, mid-1);
		else
			return -1; //not found
	}
}
long double speedUp(long long one, long long two)
{
	if(two != 0)
		return one/two;
	return 0;
}
int main()
{
	vector<string> quick_v, insertion_v, merge_v, heap_v, temp_v;
	ifstream input;
	string fileName, word, line;
	cout << "Please enter the contact file name:" <<endl;
	cin>>fileName;
	input.open(fileName.c_str());
	if(!input.fail())
	{
		cout << "Please enter the word to be queried :"<<endl;
		cin.ignore();
		getline(cin, word);
		cout <<endl << "Sorting the vector copies"<<endl<<"======================================"<<endl;
		for (int i = 0; getline(input, line); i++)
		{
			temp_v.push_back(line);
		}
		int N = 100;
		auto startQ = std::chrono::high_resolution_clock::now();
		
		quick_v = temp_v;
		quickSort(quick_v);
		
		auto endQ = std::chrono::high_resolution_clock::now();
		long long timerQ = (endQ-startQ).count();

		auto startI = std::chrono::high_resolution_clock::now();
		
		insertion_v = temp_v;
		insertionSort(insertion_v);
		
		auto endI = std::chrono::high_resolution_clock::now();
		long long timerI = (endI-startI).count();

		auto startM = std::chrono::high_resolution_clock::now();
		
		merge_v = temp_v;
		mergeSort(merge_v);
		
		auto endM = std::chrono::high_resolution_clock::now();
		long long timerM = (endM-startM).count();

		auto startH = std::chrono::high_resolution_clock::now();
		
		heap_v = temp_v;
		heapSort(heap_v);
		
		auto endH = std::chrono::high_resolution_clock::now();
		long long timerH = (endH-startH).count();
		
		cout << "Quick Sort Time: "<< timerQ <<" Nanoseconds"<<endl
			<< "insertion Sort Time: "<< timerI <<" Nanoseconds"<<endl
			<< "Merge Sort Time: "<< timerM <<" Nanoseconds" <<endl
			<< "Heap Sort Time: "<< timerH <<" Nanoseconds"<<endl;

		cout << "Searching for "<< word << endl << "======================================" << endl;
		cout << "Search results for Binary Search: "<<endl;
		vector<int> binary_v;
		auto startB = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			binary_v = binarySearch(quick_v, word, 0, quick_v.size());
		}
		auto endB = std::chrono::high_resolution_clock::now();
		long long timerB = (endB-startB).count()/100;
		
		if(binary_v.size() == 0)
		{
			string tempWord = word;
			ToUpper(tempWord);
			cout << tempWord <<" does NOT exist in the dataset" <<endl<<endl;
		}
		else
		{
			printElements(binary_v, quick_v);
		}
		cout << endl << "Binary Search Time: "<< timerB <<" Nanoseconds"<<endl<<endl;
		cout << "Search results for Sequential Search:"<<endl;
		vector<int> seq_v;
		auto startS = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			seq_v = sequentialSearch(quick_v, word);
		}
		auto endS = std::chrono::high_resolution_clock::now();
		long long timerS = (endS-startS).count()/100;
		if(seq_v.size() == 0)
		{
			string tempWord = word;
			ToUpper(tempWord);
			cout << tempWord <<" does NOT exist in the dataset" <<endl<<endl;
		}
		else
		{
			printElements(seq_v, quick_v);
		}
		cout << endl <<"Sequential Search Time: "<< timerS <<" Nanoseconds"<<endl<<endl;
		cout << "SpeedUp between Search Algorithms"<<endl;
		cout << "======================================" <<endl;
		cout << "(Sequential Search/ Binary Search) SpeedUp = "<<speedUp(timerS, timerB)<<endl<<endl;
		cout << "SpeedUps between Sorting Algorithms"<<endl;
		cout << "======================================"<<endl;
		cout << "(Insertion Sort/ Quick Sort) SpeedUp = "<<speedUp(timerI, timerQ)<<endl;
		cout << "(Merge Sort / Quick Sort) SpeedUp = " << speedUp(timerM, timerQ)<<endl;
		cout << "(Heap Sort / Quick Sort) SpeedUp = "<<speedUp(timerH, timerQ)<<endl;

	}

	return 0;
}