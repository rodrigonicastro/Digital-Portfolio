/*
This file contains the implementation of
the Hash Table
*/

#include<iostream>
#include <vector>
#include <cmath>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
MovieHashTable::MovieHashTable() {
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode*[table_size];
    n_collisions = 0;
    
    for(int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

// Constructor for MovieHashTable with given size
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    table = new MovieNode*[table_size];
    n_collisions = 0;

    for(int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
MovieHashTable::~MovieHashTable() {
    MovieNode* curr;
    MovieNode* next;
    for(int i = 0; i < table_size; i++){
        curr = table[i];

        while(curr){
            next = curr->next;
            delete curr;
            curr = next;
        }
        table[i] = 0;
    }
    delete curr;
    delete next;
    delete[] table;
    curr = 0;
    next = 0;
}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
int MovieHashTable::hash(string title) {
    string _identiKey = "110638005";
    int hashKey = table_size;    
    int ASCIIsum = 0;
    int counter = 0;
    int hashIndex;

    for(int i = 0; i < title.length(); i++){
        if(_identiKey[counter] == '0') ASCIIsum += int(title[i]);
        
        else ASCIIsum += int(title[i])*int(_identiKey[counter]);

        counter++;
        if(counter > 8) counter = 0;
    }
    
    hashIndex = ASCIIsum % table_size;

    return hashIndex;
}

// Inserts a movie node into the hash table with the specified title
void MovieHashTable::insert(string title, MovieNode* movie) {
    int hashIndex = hash(title);

    if(table[hashIndex] == nullptr){        
        table[hashIndex] = movie;
    } 

    else{
        setCollisions();
        MovieNode* temp = table[hashIndex];

        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = movie;
    }
}

// Searches for a node in the hash table with the specified title
MovieNode* MovieHashTable::search(string title) {
    int hashIndex = hash(title);
    MovieNode* temp = table[hashIndex];

    while(temp != NULL){
        if(temp->title == title) return temp;
        temp = temp->next;
    }

    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
int MovieHashTable::getCollisions() {
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() {
    n_collisions++;
}

// Used for testing purposes
void MovieHashTable::printTable(){
    for(int i = 0; i < table_size; i++){
        if(table[i] != nullptr){
            cout << i << ": ";
            MovieNode* curr = table[i];
            while(curr != nullptr){
                cout << curr->title << "-> ";
                curr = curr->next;
            }
            cout << "NULL" << endl;
        }
    }
}