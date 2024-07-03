#include<stdio.h>
#include<stdlib.h>
#include"read.h"
#include"user.h"
#include"list.h"
#include"main.h"


void write_single(struct user* user) {
	FILE* file = fopen(userdatapath, "a");
	sprintf(buffer, "%s %s %d %s %d %s %s %lf %d %lf\n", user->card, user->password, user->isfreeze, user->name, user->age, user->phone, user->identity, user->money, user->count, user->loan);
	fputs(buffer, file);
	fclose(file);
}

void write_all() {
	FILE* file = fopen(userdatapath, "w");
	fputs("", file);
	fclose(file);
	struct list* p = getlisthead()->next;
	while (p != NULL) {
		write_single(p->user);
		p = p->next;
	}
}

void write_record(char* s) {
	FILE* file = fopen(traderecordpath, "a");
	sprintf(buffer, "%s  %s\n", gettime(), s);
	fputs(buffer, file);
	fclose(file);
}