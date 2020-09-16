#include "header.h"


int main()
{
	
	int number_of_lines = 0;
	Line* normal_lines = Read_lines_fast("in.txt", &number_of_lines);

	//Print_lines(normal_lines, number_of_lines, "Look at new read");

	
	Line* copy_lines = Copy_lines(normal_lines, number_of_lines);

	Insertion_sort(copy_lines, number_of_lines, sizeof(Line), comparator_normal);

	printf("\nCHECKED\n");
	
	Write_lines("out.txt", copy_lines, number_of_lines, "w", "Watch sorted lines by first elements");
	
	Insertion_sort(copy_lines, number_of_lines, sizeof(Line), comparator_back);

	Write_lines("out.txt", copy_lines, number_of_lines, "a", "Watch sorted lines by last elements");

	Write_lines("out.txt", normal_lines, number_of_lines, "a", "Watch original text");
	
	Delete_lines(normal_lines, number_of_lines);
	Delete_lines(copy_lines, number_of_lines);

	return 0;
	
}


