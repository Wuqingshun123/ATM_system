#include"initial_function.h"
#include<stdio.h>
#include"list.h"
#include"windom.h"
#include<string.h>
#include<ctype.h>
#include"user.h"
#include"write.h"
#include"read.h"
#include"main.h"

void login() {
    char card[1000] = { 0 };
    char password[1000] = { 0 };
    printf("�𾴵��û���ã���ӭʹ�õ�¼����\n");
    printf("��������Ŀ���:");
    scanf("%s", card);
    if (strcmp(card, "admin") == 0) {
        printf("�������������:");
        scanf("%s", password);
        if (strcmp(password, "admin") == 0) {
            printf("��¼�ɹ�\n");
            line();
            adminwindom();
            return;
        }
        else {
            printf("�������\n");
            wait("�������������");
            return;
        }
    }
    struct user* user = find(card);
    if (user == NULL) {
        printf("���޴���\n");
        wait("�������������");
        return;
    }
    if (user->isfreeze == 1) {
        printf("���˺��ѱ����ᣬ����ϵ����Ա�ⶳ\n");
        wait("����������˳�");
        return;
    }
    printf("�������������п�����:");
    scanf("%s", password);
    if (strcmp(password, user->password) == 0) {
        line();
        userwindom(user);
        return;
    }
    else {
        printf("�������������������������\n");
        user->count++;
        if (user->count >= 3) {
            user->isfreeze = 1;
            printf("����˺�: %s �ѱ����ᣬ����ϵ����Ա����ⶳ\n", user->card);
            wait("�������������");
            return;
        }
        printf("��������������� %d �Σ������˻���������\n", 3 - user->count);
        wait("�������������");
        updata();
    }
}

void regist() {
    char name[1000] = { 0 };
    int age;
    char phone[1000] = { 0 };
    char identity[1000] = { 0 };
    char password[1000] = { 0 };
    char password1[1000] = { 0 };
    printf("�𾴵��û�����ӭʹ��ע�Ṧ��\n");
    printf("���Ҫ��;Ҫ�˳���ATMģ��ϵͳ�������һ������ѡ��\n");
    printf("�����·���д��Ļ�����Ϣ\n");
    printf("��������:");
    scanf("%s", name);
    printf("��������:");
    while (1) {
        age = getint();
        if (age == -1) {
            printf("��������:");
        }
        else break;
    }
    while (1) {
        int i;
        printf("���ĵ绰����:");
        scanf("%s", phone);
        if (strlen(phone) > 11) {
            printf("���Ȳ�Ӧ����11\n");
            continue;
        }
        for (i = 0; i < strlen(phone); i++) {
            if (!isdigit(phone[i])) {
                printf("����Ӧ��ȫΪ����\n");
                break;
            }
        }
        if (i == strlen(phone)) break;
    }
    while (1) {
        int i;
        printf("�������֤:");
        scanf("%s", identity);
        if (strlen(identity) > 11) {
            printf("���Ȳ�Ӧ����11\n");
            continue;
        }
        for (i = 0; i < strlen(identity); i++) {
            if (!isdigit(identity[i])) {
                printf("����Ӧ��ȫΪ����\n");
                break;
            }
        }
        if (i == strlen(identity)) break;
    }
    while (1) {
        while (1) {
            printf("�������������ĵ�¼����:");
            scanf("%s", password);
            if (islegal(password) ==  0) {
               printf("�������Ϊ6λ���������֣�����������\n");
            }
            else break;
        }
        printf("�ٴ��������ĵ�¼����:");
        scanf("%s", password1);
        if (strcmp(password, password1) != 0) {
            printf("�����������벻һ�£����ѻ�����������\n");
            continue;
        }
        else break;
    }
    if (cancel() == 0) return;
    struct user* user = getuser(name, age, phone, identity, password);
    add(user);
    write_single(user);
    printf("%s ��ϲ��ע��ɹ�\n", user->name);
    printf("���Ŀ�����:%s\n", user->card);
    sprintf(buffer, "����:%s ����:%s ע��ɹ�", user->card, user->name);
    write_record(buffer);
    wait("�������������");
}

int islegal(char* password) {
    int i;
    if (strlen(password) != 6) return 0;
    for (i = 0; i < 6; i++) {
        if (!isdigit(password[i])) return 0;
    }
    return 1;
}//�ж������Ƿ�Ϸ�