#include<iostream>
#include<conio.h>
#include <windows.h>
#include<mmsystem.h>


#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define kEY_RIGHT 77
#define KEY_LEFT 75 


using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
//Car shape
char car[4][4] = { ' ','±','±',' ',
					'±','±','±','±',
					' ','±','±',' ',
					'±','±','±','±' };

int carPos = WIN_WIDTH/2;
int score = 0;
//Placing the cursor position (change the cursor position)
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
//Used to set the Cursor
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
//Function for Draw Borders
void drawBorder(){
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±";
		}
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	}
}
//Function for Generate Enemy
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);
}
//Function for Draw Enemy
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";
	}
}
//Function for Erase Enemy
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    ";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    ";
	}
}
//Function for Reset Enemy
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 0;
	genEnemy(ind);
}
//Function for Draw Car
void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22);
			cout<<car[i][j];
		}
	}
}
//Function for Erase Car
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
//Function for Collision of car with Enemy
int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
}
//Function for Game over
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
//Function for Update Score
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}
//Function for instructions
void instructions(){

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}
//Function for Easy play Mode
void easyPlay(){
    carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;

	system("cls");
		system("color 6F");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);

	gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";

	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch==75 ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch==77 ){
				if( carPos < 50 )
					carPos += 4;
			}
			if(ch==27){
				break;
			}
		}

		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if( collision() == 1  ){
			gameover();
			return;
		}
		Sleep(45);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);

		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;

		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;

		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;

		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

//Function for Medium  play Mode
void mediumPlay(){
    carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;

	system("cls");
		system("color 5E");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);

	gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";

	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch==75 ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch==77 ){
				if( carPos < 50 )
					carPos += 4;
			}
			if(ch==27){
				break;
			}
		}

		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if( collision() == 1  ){
			gameover();
			return;
		}
		Sleep(30);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);

		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;

		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;

		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;

		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

//Function for Hard play Mode
void hardPlay(){
    carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;

	system("cls");
		system("color CF");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);

	gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";

	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch==75 ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch==77 ){
				if( carPos < 50 )
					carPos += 4;
			}
			if(ch==27){
				break;
			}
		}

		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if( collision() == 1  ){
			gameover();
			return;
		}
		Sleep(15);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);

		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;

		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;

		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;

		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

//Function for  Modes
void modes(){
    easyPlay;
    mediumPlay;
    hardPlay;

    setcursor(0,0);

    do{
        system("cls");
        system("color B0");
        sndPlaySound("awab.wav",SND_ASYNC);
        gotoxy(50,4); cout << "----------------------";
        gotoxy(50,5); cout << "|       CAR GAME     |";
        gotoxy(50,6); cout << "----------------------";
        gotoxy(50,7); cout << "Choose your difficulty level:"<<endl;
        gotoxy(50,8); cout << "                             "<<endl;
        gotoxy(50,9); cout << "1. Easy mode."<<endl;
        gotoxy(50,10);cout << "2. Medium mode."<<endl;
        gotoxy(50,11);cout << "3. Hard mode."<<endl;
        gotoxy(50,12);cout << "4. Back."<<endl;
        char op = getch();

        switch(op) {
        case '1':
            easyPlay();
            break;
        case '2':
            mediumPlay();
            break;
        case '3':
            hardPlay();
            break;
        case '4':
    setcursor(0,0);


	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- ";
		gotoxy(10,6); cout<<" |        Car Game        | ";
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Play";
		gotoxy(10,10); cout<<"2. Instructions";
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getch();

		switch(op) {
    case '1':
        modes();
        break;
    case '2':
        instructions();
        break;
    case '3':
        exit(0);
        break;
		}

	}while(1);
        }
    }while (1);
}
int main(int argc, char** argv)
{
	setcursor(0,0);

	do{
		system("cls");


		system("color F0");
		sndPlaySound("music.wav",SND_ASYNC);
		gotoxy(50,5); cout<<" -------------------------- ";
		gotoxy(50,6); cout<<" |        Car Game        | ";
		gotoxy(50,7); cout<<" --------------------------";
		gotoxy(50,9); cout<<"1. Play";
		gotoxy(50,10); cout<<"2. Instructions";
		gotoxy(50,11); cout<<"3. Quit";
		gotoxy(50,13); cout<<"Select option: ";
		char op = getch();

		switch(op) {
    case '1':
        modes();
        break;
    case '2':
        instructions();
        break;
    case '3':
        exit(0);
        break;
		}
	}while(1);

	return 0;
	}

