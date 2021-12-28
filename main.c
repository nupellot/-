#include <stdio.h>
#include <stdlib.h>

typedef struct {  // Структура студента.
	char name[50];
	char classLetter[3];
	int firstGrade;
	int secondGrade;
	int thirdGrade;
	int fourthGrade;
} student;


int main(void) {
	// Открываем исходный файл
  FILE* source = fopen("source", "r+");
	if (source == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	printf("Файл успешно открыт\n");

	// Объявляем функцию для дальнейшего использования.
	int getAmountOfFails(student*);

	char c = fgetc(source);
	// Считаем количество строк.
	int amountOfStudents = 0;
	do {
		c = fgetc(source);
		if (c == '\n') amountOfStudents++;
	} while (c != EOF && c != '#');
	fseek(source, 0, 0);

	// Выделяем память под массив студентов.
	student* allStudents;
	allStudents = (student*)malloc(sizeof(student) * amountOfStudents);

	// Считываем из файла всю необходимую информацию.
	for (int i = 0; i < amountOfStudents; i++) {
		fscanf(source, "%s %s %d %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, &allStudents[i].firstGrade, &allStudents[i].secondGrade, &allStudents[i].thirdGrade, &allStudents[i].fourthGrade);
	}
	fclose(source);
	
	// Печатаем информацию о студентах.
	printf("В структуру записаны следующие студенты:\n");
	for (int i = 0; i < amountOfStudents; i++) {
		printf("%s %s %d %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, allStudents[i].firstGrade, allStudents[i].secondGrade, allStudents[i].thirdGrade, allStudents[i].fourthGrade);
	}

	// Открываем файлы.
	FILE* zero = fopen("source", "w");
	FILE* one = fopen("1", "w");
	FILE* two = fopen("2", "w");
	FILE* threeOrMore = fopen("3 or more", "w");
	if (one == NULL || two == NULL || threeOrMore == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	printf("Файл успешно открыт\n");

	// Распределяем студентов по файлам.
	for (int i = 0; i < amountOfStudents; i++) {
		FILE* target;
		// Определяем, в какой из файлов нужно записать студента.
		switch (getAmountOfFails(&allStudents[i])) {
			case 0: {
				target = zero;
				break;
			}
			case 1: {
				target = one;
				break;
			}
			case 2: {
				target = two;
				break;
			}
			default: {
				target = threeOrMore;
				break;
			}
		}
		printf("%d\n", getAmountOfFails(&allStudents[i]));
		fprintf(target, "%s %s %d %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, allStudents[i].firstGrade, allStudents[i].secondGrade, allStudents[i].thirdGrade, allStudents[i].fourthGrade);
	}

	// Закрываем файлы.
	fclose(zero);
	fclose(one);
	fclose(two);
	fclose(threeOrMore);
	// Очищаем выделенную память.
	free(allStudents);
}

// Функция получения количества долгов студента.
int getAmountOfFails(student* student) {
	int amountOfFails = 0;
	if (student->firstGrade <= 2) amountOfFails++;
	if (student->secondGrade <= 2) amountOfFails++;
	if (student->thirdGrade <= 2) amountOfFails++;
	return amountOfFails;
}