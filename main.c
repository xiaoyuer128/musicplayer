#include<stdio.h>
#include <io.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>


//�û���¼ע�ắ��
char* input_PW();//��������
char* input_re_AC();//�ж��˺��Ƿ����
char* input_AC(char account[100]);//�����˺�
struct user* pre_user();//֮ǰ�ļ��е��˺�
struct user* logIn(struct user* head);//��¼
void createAC(struct user* head);//ע���˺�
void Main();//������
//���ֲ��Ų˵�����
void menu();//���ֲ˵�
void play();//��������
void pause();//��ͣ����
void resume();//�ָ�����
void Draw_yinliang();//����-
void Up_yinliang();//����+


struct user {
	int num;
	char account[100];
	char password[100];
	struct user* next;
};

char path_user[150] = "C:\\Users\\xiaoyuer\\OneDrive\\����\\userInfo.txt";  //�����û���Ϣ���ļ�
//��ȡָ���ļ��е��û���Ϣ�����������Ϣ���浽����


int main()
{
	Main();
	return 0;
}

void Main()
{
	int i;
	struct user* HEAD_USER = pre_user();
	printf("\t\t\t\t\t\t1.��¼\n\t\t\t\t\t\t2.ע��\n\t\t\t\t\t\t0.�˳�\n");
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
		printf("�������룡");
		Sleep(1000);
		exit(0);
	}
}
struct user* pre_user()
{

	FILE* fp;

	fp = fopen(path_user, "r");  //���ļ�
	if (fp == NULL)
	{
		printf("���ļ�ʧ��");//����ļ���ʧ�ܣ�\n
		return NULL;
	}

	struct user* head, * p, * q;
	int number = 1;//��¼�û�����

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

//�û���¼
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
		printf("\t\t\t\t\t\t�Ҳ����û�!!!!!!");//���"�Ҳ������û�"
		Sleep(1000);
		system("CLS");
		Main();
		return NULL;
	}

	strcpy(password, input_PW());

	if (strcmp(p->password, password) != 0) {
		printf("\t\t\t\t\t\t�������!!!!!!");//��� "�������";
		Sleep(1000);
		system("CLS");
		Main();
		return NULL;
	}
	if (strcmp(p->password, password) == 0) {
		printf("\t\t\t\t\t\t��ӭ!!!!!!");//printf"��ӭ";
		Sleep(1000);
		menu();
		return p;
	}
}

//�û�ע��
void createAC(struct user* head)
{

	FILE* fp;
	fp = fopen(path_user, "a");
	if (fp == NULL) {
		printf("���ļ�ʧ��");
	}
	else {
		char account[100];
		char password[100];
		struct user* p = NULL;
		int flag_repe = 0;//0��ʾ���û���û�кͱ����account�ظ���1��ʾ�ظ���
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
		printf("\t\t\t\t\t\tע��ɹ���!!!!!");
		Sleep(1000);
	}
}
char* input_AC(char account[100]) {
	system("CLS");
	printf("\t\t\t\t\t\t�����û���:");
	scanf("%s", account);
	return account;
}

char* input_re_AC() {
	char account[100];
	printf("\t\t\t\t\t\t�û����Ѿ�����.\n");
	scanf("%s", account);
	return account;
}

char* input_PW() {
	char password[100];
	printf("\t\t\t\t\t\t����������:");
	scanf("%s", password);
	return password;
}

//���ֲ������˵�����ϵ��

void menu()
{

	int i;
	printf("\n\t\t\t\t\t\t\t1.����\n");
	printf("\t\t\t\t\t\t\t2.��ͣ\n");
	printf("\t\t\t\t\t\t\t3.����\n");
	printf("\t\t\t\t\t\t\t4.����+\n");
	printf("\t\t\t\t\t\t\t5.����-\n");
	printf("\t\t\t\t\t\t\t6.���15s\n");
	printf("\t\t\t\t\t\t\t7.����15s\n");
	printf("\t\t\t\t\t\t\t0.�˳�\n");
	printf("\t\t\t\t\tѡ����Ĳ�����");
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
		printf("\t\t\t\t\t\t�˳�\n");
		break;

	}
	default:
		printf("\t\t\t\t\t\t�������");

	}

}
void play()//��������
{
	int i;
	system("CLS");
	printf("\t\t\t\t\t\t\t1.����\n");
	printf("\t\t\t\t\t\t\t2.����\n");
	printf("\t\t\t\t\t\t\t3.��д�Ĵ�ǰ\n");
	printf("\t\t\t\t\t\t\t4.ҹ�ĵ�����\n");
	printf("\t\t\t\t\t\t\t5.ҹ��\n");
	printf("\t\t\t\t��ѡ����Ų������֣�");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
	{
		mciSendString("open D:\\TestMusics\\����.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\����.mp3", NULL, 0, NULL);
		break;
	}
	case 2:
	{
		mciSendString("open D:\\TestMusics\\����.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\����.mp3", NULL, 0, NULL);
		break;
	}
	case 3:
	{
		mciSendString("open D:\\TestMusics\\��д�Ĵ�ǰ.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\��д�Ĵ�ǰ.mp3", NULL, 0, NULL);
		break;
	}
	case 4:
	{
		mciSendString("open D:\\TestMusics\\ҹ�ĵ�����.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\ҹ�ĵ�����.mp3", NULL, 0, NULL);
		break;
	}
	case 5:
	{
		mciSendString("open D:\\TestMusics\\ҹ��.mp3", NULL, 0, NULL);
		mciSendString("play D:\\TestMusics\\ҹ��.mp3", NULL, 0, NULL);
		break;
	}
	default:
		break;
	}
}
void pause()
{
	mciSendString("pause D:\\TestMusics\\����.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\����.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\��д�Ĵ�ǰ.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\ҹ�ĵ�����.mp3", NULL, 0, NULL);
	mciSendString("pause D:\\TestMusics\\ҹ��.mp3", NULL, 0, NULL);
}
void resume()
{
	mciSendString("resume D:\\TestMusics\\����.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\����.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\��д�Ĵ�ǰ.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\ҹ�ĵ�����.mp3", NULL, 0, NULL);
	mciSendString("resume D:\\TestMusics\\ҹ��.mp3", NULL, 0, NULL);
}

void Draw_yinliang()
{
	char vo[20], res[260], file1[100] = "setaudio D:\\TestMusics\\����.mp3 to ";
	int volume = 0;
	mciSendString("status D:\\TestMusics\\����.mp3 volume ", res, 260, NULL);
	volume = atoi(res);
	volume -= 200;
	itoa(volume, vo, 10);
	strcat(file1, vo);
	mciSendString(file1, NULL, 0, NULL);

}
void Up_yinliang()
{
	char vo[20], res[260], file1[100] = "setaudio D:\\TestMusics\\����.mp3 to ";
	int volume = 0;
	mciSendString("status D:\\TestMusics\\����.mp3 volume", res, 260, NULL);
	volume = atoi(res);
	printf("1.%d\n", volume);
	volume += 200;
	printf("2.%d\n", volume);
	itoa(volume, vo, 10);
	strcat(file1, vo);
	mciSendString(file1, NULL, 0, NULL);
}
