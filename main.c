#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char key[] ="1100011110";
int p10[10] = {3,5,2,7,4,10,1,9,8,6};
int p8[] = {6,3,7,4,8,5,10,9};
int iP[] ={2 ,6 ,3 ,1 ,4 ,8 ,5 ,7};
int inverIP[] ={4 ,1 ,3 ,5 ,7 ,2 ,8 ,6};
int ep[] ={4 ,1 ,2 ,3 ,2 ,3 ,4 ,1};
int p4[] = {2,4,3,1};


//LEFT SHIFT
char * leftShift(char text[], int shiftValue){
  char * shiftedText = malloc(sizeof(char)*5);
  short i;
  for (i = 0; i < 5; i++) {
    shiftedText[i%5] = text[(i+shiftValue)%5];
  }
  shiftedText[i] = '\0';
  return shiftedText;
}
//SPLIT
char * split(char text[],bool keep_left, size_t strLenght)
 {
  short half_size = strLenght/2;
  char * half_array = malloc(sizeof(char)*(strLenght/2+1));
  short i;
  if(keep_left){
    for (i=0; i<half_size; i++){
      half_array[i] = text[i];
    }
  } else {
    for (i=half_size; i<strLenght; i++){
      half_array[i%half_size] = text[i];
    }
  }
  half_array[half_size] = '\0';
  return half_array;
}
//STRING CONCAT
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
//PERMUTE
char * permute(int p[],int plength, char * text){
  char * permutated = malloc(sizeof(char)*(plength+1));
  int i;
  for (i=0 ; i < plength ; i++) {
    permutated[i] = text[p[i]-1];
  }
  permutated[i]='\0';
  return permutated;
}
//XOR
char * xor (char* string1, char* string2){
  short string_lenght = strlen(string1);
  char * stringXOR = malloc(string_lenght * sizeof(char));
  short i;
  for (i=0; i<string_lenght; i++){
    stringXOR[i] = (char)(string1[i]^string2[i]);
    printf("XOR:%01X \n",(int)stringXOR[i]);
  }
  return stringXOR;
}
//KEY GENERATOR 
char** KeyGenerator (char* key){
  char *permutated_key = permute(p10,10,key);
  char *left = split(permutated_key,true,10);
  char *right = split(permutated_key,false,10);
  char *shift_one_left = leftShift(left,1);
  char *shift_one_right = leftShift(right,1);
  char *key1 = permute(p8,8,concat(shift_one_left,shift_one_right));
  char *shift_two_left = leftShift(left,3);
  char *shift_two_right = leftShift(right,3);
  char *key2 = permute(p8,8,concat(shift_two_left,shift_two_right));
  char **keys_array = malloc(2 * sizeof(char*));
  short i;
  for (i = 0; i<2; i++){
    keys_array[i] = malloc(8*sizeof(char));
  }
  keys_array[0] = key1;
  keys_array[1] = key2;
  return keys_array;
}
//FK MASTER FUNCTION /*WARNING: needs testing*/
char** FK(char* left,char* right, key){
  char *EP = permute(ep,8,right);
  char *EPxorKey = xor(EP,key);
  char *left_half = split(EPxorKey,true,8);
  char *right_half = split(EPxorKey,false,8);
  char *sLeft = sBox(S0, left_half);
  char *sRight =  sBox(S1,right_half);
  char *sJoin = concat(sLeft,sRight);
  char *per4 = permute(p4,4,sJoin);
  char *leftxorPer4 = xor(left, per4);
  char **leftright_array = malloc(2 * sizeof(char*));
  short i;
  for (i = 0; i<2; i++){
    leftright_array[i] = malloc(4*sizeof(char));
  }
  leftright_array[0] = leftxorPer4;
  keys_array[1] = right;
  return leftright_array;
}
//MAIN
int main(){
		// printf("The shiftedTex -> %s \n",leftShift("10000",2));
    //printf("The permutated text -> %s\n",permute(p10, 10, key));
    //printf("Half array is %s\n",split("1100",false,4));
    char **keys_array = KeyGenerator("1100011110");
    //printf("KEY #1 is %s\n", keys_array[0]);
    //printf("KEY #2 is %s\n", keys_array[1]);
    xor("1100", "0011");
    return 0;
	}
