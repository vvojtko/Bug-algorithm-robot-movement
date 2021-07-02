/* Simple skeleton test program for in-robot API */
#include "allcode_api.h"    // MUST include this to define robot functions
#define n 3

struct obstacle {
   int run;
   int obstacleDistance;
   /* declare as many members as desired, but the entire structure size must be known to the compiler. */
};



void forwards(){
    FA_SetDriveSpeed (10);
    FA_Forwards(50);
}

void backwards() {
    FA_SetDriveSpeed(10);
    FA_Backwards(50);
}


void wallCalibration() {
    if (FA_ReadIR(1) > 1600) {
        backwards();
        FA_Right(4);
        forwards();
    } //kalibracja do sciany
    if (FA_ReadIR(3) > 1600) {
        backwards();
        FA_Left(4);
        forwards();
    }
}
void playSong(){
    FA_PlayNote(370,250);
    FA_PlayNote(440,250);
    FA_PlayNote(467,250);
    FA_PlayNote(467,250);
    FA_PlayNote(467,250);
    FA_PlayNote(440,250);
    FA_PlayNote(370,250);
    FA_PlayNote(370,250);
    FA_PlayNote(370,250);
    FA_PlayNote(440,250);
    FA_PlayNote(467,250);
    FA_PlayNote(467,250);
    FA_PlayNote(467,250);
    FA_PlayNote(440,250);
    FA_PlayNote(370,250);
    FA_PlayNote(330,750);
    FA_PlayNote(290,750);
}
int main()
{
    FA_RobotInit();         // MUST call this before any other robot functions
    int travelledDistance;      //travelledDistance is variable for keeping all the distance information
    struct obstacle obstacles[n]; //list of structs - not in used (further improvmenets)
    int firstObstacle;   //variable for storing data about first obstacle
    int secondObstacle;     //variable for storing data about second obstacle
    int thirdObstacle;      //variable for storing data about third obstacle
    int obstacleNumber = 0; //variable for storing data about how many obstacles the robot encounters
    FA_LCDBacklight(50);    // Switch on backlight (half brightness)
    FA_DelayMillis(1000);   // Pause 1 sec
    int mline = 110;        //variable that indicates the distance of mline
    int mline_moves = mline/5;  //variable for counting how many moves equals mline
    int actual_moves = 0;       //variable for improvements and debugging - not used
    int north = 0;      //direction variable
    float moves = 0; //variable for improvements and debugging - not used
    int west = 0;   //direction variable
    int east = 1;   //direction variable
    int south = 0;  //direction variable
    int north2 = 0; //direction variable for norht but only when obstacle avoidance is taking place
    while(north!=mline_moves) {     //when robots makes as many north moves as the mline/5 value is
        
        
        
        
        if(FA_ReadIR(2) < 300) {        //go straight ahead if nothing in the front
        forwards();
        north = north+1;
        FA_LCDNumber(north, 40, 0, FONT_NORMAL, LCD_OPAQUE);
        
        }
        
        if(FA_ReadIR(2) > 300){ //reaches obstacle
            
            //obstace avoidance 
            
            //variables alignment for data displaying and directions updating
            
            FA_LCDClear();
            int modDirections = 0;
            int directions = 64;
            west = 0;
            east = 1;
            south = 0;
            moves = 0;
            north2 = 0;

            FA_Right(90);
            directions = directions -1;
            modDirections = directions%4;
            /*
             * while loop that keeps going until the robot will find itself again on the m-line.
             * works thanks to directions (north, south, west, east)
             * if the robot finds the obstacle it turns right and follow the wall
             * it counts how many moves it did in east direction
             * when reaches to the corner it turns left
             * it counts how many moves it did in west direction
             * if number of west moves equals east moves it means it reached the m-line (starting line)
             */
            obstacleNumber = obstacleNumber + 1;
            while(east != west-1) {
                
            
            modDirections = directions%4;
           
          
                 
                
            
                if(FA_ReadIR(0) < 50) { //if there is no wall on left anymore it means the robot reached corner - then turns left
                    
                    //calibartion nodge out of wall
                    if(FA_ReadIR(1) > 1600) {         //wall calibrating
                            backwards();
                            FA_Right(4);
                            forwards();
                    }

                    if(FA_ReadIR(3) > 1600) {         //wall calibrating
                            backwards();
                            FA_Left(4);
                            forwards();
                    }
                        
                    if(FA_ReadIR(2) < 300){
                    forwards();
                    moves = moves+1;
                    
                    
                    //updating the current direction
                    
                    if (modDirections == 0){ 
                       FA_LCDPrint("north", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE);
                       north = north+1;
                       north2=north2+1;
                    } 
                    else if (modDirections == 1){
                        FA_LCDPrint("west", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        west = west+1;
                    } 
                    else if (modDirections == 2){
                        FA_LCDPrint("south", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        north = north-1;
                        south = south+1;
                    } 
                    else if (modDirections == 3){
                        FA_LCDPrint("east", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        east = east+1;
                    } 
                    
                    }
                    
                    FA_Left(90);
                    directions = directions + 1;
                    modDirections = directions%4;
                    
                    while(FA_ReadIR(1) > 1000) { //if still very close wall then calibrates
                        FA_Right(90);
                        forwards();
                        moves = moves+1;
                        
                        
                    //updating the current direction    
                    if (modDirections == 0){ 
                       FA_LCDPrint("north", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE);
                       north = north+1;
                       north2=north2+1;
                    } 
                    else if (modDirections == 1){
                        FA_LCDPrint("west", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        west = west+1;
                    } 
                    else if (modDirections == 2){
                        FA_LCDPrint("south", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        north = north-1;
                        south = south+1;
                    } 
                    else if (modDirections == 3){
                        FA_LCDPrint("east", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        east = east+1;
                    } 
                        //moves = moves+1;
                        FA_Left(90);
                        //north = north+1;
                    }
                   
                    
                    //updating the current direction
                    if (modDirections == 0){ 
                       FA_LCDPrint("north", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE);
                       north = north+1;
                       north2=north2+1;
                    } 
                    else if (modDirections == 1){
                        FA_LCDPrint("west", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        west = west+1;
                    } 
                    else if (modDirections == 2){
                        FA_LCDPrint("south", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        north = north-1;
                        south = south+1;
                    } 
                    else if (modDirections == 3){
                        FA_LCDPrint("east", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                        east = east+1;
                    } 
                       FA_LCDNumber(east, 0, 0, FONT_NORMAL, LCD_OPAQUE);
                       FA_LCDNumber(west, 40, 0, FONT_NORMAL, LCD_OPAQUE); 
                }
                
                
                //until there's no wall on left and no on left and no on right
                //very important wall following function
                //when robot reaches corner and calibrates, so moves too far from obstacle
                //the while loop makes sure it will go along the wall even though it's far
                //as it's know there's a wall because there's no other wall in the front or right
                while(FA_ReadIR(0) < 50 && FA_ReadIR(2) < 200 && FA_ReadIR(4) < 300) {
                    forwards(); 
                    moves = moves+1;
                    
                    if(FA_ReadIR(1) > 1600) {         //wall calibrating
                    backwards();
                    FA_Right(4);
                    forwards();

                    }

                    if(FA_ReadIR(3) > 1600) {         //wall calibrating
                    backwards();
                    FA_Left(4);
                    forwards();
                    }    
                    
                    //updating the current direction
                    if (modDirections == 0){ 
                         FA_LCDPrint("north", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE);
                         north = north+1;
                         north2=north2+1;
                      } 
                      else if (modDirections == 1){
                          FA_LCDPrint("west", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                          west = west+1;
                      } 
                      else if (modDirections == 2){
                          FA_LCDPrint("south", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                          north = north-1;
                          south = south+1;
                      } 
                      else if (modDirections == 3){
                          FA_LCDPrint("east", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                          east = east+1;
                      } 
                    
                    forwards(); 
                    moves = moves+1;
                    //updating the current direction
                         if (modDirections == 0){ 
                         FA_LCDPrint("north", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE);
                         north = north+1;
                         north2=north2+1;
                      } 
                      else if (modDirections == 1){
                          FA_LCDPrint("west", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                          west = west+1;
                      } 
                      else if (modDirections == 2){
                          FA_LCDPrint("south", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                          north = north-1;
                          south = south+1;
                      } 
                      else if (modDirections == 3){
                          FA_LCDPrint("east", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                          east = east+1;
                      } 
                    FA_LCDNumber(east, 0, 0, FONT_NORMAL, LCD_OPAQUE);
                    FA_LCDNumber(west, 40, 0, FONT_NORMAL, LCD_OPAQUE); 
                }
            
                 
                /* if robot sensors obstacle in front and on the left - then it turns right
                  
                 */
                if(FA_ReadIR(2) > 100 && FA_ReadIR(0) > 100) {
                    
                    if(FA_ReadIR(1) > 1600) {         //kalibrowanie do scainy od left front
                        backwards();
                        FA_Right(4);
                        forwards();
                    }

                     if(FA_ReadIR(3) > 1600) {         //kalibrowanie do scainy od right front
                        backwards();
                        FA_Left(4);
                        forwards();
                    }
                    
                    FA_Right(90);
                    directions = directions - 1;
                    modDirections = directions%4;
                    //updating the current direction
                    if (modDirections == 0){
                       FA_LCDPrint("north", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                    } 
                    else if (modDirections == 1){
                        FA_LCDPrint("west", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                    } 
                    else if (modDirections == 2){
                        FA_LCDPrint("south", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                    } 
                    else if (modDirections == 3){
                        FA_LCDPrint("east", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                    } 
                    FA_LCDNumber(east, 0, 0, FONT_NORMAL, LCD_OPAQUE);
                    FA_LCDNumber(west, 40, 0, FONT_NORMAL, LCD_OPAQUE); 
                }
    
            
              if(FA_ReadIR(0) > 50 && FA_ReadIR(2) < 50) {        //if wall is on left and is not in front then move forward along the left wall
            
                    FA_LCDClear();
                    
                    wallCalibration();
                   
                    
                if (modDirections == 0){ 
                   FA_LCDPrint("north", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE);

                   north = north+1;
                   north2=north2+1;
                } 
                else if (modDirections == 1){
                    FA_LCDPrint("west", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                    west = west+1;
                } 
                else if (modDirections == 2){
                    FA_LCDPrint("south", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                    north = north-1;
                    south = south+1;
                } 
                else if (modDirections == 3){
                    FA_LCDPrint("east", 5, 20, 25, FONT_NORMAL, LCD_OPAQUE); 
                    east = east+1;
                } 
                    FA_LCDNumber(east, 0, 0, FONT_NORMAL, LCD_OPAQUE);
                    FA_LCDNumber(west, 40, 0, FONT_NORMAL, LCD_OPAQUE); 
                    forwards();
                    moves = moves+1;
                
                }
    }
            
            
          
            /*
             *
             *  finish of obstacle
             *
             */
            
            
            //obstacles data updating
            int x = obstacleNumber;
            if(x == 0) {
                firstObstacle = 0;
                secondObstacle = 0;
            }
            else if(x == 1){
                firstObstacle = (south+west+north2+east-1);
            }else if(x == 2){
                secondObstacle = south+west+north2+east-1; 
            }
            else if(x == 3){
                thirdObstacle = south+west+north2+east-1;
            } 
            
   
        
        while(modDirections != 0){
        FA_Right(90);
        directions = directions - 1;
        modDirections = directions%4;
        }
            //travelled distance variable updating
            travelledDistance = travelledDistance + (east + west - 1);
          
       }
        
        
        
    }
    
    
    travelledDistance = (travelledDistance+mline_moves)*5; //multiplying by 5 to calculate the distance in cm - not in 'moves'
    
    FA_SetMotors(0, 0);
    FA_LCDClear();
    
    FA_LCDPrint("Travelled: ", 11, 0, 0, FONT_NORMAL, LCD_OPAQUE);   
    FA_LCDNumber(travelledDistance, 80, 0, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDPrint("M-Line: ", 8, 0,8, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDNumber(mline, 80, 8, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDPrint("Obstacle 1: ", 12, 0, 16, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDNumber(firstObstacle*5, 80, 16, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDPrint("Obstacle 2: ", 12, 0, 24, FONT_NORMAL, LCD_OPAQUE);
    FA_LCDNumber(secondObstacle*5, 80, 24, FONT_NORMAL, LCD_OPAQUE);
    //FA_LCDNumber(actual_moves, 0, 0, FONT_NORMAL, LCD_OPAQUE);
    FA_DelayMillis(10000);
    FA_SetMotors(0, 0);
    FA_DelayMillis(2000);

   
    //plays the final song
    playSong();
    
    return 0; // Actually, we should never get here...
}
