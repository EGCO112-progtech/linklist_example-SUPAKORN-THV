// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 128
// self-referential structure                       
struct Node {                                      
   //<!-- Homework Section -->
   int id;
   char name[SIZE];
   //<!-- End of Homework Section -->
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;
}; // end structure listNode                        

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, char name[SIZE] );
int delAll( LLPtr *sPtr );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int valueID, char valueName [SIZE] );
void printList( LLPtr currentPtr );
void reverseList( LLPtr currentPtr );
void instructions( void );

int main( void )
{ 
   LLPtr startPtr = NULL; // initially there are no nodes
   unsigned int choice; // user's choice
      //<!-- Homework Section -->
   int idScan;
   char nameScan[SIZE];
   //<!-- End of Homework Section -->

   instructions(); // display the menu
    scanf( "%u", &choice );

   // loop while user does not choose 3
   while ( choice != 3 ) { 

      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter your id: " );
            scanf( "%d", &idScan );
            printf("%s", "Enter your name: ");
            scanf(" %[^\n]", nameScan);           
            insert( &startPtr, idScan, nameScan ); // insert idScan in list
            printList( startPtr );
            reverseList ( startPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter id or name (case sensitivity) to be deleted: " );
               scanf(" %[^\n]", nameScan);
              //scanf( "%d", &idScan );
               // if character is found, remove it
               if ( deletes( &startPtr, nameScan ) ) { // remove idScan
                  printf( "%s deleted.\n", nameScan );
                  printList( startPtr );
                  reverseList ( startPtr );
                  printf("\n");
               } // end if
               else {
                  printf( "%s not found.\n\n", nameScan );
               } // end else
            } // end if
            else {
               puts( "List is empty.\n" );
            } // end else

            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

      printf( "%s", "? " );
      scanf( "%u", &choice );
   } // end while
  /* Clear all nodes at the end of nodes*/
   delAll( &startPtr );
   puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
   puts( 
     "Version 2.8 [Homework]\n"
     "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int valueID, char valueName [SIZE] )
{ 
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
  
   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = valueID; // place value in node
      strcpy(newPtr->name,valueName);
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->pPtr = NULL; // node does not link to another node
     
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while ( currentPtr != NULL && valueID > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list
      if ( previousPtr == NULL ) { 
         newPtr->nextPtr = *sPtr;
         if(*sPtr) (*sPtr)->pPtr = newPtr;
         *sPtr = newPtr;
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr = previousPtr; 
         newPtr->nextPtr = currentPtr;
         if(currentPtr) currentPtr->pPtr = newPtr;
 
         
      } // end else
   } // end if
   else {
      printf( "%d %s not inserted. No memory available.\n", valueID, valueName);
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, char name[SIZE] )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer
   int value = atoi(name);
  
   // delete first node
   if ( value == ( *sPtr )->id || strcmp( name, ( *sPtr )->name ) == 0 ) { 
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if(*sPtr)
      (*sPtr)->pPtr=NULL;
      free( tempPtr ); // free the de-threaded node
      return 1;
   } // end if
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;
      
      // loop to find the correct location in the list
      while ( currentPtr != NULL && ( currentPtr->id != value && ( strcmp(currentPtr->name,name ) != 0 ))) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) { 
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         currentPtr = currentPtr->nextPtr;
         if (currentPtr) currentPtr->pPtr = tempPtr->pPtr;
         free( tempPtr );
         return 1;
      } // end if
   } // end else

   return '\0';
} // end function delete

// delete a list element
int delAll( LLPtr *sPtr)
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete node 
      tempPtr = *sPtr; // hold onto node being removed
  while(tempPtr){
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      printf("Deleting %d %s\n", tempPtr->id, tempPtr->name);
      tempPtr = *sPtr; // hold onto next node being removed
    } // end while
   return '\0';
} // end function delAll

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d %s -->  ", currentPtr->id, currentPtr->name );
         currentPtr = currentPtr->nextPtr;   
      } // end while

      printf( "%d %s --> NULL\n", currentPtr->id, currentPtr->name );
       

     
       
   } // end else
} // end function printList

void reverseList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The reversed list is:" );
      
      while ( currentPtr->nextPtr!= NULL ) {
         currentPtr = currentPtr->nextPtr;   
      } // end while
     
      // while not the end of the list
      while ( currentPtr->pPtr != NULL) {
         printf( "%d %s --> ", currentPtr->id, currentPtr->name);
         currentPtr = currentPtr->pPtr;   
      } // end while

      printf( "%d %s --> NULL\n", currentPtr->id, currentPtr->name);
       

     
       
   } // end else
} // end function printList