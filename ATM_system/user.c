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
}//类似于构造方法

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
}//随机生成卡号

void check(struct user* user) {
    printf("您的当前可用余额为%.2f元\n", user->money);
    wait("输入任意键继续");
}

void deposit(struct user* user) {
    double money = 0;
    printf("输入您要存入的金额:");
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("输入您要存入的金额:");
        }
        else break;
    }
    user->money += money;
    printf("存款成功\n");
    char str[1000] = { 0 };
    sprintf(str, "卡号:%s 姓名:%s 存款%.2f元", user->card, user->name, money);
    write_record(str);
    updata();
    wait("输入任意键继续");
}

void withdraw(struct user* user) {
    double money;

    printf("输入您要取出的金额:");
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("输入您要取出的金额:");
        }
        else break;
    }

    if (money > user->money) {
        printf("您的余额不足\n");
        wait("输入任意键退出");
        return;
    }
    user->money -= money;
    printf("取款成功\n");
    char str[1000] = { 0 };
    sprintf(str, "卡号:%s 姓名:%s 取款%.2f元", user->card, user->name, money);
    write_record(str);
    updata();
    wait("输入任意键退出");
}

void loan(struct user* user) {
    if (user->loan > 0) {
        printf("本系统不允许同一卡号多次贷款，除非还完上次贷款的钱\n");
        wait("输入任意键继续");
        return;
    }
    printf("输入您要贷款的金额:");
    double money = 0;
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("输入您要贷款的金额:");
        }
        else break;
    }
    printf("贷款后您要还%.2lf元\n", money * 1.2);
    if (cancel() == 0) return;
    user->loan += money * 1.2;
    user->money += money;
    printf("贷款成功\n");
    char str[1000] = { 0 };
    sprintf(str, "卡号:%s 姓名:%s 贷款%.2f元", user->card, user->name, money);
    write_record(str);
    updata();
    wait("输入任意键继续");
}

void payback(struct user* user) {
    if (user->loan <= 0) {
        printf("您当前没有欠款\n");
        wait("输入任意键退出");
        return;
    }
    printf("请输入您要还的款:");
    double money;
    while (1) {
        money = getmoney();
        line();
        if (money == -1) {
            printf("请输入您要还的款:");
        }
        else break;
    }
    if (user->money < money) {
        printf("您的余额不足\n");
        wait("输入任意键继续");
        return;
    }
    if (user->loan < money) {
        printf("您并没有欠这么多钱\n");
        wait("输入任意键继续");
        return;
    }
    user->money -= money;
    user->loan -= money;
    printf("还款成功\n");
    char str[1000] = { 0 };
    sprintf(str, "卡号:%s 姓名:%s 还款%.2f元", user->card, user->name, money);
    write_record(str);
    updata();
    wait("输入任意键退出");
}

void freeze(struct user* user) {
    if (cancel() == 0) return;
    user->isfreeze = 1;
    printf("冻结成功\n");
    char str[1000] = { 0 };
    sprintf(str, "卡号:%s 姓名:%s 冻结卡号", user->card, user->name);
    write_record(str);
    updata();
    wait("输入任意键退出");
}

void changepassword(struct user* user) {
    printf("输入您的登录密码:");
    char password[1000] = { 0 };
    scanf("%s", password);
    if (strcmp(user->password, password) != 0) {
        printf("密码错误\n");
        wait("输入任意键退出");
        return;
    }
    while (1) {
        while (1) {
            printf("在这里输入您的新登录密码:");
            scanf("%s", password);
            if (islegal(password) == 0) {
                printf("密码必须为6位阿拉伯数字，请重新输入\n");
            }
            else break;
        }
        printf("再次输入您的登录密码:");
        char password1[1000] = { 0 };
        scanf("%s", password1);
        if (strcmp(password, password1) != 0) {
            printf("两次密码输入不一致，提醒户主重新输入\n");
            continue;
        }
        else break;
    }
    strcpy(user->password, password);
    printf("修改密码成功\n");
    updata();
    wait("输入任意键退出");
}

int cancelaccout(struct user* user) {
    if (user->money > 0) {
        printf("请用户取走所有钱，再注销\n");
        wait("输入任意键退出");
        return 1;
    }
    if (user->loan > 0) {
        printf("用户还有欠款，不能注销\n");
        wait("输入任意键退出");
        return 1;
    }
    printf("电话号码:");
    char phone[1000] = { 0 };
    scanf("%s", phone);
    if (strcmp(phone, user->phone) != 0) {
        wait("输入有误，输入任意键继续");
        return 1;
    }
    printf("身份证号码:");
    char identity[1000] = { 0 };
    scanf("%s", identity);
    if (strcmp(identity, user->identity) != 0) {
        wait("输入有误，输入任意键继续");
        return 1;
    }
    if (cancel() == 0) return 1;
    removeuser(user);
    printf("注销成功！\n");
    char str[1000] = { 0 };
    sprintf(str, "卡号:%s 姓名:%s 注销成功", user->card, user->name);
    write_record(str);
    updata();
    wait("输入任意键退出");
    return 0;
}

void transfer(struct user* user) {
    struct user* u = NULL;
    char card[1000] = { 0 };
    double money;
    printf("输入对方卡号:");
    scanf("%s", card);
    if (strcmp(user->card, card) == 0) {
        printf("不可以对自己转账\n");
        wait("输入任意键退出");
        return;
    }
    struct list* p = getlisthead()->next;
    while (p != NULL) {
        if (strcmp(p->user->card, card) == 0) {
            u = p->user;
            printf("输入转账的金额:");
            while (1) {
                money = getmoney();
                line();
                if (money == -1) {
                    printf("输入转账的金额:");
                }
                else break;
            }
            break;
        }
        p = p->next;
    }
    if (p == NULL) {
        printf("查无此人\n");
        wait("输入任意键退出");
        return;
    }
    if (user->money < money) {
        printf("余额不足\n");
        wait("输入任意键退出");
        return;
    }
    if (cancel() == 0) return;
    u->money += money;
    user->money -= money;
    printf("转账成功\n");
    char str[1000] = { 0 };
    sprintf(str, "卡号:%s 姓名:%s 向卡号%s转账%.2f元", user->card, user->name, u->card, money);
    write_record(str);
    sprintf(str, "卡号:%s 姓名:%s 收到卡号:%s的转账%.2f元", u->card, u->name, user->card, money);
    write_record(str);
    updata();
    wait("输入任意键继续");
}

void backpassword() {
    printf("输入要找回的卡号:");
    char card[1000] = { 0 };
    scanf("%s", card);
    struct user* user = find(card);
    if (user == NULL) {
        printf("查无此人\n");
        wait("输入任意键退出");
        return;
    }
    printf("电话号码:");
    char phone[1000] = { 0 };
    scanf("%s", phone);
    if (strcmp(phone, user->phone) != 0) {
        wait("输入有误，输入任意键退出");
        return;
    }
    printf("身份证号码:");
    char identity[1000] = { 0 };
    scanf("%s", identity);
    if (strcmp(identity, user->identity) != 0) {
        wait("输入有误，输入任意键退出");
        return;
    }
    printf("密码是%s\n", user->password);
    wait("输入任意键继续");
}