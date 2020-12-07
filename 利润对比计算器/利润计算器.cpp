//@author Hyq
//Version 1.0
//date 20/5/12
#include"user.h"
#define M 10
#define _CRT_SECURE_NO_WARNINGS

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coord);
}

/**************************************************************************/


void resultShow(project* p);
void grossMargin(project *p);//ë����
double doneTotal(project* p);//�ɽ���Ԥ��
double goalProfit(project *p,double done,double actual);//Ŀ�꾻����
void profitEst(project* p);//����Ԥ��
double visitorNeeds(project* p);  //����ÿ���
double visitorCost(project* p,double vist);    //�ÿͳɱ�Ԥ��
double actualVisCost(project *p,double visEst);  //ʵ�ʷÿͳɱ�Ԥ��
void spread(project* p);
double adAva(double actual);    //ÿ��ƽ����滨��
void propertion(project *p,double vis, double visCost);
void correct(project p, double goal);
/**********************************************************************/


int main()
{
	system("mode con cols=182 lines=30");
	system("color 71");
	SetConsoleTitleA("���������");
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	gotoxy(50, 10);
	cout << "˵����" << endl;
	gotoxy(55, 11);
	cout << "1��ʹ��ʱ��ÿ�����붼��Ҫ���лس���������M�����ݣ���������M������֮����ܽ��м���" ;
	gotoxy(55, 12);
	cout << "2�����һ�μ���֮����������������㣬�뽫���μ��������ü�¼���ټ���" ;
	gotoxy(55, 13);
	cout << "3������ͬʱ����10�����ݡ�ѡ����������ʱ��һ��Ҫ�����������ٻس��������Ӱ��ʹ��";
	gotoxy(55, 14);
	system("pause");
	system("cls");

	string a;
	float b, c, d, e, f, g, h, k, l;// POINT p;   û��
	project pro[M];
	int i, n;

	loop : int px=8, py=4;
	cout << "�������������������" << M << ")"<<endl;
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|FOREGROUND_RED);
	cin >> n;
	if (n > M)
	{
		cout << "ERROR!";
		return 0;
	}
	cout << "�����룺" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 215 | FOREGROUND_GREEN);
	cout << "���\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Ŀ��ؼ���\t" ;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_GREEN);
	cout << "�ÿͳɱ�Ԥ��\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 | FOREGROUND_RED);
	cout << "�͵���\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 180 | FOREGROUND_RED);
	cout << "ת����(%)\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249 | FOREGROUND_BLUE);
	cout << "�ÿ�����Ԥ��\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 42 | FOREGROUND_BLUE);
	cout << "��Ʒ�ɱ�\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 199 | FOREGROUND_GREEN);
	cout << "��������Գ�Ԥ��(%)\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 228 | FOREGROUND_GREEN);
	cout << "ƽ̨Ӷ��(%)\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 91 | FOREGROUND_GREEN);
	cout << "�ʼĳɱ�\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 142 | FOREGROUND_RED);
	cout << "��װ-�ʼĳɱ�"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wOldColorAttrs);
	for (i = 0; i < n; i++)
	{
		//cin >> a  >> b >> c >> d >> e >> f >> g >> h >> k >> l;
		//GetCursorPos(&p);	              ��������õ���������������Ļ�����꣬����Ļ�����Ͻǿ�ʼ������Ϊ��λ                       //cout << p.x <<" "<< p.y;
		
		cout << i + 1; gotoxy(px, py);	px += 16;
		cin >> a; 	gotoxy(px,py );	px += 16;                                      //cout << p.x <<" "<< p.y;
		cin >> b;  gotoxy(px, py);	px += 8;
		cin >> c; gotoxy(px, py);	px += 16;
		cin >> d; gotoxy(px, py);	px += 16;
		cin >> e; gotoxy(px, py);	px += 23;
		cin >> f; gotoxy(px, py);	px += 22;
		cin >> g; gotoxy(px, py);	px += 14;
		cin >> h; gotoxy(px, py);	px += 16;
		cin >> k; gotoxy(px, py);	px += 23;
		cin >> l; gotoxy(px, py);	py += 1; px = 8;
		pro[i].Set(a, b, c, d, e, f, g, h, k, l); cout << "\n";
	}
	cout << "\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 215 | FOREGROUND_GREEN);
	cout << "���" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Ŀ�꾻����(��)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_GREEN);
	cout << "�ɽ���Ԥ��(��)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 | FOREGROUND_RED);
	cout << "����Ԥ��(��)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 180 | FOREGROUND_RED);
	cout << "ë����" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249 | FOREGROUND_BLUE);
	cout << "����ÿ���(��)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 42 | FOREGROUND_BLUE);
	cout << "�ÿ��ܳɱ�Ԥ��(��)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 199 | FOREGROUND_GREEN);
	cout << "ʵ�ʷÿͳɱ�Ԥ��(��)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 228 | FOREGROUND_GREEN);
	cout << "ƽ��ÿ���滨��(��)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 91 | FOREGROUND_GREEN);
	cout << "�ƹ��ռ��" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 142 | FOREGROUND_RED);
	cout << "Ͷ�������"<<"  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | FOREGROUND_RED);
	cout << "Ŀ����������(��)" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wOldColorAttrs);

	char ins;
	py += 3; px = 6; double vis, visCost, actual,ava,done ,goal;
	for (i = 0; i < n; i++)
	{
		cout << i+1;
        px = 26;
		//����
		gotoxy(px, py);done= doneTotal(&pro[i]); px += 17;
		gotoxy(px, py); profitEst(&pro[i]); px += 10;//����
		gotoxy(px, py); grossMargin(&pro[i]); px += 11;
		gotoxy(px, py);vis = visitorNeeds(&pro[i]); px += 18;
		gotoxy(px, py);visCost = visitorCost(&pro[i], vis); px += 21;
		gotoxy(px, py);actual= actualVisCost(&pro[i], visCost); px += 22;
		gotoxy(px, py);ava=adAva(actual); px += 18;
		gotoxy(px, py); spread(&pro[i]); px += 14;
		gotoxy(10, py);goal= goalProfit(&pro[i], done, actual);
		gotoxy(px, py); propertion(&pro[i], vis, visCost); px += 14;
		gotoxy(px, py); correct(pro[i], goal);
		py += 1;
	}

	cout << "\n\n\n�Ƿ�������㣿Esc�˳������������";
	ins = _getch();
	switch (ins)
	{
	case 27:
		cout << "��ֹͣ����";
		break;
	default:
		system("cls");
		goto loop;
		break;
	}

	return 0;
}


/*****************************************************************************************************************/


project::project()
{
	name = 'xxx';	visEst = 0;	singlePrice = 0;	transRate = 0;	marEst = 0;
	proCost = 0;	collision = 0;	platCost = 0;	deliver = 0;	labCost = 0;
}


project::~project()
{
	
}

void project::Set(string a,float b,float c,float d,float e,float f,float g,float h,float k,float l)
{
	name = a;	visEst = b;	singlePrice = c;	transRate = d;	marEst = e;
	proCost = f;	collision = g;	platCost = h;	deliver = k;	labCost = l;
}

void resultShow(project* p)
{
	//grossMargin(p);
}

void grossMargin(project *p)   //ë����
{
	double rate;
	float m, n;
	m = p->_singlePrice();
	n = p->_proCost();
	rate = (m - n) / m;
	printf("%.2lf", rate * 100); cout << "%";
}

double doneTotal(project* p)   
{
	printf("%4.2f\t", p->_singlePrice());
	return (double)p->_singlePrice() * 10000;
}

double goalProfit(project* p, double done, double actual)
{
	double goal;
	goal = done * (1 -((double) p->_platCost()/100)) - (actual*10000) - ((double)p->_proCost() * (double)p->_marEst());
	printf("%.2lf", goal/10000);
	return goal;

}

void profitEst(project* p)
{
	printf("%4.2lf", (double)p->_singlePrice() -(double) p->_proCost());

}

double visitorNeeds(project* p)
{
	double Rate = (double)p->_transRate() / 100;
	double needs;
	needs = (double)p->_marEst() / Rate;
	printf("%.2lf", needs/10000);
	return needs;
}

double visitorCost(project* p,double vist)
{
	double cosEst;
	cosEst = vist / 10000 * (p->_visEst());
	printf("%.2lf", cosEst);
	return cosEst;
}

double actualVisCost(project* p, double visEst)
{
	double actual,freeCollision;
	freeCollision = p->_collision() / 100;

	actual = visEst * (1 - freeCollision);
	printf("%.2lf", actual);
	return actual;
}

void spread(project* p)
{
	printf("%.2lf", 100 - (double)p->_collision()); cout << "%";

}

double adAva(double actual)
{
	printf("%.2lf", actual / 30);
	return actual / 30;
}

void propertion(project* p, double vis, double visCost)
{
	double s,ss;
	s = (double)p->_singlePrice() * ((double)p->_transRate()/100);
	ss = visCost*10000 / vis;
	printf("%.2lf",s/ ss);
}


void correct(project p, double goal)
{
	double co;
	co =goal- ((double)p._labCost() + (double)p._deliver()) * p._marEst();
	printf("%.2lf", co / 10000);
}