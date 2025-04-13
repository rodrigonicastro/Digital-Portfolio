/*
This file contains the implementation of
the Skip List
*/

#include<iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
DirectorSkipList::DirectorSkipList() {
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    size = 0;
    head = new DirectorSLNode("0", levels);
}

// Constructor for DirectorSkipList with given capacity and levels
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    capacity = _cap;
    levels = _levels;
    size = 0;
    head = new DirectorSLNode("0", levels);
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
DirectorSkipList::~DirectorSkipList() {
    DirectorSLNode* curr = head;
    DirectorSLNode* next;
    
    while(curr){
        next = curr->next[0];
        delete curr;
        curr = next;
    }

    delete curr;
    delete next;
    curr = 0;
    next = 0;
}

// Inserts a movie node into the skip list with the specified director
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    int nodeLevels = 1;

    while(nodeLevels < levels && (rand() % 2 == 0)) nodeLevels++;

    DirectorSLNode* newNode = new DirectorSLNode(director, nodeLevels);

    newNode->addMovie(_movie);
    
    DirectorSLNode* curr = head;
    DirectorSLNode* prev;

    if(size == 0) _insertHelper(head, newNode);

    else if(director < head->next[0]->director) _insertHelper(head, newNode);

    else{
        // Acha o lugar para inserir o newNode e chama a _insertHelper()
        for(int i = levels - 1; i >= 0; i--){
            while(curr->next[i] && curr->director < director){
                prev = curr;
                curr = curr->next[i];
                // Se o diretor já existe, adiciona o filme nesse diretor
                // e apaga o newNode
                if(curr->director == director){
                    curr->addMovie(_movie);
                    delete newNode;
                    return;
                }
                
                else if(director > curr->director){
                    if(!curr->next[0]){
                        _insertHelper(curr, newNode);
                        return;
                    }

                    else if(director < curr->next[0]->director){
                        _insertHelper(curr, newNode);
                        return;
                    }
                }
            }        
            if(curr->director > director) curr = prev;        
        }
    }
}

void DirectorSkipList::_insertHelper(DirectorSLNode* curr, DirectorSLNode* newNode){
    size++;
    if(curr == head){
        for(int i = 0; i < newNode->next.size(); i++){
            newNode->next[i] = curr->next[i];
            curr->next[i] = newNode;
        }
        return;
    }

    else{
        // Se curr tiver mais ou o msm # de niveis de newNode,
        // copia os ponteiros de curr para newNode   
        if(curr->next.size() >= newNode->next.size()){
            for(int i = 0; i < newNode->next.size(); i++){
                newNode->next[i] = curr->next[i];
                curr->next[i] = newNode;
            }
            return;
        }

        // Caso newNode tenha mais niveis que curr
        else{
            // Ter só um contador vai facilitar o acompanhamento de
            // quantos ponteiros já foram atualizados
            int i = 0;

            // Copia todos os ponteiros de curr para newNode
            while(i < curr->next.size()){
                newNode->next[i] = curr->next[i];
                curr->next[i] = newNode;
                i++;
            }
            
            // Enquanto não atualizar todos os ponteiros de newNode:
            while(i < newNode->next.size()){
                //Acha o nó anterior com mais níves que curr
                int currLevels = curr->next.size();
                while(curr->next.size() <= currLevels) curr = findPrevious(curr);

                // Enquanto não atingir o limite de ponteiros de curr ou newNode,
                // copia os ponteiros de curr para newNode
                while(i < curr->next.size() && i < newNode->next.size()){
                    newNode->next[i] = curr->next[i];
                    curr->next[i] = newNode;
                    i++;
                }
            }
            return;
        }
    }
}

// Searches for a node in the skip list with the specified director
DirectorSLNode *DirectorSkipList::search(string director) {
    DirectorSLNode* curr = head;
    DirectorSLNode* prev;

    for(int i = levels - 1; i >= 0; i--){
        while(curr->next[i] && curr->director < director){
            prev = curr;
            curr = curr->next[i];
            if(curr->director == director) return curr;
        }

        if(curr->director > director) curr = prev;
    }

    return nullptr;
}

DirectorSLNode* DirectorSkipList::findPrevious(DirectorSLNode* curr){
    if(!curr) return nullptr;

    else{
        DirectorSLNode* prevCurr = head;
        DirectorSLNode* prevPrevCurr;

        while(prevCurr->next[0]){
            if(prevCurr->next[0]->director == curr->director) return prevCurr;

            prevCurr = prevCurr->next[0];
        }
        return nullptr;
    }
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() {
    DirectorSLNode* curr = head;

    while(curr){
            cout << curr->director << " -> ";
            curr = curr->next[0];
        }
        cout << "NULL" << endl;
}