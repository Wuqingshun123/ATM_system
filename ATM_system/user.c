#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"user.h"
#include"main.h"
#include"write.h"
#include"initial_function.h"
#include"list.h"
#include"read.h"

struct user* getuser(char* name, int age, char* phone, char* identity, char* password) {
	struct user* user = (struct user*)malloc(sizeof(struct user));
	strcpy(user->name, name);
	user->age = age;
	strcpy(user->phone, phone);
	strcpy(user->identity, identity);
	strcpy(user->password, password);
	strcpy(user->card, creatID());
	user->isfreeze = 0;
	user->money = 100;
	user->count = 0;
	user->loan = 0;
}//�����ڹ��췽��

char* creatID() {
	srand(time(NULL));
	char id[12] = { 0 };
	int i;
	for (i = 0; i < 11; i++) {
		id[i] = (rand() % 9 + 1) + '0';
	}
	char* s = (char*)malloc(sizeof(char));
	strcpy(s, id);
	return s;
}//������ɿ���

void check(struct user* user) {
    printf("���ĵ�ǰ�������Ϊ%.2fԪ\n", user->money);
    wait("�������������");
}

void deposit(struct user* user) {
    double money = 0;
    printf("������Ҫ����Ľ��:");
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("������Ҫ����Ľ��:");
        }
        else break;
    }
    user->money += money;
    printf("���ɹ�\n");
    char str[1000] = { 0 };
    sprintf(str, "����:%s ����:%s ���%.2fԪ", user->card, user->name, money);
    write_record(str);
    updata();
    wait("�������������");
}

void withdraw(struct user* user) {
    double money;

    printf("������Ҫȡ���Ľ��:");
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("������Ҫȡ���Ľ��:");
        }
        else break;
    }

    if (money > user->money) {
        printf("��������\n");
        wait("����������˳�");
        return;
    }
    user->money -= money;
    printf("ȡ��ɹ�\n");
    char str[1000] = { 0 };
    sprintf(str, "����:%s ����:%s ȡ��%.2fԪ", user->card, user->name, money);
    write_record(str);
    updata();
    wait("����������˳�");
}

void loan(struct user* user) {
    if (user->loan > 0) {
        printf("��ϵͳ������ͬһ���Ŷ�δ�����ǻ����ϴδ����Ǯ\n");
        wait("�������������");
        return;
    }
    printf("������Ҫ����Ľ��:");
    double money = 0;
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("������Ҫ����Ľ��:");
        }
        else break;
    }
    printf("�������Ҫ��%.2lfԪ\n", money * 1.2);
    if (cancel() == 0) return;
    user->loan += money * 1.2;
    user->money += money;
    printf("����ɹ�\n");
    char str[1000] = { 0 };
    sprintf(str, "����:%s ����:%s ����%.2fԪ", user->card, user->name, money);
    write_record(str);
    updata();
    wait("�������������");
}

void payback(struct user* user) {
    if (user->loan <= 0) {
        printf("����ǰû��Ƿ��\n");
        wait("����������˳�");
        return;
    }
    printf("��������Ҫ���Ŀ�:");
    double money;
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("��������Ҫ���Ŀ�:");
        }
        else break;
    }
    if (user->money < money) {
        printf("��������\n");
        wait("�������������");
        return;
    }
    if (user->loan < money) {
        printf("����û��Ƿ��ô��Ǯ\n");
        wait("�������������");
        return;
    }
    user->money -= money;
    user->loan -= money;
    printf("����ɹ�\n");
    char str[1000] = { 0 };
    sprintf(str, "����:%s ����:%s ����%.2fԪ", user->card, user->name, money);
    write_record(str);
    updata();
    wait("����������˳�");
}

void freeze(struct user* user) {
    if (cancel() == 0) return;
    user->isfreeze = 1;
    printf("����ɹ�\n");
    char str[1000] = { 0 };
    sprintf(str, "����:%s ����:%s ���Ῠ��", user->card, user->name);
    write_record(str);
    updata();
    wait("����������˳�");
}

void changepassword(struct user* user) {
    printf("�������ĵ�¼����:");
    char password[1000] = { 0 };
    scanf("%s", password);
    if (strcmp(user->password, password) != 0) {
        printf("�������\n");
        wait("����������˳�");
        return;
    }
    while (1) {
        while (1) {
            printf("���������������µ�¼����:");
            scanf("%s", password);
            if (islegal(password) == 0) {
                printf("�������Ϊ6λ���������֣�����������\n");
            }
            else break;
        }
        printf("�ٴ��������ĵ�¼����:");
        char password1[1000] = { 0 };
        scanf("%s", password1);
        if (strcmp(password, password1) != 0) {
            printf("�����������벻һ�£����ѻ�����������\n");
            continue;
        }
        else break;
    }
    strcpy(user->password, password);
    printf("�޸�����ɹ�\n");
    updata();
    wait("����������˳�");
}

int cancelaccout(struct user* user) {
    if (user->money > 0) {
        printf("���û�ȡ������Ǯ����ע��\n");
        wait("����������˳�");
        return 1;
    }
    if (user->loan > 0) {
        printf("�û�����Ƿ�����ע��\n");
        wait("����������˳�");
        return 1;
    }
    printf("�绰����:");
    char phone[1000] = { 0 };
    scanf("%s", phone);
    if (strcmp(phone, user->phone) != 0) {
        wait("���������������������");
        return 1;
    }
    printf("���֤����:");
    char identity[1000] = { 0 };
    scanf("%s", identity);
    if (strcmp(identity, user->identity) != 0) {
        wait("���������������������");
        return 1;
    }
    if (cancel() == 0) return 1;
    removeuser(user);
    printf("ע���ɹ���\n");
    char str[1000] = { 0 };
    sprintf(str, "����:%s ����:%s ע���ɹ�", user->card, user->name);
    write_record(str);
    updata();
    wait("����������˳�");
    return 0;
}

void transfer(struct user* user) {
    struct user* u = NULL;
    char card[1000] = { 0 };
    double money;
    printf("����Է�����:");
    scanf("%s", card);
    if (strcmp(user->card, card) == 0) {
        printf("�����Զ��Լ�ת��\n");
        wait("����������˳�");
        return;
    }
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(p->user->card, card) == 0) {
            u = p->user;
            printf("����ת�˵Ľ��:");
            while (1) {
                money = getmoney();
                line();
                if (money == -1) {
                    printf("����ת�˵Ľ��:");
                }
                else break;
            }
            break;
        }
        p = p->next;
    }
    if (p == NULL) {
        printf("���޴���\n");
        wait("����������˳�");
        return;
    }
    if (user->money < money) {
        printf("����\n");
        wait("����������˳�");
        return;
    }
    if (cancel() == 0) return;
    u->money += money;
    user->money -= money;
    printf("ת�˳ɹ�\n");
    char str[1000] = { 0 };
    sprintf(str, "����:%s ����:%s �򿨺�%sת��%.2fԪ", user->card, user->name, u->card, money);
    write_record(str);
    sprintf(str, "����:%s ����:%s �յ�����:%s��ת��%.2fԪ", u->card, u->name, user->card, money);
    write_record(str);
    updata();
    wait("�������������");
}

void backpassword() {
    printf("����Ҫ�һصĿ���:");
    char card[1000] = { 0 };
    scanf("%s", card);
    struct user* user = find(card);
    if (user == NULL) {
        printf("���޴���\n");
        wait("����������˳�");
        return;
    }
    printf("�绰����:");
    char phone[1000] = { 0 };
    scanf("%s", phone);
    if (strcmp(phone, user->phone) != 0) {
        wait("������������������˳�");
        return;
    }
    printf("���֤����:");
    char identity[1000] = { 0 };
    scanf("%s", identity);
    if (strcmp(identity, user->identity) != 0) {
        wait("������������������˳�");
        return;
    }
    printf("������%s\n", user->password);
    wait("�������������");
}