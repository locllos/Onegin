#include "header.h"


int main()
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

	free(buffer);
	free(copy_buffer);
	free(normal_lines);
	free(copy_lines);
	
	return 0;
	
}


