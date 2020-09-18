#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys\stat.h>

typedef struct Line
{
	char* string;
	int	  size;
} Line;


/*!
Считывает данные файла
\param[in]   file_name       название файла
\param[out]  number_of_lines количество строк
\param[out]  buffer          буфер символов
\return указатель на структуры типа Line
*/

Line* Read_lines_fast(const char* filename, int* amount_of_lines, char** buffer);

/*!
Длина массива		
\param[in]   lines           указатель на структуру типа Line
\param[out]  number_of_lines количество строк
\return длина массива
*/

int Get_length(const Line* lines, const int number_of_lines);

int comparator(const void* value_1, const void* value_2);

int comparator_back(const void* value_a, const void* value_b);

int comparator_normal (const void* value_a, const void* value_b);

int __Approx_Length__(const char* file_name);



/*!
Создает новую строку, содержащую только буквы, и перезаписывает туда поданную на вход строку
\param[in] string           строка
\param[in] size				количество символов
\returns строку, содержащую только буквы
*/

char* Erase_punct_marks(char* string, int size);

/*!
Копирует данные из структуры Line и возвращает указатель на структуру типа Line
\param[in]   lines           указатель на структуру типа Line
\param[out]  number_of_lines количество строк
\param[out]  buffer          буфер символов
\return указатель на структуры типа Line
*/

Line* Copy_lines(Line* lines, int number_of_lines, char** buffer, char** copy_buffer);

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
БЫСТРО СОРТИРУЕТ МАААААССССИВ ДАНННЫХ
\param[in]  data            указатель на ДАНННЫЕ
\param[in]  length			количество элементов
\param[in]  size			размер каждого элемента ДАНННЫЫЫХ
\param[in]  comparator		KОМПАРРРАТОРРР!
\return НИЧЕРТА ОН НЕ ВОЗВРАЩАЕТ 
*/

void QQsort(void* data, const int length, const int size, int (*comparator)(const void* value_a, const void* value_b));

/*!
СВОП СВОП СВОП ДЛЯ ЛЮБОГО ТИПА СВОП СВОП СВОП
\param[in]  a	элемент а
\param[in]  b	элемент b
\param[in] size размер элементаи
*/

void Swap(void* a, void* b, const int size);

/*!
НЕБЫСТРО СОРТИРУЕТ МАААААССССИВ ДАНННЫХ
\param[in]  data            указатель на ДАНННЫЕ
\param[in]  length			количество элементов
\param[in]  size			размер каждого элемента ДАНННЫЫЫХ
\param[in]  comparator      КОМПАРРРАТОРРР!
\return НИЧЕРТА ОН НЕ ВОЗВРАЩАЕТ
*/

void Insertion_sort(void* data, const int length, const int size, int (*comparator)(const void* value_a, const void* value_b));

void Unit_tests();

