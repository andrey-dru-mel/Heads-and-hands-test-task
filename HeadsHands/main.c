#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>	//scanf, sscanf, printf, puts
#include <stdlib.h>	//calloc, free, rand, srand
#include <time.h>	//time (для задания сида рандомайзера)

typedef struct elem_s {
	int len;	//Длина массива
	int* arr;	//Массив
}elem;

typedef unsigned char flag;

//----------Вспомогательные функции для использования qsort--------------

//По возрастанию
int downUpSort(int* a, int* b) {
	return (*a > *b ? 1 : (*a == *b ? 0 : -1));
}

//По убыванию
int upDownSort(int* a, int* b) {
	return (*a > *b ? -1 : (*a == *b ? 0 : 1));
}

//------------------------------------------------------------------------

int** reqFoo(unsigned n) {

	srand(time(0));	//сид, зависимый от текущего времени

	elem* arrs = calloc(n, sizeof(elem));
	if (!arrs) return NULL;

	for (int i = 0; i < n; i++) {
		arrs[i].len = rand() % 100;

		//Изменяет длину массива, если такая длина была у одного из предыдущих
		flag isEq = 1;
		while (isEq) {
			isEq = 0;
			for (int j = 0; j < i; j++) {
				if (arrs[j].len == arrs[i].len) {
					isEq = 1;
					arrs[i].len++;
					break;
				}
			}
		}

		arrs[i].arr = calloc(arrs[i].len, sizeof(int));	//Выделение памяти под массив со случайной длиной

		//Заполнение массивов случайными значениями
		for (int j = 0; j < arrs[i].len; j++) {
			arrs[i].arr[j] = rand();
		}

	}

	//Порядковый номер = индекс + 1

	//Нечётные
	for (int i = 0; i < n; i += 2) {
		qsort(arrs[i].arr, arrs[i].len, sizeof(int), upDownSort);	//Сортировка по убыванию
	}

	//Чётные
	for (int i = 1; i < n; i += 2) {
		qsort(arrs[i].arr, arrs[i].len, sizeof(int), downUpSort);	//Сортировка по возрастанию
	}

	return arrs;

}

int main(void) {

	unsigned n;
	char buff[15];
	scanf("%s", buff);

	//Обработка некорректного ввода
	if (sscanf(buff, "%u", &n) != 1) {
		puts("Incorrect input. Program failed.");
		return -1;
	}
	
	elem* arrs = reqFoo(n);
	if (!arrs) {
		puts("Too big or negative number. Program failed.");
		return -2;
	}

	//Вывод массивов
	for (int i = 0; i < n; i++) {

		printf("Array %d:\nLen = %d\nAi = ", i + 1, arrs[i].len);

		for (int j = 0; j < arrs[i].len - 1; j++) printf("%d, ", arrs[i].arr[j]);

		printf("%d.\n\n", arrs[i].arr[arrs[i].len - 1]);

	}

	//Освобождаем память в куче
	for (int i = 0; i < n; i++) free(arrs[i].arr);
	free(arrs);

	return 0;
}