#ifndef _STUDENT_H_
#define _STUDENT_H_

#include<stdio.h>
#include<string>
#include<stdlib.h>

using namespace std;

struct student {
	char std_name[50];
	char std_class[10];
	char std_dat[60];
	void (*import_std)(char[50], char[10], struct student*);

};

void import_std(char st_name[50], char st_class[10], struct student* st)
{
	strcpy(st->std_name, st_name);
	strcpy(st->std_class, st_class);  
	strcpy(st->std_dat, st_name);
	//strcpy(st->std_dat, st_class);
}

#endif