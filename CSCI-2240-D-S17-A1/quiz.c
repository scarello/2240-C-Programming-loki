/*
Name     : Michael Monical
Class    : 2240-850
Program #    : 1 Math Quiz
Due Date     : Sept. 15, 2016 

Honor Pledge:  On my honor as a student of the University
                of Nebraska at Omaha, I have neither given nor received
                unauthorized help on this homework assignment.

NAME: Michael Monical
NUID: 9263
EMAIL: mikemonical@gmail.com
   
Partners:None
    
This is a simple math quiz with varying degrees of difficulty. I did include Modulus division.
*/

#include <stdio.h>
#include <stdlib.h>

int genQuestion(int diff, int count);
int answerQuestion(int ans);
void response();



int main(){
    int good;
    int ans;
    int score = 0;
    int quest = 0;
    int difficulty = 0;
    int count;
    
    while( quest < 1 || quest > 20 ){
        printf("How many questions for this test (1-20)? ");
        scanf("%d", &quest);

    }
    
    while( difficulty < 1 || difficulty > 4){
        printf("Select difficulty (1-4) ");
        scanf("%d", &difficulty);
    }
    
    for(count = 1; count <= quest;count++)
    {
        ans = genQuestion(difficulty, count);
        good = answerQuestion(ans);
        if(good == 1){
            score++;
        }
        response(good);
    }
    
    printf("Your score was %d/%d\n", score, quest);

    return 0;
}
    /*  
        Method Name    :genQuestion
        Parameters     :diff and count both ints
        Return value(s):int based on the answer of the question
        Description    :This method takes both the difficulty of the question and asks the user based on that
                        it also tracks the number of questions that have been asked.
    */

int genQuestion(int diff, int count){
    
    int num1, num2, op;

    if(diff == 1){
        num1 = rand()%(10)+1;
        num2 = rand()%(10)+1;
    }
    else if(diff == 2){
        num1 = rand()%(50)+1;
        num2 = rand()%(50)+1;
    }
    else if(diff == 3){
        num1 = rand()%(100)+1;
        num2 = rand()%(100)+1;
    }
    else{
        num1 = rand()%(200)-100;
        num2 = rand()%(200)-100;
    }
    
    op = rand()%(5-1+1)+1;
    
    if(op == 1){
        printf("Question %d: %d + %d \n", count, num1, num2);
        return num1 + num2;
    }
    else if(op == 2){
        printf("Question %d: %d - %d \n", count, num1, num2);
        return num1 - num2;
    }
    else if(op == 3){
        printf("Question %d: %d * %d \n", count, num1, num2);
        return num1 * num2;
    }
    else if(op == 4){
        printf("Question %d: %d / %d \n", count, num1, num2);
        return num1 / num2;
    }
    else{
        printf("Question %d: %d %% %d \n", count, num1, num2);
        return num1 % num2;
    }

}
    /*  
        Method Name    :answerQuestion
        Parameters     :ans - int
        Return value(s):int 1 or a 0 is the answer correct or not?
        Description    :This method takes in and checks the users math answer.
    */
int answerQuestion(int ans){

    int userAns = 1001;
    /*printf("%d\n", ans);*/
    printf("Enter Answer: ");
    scanf("%d", &userAns);
    if(userAns != ans)
        return 0;
    else
        return 1;
}

    /*  
        Method Name    :response
        Parameters     :indicator int
        Return value(s):none
        Description    :This method reads in the users answer and determines if the answer 
                        is correct if it is not correct it will randomly pick how to say 
                        the user was wrong, likewise for correct answers.
    */

void response(int indicator){
    
    int res1 = rand()%(3-1+1)+1;
    printf("%d\n", res1);
    if (indicator == 1){
        if(res1 == 1){
            printf("Very Good!\n");
        }
        else if(res1 == 2){
            printf("Excellent!\n");
        }
        else if(res1 == 3){
            printf("Great Work!\n");
        }
    }
    else{
        if(res1 == 1){
            printf("Nice Try\n");
        }
        else if(res1 == 2){
            printf("Wrong\n");
        }
        else if(res1 == 3){
            printf("That is not correct\n");
        }
    }
            


}
