#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

//void mainQQ();
//void mainSystem();
void mainHookSys();

void openNotepad() {
	system("\"C:\\Program Files\\Notepad++\\notepad++.exe\"");
}

void closeNotePad() {
	printf("start to close notepad");
	system("taskkill /f /im notepad++.exe");

}

void testMain() {
	ShellExecuteA(0,"open","calc",0,0,1);
}

int main() {
	/*printf("helloworld");
	openNotepad();

	Sleep(5000);
	closeNotePad();
	test();*/
	//mainQQ();
	//mainSystem();
	//testDetours();
	//mainHookSys();
	main2levelStr();
	return 0;
}

void mainHookSys()
{
}
