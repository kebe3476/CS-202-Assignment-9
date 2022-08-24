/*
CS 202 Assignment 9

Name: Keith Beauvais, 5005338658, CS 202 Assignment 9
*/
#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif
#include <cstdlib>

/*******************************
 *  CARD CLASS 
*******************************/
Card::Card(){
    Suit = '\0';
    Value = '\0';
    Weight = -99;
}

Card::Card(char suit, char value){
    Suit = suit;
    Value = value;
    switch (value){
        case 'A':
            Weight = 14;
            break;
        case 'K':
            Weight = 13;
            break;
        case 'Q':
            Weight = 12;
            break;
        case 'J':
            Weight = 11;
            break;
        case 'T':
            Weight = 10;
            break; 
        case '9':
            Weight = 9;
            break;   
        case '8':
            Weight = 8;
            break;
        case '7':
            Weight = 7;
            break; 
        case '6':
            Weight = 6;
            break;   
        case '5':
            Weight = 5;
            break;
        case '4':
            Weight = 4;
            break; 
        case '3':
            Weight = 3;
            break;
        case '2':
            Weight = 2;
            break;        
    }          
}
/* string GetCard() will return a string representing the card.

return value - returns string concatenation of the suit and value of the card.
*/
string Card::GetCard() const{
    string val, suit;
    suit = Suit;
    val = Value;
    return " |[" + suit + val + "]| ";
}

/* Operator < is used in sorting the cards at the end of the game. The Operator first 
considers the ascii value corresponding to the suit of the card. So, a sorted list of suits will 
contain the order of either (S,H,D,C) or (C,D,H,S). If the suits are the same, then the operator will 
consider the weight.

Card rhsCard - This is the right hand side of the card being conpared as it the one being passed in

return value - returns a true or false bool value, true for if the right side is larger than the left or 
if the suits are the same but the right side weight is more. Anything else it returns a false.
*/
bool Card::operator<(Card rhsCard) const{
    if(this ->Suit < rhsCard.Suit){
        return true;
    }
    if(this -> Suit == rhsCard.Suit && this -> Weight < rhsCard.Weight){
        return true;
    }
    return false;
}
/* Operator < is the same thing as above but reverse. It is used in sorting the cards at the end of the game. The Operator first 
considers the ascii value corresponding to the suit of the card. So, a sorted list of suits will 
contain the order of either (S,H,D,C) or (C,D,H,S). If the suits are the same, then the operator will 
consider the weight.

Card rhsCard - This is the right hand side of the card being conpared as it the one being passed in

return value - returns a true or false bool value, true for if the left side is larger than the right or 
if the suits are the same but the right side weight is less. Anything else it returns a false.
*/
bool Card::operator>(Card rhsCard) const{
    if(this ->Suit > rhsCard.Suit){
        return true;
    }
    if(this -> Suit == rhsCard.Suit && this -> Weight > rhsCard.Weight){
        return true;
    }
    return false;
}
/* int GetWeight() his just returns the cards numeric weight.

return value - returns weight.
*/
int Card::GetWeight() const{
    return Weight;
}

/*******************************
 *  DECK CLASS 
*******************************/
Deck::Deck(){ 
    this -> Head = NULL;
    SizeOfDeck = 0; 
}

// Rule of Three
Deck::~Deck(){
    ClearDeck();
}
/* Operator = First, the memory of the linked list on the LHS deck needs to be deallocated. Then, check to see
if the copied head is equal to NULL or the copied size of deck is equal to zero. If it is then set the Head to NULL and
return out. If not then copy the copied size of deck over to the left side. A new pointer is established and then it
is set to the left side head pointer. The tempory pointer then copies the data that was passed in by the copied
head pointer and the next pointer is set to Null. there are two more pointers established and then are set to 
the head pointers of there respective linked lists. They then copy over the data as a deep copy.   

Deck &copy - of type deck passes in the data to be assigned. 

return value - void does not return a type. 
*/
void Deck::operator=(const Deck &copy){

    ClearDeck();
    if(copy.Head == NULL || copy.GetSizeOfDeck() == 0 ){
        this -> Head = NULL;
        return;
    }
    else{
        SizeOfDeck = copy.GetSizeOfDeck();
        Node * temp;
        temp = new Node;
        this-> Head = temp;
        temp -> card = copy.Head -> card; 
        temp -> next = NULL;
        Node * i1, *i2;
        i1 = copy.Head;
        i2 = temp;
        i1 = i1-> next;

        while(i1 != NULL){
            i2 -> next = new Node;
            i2 = i2 -> next;
            i2 -> card = i1 -> card;
            i1 = i1 -> next;
            i2 -> next= NULL;
        }
    }
}
/* Copy constructor-  First, the memory of the linked list on the LHS deck needs to be deallocated. Then, check to see
if the copied head is equal to NULL or the copied size of deck is equal to zero. If it is then set the Head to NULL and
return out. If not then copy the copied size of deck over to the left side. A new pointer is established and then it
is set to the left side head pointer. The tempory pointer then copies the data that was passed in by the copied
head pointer and the next pointer is set to Null. there are two more pointers established and then are set to 
the head pointers of there respective linked lists. They then copy over the data as a deep copy.   

Deck &copy - of type deck passes in the data to be assigned. 

return value - void does not return a type. 
*/
Deck::Deck(const Deck& copy){

    this -> Head = NULL;

    if(copy.Head == NULL || copy.GetSizeOfDeck() == 0 ){
      return;
    }
    else{
        SizeOfDeck = copy.GetSizeOfDeck();
        Node * temp;
        temp = new Node;
        this -> Head = temp;
        temp -> card = copy.Head -> card; 
        temp -> next = NULL;
        Node * i1, *i2;
        i1 = copy.Head;
        i2 = temp;
        i1 = i1-> next;

        while(i1 != NULL){
            i2 -> next = new Node;
            i2 = i2 -> next;
            i2 -> card = i1 -> card;
            i1 = i1 -> next;
            i2 -> next= NULL;
        }
    }
}
/* operator[]-  iterates through the linked list an index amount of times (int index is the parameter)
and returns the node at that position.

int index - passes in the index that wants to return.  

return value - return a pointer to a node within the linked list.. 
*/
Deck::Node* Deck::operator[](int index){

    Node * iter;
    iter = this->Head;
    if(index >= GetSizeOfDeck()|| index < 0){
        iter = NULL;
        return iter;
    }
    else{
        int count = 0;
        while(iter != NULL){
            if(count == index){
                return iter;
            }
        count++;
        iter = iter -> next;
        }
        return iter;
    }
return iter;
}

// Member Functions

/* AddToTopOfDeck()-  will add the parameter card to the top of the deck. This means allocate 
a new node, copy the parameter card into the node, and insert that node as the new head of the 
linked list.

Card card - passes in a card that will added to the top of the pile.

return value - return a pointer to a node within the linked list.. 
*/
void Deck::AddToTopOfDeck(Card card){
    Node * ins;
    ins = new Node;
    ins -> card = card;
    ins -> next = this -> Head;
    this -> Head = ins;
    
    SizeOfDeck++;
}
/* RemoveTopCard()-  will return the card stored within the head node. It will also deallocate 
the head node and update the head node to be pointing at the next node in the linked list.

return value - returns the card that was removed from the top of the deck. 
*/
Card Deck::RemoveTopCard(){
    Card removeCard;
    removeCard = this -> Head -> card;

    Node * del;
    del = this -> Head;
    this -> Head = this-> Head -> next;
    delete del;
    del = NULL;
    SizeOfDeck--;

    return removeCard; 
}
/* ShuffleDeck()-  will shuffle the cards all randomly. For a set amount of iter- ations (I picked SizeOfDeck∗3), 
swap 2 random cards in the deck. Since my SwapCards() is based on bubble sort, the cards need to be adjacent with each other. 

return value - void return. 
*/

void Deck::ShuffleDeck(){  
    int rCard= 0; 
    
    for(int i = 0; i< SizeOfDeck*3; i++){
        rCard = GetRandomCardIndex();
        SwapCards((*this)[rCard],(*this)[rCard+1]);
    }
    
}

// This is essentially the Destructor. Has use outside of destructor

/* ClearDeck()- will deallocate the entire linked list and set SizeOfDeck to 0. 
If Head is already NULL, there is nothing to deallocate.

return value - void return. 
*/
void Deck::ClearDeck(){
    SizeOfDeck = 0;
    if( this -> Head == NULL){
        return;
    }
    else{
        while( this -> Head != NULL){
            Node * del;
            del = this -> Head;
            this -> Head = this -> Head -> next;
            delete del;
        }
    }
}
/* ClearDeck()- will sort the deck using the operator overload in the Card class. I used bubble sort in this case so 
the cards need to be adjacent to each other. 

return value - void return. 
*/
void Deck::SortDeck(){

    for(int i = 0; i< SizeOfDeck; i++){
        for(int j = 0; j< SizeOfDeck - i - 1; j++){
            if((*this)[j]->card < (*this)[j+1]->card){
                SwapCards((*this)[j],(*this)[j+1]);
            }
        }
    }
}
/* SwapCards(Node* A, Node* B)- The SwapCards function will only swap 2 nodes that are adjacent (right next to each other).
the left-most node is always the previous node to the right-most node. I check to see if A is the Head, B is the tail and if 
A and B are in the middle.

Node * A- Passes in A pointer that will always be to the left of B

Node * B- Passes in B pointer that will always be to the right of A

return value - void return. 
*/
void Deck::SwapCards(Node* A, Node* B){
    
    if(A == NULL || B == NULL){
        return;
    }

    Node * tmp, *tmp2;

    if( this->Head == A){
        tmp = B->next;
        B-> next = A;
        A -> next = tmp;
        this->Head = B;
        return;
    }
    else{
        tmp = this->Head;
        tmp2 = B -> next;
        while(tmp -> next != A){
            tmp = tmp ->next;
        }
        
        if(B -> next == NULL){
            B -> next = tmp -> next;
            A -> next = NULL;
            tmp -> next = B;
        }   

        else{
            B-> next = tmp -> next;
            A->next = tmp2;
            tmp -> next = B;
       }   
    }  
}

// Getters
int Deck::GetSizeOfDeck() const{
    return SizeOfDeck;
}

bool Deck::isEmpty() const{
    if(SizeOfDeck == 0){
        return true;
    }
    return false;
}

int Deck::GetRandomCardIndex() const{
    return (rand() % SizeOfDeck);
}

void Deck::PrintDeck(){
    cout << "-------------------------" << endl;
    for(int i = 0; i < SizeOfDeck; i++){
        cout << (*this)[i]->card.GetCard();
        if((i + 1) % 4 == 0){
            cout << endl;
        }
    }
     cout << endl << "-------------------------" << endl;
}