struct user {
	char card[100]; //�˺�
	char password[100]; //����
	int isfreeze; //�ж��Ƿ񶳽�
	char name[100]; //����
	int age; //����
	char phone[100];//�绰����
	char identity[100];//���֤
	double money;//���
	int count; //�����������Ĵ���
	double loan; //����
};//�û��ṹ��

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