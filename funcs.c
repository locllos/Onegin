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
		lines[i].size++;

		lines[i].string[lines[i].size - 1] = tmp;


		if (tmp == '\n')
		{
			lines = (Line*)realloc(lines, (i + 2) * sizeof(Line)); // i + 2, because i begins from zero

			i++;

			lines[i].string = NULL;
			lines[i].size = 0;

		}

		tmp = fgetc(file);
	}

	fclose(file);

	(*number_of_lines) = i + 1;


	//���� ������������� ������ ��������� ������ ������ ���������
	if (lines[*number_of_lines - 1].string == NULL)
	{
		--* number_of_lines;
	}


	//� ������, ����� � ��������� ������� ����� �� ���������� ������� �� ��������� ������, �� ������������� ������ ������ ��������
	if (lines[*number_of_lines - 1].string[lines[*number_of_lines - 1].size - 1] != '\n')
	{
		lines[*number_of_lines - 1].string = (char*)realloc(lines[*number_of_lines - 1].string, (lines[i].size + 1) * sizeof(char));
		lines[*number_of_lines - 1].size++;
		lines[*number_of_lines - 1].string[lines[*number_of_lines - 1].size - 1] = '\n';
	}

	return lines;
}

Line* Reverse_lines(Line* old_lines, int number_of_lines)
{
	Line* new_lines = (Line*)calloc(number_of_lines, sizeof(Line));

	printf("\n");

	for (int i = 0; i < number_of_lines; ++i)
	{

		new_lines[i].string = (char*)calloc(old_lines[i].size, sizeof(char*));
		new_lines[i].size = old_lines[i].size;

		for (int j = 0; j < new_lines[i].size - 1; ++j)
		{
			int current_size = old_lines[i].size;

			new_lines[i].string[j] = old_lines[i].string[current_size - j - 2];
		}

		new_lines[i].string[new_lines[i].size - 1] = '\n';
	}

	return new_lines;
}

int comparator(const void* value_1, const void* value_2)
{
	const Line* line_1 = (const Line*)value_1;
	const Line* line_2 = (const Line*)value_2;
	
	const char* string_1 = line_1->string;
	const char* string_2 = line_2->string;

	return strcmp(string_1, string_2);

}

void Print_lines(Line* lines, int number_of_lines, char* reason)
{
	printf("\n");
	printf("%s\n", reason);
	for (int i = 0; i < number_of_lines; ++i)
	{
		printf("%d. ", lines[i].size);

		for (int j = 0; j < lines[i].size; ++j)
			printf("%c", lines[i].string[j]);
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
	}

	fclose(file);
}

void Erase_end_punctuation_marks(Line* lines, int number_of_lines)
{
	const char punct_marks[7] = { '.', ',', ':' , ';', '-', '!', '?' };

	for (int i = 0; i < number_of_lines; ++i)
	{
		//���� ������ ��������, ���� ��� ������ �������� �� ��������� ������, � ��� �� ���� ����������
		if (lines[i].size > 1) {

			for (int j = 0; j < 7; ++j)
			{
				if (lines[i].string[lines[i].size - 2] == punct_marks[j]) // -2 �.�. ��������� ������ = slash n
				{
					lines[i].string = (char*)realloc(lines[i].string, lines[i].size - 1);
					--lines[i].size;
					lines[i].string[lines[i].size - 1] = '\n';
				}
			}
		}
	}
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