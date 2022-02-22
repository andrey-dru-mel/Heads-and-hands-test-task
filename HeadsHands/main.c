#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>	//scanf, sscanf, printf, puts
#include <stdlib.h>	//calloc, free, rand, srand
#include <time.h>	//time (��� ������� ���� ������������)

typedef struct elem_s {
	int len;	//����� �������
	int* arr;	//������
}elem;

typedef unsigned char flag;

//----------��������������� ������� ��� ������������� qsort--------------

//�� �����������
int downUpSort(int* a, int* b) {
	return (*a > *b ? 1 : (*a == *b ? 0 : -1));
}

//�� ��������
int upDownSort(int* a, int* b) {
	return (*a > *b ? -1 : (*a == *b ? 0 : 1));
}

//------------------------------------------------------------------------

int** reqFoo(unsigned n) {

	srand(time(0));	//���, ��������� �� �������� �������

	elem* arrs = calloc(n, sizeof(elem));
	if (!arrs) return NULL;

	for (int i = 0; i < n; i++) {
		arrs[i].len = rand() % 100;

		//�������� ����� �������, ���� ����� ����� ���� � ������ �� ����������
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

		arrs[i].arr = calloc(arrs[i].len, sizeof(int));	//��������� ������ ��� ������ �� ��������� ������

		//���������� �������� ���������� ����������
		for (int j = 0; j < arrs[i].len; j++) {
			arrs[i].arr[j] = rand();
		}

	}

	//���������� ����� = ������ + 1

	//��������
	for (int i = 0; i < n; i += 2) {
		qsort(arrs[i].arr, arrs[i].len, sizeof(int), upDownSort);	//���������� �� ��������
	}

	//׸����
	for (int i = 1; i < n; i += 2) {
		qsort(arrs[i].arr, arrs[i].len, sizeof(int), downUpSort);	//���������� �� �����������
	}

	return arrs;

}

int main(void) {

	unsigned n;
	char buff[15];
	scanf("%s", buff);

	//��������� ������������� �����
	if (sscanf(buff, "%u", &n) != 1) {
		puts("Incorrect input. Program failed.");
		return -1;
	}
	
	elem* arrs = reqFoo(n);
	if (!arrs) {
		puts("Too big or negative number. Program failed.");
		return -2;
	}

	//����� ��������
	for (int i = 0; i < n; i++) {

		printf("Array %d:\nLen = %d\nAi = ", i + 1, arrs[i].len);

		for (int j = 0; j < arrs[i].len - 1; j++) printf("%d, ", arrs[i].arr[j]);

		printf("%d.\n\n", arrs[i].arr[arrs[i].len - 1]);

	}

	//����������� ������ � ����
	for (int i = 0; i < n; i++) free(arrs[i].arr);
	free(arrs);

	return 0;
}