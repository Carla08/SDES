#include<stdio.h>
#include <string.h>
#include <stdlib.h>

char key[] ="1100011110";
int p10[10] = {3,5,2,7,4,10,1,9,8,6};
int p8[] = {6,3,7,4,8,5,10,9};
int iP[] ={2 ,6 ,3 ,1 ,4 ,8 ,5 ,7};
int inverIP[] ={4 ,1 ,3 ,5 ,7 ,2 ,8 ,6};
int ep[] ={4 ,1 ,2 ,3 ,2 ,3 ,4 ,1};
char *s1[4][4]={{"01","00","11","10"},{"11","10","01","00"},{"00","10","01","11"},{"11","01","11","10"}};
char *s2[4][4]={{"00","01","10","11"},{"10","00","01","11"},{"11","00","01","00"},{"10","01","0","11"}};
// string[] permutate(String [] p, int length, String text){
//
// }
//STRING CONCAT

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

const char * leftShift(char text[], int shiftValue){
  char * shiftedText = malloc(sizeof(char)*5);
  int i;
  for (i = 0; i < 5; i++) {
    shiftedText[i%5] = text[(i+shiftValue)%5];
  }
  shiftedText[i] = '\0';
  return shiftedText;
}

const char * permute(int p[],int plength, char * text){
  char * permutated = malloc(sizeof(char)*(plength+1));
  int i;
  for (i=0 ; i < plength ; i++) {
    permutated[i] = text[p[i]-1];
  }
  permutated[i]='\0';
  return permutated;
}

int  bitToDecimal(char * bit){
  if (strcmp(bit,"01") || strcmp(bit,"10")) {
    return 1;
  } else if (strcmp(bit,"00") || strcmp(bit,"11")) {
    return 0;
  }
}


int * bitToCoordinates (char * string){
  int * coordinates= malloc(sizeof(int)*2);
  char * xString =malloc(sizeof(char)*3);
  char * yString= malloc(sizeof(char)*3);
  xString[0] =string[0];
  xString[1] =string[3];
  xString[2] ='\0';
  yString[0] = string[1];
  yString[1] = string[2];
  yString[2] ='\0';
  int x = bitToDecimal(xString);
  int y = bitToDecimal(yString);
  printf("X %d\n",x );
  printf("Y %d\n",y );
  coordinates[0] =x;
  coordinates[1]=y;
  return coordinates;
}

char *  sBox(char * box[4][4], char * half){
  int*  coordinates = bitToCoordinates(half);
  return box[coordinates[0]][coordinates[1]];
}
int main(){
    printf("SBox with 1111 %s\n" , sBox(s2,"1101"));
    // int * coord=bitToCoordinates("1100");
    // printf("Coordinate x %d \n" , (int) coord[1]);

    return 0;
	}
