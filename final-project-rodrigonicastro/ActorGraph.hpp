/*
This file contains the declaration of
the ActorGraph class and the Actor Node
to be used in the Graph
*/

#include <iostream>
#include <vector>
#include <queue>
#include "MovieNode.hpp"

using namespace std;

struct Actor;
/*Struct of the Actor's colleagues (to be used
as nodes in the adjacency list)*/
struct colleague{
    Actor* a;
};

/*Actor struct to be used as nodes in the Graph*/
struct Actor{
    vector<colleague> connections; //The Actor's adjacency list (other actors that "Actor" has worked with)
    vector<MovieNode*> movies;     //A list of the movies in which Actor has worked
    bool visited = false;          //A boolean showing if this Actor has been visited or not
    int distance = 0;              //The distance from this Actor to the one being used as the source of the Traverse
    string name;                   //The actor's name
    
    Actor(){} //Actor default constructor (does nothing)

    Actor(string _name){name = _name;} //Actor parametrized constructor (sets the Actor's name to _name)

    //Adds a movie to the Actor's movie list
    void addMovie(MovieNode* _movie){
        for (auto movie: movies) {
        if (movie->title == _movie->title) {
            cout << "Duplicate movie! Skipped" << endl;
            return;
        }
    }
        movies.push_back(_movie);
    }
};

//Declaration of the Graph class
class ActorGraph{
    private:
        vector<Actor*> actors; //The vector to store the actors in the Graph

    public:
        //The Graph's default constructor
        ActorGraph(); 

        //The Graph's parametrized constructor 
        ActorGraph(MovieNode** table, int tableSize); 

        //The Graph's destructor
        void graphDestructor(); 

        //Adds and actor to the Graph
        void addActor(string _name, MovieNode* _movie); 

        //Adds a connection between two actors
        void addConnection(string _actor1, string _actor2); 

        //Verifies if there is a connection between two actors
        bool is_connection(string _actor1, string _actor2); 

        //Finds the distance between two actors
        int findDistance(string _actor1, string _actor2); 

        //Sets all Actors' "visited" to false and "distance" to 0
        void resetGraph(); 

        //Searches the Graph 
        Actor* searchGraph(string actorName); 

        //Prints all actors and the connections between them (used for testing purposes)
        void displayConnections();

        //Returns the number of Actors in the graph
        int getNumActors();

        //Finds a movie that two actors have worked in together (only called when finDistance() returns 0)
        string findCommonMovie(string _actor1, string _actor2);
};