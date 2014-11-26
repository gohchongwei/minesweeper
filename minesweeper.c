#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define SEED time(0)
void generateBoard(char board[][10], int n)
{
   int i, j;
   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         board[i][j] = '.';
   for (i=1; i<n-1; i++)
      for (j=1; j<n-1; j++)
      {
         if ((rand()*rand()) % 2 == 0)
            board[i][j] = '.';
         else
            board[i][j] = '*';
      }
   return;
}
void printBoard(char board[][10], int n)
{
   int i, j;
   for (i=0; i<n; i++)
   {
      for (j=0; j<n; j++)
         printf("%2c", board[i][j]);
      printf("\n");
   }
   return;
}
void countMine(char board[][10], int r, int c)
{
   int i, j;
   int count=0;
   for (i=r-1; i<=r+1; i++)
      for (j=c-1; j<=c+1; j++)
         if (board[i][j] == '*')
            count++;

   board[r][c] = count + '0';
   return;
}
void sweep(char board[][10], int r, int c)
{
   int i, j;
   for (i=r-1; i<=r+1; i++)
      for (j=c-1; j<=c+1; j++)
         if (board[i][j] == '.')
         {
            countMine(board, i, j);
            if (board[i][j] == '0')
               sweep(board, i, j);
         }
   return;
}
bool checkWin(char board[][10], int n)
{
   int i, j;
   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         if (board[i][j] == '.')
            return false;
   return true;
}
int main(void)
{       
   bool win = false, lose = false;
   int n, r, c;
   int i, j;
   char board[9][10]={{'\0'}}, board2[9][10]={{'\0'}};

   srand((unsigned int) SEED);

   printf("Enter minefield n x n minefield dimensions (from 5 up to 9): ");
   scanf("%d", &n);

   generateBoard(board, n);
   printf("Start playing by entering a location to open.\n");
   
   /*Setting up the minefield for play*/
   for (i=0; i<n; i++)
   {
      countMine(board, 0, i);
      if (board[0][i] == '0')
         sweep(board, 0, i);
      countMine(board, i, 0);
      if (board[i][0] == '0')
         sweep(board, i, 0);
      countMine(board, n-1, i);
      if (board[n-1][i] == '0')
         sweep(board, n-1, i);
      countMine(board, i, n-1);
      if (board[i][n-1] == '0')
         sweep(board, i, n-1);
   }

   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
      {
         board2[i][j] = board[i][j];
         if (board2[i][j] == '*')
            board2[i][j] = '.';
      }
   
   printBoard(board2, n);     
   
   /*Playing the game*/
   while (!win && !lose)
   {
      printf("Enter location: ");
      scanf("%d%d", &r, &c);
      r--; c--;
      
      if (board[r][c] == '*')
      {
            printBoard(board, n);
            lose = true;
         }
      else
      {
         countMine(board, r, c);

         if (board[r][c] == '0')
            sweep(board, r, c);

         for (i=0; i<n; i++)
            for (j=0; j<n; j++)
            {
               board2[i][j] = board[i][j];
               if (board2[i][j] == '*')
                  board2[i][j] = '.';
            }
         printBoard(board2, n);      
         win = checkWin(board, n);
      }
   }
   
   /*End the game*/
   if (win)
      printf("Congratulations, you win! =)\n");
   else
      printf("You lose! Try harder next time.\n");

   return 0;
}
