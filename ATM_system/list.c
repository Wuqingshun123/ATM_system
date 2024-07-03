#include<stdio.h>
#include"list.h"
#include<stdlib.h>
#include"user.h"

void add(struct user* user) {
	struct list* li = (struct list*)malloc(sizeof(struct list));
	li->user = user;
	tail->next = li;
	tail = li;
	tail->next = NULL;
}

void removeuser(struct user* user) {
	struct list* p = getlisthead();
	while (p->next != NULL) {
		if (p->next->user = user) {
			struct list* m = p->next;
			p->next = p->next->next;
			free(m);
			return;
		}
	}
}

void initial() {
	struct list* p = (struct list*)malloc(sizeof(struct list));
	users = p;
	tail = p;
	users->next = NULL;
}

struct user* find(char* card) {
	struct list* p = users->next;
	while (p != NULL) {
		if (strcmp(card, p->user->card) == 0) return p->user;
		p = p->next;
	}
	return NULL;
}

struct list* getlisthead() {
	return users;
}