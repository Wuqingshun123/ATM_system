#include<stdio.h>
#include"initial_function.h"
#include"main.h"
#include"admin.h"
#include"read.h"
#include"user.h"
#include"windom.h"

void introduce() {
	line();
	printf("尊敬的用户，欢迎使用ATM系统！\n");
	line();
	printf("在使用ATM模拟系统之前，先请您阅读作者的前言。\n");
	wait("输入任意键继续");
	printf("1、本系统由吉首大学，计算机科学与技术，吴庆顺独自打造，学号2023400648\n");
	printf("2、本系统无初始用户，普通用户必须先注册\n");
	printf("3、本系统有系统管理员，登录管理员的初始账号和密码均是admin\n");
	printf("4、本ATM系统所有操作以元为基本单位，分为最小单位，不要出现比1分小的输入\n");
	printf("5、每个新注册的用户，账户上有100元\n");
	printf("6、关于信誉系统还待补充\n");
	wait("输入任意键继续");
}

void initialwindom() {
	while (1) {
		printf("1、登录         3、忘记密码\n");
		printf("2、注册         4、退出系统\n");
		printf("在这里输入您的选择:");
		int key = -1;
		while (1) {
			key = getint();
			line();
			if (key == -1) {
				printf("在这里输入您的选择:");
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
			printf("您的输入有误，请重新输入\n");
			wait("输入任意键继续");
			break;
		}
	}
}

void adminwindom() {
        while (1) {
            printf("尊敬的ATM系统管理员，您好\n");
            printf("1、查询所有用户         5、查询交易记录表\n");
            printf("2、查询单个用户         6、查询单个用户交易记录 \n");
            printf("3、冻结账号             7、注销客户账号\n");
            printf("4、账号解冻             8、退出登录\n");
            printf("您的选择:");
            int key = -1;
            while (1) {
                key = getint();
                line();
                if (key == -1) {
                    printf("在这里输入您的选择:");
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
                wait("输入任意键继续");
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
                printf("您的输入有误\n");
                wait("输入任意键退出");
                break;
            }
    }
}

void userwindom(struct user* user) {
    while (1) {
        printf("尊敬的%s，您好\n", user->name);
        printf("1、查询余额      7、查看交易记录\n");
        printf("2、存款          8、修改密码\n");
        printf("3、取款          9、冻结账号\n");
        printf("4、转账         10、注销账号\n");
        printf("5、贷款         11、查询欠款\n");
        printf("6、还款         12、退出\n");
        printf("您的选择:");
        int key = -1;
        while (1) {
            key = getint();
            line();
            if (key == -1) {
                printf("在这里输入您的选择:");
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
            printf("您当前欠款%.2f元\n", user->loan);
            wait("输入任意键继续");
            break;
        case 12:
            return;
        default:
            printf("您的输入有误\n");
            wait("输入任意键退出");
            break;
        }
    }
}