#include<stdio.h>
#include"initial_function.h"
#include"main.h"
#include"admin.h"
#include"read.h"
#include"user.h"
#include"windom.h"

void introduce() {
	line();
	printf("�𾴵��û�����ӭʹ��ATMϵͳ��\n");
	line();
	printf("��ʹ��ATMģ��ϵͳ֮ǰ���������Ķ����ߵ�ǰ�ԡ�\n");
	wait("�������������");
	printf("1����ϵͳ�ɼ��״�ѧ���������ѧ�뼼��������˳���Դ��죬ѧ��2023400648\n");
	printf("2����ϵͳ�޳�ʼ�û�����ͨ�û�������ע��\n");
	printf("3����ϵͳ��ϵͳ����Ա����¼����Ա�ĳ�ʼ�˺ź��������admin\n");
	printf("4����ATMϵͳ���в�����ԪΪ������λ����Ϊ��С��λ����Ҫ���ֱ�1��С������\n");
	printf("5��ÿ����ע����û����˻�����100Ԫ\n");
	printf("6����������ϵͳ��������\n");
	wait("�������������");
}

void initialwindom() {
	while (1) {
		printf("1����¼         3����������\n");
		printf("2��ע��         4���˳�ϵͳ\n");
		printf("��������������ѡ��:");
		int key = -1;
		while (1) {
			key = getint();
			line();
			if (key == -1) {
				printf("��������������ѡ��:");
			}
			else break;
		}
		switch (key) {
		case 1:
			login();
			break;
		case 2:
			regist();
			break;
		case 3:
            backpassword();
			break;
		case 4:
			return;
		default:
			printf("����������������������\n");
			wait("�������������");
			break;
		}
	}
}

void adminwindom() {
        while (1) {
            printf("�𾴵�ATMϵͳ����Ա������\n");
            printf("1����ѯ�����û�         5����ѯ���׼�¼��\n");
            printf("2����ѯ�����û�         6����ѯ�����û����׼�¼ \n");
            printf("3�������˺�             7��ע���ͻ��˺�\n");
            printf("4���˺Žⶳ             8���˳���¼\n");
            printf("����ѡ��:");
            int key = -1;
            while (1) {
                key = getint();
                line();
                if (key == -1) {
                    printf("��������������ѡ��:");
                }
                else break;
            }
            switch (key) {
            case 1:
                print_all_users();
                break;
            case 2:
                print_single_user();
                break;
            case 3:
                adminfreeze();
                break;
            case 4:
                adminunfreeze();
                break;
            case 5:
                printall_record();
                wait("�������������");
                break;
            case 6:
                checksingletrade();
                break;
            case 7:
                admincancelaccout();
                break;
            case 8:
                return;
            default:
                printf("������������\n");
                wait("����������˳�");
                break;
            }
    }
}

void userwindom(struct user* user) {
    while (1) {
        printf("�𾴵�%s������\n", user->name);
        printf("1����ѯ���      7���鿴���׼�¼\n");
        printf("2�����          8���޸�����\n");
        printf("3��ȡ��          9�������˺�\n");
        printf("4��ת��         10��ע���˺�\n");
        printf("5������         11����ѯǷ��\n");
        printf("6������         12���˳�\n");
        printf("����ѡ��:");
        int key = -1;
        while (1) {
            key = getint();
            line();
            if (key == -1) {
                printf("��������������ѡ��:");
            }
            else break;
        }
        switch (key) {
        case 1:
            check(user);
            break;
        case 2:
            deposit(user);
            break;
        case 3:
            withdraw(user);
            break;
        case 4:
            transfer(user);
            break;
        case 5:
            loan(user);
            break;
        case 6:
            payback(user);
            break;
        case 7:
            printsingle_record(user);
            break;
        case 8:
            changepassword(user);
            break;
        case 9:
            freeze(user);
            if (user->isfreeze == 1) return;
            break;
        case 10:
            if (cancelaccout(user) == 0) return;
            break;
        case 11:
            printf("����ǰǷ��%.2fԪ\n", user->loan);
            wait("�������������");
            break;
        case 12:
            return;
        default:
            printf("������������\n");
            wait("����������˳�");
            break;
        }
    }
}