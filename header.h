#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Line
{
	char* string;
	int size;
} Line;


/*!
Считывает данные файла
\param[in]   file_name       название файла
\param[out]  number_of_lines количество строк
\return указатель на структуры типа Line
*/

Line* Read_lines(char* file_name, int* number_of_lines);

int comparator(const void* value_1, const void* value_2);

int comparator_back(const void* value_a, const void* value_b);

int comparator_normal (const void* value_a, const void* value_b);

/*!
Реверс строки
\param[in] lines           указатель на структуры типа Line
\param[in] number_of_lines количество строк
\returns указатель на структуры типа Line
*/

Line* Reverse_lines(Line* old_lines, int number_of_lines);

/*!
Создает новую строку, содержащую только буквы, и перезаписывает туда поданную на вход строку
\param[in] string           строка
\param[in] size				количество символов
\returns строку, содержащую только буквы
*/

char* Erase_punct_marks(char* string, int size);

/*!
Копирует и возвращает структуры типа Line
\param[in] Line*					указатели на структры типа Line*
\param[in] nubmer_of_lines			количество строк
\returns указатели на структуры типа Line
*/

Line* Copy_lines(Line* lines, int number_of_lines);

/*!
Печатает данные файла
\param[in] lines           указатель на структуры типа Line
\param[in] number_of_lines количество строк
\param[in] reason          причина вызова функции
*/

void Print_lines(Line* lines, int number_of_lines, char* reason);

/*!
 Выводит данные в файл
\param[in] file_name	   название файла
\param[in] lines           указатель на структуры типа Line
\param[in] number_of_lines количество строк
\param[in] type            модификтор доступа к файлу
\param[in] reason		   причина вызова функции
 */

void Write_lines(char* file_name, Line* lines, int number_of_lines, char* type, char* reason);

/*!
Стирает знаки препинания строки
\param[in] lines           указатель на структуры типа Line
\param[in] number_of_lines количество строк
*/

void Erase_end_punctuation_marks(Line* lines, int number_of_lines);

/*!
Удаляет данные из lines
\param[in] lines           казатель на структуры типа Line
\param[in] number_of_lines количество строк
*/

void Delete_lines(Line* lines, int number_of_lines);
