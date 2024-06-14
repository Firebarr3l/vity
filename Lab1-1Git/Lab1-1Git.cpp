#include "stdafx.h"    
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <malloc.h>  
#include <clocale>
#include <windows.h>

using namespace std; 
using namespace System;  
using namespace System::IO;   
  
#define ENTER 13  
#define ESC 27  
#define UP 72  
#define DOWN 80 
#define HOME 71
#define END 79
#define LENGTHMENU 84

struct Kinoed  *Kinoed = NULL;

struct Kinoed {
  char name[31];
  long cost;
  long prodtiket;
  long rating;
  char studioname[18];
  char data[11];};

struct sp {
char studioname[18];
long prodtiket;
long rating;
struct sp* pred;
struct sp* sled;};

struct sp2 {
char name[32];
char studioname[18];
char data[11];
long cost;
long prodtiket;
long rating;
struct sp2* pred;
struct sp2* sled;};



int menu(int, char [][LENGTHMENU]);
void minn(struct Kinoed*, int);
void text_data(char *,char *);
void oldest(struct Kinoed*,int);
void kolvofilmov(struct Kinoed*,struct sp** spisok, int);
void vstavka(struct Kinoed*,struct sp** spisok,char *, int);
void vstavkakino(struct Kinoed*,struct sp2** spisok2, char *, int);
void alfalistkino(struct Kinoed*,struct sp2** spisok2, int);
void alfalist(struct Kinoed*,struct sp** spisok, int);
void listing(struct sp2*,struct sp2** spisok2, int);
void diagramstudio(struct Kinoed*,struct sp** spisok, int);
void diagramkino(struct Kinoed*,struct sp2** spisok2, int);
void CompereCostofkino(struct Kinoed*, int);


void minn(struct Kinoed* kino, int chislostrok)
{
int i=0;
struct Kinoed best;
strcpy(best.name,kino[0].name);
best.prodtiket=kino[0].prodtiket;
for(i=1;i<chislostrok;i++){
  if (kino[i].prodtiket<best.prodtiket){
    strcpy(best.name,kino[i].name);
    best.prodtiket=kino[i].prodtiket;}
}
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkCyan;
Console::CursorLeft=10;
Console::CursorTop=19;
printf("Наименьшее число %ld проданных билетов",best.prodtiket);
Console::CursorLeft=10;
Console::CursorTop=20;
printf("имеет фильм: %s",best.name);
getch();
}

void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
"января","февраля","марта","апреля","мая","июня",
"июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}

void oldest(struct Kinoed* kino,int chislostrok)
{
int i;
char s[17];
struct Kinoed* best=kino;
for(i=1;i<chislostrok;i++)
if (strcmp(kino[i].data,best->data)<0)
  best=&kino[i];
    text_data(s,best->data);
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkCyan;
Console::CursorLeft=10;
Console::CursorTop=18;
printf("Самый \"старый\" фильм принадлежит студии %s ",best->studioname);
Console::CursorLeft=10;
Console::CursorTop=20;
printf("это %s",best->name);
Console::CursorLeft=10;
Console::CursorTop=22;
printf("Был выпущен %s ",s);
getch();
}
void kolvofilmov(struct Kinoed *kino,struct sp** spisok, int chislostrok)
{
int i,k=0;
char vvodstudio[18];
struct sp *nt;
if(!*spisok){
  for(i=0;i<chislostrok;i++){
    vstavka(kino,spisok,kino[i].studioname, chislostrok);}
}
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkCyan;
Console::CursorTop=18;
for(nt=*spisok;nt!=0; nt=nt->sled){
  Console::CursorLeft=80;
  printf("%-20s ",nt->studioname);
  Console::CursorTop+=1;}
Console::CursorLeft=10;
Console::CursorTop=18;
printf("Введите название студии, чтобы увидеть количество ее фильмов");
SetConsoleCP(1251);
Console::CursorLeft=10;
Console::CursorTop=20;
scanf("%s", vvodstudio);
SetConsoleCP(866);
for(i=0;i<chislostrok;i++){
  if (strcmp(kino[i].studioname,vvodstudio)==0){
    k++;}
}
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkCyan;
Console::CursorLeft=10;
Console::CursorTop=22;
printf("Студия %s выпустила всего: %d фильмов",vvodstudio, k);
getch();
}

void vstavka(struct Kinoed* kinostudio,struct sp** spisok, char* studioname, int chislostrok) 
{ 
int i; 
struct sp *nov,*nt,*z=0; 
for(nt=*spisok; nt!=0 && strcmp(nt->studioname,studioname)<0; z=nt, nt=nt->sled); 
if(nt && strcmp(nt->studioname,studioname)==0) return; 
nov=(struct sp *) malloc(sizeof(struct sp)); 
strcpy(nov->studioname,studioname); 
nov->sled=nt; 
nov->prodtiket=0;
nov->rating=0;
nov->pred = z;
for(i=0;i<chislostrok;i++){
  if(strcmp(kinostudio[i].studioname,studioname)==0){ 
    nov->prodtiket+=kinostudio[i].prodtiket;
    nov->rating+=kinostudio[i].rating;}
}
if(!z) *spisok=nov; 
if(z) z->sled=nov; 
if(nt) nt->pred=nov; 
return; 
}

void vstavkakino(struct Kinoed* moovikino,struct sp2** spisok2, char* name, int chislostrok) 
{ 
int i; 
struct sp2 *nov,*nt,*z=0; 
for(nt=*spisok2; nt!=0 && strcmp(nt->name,name)<0; z=nt, nt=nt->sled); 
if(nt && strcmp(nt->name,name)==0) return; 
nov=(struct sp2 *) malloc(sizeof(struct sp2)); 
strcpy(nov->name,name); 
nov->sled=nt; 
nov->prodtiket=0;
nov->rating=0;
nov->cost=0;
strcpy(nov->studioname,"");
strcpy(nov->data,"");
nov->pred = z;
for(i=0;i<chislostrok;i++){ 
  if(strcmp(moovikino[i].name,name)==0){ 
    nov->prodtiket+=moovikino[i].prodtiket;
    nov->rating+=moovikino[i].rating;
    nov->cost+=moovikino[i].cost;
    strcat(nov->studioname, moovikino[i].studioname);
    strcat(nov->data, moovikino[i].data);}
}
if(!z) *spisok2=nov; 
if(z) z->sled=nov; 
if(nt) nt->pred=nov; 
return; 
}


void alfalistkino(struct Kinoed* kino,struct sp2** spisok2, int chislostrok)
{
int i;
char s[17];
struct sp2 *nt;
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
Console::Clear();
if(!*spisok2){
  for(i=0;i<chislostrok;i++){
    vstavkakino(kino,spisok2,kino[i].name, chislostrok);}
}
Console::Clear();
printf("\n \t\t\t\tАлфавитный список фильмов");
printf("\n ======================================================================================================================");
for(nt=*spisok2; nt!=0; nt=nt->sled){
  text_data(s,nt->data);
  printf("\n %-31s %5ld %12ld %15ld    %-18s   %-17s",nt->name,nt->cost,nt->rating, nt->prodtiket, nt->studioname, s);}
getch();
}


void alfalist(struct Kinoed* kino,struct sp** spisok, int chislostrok)
{
int i;
struct sp *nt,*z;
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
Console::Clear();
printf("\n    Алфавитный список студий");
printf(" \t\t\t\t   Обратный алфавитный список студий");
printf("\n========================================================================================================================");
if(!*spisok){
  for(i=0;i<chislostrok;i++){
    vstavka(kino,spisok, kino[i].studioname, chislostrok);}
}
for(nt=*spisok; nt!=0; nt=nt->sled){
  printf("\n %-20s %10ld",nt->studioname,nt->prodtiket);}
for(nt=*spisok,z=0; nt!=0; z=nt,nt=nt->sled);{
  Console::CursorTop=3;
  for(nt=z; nt!=0; nt=nt->pred){
    Console::CursorLeft=60;
    printf("%-20s %10ld",nt->studioname,nt->prodtiket);
    Console::CursorTop+=1;}
}
getch();
}


void listing(struct Kinoed* kino,struct sp2** spisok2, int chislostrok) 
{ 
int orn, price, i; 
char vvodstudio[18];
struct sp2 *net;
if(!*spisok2){
  for(i=0;i<chislostrok;i++){
    vstavkakino(kino,spisok2,kino[i].name, chislostrok);}
}
Console::Clear();
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
Console::Clear();
Console::CursorLeft=0;
Console::CursorTop=1;
printf("Введите название студии: ");
SetConsoleCP(1251);
Console::CursorLeft=27;
Console::CursorTop=1;
scanf("%s", vvodstudio);
SetConsoleCP(866);
Console::CursorLeft=0;
Console::CursorTop=3;
printf("Введите минимальный рейтинг фильма: ");
SetConsoleCP(1251);
Console::CursorLeft=36;
Console::CursorTop=3;
scanf("%d", &orn);
SetConsoleCP(866);
Console::CursorLeft=0;
Console::CursorTop=5;
printf("Введите минимальную стоимость: ");
SetConsoleCP(1251);
Console::CursorLeft=32;
Console::CursorTop=5;
scanf("%d", &price);
SetConsoleCP(866);
Console::Clear();
printf("\n                        Фильмы удовлетворяющие запросам  ");
printf("\n                                                                                                ");
printf("\nФильм                             Студия                       Цена/Рейтинг"); 
printf("\n======================================================================================================================="); 
for (net = *spisok2; net != 0; net = net->sled){
  if (strcmp(net->studioname,vvodstudio)==0){
    if ((((net->rating)>=orn) && ((net->cost)>=price))){
      printf("\n%-31s   %-18s          %4ld/%-7ld",net->name, net->studioname, net->cost, net->rating);}
  }
}
getch();

} 


void diagramstudio(struct Kinoed *kino,struct sp** spisok, int chislostrok)
{
struct sp *nt;
int len,i,NColor;
long copy = 0;
char str1[200];
char str2[200];
System::ConsoleColor Color;
Console::BufferHeight=720;
Console::BufferWidth=1280;
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
Console::Clear();
for(i=0;i<chislostrok;i++)copy = copy+kino[i].prodtiket;
if(!*spisok){
  for(i=0;i<chislostrok;i++){
    vstavka(kino,spisok,kino[i].studioname,chislostrok);}
}
printf("          Диаграмма проданных билетов фильмов определенной студии");
printf("\n============================================================================");
Color=ConsoleColor::DarkYellow; NColor=7;
for(nt=*spisok,i=1; nt!=0; nt=nt->sled,i++){
sprintf(str1,"%s",nt->studioname);
sprintf(str2,"%3.1f%%",(nt->prodtiket*100./copy));
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
Console::CursorLeft=0; Console::CursorTop=i+1;
printf(str1);
Console::CursorLeft=17;
printf("%s",str2);
Console::BackgroundColor=++Color;NColor++;
Console::CursorLeft=23;
for(len=0; len<(nt->prodtiket*100)/copy; len++) 
  printf(" ");
  if(NColor==13){
    Color=ConsoleColor::DarkYellow; NColor=7;}

}
getch();
return ;
}


void diagramkino(struct Kinoed *kino,struct sp2** spisok2,int chislostrok) 
{ 
struct sp2 *nt; 
int len,i,NColor; 
long sum1 = 0 ; 
long sum; 
char str1[200]; 
char str2[200]; 
System::ConsoleColor Color; 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
Console::Clear(); 
for(i=0;i<chislostrok;i++) sum1 = sum1+kino[i].rating; 
sum=sum1/chislostrok; 
if(!*spisok2){ 
  for(i=0;i<chislostrok;i++){ 
    vstavkakino(kino,spisok2,kino[i].name,chislostrok);}
}
Color=ConsoleColor::DarkYellow; NColor=7; 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan;  
printf("Cр. знач. рейтинга фильма (%d)   100%%  ",sum);
Console::BackgroundColor=ConsoleColor::Red; 
Console::CursorLeft=44; 
for(len=0; len<25; len++)printf(" ");
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
printf("\n========================================================================================================================================================================="); 
for(nt=*spisok2,i=1; nt!=0; nt=nt->sled,i++) { 
sprintf(str1,"%s",nt->name); 
sprintf(str2,"%3.1f%%",(nt->rating*100./sum)); 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan;  
Console::CursorLeft=0; Console::CursorTop=i+1; 
printf(str1); 
Console::CursorLeft=35; 
printf("%-s",str2);
Console::BackgroundColor=++Color;NColor++;
Console::CursorLeft=44;
for(len=0; len<(nt->rating)*10/sum; len++) printf(" "); 
  if(NColor==12){ 
    Color=ConsoleColor::DarkYellow; NColor=7;} 
} 
getch(); 
return ; 
}


void CompereCostofkino(struct Kinoed* kino, int chislostrok)
{
int i, j, proverka=0;
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkCyan; 
Console::CursorTop=19;
Console::CursorLeft=10;
for (i = 0; i < chislostrok - 1; i++) {
  for (j = i + 1; j < chislostrok; j++) {
    if (kino[i].cost == kino[j].cost) {
      proverka=1;
      Console::CursorLeft=10;
      printf("Фильмы %s (%s) и %s (%s) стоят одинаково: %ld руб.\n", kino[i].name, kino[i].studioname, kino[j].name,kino[j].studioname, kino[i].cost);
      Console::CursorTop+=1;}
    
  }
}
if (!proverka){
  printf("Фильмов с одинаковыми ценами нет!");}
getch();
}











int main(array<System::String ^> ^args)  
{  

char dan[][LENGTHMENU] = {  
"На какой фильм меньше всего продано билетов ?               ",
"Поиск самого старого фильма.                                ",  
"Количество выпущенных фильмов определенной студии по запросу",  
"Алфавитный список студий, количество фильмов                ",  
"Алфавитный список фильмов, со всей информацией              ",  
"Запрос по студии, минимальному рейтингу и цене              ",
"Диаграмма. Процентное соотношение рейтинга фильмов          ",
"Диаграмма. Процентноу соотношения проданных билетов         ",
"Одинаковый ценник                                           ",
"Вернуться на предыдущую страницу                            ",
"Выход                                                       ",                                                              
};
int i, n;  
FILE *in;  
struct Kinoed *kino;
int chislostrok;
point1:;
setlocale(LC_CTYPE, "Russian");  
Console::CursorVisible::set(false);  
Console::BufferHeight = 720;  
Console::BufferWidth = 1280;
if ((in = fopen("Kinoed.dat", "r")) == NULL){
    printf("\nФайл Vklad.dat не открыт!");
    getch(); exit(1);}
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::Yellow; 
printf("\nНазвание Фильма                  Цена   Проданых билетов   Рейтинг Название студии    Дата выпуска");
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::Magenta;
fscanf(in, "%d", &chislostrok);
kino = (struct Kinoed*)malloc(chislostrok * sizeof(struct Kinoed));
for (i = 0; i < chislostrok; i++){
  fscanf(in, "%s%ld%ld%ld%s%s", kino[i].name, &kino[i].cost, &kino[i].prodtiket, &kino[i].rating, kino[i].studioname, kino[i].data);}
for (i = 0; i < chislostrok; i++){
  printf("\n%-31s %5ld %12ld %15ld %-18s %s", kino[i].name, kino[i].cost, kino[i].prodtiket, kino[i].rating, kino[i].studioname, kino[i].data);}
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::White;
printf("\n");
printf("\n");
printf("\n");
printf("\nДля перехода на следующую страницу нажмите ENTER                                                                    "); 
getch();
struct sp *spisok = nullptr;
struct sp2 *spisok2 = nullptr;
while (1)  {  
  Console::ForegroundColor = ConsoleColor::Magenta;  
  Console::BackgroundColor = ConsoleColor::DarkCyan;  
  Console::Clear();
  Console::ForegroundColor = ConsoleColor::Magenta;  
  Console::BackgroundColor = ConsoleColor::Cyan;  
  Console::CursorLeft = 10;  
  Console::CursorTop = 4;  
  printf("                                                              ");  
  for (i = 0; i < 11; i++){  
    Console::CursorLeft = 10;  
    Console::CursorTop = i + 5;  
    printf(" %s ", dan[i]);}  
  Console::CursorLeft = 10;  
  Console::CursorTop = 16;  
  printf("                                                              ");  
n = menu(11, dan);  
switch (n) {  
  case 1: minn(kino,chislostrok); break;;  
  case 2: oldest(kino,chislostrok);break;  
  case 3: kolvofilmov(kino,&spisok,chislostrok);break;  
  case 4: alfalist(kino,&spisok,chislostrok);break;  
  case 5: alfalistkino(kino,&spisok2,chislostrok);break;  
  case 6: listing(kino,&spisok2,chislostrok);break;
  case 7: diagramkino(kino,&spisok2,chislostrok);break;
  case 8: diagramstudio(kino,&spisok,chislostrok);break;
  case 9: CompereCostofkino(kino,chislostrok); break;
  case 10:{Console::CursorLeft=0; 
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::White;
Console::CursorTop=0; 
Console::Clear(); 
goto point1;} 
  case 11	: exit(0);  
    }  
}  
return 0;  
}  
  
int menu(int n, char dan[][LENGTHMENU])  
{  
int y1 = 0, y2 = n - 1;  
char c = 1;  
while (c != ESC){  
  switch (c) {
    case DOWN: y2 = y1; y1++; break;  
    case UP: y2 = y1; y1--; break;
    case ENTER: return y1 + 1;
    case HOME: y2=y1; y1=0; break;
    case END: y2=y1; y1=n-1; break;}
 
  if (y1 > n - 1) { y2 = n - 1; y1 = 0; }  
  if (y1 < 0) { y2 = 0; y1 = n - 1; }
  Console::ForegroundColor = ConsoleColor::Magenta;  
  Console::BackgroundColor = ConsoleColor::Cyan;  
  Console::CursorLeft = 11;  
  Console::CursorTop = y2 + 5;  
  printf("%s", dan[y2]);
  Console::ForegroundColor = ConsoleColor::Yellow;  
  Console::BackgroundColor = ConsoleColor::DarkGreen;  
  Console::CursorLeft = 11;  
  Console::CursorTop = y1 + 5;  
  printf("%s", dan[y1]);      
  c = getch();}   
exit(0);
}