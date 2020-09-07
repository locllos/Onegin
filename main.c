#include "header.h"


int main()
{
	int number_of_lines = 0;
	Line* normal_lines = Read_lines("in.txt", &number_of_lines);

	Write_lines("out.txt", normal_lines, number_of_lines, "w", "Watch lines without any sorts");

	Erase_end_punctuation_marks(normal_lines, number_of_lines);

	qsort(normal_lines, number_of_lines, sizeof(Line), comparator);

	Write_lines("out.txt", normal_lines, number_of_lines, "a", "Watch sorted lines by first elements");

	Line* reverse_lines = Reverse_lines(normal_lines, number_of_lines);

	qsort(reverse_lines, number_of_lines, sizeof(Line), comparator);

	Line* reverse_reverse_lines = Reverse_lines(reverse_lines, number_of_lines);

	Write_lines("out.txt", reverse_reverse_lines, number_of_lines, "a", "Watch sorted lines by last elements");

	Delete_lines(normal_lines, number_of_lines);
	Delete_lines(reverse_lines, number_of_lines);
	Delete_lines(reverse_reverse_lines, number_of_lines);

	return 0;
}


