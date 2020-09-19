#include "header.h"

Line* Read_lines_fast(const char* filename, int* amount_of_lines, char** buffer)
{
	const int approx_length = __Approx_Length__(filename);

	FILE* file = fopen(filename, "r");
	*buffer = (char*)calloc(approx_length + 1, sizeof(char));

	const int length = fread(*buffer, sizeof(char), approx_length + 1, file);
	
	int number_of_lines = approx_length - length;
	Line* lines = (Line*)calloc(number_of_lines + 5, sizeof(Line)); //+5 - ШОБ НАВЕРНЯКА

	int cur_size = 0,
		cur_line = 0;
	for (int i = 0; i < length; ++i)
	{
		if ((*buffer)[i] != '\n')
			++cur_size;
		else
		{
			lines[cur_line].size = cur_size;
			lines[cur_line].string = *buffer + i - cur_size;
			lines[cur_line].string[cur_size] = '\0';
			cur_line++;
			cur_size = 0;
		}
	}

	//На случай если в конце файла не было проставлено символов перехода на следующую строку
	if ((*buffer)[length] != '\n')
	{
		(*buffer)[length] = '\0';
		lines[number_of_lines].size = cur_size;
		lines[number_of_lines].string = *buffer + length - cur_size;
		number_of_lines++;
	}

	fclose(file);
	
	(*amount_of_lines) = number_of_lines;
	return lines;
}

Line* Copy_lines(Line* lines, int number_of_lines, char** buffer, char** copy_buffer)
{
	const int length = Get_length(lines, number_of_lines);
	 
	*copy_buffer = (char*)calloc(length + 1, sizeof(char));
	Line* copy_lines = (Line*)calloc(number_of_lines, sizeof(Line));

	int cur_line = 0; 
	for (int i = 0; i < length; ++i)
	{
		(*copy_buffer)[i] = (*buffer)[i];

		if ((*copy_buffer)[i] == '\0')
		{
			copy_lines[cur_line].string = *copy_buffer + i - lines[cur_line].size;
			copy_lines[cur_line].size = lines[cur_line].size;
			cur_line++;
			
		}
	}

	return copy_lines;
}

char* Erase_punct_marks(char* string, int size)
{
	char* clear_string = (char*)calloc(size + 1, sizeof(char));

	int j = 0;
	for (int i = 0; i < size; ++i)
		if (isalpha(string[i])) clear_string[j++] = string[i];

	clear_string[size] = '\0';

	return clear_string;
}

int comparator_slow_and_bad_but_beautiful(const void* value_a, const void* value_b)
{
	const Line* line_a = (const Line*)value_a;
	const Line* line_b = (const Line*)value_b;
	
	char* string_a = Erase_punct_marks(line_a->string, line_a->size);
	char* string_b = Erase_punct_marks(line_b->string, line_b->size);
	
	const int result = strcmp(string_a, string_b);

	free(string_a);
	free(string_b);

	return  result;
	

}

int comparator_back(const void* value_a, const void* value_b)
{


	const Line* line_a = (const Line*)value_a;
	const Line* line_b = (const Line*)value_b;

	const char* string_a = line_a->string;
	const char* string_b = line_b->string;

	int cur_a = line_a->size - 1 > 0 ? line_a->size - 1 : 0;
	int cur_b = line_b->size - 1 > 0 ? line_b->size - 1 : 0;

	int a_is_ready = 0, b_is_ready = 0;

	while (cur_a && cur_b)
	{
		if (!a_is_ready && isalpha(string_a[cur_a]))
			a_is_ready = 1;
		else if (!a_is_ready)
			--cur_a;

		if (!b_is_ready && isalpha(string_b[cur_b]))
			b_is_ready = 1;
		else if (!b_is_ready)
			--cur_b;

		if (a_is_ready && b_is_ready)
		{
			if (tolower(string_a[cur_a]) != tolower(string_b[cur_b]))
			{
				return string_a[cur_a] - string_b[cur_b];

			}

			--cur_a;
			--cur_b;

			a_is_ready = 0;
			b_is_ready = 0;
		}
	}

	return tolower(string_a[cur_a]) - tolower(string_b[cur_b]);
}

int comparator_normal(const void* value_a, const void* value_b)
{
	
	const Line* line_a = (const Line*)value_a;
	const Line* line_b = (const Line*)value_b;

	const char* string_a = line_a->string;
	const char* string_b = line_b->string;

	//printf("\nCompare: %s \nand\n%s", string_a, string_b);

	int cur_a = 0;
	int cur_b = 0;
	
	int a_is_ready = 0,
		b_is_ready = 0;

	while (string_a[cur_a] && string_b[cur_b])
	{
		if (!a_is_ready && isalpha(string_a[cur_a]))
			a_is_ready = 1;
		else if (!a_is_ready)
			++cur_a;
		
		if (!b_is_ready && isalpha(string_b[cur_b]))
			b_is_ready = 1;
		else if (!b_is_ready)
			++cur_b;

		if (a_is_ready && b_is_ready)
		{
			if (tolower(string_a[cur_a]) != tolower(string_b[cur_b]))
				return string_a[cur_a] - string_b[cur_b];
			
			++cur_a;
			++cur_b;
			
			a_is_ready = 0;
			b_is_ready = 0;
		}
	}

	return tolower(string_a[cur_a]) - tolower(string_b[cur_b]);
}

int Get_length(const Line* lines, const int number_of_lines)
{
	int length = 0;
	for (int i = 0; i < number_of_lines; ++i)
		length += lines[i].size;

	length += number_of_lines; //Нужно учесть символы перехода на новую строку

	return length;
}

int __Approx_Length__(const char* file_name)
{
	struct stat buff;

	stat(file_name, &buff);

	return buff.st_size;
	
}

void Swap(void* a, void* b, const int size)
{

	char What_have_I_become_My_sweetest_friend_Everyone_I_know_Goes_away_in_the_end = 0;

	for (int cur = 0; cur < size; ++cur)
	{
		What_have_I_become_My_sweetest_friend_Everyone_I_know_Goes_away_in_the_end = *((char*)a + cur);
		*((char*)a + cur) = *((char*)b + cur);
		*((char*)b + cur) = What_have_I_become_My_sweetest_friend_Everyone_I_know_Goes_away_in_the_end;
	}
}

void Print_lines(Line* lines, int number_of_lines, char* reason)
{
	printf("\n");
	printf("%s\n", reason);
	for (int i = 0; i < number_of_lines; ++i)
	{
		printf("SIZE - %d: ", lines[i].size);

		for (int j = 0; j < lines[i].size; ++j)
			printf("%c", lines[i].string[j]);
		printf("\n");
	}

}

void Write_lines(char* file_name, Line* lines, int number_of_lines, char* type, char* reason)
{
	FILE* file = fopen(file_name, type);

	if (!strcmp(type, "a"))
		fputs("---------------------\n", file);

	fputs("Reason: \n", file);
	fputs(reason, file);
	fputs("\n---------------------\n", file);

	for (int i = 0; i < number_of_lines; ++i)
	{
		fputs(lines[i].string, file);
		fputc('\n', file);
	}

	fclose(file);
}

void Delete_lines(Line* lines, char* buffer)
{
	free(buffer);
	free(lines);
}

void QQsort(void* data, const int length, const int size, int (*comparator)(const void* value_a, const void* value_b))
{
	if (length > 2)
	{
		int cur_small = 0,
			cur_big = length - 1;

		char* pivot = (char*)malloc(size);
		for (int i = 0; i < size; ++i) {
			*(pivot + i) = *((char*)data + (length) / 2 * size + i);
		}

		//printf("\nPivot: %s\n", ((Line*)pivot)->string);


		while (cur_small <= cur_big)
		{
			while (comparator((void*)((char*)data + size * cur_small), pivot) < 0)
				++cur_small;
			while (comparator((void*)((char*)data + size * cur_big), pivot) > 0)
				--cur_big;

			if (cur_small >= cur_big)
			{
				break;
			}

			Swap((void*)((char*)data + size * cur_small), (void*)((char*)data + size * cur_big), size);
			++cur_small;
			--cur_big;
		}


		QQsort(data, cur_big + 1, size, comparator);
		QQsort((void*)((char*)data + (cur_big + 1) * size), length - cur_big - 1, size, comparator);
	}
	//Если меньше 2 элементов то сортировать там нечего
	else if (length == 2)
	{
		if ((comparator((void*)((char*)data + size * 0), (void*)((char*)data + size * 1)) > 0))
		{
			Swap((void*)((char*)data + size * 0), (void*)((char*)data + size * 1), size);
		}
	}
}

void Insertion_sort(void* data, const int length, const int size, int (*comparator)(const void* value_a, const void* value_b))
{
	for (int i = 1; i < length; ++i)
	{
		int j = i;

		while (j > 0 && (comparator((void*)((char*)data + size * (j - 1)), (void*)((char*)data + size * j))) > 0)
		{
			Swap((void*)((char*)data + size * (j - 1)), (void*)((char*)data + size * j), size);
			j--;
		}
	}
}



int compare(const void* a, const void* b) { return *(const int*)a - *(const int*)b; }
void Unit_tests()
{
	//COMPARATORS
	char* test_cmp_normal_1 = "ABC";
	char* test_cmp_normal_2 = "abc";
	char* test_cmp_normal_3 = "abac";
	char* test_cmp_normal_4 = "acab";
	Line* line_1 = calloc(1, sizeof(Line));
	line_1->size = 3;
	line_1->string = test_cmp_normal_1;
	Line* line_2 = calloc(1, sizeof(Line));
	line_2->size = 3;
	line_2->string = test_cmp_normal_2;
	Line* line_3 = calloc(1, sizeof(Line));
	line_3->size = 4;
	line_3->string = test_cmp_normal_3;
	Line* line_4 = calloc(1, sizeof(Line));
	line_4->size = 4;
	line_4->string = test_cmp_normal_4;



	if (comparator_normal((void*)line_1, (void*)line_2) != 0)
		printf("TEST#1 FAILED!\n STRING NORMAL COMPARE:\n%s\n%s\n", test_cmp_normal_1, test_cmp_normal_2);
	if (comparator_normal((void*)line_3, (void*)line_4) > 0)
		printf("TEST#2 FAILED!\n STRING NORMAL COMPARE:\n%s\n%s\n", test_cmp_normal_3, test_cmp_normal_4);

	if (comparator_back((void*)line_1, (void*)line_2) != 0)
		printf("TEST#3 FAILED!\n STRING NORMAL COMPARE:\n%s\n%s\n", test_cmp_normal_1, test_cmp_normal_2);
	if (comparator_back((void*)line_3, (void*)line_4) < 0)
		printf("TEST#4 FAILED!\n STRING NORMAL COMPARE:\n%s\n%s\n", test_cmp_normal_3, test_cmp_normal_4);

	//SORTS
	int* test_sort_1 = (int*)calloc(3, sizeof(int));
	int* test_sort_2 = (int*)calloc(5, sizeof(int));

	test_sort_1[0] = 3; test_sort_1[1] = 1; test_sort_1[2] = 2;
	for (int i = 0; i < 5; ++i)
		test_sort_2[i % 5] = (5 - i); 

	QQsort((void*)test_sort_1, 3, sizeof(int), compare);
	QQsort((void*)test_sort_2, 5, sizeof(int), compare);

	for (int i = 0; i < 5; ++i)
	{
		if (test_sort_1[i] != i + 1)
			if (i < 3)
				printf("TEST#5 FAILED!\n ARRAY SORT:\nARR[%d] = %d\nARR[%d] = %d\n", i, test_sort_1[i], i, i + 1);
		if (test_sort_2[i] != i + 1)
			printf("TEST#6 FAILED!\n ARRAY SORT:\nARR[%d] = %d\nARR[%d] = %d\n", i, test_sort_2[i], i, i+1);
	}

	//I WANNA SWAP SWAP SWAP, MA MUMMY
	int test_swap_1 = 3;
	int test_swap_2 = 4;
	Swap((void*)&test_swap_1, (void*)&test_swap_2, sizeof(int));
	if (test_swap_1 != 4 && test_swap_2 != 3)
		printf("TEST#7 FAILED!\n SWAP:\nA = %d; A_TRUE = 4; \nB = %d; B_TRUE =  3\n", test_swap_1, test_swap_2);
	
	//Read
	int true_length = 142;
	int true_number_of_lines = 7;
	int true_sizes[7] = {11, 12, 18, 7, 19, 48, 20};
	char* true_buffer = "Hello World\nHow are you?\nI am fine, and You\nI am Ok\nUhh, what happened?\nI cant stand writing unit tests, It is so boring\nUh, I underSTAND you";

	Line* test_lines = NULL;
	char* test_buffer = NULL;
	int test_number_of_lines = 0;

	test_lines = Read_lines_fast("test.txt", &test_number_of_lines, &test_buffer);
	int test_length = Get_length(test_lines, test_number_of_lines);
	if (test_length != true_length)
		printf("TEST#8 FAILED! LENGTH = %d\nTRUE LENGTH = %d\n", test_length, true_length);
	
	if (test_number_of_lines != true_number_of_lines)
		printf("TEST#9 FAILED! TEST NUMBER OF LINES = %d\nTRUE NUMBER OF LINES = %d\n", test_number_of_lines, true_number_of_lines);
	for (int i = 0; i < true_number_of_lines; ++i)
	{
		if (test_lines[i].size != true_sizes[i])
			printf("TEST#10 FAILED! TEST_LINES[%d].SIZE = %d\nTRUE_SIZES[%d] = %d\n", i, test_lines[i].size , i, true_sizes[i]);
	}

	//write
	Write_lines("test_out.txt", test_lines, test_number_of_lines, "w", "TEST");
	int test_written_lines = 0;
	char* test_written_buffer = NULL;
	Line* test_write = Read_lines_fast("test_out.txt", &test_written_lines, &test_written_buffer);
	
}
