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
    if (getlisthead()->next == NULL) printf("��ǰû���κ��û�\n");
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        printf("���ţ�%s ������%s ���䣺%d ��ǰ���%.2lfԪ ��ǰǷ��%.2lfԪ\n\n", p->user->card,p->user->name,  p->user->age, p->user->money, p->user->loan);
        p = p->next;
    }
    wait("�������������");
}

void print_single_user() {
    char card[100] = { 0 };
    printf("�����û��Ŀ���:");
    scanf("%s", card);
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(card, p->user->card) == 0) {
            printf("���ţ�%s ������%s ���䣺%d ��ǰ���%.2lfԪ ��ǰǷ��%.2lfԪ\n", p->user->card, p->user->name, p->user->age, p->user->money, p->user->loan);
            wait("�������������");
            return;
        }
        p = p->next;
    }
    printf("��ǰϵͳ�޸��û�\n");
    wait("�������������");
}

void adminfreeze() {
    printf("��������Ҫ����Ŀ���:");
    char card[1000] = { 0 };
    scanf("%s", card);
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(card, p->user->card) == 0) {
            p->user->isfreeze = 1;
            printf("���� %s ����ɹ�\n", card);
            char str[1000] = { 0 };
            sprintf(str, "����:%s ����:%s ���Ῠ��", p->user->card, p->user->name);
            write_record(str);
            updata();
            wait("�������������");
            return;
        }
        p = p->next;
    }
    printf("��ǰϵͳ�޸��û�\n");
    wait("�������������");
}
void adminunfreeze() {
    printf("��������Ҫ�ⶳ�Ŀ���:");
    char card[1000] = { 0 };
    scanf("%s", card);
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(card, p->user->card) == 0) {
            p->user->isfreeze = 0;
            p->user->count = 0;
            printf("���� %s �ⶳ�ɹ�\n", card);
            char str[1000] = { 0 };
            sprintf(str, "����:%s ����:%s �ⶳ����", p->user->card, p->user->name);
            write_record(str);
            updata();
            wait("�������������");
            return;
        }
        p = p->next;
    }
    printf("��ǰϵͳ�޸��û�\n");
    wait("�������������");

}

void admincancelaccout() {
    char card[1000] = { 0 };
    printf("�����û��Ŀ���:");
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
        printf("��ǰϵͳ�޸��û�\n");
        wait("����������˳�");
    }
}

void checksingletrade() {
        char card[1000] = { 0 };
        printf("�����û��Ŀ���:");
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
            printf("��ǰϵͳ�޸��û�\n");
            wait("����������˳�");
        }
    }

