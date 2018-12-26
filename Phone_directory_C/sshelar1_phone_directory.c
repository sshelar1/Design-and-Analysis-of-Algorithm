#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char first_name[15];
	char last_name[15];
	char mob_no[15];
}Names;

static int size = 0;

Names my_name[50];

void create(char *);

void display();

void swap(int, int);
int struct_cmp_sort(Names, Names);
int partition(int, int);
void quick_Sort(int, int);
void sort_contact();

int binary_Search(Names, int, int);
void search(char *);

void delete(char *);

void insert(char *, char *);

int main(int argc, char* argv[])
{
	create(argv[1]);
	
	int choice;
	char ch;

	do	
	{
		printf("\n1.sort_contact   2.search  3.delete   4.insert: ");
		scanf("%d", &choice);
		while(getchar()!='\n');
		switch(choice)
		{
			case 1:
				{
					sort_contact();
					display();
					break;
				}

			case 2:
				{
					char search_name[50];
					printf("\nEnter name to search: ");
					fgets(search_name, 30, stdin);
					search(search_name);
					break;
				}

			case 3:
				{
						char delete_name[30];
						printf("\nEnter Name (and Number) to delete: ");
						printf("\nxxxx xxxxx   or   xxxx xxxx, (xxx)xxx-xxxx\n");
						fgets(delete_name, 30, stdin);
						delete(delete_name);
						display();
						break;
				}

			case 4:
				{
					char insert_name[50];
					printf("\nEnter Name and Nunber in form xxx xxxx, (xxx)xxx-xxx:\n");
					fgets(insert_name, 50, stdin);
					char *s = ",";
					char *name = strtok(insert_name, s);
					char *number = strtok(NULL, s);
					insert(name, number);
					display();
					break;
				}
			}

			printf("\nDo you want to countinue ?(y/n): ");
			scanf("%c", &ch);
			while(getchar()!='\n');
	} while(ch == 'y' || ch == 'Y');

	return 0;
}

//Reads name and Number from file and Store in Phone Directory
void create(char *fnamef)
{
	FILE *fptr = fopen(fnamef, "r");

	char name[15];
	char sname[15];
	char mno[15];

	int i=0;
	//This loop will execute till it reaches end of file
	while(fscanf(fptr,"%s %s %s",name, sname, mno) !=EOF)
	{
		strcpy(my_name[i].first_name, name);
		strcpy(my_name[i].last_name, sname);
		strcpy(my_name[i].mob_no, mno);

		strcpy(my_name[i].last_name, strtok(my_name[i].last_name, ","));

		i++;
		size++;
	}

	fclose(fptr);
}

//Displays Phone Directory
void display()
{
	int i;
	printf("\n");
	for(i=0; i<size; i++)
		printf("%s\t%10s\t%s\n", my_name[i].first_name, my_name[i].last_name, my_name[i].mob_no);
}

//Swaps two Structures
void swap(int a, int b)
{
	Names temp_struct;
	temp_struct = my_name[a];
	my_name[a] = my_name[b];
	my_name[b] = temp_struct;
}

int struct_cmp_sort(Names x, Names y)
{
	if(strcmp(x.first_name, y.first_name) < 0)
		return 1;
	else if(strcmp(x.first_name, y.first_name) == 0)
	{
		if(strcmp(x.last_name, y.last_name) < 0)
			return 1;
		else if(strcmp(x.last_name, y.last_name) == 0)
		{
			if(strcmp(x.mob_no, y.mob_no) < 0)
				return 1;
		}
	}

	return 0;
}

int partion(int start, int end)
{
	int pivotIndex = start + rand()%(end - start + 1);
	Names pivot;
	int count = start - 1;
	int j;
	pivot = my_name[pivotIndex];
	swap(pivotIndex, end);
	for (j = start; j < end; j++)
	{
		if (struct_cmp_sort(my_name[j], pivot))
		{
			count++;
			swap(count, j);
		}
	}
	swap(count+1, end);
	return count + 1;
}

void quick_Sort(int min, int max)
{
	int j;
	if (min < max)
	{
		j = partion(min, max);
		quick_Sort(min, j-1);
		quick_Sort(j+1, max);
	}
}

//Sorts Phone Directory
void sort_contact()
{
	quick_Sort(0, size-1);
}

int binary_Search(Names key, int low, int high)
{
	int mid;
	int ret_val = -1;
	while(low <= high)
	{
		mid = (low + high)/2;
		if(strcmp(key.first_name, my_name[mid].first_name) < 0)
			high = mid - 1;

		else if(strcmp(key.first_name, my_name[mid].first_name) > 0)
			low = mid + 1;

		else
		{
			if(strcmp(key.last_name, my_name[mid].last_name) < 0)
				high = mid - 1;

			else if(strcmp(key.last_name, my_name[mid].last_name) > 0)
				low = mid + 1;

			else
			{
				if(strlen(key.mob_no) != 13)
					return mid;

				else
				{
					if(strcmp(key.mob_no, my_name[mid].mob_no) < 0)
					{
						high = mid - 1;
						ret_val = -2;
					}

					else if(strcmp(key.mob_no, my_name[mid].mob_no) > 0)
					{
						low = mid + 1;
						ret_val = -2;
					}

					else
						return mid;
				}
			}
		}

	}
	return ret_val;
}

//Search for Name in Directory
void search(char *name)
{
	Names temp;
	int val = -1;
	char *s = " ";
	strcpy(temp.first_name, strtok(name,s));
	strcpy(temp.last_name, strtok(NULL, s));

	int x = strlen(temp.last_name) - 1;
	temp.last_name[x] = '\0';

	val = binary_Search(temp, 0, size-1);

	if(val == -1)
		printf("%s %s is not in Phone Directory...\n", temp.first_name, temp.last_name);

	else if(val == -2)
		printf("%s %s is in Phone Directory. But Number is wrong..\n", temp.first_name, temp.last_name);

	else
		printf("%s %s is at position %d in Phone Directory...\n", temp.first_name, temp.last_name, (val+1));
}

//Delete name from Phone Directory
void delete(char *name)
{
	Names temp;
	int val = -1;
	int i;
	char delete_name[50];

	if(strlen(name) > 20)
	{
		char *s = ",";
		strcpy(delete_name, strtok(name, s));
		char *number = strtok(NULL, s);
		strcpy(temp.mob_no, number);
		int last_digit = strlen(temp.mob_no) - 1;
		temp.mob_no[last_digit] = '\0';
		strcpy(temp.mob_no, strtok(temp.mob_no," "));
	}
	else
		strcpy(delete_name, name);

	char *s1 = " ";

	strcpy(temp.first_name, strtok(delete_name,s1));
	strcpy(temp.last_name, strtok(NULL, s1));

	if(strlen(name) < 20)
	{
		int last_char = strlen(temp.last_name) - 1;
		temp.last_name[last_char] = '\0';
	}

	val = binary_Search(temp, 0, size-1);


	if(val == -1)
		printf("%s %s is not in Phone Directory...\n", temp.first_name, temp.last_name);

	else if(val == -2)
		printf("%s %s is in Phone Directory. But Number is wrong..\n", temp.first_name, temp.last_name);

	else
	{
		for(i = val; i < size-1; i++)
		{
			my_name[i] = my_name[i+1];
		}
		size--;
	}
}

//Inserts Name and Number in Phone Directory
void insert(char* name, char* phone_number)
{
	Names temp;
	int val = -1;
	char *s = " ";
	int i;
	strcpy(temp.first_name, strtok(name,s));
	strcpy(temp.last_name, strtok(NULL, s));
	strcpy(temp.mob_no, phone_number);

	int last = strlen(temp.mob_no) - 1;
	temp.mob_no[last] = '\0';
	strcpy(temp.mob_no, strtok(temp.mob_no," "));
	
	my_name[size] = temp;
	size++;
	sort_contact();
}
