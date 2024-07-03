#include"admin.h"
#include"list.h"
#include"user.h"
#include<string.h>
#include"write.h"
#include<stdlib.h>
#include"stdio.h"
#include"main.h"
#include"read.h"

void print_all_users() {
    if (getlisthead()->next == NULL) printf("当前没有任何用户\n");
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        printf("卡号：%s 姓名：%s 年龄：%d 当前存款%.2lf元 当前欠款%.2lf元\n\n", p->user->card,p->user->name,  p->user->age, p->user->money, p->user->loan);
        p = p->next;
    }
    wait("输入任意键继续");
}

void print_single_user() {
    char card[100] = { 0 };
    printf("输入用户的卡号:");
    scanf("%s", card);
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(card, p->user->card) == 0) {
            printf("卡号：%s 姓名：%s 年龄：%d 当前存款%.2lf元 当前欠款%.2lf元\n", p->user->card, p->user->name, p->user->age, p->user->money, p->user->loan);
            wait("输入任意键继续");
            return;
        }
        p = p->next;
    }
    printf("当前系统无该用户\n");
    wait("输入任意键继续");
}

void adminfreeze() {
    printf("请输入您要冻结的卡号:");
    char card[1000] = { 0 };
    scanf("%s", card);
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(card, p->user->card) == 0) {
            p->user->isfreeze = 1;
            printf("卡号 %s 冻结成功\n", card);
            char str[1000] = { 0 };
            sprintf(str, "卡号:%s 姓名:%s 冻结卡号", p->user->card, p->user->name);
            write_record(str);
            updata();
            wait("输入任意键继续");
            return;
        }
        p = p->next;
    }
    printf("当前系统无该用户\n");
    wait("输入任意键继续");
}
void adminunfreeze() {
    printf("请输入您要解冻的卡号:");
    char card[1000] = { 0 };
    scanf("%s", card);
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(card, p->user->card) == 0) {
            p->user->isfreeze = 0;
            p->user->count = 0;
            printf("卡号 %s 解冻成功\n", card);
            char str[1000] = { 0 };
            sprintf(str, "卡号:%s 姓名:%s 解冻卡号", p->user->card, p->user->name);
            write_record(str);
            updata();
            wait("输入任意键继续");
            return;
        }
        p = p->next;
    }
    printf("当前系统无该用户\n");
    wait("输入任意键继续");

}

void admincancelaccout() {
    char card[1000] = { 0 };
    printf("输入用户的卡号:");
    scanf("%s", card);
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(card, p->user->card) == 0) {
            cancelaccout(p->user);
            break;
        }
        p = p->next;
    }
    if (p == NULL) {
        printf("当前系统无该用户\n");
        wait("输入任意键退出");
    }
}

void checksingletrade() {
        char card[1000] = { 0 };
        printf("输入用户的卡号:");
        scanf("%s", card);
        struct list* p = getlisthead()->next;
        while (p != NULL) {
            if (strcmp(card, p->user->card) == 0) {
                printsingle_record(p->user);
                break;
            }
            p = p->next;
        }
        if (p == NULL) {
            printf("当前系统无该用户\n");
            wait("输入任意键退出");
        }
    }

