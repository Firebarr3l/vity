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
struct sp *spisok = NULL;
struct sp2 *spisok2 = NULL;

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
void kolvo(struct Kinoed*, int);
void vstavka(struct Kinoed*,char *, int);
void vstavkakino(struct Kinoed*, char *, int);
void alfalistkino(struct Kinoed*, int);
void alfalist(struct Kinoed*, int);
void listing(struct sp2*, int);
void diagramstudio(struct Kinoed*, int);
void diagramkino(struct Kinoed*, int);
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
  case 3: kolvoigr(kino,chislostrok);break;  
  case 4: alfalist(kino,chislostrok);break;  
  case 5: alfalistkino(kino,chislostrok);break;  
  case 6: listing(kino,chislostrok);break;
  case 7: diagramkino(kino,chislostrok);break;
  case 8: diagramstudio(kino,chislostrok);break;
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