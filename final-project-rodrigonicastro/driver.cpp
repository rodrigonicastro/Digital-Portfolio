/*
This file contains the main
function and the implementation
of the full program
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"
#include "ActorGraph.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
bool readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]){
    //Checks if a valid number of arguments was passed to the program
    if(argc != 4) cout << "Invalid number of arguments \nUsage: ./<program_name> <file.csv> <hashTable_size> <skipList_size>" << endl;

    else{
        //Declares the tableSize and SkipListSize with the arguments passed by the user
        int hashTableSize = stoi(argv[2]);
        int SkipListCapacity = stoi(argv[3]);

        //Declares and initializes the data struture classes to be used
        MovieHashTable hashTable(hashTableSize);
        DirectorSkipList directorSL(SkipListCapacity, 10);
        ActorGraph actorGraph;

        //Function readMoviesCSV will return false if the file cannot be opened
        if(readMovieCSV(argv[1], hashTable, directorSL) == true){
            int userChoice;
            string _userChoice;

            cout << "Number of collisions: " << hashTable.getCollisions() << endl;

            //Display the menu and get the user's choice
            display_menu();
            getline(cin, _userChoice);
            userChoice = stoi(_userChoice);

            //Runs the program until the user chooses 9 (exit)
            while(userChoice != 9){
                //If the users chooses to use the Graph while it was not constructed yet,
                //ask to cosntruct the Graph
                while(userChoice >= 6 && userChoice <= 8 && actorGraph.getNumActors() == 0){                    
                    string choice;
                    cout << "\nGraph does not exist!\nDo you wish to construct it? (y/n)" << endl;
                    getline(cin, choice);

                    while(choice != "n" && choice != "y" && choice != "Y" && choice != "N"){
                        cout << "Invalid option. Do you wish to construct the graph? (y/n)" << endl;
                        getline(cin, choice);
                    }

                    //If the user says yes, construct the Graph
                    if(choice == "y" || choice == "Y") userChoice = 5;

                    //If the users says "no", display the menu again
                    else{
                        display_menu();
                        getline(cin, _userChoice);
                        userChoice = stoi(_userChoice);
                    }
                }
                switch(userChoice){
                    case 1:{ //Find the director of a movie
                        string _title;
                        cout << "Enter the name of the movie:\n#>";
                        getline(cin, _title);
                        cout << endl;

                        MovieNode* targetMovie = hashTable.search(_title);

                        if(!targetMovie) cout << "Movie " << _title << " not found in the database!" << endl;

                        else cout << "The movie " << _title << " was directed by " << targetMovie->director << "!" << endl;

                        cout << endl;
                        break;
                    }

                    case 2:{ //Find the number of movies of a director
                        string _director;
                        cout << "Enter the name of a director:\n#>";
                        getline(cin, _director);
                        cout << endl;

                        DirectorSLNode* targetDirector = directorSL.search(_director);

                        if(!targetDirector) cout << "Director " << _director << " not found in the database!" << endl;

                        else cout << "Director " << _director << " has " << targetDirector->movies.size() << " movie(s) recorded in our database!" << endl;

                        cout << endl;
                        break;
                    }

                    case 3:{ //Get the description of a movie
                        string _title;
                        cout << "Enter the name of a movie:\n#>";
                        getline(cin, _title);
                        cout << endl;

                        MovieNode* targetMovie = hashTable.search(_title);

                        if(!targetMovie) cout << "Movie " << _title << " not found in the database!" << endl;

                        else{
                            cout << "Here is a brief description of " << _title << ":" << endl;
                            cout << "Released in " << targetMovie->year << " by director " << targetMovie->director << ", " << _title << " is a " << targetMovie->genre << " featuring actors " << targetMovie->actors << "." << endl;
                            cout << "Plot: " << targetMovie->description << endl;
                        }
                        cout << endl;
                        break;  
                    }

                    case 4:{ //List all movies by a director
                        string _director;
                        cout << "Enter the name of a director:\n#>";
                        getline(cin, _director);
                        cout << endl;

                        DirectorSLNode* targetDirector = directorSL.search(_director);

                        if(!targetDirector) cout << "Director " << _director << " not found in the database!" << endl;

                        else{
                            cout << "Here is a list of all movies directed by " << _director << " in our database:" << endl;
                            for(auto movie : targetDirector->movies){
                                cout << "-" << movie->title << endl;
                            }
                        }
                        cout << endl;
                        break;
                    }

                    case 5:{ //Construct the Graph           
                        if(actorGraph.getNumActors() != 0) cout << "\nGraph already exists!" << endl;

                        else{
                            actorGraph = ActorGraph(hashTable.getHashTable(), hashTableSize);
                            cout << "\nActor graph has been created! " << actorGraph.getNumActors() << " actors were added!" << endl;
                        }
                        
                        cout << endl;
                        break;
                    }

                    case 6:{ //Get the number of movies of an actor
                        string _actor;
                        cout << "Enter the name of an actor:\n#>";
                        getline(cin, _actor);
                        cout << endl;

                        Actor* targetActor = actorGraph.searchGraph(_actor);

                        if(!targetActor) cout << "Actor " << _actor << " not found in the database!" << endl;

                        else cout << _actor << " has acted in " << targetActor->movies.size() << " movie(s) in our database!" << endl;

                        cout << endl;
                        break;
                    }

                    case 7:{ //List all movies of an actor
                        string _actor;
                        cout << "Enter the name of an actor:\n#>";
                        getline(cin, _actor);
                        cout << endl;

                        Actor* targetActor = actorGraph.searchGraph(_actor);

                        if(!targetActor) cout << "Actor " << _actor << " not found in the database!" << endl;

                        else{
                            cout << "Here is a list of all movies that " << _actor << " has acted in recorded in our database:" << endl;
                            for(auto movie : targetActor->movies){
                                cout << "-" << movie->title << endl;
                            }
                        }
                        cout << endl;
                        break;
                    }

                    case 8:{ //Find the distance between two actors
                        string _actor1;
                        string _actor2;
                        cout << "Enter the name of the first actor:\n#>";
                        getline(cin, _actor1);
                        cout << "Enter the name of the second actor:\n#>";
                        getline(cin, _actor2);
                        cout << endl;

                        int distance = actorGraph.findDistance(_actor1, _actor2);

                        if(distance == -3) cout << "Actors " << _actor1 << " and " << _actor2 << " are not connected in our database!" << endl;
                        
                        if(distance == -2) cout << "One or more actors not found in the database!" << endl;

                        else if(distance == -1) cout << "Please enter two different names!" << endl;

                        else if(distance == 0) cout << "The distance between " << _actor1 << " and " << _actor2 << " is 0! They worked together in " << actorGraph.findCommonMovie(_actor1, _actor2) << endl;

                        else cout << _actor1 << " and " << _actor2 << " are " << distance << " movies apart!" << endl;

                        cout << endl;
                        break;
                    }

                    case 9:{ //Exit
                        continue;
                        break;
                    }

                    default:{ //If the user inputs a number that's not between 1 and 9, print "Invalid option"
                        cout << "\nInvalid option. ";
                        break;
                    }
                }
                //After the user's choice has been executed, re-display the menu
                display_menu();
                getline(cin, _userChoice);
                userChoice = stoi(_userChoice);
            }
            //When user chooses 9, call the Graph's destructor and print the exit message
            actorGraph.graphDestructor();
            cout << "Quitting... GoodBye!" << endl;
        }
    }
    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
bool readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    ifstream fin;
    fin.open(filename);

    if(!fin.is_open()){
        cout << "Failed to open CSV file!" << endl;
        return false;
    }

    else{
        string line;
        getline(fin, line);

        while(!fin.eof()){
            getline(fin, line);
            MovieNode* newMovie = parseMovieLine(line);

            // getchar();
            movieTable.insert(newMovie->title, newMovie);
            directorList.insert(newMovie->director, newMovie);
        }
        return true;
    }
}

// Function to display the menu options
void display_menu() {
    cout << "Please select one of the following: " << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Construct graph of actors" << endl;
    cout << "6. Find the number of movies of an actor" << endl;
    cout << "7. List all movies of an actor" << endl;
    cout << "8. Find the distance between two actors" << endl;
    cout << "9. Quit" << endl;
    cout << "#> ";
}