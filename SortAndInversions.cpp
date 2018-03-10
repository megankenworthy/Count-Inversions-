// Megan Kenworthy
// HW4 - Counting Inversions 
// Dr. Lall - CS371
// 9 March 2018

#include <iostream>
#include <cstdlib>

using namespace std;

int SortAndCount(int* MainList, int start, int finish);
int Merge(int* MainList, int Start, int Finish, int Middle);


int main()
{
	int lenlist; 		//the length of input list 
	cin >> lenlist;

	int List [lenlist];	//initialize list of len, lenlist 

	for(int i=0; i<lenlist; i++)
	{
		int inputint; 
		cin >> inputint;
		List[i] = inputint;
	}

	int NumberInversions;	//Initializing total inversions to the return of SortAndCount 
	NumberInversions = SortAndCount(List,0,lenlist-1);
	cout<<NumberInversions<<"\n";
	return 0;
}

//Pre: Input list, starting index and ending index
//Post: The total number of inversions in the list 
int SortAndCount(int* MainList, int start, int finish)
{
	int half=0;				//initializing the mid point 
	int totalinvert = 0;	//initializing number of inversions 

	//while you are looking at list of len at least 1 
	if(finish>start)
	{
		half = (start+finish)/2;							//find mid point 
		totalinvert = SortAndCount(MainList,start,half);	//recursively call left half
		totalinvert += SortAndCount(MainList,half+1,finish);//recursively call right half

		totalinvert += Merge(MainList,start,finish,half+1);	//merge the two and count inversions
	}
	return totalinvert; 
}

//Pre: Input list, starting, finishing and middle indices
//Post: The number of inversions between lists
int Merge(int* MainList, int Start, int Finish, int Middle)
{
	int currStart;    				//temporary variables for starting locations 
	int currMiddle;
	int currTemp;					//current location in temp array
	int TempList[Finish-Start+1];	//array with sorted vals

	currStart = Start;				
	currMiddle = Middle;			
	currTemp = Start;

	int inversions = 0;

	//while all elements in the left half haven't been checked 
	//and all in the right half have not been checked
	while(currStart<=Middle-1 && currMiddle<=Finish)
	{
		//if element on left side is less than that on the element on the right
		if(MainList[currStart]<MainList[currMiddle])
		{
			TempList[currTemp] = MainList[currStart]; //update temp list
			currTemp++;
			currStart++;
		}

		//there is an inversion, element on left > element on right 
		else
		{
			TempList[currTemp] = MainList[currMiddle]; //update temp list
			currTemp++;
			currMiddle++;

			//element on right will be inverted with all of those remaining on the 
			//left hand side between positions Middle-currStart
			//because both sublists, L and R, are sorted 
			inversions = inversions + (Middle-currStart); //update inversions
		
		}
	}

	//for remaining elements on left side
	while(currStart<=Middle-1)
	{
		TempList[currTemp] = MainList[currStart];	//update temp list
		currTemp++;
		currStart++;		
	}

	//for remaining elements on right side
	while(currMiddle<=Finish)
	{
		TempList[currTemp] = MainList[currMiddle];	//update temp list 
		currTemp++;
		currMiddle++;
	}

	//update mainlist to be sorted as templist 
	for(int i=Start; i <= Finish; i++)
	{
		MainList[i] = TempList[i];
	}

	return inversions;
}






