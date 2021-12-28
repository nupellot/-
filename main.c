#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[50];
	char classLetter[3];
	int firstGrade;
	int secondGrade;
	int thirdGrade;
} student ;

int main(void) {
  FILE* source = fopen("realSource", "r+");
	if (source == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	printf("Файл успешно открыт\n");


	char c = fgetc(source);
	int amountOfStudents = 0;
	do {
		c = fgetc(source);
		if (c == '\n') amountOfStudents++;
	} while (c != EOF && c != '#');
	fseek(source, 0, 0);

	student* allStudents;
	allStudents = (student*)malloc(sizeof(student) * amountOfStudents);

	// for (int i = 1; c != EOF && c != '#'; i++) {
	// 		printf("Зашли в цикл\n");
	// 	allStudents = realloc(allStudents, i);
	// 		printf("Перевыделили память\n");
	// 	fscanf(source, "%s %c %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, allStudents[i].firstGrade, allStudents[i].secondGrade, allStudents[i].thirdGrade);
	// 		printf("Записали чего-то там\n");
	// }
	
	// int amountfOfStudents = 0;
	for (int i = 0; i < amountOfStudents; i++) {
		fscanf(source, "%s %s %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, &allStudents[i].firstGrade, &allStudents[i].secondGrade, &allStudents[i].thirdGrade);

		// // fscanf(source, "%s ", allStudents[i].name);
		// printf("%s\n", allStudents[i].name);
		// // fscanf(source, "%c", &allStudents[i].classLetter);
		// printf("%s\n", allStudents[i].classLetter);
		// // fscanf(source, "%d", &allStudents[i].firstGrade);
		// printf("%d\n", allStudents[i].firstGrade);
		// // fscanf(source, "%d", &allStudents[i].secondGrade);
		// printf("%d\n", allStudents[i].secondGrade);
		// // fscanf(source, "%d\n", &allStudents[i].thirdGrade);
		// printf("%d\n", allStudents[i].thirdGrade);

		
		
		// printf("Зашли в цикл\n");
		// allStudents = (student*)realloc(allStudents, sizeof(student) * (i + 2));
		// printf("Перевыделили память\n");
		// fscanf(source, "%s %c %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, allStudents[i].firstGrade, allStudents[i].secondGrade, allStudents[i].thirdGrade);
		// printf("Записали чего-то там\n");

	}
	
	fclose(source);
	printf("В структуру записаны следующие студенты:\n");
	for (int i = 0; i < amountOfStudents; i++) {
		// printf("Дошли до вывода\n");
		printf("%s %s %d %d %d\n", allStudents[i].name, allStudents[i].classLetter, allStudents[i].firstGrade, allStudents[i].secondGrade, allStudents[i].thirdGrade);
	}
}