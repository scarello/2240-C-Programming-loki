/*
Name     : Michael Monical
Class    : 2240-850
Program #    : 2 Word Search
Due Date     : Sept. 19, 2016 

Honor Pledge:  On my honor as a student of the University
of Nebraska at Omaha, I have neither given nor received
unauthorized help on this homework assignment.

NAME: Michael Monical
NUID: 9263
EMAIL: mikemonical@gmail.com

Partners:None

This is a word search solver. It will read in a data file that will be space delimited then the words
below will be read in one at a time. After that it will write a solution file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findFirstLetter(int i, int j, int k, char **puzzle, char **words, char **solution);
int findSecondLetter(int i, int j, int k, int l, int m, char **puzzle, char **words, char **solution);
int findRest(int i, int j, int k, int l, int m, int a, int b, int c, char **puzzle, char **words, char **solution);
int main(int argc, char *argv[]){
   
    int i, j, k, l, m, x, flag;
    char *buf;
    char **puzzle;
    char **words;
    char **solution;
    FILE *fp;
    char *writeString;
    i = 0;
    j = 0;
    buf = calloc(60, sizeof(char));
    writeString = calloc(100, sizeof(char));
    puzzle = (char **)calloc(50, sizeof(char*));
    for (k = 0; k < 50; k++){
        puzzle[k] = (char *)calloc(50, sizeof(char));
    }
    words = (char **)calloc(100, sizeof(char*));
    for (k = 0; k < 100; k++){
        words[k] = (char *)calloc(51, sizeof(char));
    }
    solution = (char **)calloc(50, sizeof(char*));
    for (k = 0; k < 50; k++){
        solution[k] = (char *)calloc(50, sizeof(char));
    }
    while (fgets(buf, 60, stdin) != NULL){
        if (buf[1] == ' '){
            puzzle[i][0] = buf[0];
            x = 1;
            for (l = 2; l < 50 && buf[l+1] != '\n'; l+=2){
                puzzle[i][x] = buf[l];
                x++;
            }
            puzzle[i][x] = buf[l];
            i++;
        }   
        else{
            strcpy(words[j], buf);
            j++;
        }
    }


    for (k = 0; k < j; k++){
        flag = findFirstLetter(i, j, k ,puzzle, words, solution);
        if ( flag == 1){
            for (l = 0; l < i; l++){
                for (m = 0; m < i; m++){
                    if ( solution[l][m] != '0'){
                    }
                }
            }
        }
    }
    fp = fopen("solution", "w");
    for (k = 0; k < i; k++){
        writeString = calloc(100, sizeof(char));
        x = 0;
        for (l = 0; l < i; l++){
            if ( solution[k][l] != 0){
       /*         printf("%c ", solution[k][l]);*/
                writeString[x] = solution[k][l];
                writeString[x+1] = ' ';
            }
            else{
      /*          printf("  "); */
                writeString[x] = ' ';
                writeString[x+1] = ' ';
            }
            x = x + 2;
        }
        writeString[x] = '\n';
        fputs(writeString, fp);
        free(writeString);    
      /*  printf("\n"); */
    }
    return 0;
}

/*
Method Name     :findFirstLetter
Parameters      :ints i, j, k, char pointers puzzle, words, solution
Return Value(s) :flag int (boolean)
Partners        :None
  Description     :This looks for the first letter then returns to the main.
*/
int findFirstLetter(int i, int j, int k, char **puzzle, char **words, char **solution){

    char firstLetter = words[k][0];
    int l, m, flag;
    flag = 0;
    for (l = 0; l < i && flag != 1; l++){
        for (m = 0; m < i && flag != 1; m++){
            if (firstLetter == puzzle[l][m]){
                flag = findSecondLetter(i, j, k, l, m,  puzzle, words, solution);
            }
        }
    }
    if (flag == 1){
        solution[l-1][m-1] = firstLetter;
    }
    return flag;
    

}
/*
Method Name     :findSecondLetter
Parameters      :ints i, j, k, l, m, char pointers puzzle, words, solution
Return Value(s) :flag int (boolean)
Partners        :None
Description     :This looks for the second letter then returns to the main. If found near first letter.
*/

int findSecondLetter(int i, int j, int k, int l, int m, char **puzzle, char **words, char **solution){

    int a, b, flag;
    char secondLetter = words[k][1];
    flag = 0;
    for (a = l - 1; a <= l + 1 && flag != 1; a++){
        if ( !(a < 0 || a >= i) ){
            for (b = m - 1; b <= m + 1 && flag != 1; b++){
                if ( (!(b < 0 || b >= i))  ){
                    if ((l != a) || (m != b)){
                        if (secondLetter == puzzle[a][b]){
                            flag = findRest(i, j, k, a, b, a - l, b - m, 2, puzzle, words, solution);
                        }
                    }
                }
            }
        }
    }
    if (flag == 1){
        solution[a-1][b-1] = secondLetter;
    }
    return flag;
}   
/*
  Method Name     :findRest
  Parameters      :ints i, j, k, l, m, a, b, c char pointers puzzle, words, solution
  Return Value(s) :flag int (boolean)
  Partners        :None
  Description     :This looks for the rest of the letters in the same line that it foudn the first and second letter
  then returns to the main. 
*/


int findRest(int i, int j, int k, int l, int m, int a, int b, int c, char **puzzle, char **words, char **solution){
    int flag; 
    char findCharacter = words[k][c];
    flag = 0;
    if ( findCharacter == '\n' )
        return 1;
    if ( (l + a < 0) || (l + a >= i) || (m + b < 0) || (m + b >= i) )
        return 0;
    if ( puzzle[ l + a ][ m + b ] != findCharacter )
        return 0;
    flag = findRest(i, j, k, l + a, m + b, a, b, c + 1, puzzle, words, solution);
    if (flag == 1)
        solution[ l + a][ m + b] = findCharacter;
    return flag;
}



