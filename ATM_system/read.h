static char userdatapath[1000] = "userdata.txt"; //�û������ļ�·��
static char traderecordpath[1000] = "traderecord.txt"; //���׻�ļ�·��

static char buffer[1024] = { 0 }; //��������һЩ�޹ؽ�Ҫ������
void loadusers();

void printall_record();

void printsingle_record(struct user* user);