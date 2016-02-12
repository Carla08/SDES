#include<stdio.h>
#include <string.h>
#include <stdlib.h>

char key[] ="1100011110";
int p10[10] = {3,5,2,7,4,10,1,9,8,6};
int p8[] = {6,3,7,4,8,5,10,9};
int iP[] ={2 ,6 ,3 ,1 ,4 ,8 ,5 ,7};
int inverIP[] ={4 ,1 ,3 ,5 ,7 ,2 ,8 ,6};
int ep[] ={4 ,1 ,2 ,3 ,2 ,3 ,4 ,1};

// string[] permutate(String [] p, int length, String text){
//
// }

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
int main(){
		// printf("The shiftedTex -> %s \n",leftShift("10000",2));
    printf("The permutated text -> %s\n",permute(p10, 10, key));
    return 0;
	}
