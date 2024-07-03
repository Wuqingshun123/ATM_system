static char userdatapath[1000] = "userdata.txt"; //用户数据文件路径
static char traderecordpath[1000] = "traderecord.txt"; //交易活动文件路径

static char buffer[1024] = { 0 }; //用来接受一些无关紧要的输入
void loadusers();

void printall_record();

void printsingle_record(struct user* user);