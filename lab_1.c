#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/time.h>

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void CountingSort(int arr[], int size)
{
int max = 0, min = 100000;
for (int i = 0; i < size; i++)
{
	if (arr[i] > max)
		max = arr[i];
	if (arr[i] < min)
		min = arr[i];
}
	int a_arr[max + 1 - min];
	for (int i = 0; i < max + 1 - min; i++)
	{
		a_arr[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		a_arr[arr[i] - min] = a_arr[arr[i] - min] + 1;
	}
	int i = 0;
	for (int j = min; j < max + 1; j++)
	{
		while (a_arr[j-min] != 0)
		{
			arr[i] = j;
			a_arr[j-min]--;
			i++;
		}
	}
}

void InsertionSort(int arr[], int size)
{
int temp;
	for (int i = 1; i < size; i++)
	{
		temp = arr[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[j] < temp)
				break;
			arr[j + 1] = arr[j];
			arr[j] = temp;
		}
	}
}

void QuickSort(int arr[], int first, int last)
{
	int i = first, j = last, x = arr[first + (last - first) / 2];
	int temp;

	do {
		while (arr[i] < x) i++;
		while (arr[j] > x) j--;

		if (i <= j) {
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
		QuickSort(arr, i, last);
	if (first < j)
		QuickSort(arr, first, j);
}

void CW_Time(long size, FILE *sort)
{
	int *arr = malloc(size * sizeof(int));
	long long sum = 0, esum = 0;
	int f = 0;

	for (long i = 0; i < size; i++)
	{
		arr[i] = getrand(0, 100000);
		sum += arr[i];
	}
	double ctime = wtime();
	CountingSort(arr, size);
	ctime = wtime() - ctime;
	for (int i = 0; i < size; i++)
	{
		//printf("%d\n", arr[i]);
		esum += arr[i];
	}
	if (sum != esum)
	{
		f = 1;
		printf("Error(sum): f = %d sum = %lld esum = %lld\n", f, sum, esum);
	}
	for (int i = 0; (i < size - 1) && (f = 0); i++)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Error(cs): arr[i] = %d arr[i+1] = %d i = %d\n", arr[i], arr[i + 1], i);
			f = 1;
		}
	}
	
	f = 0;
	esum = 0;
	sum = 0;

	for (long i = 0; i < size; i++)
	{
		arr[i] = getrand(0, 100000);
		sum += arr[i];
	}
	double itime = wtime();
	InsertionSort(arr, size);
	itime = wtime() - itime;
	for (int i = 0; i < size; i++)
	{
		//printf("%d\n", arr[i]);
		esum += arr[i];
	}
	if (sum != esum)
	{
		f = 1;
		printf("Error(sum): f = %d sum = %lld esum = %lld\n", f, sum, esum);
	}
	
	f = 0;
	esum = 0;
	sum = 0;

	for (long i = 0; i < size; i++)
	{
		arr[i] = getrand(0, 100000);
		sum += arr[i];
	}
	double qtime = wtime();
	QuickSort(arr, 0, size - 1);
	qtime = wtime() - qtime;
	for (int i = 0; (i < size - 1) && (f = 0); i++)
	{
		if (arr[i] > arr[i + 1])
		{
			printf("Error(qs): arr[i] = %d arr[i+1] = %d i = %d\n", arr[i], arr[i + 1], i);
			f = 1;
		}
	}
	for (int i = 0; i < size; i++)
	{
		//printf("%d\n", arr[i]);
		esum += arr[i];
	}
	if (sum != esum)
	{
		f = 1;
		printf("Error(sum): f = %d sum = %lld esum = %lld\n", f, sum, esum);
	}
	
	free(arr);

	fprintf(sort, "%ld %f %f %f\n", size, ctime, itime, qtime);
}


int main()
{
int size = 50000;
FILE *sort = fopen("sort.dat", "w");
for (int i = 1; i <= 20; i++)
{
	CW_Time(i * size, sort);
}
fclose(sort);
return 0;
}
