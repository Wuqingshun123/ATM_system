#include<string.h>
struct list {
	struct user* user;
	struct list* next;
}; //�����洢�û�
static struct list* users;
static struct list* tail;

void add(struct user* user);

void removeuser(struct user* user);

void initial();

struct user* find(char* card);

struct list* getlisthead();