#include "header.h"


int main(int argC, char* argV[])
{

	int number_of_lines = 0;
	char* buffer = NULL;
	char* copy_buffer = NULL;
	
	Line* normal_lines = Read_lines_fast("in.txt", &number_of_lines, &buffer);

	//Print_lines(normal_lines, number_of_lines, "Look");

	Line* copy_lines = Copy_lines(normal_lines, number_of_lines, &buffer, &copy_buffer);

	QQsort(copy_lines, number_of_lines, sizeof(Line), comparator_normal);
	
	Write_lines("out.txt", copy_lines, number_of_lines, "w", "Watch sorted lines by first elements");
	
	Insertion_sort(copy_lines, number_of_lines, sizeof(Line), comparator_back);

	Write_lines("out.txt", copy_lines, number_of_lines, "a", "Watch sorted lines by last elements");
	Write_lines("out.txt", normal_lines, number_of_lines, "a", "Watch original text");

	Delete_lines(normal_lines, buffer);
	Delete_lines(copy_lines, copy_buffer);

	if (argC > 1 && *argV[1] == '-')
	{
		if (*(argV[1] + 1) == 'u')
		{
			printf("YOU HAVE LAUNCHED UNIT TESTS\n");
			Unit_tests();
		}
		else
			printf("INCORRECT  KEY\n");
	}
	
	return 0;
	
}


