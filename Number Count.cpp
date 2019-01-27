#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void heading(ofstream &outfile);
void getData(int a[]);
void printReport(int b[]);
void getMode(int g[], ofstream &outfile);

const int Isize = 500;
const int Usize = 106;
int main()
{
	//initializes all values to zero
	int integers[Isize] = { 0 };

	getData(integers);
	printReport(integers);

	system("pause");
	return 0;
}


//==================================================================

//*************************HEADING********************************
void heading(ofstream &outfile)
{
	outfile << "Purpose:This program reads numbers from a file and counts how many \n";
	outfile << "times each number occurs.It then lists them is ascending order \n";
	outfile << "based on number of occurrence then finds the mode. \n\n";
}

//**************************GET DATA****************************
void getData(int a[])
{
	ifstream infile;
	string fileName;

	cout << "Please Insert Name of File To Read From. \n";
	cin >> fileName;
	infile.open(fileName);
	//If the file is not open the do the fillowing
	if (!infile.is_open())
	{
		int x, chances = 2;
		for (x = 0; !infile.is_open() && x < 3; x++)
		{
			cout << "File Name Incorrect Please Try Again, "
				//lets user know how much chances left
				<< chances << " Chances Left \n";
			cin >> fileName;
			infile.open(fileName);
			//decrements chances
			chances--;
		}

	}
	// If the file is found then continue
	if (infile.is_open())
	{
		int x, num;
		for (x = 0; infile >> num; x++)
		{
			a[x] = num;
		}
		//closes file
		infile.close();
	}
	else
	{
		cout << " File Still Not Found, Thank You For Trying... BYE !! \n";
	}

}

//*************************PRINT REPORT**************************

void printReport(int i[])
{
	//New array to hold occurrences of numbers
	int freq[Usize] = { 0 };
	int x, y, j, m, value, max = INT_MIN;
	string file2;

	ofstream outfile;
	cout << "Please Insert Name of File To Write to. \n";
	cin >> file2;
	outfile.open(file2);

	heading(outfile);

	for (x = 0; x < Isize; x++)
	{
		//hold the value of the cell in a variable
		value = i[x];
		//variable acts as the cell number and adds one to it
		freq[value] = freq[value] +1 ;
	}
	//finding the higest value in the occurrence array
	for (j = 0; j < Usize; j++)
	{
		if (max < freq[j])
		{
			max = freq[j];
		}
	}
	outfile << setw(7) << "Integer " << setw(9) << " Frequency \n\n";
	/* look for all occurence of the max the print it out,
	the decrement max the repeat. */

	for (max; max > 0; max--) // used to decrement max
	{
		for (m = 0; m < Usize; m++)
		{
			// if max equal to the value in array
			if (max == freq[m])
				outfile << "   " << setw(4) << m << " | " << setw(4)
				<< freq[m] << endl;
		}
	}

	getMode(freq, outfile);

	//close output file
	outfile.close();
}

//************************GET MODE******************************

void getMode(int g[], ofstream &outfile)
{

	int j, i, max = INT_MIN, num = INT_MIN;

	//finding the higest value in the occurrence array again
	for (j = 0; j < Usize; j++)
	{
		if (max < g[j])
		{
			max = g[j];
		}
	}

	for (i = 0; i < Usize; i++)
	{
		/* If the occurance is equal to the max occuerence, and that number is
		larger than the previous number that had the max occurrence, then
		save it in i*/
		if (max == g[i] && num < i)
		{
			num = i;
		}
	}

	outfile << "\n The largest number that occured the most was "
		<< num << " and it occured " << max << " times. \n";
}

