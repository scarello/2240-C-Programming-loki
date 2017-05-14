/*
Name     : Michael Monical
Class    : 2240-850
Program #    : 3 Virutal Machine
Due Date     : March 13, 2017 

Honor Pledge:  On my honor as a student of the University
of Nebraska at Omaha, I have neither given nor received
unauthorized help on this homework assignment.

NAME: Michael Monical
NUID: 9263
EMAIL: mikemonical@gmail.com

Partners:None

This assignment has you creating your own virtual computer with its own 
limited instruction set and language.   

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct machineState{
    int *memory;
    int accumulator, instructionCounter, instructionRegister, operationCode, operand;
}machineState;
int compile(machineState mS);
int execute(machineState mS);
void read(machineState mS);
void write(machineState mS);
void print(machineState mS);
int load(machineState mS);
void store(machineState mS);
int add(machineState mS);
int subtract(machineState mS);
int divide(machineState mS);
int multiply(machineState mS);
int modulus(machineState mS);
int bran(machineState mS);
int brng(machineState mS);
int brzr(machineState mS);
void printM(machineState mS);


int main(int argc, char *argv[]){
    machineState mS;
    mS.memory = calloc(100, sizeof(int));
    
    if(!compile(mS))
        execute(mS);
   /* for(i = 0; i < 6; i++){
            printf("%d\n", mS.memory[i]);
    }*/
    free(mS.memory);
    return 0;
}
/*
Method Name     :compile
Parameters      :struct machineState mS
Return Value(s) :int true or false
Partners        :None
Description     :A compile error will stop the compiling process and not 
attempt to execute the program
*/



int compile(machineState mS){
    int word, location, count,flag;
    char *buf;
    char *token;
    buf = calloc(20, sizeof(char));
    location = 0;
    flag = 0;
    count = 0;

    while (fgets(buf, 20, stdin) != NULL){
            token = strtok(buf," ");    
            word = 0;        
            location = atoi(token);
            token = strtok(NULL, " ");


            if(!strcmp(token, "READ"))
                word = 1000;
            else if(!strcmp(token, "WRIT"))
                word = 1100;
            else if(!strcmp(token, "PRNT"))
                word = 1200;
            else if(!strcmp(token, "LOAD"))
                word = 2000;
            else if(!strcmp(token, "STOR"))
                word = 2100;
            else if(!strcmp(token, "SET"));
            else if(!strcmp(token, "ADD"))
                word = 3000;
            else if(!strcmp(token, "SUB"))
                word = 3100;
            else if(!strcmp(token, "DIV"))
                word = 3200;
            else if(!strcmp(token, "MULT"))
                word = 3300;
            else if(!strcmp(token, "MOD"))
                word = 3400;
            else if(!strcmp(token, "BRAN"))
                word = 4000;
            else if(!strcmp(token, "BRNG"))
                word = 4100;
            else if(!strcmp(token, "BRZR"))
                word = 4200;
            else if(!strcmp(token, "HALT")){
                word = 9900;
                flag = 1;
            }
            else{
                printf("Unknown command - Unrecognized command word, they are case sensitive: %s\n", token);
                return 1;
            }
    
            token = strtok(NULL, "\n");
          /*  printf("%d\n",atoi(token)); */
            word = word + atoi(token); 
            if(word > 9999){
                    printf("Word overflow - attempts to place a word in memory that it is larger than 4 digits: %d\n", word);
                    return 1;
            }
            mS.memory[location] = word;
           /* printf("%d\n", word);*/
            count++;


    }
    
    if(!flag){
        printf("No HALT - No HALT command is ever given\n");
        return 1;
    }
   /*
    for(word = 0; word < count; word++){
            printf("%d\n", mS.memory[word]);
    }*/
    free(buf);
    return 0;
}
/*
Method Name     :execute
Parameters      :struct machineState mS
Return Value(s) :int boolean true or false 1/0
Partners        :None
Description     : runtime error will cause a HALT, terminating 
execution and output the state of the registers and memory
*/

int execute(machineState mS){
    mS.accumulator = 0;

    for(mS.instructionCounter = 0; mS.memory[mS.instructionCounter] != 9999; mS.instructionCounter++){
            mS.instructionRegister = mS.memory[mS.instructionCounter];
            mS.operationCode = mS.instructionRegister / 100;
            mS.operand = mS.instructionRegister % 100;
            switch(mS.operationCode){
                case 10 : 
                    read(mS);
                    break;
                case 11 :
                    write(mS);
                    break;
                case 12 :
                    print(mS);
                    break;
                case 20 :
                    mS.accumulator = load(mS);
                    break;
                case 21 :
                    store(mS);
                    break;
                case 30 :
                    mS.accumulator = add(mS);
                    break;
                case 31 :
                    mS.accumulator = subtract(mS);
                    break;
                case 32 :
                    mS.accumulator = divide(mS);
                    break;
                case 33 :
                    mS.accumulator = multiply(mS);
                    break;
                case 34 :
                    mS.accumulator = modulus(mS);
                    break;
                case 40 :
                    mS.instructionCounter = bran(mS);
                    break;
                case 41 :
                    mS.instructionCounter = brng(mS);
                    break;
                case 42 :
                    mS.instructionCounter = brzr(mS);
                    break;
                default :
                    printf("Unknown command - Unrecognized command code at address: %d \n", mS.instructionCounter);
                    printM(mS);
                    return 1;
            }
    

    }
    printM(mS);
    return 0;
}
/*
Method Name     :read
Parameters      :Struct machineState mS
Return Value(s) :NONE
Partners        :None
Description     :retrieves a value from the user and places it in the given 
address
*/

void read(machineState mS){
        char *input;
        int inputAsInt;
        
        if(mS.operand > 0 || mS.operand < 100){
            stdin = fopen("/dev/tty", "r");
            input = calloc(20, sizeof(char));
            fgets(input, 20, stdin);
            inputAsInt = atoi(input);
            if(inputAsInt <= 9999 && inputAsInt >= -9999){  
                mS.memory[mS.operand] = inputAsInt;
            }
            else{
                printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
                printM(mS);
                exit(1);
            }
            
        }
        else{
            printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
            printM(mS);
            exit(1);
        }



}
/*
Method Name     :write
Parameters      :struct machineState mS
Return Value(s) :NONE
Partners        :None
Description     :Outputs a word from the given address to the terminal
*/

void write(machineState mS){

        if(mS.operand > 0 || mS.operand < 100){
            printf("%04d\n", mS.memory[mS.operand]);   
        }
        else{
            printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
            printM(mS);
            exit(1);
        }
}
/*
Method Name     :print
Parameters      :struct machineState mS
Return Value(s) :none
Partners        :None
Description     :outputs a string starting at the given address, will continue
outputting consecutive words as strings until NULL is reached
*/

void print(machineState mS){
        int flag, fChar, sChar;
        flag = 1;
        if(mS.operand > 0 || mS.operand < 100){
            while(flag){
                fChar = mS.memory[mS.operand] / 100;
                sChar = mS.memory[mS.operand] % 100;
                if(fChar != 0){
                    if(fChar == 10 || (fChar >= 65 && fChar <= 90)){
                        
                        printf("%c", fChar);
                        if(sChar != 0){
                            if(sChar == 10 || (sChar >= 65 && sChar <= 90)){
                                printf("%c", sChar);
                            }
                            else{
                                printf("Unknown Character – When printing a string, and unknown character was reached (only understands NULL, newline, and A-Z) at address: %d \n", mS.instructionCounter);
                                printM(mS);
                                exit(1);
                            
                            }
                        }
                        else{
                            flag = 0;
                        
                        }
                    }
                    else
                    {
                        printf("Unknown Character – When printing a string, and unknown character was reached (only understands NULL, newline, and A-Z) at address: %d \n", mS.instructionCounter);
                        printM(mS);
                        exit(1);
                    }
                }
                else{
                    flag = 0;
                }
            mS.operand++;
            }
            
        }
        else{
            printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
            printM(mS);
            exit(1);
        }
    




}
/*
Method Name     :load
Parameters      :Struct machineState mS
Return Value(s) :int mS.memory[mS.operand]
Partners        :None
Description     :Load a word fromt he given memory address into the
  accumulator
*/

int load(machineState mS){

    
         
        if(mS.operand > 0 || mS.operand < 100){
            if(mS.memory[mS.operand] <= 9999 && mS.memory[mS.operand] >= -9999){  
                return mS.memory[mS.operand];
                
            }
            else{
            printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
                printM(mS);
                exit(1);
            }
            
        }
        else{
            printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
            printM(mS);
            exit(1);
        }
}
/*
Method Name     :store 
Parameters      :struct machineState mS 
Return Value(s) :none
Partners        :None
  Description     :Store the word in the accumulator at the given address
*/

void store(machineState mS){
    
    
    if(mS.operand > 0 || mS.operand < 100){
        if(mS.accumulator <= 9999 && mS.accumulator >= -9999 ){
            mS.memory[mS.operand] = mS.accumulator;
        }
        else{
            printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
            printM(mS);
            exit(1);
        }
            
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
    }

    
}
/*
Method Name     :add
Parameters      :struct machineState mS
Return Value(s) :int sum 
Partners        :None
  Description     :Adds the word at the given memory address to the accumulator
*/

int add(machineState mS){
   int sum; 
    if(mS.operand > 0 || mS.operand < 100){
        sum = mS.accumulator + mS.memory[mS.operand];
        if(sum <= 9999 && sum >= -9999 ){
            return sum;
        }
        else{
            printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
            printM(mS);
            exit(1);
        }
            
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);


    }
}
/*
Method Name     :subtract
Parameters      :struct machineState mS
Return Value(s) :int difference
Partners        :None
Description     :subtracts the word at the given memory address to the 
  accumulator
*/

int subtract(machineState mS){
    int difference;
    if(mS.operand > 0 || mS.operand < 100){
        difference = mS.accumulator - mS.memory[mS.operand];
        if(difference <= 9999 && difference >= -9999 ){
            return difference;
        }
        else{
            printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
            printM(mS);
            exit(1);
        }
            
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
        
    }
}
/*
Method Name     :divide
Parameters      :struct machineState mS
Return Value(s) :int quotient
Partners        :None
  Description     :divides the word at the given memory address to the
  accumulator
*/

int divide(machineState mS){
    int quotient;
    if(mS.operand > 0 || mS.operand < 100){
        if(mS.memory[mS.operand] != 0){
            quotient = mS.accumulator / mS.memory[mS.operand];
            if(quotient <= 9999 && quotient >= -9999 ){
                return quotient;
            }
            else{
                printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
                printM(mS);
                exit(1);
            }
        }
        else{
            printf("Divide 0 - Division by 0 was attempted at address: %d \n", mS.instructionCounter);
            printM(mS);
            exit(1);
        }
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
    } 



}
/*
Method Name     :multiply
Parameters      :struct machineState mS
Return Value(s) :int product
Partners        :None
Description     :Multiplies the word at the given memory address to the accumulator
*/

int multiply(machineState mS){
    int product;
    if(mS.operand > 0 || mS.operand < 100){
        product = mS.accumulator * mS.memory[mS.operand];
        if(product <= 9999 && product >= -9999 ){
            return product;
        }
        else{
            printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
            printM(mS);
            exit(1);
        }
            
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
    } 


}

/*
Method Name     :modulus
Parameters      :struct machineState mS
Return Value(s) :int remainder
Partners        :None
Description     :Mods the word at the given memory address to the accumulator
*/

int modulus(machineState mS){
    int remainder;
    if(mS.operand > 0 || mS.operand < 100){
        remainder = mS.accumulator % mS.memory[mS.operand];
        if(remainder <= 9999 && remainder >= -9999 ){
            return remainder;
        }
        else{
            printf("Word overflow - attempts to place a word in memory or alter the accumulator so that is larger than 4 digits at address: %d\n", mS.instructionCounter);
            printM(mS);
            exit(1);
        }
            
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
    } 
    

}
/*
Method Name     :bran
Parameters      :struct machineState mS
Return Value(s) :int mS.operand
Partners        :None
Description     :Execution jumps to the given memory location
*/

int bran(machineState mS){
    if(mS.operand > 0 || mS.operand < 100){
            return mS.operand - 1;
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
    } 
    

}
/*
Method Name     :brng
Parameters      :machineState mS Struct
Return Value(s) :mS.operand int
Partners        :None
Description     :Execution jumps to the given memory location if the accumulator is negative
*/

int brng(machineState mS){
    if(mS.operand > 0 || mS.operand < 100){
       if(mS.accumulator < 0)
           return mS.operand - 1;
       return mS.instructionCounter;
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
    } 


}
/*
Method Name     :brzr
Parameters      :machineState mS Struct
Return Value(s) :int mS.operand-1
Partners        :None
Description     :Execution jumps to the given memory location if the accumulator is zero
*/

int brzr(machineState mS){
    if(mS.operand > 0 || mS.operand < 100){
       if(mS.accumulator == 0)
           return mS.operand - 1;
       return mS.instructionCounter;
    }
    else{
        printf("Segmentation fault - attempts to access an unknown address: %d\n", mS.operand);
        printM(mS);
        exit(1);
    } 



}
/*
Method Name     :printM
Parameters      :machineState MS struct
Return Value(s) :NONE
Partners        :None
Description     :This what where it prints to the console the tablet form.
*/

void printM(machineState mS){
    
    int i, j, mem;
    printf("\nREGISTERS: \n");
    if(mS.accumulator >= 0)
        printf("accumulator              +%04d\n", mS.accumulator);
    else
        printf("accumulator              %05d\n", mS.accumulator);

        printf("instructionCounter          %02d\n", mS.instructionCounter);
    if(mS.instructionRegister >= 0)
        printf("instructionRegister      +%04d\n", mS.instructionRegister);
    else
        printf("instructionRegister      %05d\n", mS.instructionRegister);

        printf("operationCode               %02d\n", mS.operationCode);
        printf("operand                     %02d\n", mS.operand);
        printf("MEMORY: \n");

    printf("       0     1     2     3     4     5     6     7     8     9\n");

    
    for(i = 0; i < 10; i++){
        printf("%2d", 10 * i);
        for(j = 0; j < 10; j++){
            mem = mS.memory[(i*10)+j];
            if(mem >= 0){
                printf(" +%04d",mem);
            }
            else
                printf(" %05d",mem);
        }
        printf("\n");
    
    }
        

}



