//Program 5 -- THE GAME
//Aaron
//Checkers red vs black
//English is important but checkers is importanter

#include<stdio.h> //C library to perform Input/Output operations

//Define constants pre-compiling
#define row 8       //Size of standard playing board for international draughts
#define columns 8   //As above, a noble game of 8X8
#define FREE 1     //available unocnipied squares
#define RED 2       //player 1 is red checkers
#define BLACK 3     //player 2 is black checkers
#define REDKING 4   //the simple men makes his way to the kings row and gains the power...to move backwards!
#define BLACKKING 5 //a challenger approaches...

#define ISRED(c)   (c == RED || c == REDKING)
#define ISBLACK(c) (c == BLACK || c == BLACKKING))
#define ISFREE(c)  (c == 1)

void ShowDisplay(int d[][columns]);
void Val(int d[row][columns], int i, int j, int k, int l);
char Pieces(int i);
void FormatDisplay(int d[][columns]);
int Play(int d[][columns], int player,int i,int j,int k,int l);

//Format the display

void FormatDisplay(int d[][columns])
{
    int rn, cn;

    //print top horizontal row
    printf("  +---+---+---+---+---+---+---+---+\n");

    //previosuly set to 8
    for (rn=0; rn <  row; ++ rn) {
        //print vertical columns between top and bottom of board
        printf("%d |", rn+1);
        for (cn=0; cn<columns; ++ cn)
        {
            printf(" %c |", Pieces(d[rn][cn]) );
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
       //identifiers, player inputs number floowed by letter (eg 1b)
       printf("    a   b   c   d   e   f   g   h\n");
}

void Val(int d[row][columns], int i, int j, int k, int l) {
    int temp;
    printf("SWAP: %d,%d to %d,%d\n", i, j, k, l);

    temp = d[i][j];

    d[i][j] = d[k][l];

    d[k][l] = temp;
}
//set pieces to dispaly their character on the board 0=NotAvailable 1=Empty 2=Red 3=Black
char Pieces(int i) {
    switch(i)
    {
  	case 0:
            return ' ';
        case 1:
            return '-';
        case 2:
            return 'R';
        case 3:
            return 'B';
    }
    return ('?');
}
//Movements and capture and removal
int Play(int d[][columns], int player,int i,int j,int k,int l)
{
    int RowJump;
    int ColumnJump;

    if(player == RED){
        //give updated movements based on input
        printf("RED move from %d,%d to %d,%d\n", i, j, k, l);
    } else {
        printf("BLACK move from %d,%d to %d,%d\n", i, j, k, l);
    }
  //Just some rules for those trying to pull a sneaky, but im sure you'll not break any!
    if(i < 0 && row <= i){
        printf("i Is off the grid\n");
        return -1;
    }
    if(j < 0 && columns <= j){
        printf("j Is off the grid");
        return -1;
    }

    if(k < 0 && row <= k){
        printf("k Is off the grid");
        return -1;

    }
    if(l < 0 && columns<= l){
        printf("l Is off the grid\n");
        return -1;
    }

    if(player == RED){
        if(d[i][j] != RED){
            printf("They're not your pieces, move your own colour\n");
            return -1;
        }
    } else {
        if(d[i][j] != BLACK){
            printf("They're not your pieces, move your own colour\n");
            return -1;
        }
    }

    if(d[k][l] != FREE){
        printf("Grid not empty");
        return -1;
    }

    if(player == RED){
        if(i >= k){
            printf("Red, you can only move towards the center of the borard unless you have a KING\n");
            return -1;
        }
    } else {
        if(i <= k){
            printf("BLACK, you can only move towards the center of the borard unless you have a KING\n");
            return -1;
        }
    }

    if(i - k == -1 || i - k == 1){
        if(j - l == 1 || j - l == -1){
            Val(d,i,j,k,l);
            return 0;
        }
    }

    if(i - k == -2 || i - k == 2){
        if(j - l == -2 || j - l == 2){
            if(i < k){ 
                RowJump = i + 1;
            } else { 
                RowJump = i - 1;
            }

            if(j < l){
                ColumnJump = j + 1;
            } else {
                ColumnJump = j - 1;
            }

            if(player==RED && d[RowJump][ColumnJump]!=BLACK)
            {
                printf("Enemeny is not Black at %d%d",RowJump, ColumnJump);
                return -1;
            }
            if(player==BLACK && d[RowJump][ColumnJump] != RED){
                printf("you can only jump over an enemy piece\n");
                return -1;
            }

            d[RowJump][ColumnJump] = 1;
            Val(d,i,j,k,l);
            return 0;
        }
    }

    //just another sneaky move, you know the rules!
    printf("Jumps can only be diagonal\n");
    return -1;

}

int main()
{
    //switch case assignment 0=NotAvailable 1=Empty 2=Red 3=Black
    //startting line up 12X12
    //Game Instructions *change the location of these so they appear only once
    printf("Instructions: Enter peice to move eg  '6a'. Press enter.\n");
    printf("Type the destination coordinates. eg '5b' . Press enter.\n");
    printf("Next player takes their turn, using the same method.\n");

	int r,c;
	int pr, pb;
	int i, k;
	char j, l;
	int d[row][columns]={
    {0,2,0,2,0,2,0,2},
    {2,0,2,0,2,0,2,0},
    {0,2,0,2,0,2,0,2},
    {1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1},
    {3,0,3,0,3,0,3,0},
    {0,3,0,3,0,3,0,3},
	{3,0,3,0,3,0,3,0}};

    for(;;){
        //Black player turn
        FormatDisplay(d);
        while(1){
            printf("Black Piece Turn: ");
            scanf("%d%c",&i,&j);
    	    printf("Move Piece to: ");
        	scanf("%d%c",&k,&l);
        	if(Play(d, BLACK, i-1,j - 'a',k-1,l - 'a') == 0)

        	    break;

        	printf("Error, Move not allowed, Please try again!\n");
        }

        //Reds players move
        FormatDisplay(d);
        while(1){
            printf("Red's turn: ");
            scanf("%d%c",&i,&j);
    	    printf("to :");
        	scanf("%d%c",&k,&l);
        	if(Play(d, RED, i-1,j - 'a',k-1,l - 'a') == 0)

                break;

        	printf("Error, Move not allowed, Please try again!\n");
        }
    }
    return 0;
}