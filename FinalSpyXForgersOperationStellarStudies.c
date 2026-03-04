/* This is to certify that this project is my own work, based on my personal 
efforts in studying and applying the concepts learned.  I have 
constructed the functions and their respective algorithms and 
corresponding code by myself.  The program was run, tested, and debugged 
by my own efforts.  I further certify that I have not copied in part or 
whole or otherwise plagiarized the work of other students and/or persons. 
                                                                      
              Dwane A. Reyes, DLSU ID# 125068501

Description: The program is a 40-day simulation game where the player progresses through daily activities, builds skills, strengthens bonds with characters, and takes photos at different venues.
Non-outing days let the player study, train, or relax, while outing days focus on photography and special interactions.
On the other hand, outing days let you visit different venues, take photos, interact with characters, and potentially improve your bonds or achieve higher photo ratings.
Throughout the game, various stats—such as Activity Points, skill levels, bond values, venue conditions, and photo quality—are updated and tracked to determine the player’s final outcome.
Overall, the code manages the flow of days, choices, and results to create a complete gameplay cycle from Day 0 to the final ending.
Programmed by: <Dwane A. Reyes> <S15>
Last Modified: <November 23, 2025>
Version: <5.0>
[Acknowledgements:

Website used to convert text to ASCII Art:
https://www.asciiart.eu/text-to-ascii-art#google_vignette

]

*/

#include <stdio.h> // standard input and output operations
#include <stdlib.h> // random numbers, absolute value, etc.
#include <time.h> // time-related functions for random number generation
#include <windows.h> // windows-specific (console or timing like sleep and system)

#define ROLLS 5 // used for number of attempts in memorable photo minigame

// FUNCTION PROTOTYPES

void clear(); // Clears the screen
void pause(); // Pauses the screen
void gameHeader(); // Prints the game's home screen header
void pressStart(); // Prints the game's home screen options
int homeScreen(); // Accepts input from the player then returns the player's choice
void meetingDialogue(); // Prints the evening outing meeting dialogue 
int chooseVenue(int *chosenVenue); // Returns the player's chosen venue
void printVenue(int *chosenVenue); // Prints the venue options
int generateRandomValue(int min,int max); // Generates a random value given a minimum and a maximum number
void mathMinigame(int *AP, int *nMathQ, int *lvlMath, int *expMath); // Plays the Study Math with Loid Minigame
void physEdMinigame(int *AP, int *nPEQ, int *lvlPE, int *expPE); // Plays the Train Physical Education with Yor Minigame
void displayPhotoRating(int *photoRating); // Prints the venue's photo rating
void memorablePhotoMinigame(int *chosenVenue, int *photoRating, int *bestAngle,
    int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland,
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland); // Plays the Memorable Photo Minigame
int inputVenue(int *chosenVenue, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond); // Prompts the player to choose a venue
int returnTotalDays(int *nNonOutingDay, int *nOutingDay); // Returns the total number of days elapsed
void stats(int *AP, int *lvlMath, int *lvlPE, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond, int *nNonOutingDay, int *nOutingDay,
    int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland); // Prints the player's current game stats
void eveningOuting(int *chosenVenue, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond, int* nNonOutingDay, int *nOutingDay); // Runs the evening phase of the outing day
void morningOuting(int *AP, int *lvlMath, int *lvlPE, int *photoRating, int *chosenVenue, int *bestAngle, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond,
    int *nNonOutingDay, int *nOutingDay, int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland, 
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland); // Runs the morning phase of the outing day
void outingDay(int *AP, int *lvlMath, int *lvlPE, int* photoRating, int *chosenVenue, int *bestAngle, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond,
    int *nNonOutingDay, int *nOutingDay, int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland,
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland); // Runs the entire outing day
void nonOutingDays(int *chosenVenue, int *AP, int *nPEQ, int *lvlPE, int *expPE, int *nMathQ, int *lvlMath, int *expMath,
    int *bondBond, int *bondBecky, int *bondHenderson, int *bondDamian, int *nNonOutingDay, int *nOutingDay,
    int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland); // Runs the 3-day cycle of non-outing days
int perfectCounter(int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium,
    int *photoMuseum, int *photoLand, int *photoDogland); // Calculates the total of perfect photo ratings
void playEnding(int *lvlMath, int *lvlPE, int *photoPark, int *photoMall, int *photoBeach,
    int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland); // Plays an ending depending on which conditions the player accomplishes
void mainGame(int* AP, int* photoRating, int *chosenVenue, int* bestAngle, int *nPEQ, int *lvlPE, int *expPE, int *nMathQ, int *lvlMath, int *expMath, int *bondBond,
    int *bondBecky, int *bondHenderson, int *bondDamian, int *nNonOutingDay, int *nOutingDay,
    int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland,
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland); // Plays the main game sequence
void dayZero(int *AP,int* photoRating,int *chosenVenue,int *bestAngle,int *nPEQ,int *lvlPE,int*expPE,int *nMathQ,int *lvlMath,int *expMath,int *bondBecky,int *bondHenderson,
    int *bondDamian,int *bondBond,int *nNonOutingDay,int *nOutingDay,
    int *photoPark,int *photoMall,int *photoBeach,int *photoAquarium,int *photoMuseum,int *photoLand,int *photoDogland,
    int *randPark,int *randMall,int *randBeach,int *randAquarium,int *randMuseum,int *randLand,int *randDogland,
    int *bestPark,int *bestMall,int *bestBeach,int *bestAquarium,int *bestMuseum,int *bestLand,int *bestDogland); // Plays the very first day after starting the game
void instructions(); // Home screen function that Prints the game instructions
void exitGame(); // Home screen function that exits the game

/*
    Clears the console screen.
    Precondition:
    @param N/A
    @return void
*/

void clear(){
    system("cls"); // system calls "cls"
}

/*
    Pauses the consoles until a key is pressed.
    Precondition: N/A
    @param N/A
    @return void
*/

void pause(){
    system("pause"); // system calls "pause"
}

// HOME SCREEN FUNCTIONS

/*
    Prints the game header "SPYxFORGERS Operation: Stellar Studies" in ASCII Art
    Precondition: N/A
    @param N/A
    @return void
*/

void gameHeader(){
    clear();
    printf("*****************************************************************************************************************************\n");
    printf("                           _____ _______     __    ______ ____  _____   _____ ______ _____   _____\n");                         
    printf("                          / ____|  __ \\ \\   / /   |  ____/ __ \\|  __ \\ / ____|  ____|  __ \\ / ____|\n");                   
    printf("                         | (___ | |__) \\ \\_/ /_  _| |__ | |  | | |__) | |  __| |__  | |__) | (___\n");
    printf("                          \\___ \\|  ___/ \\   /\\ \\/ /  __|| |  | |  _  /| | |_ |  __| |  _  / \\___ \\\n");                 
    printf("                          ____) | |      | |  >  <| |   | |__| | | \\ \\| |__| | |____| | \\ \\ ____) |\n");
    printf("                         |_____/|_|      |_| /_/\\_\\_|    \\____/|_|  \\_\\\\_____|______|_|  \\_\\_____/\n");
    printf("     ____                       _   _                   _____ _       _ _               _____ _             _ _           \n");       
    printf("    / __ \\                     | | (_)            _    / ____| |     | | |             / ____| |           | (_)          \n");
    printf("   | |  | |_ __   ___ _ __ __ _| |_ _  ___  _ __ (_)  | (___ | |_ ___| | | __ _ _ __  | (___ | |_ _   _  __| |_  ___  ___ \n");
    printf("   | |  | | '_ \\ / _ \\ '__/ _` | __| |/ _ \\| '_ \\      \\___ \\| __/ _ \\ | |/ _` | '__|  \\___ \\| __| | | |/ _` | |/ _ \\/ __|\n");
    printf("   | |__| | |_) |  __/ | | (_| | |_| | (_) | | | |_    ____) | ||  __/ | | (_| | |     ____) | |_| |_| | (_| | |  __/\\__ \\\n");
    printf("    \\____/| .__/ \\___|_|  \\__,_|\\__|_|\\___/|_| |_(_)  |_____/ \\__\\___|_|_|\\__,_|_|    |_____/ \\__|\\__,_|\\__,_|_|\\___||___/\n");
    printf("          | |                                                                                                            \n");
    printf("          |_|                                                                                                            \n");
    printf("*****************************************************************************************************************************\n");
    
    return;
}

/*
    Prints the available start options
    Precondition: N/A
    @param N/A
    @return void
*/

void pressStart(){
    printf("                                                   [1] Start Game                                                      \n");
    printf("                                                   [2] Instructions                                                    \n");
    printf("                                                   [3] Exit                                                            \n");
    printf("=============================================================================================================================\n");
}

/*
    Prints the entire home screen, including the header and the game options. Asks the player for their input.
    Precondition: N/A
    @param N/A
    @return The choice the player inputs (1-3)
*/

int homeScreen(){
    int startChoice;
    int choiceStatus;
    gameHeader();
    pressStart();
    do 
    {
        printf("                                                   Enter your choice: ");
        choiceStatus=scanf("%d", &startChoice); // Assigns input to choiceStatus

        if(choiceStatus!=1){
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
        }

        gameHeader(); // display header
        pressStart(); // display game options

        if (startChoice < 1 || startChoice > 3){
            gameHeader();
            pressStart();
            printf("                                        Error. Input must be a number between 1-3.\n");
        }
            
    } while (startChoice < 1 || startChoice > 3);
    
    gameHeader();
    pressStart();
    return startChoice;
}

/*
    Prints the family meeting dialogue during the evening phase.
    Precondition: The player must be in the meeting phase.
    @param N/A
    @return void
*/

void meetingDialogue(){
    printf("Evening\n");
    printf("Venue: 128 Park Avenue, West Berlint\n");
    printf("\nFAMILY MEETING!\n");
    printf("Loid: So, where should our next outing be?\n");
    printf("Yor: Anya-san should decide, Loid.\n");
    printf("Anya: Anya wants to go...\n\n");
}

/*
    Returns the player's current chosen venue.
    Precondition: chosenVenue points to a valid integer (1-7).
    @param chosenVenue Pointer to the selected venue.
    @return The integer value of the chosen venue.
*/

int chooseVenue(int *chosenVenue){
    return *chosenVenue; // returns the selected venue for the current cycle
}

/*
    Prints the player's current chosen venue.
    Precondition: chosenVenue points to a valid integer (1-7).
    @param chosenVenue Pointer to the selected venue.
    @return void
*/

void printVenue(int *chosenVenue){
    *chosenVenue=chooseVenue(chosenVenue); // Returns chosenVenue and assigns value to pointer
    switch(*chosenVenue){ // display the current venue
    case 1:
    printf("Park");
    break;
    case 2:
    printf("City Mall");
    break;
    case 3:
    printf("Ostania Beach");
    break;
    case 4:
    printf("West Berlint Aquarium");
    break;
    case 5:
    printf("Ostania Art Museum");
    break;
    case 6:
    printf("Berlint Mouseney Land");
    break;
    case 7:
    printf("Park Avenue Dogland");
    break;
    }
    
}

// MINIGAMES

/*
    Generates a random value within a specified range.
    Precondition: min must be less than or equal to max.
    @param min The minimum number of a range.
    @param max The maximum number of a range.
    @return The random number generated between min and max.
*/

int generateRandomValue(int min,int max){
    int randNo; 
    randNo = (rand()%(max-min+1)+min); // Generates a random number
    return randNo;
}

/*
    Plays the Math Minigame where the player answers randomly generated math equations.
    Precondition: Player must select the Math Minigame option and have at least 1 AP.
    @param AP Pointer to the current Activity Points.
    @param nMathQ Pointer to store the number of questions for this session.
    @param lvlMath Pointer to the current Math level of the player.
    @param expMath Pointer to the current Math experience points of the player.
    @return void
*/

void mathMinigame(int* AP, int *nMathQ, int *lvlMath, int *expMath){

    // solve math
    int mathOp,n1,n2,nAnswer,nInput,i;
    int nCorrect = 0;
    int gainedExp = 0;
    int maxExp = 0;
    int chance;
    int choiceStatus;

    // number of questions depend on current lvl
    if(*lvlMath == 1)
    (*nMathQ)=5;
    else if(*lvlMath == 2)
    (*nMathQ)=10;
    else if(*lvlMath == 3)
    (*nMathQ)=10;

    for(i=0;i<*nMathQ;i++){
        clear();
        printf("Minigame: Studying with Loid!\n");
        printf("Current Math Level: Level %d\n\n",*lvlMath);

        // random operator assignment
        if(*lvlMath==1)
        mathOp=generateRandomValue(1,2); // Level 1
        else if(*lvlMath>=2)
        mathOp=generateRandomValue(1,3); // Level 2 and above

        // Level 1
        if(mathOp==1 && *lvlMath==1){
            n1=generateRandomValue(1,999);
            n2=generateRandomValue(1,999);
            nAnswer=n1+n2;
        }
        // Level 2 and above
        else if(mathOp==1 && *lvlMath>=2){
            n1=generateRandomValue(1,9999);
            n2=generateRandomValue(1,9999);
            nAnswer=n1+n2;
        }
        // Level 1
        else if(mathOp==2 && *lvlMath==1){
            n1=generateRandomValue(1,999);
            n2=generateRandomValue(1,999);
            nAnswer=n1-n2;
        }
        // Level 2 and above
        else if(mathOp==2 && *lvlMath>=2){
            n1=generateRandomValue(1,9999);
            n2=generateRandomValue(1,9999);
            nAnswer=n1-n2;
        }
        // Level 2 and above
        else if(mathOp==3 && *lvlMath==2){
            n1=generateRandomValue(1,20);
            n2=generateRandomValue(1,20);
            nAnswer=n1*n2;
        }
        // Level 3 and above
        else if(mathOp==3 && *lvlMath>=3){
            n1=generateRandomValue(1,50);
            n2=generateRandomValue(1,50);
            nAnswer=n1*n2;
        }

        printf("Question #%d of %d\n",(i+1),*nMathQ);
        printf("Number of correct answers: %d\n",nCorrect);
        printf("\n");
        printf("Question: ");
        printf("%d ",n1);

        // printing the generated random operator
        switch (mathOp) 
        {
            case 1:
                printf("+ ");
                break;
            case 2:
                printf("- ");
                break;
            case 3:
                printf("* ");
                break;
        }
        printf("%d = ?\n",n2);
        printf("\n");

        do{
        printf("Your answer: ");
        choiceStatus=scanf("%d",&nInput);

        if(choiceStatus!=1){
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
        }
    }while(choiceStatus!=1);

        if(nInput==nAnswer){
            printf("Correct!\n");
            nCorrect++;
        }
        else{
            printf("Incorrect!\n");
        }
        printf("The correct answer is: %d\n\n",nAnswer);
        pause();
}

// Completed Screen

clear();
printf("Minigame: Studying with Loid!\n\n");

// Grading


if(nCorrect * 100 / *nMathQ <= 60){
    printf("Loid: Excellent work, Anya! You could do better next time.\n");
    printf("Anya: Anya head hurts... Anya will try better next time! Waku waku!!!!!\n\n");
    gainedExp=1;
    (*expMath)++;
}
else if(nCorrect * 100 / *nMathQ <= 80){
    printf("Loid: Excellent work, Anya! You could do better next time.\n");
    printf("Anya: Anya smart! Anya getting good! Waku waku!!!!!\n\n");
    gainedExp=2;
    (*expMath)+=2;
}
else if(nCorrect == *nMathQ){
    printf("Loid: Excellent work, Anya! You got a perfect score!.\n");
    printf("Anya: Anya smartest! Anya the best! Waku waku!!!!!\n\n");
    if(*lvlMath<=3){
    gainedExp=3;
    (*expMath)+=3;
    chance=generateRandomValue(1,100);
    if(chance<=50){
        (*AP)+=2;
        printf("\n1 AP was replenished and you have been awarded an additional 1 AP!\n\n");
    }
}
    else{
    chance=generateRandomValue(1,100);
    if(chance<=60){
    (*AP)+=3;
    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n");
    }
    }

}

// levels system and adding excess exp

if(*lvlMath == 1 && *expMath>=5){
    *expMath=(*expMath)%5;
    (*lvlMath)++;
}
else if(*lvlMath == 2 && *expMath>=10){
    *expMath=(*expMath)%10;
    (*lvlMath)++;
}
else if(*lvlMath == 3 && *expMath>=15){
    *expMath=(*expMath)%15;
    (*lvlMath)++;
}

if(*lvlMath == 1)
    maxExp=5;
    else if(*lvlMath == 2)
    maxExp=10;
    else if(*lvlMath == 3)
    maxExp=15;

printf("Game Complete!\n");
printf("Total Score: %d / %d\n",nCorrect,*nMathQ);
printf("EXP Gained: %d EXP\n\n",gainedExp);
if(*lvlMath>=1&&*lvlMath<=3)
printf("Current EXP: %d / %d EXP (To Level Up)\n",*expMath,maxExp);
else
printf("Current EXP: MAX\n");
if(*lvlMath>=0&&*lvlMath<=3)
printf("Current Math Level: %d\n",*lvlMath);
else
printf("Current Math Level: MAX\n");
printf("\n");
pause();


}

/*
    Plays the Physical Education (PE) Minigame where the player must match the action given using chars.
    Precondition: Player must select the PE Minigame option and have at least 1 AP.
    @param AP Pointer to the current Activity Points.
    @param nPEQ Pointer to store the number of questions for this session.
    @param lvlPE Pointer to the current PE level of the player.
    @param expPE Pointer to the current PE experience points of the player.
    @return void
*/

void physEdMinigame(int *AP, int *nPEQ, int *lvlPE, int *expPE){
    int nCorrect = 0;
    int i = 0;
    char nInput = '\0';
    int randomAction;
    int gainedExp = 0;
    int maxExp = 0;
    int choiceStatus;
    int chance;
    int mappedInput;

    // all levels have 10 prompts
    if(*lvlPE>=1)
    (*nPEQ)=10;

    for(i=0;i<*nPEQ;i++){
    clear();
    printf("Minigame: Train Physical Activity with Yor!\n\n");
    printf("Current PE Level: Level %d\n\n",*lvlPE);
    if(*lvlPE==1)
        randomAction = generateRandomValue(9,12); // W/w,A/a,S/s,D/d
        else if(*lvlPE==2)
        randomAction = generateRandomValue(5,12); // 2,4,6,8,W/w,A/a,S/s,D/d
        else if(*lvlPE==3)
        randomAction = generateRandomValue(1,16); // 1,2,3,4,5,6,7,8,9,10,11,12,W,A,S,D,w,a,s,d
    printf("Yor: Anya-san, ");
    
    switch(randomAction)
    {
        case 1:
        printf("Southwest!");
        break;
        case 2:
        printf("South!");
        break;
        case 3:
        printf("Southeast!");
        break;
        case 4:
        printf("West!");
        break;
        case 5:
        printf("Northeast!");
        break;
        case 6:
        printf("East!");
        break;
        case 7:
        printf("Northwest!");
        break;
        case 8:
        printf("North!");
        break;
        case 9:
        printf("Up!");
        break;
        case 10:
        printf("Down!");
        break;
        case 11:
        printf("Left!");
        break;
        case 12:
        printf("Right!");
        break;
        case 13:
        printf("UP AHEAD!");
        break;
        case 14:
        printf("BEHIND YOU!");
        break;
        case 15:
        printf("TO THE LEFT");
        break;
        case 16:
        printf("TO THE RIGHT!");
        break;
    }
    printf("\t\tPrompt #%d of %d\n",i+1,*nPEQ);
    printf("Anya: Anya goes...\n\n");

    int valid=0; // initialize valid

    while(!valid){
    printf("(Action): ");
    choiceStatus=scanf(" %c",&nInput);
    while(getchar() != '\n'); // clear buffer

    mappedInput=0;

    if(choiceStatus == 1){
        if(*lvlPE == 1 || *lvlPE == 2){
            switch(nInput){
                case '2': mappedInput = 2; break;
                case '4': mappedInput = 4; break;
                case '6': mappedInput = 6; break;
                case '8': mappedInput = 8; break;
                case 'W': case 'w': mappedInput = 9; break;
                case 'S': case 's': mappedInput = 10; break;
                case 'A': case 'a': mappedInput = 11; break;
                case 'D': case 'd': mappedInput = 12; break;
            }
        }
        else if(*lvlPE >= 3){
            switch(nInput){
                case '1': mappedInput = 1; break;
                case '2': mappedInput = 2; break;
                case '3': mappedInput = 3; break;
                case '4': mappedInput = 4; break;
                case '5': mappedInput = 5; break;
                case '6': mappedInput = 6; break;
                case '7': mappedInput = 7; break;
                case '8': mappedInput = 8; break;
                case 'w': mappedInput = 9; break;
                case 's': mappedInput = 10; break;
                case 'a': mappedInput = 11; break;
                case 'd': mappedInput = 12; break;
                case 'W': mappedInput = 13; break;
                case 'S': mappedInput = 14; break;
                case 'A': mappedInput = 15; break;
                case 'D': mappedInput = 16; break;
            }
        }
    }

    if(choiceStatus != 1 || mappedInput == 0)
    {
        printf("Invalid input! Only allowed keys are 1-8 or WASD.\n\n");
    }
    else
    {
        valid = 1; // stop loop and proceed to next
    }
}

    if(mappedInput==randomAction){
        printf("Good job, Anya!\n");
        nCorrect++;
    }
    else
    printf("That was incorrect, Anya. Let's try another one!\n");

    pause();
}

    // Completed Screen
    clear();
    printf("Minigame: Train Physical Activity with Yor!\n\n");

    // Grading
    
    if(nCorrect * 100 / *nPEQ <= 60){
    printf("Yor: Anya-san! That was good! You can try better next time!\n");
    printf("Anya: ...A-anya's body hurts. Anya don't want to study tonight...\n\n");
    gainedExp=1;
    (*expPE)++;
}
else if(nCorrect * 100 / *nPEQ <= 80){
    printf("Yor: Anya-san! That was great! You're getting better!\n");
    printf("Anya: ...A-anya's body hurts. Anya don't want to study tonight...\n\n");
    gainedExp=2;
    (*expPE)+=2;
}
else if(nCorrect == *nPEQ){
    printf("Yor: Anya-san! That was amazing! You are such a diligent individual!\n");
    printf("Anya: ...A-anya's body hurts. Anya don't want to study tonight...\n\n");
    if(*lvlPE<=3){
    gainedExp=3;
    (*expPE)+=3;
    chance=generateRandomValue(1,100);
    if(chance<=50){
        (*AP)+=2;
        printf("\n1 AP was replenished and you have been awarded an additional 1 AP!\n\n");
    }
}
    else{
    chance=generateRandomValue(1,100);
    if(chance<=60){
    (*AP)+=3;
    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n");
    }
    }
}

// lvls system and adding excess exp

if(*lvlPE == 1 && *expPE>=5){
    *expPE=(*expPE)%5;
    (*lvlPE)++;
}
else if(*lvlPE == 2 && *expPE>=10){
    *expPE=(*expPE)%10;
    (*lvlPE)++;
}
else if(*lvlPE == 3 && *expPE>=15){
    *expPE=(*expPE)%15;
    (*lvlPE)++;
}

    if(*lvlPE == 1)
    maxExp=5;
    else if(*lvlPE == 2)
    maxExp=10;
    else if(*lvlPE == 3)
    maxExp=15;

printf("Game Complete!\n");
printf("Total Score: %d / %d\n",nCorrect,*nPEQ);
printf("EXP Gained: %d EXP\n\n",gainedExp);
if(*lvlPE>=1&&*lvlPE<=3)
printf("Current EXP: %d / %d EXP (To Level Up)\n",*expPE,maxExp);
else
printf("Current EXP: MAX\n");
if(*lvlPE>=0&&*lvlPE<=3)
printf("Current PE Level: %d\n",*lvlPE);
else
printf("Current PE Level: MAX\n");
printf("\n");
pause();
}

/*
    Prints the current photo rating of the selected venue.
    Precondition: photoRating points to a valid value (0-4).
    @param photoRating Pointer to the current photo rating of the current venue.
    @return void
*/

void displayPhotoRating(int *photoRating){
    switch(*photoRating){ // displays photo rating
        case 0:
        printf("N/A\n");
        break;
        case 1:
        printf("NOT GOOD\n");
        break;
        case 2:
        printf("OKAY\n");
        break;
        case 3:
        printf("VERY GOOD\n");
        break;
        case 4:
        printf("PERFECT");
        break;
    }
}

/*
    Plays the Memorable Photo Minigame where the player will be given five (5) attempts to correctly guess the random generated camera angle of the current venue.
    Precondition: The player must select the Memorable Photo Minigame option and have at least 1 AP.
    @param chosenVenue Pointer to the current selected venue.
    @param photoRating Pointer to store/update the current photo rating of the venue.
    @param bestAngle Pointer to store/update the best camera angle guessed so far.
    @param photoPark Pointer to store/update photo rating for Park.
    @param photoMall Pointer to store/update photo rating for City Mall.
    @param photoBeach Pointer to store/update photo rating for Ostania Beach.
    @param photoAquarium Pointer to store/update photo rating for West Berlint Aquarium.
    @param photoMuseum Pointer to store/update photo rating for Ostania Art Museum.
    @param photoLand Pointer to store/update photo rating for Berlint Mouseney Land.
    @param photoDogland Pointer to store/update photo rating for Park Avenue Dogland.
    @param randPark Pointer to the random target angle for Park.
    @param randMall Pointer to the random target angle for City Mall.
    @param randBeach Pointer to the random target angle for Ostania Beach.
    @param randAquarium Pointer to the random target angle for West Berlint Aquarium.
    @param randMuseum Pointer to the random target angle for Ostania Art Museum.
    @param randLand Pointer to the random target angle for Berlint Mouseney Land.
    @param randDogland Pointer to the random target angle for Park Avenue Dogland.
    @param bestPark Pointer to store the best angle guessed for Park.
    @param bestMall Pointer to store the best angle guessed for City Mall.
    @param bestBeach Pointer to store the best angle guessed for Ostania Beach.
    @param bestAquarium Pointer to store the best angle guessed for West Berlint Aquarium.
    @param bestMuseum Pointer to store the best angle guessed for Ostania Art Museum.
    @param bestLand Pointer to store the best angle guessed for Berlint Mouseney Land.
    @param bestDogland Pointer to store the best angle guessed for Park Avenue Dogland.
    @return void
*/

void memorablePhotoMinigame(int *chosenVenue, int *photoRating, int *bestAngle,
    int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland,
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland){

    int randomValue;
    int bWon = 0; // tracks whether player has successfully guessed the value
    int nGuess;
    int diff; // stores the absolute different between nGuess and randomValue
    int bestDiff = 1001; // stores the smallest difference. 1001 initialization ensures that the first guess will update
    int nRolls = ROLLS;
    int choiceStatus;

    switch(*chosenVenue){
        case 1:
        randomValue=*randPark; // Assigns venue's random value to the function's current random value 
        *bestAngle=*bestPark; // Assigns venue's best angle to the function's current best value
        *photoRating=*photoPark; // Assigns venue's photo rating to the function's current photo rating
        break;
        case 2:
        randomValue=*randMall; // Assigns venue's random value to the function's current random value 
        *bestAngle=*bestMall; // Assigns venue's best angle to the function's current best value
        *photoRating=*photoMall; // Assigns venue's photo rating to the function's current photo rating
        break;
        case 3:
        randomValue=*randBeach; // Assigns venue's random value to the function's current random value 
        *bestAngle=*bestBeach; // Assigns venue's best angle to the function's current best value
        *photoRating=*photoBeach; // Assigns venue's photo rating to the function's current photo rating
        break;
        case 4:
        randomValue=*randAquarium; // Assigns venue's random value to the function's current random value 
        *bestAngle=*bestAquarium; // Assigns venue's best angle to the function's current best value
        *photoRating=*photoAquarium; // Assigns venue's photo rating to the function's current photo rating
        break;
        case 5:
        randomValue=*randMuseum; // Assigns venue's random value to the function's current random value 
        *bestAngle=*bestMuseum; // Assigns venue's best angle to the function's current best value
        *photoRating=*photoMuseum; // Assigns venue's photo rating to the function's current photo rating
        break;
        case 6:
        randomValue=*randLand; // Assigns venue's random value to the function's current random value 
        *bestAngle=*bestLand; // Assigns venue's best angle to the function's current best value
        *photoRating=*photoLand; // Assigns venue's photo rating to the function's current photo rating
        break;
        case 7:
        randomValue=*randDogland; // Assigns venue's random value to the function's current random value 
        *bestAngle=*bestDogland; // Assigns venue's best angle to the function's current best value
        *photoRating=*photoDogland; // Assigns venue's photo rating to the function's current photo rating
        break;
    }

    if(*bestAngle!=0) // if !=0, the current venue holds a best angle venue captured from previous games
    bestDiff=abs(*bestAngle-randomValue); // stores the best guess so far
    else // no previous games in this venue
    bestDiff=1001; // guarantees the first valid guess will be the new best

    clear();
    printf("Minigame: Memorable Photo!\n\n");
    printf("Outing Venue: ");
    printVenue(chosenVenue);
    printf("\n\n");
    printf("Anya: Anya needs to take a photo! Ummmm...\n\n\n");
    printf("Current Photo Rating: ");
    displayPhotoRating(photoRating);
    if(*photoRating == 4)
    printf("\n");
    printf("Best Angle: %d\n\n",*bestAngle);

    while (!bWon && nRolls > 0){
        printf("\n");
        printf("Rolls left: %d\n",nRolls);
        printf("Enter Camera Angle (1-1000): ");
        choiceStatus=scanf("%d",&nGuess);

        if(choiceStatus!=1){
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // clear buffer
        }

        diff = abs(nGuess-randomValue);
        if(diff<bestDiff){ 
            bestDiff=diff; // updates closest guess if current is smaller
            *bestAngle=nGuess; // save THAT closest guess to the best angle pointer
        }

        if(bestDiff==0)
        *photoRating=4; // perfect
        else if(bestDiff<=10)
        *photoRating=3; // very good
        else if(bestDiff<=100)
        *photoRating=2; // okay
        else
        *photoRating=1; // not good

        if(nGuess>=1 && nGuess<=1000){
        if(nGuess==randomValue) // won
            bWon=1; // exits loop
        else if(nGuess<randomValue){
            printf("Higher!\n");
            nRolls--;
        }
        else if(nGuess>randomValue){
            printf("Lower!\n");
            nRolls--;
        }}
        else
        printf("Error. Please enter a number between 1 and 1000.\n\n");

    }
    if(bWon){
        clear();
        printf("Congratulations! The number was %d\n\n",randomValue);
    }
    else
    {
        printf("\nYou ran out of rolls! Better luck next time!\n\n");
    }

    switch(*chosenVenue){
        case 1:
        *bestPark=*bestAngle; // saves/assigns the current best angle to the best park pointer
        *photoPark=*photoRating; // saves/assigns the current photo rating to its respective venue
        break;
        case 2:
        *bestMall=*bestAngle;
        *photoMall=*photoRating;
        break;
        case 3:
        *bestBeach=*bestAngle;
        *photoBeach=*photoRating;
        break;
        case 4:
        *bestAquarium=*bestAngle;
        *photoAquarium=*photoRating;
        break;
        case 5:
        *bestMuseum=*bestAngle;
        *photoMuseum=*photoRating;
        break;
        case 6:
        *bestLand=*bestAngle;
        *photoLand=*photoRating;
        break;
        case 7:
        *bestDogland=*bestAngle;
        *photoDogland=*photoRating;
        break;
    }
        
    pause();
}

/*
    Prints the currently available venues which are determined by the confidants' bond levels.
    Precondition: Player must input a valid number for an unlocked venue.
    @param chosenVenue Selected venue for a cycle's outing day
    @param bondBecky Bond level of Becky
    @param bondHenderson Bond level of Henderson
    @param bondDamian Bond level of Damian
    @param bondBond Bond level of Bond
    @return void
*/

int inputVenue(int *chosenVenue, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond){
    int nChoice=0;
    int choiceStatus;

    while(!nChoice){
        printf("[1] Park\n");
        printf("[2] City Mall\n");
        printf("[3] Ostania Beach\n");

        // Prints the locked/unlocked status

    // Becky
    printf("[");
    if (*bondBecky >= 5)
        printf("4");
    else
        printf("X");
    printf("] West Berlint Aquarium");
    if (*bondBecky < 5)
        printf(" - LOCKED");
    printf("\n");

    // Henderson
    printf("[");
    if (*bondHenderson >= 5)
        printf("5");
    else
        printf("X");
    printf("] Ostania Art Museum");
    if (*bondHenderson < 5)
        printf(" - LOCKED");
    printf("\n");

    // Damian
    printf("[");
    if (*bondDamian >= 5)
        printf("6");
    else
        printf("X");
    printf("] Berlint Mouseney Land");
    if (*bondDamian < 5)
        printf(" - LOCKED");
    printf("\n");

    // Bond
    printf("[");
    if (*bondBond >= 5)
        printf("7");
    else
        printf("X");
    printf("] Park Avenue Dogland");
    if (*bondBond < 5)
        printf(" - LOCKED");
    printf("\n");

    do{
    printf("Your choice: ");
    choiceStatus = scanf("%d",chosenVenue);
    if(choiceStatus!=1){
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
        }
    }while(choiceStatus!=1);

    clear();

    // locked/unlocked depending on bond level
        if (*chosenVenue >= 1 && *chosenVenue <= 3) 
            nChoice = 1; // always allowed
        else if (*chosenVenue == 4 && *bondBecky >= 5) 
            nChoice = 1;
        else if (*chosenVenue == 5 && *bondHenderson >= 5)
            nChoice = 1;
        else if (*chosenVenue == 6 && *bondDamian >= 5)
            nChoice = 1;
        else if (*chosenVenue == 7 && *bondBond >= 5)
            nChoice = 1;
        else 
            printf("That venue is LOCKED or INVALID! Please choose again.\n\n");
    }
    switch(*chosenVenue){
        case 1:
        printf("Anya wants to go to the Park!\n");
        break;
        case 2:
        printf("Anya wants to go to the City Mall!\n");
        break;
        case 3:
        printf("Anya wants to go to the Ostania Beach!\n");
        break;
        case 4:
        printf("Anya wants to go to the West Berlint Aquarium!\n");
        break;
        case 5:
        printf("Anya wants to go to the Ostania Art Museum!\n");
        break;
        case 6:
        printf("Anya wants to go to the Berlint Mouseney Land!\n");
        break;
        case 7:
        printf("Anya wants to go to the Park Avenue Dogland!\n");
        break;
    }

    return *chosenVenue;
}

/*
    Calculates the total number of days that have passed by summing non-outing days and outing days.
    Precondition: Both pointers nNonOutingDay and nOutingDay must point to valid integers.
    @param nNonOutingDay Pointer to the number of non-outing days.
    @param nOutingDay Pointer to the number of outing days.
    @return The total number of days (non-outing + outing).
*/

int returnTotalDays(int *nNonOutingDay, int *nOutingDay){
    return (*nNonOutingDay)+(*nOutingDay); // get the sum of days
}


/*
    Prints the player's current overall game stats.
    Precondition: Players must input either 's' or 'S' when prompted to make a choice.
    @param AP Pointer to the current Activity Points.
    @param lvlMath Pointer to the current Math level.
    @param lvlPE Pointer to the current PE level.
    @param bondBecky Pointer to Becky Blackbell bond level.
    @param bondHenderson Pointer to Mr. Henderson bond level.
    @param bondDamian Pointer to Damian Desmond bond level.
    @param bondBond Pointer to Bond Forger bond level.
    @param nNonOutingDay Pointer to the number of non-outing days elapsed.
    @param nOutingDay Pointer to the number of outing days attended.
    @param photoPark Pointer to the photo rating of the Park.
    @param photoMall Pointer to the photo rating of the City Mall.
    @param photoBeach Pointer to the photo rating of Ostania Beach.
    @param photoAquarium Pointer to the photo rating of West Berlint Aquarium.
    @param photoMuseum Pointer to the photo rating of Ostania Art Museum.
    @param photoLand Pointer to the photo rating of Berlint Mouseney Land.
    @param photoDogland Pointer to the photo rating of Park Avenue Dogland.
    @return void
*/

void stats(int *AP, int *lvlMath, int *lvlPE, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond, int *nNonOutingDay, int *nOutingDay,
    int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland){
        
        clear();
        printf("Overall STATUS\n\n");
        printf("Days elapsed: %d\n",returnTotalDays(nNonOutingDay,nOutingDay));
        printf("Outings Attended: %d\n\n",*nOutingDay);
        printf("Anya's Math Level: %d\n",*lvlMath);
        printf("Anya's PE Level: %d\n\n",*lvlPE);
        printf("Activity Points Remaining: %d\n\n",*AP);

        // Prints bond levels
        if(*bondDamian>=0&&*bondDamian<=4)
        printf("Bond Level with Damian Desmond: %d\n",*bondDamian);
        else
        printf("Bond Level with Damian Desmond: MAX\n");

        if(*bondBecky>=0&&*bondBecky<=4)
        printf("Bond Level with Becky Blackbell: %d\n",*bondBecky);
        else
        printf("Bond Level with Becky Blackbell: MAX\n");

        if(*bondHenderson>=0&&*bondHenderson<=4)
        printf("Bond Level with Mr. Henderson: %d\n",*bondHenderson);
        else
        printf("Bond Level with Mr. Henderson: MAX\n");

        if(*bondBond>=0&&*bondBond<=4)
        printf("Bond Level with Bond Forger: %d\n\n",*bondBond);
        else
        printf("Bond Level with Bond Forger: MAX\n");

        // Prints photo ratings

        printf("Memorable Photo Levels:\n");
        
        printf("Park - ");
        displayPhotoRating(photoPark);
        if(*photoPark == 4)
        printf(" (Complete)\n");

        printf("City Mall - ");
        displayPhotoRating(photoMall);
        if(*photoMall == 4)
        printf(" (Complete)\n");

        printf("Ostania Beach - ");
        displayPhotoRating(photoBeach);
        if(*photoBeach == 4)
        printf(" (Complete)\n");

        printf("West Berlint Aquarium - ");
        displayPhotoRating(photoAquarium);
        if(*photoAquarium == 4)
        printf(" (Complete)\n");

        printf("Ostania Art Museum - ");
        displayPhotoRating(photoMuseum);
        if(*photoMuseum == 4)
        printf(" (Complete)\n");

        printf("Berlint Mouseney Land - ");
        displayPhotoRating(photoLand);
        if(*photoLand == 4)
        printf(" (Complete)\n");
        
        printf("Park Avenue Dogland - ");
        displayPhotoRating(photoDogland);
        if(*photoDogland == 4)
        printf(" (Complete)\n");

        printf("\n");
        pause();
    
}

/*
    Plays the outing's evening phase.
    Precondition: Player must finish the morning phase of Day #4.
    @param chosenVenue Pointer to store the player's chosen venue for the outing.
    @param bondBecky Pointer to Becky Blackbell's bond level.
    @param bondHenderson Pointer to Mr. Henderson's bond level.
    @param bondDamian Pointer to Damian Desmond's bond level.
    @param bondBond Pointer to Bond Forger's bond level.
    @param nNonOutingDay Pointer to the number of non-outing days completed.
    @param nOutingDay Pointer to the number of outing days completed.
    @return void
*/

void eveningOuting(int *chosenVenue, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond, int* nNonOutingDay, int *nOutingDay){
    // do while(10th day) // stop this dialogue when last cycle
    clear();
    printf("Day #%d\n",returnTotalDays(nNonOutingDay,nOutingDay));
    meetingDialogue(); 
    inputVenue(chosenVenue, bondBecky, bondHenderson, bondDamian, bondBond); // Asks player for venue input
    pause();
}

/*
    Plays the outing's morning phase where the player can select activities such as the Memorable Photo Minigame.
    Precondition: Player must finish the three (3) non-outing days.
    @param AP Pointer to the current Activity Points.
    @param lvlMath Pointer to the current Math level.
    @param lvlPE Pointer to the current PE level.
    @param photoRating Pointer to store the current photo rating for the chosen venue.
    @param chosenVenue Pointer to the currently selected outing venue.
    @param bestAngle Pointer to store the best camera angle for the current venue.
    @param bondBecky Pointer to the bond level with Becky Blackbell.
    @param bondHenderson Pointer to the bond level with Mr. Henderson.
    @param bondDamian Pointer to the bond level with Damian Desmond.
    @param bondBond Pointer to the bond level with Bond Forger.
    @param nNonOutingDay Pointer to the number of non-outing days completed.
    @param nOutingDay Pointer to the number of outing days completed.
    @param photoPark Pointer to the photo rating at the Park.
    @param photoMall Pointer to the photo rating at the City Mall.
    @param photoBeach Pointer to the photo rating at Ostania Beach.
    @param photoAquarium Pointer to the photo rating at West Berlint Aquarium.
    @param photoMuseum Pointer to the photo rating at Ostania Art Museum.
    @param photoLand Pointer to the photo rating at Berlint Mouseney Land.
    @param photoDogland Pointer to the photo rating at Park Avenue Dogland.
    @param randPark Pointer to the randomly generated best angle at the Park.
    @param randMall Pointer to the randomly generated best angle at the City Mall.
    @param randBeach Pointer to the randomly generated best angle at Ostania Beach.
    @param randAquarium Pointer to the randomly generated best angle at West Berlint Aquarium.
    @param randMuseum Pointer to the randomly generated best angle at Ostania Art Museum.
    @param randLand Pointer to the randomly generated best angle at Berlint Mouseney Land.
    @param randDogland Pointer to the randomly generated best angle at Park Avenue Dogland.
    @param bestPark Pointer to store the best angle for the Park.
    @param bestMall Pointer to store the best angle for the City Mall.
    @param bestBeach Pointer to store the best angle for Ostania Beach.
    @param bestAquarium Pointer to store the best angle for West Berlint Aquarium.
    @param bestMuseum Pointer to store the best angle for Ostania Art Museum.
    @param bestLand Pointer to store the best angle for Berlint Mouseney Land.
    @param bestDogland Pointer to store the best angle for Park Avenue Dogland.
    @return void
*/

void morningOuting(int *AP, int *lvlMath, int *lvlPE, int *photoRating, int *chosenVenue, int *bestAngle, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond,
    int *nNonOutingDay, int *nOutingDay, int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland, 
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland){

    char choice;
    int valid=0;
    int choiceStatus;

    clear();
    printf("Day #%d %-40s Day(s) Till next Outing: 0\n",returnTotalDays(nNonOutingDay,nOutingDay),"");
    printf("%-47s Next Outing Venue: ", "Morning");
    printVenue(chosenVenue);
    printf("\n\nLoid: Well Anya, I hope you have prepared for today.\n");
    printf("Anya: YEY! OOTING! OOTING! OOTING! ANYA IS GOING OOTING!\n");
    printf("Yor: A-anya san, don't forget your bag!\n");
    printf("Bond: *Borf*\n");
    printf("Anya: Anya will bring Mr. Penguin, and Anya wants peanuts.\n");
    printf("Loid: I don't think we'll need those…\n");
    printf("Anya: OOTING! OOTING! Mr. Penguin goes to OOTING! OOTING!\n");
    printf("Yor: I think Anya-san will be fine, Loid-san.\n");
    printf("Loid: Seems like it.\n");
    printf("Anya: OOTING! OOTING!\n\n");
    pause();

do{
    clear();
    printf("Day #%d %-40s Outing Day: ",returnTotalDays(nNonOutingDay,nOutingDay),"");
    printVenue(chosenVenue);
    printf("\nMorning %-39s AP Remaining: ","");
    printf("%d\n\n",*AP);
    printf("Venue: ");
    printVenue(chosenVenue);
    printf("\nBest Photo Rating: ");

    // Displays best photo rating depending on current chosen venue
    switch(*chosenVenue){
        case 1:
        displayPhotoRating(photoPark);
        break;
        case 2:
        displayPhotoRating(photoMall);
        break;
        case 3:
        displayPhotoRating(photoBeach);
        break;
        case 4:
        displayPhotoRating(photoAquarium);
        break;
        case 5:
        displayPhotoRating(photoMuseum);
        break;
        case 6:
        displayPhotoRating(photoLand);
        break;
        case 7:
        displayPhotoRating(photoDogland);
        break;
    }
    printf("\n");
    printf("Loid: Anya, what should we do?\n");
    printf("Anya: Waku-waku... %-28s [S]tats","");
    printf("\nLoid: *sigh* At least she's enjoying.\n");
    printf("\n");
    printf("[1] - Take a Memorable Photo for the Project\n");
    printf("[2] - Go Home\n");
    printf("\n");
    printf("Your Choice: ");
    choiceStatus = scanf(" %c", &choice); // clear buffer

    valid=0;

    if(choiceStatus!=1){
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
        }

    else if(choice == '1' && *AP < 1){
            printf("Insufficient AP for this activity!\n");
            pause();
            choice=0;
        }
    else{
        switch(choice){
            case 's':
            case 'S':
            stats(AP,lvlMath,lvlPE,bondBecky,bondHenderson,bondDamian,bondBond,nNonOutingDay,nOutingDay,
                photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland);
            break;
            case '1':
            printf("Taking a Memorable Photo for the Project!\n\n");
            (*AP)--;
            pause();
            memorablePhotoMinigame(chosenVenue,photoRating,bestAngle,photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland,
                    randPark,randMall,randBeach,randAquarium,randMuseum,randLand,randDogland,
                    bestPark,bestMall,bestBeach,bestAquarium,bestMuseum,bestLand,bestDogland);
            break;
            case '2':
            printf("Going home...\n\n");
            pause();
            valid=1; // Stops loop and proceeds to next phase
            break;
            default:
            printf("\nError. Please enter a valid input\n");
            pause();
            }}
}while(!valid);

    }

/*
    Plays the entire sequence of the outing day.
    Precondition: Player must finish the three (3) non-outing days.
    @param AP Pointer to the current Activity Points.
    @param lvlMath Pointer to the current Math level.
    @param lvlPE Pointer to the current PE level.
    @param photoRating Pointer to store the current photo rating for the chosen venue.
    @param chosenVenue Pointer to the currently selected outing venue.
    @param bestAngle Pointer to store the best camera angle for the current venue.
    @param bondBecky Pointer to the bond level with Becky Blackbell.
    @param bondHenderson Pointer to the bond level with Mr. Henderson.
    @param bondDamian Pointer to the bond level with Damian Desmond.
    @param bondBond Pointer to the bond level with Bond Forger.
    @param nNonOutingDay Pointer to the number of non-outing days completed.
    @param nOutingDay Pointer to the number of outing days completed.
    @param photoPark Pointer to the photo rating at the Park.
    @param photoMall Pointer to the photo rating at the City Mall.
    @param photoBeach Pointer to the photo rating at Ostania Beach.
    @param photoAquarium Pointer to the photo rating at West Berlint Aquarium.
    @param photoMuseum Pointer to the photo rating at Ostania Art Museum.
    @param photoLand Pointer to the photo rating at Berlint Mouseney Land.
    @param photoDogland Pointer to the photo rating at Park Avenue Dogland.
    @param randPark Pointer to the randomly generated best angle at the Park.
    @param randMall Pointer to the randomly generated best angle at the City Mall.
    @param randBeach Pointer to the randomly generated best angle at Ostania Beach.
    @param randAquarium Pointer to the randomly generated best angle at West Berlint Aquarium.
    @param randMuseum Pointer to the randomly generated best angle at Ostania Art Museum.
    @param randLand Pointer to the randomly generated best angle at Berlint Mouseney Land.
    @param randDogland Pointer to the randomly generated best angle at Park Avenue Dogland.
    @param bestPark Pointer to store the best angle for the Park.
    @param bestMall Pointer to store the best angle for the City Mall.
    @param bestBeach Pointer to store the best angle for Ostania Beach.
    @param bestAquarium Pointer to store the best angle for West Berlint Aquarium.
    @param bestMuseum Pointer to store the best angle for Ostania Art Museum.
    @param bestLand Pointer to store the best angle for Berlint Mouseney Land.
    @param bestDogland Pointer to store the best angle for Park Avenue Dogland.
    @return void
*/

void outingDay(int *AP, int *lvlMath, int *lvlPE, int* photoRating, int *chosenVenue, int *bestAngle, int *bondBecky, int *bondHenderson, int *bondDamian, int *bondBond,
    int *nNonOutingDay, int *nOutingDay, int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland,
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland){
        
        (*nOutingDay)++; // increase # of outing days
        
        morningOuting(AP,lvlMath,lvlPE,photoRating,chosenVenue,bestAngle,bondBecky,  bondHenderson,  bondDamian,  bondBond,
         nNonOutingDay, nOutingDay, photoPark,  photoMall,  photoBeach,  photoAquarium,  photoMuseum,  photoLand,  photoDogland,
         randPark,  randMall,  randBeach,  randAquarium,  randMuseum,  randLand,  randDogland,
         bestPark,  bestMall,  bestBeach,  bestAquarium,  bestMuseum,  bestLand,  bestDogland);

         if(*nOutingDay<=8) // only allows 8 outing days. the outing day of the last cycle should not run.
         eveningOuting(chosenVenue, bondBecky, bondHenderson, bondDamian, bondBond, nNonOutingDay, nOutingDay);
         
}

/*
    Plays the entire sequence of the three (3) non-outing days where the player can engage in activities such as bonding with confidants, playing minigames, or slacking off. 
    Each day is divided into morning and afternoon phases, with Activity Points (AP) spent on activities and replenished after each day.
    Precondition: Player must have selected a venue and start from Day #1 of the non-outing period.
    @param chosenVenue Pointer to the currently selected outing venue.
    @param AP Pointer to the current Activity Points.
    @param nPEQ Pointer to the number of Physical Education questions (for PE minigame).
    @param lvlPE Pointer to the current PE level.
    @param expPE Pointer to accumulated experience points in PE.
    @param nMathQ Pointer to the number of Math questions (for Math minigame).
    @param lvlMath Pointer to the current Math level.
    @param expMath Pointer to accumulated experience points in Math.
    @param bondBond Pointer to the bond level with Bond Forger.
    @param bondBecky Pointer to the bond level with Becky Blackbell.
    @param bondHenderson Pointer to the bond level with Mr. Henderson.
    @param bondDamian Pointer to the bond level with Damian Desmond.
    @param nNonOutingDay Pointer to the count of non-outing days completed.
    @param nOutingDay Pointer to the count of outing days completed.
    @param photoPark Pointer to the photo rating for Park.
    @param photoMall Pointer to the photo rating for City Mall.
    @param photoBeach Pointer to the photo rating for Ostania Beach.
    @param photoAquarium Pointer to the photo rating for West Berlint Aquarium.
    @param photoMuseum Pointer to the photo rating for Ostania Art Museum.
    @param photoLand Pointer to the photo rating for Berlint Mouseney Land.
    @param photoDogland Pointer to the photo rating for Park Avenue Dogland.
    @return void
*/

void nonOutingDays(int *chosenVenue, int *AP, int *nPEQ, int *lvlPE, int *expPE, int *nMathQ, int *lvlMath, int *expMath,
    int *bondBond, int *bondBecky, int *bondHenderson, int *bondDamian, int *nNonOutingDay, int *nOutingDay,
    int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland){

    int max=3;

    for(int i=0;i<3;i++){ // 3 non-outing days
        (*nNonOutingDay)++; // increase # of non-outing days

        int randBecky = generateRandomValue(1,100);
        int randHenderson = generateRandomValue(1,100);
        int randDamian = generateRandomValue(1,100);
        char choice;
        int valid = 0;
        int chance;
        
        while(!valid){
            clear();
            printf("Day #%d %-40s Day(s) Till next Outing: %d\n",returnTotalDays(nNonOutingDay,nOutingDay),"",max-i);
            printf("%-47s Next Outing Venue: ", "Morning");
            printVenue(chosenVenue);
            printf("\n\n");
            printf("%-47s AP Remaining: ", "Venue: Eden Academy");
            printf("%d\n\n",*AP);
            printf("[1] Bond with Damian\n");
            printf("[2] Bond with Becky\n");
            printf("[3] Bond with Mr. Henderson %-19s [S]tats\n","");
            printf("[4] Proceed Home\n");
            printf("Your choice: ");
            scanf(" %c", &choice);
            while(getchar() != '\n'); // Clear buffer
            printf("\n");

            if((choice < '1' || choice > '4') && choice != 's' && choice != 'S'){
                printf("Invalid input! Only 1-4 or S allowed.\n");
                pause();
            }
            else if((choice >= '1' && choice <= '3') && *AP < 1){
                printf("Insufficient AP for this activity!\n");
                pause();
            }
            else{
                switch(choice){
                case 's':
                case 'S':
                stats(AP,lvlMath,lvlPE,bondBecky,bondHenderson,bondDamian,bondBond,nNonOutingDay,nOutingDay,
                    photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland);
                break;

                case '1':
                if(*lvlPE==1)
                printf("Bond with Damian failed! PE level is too low!\n");

                else if(*lvlPE>=2 && *bondDamian<5){
                if((*lvlPE==2 && randDamian<26) || (*lvlPE==3 && randDamian<51) || (*lvlPE==4 && randDamian<76)){ // chances based on level
                    printf("Bonded with Damian! Increased Bond Point by 1!\n");
                    (*bondDamian)++;
                }
                else
                printf("Bond with Damian failed! Try again next time!\n");
            }

                else if(*bondDamian==5){
                    printf("Bonded with Damian! Maximum Bond Points reached! You have been awarded +3 AP!\n"); // one-time +3 AP
                    (*bondDamian)++;
                    (*AP)+=3;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n"); // returns 1 used AP and an additional 2 AP = +3 AP
                    (*AP)+=3;
                }
            }
                
                else{
                    printf("Bonded with Damian! Maximum Bond Points reached! (You did not gain additional bond points.)\n"); // max level. bond is internal and will not get displayed at any point of the program.
                                                                                                                             // therefore, I did not cap the bond points at 5
                    (*bondDamian)++;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n"); // returns 1 used AP and an additional 2 AP = +3 AP
                    (*AP)+=3;
                }
                    
            }
                (*AP)--;
                pause();
                valid = 1; // Stops loop and proceeds to next phase
                break;
                case '2':
                if(*bondBecky<5){
                    if(randBecky<76){ // chances based on level
                        printf("Bonded with Becky! Increased Bond Point by 1!\n"); 
                        (*bondBecky)++;
                    }
                    else
                    printf("Bond with Becky failed! Try again next time!\n");
                }

                else if(*bondBecky==5){
                    printf("Bonded with Becky! Maximum Bond Points reached! You have been awarded +3 AP!\n"); // one-time +3 AP
                    (*bondBecky)++;
                    (*AP)+=3;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                        printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n"); // returns 1 used AP and an additional 2 AP = +3 AP
                        (*AP)+=3;
                    }
                }
                
                else{
                    printf("Bonded with Becky! Maximum Bond Points reached! (You did not gain additional bond points.)\n"); // max level. bond is internal and will not get displayed at any point of the program.
                                                                                                                             // therefore, I did not cap the bond points at 5
                    (*bondBecky)++;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n"); // returns 1 used AP and an additional 2 AP = +3 AP
                    (*AP)+=3;
                }
                    
            }
                (*AP)--;
                pause();
                valid = 1; // Stops loop and proceeds to next phase
                break;
                case '3':
                if(*lvlMath==1)
                printf("Bond with Mr. Henderson failed! Math level is too low!\n");

                else if(*lvlMath>=2 && *bondHenderson<5){
                    if((*lvlMath==2 && randHenderson<51) || (*lvlMath==3 && randHenderson<76) || *lvlMath==4){ // chances based on level
                        printf("Bonded with Mr. Henderson! Increased Bond Point by 1!\n");
                        (*bondHenderson)++;
                    }
                    else
                    printf("Bond with Mr. Henderson failed! Try again next time!\n");
                }

                else if(*bondHenderson==5){
                    printf("Bonded with Mr. Henderson! Maximum Bond Points reached! You have been awarded +3 AP!\n"); // one-time +3 AP
                    (*bondHenderson)++;
                    (*AP)+=3;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n"); // returns 1 used AP and an additional 2 AP = +3 AP
                    (*AP)+=3;
                }
            }
                
                else{
                    printf("Bonded with Mr. Henderson! Maximum Bond Points reached! (You did not gain additional bond points.)\n"); // max level. bond is internal and will not get displayed at any point of the program.
                                                                                                                             // therefore, I did not cap the bond points at 5
                    (*bondHenderson)++;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n");
                    (*AP)+=3;
                }
            }
                (*AP)--;
                pause();
                valid = 1; // Stops loop and proceeds to next phase
                break;
                case '4':
                printf("Going home...\n");
                pause();
                valid = 1; // Stops loop and proceeds to next phase
                break;
            }
            }
        }

        valid = 0;
        while(!valid){
            clear();
            printf("Day #%d %-40s Day(s) Till next Outing: %d\n",returnTotalDays(nNonOutingDay,nOutingDay),"",max-i);
            printf("%-47s Next Outing Venue: ", "Afternoon");
            printVenue(chosenVenue);
            printf("\n\n");
            printf("%-47s AP Remaining: ", "Venue: 128 Park Avenue, West Berlint");
            printf("%d\n\n",*AP);
            printf("[1] Study Math with Loid\n");
            printf("[2] Train Physical Education with Yor\n");
            printf("[3] Bond with Bond Forger %-21s [S]tats\n","");
            printf("[4] Slack Off\n");
            printf("Your choice: ");
            scanf(" %c", &choice);
            while(getchar() != '\n'); // Clear buffer
            printf("\n");

            if((choice < '1' || choice > '4') && choice != 's' && choice != 'S'){
            printf("Invalid input! Only 1-4 or S allowed.\n");
            pause();
            }
            else if((choice >= '1' && choice <= '3') && *AP < 1){
            printf("Insufficient AP for this activity!\n");
            pause();
            }
            else{
                switch(choice){
                case 's':
                case 'S':
                stats(AP,lvlMath,lvlPE,bondBecky,bondHenderson,bondDamian,bondBond,nNonOutingDay,nOutingDay,
                        photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland);
                break;
                case '1':
                printf("Study Math with Loid!\n");
                (*AP)--;
                pause();
                mathMinigame(AP,nMathQ,lvlMath,expMath);
                valid = 1; // Stops loop and proceeds to next phase
                break;
                case '2':
                printf("Train Physical Education with Yor!\n");
                (*AP)--;
                pause();
                physEdMinigame(AP,nPEQ,lvlPE,expPE);
                valid = 1; // Stops loop and proceeds to next phase
                break;
                case '3':

                if(*bondBond<5){
                printf("Bonded with Bond Forger! Increased Bond Point by 1!\n");
                (*bondBond)++;}
                
                else if(*bondBond==5){
                    printf("Bonded with Bond Forger! Maximum Bond Points reached! You have been awarded +3 AP!\n"); // one-time +3 AP
                    (*bondBond)++;
                    (*AP)+=3;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n"); // returns 1 used AP and an additional 2 AP = +3 AP
                    (*AP)+=3;
                }
            }
                
                else{
                    printf("Bonded with Bond Forger! Maximum Bond Points reached! (You did not gain additional bond points.)\n"); // max level. bond is internal and will not get displayed at any point of the program.
                                                                                                                             // therefore, I did not cap the bond points at 5
                    (*bondBond)++;
                    chance=(generateRandomValue(1,100));
                    if(chance<51){
                    printf("\n1 AP was replenished and you have been awarded an additional 2 AP!\n\n"); // returns 1 used AP and an additional 2 AP = +3 AP
                    (*AP)+=3;
                }
            }
                (*AP)--;
                pause();
                valid = 1; // Stops loop and proceeds to next phase
                break;
                case '4':
                printf("Anya slacked off and then went to sleep...\n");
                pause();
                valid = 1; // Stops loop and proceeds to next phase
                break;
                }
            }
        }

        // Replenishes AP only on Day 1 and 2
        if(i == 0 || i == 1)
        (*AP)++;

    }
}

/*
    Returns the total number of perfect photo ratings to determine which ending the player will get.
    Precondition: ALL photo ratings are initialized and valid.
    @param photoPark Pointer to the Park photo rating.
    @param photoMall Pointer to the City Mall photo rating.
    @param photoBeach Pointer to the Ostania Beach photo rating.
    @param photoAquarium Pointer to the West Berlint Aquarium photo rating.
    @param photoMuseum Pointer to the Ostania Art Museum photo rating.
    @param photoLand Pointer to the Berlint Mouseney Land photo rating.
    @param photoDogland Pointer to the Park Avenue Dogland photo rating.
    @return The total number of perfect photo ratings.
*/

int perfectCounter(int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland){
    // checks whether venues have perfect ratings and calculates sum
    return (*photoPark > 3) + (*photoMall > 3) + (*photoBeach > 3) + (*photoAquarium > 3) + (*photoMuseum > 3) + (*photoLand > 3) + (*photoDogland > 3);
}

/*
    Prints the ending achieved by the player based on Math and PE levels 
    and the number of perfect photo ratings obtained in all venues.
    Precondition: The player must finish the 40-day cycle.
    @param lvlMath Pointer to the player's Math level.
    @param lvlPE Pointer to the player's Physical Education (PE) level.
    @param photoPark Pointer to the Park photo rating.
    @param photoMall Pointer to the City Mall photo rating.
    @param photoBeach Pointer to the Ostania Beach photo rating.
    @param photoAquarium Pointer to the West Berlint Aquarium photo rating.
    @param photoMuseum Pointer to the Ostania Art Museum photo rating.
    @param photoLand Pointer to the Berlint Mouseney Land photo rating.
    @param photoDogland Pointer to the Park Avenue Dogland photo rating.
    @return void
*/

void playEnding(int *lvlMath, int *lvlPE, int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland){

    int perfectCount = perfectCounter(photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland); // Assigns number of perfect photo ratings to perfectCount

    clear();

    if(*lvlMath > 3 && *lvlPE > 3 && perfectCount == 7){ // perfect ending
        printf("PERFECT ENDING\n\n");
        printf("Anya succeeds in submitting her project and ends up with near-top ranks in the exams.\n");
        printf("As a result, she is awarded the Stella Star, with Mr. Henderson praising her for her performance being “Very Elegant”.\n\n");
        printf("This ending is achievable by obtaining a PERFECT rating in ALL memorable photos for ALL venues.\n\n");
        printf("The END.\n\n");
}

    if(*lvlMath > 3 && *lvlPE > 3 && perfectCount >= 3){ // neutral ending
        printf("NEUTRAL ENDING\n\n");
        printf("Anya submits her project, but there are better projects that have been submitted.\n");
        printf("However, she passes her exams, but does not earn the Stella Star.\n\n");
        printf("This ending is achieved by obtaining a PERFECT memorable photo rating in at least 3 venues and maxing out her Math and PE levels\n\n");
        printf("The END.\n\n");
}
else{ // bad ending
        printf("BAD ENDING\n\n"); 
        printf("Anya submits her project, but it is incomplete. Likewise, she does not pass her\n");
        printf("exams and, to Loid's dismay, Anya gets a Tonitrus bolt for her performance.\n\n");
        printf("This ending is obtained if less than 3 PERFECT memorable photo ratings are obtained");
        printf("or her PE and MATH levels are not maxed out\n\n");
        printf("The END.\n\n");
}

    pause();

}

/*
    Plays the entire 40-day game cycle, alternating between non-outing days 
    and outing days. Ensures Activity Points (AP) are restored to a minimum of 3 
    after each outing day. At the end of the cycle, determines and displays 
    the ending achieved by the player based on Math/PE levels and perfect photo ratings.
    Precondition: Players must get past Day #0.
    @param AP Pointer to the player's current Activity Points.
    @param photoRating Pointer to the current photo rating.
    @param chosenVenue Pointer to the currently selected outing venue.
    @param bestAngle Pointer to the best photo angle for minigames.
    @param nPEQ Pointer to the number of PE minigame questions.
    @param lvlPE Pointer to the player's PE level.
    @param expPE Pointer to the player's PE experience points.
    @param nMathQ Pointer to the number of Math minigame questions.
    @param lvlMath Pointer to the player's Math level.
    @param expMath Pointer to the player's Math experience points.
    @param bondBond Pointer to the Bond Forger bond level.
    @param bondBecky Pointer to the Becky Blackbell bond level.
    @param bondHenderson Pointer to Mr. Henderson bond level.
    @param bondDamian Pointer to Damian Desmond bond level.
    @param nNonOutingDay Pointer to the number of non-outing days completed.
    @param nOutingDay Pointer to the number of outing days completed.
    @param photoPark Pointer to Park photo rating.
    @param photoMall Pointer to City Mall photo rating.
    @param photoBeach Pointer to Ostania Beach photo rating.
    @param photoAquarium Pointer to West Berlint Aquarium photo rating.
    @param photoMuseum Pointer to Ostania Art Museum photo rating.
    @param photoLand Pointer to Berlint Mouseney Land photo rating.
    @param photoDogland Pointer to Park Avenue Dogland photo rating.
    @param randPark Pointer to random value for Park photo minigame.
    @param randMall Pointer to random value for City Mall photo minigame.
    @param randBeach Pointer to random value for Ostania Beach photo minigame.
    @param randAquarium Pointer to random value for West Berlint Aquarium photo minigame.
    @param randMuseum Pointer to random value for Ostania Art Museum photo minigame.
    @param randLand Pointer to random value for Berlint Mouseney Land photo minigame.
    @param randDogland Pointer to random value for Park Avenue Dogland photo minigame.
    @param bestPark Pointer to the best angle for Park photo minigame.
    @param bestMall Pointer to the best angle for City Mall photo minigame.
    @param bestBeach Pointer to the best angle for Ostania Beach photo minigame.
    @param bestAquarium Pointer to the best angle for West Berlint Aquarium photo minigame.
    @param bestMuseum Pointer to the best angle for Ostania Art Museum photo minigame.
    @param bestLand Pointer to the best angle for Berlint Mouseney Land photo minigame.
    @param bestDogland Pointer to the best angle for Park Avenue Dogland photo minigame.
    @return void
*/

void mainGame(int* AP, int* photoRating, int *chosenVenue, int* bestAngle, int *nPEQ, int *lvlPE, int *expPE, int *nMathQ, int *lvlMath, int *expMath, int *bondBond,
    int *bondBecky, int *bondHenderson, int *bondDamian,
    int *nNonOutingDay, int *nOutingDay, int *photoPark, int *photoMall, int *photoBeach, int *photoAquarium, int *photoMuseum, int *photoLand, int *photoDogland,
    int *randPark, int *randMall, int *randBeach, int *randAquarium, int *randMuseum, int *randLand, int *randDogland,
    int *bestPark, int *bestMall, int *bestBeach, int *bestAquarium, int *bestMuseum, int *bestLand, int *bestDogland){
    
    for(int i=0;i<10;i++){ // 10 cycles
        nonOutingDays(chosenVenue, AP, nPEQ, lvlPE, expPE, nMathQ, lvlMath, expMath, bondBond, bondBecky, bondHenderson, bondDamian, nNonOutingDay, nOutingDay,
            photoPark, photoMall, photoBeach, photoAquarium, photoMuseum, photoLand, photoDogland);
        outingDay(AP, lvlMath, lvlPE, photoRating, chosenVenue, bestAngle, bondBecky, bondHenderson, bondDamian, bondBond,
            nNonOutingDay,nOutingDay,photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland,
            randPark, randMall, randBeach, randAquarium, randMuseum, randLand, randDogland,
            bestPark, bestMall, bestBeach, bestAquarium, bestMuseum, bestLand, bestDogland);
        
        // Resets AP if remaining points are less than 3. Otherwise, the number is unchanged.
        if(*AP<3)
        (*AP)=3;
    }

    // plays ending once all 10 cycles are done
    playEnding(lvlMath,lvlPE,photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland);
    
}

/*
    The start of the game. Prompts the player to select their very first venue 
    and initializes the game state before starting the full 40-day cycle.
    Precondition: Players must select the Start Game option in the home screen.
    @param AP Pointer to the player's starting Activity Points.
    @param photoRating Pointer to the initial photo rating.
    @param chosenVenue Pointer to store the player's first selected venue.
    @param bestAngle Pointer to store the best angle for photo minigames.
    @param nPEQ Pointer to the number of PE minigame questions.
    @param lvlPE Pointer to the player's initial PE level.
    @param expPE Pointer to the player's PE experience points.
    @param nMathQ Pointer to the number of Math minigame questions.
    @param lvlMath Pointer to the player's initial Math level.
    @param expMath Pointer to the player's Math experience points.
    @param bondBecky Pointer to Becky Blackbell bond level.
    @param bondHenderson Pointer to Mr. Henderson bond level.
    @param bondDamian Pointer to Damian Desmond bond level.
    @param bondBond Pointer to Bond Forger bond level.
    @param nNonOutingDay Pointer to the number of non-outing days completed.
    @param nOutingDay Pointer to the number of outing days completed.
    @param photoPark Pointer to Park photo rating.
    @param photoMall Pointer to City Mall photo rating.
    @param photoBeach Pointer to Ostania Beach photo rating.
    @param photoAquarium Pointer to West Berlint Aquarium photo rating.
    @param photoMuseum Pointer to Ostania Art Museum photo rating.
    @param photoLand Pointer to Berlint Mouseney Land photo rating.
    @param photoDogland Pointer to Park Avenue Dogland photo rating.
    @param randPark Pointer to random value for Park photo minigame.
    @param randMall Pointer to random value for City Mall photo minigame.
    @param randBeach Pointer to random value for Ostania Beach photo minigame.
    @param randAquarium Pointer to random value for West Berlint Aquarium photo minigame.
    @param randMuseum Pointer to random value for Ostania Art Museum photo minigame.
    @param randLand Pointer to random value for Berlint Mouseney Land photo minigame.
    @param randDogland Pointer to random value for Park Avenue Dogland photo minigame.
    @param bestPark Pointer to best angle for Park photo minigame.
    @param bestMall Pointer to best angle for City Mall photo minigame.
    @param bestBeach Pointer to best angle for Ostania Beach photo minigame.
    @param bestAquarium Pointer to best angle for West Berlint Aquarium photo minigame.
    @param bestMuseum Pointer to best angle for Ostania Art Museum photo minigame.
    @param bestLand Pointer to best angle for Berlint Mouseney Land photo minigame.
    @param bestDogland Pointer to best angle for Park Avenue Dogland photo minigame.
    @return void
*/

void dayZero(int *AP,int* photoRating,int *chosenVenue,int *bestAngle,int *nPEQ,int *lvlPE,int*expPE,int *nMathQ,int *lvlMath,int *expMath,int *bondBecky,int *bondHenderson,
    int *bondDamian,int *bondBond,int *nNonOutingDay,int *nOutingDay,
    int *photoPark,int *photoMall,int *photoBeach,int *photoAquarium,int *photoMuseum,int *photoLand,int *photoDogland,
    int *randPark,int *randMall,int *randBeach,int *randAquarium,int *randMuseum,int *randLand,int *randDogland,
    int *bestPark,int *bestMall,int *bestBeach,int *bestAquarium,int *bestMuseum,int *bestLand,int *bestDogland){

    clear();
    printf("Day #0\n");
    meetingDialogue();

    inputVenue(chosenVenue, bondBecky, bondHenderson, bondDamian, bondBond);
    chooseVenue(chosenVenue);
    pause();
    mainGame(AP,photoRating,chosenVenue,bestAngle,nPEQ,lvlPE,expPE,nMathQ,lvlMath,expMath,bondBond,bondBecky,bondHenderson,bondDamian,nNonOutingDay,nOutingDay,
        photoPark,photoMall,photoBeach,photoAquarium,photoMuseum,photoLand,photoDogland,
        randPark, randMall, randBeach, randAquarium, randMuseum, randLand, randDogland,
        bestPark, bestMall, bestBeach, bestAquarium, bestMuseum, bestLand, bestDogland);
}


// HOME SCREEN OPTIONS

/*
    Prints the Gameplay Premise and Objectives based on Sir Art's provided file.
    Precondition: Player must select the Instructions option in the home screen.
    @param N/A
    @return void
*/

void instructions(){

    clear();

    printf("*****************************************************************************************************************************\n");
    printf("GAMEPLAY PREMISE\n\n");
    printf("At the beginning of the game, Anya is given an assignment by her adviser Mr. Henderson, who\n");
    printf("informs Anya that she has an assignment that requires her to create a photo collage of memories\n");
    printf("spent with peers, which should properly demonstrate the ""elegance"" of Eden Academy's students\n");
    printf("in and around their respective communities. Anya is also reminded of an upcoming set of\n");
    printf("assessments for students that will properly asses their mathematical and physical skills, of which\n");
    printf("the best overall performing students in both the assessments and the project will be given a ""Stella Star"".\n\n");

    printf("Anya will have exactly 40 days to accomplish all of these tasks, which are to prepare and study\n");
    printf("for the Math and Physical Assessments by being tutored by her parents Loid Forger, and Yor\n");
    printf("Forger respectively. At the same time, she'll have to plan outings (called ""Ootings"" by Anya) and\n");
    printf("spend time with her family while bonding with her peers during school days.\n");
    printf("*****************************************************************************************************************************\n");
    printf("GAMEPLAY OBJECTIVES\n\n");
    printf("Within the span of 40 days, players must use their time wisely in helping Anya bond with her peers\n");
    printf("while studying for Math and training for her Physical Education assessments. While studying, she\n");
    printf("should bond with her peers to properly unlock places where she can have her outings. During her\n");
    printf("outings, players should guide her to take the ""Perfect Photo"" that she can add to her photo collage.\n");
    printf("*****************************************************************************************************************************\n");
    printf("STARTING VALUES\n\n");
    printf("Anya starts the game with the following stats:\n");
    printf("+ 3 AP = AP (Activity Points) determine how much ""Energy"" Anya has to do certain activities available to her.\n");
    printf("More on this in later sections.\n");
    printf("+ 0 BP for everybody (Desmond, Becky, Mr. Henderson, Bond) = BP (Bond Points) refer to her Bond Level with the\n");
    printf("four aforementioned individuals. She can raise these values through Bond Activities, which are discussed in Section VI.\n");
    printf("+ Math Level 1 = This determines how proficient she is in Math, and how the ""Study Activity"" Minigame will play out.\n");
    printf("She earns Levels based on how she performs in this mini game.\n");
    printf("+ PE Level 1 = This determines how proficient she is in Physical Education, and how the ""PE Activity"" Minigame will play out.\n");
    printf("She earns Levels based on how she performs in this mini game.\n");
    printf("+ 5 Camera Rolls = This determines the number of attempts she has at taking photos during her Outing Days.\n");
    printf("This is an important factor for the ""Memorable Photo"" minigame.\n");
    printf("*****************************************************************************************************************************\n");
    printf("NON-OUTING DAYS\n\n");
    printf("On non-outing days, you choose activities for morning and afternoon.\n");
    printf("Most actions cost 1 AP, except resting. Each function requires inputs within a specific range:\n");
    printf("Math Minigame: Answer math questions. Invalid answers repeat.\n");
    printf("PE Minigame: Match Yor's direction using the correct key. Wrong or invalid inputs repeat.\n");
    printf("Photo Minigame: Guess a number 1-1000. Anything outside this range shows an error.\n");
    printf("Venue Selection: Choose from 1-7; locked or out-of-range choices show an error.\n");
    printf("Non-Outing Activities (1-4): Options 1-3 need AP; option 4 is free. Invalid choices repeat.\n");
    printf("Errors always make the game ask again until the player enters a valid input.\n");
    printf("*****************************************************************************************************************************\n");
    printf("OUTING DAYS\n\n");
    printf("On outing days, the player visits the chosen venue and plays through a morning and afternoon sequence. Some actions cost AP, and the game checks the following:\n");
    printf("Morning Outing: Choose between available options (usually 1-2). If you don't have enough AP, the game shows an error and repeats the question.\n");
    printf("Activities & Bonding: Actions may increase photo ratings or bond levels depending on choices.\n");
    printf("Input Validation:\n");
    printf("Only valid options (usually 1-2) are accepted.\n");
    printf("Any number outside the given range prints an error and asks again.\n");
    printf("Venue Effects: Each venue has randomized values that affect the best photo result.\n");
    printf("Outing days always guide the player through dialogue, choices, and results, and the game does not move forward until valid input is given.\n");
    printf("*****************************************************************************************************************************\n");
    printf("GAMEPLAY MECHANICS\n\n");
    printf("Each activity that Anya performs costs 1 AP, including: Bond Activities and Mini-games\n");
    printf("If Anya does not have enough AP, she cannot select an activity that requires AP.\n");
    printf("Free Actions (Do NOT cost AP):\n");
    printf("Proceed Home (Regular School Day - Morning at Eden Academy)\n");
    printf("Slack Off (Regular School Day - Afternoon at Home)\n");
    printf("Go to Ooting! (Outing Day - Morning Preparation)\n");
    printf("Go Home (Outing Day - Morning - Ooting Time!)\n");
    printf("Decide Next Outing Venue (Outing Day - Evening - Family Meeting)\n");
    printf("Daily AP Recovery:\n");
    printf("At the end of each day, Anya automatically gains +1 AP except: on the 3rd regular school day of each 4-day cycle (no AP gained)\n");
    printf("Cycle Reset Rule:\n");
    printf("At the end of a 4-day cycle, Anya's AP resets to 3 unless she has more than 3 AP saved (e.g., she has 5 AP).\n");
    printf("In that case, she keeps her higher AP amount.\n");
    printf("*****************************************************************************************************************************\n");
    printf("BOND ACTIVITIES\n\n");
    printf("Anya can perform Bond Activities with four characters: Damian, Becky, Mr. Henderson, and Bond.\n");
    printf("Each character starts with 0 Bond Points (BP), and Anya can earn up to 5 BP per character to reach their maximum bond level.\n");
    printf("\nPerforming a Bond Activity:\n");
    printf("Costs 1 AP\n");
    printf("Advances the day/phase automatically\n");
    printf("After bonding with Damian, Becky, or Mr. Henderson, Anya goes home\n");
    printf("After bonding with Bond, the day ends\n");
    printf("\nWhen bonding, Anya can earn 1 BP depending on her stats:\n");
    printf("\tDamian Desmond:\n");
    printf("\tLevel 1 PE = 0%% chance\n");
    printf("\tLevel 2 PE = 25%%\n");
    printf("\tLevel 3 PE = 50%%\n");
    printf("\tMAX PE = 75%%\n");
    printf("\tBecky Blackbell:\n");
    printf("\tAlways 75%% chance, regardless of stats\n");
    printf("\tMr. Henderson:\n");
    printf("\tLevel 1 Math = 0%%\n");
    printf("\tLevel 2 Math = 50%%\n");
    printf("\tLevel 3 Math = 75%%\n");
    printf("\tMAX Math = 100%%\n");
    printf("\tBond Forger:\n");
    printf("\tAlways 100%% chance to gain 1 BP\n");
    printf("*****************************************************************************************************************************\n");
    printf("MINIGAMES\n\n");
    printf("When Anya completes a minigame, she earns EXP based on her performance: 60%% correct grants 1 EXP, 80%% correct grants 2 EXP,\n");
    printf("and 100%% correct grants 3 EXP with a 50%% chance of not consuming an AP point and awarding an additional 1 AP.\n");
    printf("The EXP required to level up increases with each level: 5 EXP for Level 1, 10 EXP for Level 2, and 15 EXP for Level 3,\n");
    printf("and EXP resets to 0 upon leveling up. At Level MAX, Anya no longer gains EXP, but achieving 100%% still gives a 60%% chance\n");
    printf("of not using an AP point and grants 2 additional AP. Regardless of performance, playing a minigame ends the day and\n");
    printf("progresses the game to the next day.\n");
    printf("*****************************************************************************************************************************\n");
    printf("MATH MINIGAME\n\n");
    printf("The ""Study Math with Loid"" minigame allows the player to help Anya improve her mathematical skills by answering randomly\n");
    printf("generated equations. In each round, two integers and an operator are displayed, and Anya must provide the correct answer.\n");
    printf("The difficulty and type of questions depend on Anya’s Math Level: Level 1 features addition and subtraction with numbers\n");
    printf("from 1 to 999 (5 questions); Level 2 adds multiplication with numbers from 1 to 20 and uses values up to 9999 (10 questions);\n");
    printf("Level 3 expands multiplication to numbers up to 50 while keeping addition and subtraction with numbers up to 9999\n");
    printf("(10 questions); Level MAX has the same range and operations as Level 3.\n");
    printf("*****************************************************************************************************************************\n");
    printf("PHYSICAL EDUCATION MINIGAME\n\n");
    printf("""Train Physical Activity with Yor"" helps Anya improve her PE skills by testing her reaction time.\n");
    printf("Yor gives prompts, and Anya must input the correct corresponding action. The prompts vary by PE Level:\n");
    printf("PE Level 1: 10 random prompts consisting of Up! = 'w'/'W', Down! = 's'/'S', Left! = 'a'/'A', Right! = 'd'/'D'.\n");
    printf("PE Level 2: 10 random prompts including Level 1 prompts plus North! = '8', South! = '2', East! = '6', West! = '4'.\n");
    printf("PE Level 3: 10 random prompts including all Level 2 prompts plus UP AHEAD! = 'W', BEHIND YOU! = 'S', TO THE LEFT! = 'A',\n");
    printf("TO THE RIGHT! = 'D', and diagonals Northwest! = '7', Northeast! = '9', Southwest! = '1', Southeast! = '3'.\n");
    printf("PE Level MAX: Identical to Level 3, with all above prompts included.\n");
    printf("Anya must provide the correct input for each prompt to successfully complete the minigame.\n");
    printf("*****************************************************************************************************************************\n");
    printf("MEMORABLE PHOTO MINIGAME\n\n");
    printf("The “Memorable Photo” minigame allows Anya to collect memorable photos during outings with Loid and Yor.\n");
    printf("In this minigame, Anya has 5 rolls to guess a number between 1 and 1000, which is randomly generated for\n");
    printf("each venue at the start of the playthrough and remains the same for that venue throughout the game.\n");
    printf("Her photo rating depends on how close her guess is to the venue's magical number:\n");
    printf("NOT GOOD: Default rating for venues where the minigame hasn't been played or guesses are far from the magical number.\n");
    printf("OKAY: Guess is within 100 points of the magical number.\n");
    printf("VERY GOOD: Guess is within 10 points of the magical number.\n");
    printf("PERFECT: Guess matches the magical number exactly.\n");
    printf("Unlike other minigames, Anya can re-attempt the Memorable Photo minigame as long as she has remaining AP.\n");
    printf("*****************************************************************************************************************************\n");
    printf("PLAYER STATISTICS\n\n");
    printf("As the players play through the game, they are able to view the Stats that the player has obtained\n");
    printf("so far, ranging from the Levels of Anya, her previous performances in the photos, and her bond levels.\n");
    printf("*****************************************************************************************************************************\n");
    printf("ENDINGS\n\n");
    printf("Once the 40 days have elapsed, Anya's performance will lead her to the game's ending.\n");
    printf("Perfect Ending: Anya succeeds in submitting her project and ends up with near-top ranks in the\n");
    printf("exams. As a result, she is awarded the Stella Star, with Mr. Henderson praising her for her\n");
    printf("performance being “Very Elegant”. This ending is achievable by obtaining a PERFECT rating in ALL memorable photos for ALL venues.\n");
    printf("Neutral Ending: Anya submits her project, but there are better projects that have been submitted.\n");
    printf("However, she passes her exams, but does not earn the Stella Star. This ending is achieved by\n");
    printf("obtaining a PERFECT memorable photo rating in at least 3 venues and maxing out her Math and PE levels.\n");
    printf("Bad Ending: Anya submits her project, but it is incomplete. Likewise, she does not pass her\n");
    printf("exams and, to Loid's dismay, Anya gets a Tonitrus bolt for her performance. This ending is\n");
    printf("obtained if less than 3 PERFECT memorable photo ratings are obtained or her PE and MATH levels are not maxed out.\n");
    printf("*****************************************************************************************************************************\n");
    printf("SCROLL to read INSTRUCTIONS!\n");
    printf("*****************************************************************************************************************************\n");
    pause();

}

/*
    Exits the game and then prints a farewell greeting in ASCII art.
    Precondition: Players must select the Exit option in the home screen.
    @param N/A
    @return void
*/

void exitGame(){
    clear();
    printf("*****************************************************************************************************************************\n");
    printf("\t\t\t\t\t  _____                 _ _                _ \n");
    printf("\t\t\t\t\t / ____|               | | |              | |\n");
    printf("\t\t\t\t\t| |  __  ___   ___   __| | |__  _   _  ___| |\n");
    printf("\t\t\t\t\t| | |_ |/ _ \\ / _ \\ / _` | '_ \\| | | |/ _ \\ |\n");
    printf("\t\t\t\t\t| |__| | (_) | (_) | (_| | |_) | |_| |  __/_|\n");
    printf("\t\t\t\t\t \\_____|\\___/ \\___/ \\__,_|_.__/ \\__, |\\___(_)\n");
    printf("\t\t\t\t\t                                 __/ |       \n");
    printf("\t\t\t\t\t                                |___/        \n");
    printf("*****************************************************************************************************************************\n");
}

/*
    Main function that plays the entire game.
    Precondition: N/A
    @param N/A
    @return 0 on success
*/

int main()
{
    srand(time(NULL));

    int lvlMath = 1, lvlPE = 1, photoRating = 0;
    int bondBecky = 0, bondHenderson = 0, bondDamian = 0, bondBond = 0;
    int nMathQ = 0, nPEQ = 0;
    int expMath = 0, expPE = 0, bestAngle = 0;
    int photoPark = 0, photoMall = 0, photoBeach = 0, photoAquarium = 0, photoMuseum = 0, photoLand = 0, photoDogland = 0;
    int randPark = generateRandomValue(1,1000), randMall = generateRandomValue(1,1000), randBeach = generateRandomValue(1,1000),
    randAquarium = generateRandomValue(1,1000), randMuseum = generateRandomValue(1,1000), randLand = generateRandomValue(1,1000), randDogland = generateRandomValue(1,1000);
    
    int bestPark = 0, bestMall = 0, bestBeach = 0, bestAquarium = 0, bestMuseum = 0, bestLand = 0, bestDogland = 0;
    int nNonOutingDay = 0, nOutingDay = 0, chosenVenue = 0, AP = 3;

    int valid=1;
    

    while (valid){
        int startChoice = homeScreen();
    switch (startChoice)
    {
    case 1:
    printf("                                                    Starting game...");
    Sleep(1000); // delay for 1000 milliseconds
    dayZero(&AP,&photoRating,&chosenVenue,&bestAngle,&nPEQ,&lvlPE,&expPE,&nMathQ,&lvlMath,&expMath,&bondBecky,&bondHenderson,&bondDamian,&bondBond,&nNonOutingDay,&nOutingDay,
        &photoPark,&photoMall,&photoBeach,&photoAquarium,&photoMuseum,&photoLand,&photoDogland,
        &randPark,&randMall,&randBeach,&randAquarium,&randMuseum,&randLand,&randDogland,
        &bestPark, &bestMall, &bestBeach, &bestAquarium, &bestMuseum, &bestLand, &bestDogland);
    break;
    case 2:
    printf("                                                  Showing instructions...");
    Sleep(1000); // delay for 1000 milliseconds
    instructions();
    break;
    case 3:
    printf("                                                       Exiting...");
    Sleep(1000); // delay for 1000 milliseconds
    exitGame();
    valid=0; // exits loop
    break;
    default:
    clear();
    break;
    }
}

    return 0;

}