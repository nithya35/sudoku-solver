#include<windows.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
void firstrow(int Board[9][9]);
void printsudoku();
void smile();
void print8();
void filldiagonalmatrices(int Board[9][9]);
void printBoard(int Board[9][9],int temp[9][9]);
int Valid(int Board[9][9], int row, int col, int num);
int solveSudoku(int Board[9][9]);
int findEmptyCell(int Board[9][9], int *row, int *col);
int Full(int Board[9][9]);
void remove_random(int ar[9][9],int difficulty);
void Menu(int *difficulty);
void take_input(int board[9][9]) {
    printf("Enter the Sudoku board (use numbers, _, and spaces):\n");
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            char input[5];
            scanf(" %s", input);
            if (strcmp(input, "_") == 0) {
                board[row][col] = 0;
            } else if (input[0] >= '0' && input[0] <= '9') {
                board[row][col] = atoi(input);
            } else {
                col--;
            }
        }
    }
}

void gotoxy(int x,int y){
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void Menu(int *difficulty){
	gotoxy(22,2);
	int j;
	int z;
	char name[40]="WELCOME";
	z=strlen(name);
    printf("             ");
	for(j=0;j<=16;j++){
		Sleep(50);
		printf(ANSI_COLOR_MAGENTA"\xDB"ANSI_COLOR_RESET);
	}
	for(j=0;j<=z;j++){
		Sleep(60);
		printf(ANSI_COLOR_CYAN" %c"ANSI_COLOR_RESET,name[j]);
	}
	for(j=0;j<=16;j++){
		Sleep(50);
		printf(ANSI_COLOR_MAGENTA"\xDB" ANSI_COLOR_MAGENTA);
	}
    printsudoku();
    smile();
	gotoxy(23,25);
	printf(ANSI_COLOR_CYAN"Enter Difficulty(1 for easy,2 for moderate and 3 for hard):"ANSI_COLOR_RESET);
    int d;
	scanf("%d",&d);
	if(d==1||d==2||d==3){
        *difficulty=d;
    }
	else{
		gotoxy(30,6);
		printf("Invalid input");
		Sleep(700);
		system("cls");
		Menu(difficulty);
}
}
int Makegame(int Board[9][9],int difficulty){     
    filldiagonalmatrices(Board);
    solveSudoku(Board);
    remove_random(Board,difficulty);
    }

int PrintSolution(int ar[9][9],int temp[9][9]){
    solveSudoku(ar);
    printBoard(ar,temp);
}

void firstrow(int Board[9][9]){
    srand(time(NULL));
    int order[9];
    for (int i=0;i<9;i++){
        order[i]=i+1;
    }
    for (int i=9-1;i>0;i--){
        int j=rand()%(i+1);
        int temp=order[i];
        order[i]=order[j];
        order[j]=temp;
    }
    for(int i=0;i<9;i++){
        Board[0][i]=order[i];
    }
}
void filldiagonalmatrices(int Board[9][9]){
    srand(time(NULL));
    for(int x=0;x<3;x++){
        int k=0;
        for(int i=3*x;i<3*x+3;i++){
            for(int j=3*x;j<3*x+3;j++){
                Board[i][j]=++k;
            }
        } 
        for(int i=3*x;i<3*x+3;i++){
            for(int j=3*x;j<3*x+3;j++){
                int randrow=3*x+rand()%3;
                int randcol=3*x+rand()%3;
                int temp=Board[randrow][randcol];
                Board[randrow][randcol]=Board[i][j];
                Board[i][j]=temp;
            }
        }
    }
}

void printBoard(int Board[9][9], int temp[9][9]) {
    system("cls");
    gotoxy(30, 1);
    printf("SUDOKU:\n");
    for (int i = 0; i < 9; i++){
        gotoxy(31, 2 + i);
        for (int j = 0; j < 9; j++){
            if (Board[i][j] == 0){
                Sleep(5);
                printf("_   ");
            } else if (Board[i][j]!=temp[i][j]){
                Sleep(5);
                printf("%d   ", Board[i][j]);
            } else {
                Sleep(5);
                printf(ANSI_COLOR_GREEN"%d   "ANSI_COLOR_RESET, Board[i][j]);
            }
        }
        printf("\n\n");
    }
}

int Valid(int Board[9][9], int row, int col,int num){
    for (int i = 0; i < 9; i++) {
        if (Board[row][i] == num || Board[i][col] == num) {
            return 0;
        }
    }
    int subgridRow = (row / 3) * 3;
    int subgridCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j<3;j++){
            if (Board[subgridRow+i][subgridCol+j]==num){
                return 0;
            }
        }
    }
    return 1;
}

int solveSudoku(int Board[9][9]){
    int row,col;
    if (!findEmptyCell(Board,&row,&col)){
        return 1;
    }
    for (int num=1;num<=9;num++){
        if(Valid(Board,row,col,num)){
            Board[row][col]=num;
            if(solveSudoku(Board)){
                return 1;
            }
            Board[row][col]=0;
        }
    }
    return 0;
}

int findEmptyCell(int Board[9][9],int *row,int *col){
    for(*row=0;*row<9;(*row)++){
        for(*col=0;*col<9;(*col)++){
            if (Board[*row][*col]==0){
                return 1;
            }
        }
    }
    return 0;
}

int Full(int Board[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(Board[i][j]==0){
                return 0;
            }
        }
    }
    return 1;
}
void remove_random(int ar1[9][9],int difficulty){
    int k;
    switch(difficulty){
        case 1: 
        k=20;
        break;
        case 2:
        k=35;
        break;
        case 3:
        k=50;
        break;
        default:
        break;
    }
    int randrow,randcol;
    for(int i=0;i<k;i++){
        randrow=rand()%9;
        randcol=rand()%9;
        if(ar1[randrow][randcol]==0){
            i--;
        }
        ar1[randrow][randcol]=0;
    }
}
void printsudoku(){
    gotoxy(23,8);//1st row
    print8();
    printf("    \xDB      \xDB    \xDB\xDB");
    print8();
    printf("    ");
    print8();
    printf("    \xDB        \xDB\xDB     \xDB      \xDB");
    Sleep(50);
    gotoxy(23,9);//2nd row
    printf("\xDB       ");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB       \xDB");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,10);//3rd row
    printf("\xDB       ");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB      \xDB ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,11);//4th row
    printf("\xDB       ");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB     \xDB  ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,12);//5th 
    printf("\xDB       ");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB    \xDB   ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,13);//6th
    printf("\xDB       ");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB   \xDB    ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,14);//7th
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB  \xDB     ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,15);//8th
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB \xDB      ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,16);//9th
    printf("       \xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB \xDB      ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,17);//10th
    printf("       \xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB  \xDB     ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,18);//11th
    printf("       \xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB   \xDB    ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,19);//12th 
    printf("       \xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB    \xDB   ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,20);//13th row
    printf("       \xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB     \xDB  ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,21);//14th row
    printf("       \xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB      \xDB ");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,22);//15TH row
    printf("       \xDB");//S
    printf("    \xDB      \xDB    ");
    printf("\xDB\xDB\xDB      \xDB    \xDB      \xDB    \xDB       \xDB");
    printf("       \xDB      \xDB");
    Sleep(50);
    gotoxy(23,23);//16th row
    print8();
    printf("    ");
    print8();
    printf("    \xDB\xDB");
    print8();
    printf("    ");
    print8();
    printf("    \xDB        \xDB\xDB     ");
    for(int i=0;i<8;i++){
        printf(ANSI_COLOR_MAGENTA"\xDB"ANSI_COLOR_RESET);
    }
}
void print8(){
    for(int i=0;i<8;i++){
        printf(ANSI_COLOR_MAGENTA"\xDB");
    }
}
void smile(){
    gotoxy(63,11);
    printf(ANSI_COLOR_MAGENTA"\xDB");
    Sleep(100);  
    printf("  \xDB"ANSI_COLOR_RESET);
    gotoxy(63,19);
    Sleep(50);
    printf(ANSI_COLOR_MAGENTA"\xDB  ");
    Sleep(100);  
    printf("\xDB"ANSI_COLOR_RESET);
    Sleep(50);
    gotoxy(63,20);
    for(int i=0;i<4;i++){
        Sleep(50);
    printf(ANSI_COLOR_MAGENTA"\xDB"ANSI_COLOR_RESET);
    }    
}