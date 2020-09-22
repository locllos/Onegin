#include "header.h"


int main(int argC, char* argV[])
{
	char* filename = "in.txt";
	
	if (argC > 1 && *argV[1] == '-')
	{
		if (*(argV[1] + 1) == 'u')
		{
			printf("YOU HAVE LAUNCHED UNIT TESTS\n");
			return Unit_tests();
		}
		
		else if (argC == 3 && *(argV[1] + 1) == 'n')
			filename = argV[2];
		
		else 
			return INCORRECT_KEY;
	}
	
	else if (argC > 1)
		return INCORRECT_INPUT;
	
	int number_of_lines = 0;
	char* buffer = NULL;

	Line* normal_lines = Read_lines_fast(filename, &number_of_lines, &buffer);

	//Print_lines(normal_lines, number_of_lines, "Look");

	Line* copy_lines = Copy_lines(normal_lines, number_of_lines, &buffer);

	QQsort(copy_lines, number_of_lines, sizeof(Line), Comparator_normal);

	Write_lines("out.txt", copy_lines, number_of_lines, "w", "Watch sorted lines by first elements");

	Insertion_sort(copy_lines, number_of_lines, sizeof(Line), Comparator_back_but_I_dont_like_it);

	Write_lines("out.txt", copy_lines, number_of_lines, "a", "Watch sorted lines by last elements");
	Write_lines("out.txt", normal_lines, number_of_lines, "a", "Watch original text");

	Delete_lines(normal_lines);
	Delete_lines(copy_lines);

	free(buffer);

	return NORMAL_SITUATION;
	
}


