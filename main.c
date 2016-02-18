
#include <stdio.h>
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

char * pairs[245][2];
char *s1[4][4]={{"01","00","10","11"},{"11","10","01","00"},{"00","10","01","11"},{"11","01","11","10"}};
char *s2[4][4]={{"00","01","10","11"},{"10","00","01","11"},{"11","00","01","00"},{"10","01","00","11"}};

//STRING CONCAT
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

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

int  bitToDecimal(char * bit){
    int test = strcmp(bit,"00");
    if (!strcmp(bit,"00")) {
        return 0;
    } else if (!strcmp(bit,"01"))
    {
        return 1;
    }else if (!strcmp(bit,"10"))
    {
        return 2;
    }else {
        return 3;
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
    printf("Coordinates: x,y %d,%d\n", x,y);
    coordinates[0] =x;
    coordinates[1] =y;
    return coordinates;
}

char *  sBox(char * box[4][4], char * half){
    int*  coordinates = bitToCoordinates(half);
    return box[coordinates[0]][coordinates[1]];
}

//XOR
char * xor (char* string1, char* string2){
    short string_lenght = strlen(string1);
    char * stringXOR = malloc(string_lenght * sizeof(char));
    short i;
    for (i=0; i<string_lenght; i++){
        if (string1[i] != string2[i]) {
            stringXOR[i]= '1';
        } else  {
            stringXOR[i]= '0';
        }
    }
    printf("XORed String: %s\n", stringXOR);
    return stringXOR;
}

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
char** FK(char* left,char* right, char* key){
    printf("LEFT: %s, RIGHT: %s, KEY: %s \n", left,right,key);
    char *EP = permute(ep,8,right);
    char *EPxorKey = xor(EP,key);
    printf("EPxorKey%s\n", EPxorKey);
    char *left_half = split(EPxorKey,true,8);
    char *right_half = split(EPxorKey,false,8);
    char *sLeft = sBox(s1, left_half);
    char *sRight =  sBox(s2,right_half);
    printf("SBOX left: %s right %s\n", sLeft,sRight);
    char *sJoin = concat(sLeft,sRight);
    char *per4 = permute(p4,4,sJoin);
    char *leftxorPer4 = xor(left, per4);
    printf("leftxorPer4 :%s     left:%s    per4:%s \n ",leftxorPer4,left,per4);
    char **leftright_array = malloc(2 * sizeof(char*));
    short i;
    for (i = 0; i<2; i++){
        leftright_array[i] = malloc(4*sizeof(char));
    }
    // printf("leftxorPer4 : %s\n", leftxorPer4);
    leftright_array[0] = leftxorPer4;
    leftright_array[1] = right;
    return leftright_array;
}
//ENCRYPT MASTER
char * encrypt (char* plaintext, char * key){
    char *permutated_plain = permute(iP, 8, plaintext);
    printf("PERMUTATED PLAIN: %s\n",permutated_plain);
    char **keys_array = KeyGenerator(key);
    char *left = split(permutated_plain,true,8);
    printf("LEFT OF PERMUTATED PLAIN: %s\n", left);
    char *right = split(permutated_plain,false,8);
    printf("RIGHT OF PERMUTATED PLAIN: %s\n", right);
    char *key1 = keys_array[0];
    char *key2 = keys_array[1];
    printf("KEY1: %s\n KEY2: %s\n",keys_array[0],keys_array[1]);
    char **fk1 = FK(left,right,key1);
    //swap block
    printf("BEFORE SWAP: LEFT FK1: %s RIGHT FK1: %s\n",fk1[0],fk1[1]);
    char *left2 = fk1[1]; //swp
    char *right2 = fk1[0]; //swp
    printf("Left and right %s %s\n",left2,right2 );
    char **fk2 = FK(left2,right2,key2);
    char *left_final = fk2[0];
    char *right_final = fk2[1];

    char *ciphertext = permute(inverIP,8,concat(left_final,right_final));
    return ciphertext;
}

void readPairs(char * filename, char ** plaintext,char ** ciphertext){
    FILE *fp;
    char ch;
    fp = fopen(filename,"r"); // read mode
    if( fp == NULL ){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    short lineNumber=0;
    short column;
    char * string=malloc(sizeof(char)*9);
    char line[19];
    while (fgets(line, sizeof(line), fp) ) {
        char * actualLine= strtok(line,",\0");

        for (column = 0; column < 2 && actualLine != NULL ; column++) {
            if(actualLine[8]=='\n'){
                actualLine[8]=(char)'\0';
            }
            if (column==0){
                plaintext[lineNumber]=malloc(sizeof(char)*9);
                plaintext[lineNumber]=actualLine;
            }else if (column ==1){
                ciphertext[lineNumber]=malloc(sizeof(char)*9);
                ciphertext[lineNumber]=actualLine;
            }


            actualLine=strtok(NULL, ",");
        }
        printf("Actual Line %d %s  %s\n",lineNumber,plaintext[lineNumber], ciphertext[lineNumber]);
        lineNumber++;

    }



    fclose(fp);

}
//MAIN
int main(int argc, char *argv[]){
    char **plaintext = malloc(sizeof(char*)*245);
    char **ciphertext = malloc(sizeof(char*)*245);
    readPairs("C:\\Users\\mario\\Documents\\GitHub\\SDES\\pares.txt", plaintext, ciphertext);

    // printf("The shiftedTex -> %s \n",leftShift("10000",2));
    //printf("The permutated text -> %s\n",permute(p10, 10, key));
    //printf("Half array is %s\n",split("1100",false,4));
    //char **keys_array = KeyGenerator("1100011110");
    //char **fk_test = FK("0010","0010","1100011110");
    //printf("ciphertext :%s\n", encrypt("00101000", "1100011110"));
    // printf("Right of FK :%s\n", fk_test[1]);
    //printf("KEY #1 is %s\n", keys_array[0]);
    //printf("KEY #2 is %s\n", keys_array[1]);
    //xor("1100", "0011");
    return 0;
}
