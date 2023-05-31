#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_LENGTH 10
#define CHANCES 5

void printMenu(){
    printf("=======================================\n");
    printf("          H  A  N  G  M  A  N          \n");
    printf("=======================================\n");
}


void printProgress(char w[], int p[]){
    unsigned int i;
    for(i = 0; i < strlen(w); i++){
        if(p[i]){
            printf("%c", w[i]);
        }else{
            printf("_");
        }
    }
    printf("\n\n");
    
}


int checkWin(char w[], int p[]){
    for(unsigned int i = 0; i < strlen(w); i++){
        if(p[i] == 0){
            return 0;
        }
    }
    return 1;
}


int checkAlreadyGuessed(char g[]){
    static char guessedLetters[26];
    for(unsigned int i = 0; i < 26; i++){
        if(strncmp(g, &guessedLetters[i],1) == 0){
            return 0;
        }
    }
    strcat(guessedLetters, g);
    return 1;
}


int main(){
    printMenu();
    char word[MAX_LENGTH];
    int progress[MAX_LENGTH] = {0};
    char guess[2];
    int guessedCorrect = 0;
    int chancesLeft =  CHANCES;

    printf("Executioner, Please Choose a Word: ");
    scanf("%s", word);
    
    while(1){
        printProgress(word, progress);                      // Print Progress
        printf("Chances Left: %d\n", chancesLeft);          // Print Chances Left
        sleep(1);                                           // One Second Delay
        printf("Guesser, Please Guess a Letter: ");         
        scanf("%s", guess);                                 // Get Guess
        if(!checkAlreadyGuessed(guess)){                    // Check for Redundant Guess
            printf("You Guessed This Letter Already!\n");
            continue;
        }
        for(unsigned int i = 0; i < strlen(word); i++){     // Check for Letter in Word
            if(strncmp(guess, &word[i], 1) == 0){
                guessedCorrect = guessedCorrect + 1;        // Correct Guess
                progress[i] = 1;                            // Update Progress
            }else{
                progress[i] = progress[i];
            }
        }
        if(guessedCorrect == 0){                            // Update Chances
            printf("MISS!\n");
            chancesLeft = chancesLeft - 1;
            if(chancesLeft == 0){
                printf("GAME OVER!\n");
                break;
            }
        }else{
            printf("HIT!\n");
        }
        guessedCorrect = 0;

        if(checkWin(word, progress) == 1){                  // Check For Win
            printProgress(word, progress);
            printf("You Win!\n");
            break;
        }

    }
}

