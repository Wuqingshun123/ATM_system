#include"read.h"
#include<stdio.h>
#include<stdlib.h>
#include"user.h"
#include"list.h"
#include<string.h>
#include"main.h"

void loadusers() {
	FILE* file = fopen(userdatapath, "r");
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		struct user* user = (struct user*)malloc(sizeof(struct user));
		sscanf(buffer, "%s %s %d %s %d %s %s %lf %d %lf\n", user->card, user->password, &user->isfreeze, user->name, &user->age, user->phone, user->identity, &user->money, &user->count, &user->loan);
		add(user);
	}
	fclose(file);
}

void printall_record() {
	FILE* file = fopen(traderecordpath, "r");
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		printf("%s\n", buffer);
	}
	fclose(file);
}

void printsingle_record(struct user* user) {
    FILE* f = fopen(traderecordpath, "r");
    printf("卡号:%s 户主 %s 交易记录如下\n", user->card, user->name);
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        char card[12] = { 0 };
        int i;
        for (i = 0; i < 11; i++) {
            card[i] = buffer[i + 28];
        }
        if (strcmp(user->card, card) == 0) {
            char time[22] = { 0 };
            for (i = 0; i < 21; i++) {
                time[i] = buffer[i];
            }
            int last = 0;
            for (i = 0; i < strlen(buffer); i++) {
                if (buffer[i] == ' ') last = i;
            }
            char message[1000] = { 0 };
            int j = 0;
            for (i = last + 1; i < strlen(buffer); i++) {
                message[j++] = buffer[i];
            }
            printf("%s %s", time, message);
        }
    }
    fclose(f);
    wait("输入任意键继续");
}