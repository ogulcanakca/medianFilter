#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <map>
using namespace std;

int* sortArray(int arr[], int size) // Selection Sort
{
	int i, j;
	int minimumindex;
	for (i = 0; i < size; i++)
	{
		minimumindex = i;
		for (j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[minimumindex])
			{
				minimumindex = j;

			}

		}
		int temp = arr[i];
		arr[i] = arr[minimumindex];
		arr[minimumindex] = temp;
	}
	return arr;
}

list<string> medianFiltering(list<string> column)
{

	list<string> returned_column;
	int i = 0;
	int j = 0;
	int size = column.size();
	int median_filter[5];
	int median = 0;

	for (list<string>::iterator number = column.begin(); number != column.end(); number++)
	{
		median_filter[j] = stoi(*number);

		if (j == 4)
		{
			sortArray(median_filter, j + 1);
			int median = median_filter[2];
			returned_column.push_back(to_string(median));
			j = -1;
			number--;
			number--;
			number--;
		}
		j++;
	}
	return returned_column;

}
void fileReading_in_number_with_char(ifstream& file_reading)
{
	int count = 0;
	list<string> temp;

	list<string> first;
	list<string> second;
	list<string> third;
	list<string> fourth;

	if (file_reading)
	{
		int count = 0;
		char item;
		string temp_ch;
		string number;
		int hyphen = 0;

		while (file_reading.get(item))
		{

			if (item != '.' && item != '0' && item != ' ')
			{

				temp_ch += item;

			}
			if (item == '\n')
			{

				for (auto ch : temp_ch)
				{
					if (ch != '\t' && ch != '\n')
					{

						number = +ch;
						if (ch == '-')
						{
							hyphen = count;
						}
						if (hyphen + 1 == count)
						{
							number = "-" + number;
						}
					}
					else
					{

						temp.push_back(number);
						number = "";
					}

					count++;


				}
				temp_ch = "";
			}

		}

		file_reading.close();
	}
	else
	{
		cout << "Dosya açılamadı." << endl;
	}

	for (auto number : temp)
	{
		count++;
		if (count % 4 == 1)
		{
			first.push_back(number);
		}
		if (count % 4 == 2)
		{
			second.push_back(number);
		}
		if (count % 4 == 3)
		{
			third.push_back(number);
		}
		if (count % 4 == 0)
		{
			fourth.push_back(number);
		}

	}
	first = medianFiltering(first);
	second = medianFiltering(second);
	third = medianFiltering(third);
	fourth = medianFiltering(fourth);
	/*for (auto number : fourth)
	{
		cout << number << endl;
	}*/
	ofstream outfile("sig4Channels_last.txt");

	for(int i =0; i<first.size(); i++)
	{
		outfile << first.front() <<"\t" << second.front() << "\t" << third.front() << "\t" << fourth.front() <<endl;
		first.pop_front();
		second.pop_front();
		third.pop_front();
		fourth.pop_front();
	}

}

int main()
{
	ifstream file_reading;
	string filename_1 = "sig4Channel.txt";
	file_reading.open(filename_1);
	fileReading_in_number_with_char(file_reading);
}
