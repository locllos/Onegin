#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line
{
	char* string;
	int size;
} Line;


/*!
��������� ������ �����
\param[in]   file_name       �������� �����
\param[out]  number_of_lines ���������� �����
\return ��������� �� ��������� ���� Line
*/

Line* Read_lines(char* file_name, int* number_of_lines);

int comparator(const void* value_1, const void* value_2);

/*!
������ ������
\param[in] lines           ��������� �� ��������� ���� Line
\param[in] number_of_lines ���������� �����
\returns ��������� �� ��������� ���� Line
*/

Line* Reverse_lines(Line* old_lines, int number_of_lines);

/*!
�������� ������ �����
\param[in] lines           ��������� �� ��������� ���� Line
\param[in] number_of_lines ���������� �����
\param[in] reason          ������� ������ �������
*/

void Print_lines(Line* lines, int number_of_lines, char* reason);

/*!
 ������� ������ � ����
\param[in] file_name	   �������� �����
\param[in] lines           ��������� �� ��������� ���� Line
\param[in] number_of_lines ���������� �����
\param[in] type            ���������� ������� � �����
\param[in] reason		   ������� ������ �������
 */

void Write_lines(char* file_name, Line* lines, int number_of_lines, char* type, char* reason);

/*!
������� ����� ���������� � ����� ������
\param[in] lines           ��������� �� ��������� ���� Line
\param[in] number_of_lines ���������� �����
*/

void Erase_end_punctuation_marks(Line* lines, int number_of_lines);

/*!
������� ������ �� lines
\param[in] lines           �������� �� ��������� ���� Line
\param[in] number_of_lines ���������� �����
*/

void Delete_lines(Line* lines, int number_of_lines);
