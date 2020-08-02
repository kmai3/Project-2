/*
 * File:   main.cpp
 * Author: Kevin Mai
 * Created on August 1, 2020, 5:00 PM
 * Purpose: Dungeons and Dragon Board Game Project
 */

#include <iostream> //I/O Library
#include <string> // for strings
#include <iomanip> //setw
#include <cmath> // For sqrt and pow functions
#include <fstream> // To put in files
#include <cstdlib> //Random Seed Time, Exit Function 
#include <ctime> //Random Seed
#include <vector> // Vectors 
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...
//Function Prototypes
char start1(); // Basic Menu to Start the Game
void start2(char , char &, string &, string oldsc);
bool capt(vector <int> &, int); //Captcha to detect boting 
void showmobs(string[][4]); //Displays the Mobs able to be fought 
int atkcalc(int, int); // Calculates Attack value
void compsc(); // Shows Completion Value 
bool gfight(string [], int &, int , int, int ,int &, //Goblin Battle
            int, int, float &, int, int, int, int);
bool sfight(string [], int &, int, int, int, int &, //Skeleton Battle
            int, int, float &, int, int, int, int);
bool ofight(string [], int &, int, int, int, int &, //Ogre Battle
            int, int, float &, int, int, int, int, string[][4]);
bool sGfght(string [], int &, int, int, int, int &,//Skeleton Giant Battle
            int, int, float &, int, int, int, int, string[][4]);
bool dMfght(string [], int &, int, int, int, int &, //Dark Mage Battle
            int, int, float &, int, int, int, int, string[][4]);
bool dfight(string [], int &, int, int, int, int &, //Dragon Battle
            int, int, float &, int, int, int, int, string[][4]);
//Execution of Code Begins here
int main(int argc, char** argv) {
    //Random seed
    srand(static_cast<unsigned int>(time(0)));
    unsigned int cd = rand() % 4 + 2; //Cd is the crit damage 
    
    //Declare all variables for this function
    float score;
    fstream file;
    int magehp, //The hp value of the mage
        atk ,//The atk value of the character
        fhp, // The HP of the fighter
        rhp, //The HP value of the ranger
        gobhp, //HP of the goblin
        skelhp, //HP of the Skeleton
        ogrehp, //HP of the ogre
        gskhp, //HP of the Skeleton Giant 
        dmhp, //Hp of the Darkmage
        job, //job
        gatk, //Attack of the Goblin
        satk, //Attack of the Skeleton
        oatk, //Attack of the Ogre
        gsatk, //Attack of the Skeleton Giant 
        dMatk, //Attack of the Dark Mage
        datk, //Attack of the Dragon
        rgob, //Rounds to beat goblin
        rskel, //Rounds to beat skeleton
        rogre, //Rounds to beat the ogre
        rgskel, //Rounds to beat Giant Skeleton
        rDMage, //Rounds to beat the Dark Mage
        rdrag, //Rounds to beat the dragon
        n, //Size of the cpch vector 
        xp, // The amount of xp of the character, makes the character stronger
        draghp; //HP of the Dragon
    char njob, //Job represented in a number
         start; // Start of the game Menu
    string name, //Name of the Player
           oldsc; // Old score from the previous game
    string rclass[12]={"Fireball", "Hydro Cannon", "Force Smash", "Earthquake",
    "Fire Arrow", "Ice Shot", "Charged Shot", "Metal Bolt", "Fire Sword",
    "Hydro Slash", "Heavy Strike", "Obsidian Pillar"};
    bool cont;
    string bosses[3][4]={{"Goblin", "Skeleton", "Ogre"},
                         {"Skeleton Giant", "Dark Mage", "Dragon"}};
    vector<int> cpch(n); //used in computer check
    
    //Initialize the code
    //Balancing Area Change Values to make it harder or easier
    magehp=100;
    fhp=300;
    rhp=150;
    xp=1;
    //Boss Values
    gobhp=15;
    skelhp=20;
    ogrehp=30;
    gskhp=56;
    dmhp=40;
    draghp=100;
    gatk=1;
    satk=2;
    oatk=5;
    gsatk=10;
    dMatk=20;
    datk=20;
    //Amount of Rounds to beat the bosses
    rgob=9;
    rskel=5;
    rogre=5;
    rgskel=5;
    rDMage=10;
    rdrag=20;
    score=100;
    n=10;
    oldsc="";
    string temp; //Temp String for scoreboard
        while(file >> temp){ //Shows the Old Scores
            oldsc+=temp+"/n";
        }
    //Scoreboard called score.txt
    file.open("score.txt",ios::in|ios::out);
    file >> oldsc;
    if(file.is_open()){cout<<"Score Works"<<endl;} //Checks if file is opened
    //Start up of the Game
    start=start1();
    start2(start, njob, name, oldsc);
    if(capt(cpch, n)){
          cout<<"You Failed the Captcha"<<endl;
          cout<<"Exiting....."<<endl;
          exit(0);
      } 
    //Attack values depend on xp and class 
    atk=atkcalc(njob,xp); 
    showmobs(bosses);
    if (njob==49) //If the class chosen is Mage 
    {
      compsc();
      cont=gfight(rclass, magehp, gobhp, atk, cd, xp, 
                    gatk, rgob, score, 0, 1, 2, 3 ); //First Goblin Fight
      if (cont=false){ //Checks for Game Over
          exit(0);
      }
      else compsc();
      atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
      cont=sfight(rclass, magehp, skelhp, atk, cd, xp,
                     satk, rskel, score, 0, 1, 2, 3);//Skeleton Fight 
      if (cont=false){ //Checks for Game Over
          exit(0);
      }
      else compsc();
      atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
      cont=ofight(rclass, magehp, ogrehp, atk, cd, xp,
                     oatk, rogre, score, 0, 1, 2, 3, bosses);//Ogre Fight
      if (cont=false){ //Checks for Game Over
          exit(0);
      }
      else compsc();
      atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
      cont=sGfght(rclass, magehp, gskhp, atk, cd, xp,
                      gsatk, rgskel, score, 0, 1, 2, 3, bosses);
      //^Skeleton Giant Fight
      if (cont=false){ //Checks for Game Over
          exit(0);
      }
      else compsc();
      atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
      cont=dMfght(rclass, magehp, dmhp, atk, cd, xp,
                      dMatk, rDMage, score, 0, 1, 2, 3, bosses);
      //^Dark Mage Fight
      if (cont=false){ //Checks for Game Over
          exit(0);
      }
      else compsc();
      atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
      cont=dfight(rclass, magehp, draghp, atk, cd, xp,
                      datk, rdrag, score, 0, 1, 2, 3, bosses);
      //^Dragon fight
      if (cont=false){ //Checks for Game Over
          exit(0);
      }
      else compsc();
    }
    // End of Mage Code
    if (njob==50) //If the class chosen is Ranger
    {
        compsc();
        cont=gfight(rclass, rhp, gobhp, atk, cd, //First Goblin Fight
                    xp, gatk, rgob, score, 4,5,6,7);
        if (cont=false){
            exit(0);
           }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and changes attack value 
        cont=sfight(rclass, rhp, skelhp, atk, cd, xp,
                     satk, rskel, score, 4, 5, 6, 7); //Skeleton Fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=ofight(rclass, rhp, ogrehp, atk, cd, xp,
                     oatk, rogre, score, 4, 5, 6, 7, bosses); //Ogre Fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=sGfght(rclass, rhp, gskhp, atk, cd, xp,
                      gsatk, rgskel, score, 4, 5, 6, 7, bosses);
        //^Skeleton Giant Fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=dMfght(rclass, rhp, dmhp, atk, cd, xp,
                      dMatk, rDMage, score, 4, 5, 6, 7, bosses);
         //^Dark Mage Fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=dfight(rclass, rhp, draghp, atk, cd, xp,
                      datk, rdrag, score, 4, 5, 6, 7, bosses);
        //^Dragon fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
    }
    // End of Ranger Code
    if (njob==51) //If the class chosen is Fighter
    {
        compsc();
        cont=gfight(rclass, fhp, gobhp, atk, cd, xp, //First Goblin Fight
                    gatk, rgob, score, 8,9,10,11);
        atk=atkcalc(njob,xp); //Levels up and changes attack value
        if(cont=false){
            exit(0);
        }
        else compsc();
        cont=sfight(rclass, fhp, skelhp, atk, cd, xp,
                        satk, rskel, score, 8, 9, 10, 11); //Skeleton Fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=ofight(rclass, fhp, ogrehp, atk, cd, xp,
                     oatk, rogre, score, 8, 9, 10, 11, bosses); //Ogre Fight 
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=sGfght(rclass, fhp, gskhp, atk, cd, xp,
                      gsatk, rgskel, score, 8, 9, 10, 11, bosses);
        //^Skeleton Giant Fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=dMfght(rclass, fhp, dmhp, atk, cd, xp,
                      dMatk, rDMage, score, 8, 9, 10, 11, bosses);
         //^Dark Mage Fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
        atk=atkcalc(njob,xp); //Levels up and Changes Attack Value 
        cont=dfight(rclass, fhp, draghp, atk, cd, xp,
                      datk, rdrag, score, 8, 9, 10, 11, bosses);
        //^Dragon fight
        if (cont=false){ //Checks for Game Over
          exit(0);
        }
        else compsc();
    }
    //End of Fighter's Code
    
    //Score Showing in the txt file
    file << oldsc;
    file <<fixed << name <<setw(7) << setprecision(2) << score << endl;
    file.close();
    //Clean up the code, close files, deallocate memory, etc...
    //Exit stage right
    return 0;
}
char start1(){
    char start;
    cout<<"Dungeon and Dragons AI ver"<<endl;
    cout<<"Enter 1 to Start, or Enter 2 for more information"<<endl;
    cout<<"Enter Anything Else to show the Previous Score"<<endl;
    cin>>start;
    return start;
}
void start2(char start, char &njob, string &name, string oldsc){
    int vstart=start-48; //Converts into menu options with Type Casting
    if (vstart==2) //Choice 2 Gives more information about the game 
    {
        cout<<"This is based off the board game Dungeons and Dragons"<<endl;
        cout<<"The objective of the game is to clear the dungeon"<<endl;
        cout<<"To clear the Dungeon you must kill 5 main monsters"<<endl;
        cout<<"Each monster is weak to a certain attribute"<<endl;
        cout<<"Read the game information to learn more about this"<<endl;
        cout<<"You are to pick from 3 different classes"<<endl;
        start=1;
    }
    else if (vstart==1) // After Starting, Player chooses a class
    {
        cout<<"Enter Your Name for Scoreboard"<<endl;
        cin>>name;
        cout<<"Pick a Class"<<endl;
        cout<<"1=Mage, 2=Ranger, or 3=Fighter"<<endl;
        cout<<"Enter in the Number Associated "<<endl;
        cin>>njob;
        while (njob>51 || njob<48)
        {
            cout<<"Please Enter your Class Again"<<endl;
            cin>>njob;
        }
    }
    else
    {
        cout<<oldsc<<endl;
    }
}
bool capt(vector <int> &a, int n){
    int s; //Smallest Number
    cout<<"Bot Check"<<endl;
    for(int i=0; i<n; i++){
        a[i]=rand()%90+10; //[10,99]
    }
    a.shrink_to_fit();
    for(int i=0; i<n; i++){
        cout<<a[i]<<endl;
    }
    cout<<"What is the smallest number?"<<endl;
    cin>>s;
    for(int i=0; i<n-1;i++){
        int minval=a[i];
        int idx=i;
        for(int j=i+1;j<n;j++){
            if(minval>a[j]){
             minval=a[j];
             idx=j;
            }
        }
        a[idx]=a[i];
        a[i]=minval;
    }
    if(s==a[0]){
        return false;
    }
    else{
        return true;
    }
}
void showmobs(string bosses[][4]){
    cout<<"Mob List"<<endl;
    for(int i=0; i<2; i++){
        for(int j=0; j<3; j++){
        cout<<setw(15)<<bosses[i][j]<<"->";
        }
        cout<<endl;
    }
}
int atkcalc(int njob, int xp){
    int atk;
    atk=(njob==49) ? 2+2*xp:(njob==50)? 2+pow(2,xp):4+xp; 
    return atk;
}
void compsc(){
    static int cscore=0; //Completion Score 
    cout<<"Your Completion Score is "<<cscore<<endl;
    cscore++; 
}
bool gfight(string rclass[], int &hp, int gobhp,int atk,int cd,int &xp, 
        int gatk, int rgob, float &score, int move1, int move2, 
        int move3, int move4){
    bool cont;
    do{ //Battle Begins!
         cout<<"You enter in the Dungeon and around the corner you see"<<endl;
         cout<<"A goblin approaches"<<endl; 
         cout<<"Battle"<<endl;
             int dmg1;
             cout<<fixed;
             cout<<"The Goblin has "<<gobhp<<" Hp"<<endl;
             cout<<"You have "<<hp<<"Hp"<<endl;
             cout<<"You have "<<rgob;
             cout<<" rounds left before reinforcements"<<endl;
             cout<<"Pick your ability "<<endl;
             cout<<"Enter 1 for "<<rclass[move1]<<endl;
             cout<<"Enter 2 for "<<rclass[move2]<<endl; 
             cout<<"Enter 3 for "<<rclass[move3]<<endl;
             cout<<"Enter 4 for "<<rclass[move4]<<endl;
             cin>>dmg1;
             switch(dmg1){ //Menu for picking abilities 
                 case 1: gobhp=gobhp-(atk*cd);break;
                 case 2: gobhp=gobhp-(atk/cd);break;
                 case 3: gobhp=gobhp-atk;break;
                 case 4: gobhp=gobhp-atk;break;
                 default: cout<<"Pick one of the numbers provided"<<endl;
                 cin>>dmg1;break;
             }
         score-=1;
         rgob-=1;
         hp-=gatk;
         //Stops the loops when someone dies or reinforcements come 
     }while(hp>0 && rgob>0 && gobhp>0); 
     for(int i=1; i<25; i++) //For Visual Seperation of the End Game 
     {
         cout<<"*";
     }
     cout<<endl;
     if (gobhp<=0){ //If Kills the Goblin
         cout<<"Congrats You have killed the Goblin"<<endl;
         cout<<"You have gained a Level"<<endl;
         xp=xp+1;
         cont=true;
     }
     if (rgob<=0){ //If Reinforcements came
         cout<<"Goblin Reinforcements have came"<<endl;
         cout<<"Game Over"<<endl;
         score=score/2;
         cont=false;
     }
     if (hp<=0){ //If Player Died 
         cout<<"You have Died"<<endl;
         cout<<"Game Over"<<endl;
         score=score/4;
         cont=false;
     }
     if(cont==true) //continues down the dungeon if goblin was killed
     {
         cout<<"Down the Dungeon you go"<<endl;
     }
     return cont;
}
bool sfight(string rclass[], int &hp, int bosshp,int atk,int cd,int &xp, 
        int aboss, int rboss, float &score, int move1, int move2, 
        int move3, int move4){
    bool cont;
    do{ //Battle Begins!
         cout<<"You went further down the dungeon"<<endl;
         cout<<"A Skeleton approaches"<<endl; 
         cout<<"Battle"<<endl;
             int dmg1;
             cout<<fixed;
             cout<<"The Skeleton has "<<bosshp<<" Hp"<<endl;
             cout<<"You have "<<hp<<"Hp"<<endl;
             cout<<"You have "<<rboss;
             cout<<" rounds left before reinforcements"<<endl;
             cout<<"Pick your ability "<<endl;
             cout<<"Enter 1 for "<<rclass[move1]<<endl;
             cout<<"Enter 2 for "<<rclass[move2]<<endl; 
             cout<<"Enter 3 for "<<rclass[move3]<<endl;
             cout<<"Enter 4 for "<<rclass[move4]<<endl;
             cin>>dmg1;
             switch(dmg1){ //Menu for picking abilities 
                 case 1: bosshp=bosshp-(atk/cd);break;
                 case 2: bosshp=bosshp-atk;break;
                 case 3: bosshp=bosshp-atk;break;
                 case 4: bosshp=bosshp-(atk*cd);break;
                 default: cout<<"What ability did you use?, hurry you are dying"
                         <<endl;
                 cin>>dmg1;break;
             }
         score-=1;
         rboss-=1;
         hp-=aboss;
         //Stops the loops when someone dies or reinforcements come 
     }while(hp>0 && rboss>0 && bosshp>0); 
     for(int i=1; i<25; i++) //For Visual Seperation of the End Game 
     {
         cout<<"*";
     }
     cout<<endl;
     if (bosshp<=0){ //If Kills the Skeleton
         cout<<"Congrats You have killed the Skeleton"<<endl;
         cout<<"You have gained a Level"<<endl;
         xp=xp+1;
         cont=true;
     }
     if (rboss<=0){ //If Reinforcements came
         cout<<"Skeleton Reinforcements have came"<<endl;
         cout<<"Game Over"<<endl;
         score=score/2;
         cont=false;
     }
     if (hp<=0){ //If Player Died 
         cout<<"You have Died"<<endl;
         cout<<"Game Over"<<endl;
         score=score/4;
         cont=false;
     }
     if(cont==true) //continues down the dungeon if skeleton was killed
     {
         cout<<"Down the Dungeon you go"<<endl;
     }
     return cont;
}
bool ofight(string rclass[], int &hp, int bosshp,int atk,int cd,int &xp, 
        int aboss, int rboss, float &score, int move1, int move2, 
        int move3, int move4, string bosses[][4]){
    bool cont;
    do{ //Battle Begins!
         cout<<"You went further down the dungeon"<<endl;
         cout<<"A "<<bosses[0][2]<<"approaches"<<endl; 
         cout<<"Battle"<<endl;
             int dmg1;
             cout<<fixed;
             cout<<"The "<<bosses[0][2]<<" has "<<bosshp<<" Hp"<<endl;
             cout<<"You have "<<hp<<"Hp"<<endl;
             cout<<"You have "<<rboss;
             cout<<" rounds left before reinforcements"<<endl;
             cout<<"Pick your ability "<<endl;
             cout<<"Enter 1 for "<<rclass[move1]<<endl;
             cout<<"Enter 2 for "<<rclass[move2]<<endl; 
             cout<<"Enter 3 for "<<rclass[move3]<<endl;
             cout<<"Enter 4 for "<<rclass[move4]<<endl;
             cin>>dmg1;
             switch(dmg1){ //Menu for picking abilities 
                 case 1: bosshp=bosshp-(atk*cd);break;
                 case 2: bosshp=bosshp-atk;break;
                 case 3: bosshp=bosshp-atk;break;
                 case 4: bosshp=bosshp-(atk/cd);break;
                 default: cout<<"What ability did you use?, hurry you are dying"
                         <<endl;
                 cin>>dmg1;break;
             }
         score-=1;
         rboss-=1;
         hp-=aboss;
         //Stops the loops when someone dies or reinforcements come 
     }while(hp>0 && rboss>0 && bosshp>0); 
     for(int i=1; i<25; i++) //For Visual Seperation of the End Game 
     {
         cout<<"*";
     }
     cout<<endl;
     if (bosshp<=0){ //If Kills the Ogre
         cout<<"Congrats You have killed the "<<bosses[0][2]<<endl;
         cout<<"You have gained a Level"<<endl;
         xp=xp+1;
         cont=true;
     }
     if (rboss<=0){ //If Reinforcements came
         cout<<bosses[0][2]<<"Reinforcements have came"<<endl;
         cout<<"Game Over"<<endl;
         score=score/2;
         cont=false;
     }
     if (hp<=0){ //If Player Died 
         cout<<"You have Died"<<endl;
         cout<<"Game Over"<<endl;
         score=score/4;
         cont=false;
     }
     if(cont==true) //continues down the dungeon if ogre was killed
     {
         cout<<"Down the Dungeon you go"<<endl;
     }
     return cont;
}
bool sGfght(string rclass[], int &hp, int bosshp,int atk,int cd,int &xp, 
        int aboss, int rboss, float &score, int move1, int move2, 
        int move3, int move4, string bosses[][4]){
    bool cont;
    do{ //Battle Begins!
         cout<<"You went further down the dungeon"<<endl;
         cout<<"A "<<bosses[1][0]<<"approaches"<<endl; 
         cout<<"Battle"<<endl;
             int dmg1;
             cout<<fixed;
             cout<<"The "<<bosses[1][0]<<" has "<<bosshp<<" Hp"<<endl;
             cout<<"You have "<<hp<<"Hp"<<endl;
             cout<<"You have "<<rboss;
             cout<<" rounds left before reinforcements"<<endl;
             cout<<"Pick your ability "<<endl;
             cout<<"Enter 1 for "<<rclass[move1]<<endl;
             cout<<"Enter 2 for "<<rclass[move2]<<endl; 
             cout<<"Enter 3 for "<<rclass[move3]<<endl;
             cout<<"Enter 4 for "<<rclass[move4]<<endl;
             cin>>dmg1;
             switch(dmg1){ //Menu for picking abilities 
                 case 1: bosshp=bosshp-(atk/cd);break;
                 case 2: bosshp=bosshp-atk;break;
                 case 3: bosshp=bosshp-atk;break;
                 case 4: bosshp=bosshp-(atk*cd);break;
                 default: cout<<"What ability did you use?, hurry you are dying"
                         <<endl;
                 cin>>dmg1;break;
             }
         score-=1;
         rboss-=1;
         hp-=aboss;
         //Stops the loops when someone dies or reinforcements come 
     }while(hp>0 && rboss>0 && bosshp>0); 
     for(int i=1; i<25; i++) //For Visual Seperation of the End Game 
     {
         cout<<"*";
     }
     cout<<endl;
     if (bosshp<=0){ //If Kills the Skeleton Giant
         cout<<"Congrats You have killed the "<<bosses[1][0]<<endl;
         cout<<"You have gained a Level"<<endl;
         xp=xp+1;
         cont=true;
     }
     if (rboss<=0){ //If Reinforcements came
         cout<<bosses[1][0]<<"Reinforcements have came"<<endl;
         cout<<"Game Over"<<endl;
         score=score/2;
         cont=false;
     }
     if (hp<=0){ //If Player Died 
         cout<<"You have Died"<<endl;
         cout<<"Game Over"<<endl;
         score=score/4;
         cont=false;
     }
     if(cont==true) //continues down the dungeon if skeleton giant was killed
     {
         cout<<"Down the Dungeon you go"<<endl;
     }
     return cont;
}
bool dMfght(string rclass[], int &hp, int bosshp,int atk,int cd,int &xp, 
        int aboss, int rboss, float &score, int move1, int move2, 
        int move3, int move4, string bosses[][4]){
    bool cont;
    do{ //Battle Begins!
         cout<<"You went further down the dungeon"<<endl;
         cout<<"A "<<bosses[1][1]<<"approaches"<<endl; 
         cout<<"Battle"<<endl;
             int dmg1;
             cout<<fixed;
             cout<<"The "<<bosses[1][1]<<" has "<<bosshp<<" Hp"<<endl;
             cout<<"You have "<<hp<<"Hp"<<endl;
             cout<<"You have "<<rboss;
             cout<<" rounds left before reinforcements"<<endl;
             cout<<"Pick your ability "<<endl;
             cout<<"Enter 1 for "<<rclass[move1]<<endl;
             cout<<"Enter 2 for "<<rclass[move2]<<endl; 
             cout<<"Enter 3 for "<<rclass[move3]<<endl;
             cout<<"Enter 4 for "<<rclass[move4]<<endl;
             cin>>dmg1;
             switch(dmg1){ //Menu for picking abilities 
                 case 1: bosshp=bosshp-(atk/cd);break;
                 case 2: bosshp=bosshp-(atk/cd);break;
                 case 3: bosshp=bosshp-(atk*cd);break;
                 case 4: bosshp=bosshp-(atk/cd);break;
                 default: cout<<"What ability did you use?, hurry you are dying"
                         <<endl;
                 cin>>dmg1;break;
             }
         score-=1;
         rboss-=1;
         hp-=aboss;
         //Stops the loops when someone dies or reinforcements come 
     }while(hp>0 && rboss>0 && bosshp>0); 
     for(int i=1; i<25; i++) //For Visual Seperation of the End Game 
     {
         cout<<"*";
     }
     cout<<endl;
     if (bosshp<=0){ //If Kills the dark mage
         cout<<"Congrats You have killed the "<<bosses[1][1]<<endl;
         cout<<"You have gained a Level"<<endl;
         xp=xp+1;
         cont=true;
     }
     if (rboss<=0){ //If Reinforcements came
         cout<<bosses[1][1]<<"Reinforcements have came"<<endl;
         cout<<"Game Over"<<endl;
         score=score/2;
         cont=false;
     }
     if (hp<=0){ //If Player Died 
         cout<<"You have Died"<<endl;
         cout<<"Game Over"<<endl;
         score=score/4;
         cont=false;
     }
     if(cont==true) //continues down the dungeon if the dark mage was defeated
     {
         cout<<"Down the Dungeon you go"<<endl;
         cout<<"Fighting the Dark Mage has taught you how to self heal"<<endl;
         cout<<"You can now self heal and block at the same time"<<endl;
         cout<<"Added on the next Update"<<endl;
     }
     return cont;
}
bool dfight(string rclass[], int &hp, int bosshp,int atk,int cd,int &xp, 
        int aboss, int rboss, float &score, int move1, int move2, 
        int move3, int move4, string bosses[][4]){
    bool cont;
    do{ //Battle Begins!
         cout<<"You are nearing the end of the dungeon"<<endl;
         cout<<"A "<<bosses[1][2]<<"approaches"<<endl; 
         cout<<"Battle"<<endl;
             int dmg1;
             cout<<fixed;
             cout<<"The "<<bosses[1][2]<<" has "<<bosshp<<" Hp"<<endl;
             cout<<"You have "<<hp<<"Hp"<<endl;
             cout<<"You have "<<rboss;
             cout<<" rounds left before reinforcements"<<endl;
             cout<<"Pick your ability "<<endl;
             cout<<"Enter 1 for "<<rclass[move1]<<endl;
             cout<<"Enter 2 for "<<rclass[move2]<<endl; 
             cout<<"Enter 3 for "<<rclass[move3]<<endl;
             cout<<"Enter 4 for "<<rclass[move4]<<endl;
             cout<<"Enter 5 to Block and Heal"<<endl;
             cin>>dmg1;
             switch(dmg1){ //Menu for picking abilities 
                 case 1: bosshp=bosshp-(atk/cd);break;
                 case 2: bosshp=bosshp-(atk*cd);break;
                 case 3: bosshp=bosshp-(atk/cd);break;
                 case 4: bosshp=bosshp-(atk/cd);break;
                 case 5: hp+=aboss+atk;break;
                 default: cout<<"What ability did you use?, hurry you are dying"
                         <<endl;
                 cin>>dmg1;break;
             }
         score-=1;
         rboss-=1;
         hp-=aboss;
         //Stops the loops when someone dies or reinforcements come 
     }while(hp>0 && rboss>0 && bosshp>0); 
     for(int i=1; i<25; i++) //For Visual Seperation of the End Game 
     {
         cout<<"*";
     }
     cout<<endl;
     if (bosshp<=0){ //If Kills the dragon
         cout<<"Congrats You have killed the "<<bosses[1][2]<<endl;
         cout<<"You have gained a Level"<<endl;
         xp=xp+1;
         cont=true;
     }
     if (rboss<=0){ //If Reinforcements came
         cout<<bosses[1][2]<<"Reinforcements have came"<<endl;
         cout<<"Game Over"<<endl;
         score=score/2;
         cont=false;
     }
     if (hp<=0){ //If Player Died 
         cout<<"You have Died"<<endl;
         cout<<"Game Over"<<endl;
         score=score/4;
         cont=false;
     }
     if(cont==true) //continues down the dungeon if dragon was killed
     {
         cout<<"You Returned Home with your Glory"<<endl;
     }
     return cont;
}