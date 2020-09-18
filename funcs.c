#include "header.h"

Line* Read_lines_slow_and_old(char* file_name, int* number_of_lines)
{
	FILE* file = fopen(file_name, "r");
	Line* lines = (Line*)malloc(sizeof(Line));
	lines[0].string = NULL;
	lines[0].size = 0;

	int i = 0;
	char tmp = fgetc(file);
	while (tmp != EOF)
	{
		lines[i].string = (char*)realloc(lines[i].string, (lines[i].size + 1) * sizeof(char));

		lines[i].string[lines[i].size] = (tmp == '\n') ? '\0' : tmp;


		if (tmp == '\n')
		{
			lines = (Line*)realloc(lines, (i + 2) * sizeof(Line)); // i + 2, because i begins from zero

			i++;

			lines[i].string = NULL;
			lines[i].size = 0;

		}
		else lines[i].size++;

		tmp = fgetc(file);
	}

	fclose(file);

	(*number_of_lines) = i + 1;


	//Если предпоследняя строка содержала только символ slash n
	if (lines[*number_of_lines - 1].string == NULL)
	{
		--*number_of_lines;
	}


	//В случае, когда в последней строчке файла не был проставлен переход на следующую строку
	if (lines[*number_of_lines - 1].string[lines[*number_of_lines - 1].size] != '\0')
	{
		lines[*number_of_lines - 1].string = (char*)realloc(lines[*number_of_lines - 1].string, (lines[i].size + 1) * sizeof(char));
		lines[*number_of_lines - 1].string[lines[*number_of_lines - 1].size] = '\0';
	}

	return lines;
}

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

char* Erase_punct_marks(char* string, int size)
{
	char* clear_string = (char*)calloc(size + 1, sizeof(char));

	int j = 0;
	for (int i = 0; i < size; ++i)
		if (isalpha(string[i])) clear_string[j++] = string[i];

	clear_string[size] = '\0';

	return clear_string;
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
