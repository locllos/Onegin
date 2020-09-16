#include "header.h"


Line* Read_lines(char* file_name, int* number_of_lines)
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

Line* Read_lines_fast(const char* filename, int* amount_of_lines)
{
	const int approx_length = __Approx_Length__(filename);

	FILE* file = fopen(filename, "r");
	Line* lines = (Line*)calloc(approx_length, sizeof(Line));
	char* buffer = (char*)calloc(approx_length + 1, sizeof(char));

	const unsigned int length = fread(buffer, sizeof(char), approx_length + 1, file);

	buffer[length] = '\0';

	int cur_size = 0,
		number_of_lines = 0;
	for (int i = 0; i < length; ++i)
	{
		if (buffer[i] != '\n')
			++cur_size;
		else
		{
			lines[number_of_lines++].size = cur_size;
			cur_size = 0;
		}
	}

	//На случай если в конце файла не было проставлено символов перехода на следующую строку
	if (buffer[length - 1] != '\n')
	{
		lines[number_of_lines].size = cur_size;
		++number_of_lines;
	}

	int cur_buf = 0;
	for (int i = 0; i < number_of_lines; ++i)
	{
		lines[i].string = (char*)calloc(lines[i].size + 1, sizeof(char));
		for (int j = 0; j < lines[i].size; ++j)
			lines[i].string[j] = buffer[cur_buf++];

		lines[i].string[lines[i].size] = '\0';
		++cur_buf; // Jump over slash n
	}

	fclose(file);
	
	(*amount_of_lines) = number_of_lines;
	return lines;
}

Line* Copy_lines(Line* lines, int number_of_lines)
{
	Line* copy_lines = (Line*)calloc(number_of_lines, sizeof(Line));

	for (int i = 0; i < number_of_lines; ++i)
	{
		copy_lines[i].size = lines[i].size;
		copy_lines[i].string = (char*)calloc(lines[i].size + 1, sizeof(char));
		
		for (int j = 0; j < lines[i].size + 1; ++j)
		{
			copy_lines[i].string[j] = lines[i].string[j];
		}
	}

	return copy_lines;
}

Line* Reverse_lines(Line* old_lines, int number_of_lines)
{
	Line* new_lines = (Line*)calloc(number_of_lines, sizeof(Line));

	printf("\n");

	for (int i = 0; i < number_of_lines; ++i)
	{

		new_lines[i].string = (char*)calloc(old_lines[i].size, sizeof(char*));
		new_lines[i].size = old_lines[i].size;

		for (int j = 0; j < new_lines[i].size; ++j)
		{
			int current_size = old_lines[i].size;

			new_lines[i].string[j] = old_lines[i].string[current_size - j - 1];
		}

		//new_lines[i].string[new_lines[i].size] = '\0';
	}

	return new_lines;
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

	int cur_a = 0;
	int cur_b = 0;
	
	int a_is_ready = 0, b_is_ready = 0;

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
			{
				return string_a[cur_a] - string_b[cur_b];

			}
			
			++cur_a;
			++cur_b;
			
			a_is_ready = 0;
			b_is_ready = 0;
		}
	}

	return tolower(string_a[cur_a]) - tolower(string_b[cur_b]);
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

void Print_lines(Line* lines, int number_of_lines, char* reason)
{
	printf("\n");
	printf("%s\n", reason);
	for (int i = 0; i < number_of_lines; ++i)
	{
		printf("%d: ", lines[i].size);

		for (int j = 0; j < lines[i].size; ++j)
			printf("%c", lines[i].string[j]);
		printf("\n");
	}

}

void Write_lines(char* file_name, Line* lines, int number_of_lines, char* type, char* reason)
{
	FILE* file = fopen(file_name, type);

	if (!strcmp(type, "a"))
		fputc('\n', file);


	fputs("Reason: \n", file);
	fputs(reason, file);
	fputc('\n', file);

	for (int i = 0; i < number_of_lines; ++i)
	{
		for (int j = 0; j < lines[i].size; ++j)
			fputc(lines[i].string[j], file);
		fputc('\n', file);
	}

	fclose(file);
}

void Delete_lines(Line* lines, int number_of_lines)
{
	for (int i = 0; i < number_of_lines; ++i)
	{
		free(lines[i].string);
		lines[i].size = 0;
	}

	free(lines);
}
