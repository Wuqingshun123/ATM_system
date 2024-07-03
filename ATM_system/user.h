struct user {
	char card[100]; //账号
	char password[100]; //密码
	int isfreeze; //判断是否冻结
	char name[100]; //名字
	int age; //年龄
	char phone[100];//电话号码
	char identity[100];//身份证
	double money;//存款
	int count; //当日输错密码的次数
	double loan; //贷款
};//用户结构体

struct user* getuser(char*, int, char*, char*, char*);
char* creatID();

void check(struct user* user);

void deposit(struct user* user);

void withdraw(struct user* user);

void loan(struct user* user);

void payback(struct user* user);

void freeze(struct user* user);

void changepassword(struct user* user);

int cancelaccout(struct user* user);

void transfer(struct user* user);

void backpassword();