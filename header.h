#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys\stat.h>

enum ERROR
{
	NORMAL_SITUATION,

	INCORRECT_KEY,
	INCORRECT_INPUT,

	TEST_1_FAILED,
	TEST_2_FAILED,
	TEST_3_FAILED,
	TEST_4_FAILED,
	TEST_5_FAILED,
	TEST_6_FAILED,
	TEST_7_FAILED,
	TEST_8_FAILED,
	TEST_9_FAILED,
	TEST_10_FAILED,

	TEST_PASSED

};

/*!
string      строка
\n
size        размер строки
*/
typedef struct Line
{
	char* string;
	int	  size;

} Line;

/*!
Считывает данные файла
@param[in]   filename       название файла
@param[out]  length          количестов символов
@return указатель на структуры типа Line
*/
char* Read_contents(const char* filename, int* length);

/*!
Распределеяет данные по структрурам
@param[in]   filename       название файла
@param[out]  number_of_lines количество строк
@param[out]  buffer          буфер символов
@param[in]   length          количество символов
@return указатель на структуры типа Line
*/
Line* Parse_contents(const char* filename, int* number_of_lines, char** buffer, int length);

/*!
Считывает данные файла, распределяя их по структурам 
@param[in]   file_name       название файла
@param[out]  number_of_lines количество строк
@param[out]  buffer          буфер символов
@return указатель на структуры типа Line
*/
Line* Read_lines_fast(const char* filename, int* amount_of_lines, char** buffer);

/*!
Длина массива		
@param[in]   lines           указатель на структуру типа Line
@param[out]  number_of_lines количество строк
@return длина массива
*/
int Get_length(const Line* lines, const int number_of_lines);

int Comparator_back(const void* value_a, const void* value_b);

int Comparator_normal (const void* value_a, const void* value_b);

int Comparator_ugly_but_universal(char* string_a, const int size_a, char* string_b, const int size_b, const int from_start_or_end);

int Comparator_normal_but_I_dont_like_it(const void* value_a, const void* value_b);

int Comparator_back_but_I_dont_like_it(const void* value_a, const void* value_b);

int __Approx_Length__(const char* file_name);



/*!
Создает новую строку, содержащую только буквы, и перезаписывает туда поданную на вход строку
@param[in] string           строка
@param[in] size				количество символов
@returns строку, содержащую только буквы
*/
char* Erase_punct_marks(char* string, int size);

/*!
Копирует данные из структуры Line и возвращает указатель на структуру типа Line
@param[in]      lines           указатель на структуру типа Line
@param[in]     number_of_lines количество строк
@param[out]     buffer          буфер символов
@param[out]  copy_buffer     буфер, в который копируются строки
@return указатель на структуры типа Line
*/
Line* Copy_lines(Line* lines, int number_of_lines, char** buffer);

/*!
Печатает данные файла
@param[in] lines           указатель на структуры типа Line
@param[in] number_of_lines количество строк
@param[in] reason          причина вызова функции
*/
void Print_lines(Line* lines, int number_of_lines, const char* reason);

/*!
 Выводит данные в файл
@param[in] file_name	   название файла
@param[in] lines           указатель на структуры типа Line
@param[in] number_of_lines количество строк
@param[in] type            модификтор доступа к файлу
@param[in] reason		   причина вызова функции
 */
void Write_lines(char* file_name, Line* lines, int number_of_lines, const char* type, const char* reason);

/*!
 Удаляет данные из памяти
@param[in] lines           указатель на структуры типа Line
@param[in] buffer		   указатель на строки
 */
void Delete_lines(Line* lines);

/*!
Стирает знаки препинания строки
@param[in] lines           указатель на структуры типа Line
@param[in] number_of_lines количество строк
*/
void Erase_end_punctuation_marks(Line* lines, int number_of_lines);

/*!
БЫСТРО СОРТИРУЕТ МАССССИВ ДАНННННЫХ
@param[in]  data            указатель на ДАНННЫЕ
@param[in]  length			количество элементов
@param[in]  size			размер каждого элемента ДАНННЫЫЫХ
@param[in]  comparator		KОМПАРРРАТОРРР!
@return НИЧЕРТА ОН НЕ ВОЗВРАЩАЕТ 
*/
void QQsort(void* data, const int length, const int size, int (*comparator)(const void* value_a, const void* value_b));

/*!
СВОП СВОП СВОП ДЛЯ ЛЮБОГО ТИПА СВОП СВОП СВОП
@param[in]  a	 элемент а
@param[in]  b	 элемент b
@param[in]  size размер элементаи
*/
void Swap(void* a, void* b, const int size);

/*!
НЕБЫСТРО СОРТИРУЕТ МАССССИВ ДАННННННЫХ
@param[in]  data            указатель на ДАНННЫЕ
@param[in]  length			количество элементов
@param[in]  size			размер каждого элемента ДАНННЫЫЫХ
@param[in]  comparator      КОМПАРРРАТОРРР!
@return НИЧЕРТА ОН НЕ ВОЗВРАЩАЕТ
*/
void Insertion_sort(void* data, const int length, const int size, int (*comparator)(const void* value_a, const void* value_b));

int Unit_tests();

