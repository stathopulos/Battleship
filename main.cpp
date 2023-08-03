#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

//#4 Variables
string username;
const string filename = "records.csv";

const int GRID_SIZE = 10;
const int NUM_SHIPS = 5;

//Clears the console
void Clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

//#5 arrays
char gridPlayer[GRID_SIZE][GRID_SIZE]; //Grid to track player's ships and moves
char gridCPU[GRID_SIZE][GRID_SIZE];    //Grid to track CPU's ships and moves

//Initialize both player and CPU grids with '-'
void initializeGrids()
{
    //#7 iteration
    for (int i = 0; i < GRID_SIZE; i++)
    {
        //#7 iteration
        for (int j = 0; j < GRID_SIZE; j++)
        {
            //#5 Arrays
            gridPlayer[i][j] = '-';
            gridCPU[i][j] = '-';
        }
    }
}

void printGrids()
//This function prints the grids so #3 Output, also uses arrays #5 and loops #7
{
    //#3 Output
    cout << "   ";
    //#7 Iteration #3 Output
    for (int i = 0; i < GRID_SIZE; i++)
    {
        cout << static_cast<char>('a' + i) << " ";
    }
    cout << "       ";
    //#7 Iteration #3 Output
    for (int i = 0; i < GRID_SIZE; i++)
    {
        cout << static_cast<char>('a' + i) << " ";
    }
    cout << endl;

    //#7 Iteration #3 Output
    for (int i = 0; i < GRID_SIZE; i++)
    {
        cout << " " << i << " ";
        for (int j = 0; j < GRID_SIZE; j++)
        {
            //#5 Arrays
            cout << gridPlayer[i][j] << " ";
        }

        cout << "     " << i << " ";
        //#7 Iteration #3 Output
        for (int j = 0; j < GRID_SIZE; j++)
        {
            //#5 Arrays #3 Output
            if (gridCPU[i][j] == 'S') { //Hides CPU ships from player
                cout << '-' << " ";
            }
            else{
                cout << gridCPU[i][j] << " ";
            }
        }

        cout << endl;
    }
}

//Check if the move (x, y) is within the grid boundaries
bool isValidMove(int x, int y)
{
    //#9 Control
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

//Check if the cell is within the grid boundaries and contains '-'
bool isCellEmpty(char grid[GRID_SIZE][GRID_SIZE], int x, int y)
{
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] == '-');
}

//Helper function for placeShips()
bool canPlaceShip(char grid[GRID_SIZE][GRID_SIZE], int x, int y, int length, bool horizontal)
{
    //#9 Control
    if (horizontal)
    {
        //#9 Control, #7 iteration, #4 variables, #5 arrays
        for (int i = 0; i < length; i++)
        {
            //Check if any adjacent cell contains 'S'
            if (!isCellEmpty(grid, x, y + i) || !isCellEmpty(grid, x + 1, y + i) || !isCellEmpty(grid, x - 1, y + i) ||
                !isCellEmpty(grid, x, y + i + 1) || !isCellEmpty(grid, x, y + i - 1))
            {
                return false;
            }
        }
    }
    else
    {
        //#9 Control, #7 iteration, #4 variables, #5 arrays
        for (int i = 0; i < length; i++)
        {
            //Check if any adjacent cell contains 'S'
            if (!isCellEmpty(grid, x + i, y) || !isCellEmpty(grid, x + i, y + 1) || !isCellEmpty(grid, x + i, y - 1) ||
                !isCellEmpty(grid, x + i + 1, y) || !isCellEmpty(grid, x + i - 1, y))
            {
                return false;
            }
        }
    }

    return true;
}

//Places ships on the grids so they don't touch or overlap. 5 ships of lengths 5,4,3,3, and 2.
void placeShips()
{
    srand(time(NULL));

    //#4 Variables
    int playerShipsPlaced = 0;
    int cpuShipsPlaced = 0;

    //##7 iteration
    while (playerShipsPlaced < NUM_SHIPS)
    {
        //#9 Control, #4 variables
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        bool horizontal = rand() % 2 == 0; //Randomly choose horizontal or vertical placement

        //#4 Variables
        int shipLength = 0;

        //#9 Control
        switch (playerShipsPlaced)
        {
            case 0:
                shipLength = 5;
                break;
            case 1:
                shipLength = 4;
                break;
            case 2:
            case 3:
                shipLength = 3;
                break;
            case 4:
                shipLength = 2;
                break;
            default:
                break;
        }

        //#9 Control, #4 variables, #5 arrays
        if (canPlaceShip(gridPlayer, x, y, shipLength, horizontal))
        {
            //Place the ship
            if (horizontal)
            {
                //#7 iteration, #4 variables, #5 arrays
                for (int i = 0; i < shipLength; i++)
                {
                    gridPlayer[x][y + i] = 'S';
                }
            }
            else
            {
                //#7 iteration, #4 variables, #5 arrays
                for (int i = 0; i < shipLength; i++)
                {
                    gridPlayer[x + i][y] = 'S';
                }
            }
            //#4 Variables
            playerShipsPlaced++;
        }
    }

    //#7 iteration
    while (cpuShipsPlaced < NUM_SHIPS)
    {
        //#4 variables
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        bool horizontal = rand() % 2 == 0;

        int shipLength = 0;

        //#9 Control
        switch (cpuShipsPlaced)
        {
            case 0:
                shipLength = 5;
                break;
            case 1:
                shipLength = 4;
                break;
            case 2:
            case 3:
                shipLength = 3;
                break;
            case 4:
                shipLength = 2;
                break;
            default:
                break;
        }

        //#9 Control
        if (canPlaceShip(gridCPU, x, y, shipLength, horizontal))
        {
            if (horizontal)
            {
                //#7 Iteration
                for (int i = 0; i < shipLength; i++)
                {
                    //#5 Arrays
                    gridCPU[x][y + i] = 'S';
                }
            }
            else
            {
                //#7 Iteration
                for (int i = 0; i < shipLength; i++)
                {
                    //#5 Arrays
                    gridCPU[x + i][y] = 'S';
                }
            }
            cpuShipsPlaced++;
        }
    }
}

//Check if any ships remain on the provided grid
bool hasRemainingShips(char grid[GRID_SIZE][GRID_SIZE])
//#7 Iteration, #5 Arrays
{
    //Check if the grid has any remaining ships
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == 'S')
            {
                return true; //If there is still at least one ship remaining, return true
            }
        }
    }
    return false; //All ships have been sunk, return false
}

//Return true if either player has no ships remaining
bool isGameOver()
//#9 Control, #4 Variables
{
    //Check if either player's grid has any remaining ships
    bool playerHasShips = hasRemainingShips(gridPlayer);
    bool cpuHasShips = hasRemainingShips(gridCPU);

    return !(playerHasShips && cpuHasShips); //Game over if either player has no ships remaining
}

void playerMove()
//#3 I/O, #4 variables, #5 arrays, #8 Interaction, #9 control
{
    //#4 Variables
    string input;
    int x, y;

    //#3 I/O #8 Interaction
    cout << "Enter your move (e.g., f7): ";
    cin >> input; //#3 Input

    y = input[0] - 'a'; //Convert the letter coordinate to corresponding numeric index
    x = input[1] - '1' + 1; //Convert the numeric coordinate to corresponding numeric index

    //#9 Control, #3 I/O
    if (!isValidMove(x, y))
    {
        cout << "Invalid move. Try again.\n";
        playerMove(); //If the move is invalid, ask for input again
        return;
    }

    //#5 Arrays, #9 Control
    if (gridCPU[x][y] == 'S')
    {
        //#5 Arrays
        gridCPU[x][y] = 'X'; //The player hit the CPU's ship
        //#3 Output
        Clear();
        cout << "You hit the CPU's ship!\n";
    }
    else if (gridCPU[x][y] == '-')
    {
        //#5 Arrays
        gridCPU[x][y] = 'O'; //The player missed
        //#3 Output
        Clear();
        cout << "You missed!\n";
    }
    else
    {
        //#3 Output
        cout << "You already made that move. Try again.\n";
        playerMove(); //If the move was already made, ask for input again
    }
}

void CPUMove()
//#9 control, #5 arrays, #4 variables, #7 iteration, #3 output
{
    //#4 Variables
    int x, y;

    //#9 Control, #7 Iteration
    do
    {
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
    } while (!isValidMove(x, y) || gridPlayer[x][y] != '-' && gridPlayer[x][y] != 'S');

    //#9 Control, #5 Arrays, #3 Output
    if (gridPlayer[x][y] == 'S')
    {
        gridPlayer[x][y] = 'X'; //The CPU hit the player's ship
        cout << "The CPU hit your ship at " << static_cast<char>('a' + y) << (x) << "!\n";
    }
    else
    {
        gridPlayer[x][y] = 'O'; //The CPU missed
        cout << "The CPU missed at " << static_cast<char>('a' + y) << (x) << "!\n";
    }
}

//record struct for the format of my file
struct Record {
    //#4 Variables
    string username;
    int wins;
    int losses;
};

//Creates file with header Username,Wins,Losses
void createRecordFile(const string& filename) {
    //#6 File I/O, #4 Variable
    ofstream file(filename);
    //#9 Control, #6 File I/O
    if (file) {
        file << "Username,Wins,Losses" << endl;
        cout << "Record file created: " << filename << endl;
    } else {
        cout << "Error: Unable to create the record file." << endl;
    }
}

//Keeps and sorts win/loss record in the format username,win,loss on each line.
Record updateRecord(const string& username, bool isVictory) {
    //#6 File I/O, #4 Variables
    ifstream file(filename);

    //#4 Variables
    bool found = false;
    string line;
    vector<Record> records;

    //#9 Control, #6 File I/O
    if (!file) {
        cout << "Record file not found. Creating a new record file..." << endl;
        file.close();
        createRecordFile(filename);
    }

    //Skip the header line
    getline(file, line);

    //#7 Iteration, #6 File I/O
    while (getline(file, line)) {
        //#4 Variables
        Record record;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        //#9 Control, #4 Variables
        if (pos1 != string::npos && pos2 != string::npos) {
            record.username = line.substr(0, pos1);
            record.wins = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            record.losses = stoi(line.substr(pos2 + 1));

            //#9 Control
            if (record.username == username) {
                found = true;
                if (isVictory) {
                    record.wins++;
                } else {
                    record.losses++;
                }
            }

            records.push_back(record);
        }
    }

    //#9 Control
    if (!found) {
        //If the username is not already in the file, add it to the records
        records.push_back({username, (isVictory ? 1 : 0), (isVictory ? 0 : 1)});
    }

    file.close();

    //Write the records back to the file
    //#6 File I/O
    ofstream tempFile("temp.csv");
    tempFile << "Username,Wins,Losses" << endl;
    //#7 Iteration, #6 File I/O
    for (const auto& record : records) {
        tempFile << record.username << ',' << record.wins << ',' << record.losses << '\n';
    }
    tempFile.close();

    //Rename the temporary file to the original filename
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());

    //Return the player's win loss record.
    //#7 Iteration, #9 Control, #3 Output
    for (const auto& record : records) {
        if (record.username == username) {
            return record;
        }
    }

    return Record{"",0,0};
}


int main()
{
    Clear();
    //Take username input
    while (true)
    {
        //#3 I/O
        cout << "What's your name?: ";
        getline(cin, username);
        //Remove commas from username for later use in CSV file
        username.erase(remove(username.begin(), username.end(), ','), username.end());
        //Make username lowercase
        transform(username.begin(), username.end(), username.begin(), ::tolower);
        if (!username.empty()) {
            cout << "Hello " << username << "!" << endl << endl;
            break; //Exit the loop if the input is not empty
        } else {
            cout << "Username is empty or all commas. Please try again." << endl;
        }
    }

    //#3 I/O
    cout << "Press enter to play: ";
    cin.ignore();
    Clear();

    initializeGrids();
    placeShips();

    //#3 Output
    cout << "*** BATTLESHIP ***\n";
    cout << "Let's play!\n";

    //#7 Iteration
    while (!isGameOver())
    {
        printGrids();

        playerMove();

        //#9 Control, #3 output
        if (isGameOver())
        {
            cout << "\nYou sunk all the CPU's ships!\n";
            Record updatedRecord = updateRecord(username, true);
            cout << "Congratulations " << updatedRecord.username << "! You've won " << updatedRecord.wins << " times and lost " << updatedRecord.losses << " times!" << endl;
            cout << "Thank you for playing! Goodbye!" << endl;
            break;
        }

        CPUMove();

        //#9 Control, #3 output
        if (isGameOver())
        {
            cout << "\nOh no! The CPU sunk all your ships!\n";
            Record updatedRecord = updateRecord(username, true);
            cout << "Better luck next time " << updatedRecord.username << "! You've won " << updatedRecord.wins << " times and lost " << updatedRecord.losses << " times!" << endl;
            cout << "Thank you for playing! Goodbye!" << endl;
            break;
        }
    }

    return 0;
}