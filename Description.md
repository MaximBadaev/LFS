# LFS
A Windows file search console program performing a recursive search through the whole directory tree on the path which is set manually by the user. The determination of the file system object's being a directory is done by the logarithmic calculations being performed with the file attribute constants 
https://docs.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants

Notes:
1. Input search: - the object of searching. There are two modes of searching: rough mode- finds all files and folders that have the input symbol combination in their names, accurate mode- the value being searched is written in quoters (like in Yandex search:)), finds only those files which names with their extensions completely coincide with the input value.
2. Input path: - the path where to search. The path is put in in the following form: Disk:/folder/.../folder/* (an asterisk in the end is necessary).
3. After typing all of the input data there`s an option of pressing Enter 2 times for running a search, also after first Enter pressing there`s a possibility of pressing E for putting in a list of exclusions. In this case the program won`t process the directories in the given locations. First the number of exclusions is given, then the list itself. The exclusions should be put in in the form of full path to the directory the same way as in "Input path". In case of pressing S after first Enter keystroke the full content of the directory which is set as the path will be shown on the screen.
4. The Esc key stops the searching process.
5. There`s a bug with the stretched console in Windows 10. It can be fixed by switching off a "Bold" flag in cmd font settings. The source code of the program was initially written on the machine with the Windows 7 OS which uses raster fonts in cmd. These fonts don`t work correctly with Russian Cyrillic letters despite the locales in the source code being set to universal and the codepage being set to Windows-1251. Because all of this the patch function that automatically changes console font to Lucida Console was written. It works in Windows 7, but a little bit distorts the image in Windows 10. Most probably it will be fixed soon.
6.Also the program doesn`t work with directories with high access restrictions and some folders which names start with $ symbol, but still works with most of the hidden files and directories, including the $-named ones too. This issue is also being solved.
The project is gonna be improved anyway.)


Консольное приложение для Windows, которое осуществляет рекурсивный поиск по всему древу каталогов. Путь поиска вручную задаётся пользователем. Определение является ли файловый объект каталогом производится за счёт логарифмических вычислений, выполняемых над константами файловых атрибутов.
https://docs.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants

Пояснения:
1.Input search: - что искать. Есть два режима поиска: грубый- находит все файлы и папки, в названиях которых встречается заданная комбинация символов, точный- искомое значение заключается в кавычки (как в Яндексе:)), находит только те файлы, имена которых полностью соответствуют введённому в кавычках значению вместе с расширением файла.
2.Input path:- путь, где искать. Путь вводится в формате: Диск:/папка/…/папка/* (звёздочка обязательно ставится в конце).
3. После ввода всех входных данных можно нажать два раза Enter для запуска поиска, также можно после первого Enter нажать E для ввода списка исключений, тогда программа не будет перебирать папки по указанным путям , сначала вводится количество исключений, потом сам список, исключения вводятся полными путями как в “Input path:” или клавишу S для вывода на экран содержимого папки по указанному пути.
4. Остановить перебор папок досрочно можно клавишей Esc.
5. На Windows 10 возможен глюк с растянутым шрифтом в консоли, исправляется отжатием галочки «Жирный жрифт» в настройках шрифта cmd. Дело в том, что писалось всё это на машине с Windows 7, на котором в cmd по умолчанию точечные шрифты, которые не дружат с русскими буквами, в следствие чего был написан патч, автоматически меняющий шрифт в консоли на Lucida Console. В Семёрке это работает, а в 10-ке немного искажает изображение. Скорее всего, будет поправлено в ближайшее время.
6. Также программа пока не работает с каталогами с большими ограничениями по доступу и некоторыми папками, имена которых начинаются на $, но всё равно работает с подавляющим большинством скрытых файлов и каталогов, включая и те, у которых имена которых начинаются на $. Этот вопрос также решается.
Ещё буду доделывать и совершенствовать.)
