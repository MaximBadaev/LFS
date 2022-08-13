/* 
 * File:   main.cpp
 * Author: Stan
 *
 * Created on 15 Январь 2021 г., 23:30
 */

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <conio.h>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <vector>


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

void Search2(string spath, string search, stringstream* str1, 
        vector <string>* excv, bool q, int *e1){

HANDLE search_file;//Объект типа handle, в который записывается результат   
 //FindFirstFile, получающийся за счёт пути к папке, где производится поиск,
 //и указателя на объект fd, в котором хранятся данные по файлу.
WIN32_FIND_DATA fd;//Объект типа WIN32_FIND_DATA для хранения найденных
    //данных.

int dc=0;//Счётчик каталогов.
int r;//Остаток.
float a2log;//Логарифм по основанию 2
int n;//Целый показатель
int pw;//Степень
int tc=0;//Счётчик всех объектов файловой системы.
int pos;//Для грубого поиска.
int e2;//Вторая переменная для передачи сигнала выхода.
int c;

bool exit;

string fst;//Статус файлового объекта.
string dnext;

stringstream str2;

vector <string> excv2=*excv;

search_file = FindFirstFile(spath.c_str(), &fd);


while (FindNextFile(search_file, &fd) != NULL)
{
//Переключатель режимов поиска.
//Точный режим.
if(q==1){    
if ((string)fd.cFileName==search) 
*str1<<"Name:"<<(string)fd.cFileName<<" "<<"Path:"<<spath<<"\n";
}
//Грубый режим.
else{
pos=((string)fd.cFileName).find(search,0);
if (pos!=-1) {
*str1<<"Name:"<<(string)fd.cFileName<<" "<<"Path:"<<spath<<"\n";    
}
}
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
    
 //Формирование нового пути.   
    if (fst=="D"){
    dc++;
    dnext=fd.cFileName;
    spath.erase(spath.length()-1,1);
    spath+=dnext+"/"+"*";
    //Если есть исключения.
    if (excv2.size()!=0){
        for(int i=0;i<excv2.size();i++){
        if (excv2[i]==spath) goto JumpOver;//"Перескакивание" перехода в папку 
        //в случае нахождения исключения.    
        }
     }
    cout<<spath<<endl;
    Search2(spath, search, &str2, &excv2, q, &e2);//Рекурсивный вызов функции для
    //перебора дочерних папок.
    JumpOver://"Перескакивание" перехода в папку в случае нахождения исключения.
    //Передача найденных данных в "верхний" поток.
    *str1<<str2.str();
    //Очистка данных для следующих итераций.
    str2.str("");
    *e1=e2;//Передача сигнала выхода из первой переменной во вторую.
    spath.erase(spath.length()-2,spath.length());
    while (spath[spath.length()-1]!='/')
    {
      spath.erase(spath.length()-1,spath.length()-1);  
    }
    spath+="*";
    
    }
   dnext="";
   
   //Фиксация сигнала выхода с клавиатуры.  
   if (GetAsyncKeyState(VK_ESCAPE)){
       cout<<" "<<endl;
       cout<<"Press 'E' to exit or press any key to continue"<<endl;
       cout<<" "<<endl;
       *e1=getch();
       if (*e1==101) return;
       
   }
   if(e2==101) return;      
 }

}


int main() {
    setlocale(LC_ALL, "");//Поддержка других языков   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ChangeFontToLC();//Смена точечного шрифта на Lucida Console (для рус. букв).
    
    string spath;
    string search;
    stringstream str;
    string excs;
    
    vector <string> excv;
    
    bool q;//Детектор кавычек.
    int e3;//Третья переменная для передачи сигнала выхода.
    
    HANDLE search_file;//Объект типа handle, в который записывается результат   
 //FindFirstFile, получающийся за счёт пути к папке, где производится поиск,
 //и указателя на объект fd, в котором хранятся данные по файлу.
    WIN32_FIND_DATA fd;//Объект типа WIN32_FIND_DATA для хранения найденных
    //данных.
        
    Input:
    cout<<"Logarithmic File Search 2, 2021, Maxim Badaev"<<endl; 
    cout<<" "<<endl;
    cout<<"Input search:"<<endl;
    getline(cin,search);
    cout<<"Input path:"<<endl;
    getline(cin,spath);
        
    //Фильтр путей.
     if (FindFirstFile(spath.c_str(), &fd)==INVALID_HANDLE_VALUE){
         cout<<"No such path"<<endl;
         goto Input;
     }
    
    switch(getch())
{
    case 101:
    cout<<"Type exclusions:"<<endl; 
    Next:
    getline(cin,excs);
    excv.push_back(excs);
    excs="";
    if (getch()==110) goto Next;
    break;    
        
    case 115:
    cout<<" "<<endl;
    Show(spath);
    goto Finish;
    break;    
        
}

//Режим поиска.    
if((search[0]==34)&&(search[search.length()-1]==34)){
q=1;
search.erase(0,1);
search.erase(search.length()-1,1);
}
    
    cout<<" "<<endl;
    Search2(spath, search, &str, &excv, q, &e3); 
        
    cout<<" "<<endl;
    cout<<search<<endl;
    cout<<" "<<endl;
    cout<<str.str()<<endl;
    
    Finish:
    str.str("");//Сброс потока.
    q=0;//Сброс режима поиска.
    cout<<"Press 'N' to start a new search or press 'Enter' to exit"<<endl;
    if (getch()==110){ 
    system("cls"); 
    goto Input;
    }
    system("pause");
    return 0;
}

