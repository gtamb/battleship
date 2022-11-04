// Title: Battleship
// Description: An online version of the Battleship boardgame, wherin two different players can place their ships and then target the other board by entering the x coordinate (0-9) and then the y coordinate (a-j). This will continue until one of the players has had all of their boats sunk. There is a save function wherein after placing the boats either player can save their game and then reload the file later.
// Version 3.0
// Designed by Gillian Tamblyn
// Created on February 11, 2021
// Last Updated on March 05, 2021
// Known Limitations: Only works between two players. Can only enter a number (0-9) for the vertical columns, and for the horizontal rows can only accept a letter (a-j). Directions must be eithe 'h' or 'v' Can only load and save files on school computers that have period1 as their user. Cannot place ships overtop of each other. Game will go on until one of the players has sunk all of the others ships or one of them has saved the game.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

const string EMPTY = "|   |";
const string MISS = "| - |";
const string HIT = "| x |";
const string SHIP = "| o |";
const string SHIP2 = "| o |";
const string SHIP3 = "| o |";

class gameboard {
    
public:
    
    // variable for the amount of ahips that each player had
    int shipsLeft;
    
    // string that will separate the boards by player name
    string playerName;
    
    // the actual board array
    string ocean [10][10];
    
    //constructor - creates an empty board with empty stirng as the player name
    gameboard() {
        shipsLeft = 0;
        playerName = "";
        
        //making each square of the board EMPTY at the beginning
        for (int s = 0; s < 10; s++){
            for(int y = 0; y < 10; y++){
                ocean[y][s] = EMPTY;
            }
            
        }
        
    }
    
    // Sets the player name to their board
    void setPlayerName(string name){
        playerName = name;
    }
    
    // method for printing the board that will be able to be updated as the players take different actions
    void printBoard(bool showShips = true){
        
       //the different options for spaces on the board that go in the top and the sides
        char sideLoc [10] =  {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        char topLoc [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        
        
        // printing the top of the board
        cout << "|||";
        for (int t = 0; t < 10; t++){
            cout << "| "<< topLoc[t] << " |";
        }
        cout << "\n";
        
        // printing the side of the board and its corresponding empty spaces
        for (int s = 0; s < 10; s++){
            cout << sideLoc[s] << " |";
            for(int y = 0; y < 10; y++){
                
                // different spaces with corresponding actions
                // empty water space
                
                if(ocean[y][s] == EMPTY){
                    cout << EMPTY;
                    continue;
                }
                
                // when a player targets and then it is a miss
                if(ocean[y][s] == MISS){
                    cout << MISS;
                    continue;
                }
                
                // when a player hits a ship
                if(ocean[y][s] == HIT){
                    cout << HIT;
                    continue;
                }
                
                // for the second board that is used for targetting it will show all EMPTY squares except for the targetted actions taken
                if(!showShips){
                    cout << EMPTY;
                    continue;
                }
                // steamer (2 squares)
                if(ocean[y][s] == SHIP){
                    cout << SHIP;
                    continue;
                }
                
                // submarine (3 squares)
                else if(ocean[y][s] == SHIP2){
                    cout << SHIP2;
                    continue;
                }
                
                // battleship (4 squares)
                else if(ocean[y][s] == SHIP3){
                    cout << SHIP3;
                    continue;
                }
            } // end of for y
            cout << "\n";
        } // end of for s
        cout << "\n";
        
    } // end of print board
    
    // Save the board to the save game file provided
    void saveGame(std::ofstream& file){
        
        // saving the amount of ships each player has, their name board
        file << shipsLeft;
        file << "\n";
        file << playerName;
        file <<"\n";

        for(int y = 0; y < 10; y++){
            for(int x = 0; x < 10; x++){
                file << ocean[x][y] << "\n";
            }
        }
    } // saveGame
    
    // used for load the game
    void loadGame(std::ifstream& file){
      
        //used for getting all the saved information
        file >> shipsLeft;
        file >> playerName;
        
      // Read past end of line
        string spacer;
        getline(file, spacer);
        
        for(int y = 0; y < 10; y++){
            for(int x = 0; x < 10; x++){
                string fileText;
                getline(file, fileText);
                ocean[x][y] = fileText;
            }
        }
        
    } // saveGame
    
    // Returns 0 to 9 corresponding to a-j or 0-9 characters
    int charToInt(char location){
        
        // forcing the character to be a lowercase
        location = tolower(location);
        
        // if it is any of the following letters
        if(location == 'a' || location == 'b' || location == 'c' || location == 'd' || location == 'e' || location == 'f' || location == 'g' || location == 'h' || location == 'i' || location == 'j'){
            
            // changing the char to an int
            int y = (int)location - (int)'a';
            return y;
            
        }
        
        else if(location == '0' || location == '1' || location == '2' || location == '3' || location == '4' || location == '5' || location == '6' || location == '7' || location == '8' || location == '9'){
            
            // changing the char num to an int
            int x = (int)location - (int)'0';
            return x;
        }
        return -1;
        
    } // end of charToInt

    // to check if the coordinates for placement are in bounds
    bool inBoundsInt(int col, int row ) {
        
        // if the vertical column goes out of bounds
        if(col < 0 || col > 9){
            return false;
        }
        
        // if the horiontal rows goes out of bounds
        else if(row < 0 || row > 9){
            return false;
        }
        
        // if they are both in bounds then will return true
        return true;
    
    }
    
    // method that each boat will go through when placing the boat, called in placeAllShips
    
    void placeShip(int boatLength, int xCol, int yRow, char whichWay){
        
        // for the steamer
        
        if(boatLength == 2){
            
            // sideways locations
            
            if(whichWay == 'h'){
                // changing an empty spot to a SHIP
                ocean[xCol][yRow] = SHIP;
                ocean[xCol + 1][yRow] = SHIP;
                
            }
            
            
            // up and down locations
            
            else if(whichWay == 'v'){
                
                // changing two empty spots to SHIP
                
                ocean[xCol][yRow] = SHIP;
                ocean[xCol][yRow + 1] = SHIP;
                
            }
            
        }// end of boatLength == 2
        
        // for the submarine
        
        else if(boatLength == 3){
            
            // sideways locations
            
            if(whichWay == 'h'){
                // changing 3 empty spots to SHIP2
                
                ocean[xCol][yRow] = SHIP2;
                ocean[xCol + 1][yRow] = SHIP2;
                ocean[xCol + 2][yRow] = SHIP2;
            }
            
            // up and down locations
            
            else if(whichWay == 'v'){
                
                // changing 3 empty spots to SHIP2
                
                ocean[xCol][yRow] = SHIP2;
                ocean[xCol][yRow + 1] = SHIP2;
                ocean[xCol][yRow + 2] = SHIP2;
            }
            
        } // end of boatLength == 3
        
        // for the battleship
        
        else if(boatLength == 4){
            
            // sideways locations
            
            if(whichWay == 'h'){
                
                // changing 4 empty spots to SHIP3
                
                ocean[xCol][yRow] = SHIP3;
                ocean[xCol + 1][yRow] = SHIP3;
                ocean[xCol + 2][yRow] = SHIP3;
                ocean[xCol + 3][yRow] = SHIP3;
                
            }
            
            // up and down locations
            else if(whichWay == 'v'){
                
                // changing 4 empty spots to SHIP3
                ocean[xCol][yRow] = SHIP3;
                ocean[xCol][yRow + 1] = SHIP3;
                ocean[xCol][yRow + 2] = SHIP3;
                ocean[xCol][yRow + 3] = SHIP3;
            }
            
        }// end of boatLength 4
    
    } // end of placeShip
    
    // method to check if when placing that last two ships they do not overlap with another ship
    bool isItEmpty(int numSquares, int numCol, int letRow, char direction){
        
        // for the submarine
        if(numSquares == 3){
            
            if(direction == 'h'){
                
                // checking if each of its 3 spaces spread out horizontally are EMPTY
                if(ocean[numCol][letRow] != EMPTY){
                    return false;
                }
                else if(ocean[numCol + 1][letRow] != EMPTY){
                    return false;
                }
                else if(ocean[numCol + 2][letRow] != EMPTY){
                    return false;
                }
            }
                
            if(direction == 'v'){
                
                // cheking if each of its 3 spaces spread out vertically are crossing any ships
                if(ocean[numCol][letRow] != EMPTY){
                    return false;
                }
                else if(ocean[numCol][letRow + 1] != EMPTY){
                    return false;
                }
                else if(ocean[numCol][letRow + 2] != EMPTY){
                    return false;
                }
            }
            
        }
        
        // the battleship
        if(numSquares == 4){
        
            
            if(direction == 'h'){
                
                // checking if any of its 4 spaces spread out horizontally are crossing any ships
                if(ocean[numCol][letRow] != EMPTY){
                    return false;
                }
                else if(ocean[numCol + 1][letRow] != EMPTY){
                    return false;
                }
                else if(ocean[numCol + 2][letRow] != EMPTY){
                    return false;
                }
                else if(ocean[numCol + 3][letRow] != EMPTY){
                    return false;
                }
            }
                
            if(direction == 'v'){
                
                // checking if any of its 4 squares spread out vertcially are crossing any ships
                if(ocean[numCol][letRow] != EMPTY){
                    return false;
                }
                else if(ocean[numCol][letRow + 1] != EMPTY){
                    return false;
                }
                else if(ocean[numCol][letRow + 2] != EMPTY){
                    return false;
                }
                else if(ocean[numCol][letRow + 3] != EMPTY){
                    return false;
                }
            }
            
        }
        
        // if none of them cross another ship return true
        return true;
        
    }
    
    // for placing all of the ships
    void placeAllShips(){
        
        // valid placements
        int placeColRow [10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        int length [3] = {2, 3, 4}; // length of the 3 ships
        
        // the extra squares besides the first one that each ship takes up
        int shipSquares [3] = {1, 2, 3};
        
        
        while(shipsLeft!= 3){
            char shipLocationY; // what the use will input for the x axis location
            char shipLocationX; // what user will input for the y axis location
            char shipDirection; // whether the ship is going up or to the side
            

            
            // print the board each time it goes through this loop with th eupdated ship locations
            printBoard();
            
            // just telling the player what ship they are placing and how much space it will require
            if(shipsLeft == 0){
                cout << "First up is the steamer which will take up 2 spaces\n";
            }
            else if(shipsLeft == 1){
                cout << "Second up is the submarine which will take up 3 spaces. \n";
            }
            else if(shipsLeft == 2){
                cout << "Last ship is the battleship which will take up 4 spaces. \n";
            }
            
            // asking what direction the user wants their ship to go in
            cout << "Do you want it to be horizontal or vertical facing? (Horizontal = h & Vertical = v) \n";
            cin >> shipDirection;
            
            // if it is not any of the aforementioned valid locations on the y axis, the horizontal rows
            
            // asks them to reinput h or v
            if(shipDirection != 'h' && shipDirection != 'v'){
                cout <<"Sorry that is not a valid orientation for the vessel. Please enter either h for horizontal or v for vertical. \n";
                continue;
            }
            
            
            cout <<" Please enter location of your vessel. (#, l) \n";
            
            // asking for the location on the x axis
            
            cout << "Column Number: ";
            cin >> shipLocationX;
            cout <<"\n";
            
            // switches it to an integer
            int Xlocation = charToInt(shipLocationX);
            
            // whether this is a valid location on the x axis, in th evertical columns
            bool validLocationX;
            
            validLocationX = (Xlocation  == placeColRow[0] || Xlocation  == placeColRow[1] || Xlocation  == placeColRow[2] || Xlocation  == placeColRow[3] || Xlocation  == placeColRow[4] || Xlocation  == placeColRow[5] || Xlocation  == placeColRow[6] || Xlocation  == placeColRow[7] || Xlocation  == placeColRow[8] || Xlocation  == placeColRow[9]);
            
            
            // if the entered x coordinate is not valid ask for a new one

            if(validLocationX == false){
                
                cout << shipLocationX << " is not an accepatble answer for the vertical columns. Please enter a value between 0 - 9. \n";
                
                continue;
                
            }
            
            
            // asking for the location on the y axis
            cout << "Row Letter: ";
            cin >> shipLocationY;
            cout << "\n";
            
            // switches to an int
            int Ylocation = charToInt(shipLocationY);
            
            // whether this is a valid location on the y Axis, in the horizontal rows
            bool validLocationY;
            
            validLocationY = (Ylocation == placeColRow[0] || Ylocation == placeColRow[1] || Ylocation == placeColRow[2] || Ylocation == placeColRow[3] || Ylocation == placeColRow[4] || Ylocation == placeColRow[5]|| Ylocation == placeColRow[6] || Ylocation == placeColRow[7] || Ylocation == placeColRow[8] || Ylocation == placeColRow[9] );
            
            
            // if the y coordinate that they entered is not one of the valid answers asks them for a new one
            if(validLocationY == false){
                
                cout << shipLocationY << " is not and acceptable answer for the horizontal rows. Please enter a value between a - j. \n";
                
                continue;
                
            }
            
            
            // if both y axis and x axis are valid
            
            if(validLocationX && validLocationY){
                
                // checks if ship direction for going horizontal is valid
                
                if(shipDirection == 'h'){
                    
                    // If the end location and the start location are both in bounds...
                    if (inBoundsInt((Xlocation + shipSquares[shipsLeft]), Ylocation ) && inBoundsInt(Xlocation, Ylocation)){
                        
                        // The end location is not empty...
                        if(isItEmpty(length[shipsLeft], Xlocation, Ylocation, shipDirection) == false){
                            cout << "This spot is already occupied by another ship, please choose another placement. \n";
                            
                            continue;
                        }
                        
                        // Put a ship of the given length at the given location and orientation
                        placeShip(length[shipsLeft], Xlocation, Ylocation, shipDirection);
                        
                        // Advance number of ships placed
                        shipsLeft++;
                        
                    }
                    
                    // Don't let any placement be out of bounds
                    else{
                        
                        cout << "Sorry, (" << shipLocationX << ", " << shipLocationY << ") with this direction causes this ship to go out of bounds, please try another placement. \n";
                        
                        continue;
                    }
                }
                // for vertical
                else if(shipDirection == 'v'){
                    
                    // checks if top and bottom of ship are in  inbounds
                    if (inBoundsInt(Xlocation, Ylocation + shipSquares[shipsLeft])  && inBoundsInt(Xlocation, Ylocation)){
                        
                        // checks if the end location and the start location of the ship is not empty...
                        if(isItEmpty(length[shipsLeft], Xlocation, Ylocation, shipDirection) == false){
                            cout << "This spot is already occupied by another ship, please choose another placement. \n";
                            
                            continue;
                        }
                        
                        // places the ships at the given coordinates
                        placeShip(length[shipsLeft], Xlocation, Ylocation, shipDirection);
                        
                        // add a ship with each completed placement
                        shipsLeft++;
                        
                    }
                    // Don't let any placement out of bounds
                    else {
                        
                        cout << "Sorry, ( " << shipLocationX << ", " << shipLocationY << " ) with this direction causes this ship to go out of bounds, please try another placement. \n";
                        
                        continue;
                    }
                    
                } // end of ShipDirection = u
                
            } // end of validLocations
            
        } // end of for shipsLeft
        
        // spacing so other player cant see your work
        for(int g = 0; g < 25; g++){
            cout << endl;
            
        }
    } // end of placeALLships
    
    // returns the string at the given ocean location
    // or ? if out of bounds
    
    string location( int x, int y ){
        if(inBoundsInt(x, y)) {
            
            // if it is occupied by shipType
            return ocean[x][y];
        }
        
        return "?";
    }
            
    
    
    // returns true if there are no more pieces of the ship on the board
    // adjacent to xSide and ySide
    bool shipDestroyed(string shipType, int xSide, int ySide ){
        // checking if the ship still on the board for one spot to the right
        
        // The number of sides we have checked thus far (4 is all of them)
        int f;
        // if right side is still has a piece of the ship..
        for(f = 1; f < 4; f++){
            if(location(xSide + f, ySide) == shipType) {
        
            // this means that the ship is still there so it is not sunk
                return false;
            }
        }
            // if the bottom side is still on the board...
        for(f = 1; f < 4; f++){
            if (location(xSide, ySide + f) == shipType) {
            
                return false;
            }// end of inBounds( xSide +1, ySide)
        }
        // if this side is still on the board
        for(f = 1; f < 4; f++){
            if(location(xSide - 1, ySide) == shipType){
                            
            return false;
            
            } // end of if inBounds(xSide - 1, ySide)
        }
        for(f = 1; f < 4; f++){
            if(location(xSide, ySide - 1) == shipType){
            
                return false;
            } // end of inBounds(xSide, ySide - 1)
        }
        return true;
    } // end of shipDestroyed
        
    // function called when targetting ships, checks if they already targeted that place and whether or not they hit or missed a vessel
    
    // returns true if player targetted ships, returns false if player wants to save and end game
    bool targetShips(){
        
        char enteredRow;
        char enteredColumn;
        bool validRow = false;
        bool validColumn = false;
        char targetRow [10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
        char targetColumn [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        
       
        
        // printing an empty board that only displays the actions taken against the enemy
        printBoard(false);
        
        // checks if the targetting selection has been made
        bool selectionMade = false;
        
        while(!selectionMade) {
        
            // target from the x axis
            cout << "Enter the column you want to target 0 - 9 or s to save and exit game.\n";
            cin >> enteredColumn;

            // if they saved the game it will exit this method and go to main where it will save the game
            if(enteredColumn == 's'){
                return false;
            }
            
            // identifying when the entered column matches the possible target
            validColumn = (enteredColumn == targetColumn[0] || enteredColumn == targetColumn[1] || enteredColumn == targetColumn[2] || enteredColumn == targetColumn[3] || enteredColumn == targetColumn[4] || enteredColumn == targetColumn[5] || enteredColumn == targetColumn[6] || enteredColumn == targetColumn[7] || enteredColumn == targetColumn[8] || enteredColumn == targetColumn[9]);
            
            // if not 0-9
            if(!validColumn){
                
                cout << "That is an invalid answer. Please enter a number from 0 to 9 or s to save and exit game.\n";
                continue;
            }
                    
            // target from the y axis
            cout << "Enter the row of the target. (abc etc) \n";
            cin >> enteredRow;
            
            // identifying when the entered row matches with a possible target
            validRow = (enteredRow == targetRow[0] || enteredRow == targetRow[1]  || enteredRow == targetRow[2]  || enteredRow == targetRow[3] || enteredRow == targetRow[4] || enteredRow == targetRow[5]  || enteredRow == targetRow[6] ||  enteredRow == targetRow[7] || enteredRow == targetRow[8] || enteredRow == targetRow[9]);
            
            // if they did not enter a - j
            if(!validRow){
                
                cout << "That is an invalid answer. Please enter a letter from a to j. \n ";
                continue;
            }
            
            // changes the coordinates from a char to an int
            int tarRow = charToInt(enteredRow);
            int tarCol = charToInt(enteredColumn);
            
            // if this spot hasalready been targetted
            if(ocean[tarCol][tarRow] == MISS || ocean[tarCol][tarRow] == HIT ){
                cout << "You have already targetted this location, please enter another target. \n";
                continue;
            }
            
            // if this target is valid
            if(validRow == true && validColumn == true ){
                
                // check what it hit and then add on to the board the various corrsponding characters
                
                // if the square that they hit was empty then they missed
                if(ocean[tarCol][tarRow] == EMPTY){
                    
                    // change the suare to display a miss
                    ocean[tarCol][tarRow] = MISS;
                    
                    // reprint the action board with the actions taken
                    printBoard(false);
                    
                    sleep(2);//sleeps for 2 second
                    return true;
                }
                // See what got hit if anything
                string target = location(tarCol, tarRow);
                
                // if they hit the ship
                if(target == SHIP  || target == SHIP2 || target == SHIP3 ){
                
                    // change the square to a hit
                    ocean[tarCol][tarRow] = HIT;
                    
                    // if there are none parts of the ship left...
                    if(shipDestroyed(target, tarCol, tarRow)){
                        
                        // takes away a ship from the total amount.
                        shipsLeft--;
                    }
                    
                    // reprint the action board with the actions taken
                    printBoard(false);
                    
                    sleep(2);//sleeps for 2 second
                    return true;
                }
                
            } // end of if both row and col are valid
            
        } // end of while
            
        return true;
    }// end of targetShips
    
}; // end of gameboard


int main() {
    char startGame = 'y'; // variable that user will use to start the game
    string playerOne;
    string playerTwo;
    string enteredFileName;
    char whichGame = 'n';
    char acceptTurn = 'y';
    
    cout <<" ____    ____  ______  ______   _        ___    _____ __ __  ____  ____\n";
    cout <<"|    \\  /    ||      ||      | | |      /  _]  / ___/|  | |  |  | |    \\ \n";
    cout <<"|  o  )|  o  ||      ||      | | |     /  [_  (  \\_  |  |  | |  | |  o  ) \n";
    cout <<"|     ||     ||_|  |_||_|  |_| | |___ |    _] \\__  | |  _  | |  | |   _/ \n";
    cout <<"|  O  ||  _  |  |  |    |  |   |     ||   [_  /  \\ | |  |  | |  | |  |  \n";
    cout <<"|     ||  |  |  |  |    |  |   |     ||     | \\    | |  |  | |  | |  |   \n";
    cout <<"|_____||__|__|  |__|    |__|   |_____||_____|  \\___| |__|__||____||__| \n";
    
    cout << "Welcome To BATTLESHIP! An online battleship game with the goal of destroying you opponents ships while they try to sink your own. \n";
    cout <<"Everyone will have 3 different ships, a steamer which traverses 2 squares, a submarine which is 3 squares long, and a battleship which is 4 squares long. \n";
    cout <<" Player 1 will start by placing their ships one at a time by first entering the vertical column (a Number) then entering the horizontal row (a Letter). They will have a final chance to confirm all of their placements then they will pass the screen over to their opponent who will repeat the process. \n \n";
    cout <<"From there on they will commit a similar process of choosing target (# , a ) until one of them looses all of their vessels. \n ";
    cout << "for each different space there is a different symbol that represents the action taken: \n\n |   | = an empty water space or an unkknown space based on if it is the players board or a map of their actions \n | o | = the current players ship occupies that space, \n | - | = there was a miss in this location, \n | x | = a ship has been hit. \n\n";
    
    cout <<"New game (n) or load from save (l)?  \n";
    cin >> whichGame;
    
    cout << "Are you ready to start?(y/n) \n";
    
    cin >> startGame; // user input y or n if they want to start the game
    
    while(startGame == 'y' || startGame == 'Y'){
        
        // creating to different boards
        gameboard boards[2] = {gameboard(), gameboard()} ;

        
        if(whichGame == 'n' || whichGame == 'N'){
            
            // assigning player one board 0
            cout <<"Enter player one's name. \n";
            cin >> playerOne;
        
            // assigning player two board 1
            cout << "Enter player two's name. \n";
            cin >> playerTwo;
            
            boards[0].setPlayerName(playerOne);
            boards[1].setPlayerName(playerTwo);
            
            cout << playerOne << "'s board\n";
            
            //Player One places their ships
            boards[0].placeAllShips();
            
            // extra spacing
            for(int g = 0; g < 45; g++){
                cout << endl;
                
            }

            cout << "Pass the computer over to " << playerTwo << "\n";
            
            // player two place their ships
            boards[1].placeAllShips();
            
        }
    
        else if(whichGame == 'l' || whichGame == 'L'){
           // Create empty game boards
            bool fileOk = false;
            
            // ask which file is wanted
            while(!fileOk){
                cout << "What is the name of the saved file? \n";
                cin >> enteredFileName;
            
            // finds it in a specific directory
                enteredFileName = "/Users/gillian/" + enteredFileName;
                
                ifstream saveFile(enteredFileName);
            
                fileOk = saveFile.is_open();
                
                // check of file is fine then it will open
                if(fileOk){
                    boards[0].loadGame(saveFile);
                    boards[1].loadGame(saveFile);
                    
                }
                
                // if the file could not be opened
                else{
                    cout << "ERROR \n";
                    cout << "Could not open file " << enteredFileName << " please try again. \n";
                    continue;
                }
            }
       }
    
        int currentPlayer = 0;
        int otherPlayer = 1;
        int turnCounter = 1;  // start at first turn
        
            // While both boards have ships left...
        while(boards[0].shipsLeft > 0 || boards[1].shipsLeft > 0){
            
            for(int g = 0; g < 45; g++){
                cout << endl;
                
            }
            
            
            // Show current turn
            cout << "Turn: " << turnCounter << "\n";
            
            // If this is the second player, increment for next time
            if (currentPlayer == 1)
                turnCounter++;
            
            // waits for acceptance to open the board
            cout << "Ready Player: \n" << boards[currentPlayer].playerName << "\n\n";
            cout << boards[currentPlayer].playerName << " press y to accept your turn. \n";
            cin >> acceptTurn;
            
            if(acceptTurn == 'y'){
                // how many ships you and the other player have
                cout << "Enemy has " << boards[otherPlayer].shipsLeft << " ships left.\n";
                cout << "You have " << boards[currentPlayer].shipsLeft << " ships left. \n";
            
                // Show the current player's board (with ships visible)
                boards[currentPlayer].printBoard();
            
            // Show the other player's board (with ships hidden) and accept targets
                bool continueGame = boards[otherPlayer].targetShips();
            
            // If the player chose to stop game and save...
                if(!continueGame){
                    cout << "Enter the name of the file you would like to save the game in. \n";
                    cin >> enteredFileName;
                    
                    // Force to temp directory so it doesn't matter where the program is run from
                    enteredFileName = "/Users/gillian/" + enteredFileName;
                
                    ofstream saveFile(enteredFileName);
                    
                    // save both of the boards
                    if(saveFile.is_open()){
                        boards[0].saveGame(saveFile);
                        
                        boards[1].saveGame(saveFile);
                        
                        saveFile.close();
                        
                        cout << "Saved game to: " << enteredFileName;
                    }
                    // if they can not save it
                    else{
                        cout << "ERROR \n";
                    }
                    return 0; // exit the program
                }
                
            // Check to see if the game is over...
                if(boards[otherPlayer].shipsLeft == 0){
                    break;
                }
            
            // Swap the current other other player
                int x = currentPlayer;
                currentPlayer = otherPlayer;
                otherPlayer = x;
                
            }

        } // end of while
        
        // when someone has won the game
        cout << boards[currentPlayer].playerName << " has won the Game! \n";
        
        cout << "Would you like to play again? (y/n) \n";
        
        cin >> startGame;
        
        if(startGame == 'y' || startGame == 'Y'){
            
            // resetting both boards to have all EMPTY spaces and making shipsLeft 0 again
            for(int s = 0; s < 10; s++){
                
                for(int r = 0; r < 10; r++){
                    
                    boards[0].shipsLeft = 0;
                    
                    boards[0].ocean[s][r] = EMPTY;
                    
                    boards[1].shipsLeft = 0;
                    
                    boards[1].ocean[s][r] = EMPTY;
                }
            }
            
            // restarting the game
            
            continue;
        } // end of startgame
        
        else{
            cout <<" Thanks for playing! \n";
        }
    }// end of while loop
    
    return 0;
};
