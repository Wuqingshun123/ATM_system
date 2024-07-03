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
    printf("尊敬的用户你好，欢迎使用登录功能\n");
    printf("请输入你的卡号:");
    scanf("%s", card);
    if (strcmp(card, "admin") == 0) {
        printf("请输入你的密码:");
        scanf("%s", password);
        if (strcmp(password, "admin") == 0) {
            printf("登录成功\n");
            line();
            adminwindom();
            return;
        }
        else {
            printf("密码错误\n");
            wait("输入任意键继续");
            return;
        }
    }
    struct user* user = find(card);
    if (user == NULL) {
        printf("查无此人\n");
        wait("输入任意键继续");
        return;
    }
    if (user->isfreeze == 1) {
        printf("该账号已被冻结，请联系管理员解冻\n");
        wait("输入任意键退出");
        return;
    }
    printf("请输入您的银行卡密码:");
    scanf("%s", password);
    if (strcmp(password, user->password) == 0) {
        line();
        userwindom(user);
        return;
    }
    else {
        printf("您输入的密码有误，请重新输入\n");
        user->count++;
        if (user->count >= 3) {
            user->isfreeze = 1;
            printf("你的账号: %s 已被冻结，请联系管理员申请解冻\n", user->card);
            wait("输入任意键继续");
            return;
        }
        printf("今日若在输入错误 %d 次，您的账户将被冻结\n", 3 - user->count);
        wait("输入任意键继续");
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
    printf("尊敬的用户，欢迎使用注册功能\n");
    printf("如果要中途要退出，ATM模拟系统在最后有一个放弃选项\n");
    printf("请在下方填写你的基本信息\n");
    printf("您的姓名:");
    scanf("%s", name);
    printf("您的年龄:");
    while (1) {
        age = getint();
        if (age == -1) {
            printf("您的年龄:");
        }
        else break;
    }
    while (1) {
        int i;
        printf("您的电话号码:");
        scanf("%s", phone);
        if (strlen(phone) > 11) {
            printf("长度不应超过11\n");
            continue;
        }
        for (i = 0; i < strlen(phone); i++) {
            if (!isdigit(phone[i])) {
                printf("输入应该全为数字\n");
                break;
            }
        }
        if (i == strlen(phone)) break;
    }
    while (1) {
        int i;
        printf("您的身份证:");
        scanf("%s", identity);
        if (strlen(identity) > 11) {
            printf("长度不应超过11\n");
            continue;
        }
        for (i = 0; i < strlen(identity); i++) {
            if (!isdigit(identity[i])) {
                printf("输入应该全为数字\n");
                break;
            }
        }
        if (i == strlen(identity)) break;
    }
    while (1) {
        while (1) {
            printf("在这里输入您的登录密码:");
            scanf("%s", password);
            if (islegal(password) ==  0) {
               printf("密码必须为6位阿拉伯数字，请重新输入\n");
            }
            else break;
        }
        printf("再次输入您的登录密码:");
        scanf("%s", password1);
        if (strcmp(password, password1) != 0) {
            printf("两次密码输入不一致，提醒户主重新输入\n");
            continue;
        }
        else break;
    }
    if (cancel() == 0) return;
    struct user* user = getuser(name, age, phone, identity, password);
    add(user);
    write_single(user);
    printf("%s 恭喜您注册成功\n", user->name);
    printf("您的卡号是:%s\n", user->card);
    sprintf(buffer, "卡号:%s 姓名:%s 注册成功", user->card, user->name);
    write_record(buffer);
    wait("输入任意键继续");
}

int islegal(char* password) {
    int i;
    if (strlen(password) != 6) return 0;
    for (i = 0; i < 6; i++) {
        if (!isdigit(password[i])) return 0;
    }
    return 1;
}//判断输入是否合法