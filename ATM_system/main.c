#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"user.h"
#include"list.h"
#include"windom.h"
#include"read.h"
#include"initial_function.h"
#include"write.h"

int main() {
	initial();
	loadusers();
	introduce();
	initialwindom();
	return 0;
}


void line() {
	printf("------------------------------------------------------------------------------------------------------\n");
}//分隔线，美观

void updata() {
	write_all();
}

int getint() {
	double a = 0;
	while (1) {
		if (scanf("%lf", &a) != 1) {
			printf("请输入整数\n");
			scanf("%s", buffer);
			return -1;
		}
		else {
			if (a == -1) {
				printf("您的输入溢出，请重新输入\n");
				return -1;
			}
			if (a - floor(a) != 0) {
				printf("请输入整数\n");
				return -1;
			}
			return (int)a;
		}
	}
}//对整数的异常处理

double getmoney() {
	double a = 0;
	while (1) {
		if (scanf("%lf", &a) != 1) {
			printf("请输入实数\n");
			scanf("%s", buffer);
			return -1;
		}
		else {
			if (a == -1) {
				printf("您的输入溢出，请重新输入\n");
				return -1;
			}
			double b = a * 100;
			if (b != floor(b)) {
				printf("不要出现必分小的钱\n");
				return -1;
			}
			if (a < 0) {
				printf("输入必须大于0\n");
				return -1;
			}
			return a;
		}
	}
}//对整数的异常处理

void wait(char* str) {
	printf("%s:", str);
	scanf("%s", buffer);
	line();
}

int cancel() {
	int key = 0;
	printf("是否继续此次操作，如果继续输入1，否则终止操作:");
	while (1) {
		key = getint();
		line();
		if (key == -1) {
			printf("是否继续此次操作，如果继续输入1，否则终止操作:");
		}
		else break;
	}
	if (key != 1) {
		printf("终止操作成功\n");
		wait("输入任意键继续:");
		return 0;
	}
	return 1;
}

char* gettime() {
	time_t t = time(NULL); // 获取当前时间
	struct tm* now = localtime(&t); // 将时间转换为当地时间
	// 格式化日期和时间，并存储在缓冲区中
	snprintf(buffer, sizeof(buffer), "[%04d-%02d-%02d %02d:%02d:%02d]",now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
	return buffer;
}
