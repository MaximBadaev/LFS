/* 
 * File:   main.cpp
 * Author: Stan
 *
 * Created on 19 Сентябрь 2019 г., 11:06
 */
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <cctype>
#include <math.h>



using namespace std;

/*
 * 
 */

//Для смены шрифта.
//Объявление функций и типов в коде вручную (объект шрифта и функция для его
//смены).
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
//the function declaration begins
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, 
BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif
////the function declaration ends
//Сама функция для смены шрифта на Lucida Console.
void ChangeFontToLC()
{
    CONSOLE_FONT_INFOEX lpConsoleCurrentFontEx;
	lpConsoleCurrentFontEx.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	lpConsoleCurrentFontEx.dwFontSize.X = 12;
	lpConsoleCurrentFontEx.dwFontSize.Y = 12;
	lstrcpyW(lpConsoleCurrentFontEx.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx ( GetStdHandle(STD_OUTPUT_HANDLE), false,
        &lpConsoleCurrentFontEx );
}

void Show(string spath){

HANDLE search_file;//Объект типа handle, в который записывается результат   
 //FindFirstFile, получающийся за счёт пути к папке, где производится поиск,
 //и указателя на объект fd, в котором хранятся данные по файлу.
WIN32_FIND_DATA fd;//Объект типа WIN32_FIND_DATA для хранения найденных
    //данных.

string fst;//Статус файлового объекта.
int r;//Остаток.
float a2log;//Логарифм по основанию 2
int n;//Целый показатель
int pw;//Степень
int tc=0;//Счётчик всех объектов файловой системы.
int dc=0;//Счётчик папок

search_file = FindFirstFile(spath.c_str(), &fd);

while (FindNextFile(search_file, &fd) != NULL)
{
//Определитель папок
        if ((fd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)&&
            ((string)fd.cFileName!="..")) fst="D";
        else fst="";
            
r=fd.dwFileAttributes;
ReLog:
if ((r>16)&&((string)fd.cFileName!="..")){
a2log=log(r)/log(2);
if ((float)a2log!=(int)a2log){
      pw=(int)a2log;
      n=pow(2,pw);
      r=r-n;
      if ((r==16)||(n==16)){
  fst="D";
 }
      else{
          fst="";
          goto ReLog;
      }
}      
}         
    
 cout<<fd.cFileName<<"   "<<fst<<endl; //Вывод имени файла/папки 
 if ((string)fd.cFileName!="..") tc++;
 if (fst=="D") dc++;
 }

cout<<" "<<endl;
cout<<"Directories:"<<dc<<endl;
cout<<"Total Objects:"<<tc<<endl;

}

//Основная функция
int main() {

 setlocale(LC_ALL, "");//Поддержка других языков   
 SetConsoleCP(1251);
 SetConsoleOutputCP(1251);
 ChangeFontToLC();//Смена точечного шрифта на Lucida Console (для рус. букв).
 HANDLE search_file;//Объект типа handle, в который записывается результат   
 //FindFirstFile, получающийся за счёт пути к папке, где производится поиск,
 //и указателя на объект fd, в котором хранятся данные по файлу.
 string spath;//Путь.
 string pathcheck;//Переменная проверки пути.
 string dnext; //Имя выбранной папки для перехода
 string p="forth"; //Предыдущее направление движения перебора. 
 string dir="forth";//Направление движения перебора.
 string fst;
 string search;//Строка для поиска.
 string e;//Строка для одного исключения в векторе.
 //Путевые векторы
 vector<string> fpath;//Путь к найденному объекту.
 vector<int> dnvv;//Вектор значений номера папки на пути
 vector<int> dcvv;//Вектор значений количества папок в папке
 vector<string> ex;//Список исключений.
 vector<string> found;//Вектор для найденного.
 int dc=0;//Счётчик папок
 int dnum=1;//Номер выбранной папки
 int enddc=0; //Текущее значение конечного элемента вектора количества папок.
 int enddn=0;//Текущее значение конечного элемента вектора номеров выбранных 
 //папок.
 int en;//Число исключений.
 int renddc=0;//Начальное значение вектора количества папок. Первый элемент.
 int renddn=0;//Начальное значение вектора номеров выбранных 
 //папок. Первый элемент.
 int pos; //Позиция символа в поиске по совпадениям в строке. 
 int pw;//Целый логарифм
 int n;//Целый показатель
 int r;//Остаток
 float a2log;
 bool q;//Детектор кавычек.
 bool exf;//1, если исключение найдено. 
 
 stringstream sp;
  
// spath="C:/Program Files/*";
 WIN32_FIND_DATA fd;//Объект типа WIN32_FIND_DATA для хранения найденных
    //данных.

 Input:
 cout<<"Logarithmic File Search, 2021, Maxim Badaev"<<endl; 
 cout<<" "<<endl;
 cout<<"Input search:"<<endl;
 getline(cin, search);
 cout<<" "<<endl;
 cout<<"Input path:"<<endl;
// cin>>spath;
 getline(cin, spath);   
 
 pathcheck=spath;
 
switch(getch())
{

case 101:
int en;//Число исключений.
cout<<" "<<endl;
cout<<"Type number of exclusions"<<endl;
cin>>en;
cout<<" "<<endl;
cout<<"Type exclusions"<<endl;
for(int i=0;i<=en;i++){
EType:
getline(cin,e,'\n');
if (e==spath){
    cout<<"Exclusion is equal to the path, type another one"<<endl;
    goto EType;
}
ex.push_back(e);
e="";
}
cout<<" "<<endl;
break;

case 115:
cout<<" "<<endl;
Show(spath);
goto Finish;
break;

}
 
 
 if((search[0]==34)&&(search[search.length()-1]==34)){
q=1;
search.erase(0,1);
search.erase(search.length()-1,1);
}
 
 while(renddn<=renddc)
 {
 
 search_file = FindFirstFile(spath.c_str(), &fd);
 //Фильтр путей. Доработать.
 if (FindFirstFile(pathcheck.c_str(), &fd)==INVALID_HANDLE_VALUE){
     cout<<"No such path"<<endl;
     goto Input;
 }
 
 //Базовый перебор. 
 while (FindNextFile(search_file, &fd) != NULL)
 {
   
   //Определитель папок
        if ((fd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)&&
            ((string)fd.cFileName!="..")) fst="D";
        else fst="";
            
r=fd.dwFileAttributes;
ReLog:
if ((r>16)&&((string)fd.cFileName!="..")){
a2log=log(r)/log(2);
if ((float)a2log!=(int)a2log){
      pw=(int)a2log;
      n=pow(2,pw);
      r=r-n;
      if ((r==16)||(n==16)){
  fst="D";
 }
      else{
          fst="";
          goto ReLog;
      }
}      
}     
     
   //Базовый перебор. Движение вперёд (от корня).
   if (dir=="forth"){
//   cout<<fd.cFileName<<endl; //Вывод имени файла/папки
   //"Грубый" поиск.
//   if((string)fd.cFileName==search) {
//       found.push_back((string)fd.cFileName);
//       fpath.push_back(spath);
//   }
       
     //Точный поиск
if(q==1){
   if((string)fd.cFileName==search) {
       found.push_back((string)fd.cFileName);
       fpath.push_back(spath);
   }
}
//Грубый поиск
else{
pos=((string)fd.cFileName).find(search,0);   
if (pos!=-1) {
found.push_back((string)fd.cFileName);
fpath.push_back(spath);
}
}  
       
       
   
   if (fst=="D") dc++;//Прибавление счётчика папок
   
   if ((dc==dnum)&&(fst=="D")) 
   dnext=(string)fd.cFileName;//Получение следующей папки для перехода
   }
   
   //Базовый перебор. Движение назад (к корню).
   else if(dir=="back1"){
//   cout<<fd.cFileName<<endl;//Вывод имени файла/папки
   if (fst=="D") dc++;//Прибавление счётчика папок
   
   if ((dc==dnvv[dnvv.size()-1])&&
   (fst=="D")) 
   dnext=(string)fd.cFileName;//Получение следующей папки для перехода   
   }
 }
 
 if(dc==0 && dcvv.size()==0 && dnvv.size()==0){
     cout<<" "<<endl;
     cout<<"Empty root directory."<<endl;
     cout<<" "<<endl;
     goto Show;
 }
 //Вывод проверочной информации
// cout<<" "<<endl;
// cout<<dc<<endl;//Вывод количества папок
 
 //Действия при дальнейшем движении вперёд. Если в папке есть ещё папки
 if (dc!=0){ 
     dir="forth";
 if (dir=="forth"){
    //Формирование новой строки пути
    spath.erase(spath.length()-1,spath.length()-1);
    spath+=dnext+"/*";
    
    //Если путь в списке исключений
if(ex.size()!=0){
for(int i=1;i<ex.size();i++){
if(ex[i]==spath){ 
dir="back1";
//cout<<"Exclusion found"<<endl;
//system("pause");
exf=1;

}
}
}    
    //Добавление новых значений к путевым векторам из пройденной папки
    if (p=="forth"){
    dcvv.push_back(dc);
    dnvv.push_back(dnum);
    }
    p="forth";
    if (exf==1){
        exf=0;
        goto ExBack;
    } 
        
 }
 }    
 
 //Действия при дальнейшем движении назад. Если в папке нет папок
 else if (dc==0) {
     dir="back1";
 ExBack: //Пропуск в случае исключения.    
 if (dir=="back1"){
    //Формирование новой строки пути
    spath.erase(spath.length()-2,spath.length());
    while (spath[spath.length()-1]!='/')
    {
      spath.erase(spath.length()-1,spath.length()-1);  
    }
    spath+="*";
    //Прибавление на 1 элемента вектора выбора на предыдущем уровне.
    dnvv[dnvv.size()-1]++;
    p="back1";
    
    //Получение коэффициентов текущих конечных значений векторов.
enddc=dcvv[dnvv.size()-1];
enddn=dnvv[dnvv.size()-1];

checked:
//Возврат на верхний уровень в случае если на предыдущем все папки закончились
 if (enddn>enddc){
     if ((dcvv.size()>1)&&(dnvv.size()>1)){
     //Формирование новой строки пути
    spath.erase(spath.length()-2,spath.length());
    while (spath[spath.length()-1]!='/')
    {
      spath.erase(spath.length()-1,spath.length()-1);  
    }
    spath+="*";
    //Отброс отработанных конечных элементов вектора
    dcvv.pop_back();
    dnvv.pop_back();
          
    //Прибавление на 1 элемента вектора выбора на предыдущем уровне.
    dnvv[dnvv.size()-1]++;
    
    //Если верхние уровни достигли края
    //Получение коэффициентов текущих конечных значений векторов.
enddc=dcvv[dnvv.size()-1];
enddn=dnvv[dnvv.size()-1];

if (enddn>enddc) {
        
    goto checked;
}
  
     }
 }
 }
 }
     
 //Обнуление счётчика папок в конце перебора и сбора значений
 dc=0;
 
 
  
 //Получение коэффициентов текущих начальных значений векторов.
 renddc=dcvv[0];
 renddn=dnvv[0];

 
 
//Вывод проверочной информации
//cout<<" "<<endl;
//    for(int i=0;i<dcvv.size();i++){
//        cout<<"/"<<dcvv[i];
//    }
//    cout<<endl;
//    
//    for(int i=0;i<dnvv.size();i++){
//        cout<<"/"<<dnvv[i];
//    }
//    cout<<endl;
//    
//    cout<<" "<<endl;
//    cout<<renddc<<endl;
//    cout<<renddn<<endl;
    cout<<" "<<endl;
    cout<<spath<<endl;
    cout<<" "<<endl;
    
    //Результаты поиска.
    Show:
    if(found.size()!=0){
    for(int i=0;i<found.size();i++)
    cout<<"Name:"<<found[i]<<" "<<"Path:"<<fpath[i]<<endl;
    }
    
    if(dc==0 && dcvv.size()==0 && dnvv.size()==0) goto Finish;
    
    if (GetAsyncKeyState(VK_ESCAPE)) goto Finish;//Остановка клавишей Esc.
        
    if(renddn<=renddc) system("cls");
    
 }

Finish://Для остановки клавишей Esc.    
 
system("pause");
return 0;
}




