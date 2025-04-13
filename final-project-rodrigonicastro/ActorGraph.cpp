/*
This file contains the implementation of
the ActorGraph
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "ActorGraph.hpp"

using namespace std;

/*
ActorGraph - default constructor (does nothing)
*/
ActorGraph::ActorGraph(){
}

/*
ActorGraph - parametrized constructor

@param MovieNode** table
@param int tableSize
*/
ActorGraph::ActorGraph(MovieNode** table, int tableSize){
    for(int i = 0; i < tableSize; i++){
        while(table[i]){
            stringstream ss(table[i]->actors);
            vector<string> vctActors;
            string ssActor;

            while(getline(ss, ssActor, ',')) {
                ssActor.erase(0, ssActor.find_first_not_of(" "));
                ssActor.erase(ssActor.find_last_not_of(" ") + 1);

                vctActors.push_back(ssActor);
            }

            for(int j = 0; j < vctActors.size(); j++){
                addActor(vctActors[j], table[i]);
            }

            for(int j = 0; j < vctActors.size(); j++){
                for(int k = 0; k < vctActors.size(); k++){
                    addConnection(vctActors[j], vctActors[k]);
                }
            }
            table[i] = table[i]->next;
        }
    }
}

/*
graphDestructor() - destructor of the Graph
*/
void ActorGraph::graphDestructor(){
    for(auto actor : actors){
        delete actor;
        actor = 0;
    }

    actors.clear();
}

/*
addActor() - adds an actor to the Graph

@param string _name
@param MovieNode* _movie
*/
void ActorGraph::addActor(string _name, MovieNode* _movie){
    Actor* actor = searchGraph(_name);
    if(!actor){
        Actor* newActor = new Actor(_name);
        newActor->addMovie(_movie);
        actors.push_back(newActor);
    }

    else actor->addMovie(_movie);

    
}

/*
addConnection() - adds a connection between two actors

@param string _actor1
@param string _actor2
*/
void ActorGraph::addConnection(string _actor1, string _actor2){
    Actor* actor1 = searchGraph(_actor1);
    Actor* actor2 = searchGraph(_actor2);

    if((!actor1 || !actor2) || (_actor1 == _actor2)) return;

    else if(is_connection(_actor1, _actor2)) return;

    colleague c1;
    colleague c2;

    c1.a = actor2;
    c2.a = actor1;

    actor1->connections.push_back(c1);
    actor2->connections.push_back(c2);
}

/*
is_connection() - verifies if there is a connection between two actors

@param string _actor1
@param string _actor2

@return bool
*/
bool ActorGraph::is_connection(string _actor1, string _actor2){
    Actor* actor1 = searchGraph(_actor1);
    Actor* actor2 = searchGraph(_actor2);

    for(auto colleague : actor1->connections){
        if(colleague.a->name == _actor2) return true;
    }

    return false;
}

/*
findDistance() - finds how many movies apart two actors are 

@param string _actor1
@param  string _actor2

@return int
*/
int ActorGraph::findDistance(string _actor1, string _actor2){
    if(_actor1 == _actor2) return -1;

    if(!searchGraph(_actor1) || !searchGraph(_actor2)) return -2;
    
    resetGraph();
    Actor* src = searchGraph(_actor1);

    queue<Actor*> qq;
    src->visited = true;
    src->distance = -1;

    qq.push(src);

    while(!qq.empty()){
        Actor* u = qq.front();

        qq.pop();

        for(auto colleague : u->connections){
            if(!colleague.a->visited){
                colleague.a->visited = true;
                colleague.a->distance = u->distance + 1;

                if(colleague.a->name == _actor2) return searchGraph(_actor2)->distance;

                qq.push(colleague.a);
            }
        }
    }
    return -3;
}

/*
findCommonMovie() - finds a movie that two actors have acted in together

@param _actor1
@param _actor2

@return string
*/
string ActorGraph::findCommonMovie(string _actor1, string _actor2){
    vector<MovieNode*> movies1 = searchGraph(_actor1)->movies;
    vector<MovieNode*> movies2 = searchGraph(_actor2)->movies;

    for(int i = 0; i < movies1.size(); i++){
        for(int j = 0; j < movies2.size(); j++){
            if(movies1[i]->title == movies2[j]->title) return movies1[i]->title;
        }
    }
    return "";
}

/*
searchGraph() - finds an Actor* of an actor

@param actorName

@return Actor*
*/
Actor* ActorGraph::searchGraph(string actorName){
    for(auto actor : actors){
        if(actor->name == actorName) return actor;
    }

    return nullptr;
}

/*
displayConnections() - prints all actors and the connections between them (used for testing purposes)
*/
void ActorGraph::displayConnections(){
    resetGraph();
    cout << "Displaying connections" << endl;
    for(auto actor : actors){
        cout << actor->name;
        for(auto colleague : actor->connections){
            cout << " --> " << colleague.a->name;
        }
        cout << endl;
    }
}

/*
resetGraph() - sets all nodes' visited = false and distance = 0
*/
void ActorGraph::resetGraph(){
    for(auto actor : actors){
        actor->visited = false;
        actor->distance = 0;
    }
}

/*
getNumActors() - returns the number of actors in the Graph

@return int
*/
int ActorGraph::getNumActors(){
    return actors.size();
}