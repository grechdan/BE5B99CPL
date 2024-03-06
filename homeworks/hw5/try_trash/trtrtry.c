#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	char filename[20];
	unsigned char buffer[100];
	char line[100];
  int salary;
  int year, month, day;

	FILE* file = fopen("094.dat","r");

	
	while (fgets(line, sizeof(line), file) != NULL) {

	  // Check if the line starts with "Salary: "
	  if (strncmp(line, "Salary: ", 8) == 0) {
	      // Extract the salary amount
	      sscanf(line, "Salary: %d", &salary);
	  }
	  // Check if the line starts with "Date of birth: "
	  if (strncmp(line, "Date of birth: ", 8) == 0) {
	      // Extract the date of birth
	      sscanf(line, "Date of birth: %d-%d-%d", &year, &month, &day);
	  }
	
	}

    // Close the file
    fclose(file);

    printf("Salary: %d\n", salary);
    printf("Date of birth: %d-%d-%d\n", year, month, day);

    return 0;

}