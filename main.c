#include<stdio.h>
#include <io.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>


//用户登录注册函数
char* input_PW();//输入密码
char* input_re_AC();//判断账号是否存在
char* input_AC(char account[100]);//输入账号
struct user* pre_user();//之前文件中的账号
struct user* logIn(struct user* head);//登录
void createAC(struct user* head);//注册账号
void Main();//主函数
//音乐播放菜单函数
void menu();//音乐菜单
void play();//播放音乐
void pause();//暂停播放
void resume();//恢复播放
void Draw_yinliang();//音量-
void Up_yinliang();//音量+


struct user {
	int num;
	char account[100];
	char password[100];
	struct user* next;
};

char path_user[150] = "C:\\Users\\xiaoyuer\\OneDrive\\桌面\\userInfo.txt";  //储存用户信息的文件
//读取指定文件中的用户信息，并把相关信息储存到链表


int main()
{
	Main();
	return 0;
}

void Main()
{
	int i;
	struct user* HEAD_USER = pre_user();
	printf("\t\t\t\t\t\t1.登录\n\t\t\t\t\t\t2.注册\n\t\t\t\t\t\t0.退出\n");
	printf("\t\t\t\t\t\tinput your choice:");
	scanf("%d", &i);
	switch (i) {
	case 1:
		logIn(HEAD_USER);
		system("CLS");
		break;
	case 2:
		createAC(HEAD_USER);
		system("CLS");
		Main();
		break;
	case 0:
		exit(0);
	default:
		printf("错误输入！");
		Sleep(1000);
		exit(0);
	}
}
struct user* pre_user()
{

	FILE* fp;

	fp = fopen(path_user, "r");  //打开文件
	if (fp == NULL)
	{
		printf("打开文件失败");//输出文件打开失败！\n
		return NULL;
	}

	struct user* head, * p, * q;
	int number = 1;//记录用户个数

	head = (struct user*)malloc(sizeof(struct user));
	head->next = NULL;
	p = (struct user*)malloc(sizeof(struct user));

	fscanf(fp, "%s", p->account);
	fscanf(fp, "%s", p->password);
	p->num = number;
	head->next = p;

	while (!feof(fp)) {

		number++;
		q = (struct user*)malloc(sizeof(struct user));
		fscanf(fp, "%s", q->account);
		fscanf(fp, "%s", q->password);
		q->num = number;
		q->next = NULL;
		p->next = q;
		p = q;
	}

	p = head->next;

	fclose(fp);
	return head;
}

//用户登录
struct user* logIn(struct user* head)
{
	char account[100];
	char password[100];
	struct user* p = head->next;
	input_AC(account);

	while (p != NULL && strcmp(p->account, account) != 0)
	{
		p = p->next;
	}
	if (p == NULL) {
		printf("\t\t\t\t\t\t找不到用户!!!!!!");//输出"找不到该用户"
		Sleep(1000);
		system("CLS");
		Main();
		return NULL;
	}

	strcpy(password, input_PW());

	if (strcmp(p->password, password) != 0) {
		printf("\t\t\t\t\t\t密码错误!!!!!!");//输出 "密码错误";
		Sleep(1000);
		system("CLS");
		Main();
		return NULL;
	}
	if (strcmp(p->password, password) == 0) {
		printf("\t\t\t\t\t\t欢迎!!!!!!");//printf"欢迎";
		Sleep(1000);
		menu();
		return p;
	}
}

//用户注册
void createAC(struct user* head)
{

	FILE* fp;
	fp = fopen(path_user, "a");
	if (fp == NULL) {
		printf("打开文件失败");
	}
	else {
		char account[100];
		char password[100];
		struct user* p = NULL;
		int flag_repe = 0;//0表示该用户名没有和别个的account重复，1表示重复了
		struct user* q = (struct user*)malloc(sizeof(struct user));
		input_AC(account);
		p = head->next;
		while (p != NULL) {
			if (strcmp(p->account, account) == 0)
			{
				flag_repe = 1;
			}
			p = p->next;
		}
		while (flag_repe == 1) {
			p = head->next;
			flag_repe = 0;
			strcpy(account, input_re_AC());
			while (p != NULL) {
				if (strcmp(p->account, account) == 0) {
					flag_repe = 1;
				}
				p = p->next;
			}
		}
		strcpy(password, input_PW());
		p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		strcpy(q->account, account);
		strcpy(q->password, password);
		q->next = NULL;
		p->next = q;
		fprintf(fp, "\n%s\n%s", account, password);
		fclose(fp);
		printf("\t\t\t\t\t\t注册成功！!!!!!");
		Sleep(1000);
	}
}
char* input_AC(char account[100]) {
	system("CLS");
	printf("\t\t\t\t\t\t输入用户名:");
	scanf("%s", account);
	return account;
}

char* input_re_AC() {
	char account[100];
	printf("\t\t\t\t\t\t用户名已经存在.\n");
	scanf("%s", account);
	return account;
}

char* input_PW() {
	char password[100];
	printf("\t\t\t\t\t\t请输入密码:");
	scanf("%s", password);
	return password;
}

//音乐播放器菜单函数系列

void menu()
{

	int i;
	printf("\n\t\t\t\t\t\t\t1.播放\n");
	printf("\t\t\t\t\t\t\t2.暂停\n");
	printf("\t\t\t\t\t\t\t3.继续\n");
	printf("\t\t\t\t\t\t\t4.音量+\n");
	printf("\t\t\t\t\t\t\t5.音量-\n");
	printf("\t\t\t\t\t\t\t6.快进15s\n");
	printf("\t\t\t\t\t\t\t7.快退15s\n");
	printf("\t\t\t\t\t\t\t0.退出\n");
	printf("\t\t\t\t\t选择你的操作：");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
	{
		play();
		system("CLS");
		menu();
		break;
	}
	case 2:
	{
		pause();
		system("CLS");
		menu();
		break;

	}
	case 3:
	{
		resume();
		system("CLS");
		menu();
		break;

	}
	case 4:
	{
		Up_yinliang();
		system("CLS");
		menu();
		break;

	}
	case 5:

	{
		Draw_yinliang();
		system("CLS");
		menu();
		break;

	}
	case 0:
	{
		printf("\t\t\t\t\t\t退出\n");
		break;

	}
	default:
		printf("\t\t\t\t\t\t输入错误！");

	}

}
void play()//播放音乐
{
	int i;
	system("CLS");
	printf("\t\t\t\t\t\t\t1.稻香\n");
	printf("\t\t\t\t\t\t\t2.晴天\n");
	printf("\t\t\t\t\t\t\t3.手写的从前\n");
	printf("\t\t\t\t\t\t\t4.夜的第七章\n");
	printf("\t\t\t\t\t\t\t5.夜曲\n");
	printf("\t\t\t\t请选择序号播放音乐：");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
	{
		mciSendString("open D:\\TestMusics\\稻香.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\稻香.mp3", NULL, 0, NULL);
		break;
	}
	case 2:
	{
		mciSendString("open D:\\TestMusics\\晴天.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\晴天.mp3", NULL, 0, NULL);
		break;
	}
	case 3:
	{
		mciSendString("open D:\\TestMusics\\手写的从前.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\手写的从前.mp3", NULL, 0, NULL);
		break;
	}
	case 4:
	{
		mciSendString("open D:\\TestMusics\\夜的第七章.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\夜的第七章.mp3", NULL, 0, NULL);
		break;
	}
	case 5:
	{
		mciSendString("open D:\\TestMusics\\夜曲.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\夜曲.mp3", NULL, 0, NULL);
		break;
	}
	default:
		break;
	}
}
void pause()
{
	mciSendString("pause D:\\TestMusics\\稻香.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\晴天.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\手写的从前.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\夜的第七章.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\夜曲.mp3", NULL, 0, NULL);
}
void resume()
{
	mciSendString("resume D:\\TestMusics\\稻香.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\晴天.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\手写的从前.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\夜的第七章.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\夜曲.mp3", NULL, 0, NULL);
}

void Draw_yinliang()
{
	char vo[20], res[260], file1[100] = "setaudio D:\\TestMusics\\稻香.mp3 to ";
	int volume = 0;
	mciSendString("status D:\\TestMusics\\稻香.mp3 volume ", res, 260, NULL);
	volume = atoi(res);
	volume -= 200;
	itoa(volume, vo, 10);
	strcat(file1, vo);
	mciSendString(file1, NULL, 0, NULL);

}
void Up_yinliang()
{
	char vo[20], res[260], file1[100] = "setaudio D:\\TestMusics\\稻香.mp3 to ";
	int volume = 0;
	mciSendString("status D:\\TestMusics\\稻香.mp3 volume", res, 260, NULL);
	volume = atoi(res);
	printf("1.%d\n", volume);
	volume += 200;
	printf("2.%d\n", volume);
	itoa(volume, vo, 10);
	strcat(file1, vo);
	mciSendString(file1, NULL, 0, NULL);
}
