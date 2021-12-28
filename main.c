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
  FILE* source = fopen("source", "r");
	if (source == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	// Выводим содержимое исходного файла.
	printf("\033[45m%s\033[0m\n", "Содержимое исходного файла до обработки:");
	char c;
	while ((c = fgetc(source)) != EOF && c != '#') printf("%c", c);
	fseek(source, 0, 0); // Уходим обратно к началу файла.
	// printf("Файл успешно открыт\n");

	// Объявляем функцию для дальнейшего использования.
	int getAmountOfFails(student*);

	c = fgetc(source);
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
	// printf("В структуру записаны следующие студенты:\n");
	// for (int i = 0; i < amountOfStudents; i++) {
	// 	printf("%s %s %d %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, allStudents[i].firstGrade, allStudents[i].secondGrade, allStudents[i].thirdGrade, allStudents[i].fourthGrade);
	// }

	// Открываем файлы для записи в них данных.
	FILE* zero = fopen("source", "w");
	FILE* one = fopen("1", "w");
	FILE* two = fopen("2", "w");
	FILE* threeOrMore = fopen("3 or more", "w");
	if (one == NULL || two == NULL || threeOrMore == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	// printf("Файл успешно открыт\n");

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
		fprintf(target, "%s %s %d %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, allStudents[i].firstGrade, allStudents[i].secondGrade, allStudents[i].thirdGrade, allStudents[i].fourthGrade);
	}

	// Закрываем файлы.
	fclose(zero);
	fclose(one);
	fclose(two);
	fclose(threeOrMore);
	// Очищаем выделенную память.
	free(allStudents);

	// Открываем файлы заново, но уже для чтения, а не записи.
	zero = fopen("source", "r");
	one = fopen("1", "r");
	two = fopen("2", "r");
	threeOrMore = fopen("3 or more", "r");

	// Выводим информацию из всех файлов.
		printf("\033[42m%s\033[0m\n", "Содержимое исходного файла после обработки:");
	while ((c = fgetc(zero)) != EOF) printf("%c", c);
		printf("\033[46m%s\033[0m\n", "Содержимое файла \"1\":");
	while ((c = fgetc(one)) != EOF) printf("%c", c);
		printf("\033[43m%s\033[0m\n", "Содержимое файла \"2\":");
	while ((c = fgetc(two)) != EOF) printf("%c", c);
		printf("\033[41m%s\033[0m\n", "Содержимое файла \"3 or more\":");
	while ((c = fgetc(threeOrMore)) != EOF) printf("%c", c);
}

// Функция получения количества долгов студента.
int getAmountOfFails(student* student) {
	int amountOfFails = 0;
	if (student->firstGrade <= 2) amountOfFails++;
	if (student->secondGrade <= 2) amountOfFails++;
	if (student->thirdGrade <= 2) amountOfFails++;
	return amountOfFails;
}