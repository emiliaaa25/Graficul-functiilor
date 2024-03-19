#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include<winbgim.h>
#include<string.h>
#include<math.h>

#define INFINIT 100000
#define NMAX 200
#define EPSILON 0.0001

using namespace std;

double MIN,MAX;
double minim, maxim;
char fun[256];
char capatst[256];
char capatdr[256];
char temp[256];
int STANGA=250, DREAPTA=1100, TOP=150, BOTTOM=600;
char vect[256];
int k,k2,v[50], contorev,pozitiei=0, pozitiest=0, pozitiedr=0;

struct nod{
    double info;
    char inf;
    nod *urm;
};

nod *infixata,*postfixata,*S,*p,*varf,*prim,*ultim;

//stive:
void push(nod *&varf, char element);
void push2(nod *&varf, double element);
void pop(nod *&varf );
bool esteVidaS(nod *&Stiva);
void stivaVida(nod *&S);

//cozi:
void eliminare(nod *&postfixata);
void inserare(nod *&postfixata, char element);
bool esteVidaC(nod *&prim);
void coadaVida(nod *&prim);

//dimensiuni:
void fullscreen(int &width, int &height);


//ferestre:
void fereastra_cu_graficul_desenat(double A, double B,int ok, int poza,int limba,int culoarerama, int culoaregrafic);
void fereastra_de_alegeri(int width, int height);
void fereastra_principala(int width, int height,int ok,int poza,int limba);
void fereastra_Grafic(int width, int height,int ok,int poza,int limba);
void fereastra_Informatii(int width, int height,int ok,int poza,int limba);
void explicatii_grafic(int width,int height,int limba);
void buton_iesire(int width, int height);
void buton_inapoi(int width, int height);


//click:
void click(int &coordxclick, int &coordyclick );
void schimbare_sunet(int ok);
void schimbare_culoare_buton(int a, int b, int c, int d);
void click_pe_Grafic(double &A, double &B, int width, int height,int ok,int poza,int limba,int culoarerama, int culoaregrafic);
void click_pe_Informatii(double A, double B,int width, int height,int ok,int poza,int limba,int culoarerama, int culoaregrafic);
void click_pe_fereastra_pr(double A, double B,int ok, int poza,int &limba,int culoarerama, int culoaregrafic);
void caseta_text_functie(int width, int height,int ok);
void caseta_text_capat_stanga(int width, int height,double &A,int ok);
void caseta_text_capat_dreapta(int width, int height,double &A,double &B,int ok);
void click_pe_fereastra_de_alegeri(double A, double B, int &ok, int &poza, int &limba, int &culoarerama, int &culoaregrafic);
void click_back_grafic(double A, double B, int width, int height,int ok,int poza,int limba,int culoarerama, int culoaregrafic);


//functie:
double functie(double x);
double calculare_integrala_functiei(double A, double B, double(*f)(double));
bool discontinuitate(double x);
void aflare_min_si_max();
void aflare_min_max_din_interval(double A, double B, double &minim, double &maxim);
void desenare_grafic_functie(double A, double B, int culoarefunctie,int culoarerama);
void redesenare_grafic(double A, double B, int widget,int height,int ok,int poza,int limba,int culoarerama, int culoaregrafic);
double operatie (char r, double x, double y);
double operatie_speciala (char r, double x);
int prioritate_caracter(char a);
void transformare_functie();
void transformare_din_infix_in_postinfx();
double calculare_f_din_postf(double x);


//evaluator:
void evaluator();
void evaluare_interval(int width, int height,double A, double B,int limba);
void mesaj_evaluator(int width, int height,int limba);


//axe
void desenare_axe(double A, double B);


//asimptote
double asimptota_orizontala();
double asimptota_verticala();
void desenare_asimptote(double A, double B);

int main()
{
    int height, width;
    char capatst[257],capatdr[257];
    int ok=1;
    int poza=1;
    int limba=1;
    int culoarerama=1;
    int culoaregrafic=1;
    double A,B;
    fun[0]='\0';
    capatst[0]='\0';
    capatst[0]='\0';
    A=B=0;
    fullscreen(width, height);
    fereastra_de_alegeri(width,height);
    click_pe_fereastra_de_alegeri(A,B,ok,poza,limba,culoarerama,culoaregrafic);
    getch();
    closegraph();
    return 0;
}

//stive
void push(nod *&varf, char element)
{
nod *Stiva;
Stiva=new nod;
Stiva->inf=element;
Stiva->urm = varf;
varf=Stiva;
}

void push2(nod *&varf, double element)
{
nod *Stiva;
Stiva=new nod;
Stiva->info=element;
Stiva->urm = varf;
varf=Stiva;
}

void pop(nod *&varf )
{
    nod *Stiva=varf;
    varf=varf->urm;
    delete Stiva;

}

bool esteVidaS(nod *&Stiva)//stiva
{
    if(Stiva==NULL)return 1;
        else return 0;
}

void stivaVida(nod *&S)
{
    S=NULL;
}


//cozi
void eliminare(nod *&postfixata)
{
    nod *q;
    q=postfixata;
    postfixata=postfixata->urm;
    delete q;
 }

void inserare(nod *&postfixata, char element)
{
  nod *q =new nod;
  q->inf=element;
  q->urm=NULL;
  if(postfixata==NULL)
    postfixata=q;
  else
  {
    nod *p=postfixata;
    while(p->urm!=NULL)
      p=p->urm;
    p->urm=q;
  }
}

bool esteVidaC(nod *&prim)//coada
{
    if(prim==NULL)
    return 1;
else
    return 0;
}

void coadaVida(nod *&prim)
{
    prim=NULL;
}


//dimensiuni:
void fullscreen(int &width, int &height)
{
    height=GetSystemMetrics(SM_CYSCREEN);
    width=GetSystemMetrics(SM_CXSCREEN);
}


//ferestre
void fereastra_de_alegeri(int width, int height)
{
    initwindow(width,height,"Fereastra principala",-4,-4);
    readimagefile("image1_1.jpg",0,0,width,height);//imagine de fundal

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 8 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    char t[256];
    strcpy(t,"Alegeti:");
    outtextxy(width/2,height/4,t);

    buton_iesire(width, height);

    setfillstyle(0,BLACK);
    bar(width/10,height/3,width/10+200,height/3+200);//fundal
    readimagefile("image1_1.jpg",width/10+50,height/3+10,width/10+150,height/3+80);//imagine de fundal
    readimagefile("Backgrf.jpg",width/10+50,height/3+110,width/10+150,height/3+180);//imagine de fundal

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 2 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Poza fundal");
    outtextxy(width/10+100,height/3+230,t);

    bar(width/10+440,height/3,width/10+640,height/3+200);//limba
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Romana");
    outtextxy(width/10+540,height/3+60,t);
    rectangle(width/10+470,height/3+40,width/10+615,height/3+70);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"English");
    outtextxy(width/10+540,height/3+140,t);
    rectangle(width/10+470,height/3+120,width/10+615,height/3+150);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Limba");
    outtextxy(width/10+545,height/3+230,t);

    bar(width/10+220,height/3,width/10+420,height/3+200);//sunet
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 2 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t," Sunet inchis");
    outtextxy(width/10+315,height/3+60,t);
    rectangle(width/10+245,height/3+40,width/10+400,height/3+70);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 2 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Sunet deschis");
    outtextxy(width/10+319,height/3+140,t);
    rectangle(width/10+240,height/3+120,width/10+400,height/3+150);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Sunet");
    outtextxy(width/10+310,height/3+230,t);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t," OK! ");
    outtextxy(width/2,height/2+250,t);
    rectangle(width/2-52,height/2+226,width/2+50,height/2+260);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR,  2);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Culori rama");
    outtextxy(width/10+760,height/3+230,t);
    strcpy(t,"grafic");
    outtextxy(width/10+760,height/3+250,t);

    bar(width/10+660,height/3,width/10+860,height/3+200);

    //culori rama
    setfillstyle(1,RED);
    bar(width/10+680,height/3+40,width/10+750,height/3+90);
    setfillstyle(1,YELLOW);
    bar(width/10+770,height/3+40,width/10+840,height/3+90);
    setfillstyle(1,CYAN);
    bar(width/10+680,height/3+110,width/10+750,height/3+160);
    setfillstyle(1,GREEN);
    bar(width/10+770,height/3+110,width/10+840,height/3+160);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR,  2);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Culori grafic");
    outtextxy(width/10+980,height/3+230,t);

    setfillstyle(1,BLACK);
    bar(width/10+880,height/3,width/10+1080,height/3+200);

    //culori grafic
    setfillstyle(1,RED);
    bar(width/10+900,height/3+40,width/10+970,height/3+90);
    setfillstyle(1,YELLOW);
    bar(width/10+990,height/3+40,width/10+1060,height/3+90);
    setfillstyle(1,CYAN);
    bar(width/10+900,height/3+110,width/10+970,height/3+160);
    setfillstyle(1,GREEN);
    bar(width/10+990,height/3+110,width/10+1060,height/3+160);

    buton_iesire(width, height);
}

void fereastra_cu_graficul_desenat(double A, double B,int ok, int poza, int limba,int culoarerama,int culoaregrafic)
{
    int height, width;

    height=GetSystemMetrics(SM_CYSCREEN);
    width=GetSystemMetrics(SM_CXSCREEN);

    initwindow(width,height,"Fereastra",-4,-4);

    if(culoarerama==1)setcolor(RED);
        else if(culoarerama==2)setcolor(YELLOW);
        else if(culoarerama==3)setcolor(CYAN);
        else if(culoarerama==4)setcolor(GREEN);

    rectangle(STANGA,TOP,DREAPTA,BOTTOM);

    setcolor(DARKGRAY);
    desenare_axe(A,B);

    if(culoaregrafic==1)setcolor(RED);
        else if(culoaregrafic==2)setcolor(YELLOW);
        else if(culoaregrafic==3)setcolor(CYAN);
        else if(culoaregrafic==4)setcolor(GREEN);

    redesenare_grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);//graficul efectiv
}

void fereastra_principala(int width, int height,int ok, int poza,int limba)
{
    char t[256];
    initwindow(width,height,"Fereastra principala",-4,-4);
    if(poza==1)
        readimagefile("image1_1.jpg",0,0,width,height);//imagine de fundal
    else
        readimagefile("Backgrf.jpg",0,0,width,height);//imagine de fundal

    if(ok==1)
    {
        readimagefile("sunetdeschis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);//sunet
        PlaySound("sound2.wav",NULL,SND_ASYNC);//sunet de fundal
    }
    else
    {
        readimagefile("sunetinchis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);
        PlaySound(NULL,0,0);
    }

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 8 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    if(limba==1)
    {
        strcpy(t,"Graficul functiei");
        outtextxy(width/2,height/4,t);//setari titlu
    }
        else {
                strcpy(t,"Function's graphic");
                outtextxy(width/2,height/4,t);//setari titlu
            }

    settextstyle(8, HORIZ_DIR, 6);
    if(limba==1)
        {
            strcpy(t,"Grafic");
            outtextxy(width/2,height/2,t);
            rectangle(width/2-100,height/2-40,width/2+98,height/2+12);//setari a doua linie de text
        }
        else {
                strcpy(t,"Graphic");
                outtextxy(width/2,height/2,t);
                rectangle(width/2-119,height/2-40,width/2+118,height/2+12);//setari a doua linie de text
            }

    if(limba==1)
        {
            settextstyle(8, HORIZ_DIR, 6);
            strcpy(t,"Informatii");
            outtextxy(width/2,height/2+150,t);
            rectangle(width/2-168,height/2+110,width/2+165,height/2+165);
        }
        else {
                settextstyle(8, HORIZ_DIR, 6);
                strcpy(t,"Information");
                outtextxy(width/2,height/2+150,t);
                rectangle(width/2-185,height/2+110,width/2+183,height/2+165);
        }

    buton_iesire(width, height);
}

void fereastra_Grafic(int width, int height,int ok,int poza,int limba)
{
    char t[256];
    initwindow(width,height,"Fereastra",-4,-4);

    if(poza==1)
        readimagefile("image1_1.jpg",0,0,width,height);//imagine de fundal
    else
        readimagefile("Backgrf.jpg",0,0,width,height);//imagine de fundal

    if(ok==1)
    {
        readimagefile("sunetdeschis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);//sunet
        PlaySound("sound2.wav",NULL,SND_ASYNC);//sunet de fundal
    }
    else
    {
        readimagefile("sunetinchis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);
        PlaySound(NULL,0,0);
    }

    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    if(limba==1)
        {
            strcpy(t,"Introduceti intervalul aici:");
            outtextxy(width/2+10,height/4-40,t);
        }
        else   {
                strcpy(t,"Write the interval:");
                outtextxy(width/2+10,height/4-40,t);
                }

    setfillstyle(0,BLACK);
    bar(width/2-320,height/4-10,width/4+320,height/4+50);//stanga
    bar(width/4+340,height/4-10,width/4+655,height/4+50);//dreapta

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    if(limba==1)
    {
        strcpy(t,"Stanga:");
        outtextxy(width/2-400,height/4+33,t);
    }
        else {
                strcpy(t,"Left:");
                outtextxy(width/2-395,height/4+33,t);
            }

    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);

     if(limba==1) {
                    strcpy(t,":Dreapta");
                    outtextxy(width/2+400,height/4+33,t);
                    }
        else {
                strcpy(t,":Right");
                outtextxy(width/2+400,height/4+33,t);
            }

    rectangle(width/2-320,height/4-10,width/4+320,height/4+50);//stanga
    rectangle(width/4+340,height/4-10,width/4+655,height/4+50);//dreapta

    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    if(limba==1) {
                strcpy(t,"Introduceti functia aici:");
                outtextxy(width/2,height/3+40,t);
                }
        else   {
                strcpy(t,"Write the funtion");
                outtextxy(width/2,height/3+40,t);
                }

    setfillstyle(0,BLACK);
    bar(width/2-320,height/3+70,width/4+655,height/3+130);//introducere functie
    setcolor(WHITE);
    rectangle(width/2-320,height/3+70,width/4+655,height/3+130);//introducere functie

    settextstyle(8, HORIZ_DIR, 4);
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    if(limba==1){
                strcpy(t,"Evaluator functie");
                outtextxy(width/2,height/2+35,t);
                }
        else {
                strcpy(t,"Function evaluation");
                outtextxy(width/2,height/2+35,t);
            }

    setfillstyle(0,BLACK);
    bar(width/2-550,height/2+70,width/2+550,height/2+250);//evaluator
    setcolor(WHITE);
    rectangle(width/2-550,height/2+70,width/2+550,height/2+250);//evaluator
    settextstyle(8, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    strcpy(t," OK! ");
    outtextxy(width/2+500,height/2,t);//buton spre functie
    setcolor(WHITE);
    rectangle(width/2+460,height/2-18,width/2+540,height/2+7);

    setcolor(WHITE);
    buton_inapoi(width, height);
    buton_iesire(width, height);
}

void fereastra_Informatii(int width, int height,int ok,int poza,int limba)
{
    char t[256];
    initwindow(width,height,"Fereastra",-4,-4);

    if(poza==1)
        readimagefile("image1_1.jpg",0,0,width,height);//imagine de fundal
    else
        readimagefile("Backgrf.jpg",0,0,width,height);//imagine de fundal

    if(ok==1)
    {
        readimagefile("sunetdeschis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);//sunet
        PlaySound("sound2.wav",NULL,SND_ASYNC);//sunet de fundal
    }
    else
    {
        readimagefile("sunetinchis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);
        PlaySound(NULL,0,0);
    }

    settextstyle(8, HORIZ_DIR, 4);
    if(limba==1)
        {
            strcpy(t,"Proiectul a fost realizat de:");
            outtextxy(width/2-600,height/2-200,t);//text 1
            }
        else  {
                strcpy(t,"The project was made by:");
                outtextxy(width/2-600,height/2-200,t);//text 1
        }

    settextstyle(8, HORIZ_DIR, 4);

    strcpy(t,"Ursache Ana-Maria");
    outtextxy(width/2-530,height/2-70,t);//text 2

    settextstyle(8, HORIZ_DIR, 4);
    if(limba==1)
        {
            strcpy(t,"si");
            outtextxy(width/2-380,height/2+8,t);//text 3
        }
        else {
                strcpy(t,"and");
                outtextxy(width/2-380,height/2+8,t);//text 3
        }

    settextstyle(8, HORIZ_DIR, 4);

    strcpy(t,"Galatanu Emilia");
    outtextxy(width/2-510,height/2+80,t);//text 4

    setfillstyle(0,BLACK);
    bar(width/2,height/2-200,width-100,height-150);
    setcolor(WHITE);
    rectangle(width/2,height/2-200,width-100,height-150);

    if(limba==1)
                {
                    strcpy(t,"Informatii suplimentare:");
                    outtextxy(width/2+52,height/2-150,t);
                }
            else {
                    strcpy(t,"More information:");
                    outtextxy(width/2+52,height/2-150,t);
                }

    if(limba==1)
                {
                    settextstyle(8, HORIZ_DIR, 2);
                    strcpy(t,"-Functiile trigonometrice se vor scrie cu");
                    outtextxy(width/2+32,height/2-80,t);
                    }
            else {
                    settextstyle(8, HORIZ_DIR, 2);
                    strcpy(t,"-Trigonometric functions will be written");
                    outtextxy(width/2+32,height/2-80,t);
            }
    if(limba==1)
                {
                    strcpy(t,"cu paranteze rotunde.");
                    outtextxy(width/2+32,height/2-50,t);
                    }
            else {
                    strcpy(t,"with round brackets.");
                    outtextxy(width/2+32,height/2-50,t);
            }

    strcpy(t,"ex: sin(x), cos(2*x).");
    outtextxy(width/2+32,height/2-20,t);

    if(limba==1)
                {
                    strcpy(t,"-Singura variabila pe care o puteti");
                    outtextxy(width/2+32,height/2+40,t);
                    }
            else {
                    strcpy(t,"-The only variable you can");
                    outtextxy(width/2+32,height/2+40,t);
            }
    if(limba==1)
                {
                    strcpy(t,"utiliza este variabila x.");
                    outtextxy(width/2+32,height/2+70,t);
                    }
            else {
                    strcpy(t,"use is variable x.");
                    outtextxy(width/2+32,height/2+70,t);
            }
    if(limba==1)
                {
                    strcpy(t,"-Se pot folosi doar functiile:");
                    outtextxy(width/2+32,height/2+130,t);
                    }
            else {
                    strcpy(t,"-Only the following functions that can");
                    outtextxy(width/2+32,height/2+130,t);
            }
    if(limba==1)
                {
                    strcpy(t,"sin, cos, log, tg, rad.");
                    outtextxy(width/2+32,height/2+160,t);
                    }
            else {
                    strcpy(t,"be used: sin, cos, log, tg, rad.");
                    outtextxy(width/2+32,height/2+160,t);
            }

    setcolor(WHITE);
    buton_inapoi(width, height);
    buton_iesire(width, height);
}

void explicatii_grafic(int width, int height, int limba)
{
    char t[256];
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 2 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    if(limba==1)
    {
        strcpy(t,"w/UP: Zoom in");
        outtextxy(width/2+550,height/4+130,t);
        strcpy(t,"s/DOWN: Zoom out");
        outtextxy(width/2+550,height/4+160,t);
        strcpy(t,"a/<-: Stanga");
        outtextxy(width/2+550,height/4+190,t);
        strcpy(t,"d/->: Dreapta");
        outtextxy(width/2+550,height/4+220,t);
    }
        else  {
                strcpy(t,"w/UP: Zoom in");
                outtextxy(width/2+550,height/4+130,t);
                strcpy(t,"s/DOWN: Zoom out");
                outtextxy(width/2+550,height/4+160,t);
                strcpy(t,"a/<-: Left");
                outtextxy(width/2+550,height/4+190,t);
                strcpy(t,"d/->: Right");
                outtextxy(width/2+550,height/4+220,t);
        }
}


void buton_iesire(int width, int height)
{
    char t[256];
    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Exit");
    outtextxy(width/16+10,height/5-120,t);//setari pentru formare buton exit
    rectangle(width/16-31,height/5-145,width/10,height/5-114);
}

void buton_inapoi(int width, int height)
{
    char t[256];
    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Back");
    outtextxy(width/10+51,height/5-120,t);//setari pentru formare buton back
    rectangle(width/10+10,height/5-145,width/10+90,height/5-114);
}


//click-uri
void click(int &coordxclick, int &coordyclick )
{
    int x, y;
    while(!ismouseclick(WM_LBUTTONDOWN))
        delay(20);
    getmouseclick(WM_LBUTTONDOWN, x, y);
    coordxclick=x;
    coordyclick=y;
}

void schimbare_sunet(int ok)
{
    PlaySound("sunet_buton.wav",NULL,SND_ASYNC);
    delay(100);
    if(ok==1)
        PlaySound("sound2.wav",NULL,SND_ASYNC);
}

void schimbare_culoare_buton(int a, int b, int c, int d)
{
    setcolor(YELLOW);
    rectangle(a,b,c,d);
    delay(120);
    setcolor(WHITE);
    rectangle(a,b,c,d);
}

void click_pe_fereastra_de_alegeri(double A, double B, int &ok, int &poza,int &limba, int &culoarerama, int &culoaregrafic)
{
    int coordx, coordy;
    int a,b,c,d;
    int height, width;
    fullscreen(width,height);
    if(ok==1)
        PlaySound("sound2.wav",NULL,SND_ASYNC);
    while(true)
    {

    click(coordx,coordy);
    if(coordx>=(width/2-52)&&coordx<=(width/2+50)&&coordy>=(height/2+226)&&coordy<=(height/2+260))//click pe ok
        {
            a=width/2-52; b=height/2+226; c=width/2+50; d=height/2+260;
            schimbare_culoare_buton(a,b,c,d);
            rectangle(a,b,c,d);
            schimbare_sunet(ok);
            closegraph();
            fereastra_principala(width,height,ok,poza,limba);
            click_pe_fereastra_pr(A,B,ok,poza,limba,culoarerama,culoaregrafic);
        }
    else if(coordx>=width/16-31&&coordx<=width/10&&coordy>=height/5-145&&coordy<=height/5-114)//click pe exit
        {
            a=width/16-31; b=height/5-145; c=width/10; d=height/5-114;
            schimbare_culoare_buton(a,b,c,d);
            rectangle(a,b,c,d);
            schimbare_sunet(ok);
            exit(1);
        }
    else if(coordx>=(width/10+245)&&coordx<=(width/10+400)&&coordy>=(height/3+40)&&coordy<=(height/3+70))//sunet inchis
        {
            a=width/10+245; b=height/3+40; c=width/10+400; d=height/3+70;
            schimbare_culoare_buton(a,b,c,d);
            rectangle(a,b,c,d);
            schimbare_sunet(ok);
            PlaySound(NULL,0,0);
            ok=0;
        }
     else if(coordx>=(width/10+240)&&coordx<=(width/10+400)&&coordy>=(height/3+120)&&coordy<=(height/3+150))//sunet deschis
        {
            a=width/10+240; b=height/3+120; c=width/10+400; d=height/3+150;
            schimbare_culoare_buton(a,b,c,d);
            rectangle(a,b,c,d);
            schimbare_sunet(ok);
            PlaySound("sound2.wav",NULL,SND_ASYNC);//sunet de fundal
            ok=1;
        }
    else if(coordx>=(width/10+50)&&coordx<=(width/10+150)&&coordy>=(height/3+10)&&coordy<=(height/3+80))//poza mate
        {
            a=width/10+50; b=height/3+10; c=width/10+150; d=height/3+80;
            schimbare_sunet(ok);
            poza=1;
        }
    else if(coordx>=(width/10+50)&&coordx<=(width/10+150)&&coordy>=(height/3+110)&&coordy<=(height/3+180))//poza craciun
        {
            a=width/10+50; b=height/3+110; c=width/10+150; d=height/3+180;
            schimbare_sunet(ok);
            poza=0;
        }
    else if(coordx>=(width/10+470)&&coordx<=(width/10+615)&&coordy>=(height/3+40)&&coordy<=(height/3+70))//buton romana
    {
        a=width/10+470; b=height/3+40; c=width/10+615; d=height/3+70;
        schimbare_culoare_buton(a,b,c,d);
        rectangle(a,b,c,d);
        schimbare_sunet(ok);
        limba=1;
    }

    else if(coordx>=(width/10+470)&&coordx<=(width/10+615)&&coordy>=(height/3+120)&&coordy<=(height/3+150))//buton engleza
    {
        a=width/10+470; b=height/3+120; c=width/10+615; d=height/3+150;
        schimbare_culoare_buton(a,b,c,d);
        rectangle(a,b,c,d);
        schimbare_sunet(ok);
        limba=0;
    }
    else if(coordx>=(width/10+680)&&coordx<=(width/10+750)&&coordy>=(height/3+40)&&coordy<=(height/3+90))//rama rosu
        {
        schimbare_sunet(ok);
        culoarerama=1;
        }
    else if(coordx>=(width/10+770)&&coordx<=(width/10+840)&&coordy>=(height/3+40)&&coordy<=(height/3+90))//rama galben
    {
        schimbare_sunet(ok);
        culoarerama=2;
    }
    else if(coordx>=(width/10+680)&&coordx<=(width/10+750)&&coordy>=(height/3+110)&&coordy<=(height/3+160))//rama cyan
    {
        schimbare_sunet(ok);
        culoarerama=3;
    }
    else if(coordx>=(width/10+770)&&coordx<=(width/10+840)&&coordy>=(height/3+110)&&coordy<=(height/3+160))//rama verde
    {
        schimbare_sunet(ok);
        culoarerama=4;
    }

    else if(coordx>=(width/10+900)&&coordx<=(width/10+970)&&coordy>=(height/3+40)&&coordy<=(height/3+90))//functie rosu
        {
        schimbare_sunet(ok);
        culoaregrafic=1;
    }
    else if(coordx>=(width/10+990)&&coordx<=(width/10+1060)&&coordy>=(height/3+40)&&coordy<=(height/3+90))//functie galben
    {
        schimbare_sunet(ok);
        culoaregrafic=2;
    }
    else if(coordx>=(width/10+900)&&coordx<=(width/10+970)&&coordy>=(height/3+110)&&coordy<=(height/3+160))//functie cyan
    {
        schimbare_sunet(ok);
        culoaregrafic=3;
    }
    else if(coordx>=(width/10+990)&&coordx<=(width/10+1060)&&coordy>=(height/3+110)&&coordy<=(height/3+160))//functie verde
    {
        schimbare_sunet(ok);
        culoaregrafic=4;
    }
    }
}

void click_pe_fereastra_pr(double A, double B, int ok, int poza, int &limba,int culoarerama, int culoaregrafic)
{
    int coordx, coordy;
    int a,b,c,d;
    int height, width;
    fullscreen(width,height);

    while(true)
    {

    click(coordx,coordy);
    if(coordx>=width/16-31&&coordx<=width/10&&coordy>=height/5-145&&coordy<=height/5-114)//click pe exit
        {
            a=width/16-31; b=height/5-145; c=width/10; d=height/5-114;
            schimbare_culoare_buton(a,b,c,d);
            rectangle(a,b,c,d);
            schimbare_sunet(ok);
            exit(1);
        }
    else if(coordx>=(width/2-100)&&coordx<=(width/2+98)&&coordy>=(height/2-40)&&coordy<=(height/2+12)&&limba==1)
            {//daca se face click pe primul buton: "Grafic"
                a=width/2-100; b=height/2-40; c=width/2+98; d=height/2+12;
                schimbare_culoare_buton(a,b,c,d);
                schimbare_sunet(ok);
                clearmouseclick(WM_LBUTTONUP);
                fereastra_Grafic(width,height,ok,poza,limba);
                click_pe_Grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
            }
    else if(coordx>=(width/2-119)&&coordx<=(width/2+118)&&coordy>=(height/2-40)&&coordy<=(height/2+12)&&limba==0)
            {//daca se face click pe "Graph"
                a=width/2-119; b=height/2-40; c=width/2+118; d=height/2+12;
                schimbare_culoare_buton(a,b,c,d);
                schimbare_sunet(ok);
                clearmouseclick(WM_LBUTTONUP);
                fereastra_Grafic(width,height,ok,poza,limba);
                click_pe_Grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
            }

    else if(coordx>=(width/2-168)&&coordx<=(width/2+165)&&
                coordy>=(height/2+110)&&coordy<=(height/2+165)&&limba==1)
            {
            //daca se apasa butonul de "Informatii"
            //se schimba culoare dreptunghiului in galben la click
                a=width/2-168; b=height/2+110; c=width/2+165; d=height/2+165;
                schimbare_culoare_buton(a,b,c,d);
                schimbare_sunet(ok);
                fereastra_Informatii(width, height,ok,poza,limba);
                click_pe_Informatii(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
            }
    else if(coordx>=(width/2-185)&&coordx<=(width/2+183)&&
                coordy>=(height/2+110)&&coordy<=(height/2+165)&&limba==0)
            {
            //daca se apasa butonul de "Information"
            //se schimba culoare dreptunghiului in galben la click

                a=width/2-185; b=height/2+110; c=width/2+183; d=height/2+165;
                schimbare_culoare_buton(a,b,c,d);
                schimbare_sunet(ok);
                fereastra_Informatii(width, height,ok,poza,limba);
                click_pe_Informatii(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
            }


    else if(coordx>=(width/16-31)&&coordx<=(width/16)&&
                    coordy>=(height/5-100)&&coordy<=(height/5-70))
            {
                readimagefile("sunetinchis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);
                PlaySound(NULL,0,0);
            }
    }
}

void caseta_text_functie(int width, int height,int ok,int limba)
{
        int a, b, c, d;
        char car;
        a=width/2-320; b=height/3+70; c=width/4+655; d=height/3+130;
        schimbare_culoare_buton(a,b,c,d);
        schimbare_sunet(ok);
            do
            {
                car = getch();
                if(car!=8 && car !=13)
                    {
                        fun[pozitiei]=car;
                        fun[pozitiei+1]='\0';
                        pozitiei++;

                        settextstyle(8, HORIZ_DIR, 4 );
                        setfillstyle(0,BLACK);
                        bar(width/2-320,height/3+70,width/4+655,height/3+130);

                        setcolor(WHITE);
                        rectangle(width/2-320,height/3+70,width/4+655,height/3+130);
                        settextjustify(LEFT_TEXT, CENTER_TEXT);

                        outtextxy(a+30,b+30,fun);
                    }
                else if(car==8)
                    {
                        setcolor(WHITE);
                        setfillstyle(0,BLACK);
                        bar(width/2-320,height/3+70,width/4+655,height/3+130);

                        setcolor(WHITE);
                        rectangle(width/2-320,height/3+70,width/4+655,height/3+130);

                        settextstyle(8, HORIZ_DIR, 4 );
                        fun[pozitiei-1]='\0';

                        settextjustify(LEFT_TEXT, CENTER_TEXT);
                        outtextxy(a+30,b+30,fun);
                        pozitiei--;
                    }
            }
            while(car!=13);

            if(car==13)
                {
                    a=width/2-550; b=height/2+70; c=width/2+550; d=height/2+250;
                    setfillstyle(0,BLACK);
                    bar(width/2-550,height/2+70,width/2+550,height/2+250);//evaluator
                    setcolor(WHITE);
                    rectangle(width/2-550,height/2+70,width/2+550,height/2+250);
                    schimbare_culoare_buton(a,b,c,d);
                    schimbare_sunet(ok);
                    mesaj_evaluator(width,height,limba);
                }

        }



void caseta_text_capat_stanga(int width, int height,double &A,int ok)
{
        int a, b, c, d;
        char car;
        a=width/2-320; b=height/4-10; c=width/4+320; d=height/4+50;
        schimbare_culoare_buton(a,b,c,d);
        schimbare_sunet(ok);
            do
            {
                car = getch();
                if(car!=8 && car !=13)
                    {
                        capatst[pozitiest]=car;
                        capatst[pozitiest+1]='\0';
                        pozitiest++;

                        settextstyle(8, HORIZ_DIR, 4 );
                        setfillstyle(0,BLACK);
                        bar(width/2-320,height/4-10,width/4+320,height/4+50);

                        setcolor(WHITE);
                        rectangle(width/2-320,height/4-10,width/4+320,height/4+50);
                        settextjustify(LEFT_TEXT, CENTER_TEXT);

                        outtextxy(a+30,b+30,capatst);
                    }
                else if(car==8)
                    {
                        setcolor(WHITE);
                        setfillstyle(0,BLACK);
                        bar(width/2-320,height/4-10,width/4+320,height/4+50);

                        setcolor(WHITE);
                        rectangle(width/2-320,height/4-10,width/4+320,height/4+50);
                        settextstyle(8, HORIZ_DIR, 4 );

                        capatst[pozitiest-1]='\0';
                        settextjustify(LEFT_TEXT, CENTER_TEXT);
                        outtextxy(a+30,b+30,capatst);

                        pozitiest--;
                    }
            }
            while(car!=13);
            A=atof((char*)capatst);
        }


void caseta_text_capat_dreapta(int width, int height,double &A,double &B,int ok, int limba)
{
        int a, b, c, d;
        char car;
        a=width/4+340; b=height/4-10; c=width/4+655; d=height/4+50;
        schimbare_culoare_buton(a,b,c,d);
        schimbare_sunet(ok);
            do
            {
                car = getch();
                if(car!=8 && car !=13)
                    {
                        capatdr[pozitiedr]=car;
                        capatdr[pozitiedr+1]='\0';
                        pozitiedr++;

                        settextstyle(8, HORIZ_DIR, 4 );
                        setfillstyle(0,BLACK);
                        bar(width/4+340,height/4-10,width/4+655,height/4+50);

                        setcolor(WHITE);
                        rectangle(width/4+340,height/4-10,width/4+655,height/4+50);
                        settextjustify(LEFT_TEXT, CENTER_TEXT);

                        outtextxy(a+30,b+30,capatdr);
                    }
                else if(car==8)
                    {
                        setcolor(WHITE);
                        setfillstyle(0,BLACK);
                        bar(width/4+340,height/4-10,width/4+655,height/4+50);

                        setcolor(WHITE);
                        rectangle(width/4+340,height/4-10,width/4+655,height/4+50);
                        settextstyle(8, HORIZ_DIR, 4 );
                        capatdr[pozitiedr-1]='\0';
                        settextjustify(LEFT_TEXT, CENTER_TEXT);
                        outtextxy(a+30,b+30,capatdr);

                        pozitiedr--;
                    }
                }
                while(car!=13);
                B=atof((char*)capatdr);

                if(car==13)
                    {
                        a=width/2-550; b=height/2+70; c=width/2+550; d=height/2+250;
                        setfillstyle(0,BLACK);
                        bar(width/2-550,height/2+70,width/2+550,height/2+250);//evaluator
                        setcolor(WHITE);
                        rectangle(width/2-550,height/2+70,width/2+550,height/2+250);
                        schimbare_culoare_buton(a,b,c,d);
                        schimbare_sunet(ok);
                        evaluare_interval(width,height,A,B,limba);
                    }
        }


void click_pe_Grafic(double &A, double &B, int width, int height,int ok,int poza, int limba, int culoarerama, int culoaregrafic)
{
    int coordx, coordy;
    int a,b,c,d;
    fullscreen(width,height);

    while(true)
    {
    click(coordx,coordy);
    if(coordx>=width/10+10&&coordx<=width/10+90&&coordy>=height/5-145&&coordy<=height/5-114)//back
        {
            a=width/10+10; b=height/5-145; c=width/10+90; d=height/5-114;
            schimbare_culoare_buton(a,b,c,d);
            schimbare_sunet(ok);
            closegraph();
            fereastra_principala(width, height,ok,poza,limba);
            click_pe_fereastra_pr(A,B,ok,poza,limba,culoarerama, culoaregrafic);

        }
else if(coordx>=width/16-31&&coordx<=width/10&&coordy>=height/5-145&&coordy<=height/5-114)//exit
        {
            a=width/16-31; b=height/5-145; c=width/10; d=height/5-114;
            schimbare_culoare_buton(a,b,c,d);
            schimbare_sunet(ok);
            exit(1);
        }
    else if(coordx>=(width/16-31)&&coordx<=(width/16)&&
                    coordy>=(height/5-100)&&coordy<=(height/5-70))//sunet inchis
            {
                readimagefile("sunetinchis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);
                PlaySound(NULL,0,0);
            }
        else if(coordx>=(width/2-320)&&coordx<=(width/4+655)&&coordy>=(height/3+70)&&coordy<=(height/3+130))
        {
            //daca se apasa caseta cu "Introduceti functia aici:"
            //se schimba culoare dreptunghiului in galben la click

            caseta_text_functie(width,height,ok,limba);
            strcpy(temp,fun);
            click_pe_Grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
        }

    else if(coordx>=(width/2-320)&&coordx<=(width/4+320)&&coordy>=(height/4-10)&&coordy<=(height/4+50))//stanga
        {

        caseta_text_capat_stanga(width,height,A,ok);
        click_pe_Grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
        }
    else if(coordx>=(width/4+340)&&coordx<=(width/4+655)&&coordy>=(height/4-10)&&coordy<=(height/4+50))//dreapta
        {
         caseta_text_capat_dreapta(width,height,A,B,ok,limba);
        click_pe_Grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
        }
    else if(coordx>=(width/2+460)&&coordx<=(width/2+540)&&coordy>=(height/2-18)&&coordy<=(height/2+7))//buton spre functie
        {
        if(k2==1&&k==0)
            {
            a=width/2+460; b=height/2-18; c=width/2+540; d=height/2+7;
            schimbare_culoare_buton(a,b,c,d);
            schimbare_sunet(ok);
            fereastra_cu_graficul_desenat(A,B,ok,poza,limba,culoarerama,culoaregrafic);
            closegraph();
            }
        }
    }
}

void click_pe_Informatii(double A, double B, int width, int height,int ok,int poza,int limba,int culoarerama, int culoaregrafic)
{
    int coordx, coordy;
    int a,b,c,d;
    fullscreen(width, height);
    while(true)
    {
        click(coordx,coordy);
        if(coordx>=width/10+10&&coordx<=width/10+90&&coordy>=height/5-145&&coordy<=height/5-114)//back
            {
                a=width/10+10; b=height/5-145; c=width/10+90; d=height/5-114;
                schimbare_culoare_buton(a,b,c,d);
                schimbare_sunet(ok);
                closegraph();
                fereastra_principala(width, height,ok,poza,limba);
                click_pe_fereastra_pr(A,B,ok,poza,limba,culoarerama,culoaregrafic);
            }
    else if(coordx>=width/16-31&&coordx<=width/10&&coordy>=height/5-145&&coordy<=height/5-114)//exit
            {
                a=width/16-31; b=height/5-145; c=width/10; d=height/5-114;
                schimbare_culoare_buton(a,b,c,d);
                schimbare_sunet(ok);
                exit(1);
            }
    else if(coordx>=(width/16-31)&&coordx<=(width/16)&&
                        coordy>=(height/5-100)&&coordy<=(height/5-70))//sunet inchis
                {
                    readimagefile("sunetinchis1.jpeg",width/16-31,height/5-100,width/16,height/5-70);
                    PlaySound(NULL,0,0);
                }

        }
}

void click_back_grafic(double A, double B, int width, int height,int ok,int poza,int limba,int culoarerama, int culoaregrafic)
{
    int coordx, coordy;
    int a,b,c,d;
    fullscreen(width, height);
    fun[0]='/0';
    capatdr[0]='/0';
    capatst[0]='/0';

    pozitiei=0;
    pozitiest=0;
    pozitiedr=0;

    while(true)
    {
        click(coordx,coordy);
        if(coordx>=width/10-100&&coordx<=width/10-20&&coordy>=height/5-145&&coordy<=height/5-114)//back
            {
                a=width/10-100; b=height/5-145; c=width/10-20; d=height/5-114;
                schimbare_culoare_buton(a,b,c,d);
                schimbare_sunet(ok);
                contorev=0;
                closegraph();
                fereastra_Grafic(width,height,ok,poza,limba);
                click_pe_Grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);
            }
    }
}


//functie:
double functie(double x)
{
    transformare_functie();
    transformare_din_infix_in_postinfx();
    return calculare_f_din_postf(x);
}

double calculare_integrala_functiei(double A, double B, double(*f)(double))
{
    if((B-A)<EPSILON)
        return (B-A)*((*f)(A)+(*f)(B))/2.0;

    else {
            double punctint;
            punctint=(A+B)/2.0;
            return calculare_integrala_functiei(A,punctint,f)+calculare_integrala_functiei(punctint,B,f);
        }
}

bool discontinuitate(double x)
{
        if((floor(functie(x-EPSILON))!=floor(functie(x+EPSILON)))||(floor(functie(x-EPSILON))!=floor(functie(x)))||(floor(functie(x+EPSILON))!=floor(functie(x))))return 1;//punct de discontinuitate
                else return 0;//continuu in x
}

void aflare_min_si_max(double A, double B)
{
    int i;
    double x,y;
    MIN=100000001;
    MAX=-MIN;
    for(i=0;i<=(DREAPTA-STANGA);i++)
    {
        x=A+i*(B-A)/(DREAPTA-STANGA);
        y=functie(x);//functia introdusa de la la fereastra in casuta de text
        MAX=max(MAX,y);//noul max in y
        MIN=min(MIN,y);//noul min in y
    }
}

void aflare_min_max_din_interval(double A, double B, double &minim, double &maxim)
{
    minim=100000001;
    maxim=-minim;
    double i;
    double x,y,ypunctactual;
    x=A;
    y=functie(x);
    aflare_min_si_max(A,B);
    for(i=0;i<=DREAPTA-STANGA;i++)
    {
        x=A+i*(B-A)/(DREAPTA-STANGA);
        y=functie(x);
        ypunctactual=(int)((BOTTOM-TOP)*y/(MAX-MIN)+(MAX*TOP-MIN*BOTTOM)/(MAX-MIN));
        minim=min(minim,ypunctactual);
        maxim=max(maxim,ypunctactual);
    }
}

void desenare_grafic_functie(double A, double B, int culoaregrafic, int culoarerama)
{
    int i;
    double x,y,xecran,yecran,xpunctactual,ypunctactual;

    aflare_min_max_din_interval(A,B,minim,maxim);

    x=A;
    y=(functie(A));
    aflare_min_si_max(A,B);
    xecran=(DREAPTA-STANGA)*x/(B-A)+(B*STANGA-A*DREAPTA)/(B-A);
    yecran=(BOTTOM-TOP)*y/(MAX-MIN)+(MAX*TOP-MIN*BOTTOM)/(MAX-MIN);
    for(i=0;i<=DREAPTA-STANGA;i++)
    {
        x=A+i*(B-A)/(DREAPTA-STANGA);
        y=functie(x);
        xpunctactual=((DREAPTA-STANGA)*x/(B-A)+(B*STANGA-A*DREAPTA)/(B-A));
        ypunctactual=((BOTTOM-TOP)*y/(MAX-MIN)+(MAX*TOP-MIN*BOTTOM)/(MAX-MIN));

        if(discontinuitate(x)==1)
        {
            setcolor(COLOR(18,18,18));
            line(xecran,TOP+2,xecran,BOTTOM-2);

            if(culoarerama==1)setcolor(RED);
                        else if(culoarerama==2)setcolor(YELLOW);
                        else if(culoarerama==3)setcolor(CYAN);
                        else if(culoarerama==4)setcolor(GREEN);

            rectangle(STANGA,TOP,DREAPTA,BOTTOM);
        }

        if(ypunctactual==minim)
        {
            setcolor(WHITE);
            line(xecran,yecran,xpunctactual,ypunctactual);
        }
    else if(ypunctactual==maxim)
        {
            setcolor(WHITE);
            line(xecran,yecran,xpunctactual,ypunctactual);
        }
   else {
            if(culoaregrafic==1)setcolor(RED);
                else if(culoaregrafic==2)setcolor(YELLOW);
                else if(culoaregrafic==3)setcolor(CYAN);
                else if(culoaregrafic==4)setcolor(GREEN);

            line(xecran,yecran,xpunctactual,ypunctactual);
        }
        xecran=xpunctactual;
        yecran=ypunctactual;
    }
}

void redesenare_grafic(double A, double B, int width, int height,int ok,int poza,int limba,int culoarerama, int culoaregrafic)
{
    char t[256];
    double valoareintegrala;

    if(culoaregrafic==1)setcolor(RED);
        else if(culoaregrafic==2)setcolor(YELLOW);
        else if(culoaregrafic==3)setcolor(CYAN);
        else if(culoaregrafic==4)setcolor(GREEN);

    desenare_grafic_functie(A,B,culoaregrafic,culoarerama);
    desenare_asimptote(A,B);
    explicatii_grafic(width,height,limba);

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 4 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    strcpy(t,"Back");
    outtextxy(width/10-60,height/5-120,t);//setari pentru formare buton back
    rectangle(width/10-100,height/5-145,width/10-20,height/5-114);

    if(limba==1)
    {
        strcpy(t,"Reprezentarea functiei:");
        outtextxy(width/2,height/4-70,t);
    }
        else  {
                strcpy(t,"Graph reprezentation:");
                outtextxy(width/2,height/4-70,t);
                }

    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR, 3 );
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    if(limba==1)
    {
        strcpy(t,"Integrala:");
        outtextxy(width/4+250,height-100,t);
        valoareintegrala=calculare_integrala_functiei(A,B,&functie);
        char charintegrala[256];
        sprintf(charintegrala," %lf",valoareintegrala);
        outtextxy(width/4+430, height-100,charintegrala);
    }
        else  {
                strcpy(t,"Integral:");
                outtextxy(width/4+250,height-100,t);
                valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                char charintegrala[256];
                sprintf(charintegrala," %lf",valoareintegrala);
                outtextxy(width/4+430, height-100,charintegrala);
            }
    char car;
    do
        {
            car = getch();
            if((car==KEY_RIGHT||car=='d')&&car!=13)//dr
                {
                    cleardevice();
                    A+=2;
                    B+=2;

                    if(culoarerama==1)setcolor(RED);
                        else if(culoarerama==2)setcolor(YELLOW);
                        else if(culoarerama==3)setcolor(CYAN);
                        else if(culoarerama==4)setcolor(GREEN);

                    rectangle(STANGA,TOP,DREAPTA,BOTTOM);

                    setcolor(WHITE);
                    settextstyle(8, HORIZ_DIR, 4 );
                    settextjustify(CENTER_TEXT,CENTER_TEXT);
                    strcpy(t,"Back");
                    outtextxy(width/10-60,height/5-120,t);//setari pentru formare buton back
                    rectangle(width/10-100,height/5-145,width/10-20,height/5-114);

                    explicatii_grafic(width,height,limba);

                    setcolor(WHITE);
                    settextstyle(8, HORIZ_DIR, 4 );
                    settextjustify(CENTER_TEXT,CENTER_TEXT);

                    if(limba==1)
                    {
                        strcpy(t,"Reprezentarea functiei:");
                        outtextxy(width/2,height/4-70,t);
                    }
                    else  {
                            strcpy(t,"Graph reprezentation:");
                            outtextxy(width/2,height/4-70,t);
                            }

                    setcolor(WHITE);
                    settextstyle(8, HORIZ_DIR, 3 );
                    settextjustify(CENTER_TEXT,CENTER_TEXT);

                    if(limba==1)
                        {
                            strcpy(t,"Integrala:");
                            outtextxy(width/4+250,height-100,t);
                            valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                            char charintegrala[256];
                            sprintf(charintegrala,"%lf",valoareintegrala);
                            outtextxy(width/4+430, height-100,charintegrala);
                        }
                    else  {
                            strcpy(t,"Integral:");
                            outtextxy(width/4+250,height-100,t);
                            valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                            char charintegrala[256];
                            sprintf(charintegrala,"%lf",valoareintegrala);
                            outtextxy(width/4+430, height-100,charintegrala);
                            }

                    desenare_grafic_functie(A,B,culoaregrafic,culoarerama);
                    setcolor(DARKGRAY);
                    desenare_axe(A,B);
                    desenare_asimptote(A,B);
                }
            else if((car==KEY_LEFT||car=='a')&&car!=13)//st
            {
                cleardevice();
                A-=2;
                B-=2;

                if(culoarerama==1)setcolor(RED);
                    else if(culoarerama==2)setcolor(YELLOW);
                    else if(culoarerama==3)setcolor(CYAN);
                    else if(culoarerama==4)setcolor(GREEN);

                rectangle(STANGA,TOP,DREAPTA,BOTTOM);

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 4 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                strcpy(t,"Back");
                outtextxy(width/10-60,height/5-120,t);//setari pentru formare buton back
                rectangle(width/10-100,height/5-145,width/10-20,height/5-114);

                explicatii_grafic(width,height,limba);

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 4 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);

                if(limba==1)
                    {
                        strcpy(t,"Reprezentarea functiei:");
                        outtextxy(width/2,height/4-70,t);
                    }
                    else  {
                            strcpy(t,"Graph reprezentation:");
                            outtextxy(width/2,height/4-70,t);
                            }

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 3 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);

                if(limba==1)
                    {
                        strcpy(t,"Integrala:");
                        outtextxy(width/4+250,height-100,t);
                        valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                        char charintegrala[256];
                        sprintf(charintegrala,"%lf",valoareintegrala);
                        outtextxy(width/4+430, height-100,charintegrala);
                    }
                else  {
                        strcpy(t,"Integral:");
                        outtextxy(width/4+250,height-100,t);
                        valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                        char charintegrala[256];
                        sprintf(charintegrala,"%lf",valoareintegrala);
                        outtextxy(width/4+430, height-100,charintegrala);
                        }

                desenare_grafic_functie(A,B,culoaregrafic,culoarerama);
                setcolor(DARKGRAY);
                desenare_axe(A,B);
                desenare_asimptote(A,B);
                }
            else if((car=='w'||car==KEY_UP)&&car!=13)//ZOOM -
            {
                if((A+2)<(B-2))
                {
                cleardevice();
                A+=2;
                B-=2;

               if(culoarerama==1)setcolor(RED);
                    else if(culoarerama==2)setcolor(YELLOW);
                    else if(culoarerama==3)setcolor(CYAN);
                    else if(culoarerama==4)setcolor(GREEN);

                rectangle(STANGA,TOP,DREAPTA,BOTTOM);

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 4 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                strcpy(t,"Back");
                outtextxy(width/10-60,height/5-120,t);//setari pentru formare buton back
                rectangle(width/10-100,height/5-145,width/10-20,height/5-114);

                explicatii_grafic(width,height,limba);

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 4 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);

                if(limba==1)
                    {
                        strcpy(t,"Reprezentarea functiei:");
                        outtextxy(width/2,height/4-70,t);
                    }
                    else  {
                            strcpy(t,"Graph reprezentation:");
                            outtextxy(width/2,height/4-70,t);
                            }

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 3 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);

                if(limba==1)
                    {
                        strcpy(t,"Integrala:");
                        outtextxy(width/4+250,height-100,t);
                        valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                        char charintegrala[256];
                        sprintf(charintegrala,"%lf",valoareintegrala);
                        outtextxy(width/4+430, height-100,charintegrala);
                    }
                else  {
                        strcpy(t,"Integral:");
                        outtextxy(width/4+250,height-100,t);
                        valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                        char charintegrala[256];
                        sprintf(charintegrala,"%lf",valoareintegrala);
                        outtextxy(width/4+430, height-100,charintegrala);
                    }


                desenare_grafic_functie(A,B,culoaregrafic,culoarerama);
                setcolor(DARKGRAY);
                desenare_axe(A,B);
                desenare_asimptote(A,B);
                }
            }
            else if((car=='s'||car==KEY_DOWN)&&car!=13)//ZOOM +
            {
                cleardevice();
                A-=2;
                B+=2;

                if(culoarerama==1)setcolor(RED);
                    else if(culoarerama==2)setcolor(YELLOW);
                    else if(culoarerama==3)setcolor(CYAN);
                    else if(culoarerama==4)setcolor(GREEN);

                rectangle(STANGA,TOP,DREAPTA,BOTTOM);

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 4 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                strcpy(t,"Back");
                outtextxy(width/10-60,height/5-120,t);//setari pentru formare buton back
                rectangle(width/10-100,height/5-145,width/10-20,height/5-114);

                explicatii_grafic(width,height,limba);

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 4 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);

                if(limba==1)
                    {
                        strcpy(t,"Reprezentarea functiei:");
                        outtextxy(width/2,height/4-70,t);
                    }
                    else  {
                            strcpy(t,"Graph reprezentation:");
                            outtextxy(width/2,height/4-70,t);
                            }

                setcolor(WHITE);
                settextstyle(8, HORIZ_DIR, 3 );
                settextjustify(CENTER_TEXT,CENTER_TEXT);

                if(limba==1)
                    {
                        strcpy(t,"Integrala:");
                        outtextxy(width/4+250,height-100,t);
                        valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                        char charintegrala[256];
                        sprintf(charintegrala,"%lf",valoareintegrala);
                        outtextxy(width/4+430, height-100,charintegrala);
                    }
                else  {
                        strcpy(t,"Integral:");
                        outtextxy(width/4+250,height-100,t);
                        valoareintegrala=calculare_integrala_functiei(A,B,&functie);
                        char charintegrala[256];
                        sprintf(charintegrala,"%lf",valoareintegrala);
                        outtextxy(width/4+430, height-100,charintegrala);
                    }

                desenare_grafic_functie(A,B,culoaregrafic,culoarerama);
                setcolor(DARKGRAY);
                desenare_axe(A,B);
                desenare_asimptote(A,B);
            }
        }
    while(car!=13);
    click_back_grafic(A,B,width,height,ok,poza,limba,culoarerama,culoaregrafic);

}

void transformare_functie()
{
    int i=0,j,nr=0;
    double numar;
    while(i<=strlen(fun)-1)
    {
        if(isdigit(fun[i])!=0)
        {
            while(isdigit(fun[i])!=0)
            {
                vect[nr]=fun[i];
                i++;j=1;
                nr++;
            }
        vect[nr]=' ';nr++;
        }
        else
            if(strchr("+-*^/)(",fun[i]))
                {
                    vect[nr]=fun[i];
                    nr++;i=i+1;j=1;
                    vect[nr]=' ';nr++;
                }
            else
                if(fun[i]=='x')
                    {
                        vect[nr]=fun[i];
                        nr++;j=1;
                        i++;
                        vect[nr]=' ';nr++;
                    }
                else
                    {
                        if('s'==fun[i])
                            {
                                vect[nr]=fun[i];
                                nr++;i=i+3;j=3;
                                vect[nr]=' ';nr++;
                            }
                        else
                            if('c'==fun[i])
                                {
                                    vect[nr]=fun[i];
                                    nr++;i=i+3;j=3;
                                    vect[nr]=' ';nr++;
                                }
                            else
                                if('l'==fun[i])
                                {
                                    vect[nr]=fun[i];
                                    nr++;i=i+2;j=2;
                                    vect[nr]=' ';nr++;
                                }
                                else
                                    if('t'==fun[i])
                                        {
                                            vect[nr]=fun[i];
                                            nr++;i=i+2;j=2;
                                        }


                    }
}

for(i=0;i<=strlen(vect)-1;i++)
    if(vect[i]!=' ')
        inserare(infixata,vect[i]);

}

void transformare_din_infix_in_postinfx( )
{
    while (esteVidaC(infixata)==0)
    {
        if(infixata->inf=='x')// x=necunoscuta
                 {
                     inserare(postfixata,'x');
                     eliminare(infixata);
                }

        else
            if(isdigit(infixata->inf))//cifre
            {
                inserare(postfixata,infixata->inf);
                eliminare(infixata);
            }
                else
                    if(infixata->inf==')')
                        {
                            while(S->inf!='(')
                                {
                                    inserare(postfixata,S->inf);
                                    pop(S);
                                }
                        pop(S); eliminare(infixata);
                        }
                    else
                        {
                            while (esteVidaS(S)==0&&S->inf!='('&&prioritate_caracter(S->inf)>= prioritate_caracter(infixata->inf))
                            {
                                inserare(postfixata,S->inf);
                                pop(S);
                            }
                        push(S,infixata->inf);
                        eliminare(infixata);
                        }
    }
    while (esteVidaS(S)==0)
    {
        inserare(postfixata,S->inf);
        pop(S);
    }
}

double calculare_f_din_postf(double x)
{
    double val;
    while(esteVidaC(postfixata)==0)
    {
        if(postfixata->inf=='x')// x=necunoscuta
                 {
                     push2(S,x);
                     eliminare(postfixata);
                }

        else
            if(isdigit(postfixata->inf))//cifre
            {
                val=0;
                while(isdigit(postfixata->inf))
                      {
                        char c=postfixata->inf;
                        val=val*10+(c-'0');
                        eliminare(postfixata);
                      }
                push2(S,val);
            }

        else
            if(strchr("+-/^*",postfixata->inf)!=0)
                        {
                            double valoare1, valoare2,answ;
                            valoare1=S->info;
                            pop(S);
                            valoare2=S->info;
                            pop(S);
                            char operator1=postfixata->inf;
                            answ=operatie(operator1, valoare2, valoare1);
                            eliminare(postfixata);
                            push2(S,answ);
                        }
            else
                if(strchr("sclrt",postfixata->inf)!=0)
                    {
                        double valoare1,answ;
                        valoare1=S->info;
                        pop(S);
                        char operator1=postfixata->inf;
                        answ=operatie_speciala(operator1,valoare1);
                        eliminare(postfixata);
                        push2(S,answ);
                    }
                }

    double valoare=S->info;pop(S);
    return valoare;
}

double operatie (char r, double x, double y)
{
    if(r=='+')return x+y;
    if(r=='-')return x-y;
    if(r=='*')return x*y;
    if(r=='/')return x/y;
    if(r=='^')return pow(x,y);
}

double operatie_speciala (char r, double x)
{
    if(r=='s')return sin(x);
    if(r=='c')return cos(x);
    if(r=='l')return log(x);
    if(r=='r')return sqrt(x);
    if(r=='t')return tan(x);
}

int prioritate_caracter(char a)
{
    if(strchr("+",a)||strchr("-",a))return 1;
        else if(strchr("*",a)||strchr("/",a))return 2;
                else if(strchr("^",a))return 3;
                        else if(strchr("scltr",a))return 4;
                                else if(strchr("(",a)||strchr(")",a))return 5;
}


//evaluator:
void evaluator()
{
    int nr=0,ok=0,nr1=0,i;
    for(i=0; i<=strlen(fun)-1; i++)
    {
        if(fun[i]=='(')
            nr++;
        if(fun[i]==')')
            nr1++;
        if(fun[i]=='('&&fun[i+1]==')')
            {ok=1;v[++k]=ok;}
        if(fun[i]=='('&&fun[i+1]=='+')
            {ok=2;v[++k]=ok;}
        if(fun[i]=='('&&fun[i+1]=='-')
            {ok=3;v[++k]=ok;}
        if(fun[i]=='('&&fun[i+1]=='*')
            {ok=4;v[++k]=ok;}
        if(fun[i]=='('&&fun[i+1]=='/')
            {ok=5;v[++k]=ok;}
        if(fun[i]=='('&&fun[i+1]=='^')
            {ok=6;v[++k]=ok;}
        if(fun[i]==')'&&fun[i]=='(')
            {ok=7;v[++k]=ok;}
        if(fun[i]==')'&&fun[i+1]=='s')
            {ok=8;v[++k]=ok;}
        if(fun[i]==')'&&fun[i+1]=='c')
            {ok=9;v[++k]=ok;}
        if(fun[i]==')'&&fun[i+1]=='l')
            {ok=10;v[++k]=ok;}
        if(fun[i]==')'&&fun[i+1]=='r')
            {ok=11;v[++k]=ok;}
        if(fun[i]==')'&&fun[i+1]=='t')
            {ok=12;v[++k]=ok;}
        if(fun[i]==')'&&fun[i+1]=='x')
            {ok=13;v[++k]=ok;}
        if(fun[i]==')'&&isdigit(fun[i+1]))
            {ok=14;v[++k]=ok;}
        if(fun[i]=='+'&&fun[i+1]=='+')
            {ok=15;v[++k]=ok;}
        if(fun[i]=='+'&&fun[i+1]=='-')
            {ok=16;v[++k]=ok;}
        if(fun[i]=='+'&&fun[i+1]=='*')
            {ok=17;v[++k]=ok;}
        if(fun[i]=='+'&&fun[i+1]=='/')
            {ok=18;v[++k]=ok;}
        if(fun[i]=='+'&&fun[i+1]=='^')
            {ok=19;v[++k]=ok;}
        if(fun[i]=='-'&&fun[i+1]=='+')
            {ok=20;v[++k]=ok;}
        if(fun[i]=='-'&&fun[i+1]=='-')
            {ok=21;v[++k]=ok;}
        if(fun[i]=='-'&&fun[i+1]=='*')
            {ok=22;v[++k]=ok;}
        if(fun[i]=='-'&&fun[i+1]=='/')
            {ok=23; v[++k]=ok;}
        if(fun[i]=='-'&&fun[i+1]=='^')
            {ok=24;v[++k]=ok;}
        if(fun[i]=='*'&&fun[i+1]=='+')
            {ok=25; v[++k]=ok;}
        if(fun[i]=='*'&&fun[i+1]=='-')
            {ok=26; v[++k]=ok;}
        if(fun[i]=='*'&&fun[i+1]=='*')
            {ok=27; v[++k]=ok;}
        if(fun[i]=='*'&&fun[i+1]=='/')
            {ok=28; v[++k]=ok;}
        if(fun[i]=='*'&&fun[i+1]=='^')
            {ok=29; v[++k]=ok;}
        if(fun[i]=='/'&&fun[i+1]=='+')
            {ok=30; v[++k]=ok;}
        if(fun[i]=='/'&&fun[i+1]=='-')
            {ok=31; v[++k]=ok;}
        if(fun[i]=='/'&&fun[i+1]=='*')
            {ok=32; v[++k]=ok;}
        if(fun[i]=='/'&&fun[i+1]=='/')
            {ok=33; v[++k]=ok;}
        if(fun[i]=='/'&&fun[i+1]=='^')
            {ok=34; v[++k]=ok;}
        if(fun[i]=='^'&&fun[i+1]=='+')
            {ok=35; v[++k]=ok;}
        if(fun[i]=='^'&&fun[i+1]=='-')
            {ok=36; v[++k]=ok;}
        if(fun[i]=='^'&&fun[i+1]=='*')
            {ok=37; v[++k]=ok;}
        if(fun[i]=='^'&&fun[i+1]=='/')
            {ok=38; v[++k]=ok;}
        if(fun[i]=='^'&&fun[i+1]=='^')
            {ok=39; v[++k]=ok;}
        if(strchr("sctlr",fun[i])&&strchr("sctlr",fun[i+1]))
            {ok=40; v[++k]=ok;}
        if(fun[i]=='s'&&(fun[i+1]!='i'||fun[i+2]!='n'))
            {ok=41; v[++k]=ok;}
        if(fun[i]=='c'&&(fun[i+1]!='o'||fun[i+2]!='s'))
            {ok=42; v[++k]=ok;}
        if(fun[i]=='r'&&(fun[i+1]!='a'||fun[i+2]!='d'))
            {ok=43; v[++k]=ok;}
        if(fun[i]=='l'&&fun[i+1]!='n')
            {ok=44; v[++k]=ok;}
        if(fun[i]=='t'&&fun[i+1]!='g')
            {ok=45; v[++k]=ok;}
        if(strchr("+/-*^",fun[i])&&fun[i+1]==')')
            {ok=50;v[++k]=ok;}
    }
    if(strchr("-*/^",fun[0]))
        {ok=46; v[++k]=ok;}

    if(strchr("+-*/^",fun[strlen(fun)-1]))
        {ok=47; v[++k]=ok;}

    if(nr!=nr1)
        {ok=48; v[++k]=ok;}

    if(k==0)ok=49;
}

void evaluare_interval(int width, int height,double A, double B,int limba)
{
    k2=0;contorev=0;
    char t[256];
    if(A>=B)//intervalul nu e bun
            {
                settextstyle(8, HORIZ_DIR, 3);
                settextjustify(CENTER_TEXT,contorev);
                setcolor(WHITE);
                if(limba==1)strcpy(t,"Intervalul nu este bine ales");
                    else strcpy(t,"The range is not well chosen");
                outtextxy(width/2,height/2+100+contorev,t);
                k2=0;
                contorev+=27;
            }
        else
        {
            settextstyle(8, HORIZ_DIR, 3);
            settextjustify(CENTER_TEXT,contorev);
            setcolor(WHITE);
            if(limba==1)strcpy(t,"Intervalul este bine ales");
                else strcpy(t,"The range is well chosen");
            outtextxy(width/2,height/2+100+contorev,t);
            k2=1;
            contorev+=27;
        }

}

void mesaj_evaluator(int width, int height, int limba)
 {
    k=0;contorev=0;
    char t[256];
    settextstyle(8, HORIZ_DIR, 3);
    int i;
    evaluator();

    settextjustify(CENTER_TEXT,contorev);
    setcolor(WHITE);

 for(i=0;i<=k;i++)
    {
    if(limba==1){
    if(v[i]==1){
        strcpy(t,"Nu poate aparea o paranteza deschisa urmata de o paranteza inchisa");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==2){
        strcpy(t,"Nu poate aparea o paranteza deschisa urmata de +");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==3){
        strcpy(t,"Nu poate aparea o paranteza deschisa urmata de -");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==4){
        strcpy(t,"Nu poate aparea o paranteza deschisa urmata de *");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==5){
        strcpy(t,"Nu poate aparea o paranteza deschisa urmata de /");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==6){
        strcpy(t,"Nu poate aparea o paranteza deschisa urmata de ^");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==7){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de o paranteza deschisa");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==8){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de functia sinus");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==9){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de functia cosinus");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==10){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de functia logaritmica");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==11){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de functia radical");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==12){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de functia tangenta");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==13){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de constanta x");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==14){
        strcpy(t,"Nu poate aparea o paranteza inchisa urmata de un numar");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==15){
        strcpy(t,"Nu poate aparea simbolul + urmat de simbolul + ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==16){
        strcpy(t,"Nu poate aparea simbolul + urmat de simbolul - ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==17){
        strcpy(t,"Nu poate aparea simbolul + urmat de simbolul * ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==18){
        strcpy(t,"Nu poate aparea simbolul + urmat de simbolul / ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==19){
        strcpy(t,"Nu poate aparea simbolul + urmat de simbolul ^ ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==20){
        strcpy(t,"Nu poate aparea simbolul - urmat de simbolul + ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==21){
        strcpy(t,"Nu poate aparea simbolul - urmat de simbolul - ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==22){
        strcpy(t,"Nu poate aparea simbolul - urmat de simbolul * ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==23){
        strcpy(t,"Nu poate aparea simbolul - urmat de simbolul / ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==24){
        strcpy(t,"Nu poate aparea simbolul - urmat de simbolul ^ ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==25){
        strcpy(t,"Nu poate aparea simbolul * urmat de simbolul + ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==26){
        strcpy(t,"Nu poate aparea simbolul * urmat de simbolul - ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==27){
        strcpy(t,"Nu poate aparea simbolul * urmat de simbolul * ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==28){
        strcpy(t,"Nu poate aparea simbolul * urmat de simbolul / ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==29){
        strcpy(t,"Nu poate aparea simbolul * urmat de simbolul ^ ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==30){
        strcpy(t,"Nu poate aparea simbolul / urmat de simbolul + ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==31){
        strcpy(t,"Nu poate aparea simbolul / urmat de simbolul - ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==32){
        strcpy(t,"Nu poate aparea simbolul / urmat de simbolul * ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==33){
        strcpy(t,"Nu poate aparea simbolul / urmat de simbolul / ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==34){
        strcpy(t,"Nu poate aparea simbolul / urmat de simbolul ^ ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==35){
        strcpy(t,"Nu poate aparea simbolul ^ urmat de simbolul + ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==36){
        strcpy(t,"Nu poate aparea simbolul ^ urmat de simbolul - ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==37){
        strcpy(t,"Nu poate aparea simbolul ^ urmat de simbolul * ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==38){
        strcpy(t,"Nu poate aparea simbolul ^ urmat de simbolul / ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==39){
        strcpy(t,"Nu poate aparea simbolul ^ urmat de simbolul ^ ");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==40){
        strcpy(t,"Nu se pot folosi 2 astfel de simboluri lipite");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==41){
        strcpy(t,"Functia sin nu este bine scrisa");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==42){
        strcpy(t,"Functia cos nu este bine scrisa");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==43){
        strcpy(t,"Functia rad nu este bine scrisa");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==44){
        strcpy(t,"Functia ln nu este bine scrisa");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==45){
        strcpy(t,"Functia tg nu este bine scrisa");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==46){
        strcpy(t,"Inceputul functiei nu este corect scris");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==47){
        strcpy(t,"Finalul functiei nu este corect scris");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==48){
        strcpy(t,"Numarul de paranteze deschise nu coincide cu nr. de paranteze inchise");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==50){
        strcpy(t,"Nu pot fi lipite 2 astfel de semne");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    }
    else{
        if(v[i]==1){
        strcpy(t,"An open parenthesis followed by a closed one cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==2){
        strcpy(t,"An open parenthesis followed by + cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==3){
        strcpy(t,"An open parenthesis followed by - cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==4){
        strcpy(t,"An open parenthesis followed by * cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==5){
        strcpy(t,"An open parenthesis followed by / cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==6){
        strcpy(t,"An open parenthesis followed by ^ cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==7){
        strcpy(t,"An closed parenthesis followed by a open one cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==8){
        strcpy(t,"A  '(' followed by the sin function cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==9){
        strcpy(t,"A  ')' followed by the cosine function cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==10){
        strcpy(t,"A ')' followed by the logarithmic function cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==11){
        strcpy(t,"A ')' followed by the radical function cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==12){
        strcpy(t,"A ')' followed by the tangent function cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==13){
        strcpy(t,"A ')' followed by the constant x cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==14){
        strcpy(t,"A ')' followed by a number cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==15){
        strcpy(t,"The + symbol followed by the + symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==16){
        strcpy(t,"The + symbol followed by the - symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==17){
        strcpy(t,"The + symbol followed by the * symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==18){
        strcpy(t,"The + symbol followed by the / symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==19){
        strcpy(t,"The + symbol followed by the ^ symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==20){
        strcpy(t,"The - symbol cannot appear followed by the + symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==21){
        strcpy(t,"The - symbol cannot appear followed by the - symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==22){
        strcpy(t,"The - symbol cannot appear followed by the * symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==23){
        strcpy(t,"The - symbol cannot appear followed by the / symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==24){
        strcpy(t,"The - symbol cannot appear followed by the ^ symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==25){
        strcpy(t,"The * symbol followed by the + symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==26){
        strcpy(t,"The symbol * followed by the symbol - cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==27){
        strcpy(t,"The * symbol cannot appear followed by the * symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==28){
        strcpy(t,"The symbol * followed by the symbol / cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==29){
        strcpy(t,"The * symbol followed by the ^ symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==30){
        strcpy(t,"The / symbol followed by the + symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==31){
        strcpy(t,"The / symbol cannot appear followed by the - symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==32){
        strcpy(t,"The / symbol cannot appear followed by the * symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==33){
        strcpy(t,"The / symbol cannot appear followed by the / symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==34){
        strcpy(t,"The symbol / followed by the symbol ^ cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==35){
        strcpy(t,"The ^ symbol followed by the + symbol cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==36){
        strcpy(t,"The symbol ^ followed by the symbol - cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==37){
        strcpy(t,"The symbol ^ followed by the symbol * cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==38){
        strcpy(t,"The symbol ^ followed by the symbol / cannot appear");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==39){
        strcpy(t,"The ^ symbol cannot appear followed by the ^ symbol");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==40){
        strcpy(t,"Two such symbols stuck together cannot be used");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==41){
        strcpy(t,"The sin function is not well written");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==42){
        strcpy(t,"The cos function is not well written");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==43){
        strcpy(t,"The rad function is not well written");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==44){
        strcpy(t,"The ln function is not well written");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==45){
        strcpy(t,"The tg function is not well written");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==46){
        strcpy(t,"The beginning of the function is not well written");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==47){
        strcpy(t,"The end of the function is not written correctly");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==48){
        strcpy(t,"The number of '(' does not coincide with the nr. of ')'");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}
    else if(v[i]==50){
        strcpy(t,"Two such signs cannot be pasted");
        if(contorev<=135){outtextxy(width/2,height/2+100+contorev,t);
                        contorev+=27;}}

    }
    }
    if(k==0){
        if(limba==1)strcpy(t,"Functia e bine scrisa");
        else strcpy(t,"The function is well written");
        outtextxy(width/2,height/2+100+contorev,t);
        contorev+=27;}


 }


//axe
void desenare_axe(double A, double B)
{
    double dim, unitate, i;
    if(A<0&&B>0)
        {
            dim=B-A;
            unitate=(DREAPTA-STANGA)/dim;
            line(STANGA-A*unitate,TOP,STANGA-A*unitate,BOTTOM);//oy
            line(STANGA-A*unitate-7,TOP+7,STANGA-A*unitate,TOP);//sagetele pt oy
            line(STANGA-A*unitate+7,TOP+7,STANGA-A*unitate,TOP);//sagetele pt oy

            for(i=TOP+unitate;i<=BOTTOM;i+=unitate)
                line(STANGA-A*unitate-2,i,STANGA-A*unitate+2,i);
        }

    line(STANGA,TOP+(BOTTOM-TOP)/2,DREAPTA,TOP+(BOTTOM-TOP)/2);//ox
    line(DREAPTA-7,TOP+(BOTTOM-TOP)/2-7,DREAPTA,TOP+(BOTTOM-TOP)/2);//sagetele pt ox
    line(DREAPTA-7,TOP+(BOTTOM-TOP)/2+7,DREAPTA,TOP+(BOTTOM-TOP)/2);//sagetele pt ox

    dim=B-A;
    unitate=(DREAPTA-STANGA)/dim;
    for(i=STANGA+unitate;i<=DREAPTA;i+=unitate)
                line(i,TOP+(BOTTOM-TOP)/2-2,i,TOP+(BOTTOM-TOP)/2+2);
}

//asimptote
double asimptota_orizontala()
{
    double c,a,b,k,l,ok=0;int i,j,ok1=0;
    if(strchr(temp,'/')&&!strchr(temp,'s')&&!strchr(temp,'c')&&!strchr(temp,'l')&&!strchr(temp,'r')&&!strchr(temp,'t'))
        {for(i=0;i<=strlen(temp)-1;i++)
            if(temp[i]!='/')
               {if(temp[i]=='x'&&ok==0)
                    {if(temp[i+1]=='^')
                        {k=temp[i+2]-'0'; ok=1;}
                    else
                        {k=1;ok=1;}
                     if(temp[i-1]=='*')
                            {a=temp[i-2]-'0';}
                    else
                            a=1;
                    }
               }
                else
                    break;

            for(j=i+1;j<=strlen(temp)-1;j++)
                if(temp[j]=='x'&&ok1==0)
                    {if(temp[j+1]=='^')
                    {l=temp[j+2]-'0'; ok1=1;}
                            else
                            {l=1;ok1=1;}
                       if(temp[j-1]=='*')
                            b=temp[j-2]-'0';
                        else
                            b=1;}
    if(k==l)
        c=a/b;
    else
        if(k<l)
            c=0;
        else
            c=EPSILON;
    if(c==floor(c))
        return c;
    else
        return INFINIT;
        }
}


double asimptota_verticala()
{
    double c,a=0,b=0;int i,j,ok1=0;
    if(strchr(temp,'/')&&!strchr(temp,'s')&&!strchr(temp,'c')&&!strchr(temp,'l')&&!strchr(temp,'r')&&!strchr(temp,'t'))
        {for(i=0;i<=strlen(temp)-1;i++)
            if(temp[i]=='/')
                    break;
            for(j=strlen(temp)-1;j>=i+1;j--)
                if(isdigit(temp[j])&&temp[j-1]!='^'&&ok1==0)
                    {if(temp[j-1]=='-')
                            {a=temp[j]-'0';
                            a=-a;
                            ok1++;}
                    else
                        {a=temp[j]-'0'; ok1++;}
                    }
                else
                    if(temp[j]=='x'&&temp[j-1]!='*'&&ok1==0)
                        {if(temp[j-1]=='+')
                            {a=1; ok1++;}
                        else
                            if(temp[j-1]=='-')
                                {a=-1; ok1++;}}
                else
                    if(isdigit(temp[j])&&temp[j-1]!='^'&&ok1==1)
                    {
                        if(temp[j-1]=='-')
                            {b=temp[j]-'0';
                            b=-b;
                            ok1++;}
                        else
                            {b=temp[j]-'0'; ok1++;}
                        }
                    else
                        if(temp[j]=='x'&&temp[j-1]!='*'&&ok1==1)
                            {
                            if(temp[j-1]=='-')
                                {b=-1; ok1++;}
                            else
                                {b=1;ok1++;}
                            }

    if(b!=0)
        c=(-a)/b;
    else
        c=-a;
    return c;

        }
}

void desenare_asimptote(double A, double B)
{
    double dim,unitate,unitate1,punctmijloc1,punctmijloc;
    dim=B-A;
    unitate=(TOP+BOTTOM)/dim;
    punctmijloc=(TOP+BOTTOM)/2;
    int c=asimptota_orizontala();
    c=c*unitate;
    if(c!=EPSILON&&c!=INFINIT)
        {
            setcolor(MAGENTA);
            line(STANGA,punctmijloc-c,DREAPTA,punctmijloc-c);
        }
    if(A<0&&B>0)
        {
        dim=B-A;
        if(c!=0||c==INFINIT)
            {
                unitate1=(STANGA+DREAPTA)/dim;
                punctmijloc1=(STANGA+DREAPTA)/2;
                int a=asimptota_verticala();
                a=a*unitate;
                setcolor(BLUE);
                line(punctmijloc-a,TOP,punctmijloc-a,BOTTOM);
           }
        }
}
