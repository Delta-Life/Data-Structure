#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student{
	char name[31];
	int student_id;
	char major[31];
}student;

int main(int argc, char** args){

	char *input_path, *output_path;
	FILE *fi, *fo;
	int num;
	int i;
	student* students;

	input_path= args[1];
	output_path= args[2];
	
	fi = fopen(input_path, "r");
	fo= fopen(output_path, "w");

	fscanf(fi, "%d", &num);
	fgetc(fi);

	students = (student*)malloc(sizeof(student) * num);

	for(i = 0; i < num; i++){
		fscanf(fi, "%s %d %s", students[i].name, &students[i].student_id, students[i].major);
		fgetc(fi);
		fprintf(fo, "%s\t%d\t%s\n", students[i].name, students[i].student_id, students[i].major);
	}

	free(students);

	return 0;
}
