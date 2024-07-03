#include<string.h>
struct list {
	struct user* user;
	struct list* next;
}; //用来存储用户
static struct list* users;
static struct list* tail;

void add(struct user* user);

void removeuser(struct user* user);

void initial();

struct user* find(char* card);

struct list* getlisthead();