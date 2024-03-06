#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float salaryAverage = 0;  // Average salary, first output
int salaryTotal = 0;  
int histogram[12] = {0};
int agePerson = 40;  // Persons age, who will be "agePerson" years old this year(2022)
int dobPerson = 23;  // 
int mobPerson = 2;
int foundID = 0;


int main(int argc, char* argv[]){

	

	for(int i = 1; i <= 100; i++){

		char filename[20];
		char line[100];
		int salary;
		int year, month, day;

		sprintf(filename, "%03i.dat",i); 
			FILE* file = fopen(filename,"r");

			while (fgets(line, sizeof(line), file) != NULL) {

				if (strncmp(line, "Salary: ", 8) == 0) {
				
					sscanf(line, "Salary: %d", &salary);
				
				}

				if (strncmp(line, "Date of birth: ", 8) == 0) {
				
					sscanf(line, "Date of birth: %d-%d-%d", &year, &month, &day);
				
				}

			}

			fclose(file);

		salaryTotal = salaryTotal + salary;
		if(month == mobPerson && day == dobPerson && agePerson == 2022 - year)

			foundID = i;

		histogram[month - 1]++;

	}

	salaryAverage = salaryTotal / 100;
	printf("salaryAverage: %f\n", salaryAverage);
	for(int i = 0; i < 12; i++){

		printf("%i  ", histogram[i]);

	}
	printf("\n");
	printf("foundID: %i\n", foundID);

}