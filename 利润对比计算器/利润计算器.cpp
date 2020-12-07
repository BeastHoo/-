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
void grossMargin(project *p);//毛利率
double doneTotal(project* p);//成交额预估
double goalProfit(project *p,double done,double actual);//目标净利润
void profitEst(project* p);//利润预估
double visitorNeeds(project* p);  //所需访客数
double visitorCost(project* p,double vist);    //访客成本预估
double actualVisCost(project *p,double visEst);  //实际访客成本预估
void spread(project* p);
double adAva(double actual);    //每日平均广告花费
void propertion(project *p,double vis, double visCost);
void correct(project p, double goal);
/**********************************************************************/


int main()
{
	system("mode con cols=182 lines=30");
	system("color 71");
	SetConsoleTitleA("利润计算器");
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	gotoxy(50, 10);
	cout << "说明：" << endl;
	gotoxy(55, 11);
	cout << "1·使用时，每次输入都需要进行回车，若计算M组数据，则输入完M组数据之后才能进行计算" ;
	gotoxy(55, 12);
	cout << "2·完成一次计算之后，如果决定继续计算，请将本次计算结果做好记录后再继续" ;
	gotoxy(55, 13);
	cout << "3·最多可同时计算10组数据。选择输入组数时，一定要先输入数字再回车，否则会影响使用";
	gotoxy(55, 14);
	system("pause");
	system("cls");

	string a;
	float b, c, d, e, f, g, h, k, l;// POINT p;   没用
	project pro[M];
	int i, n;

	loop : int px=8, py=4;
	cout << "请输入待计算组数（≤" << M << ")"<<endl;
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|FOREGROUND_RED);
	cin >> n;
	if (n > M)
	{
		cout << "ERROR!";
		return 0;
	}
	cout << "请输入：" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 215 | FOREGROUND_GREEN);
	cout << "序号\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | FOREGROUND_BLUE);
	cout << "目标关键词\t" ;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_GREEN);
	cout << "访客成本预估\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 | FOREGROUND_RED);
	cout << "客单价\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 180 | FOREGROUND_RED);
	cout << "转化率(%)\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249 | FOREGROUND_BLUE);
	cout << "访客数量预估\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 42 | FOREGROUND_BLUE);
	cout << "产品成本\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 199 | FOREGROUND_GREEN);
	cout << "免费流量对冲预估(%)\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 228 | FOREGROUND_GREEN);
	cout << "平台佣金(%)\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 91 | FOREGROUND_GREEN);
	cout << "邮寄成本\t";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 142 | FOREGROUND_RED);
	cout << "包装-邮寄成本"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wOldColorAttrs);
	for (i = 0; i < n; i++)
	{
		//cin >> a  >> b >> c >> d >> e >> f >> g >> h >> k >> l;
		//GetCursorPos(&p);	              这个函数得到的鼠标的在整个屏幕的坐标，从屏幕的左上角开始，像素为单位                       //cout << p.x <<" "<< p.y;
		
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
	cout << "序号" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | FOREGROUND_BLUE);
	cout << "目标净利润(万)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_GREEN);
	cout << "成交额预估(万)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160 | FOREGROUND_RED);
	cout << "利润预估(万)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 180 | FOREGROUND_RED);
	cout << "毛利率" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249 | FOREGROUND_BLUE);
	cout << "所需访客数(万)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 42 | FOREGROUND_BLUE);
	cout << "访客总成本预估(万)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 199 | FOREGROUND_GREEN);
	cout << "实际访客成本预估(万)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 228 | FOREGROUND_GREEN);
	cout << "平均每天广告花费(万)" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 91 | FOREGROUND_GREEN);
	cout << "推广费占比" << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 142 | FOREGROUND_RED);
	cout << "投入产出比"<<"  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | FOREGROUND_RED);
	cout << "目标利润修正(万)" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wOldColorAttrs);

	char ins;
	py += 3; px = 6; double vis, visCost, actual,ava,done ,goal;
	for (i = 0; i < n; i++)
	{
		cout << i+1;
        px = 26;
		//函数
		gotoxy(px, py);done= doneTotal(&pro[i]); px += 17;
		gotoxy(px, py); profitEst(&pro[i]); px += 10;//函数
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

	cout << "\n\n\n是否继续计算？Esc退出，任意键继续";
	ins = _getch();
	switch (ins)
	{
	case 27:
		cout << "已停止运行";
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

void grossMargin(project *p)   //毛利率
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