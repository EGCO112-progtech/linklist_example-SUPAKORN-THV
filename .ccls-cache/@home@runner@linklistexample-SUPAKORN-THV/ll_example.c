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

int deletes( LLPtr *headPtr, LLPtr *tailPtr, char name[SIZE] );
int delAll( LLPtr *headPtr, LLPtr *tailPtr );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *headPtr, LLPtr *tailPtr, int valueID, char valueName [SIZE] );
void printList( LLPtr currentPtr, LLPtr tailPtr );
void reverseList( LLPtr currentPtr, LLPtr tailPtr );
void instructions( void );

int main( void )
{ 
   LLPtr startPtr = NULL; // initially there are no nodes
   LLPtr tailPtr = NULL; // initially tail pointer is NULL
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
            insert( &startPtr, &tailPtr, idScan, nameScan ); // insert idScan in list
            printList( startPtr , tailPtr);
            reverseList ( startPtr, tailPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter id or name (case sensitivity) to be deleted: " );
               scanf(" %[^\n]", nameScan);
              //scanf( "%d", &idScan );
               // if character is found, remove it
               if ( deletes( &startPtr, &tailPtr, nameScan ) ) { // remove idScan
                  printf( "%s deleted.\n", nameScan );
                  printList( startPtr , tailPtr);
                  reverseList ( startPtr, tailPtr );
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
   delAll( &startPtr, &tailPtr);
   printList( startPtr , tailPtr);
   puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
   puts( 
     "Version 3.1 [Circular Linked List]\n"
     "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( LLPtr *headPtr, LLPtr *tailPtr, int valueID, char valueName [SIZE] )
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
      currentPtr = *headPtr;

      if(currentPtr==NULL) {// Insert the first node
        *headPtr = newPtr;
        *tailPtr = newPtr;
        newPtr->nextPtr = newPtr;
        newPtr->pPtr = newPtr;
        printf("Node initialized!\n");
      }
      else if (*headPtr == *tailPtr) { //Check if only the first node is inserted (Insert the second node)
        if (newPtr->id > currentPtr->id){ printf("Only the first node!\n");
          *tailPtr = newPtr;
          newPtr->pPtr = currentPtr;
          newPtr->nextPtr = *headPtr;
          currentPtr->nextPtr = newPtr;
        }
        else { printf("Beginning...! Head x Tail\n");
          *headPtr = newPtr;
          newPtr->pPtr = *tailPtr;
          newPtr->nextPtr = currentPtr;
          currentPtr->pPtr = newPtr;
          (*tailPtr)->nextPtr = newPtr;
        }
      } else {
         // loop to find the correct location in the list       
         while ( currentPtr != *tailPtr && newPtr->id > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
         printf("Waliking OK!\n");
        } // end while  

        if(previousPtr == NULL) {//At the beginning
          printf("Beginning...!\n");
          *headPtr = newPtr;
          currentPtr->pPtr = newPtr;
          newPtr->pPtr = *tailPtr;
          newPtr->nextPtr = currentPtr;
          (*tailPtr)->nextPtr = newPtr;
        } else if (currentPtr != *tailPtr || newPtr->id <= currentPtr->id)
        { //In the Middle
          printf("Centering...!\n");
          newPtr->pPtr = previousPtr;
          newPtr->nextPtr = currentPtr;
          previousPtr->nextPtr = newPtr;
          currentPtr->pPtr = newPtr;
        } else { //At the final
          printf("Finalize...!\n");
          *tailPtr = newPtr;
          currentPtr->nextPtr = newPtr;
          newPtr-> pPtr = currentPtr;
          newPtr-> nextPtr = *headPtr;
          (*headPtr)->pPtr = newPtr;
        }
      }                                 
     }
      /*// insert new node at beginning of list
      if ( previousPtr == NULL ) { 
         if(*sPtr) (*sPtr)->pPtr = newPtr; // For not the first add
         newPtr->nextPtr = *sPtr;
         if(*tPtr == NULL) { 
           *tPtr = newPtr; // If the first add set tail as start
           newPtr->nextPtr = *tPtr;
           }
         newPtr->pPtr = *tPtr; //Node to tail
         *sPtr = newPtr;
        
        
      } // end if
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr = previousPtr; 
         newPtr->nextPtr = currentPtr;
         if(currentPtr != *tPtr) currentPtr->pPtr = newPtr; // Not the last
         else *tPtr = newPtr; //Change tail to the last
 
         
      } // end else
   } // end if*/
   else {
      printf( "%d %s not inserted. No memory available.\n", valueID, valueName);
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *headPtr, LLPtr *tailPtr, char name[SIZE] )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer
   int value = atoi(name);
  
   // delete first node
   if ( value == ( *headPtr )->id || strcmp( name, ( *headPtr )->name ) == 0 ) { 
      tempPtr = *headPtr; // hold onto node being removed
      if(( *headPtr ) != *tailPtr) 
      {
        *headPtr = ( *headPtr )->nextPtr; // de-thread the node
        (*headPtr)->pPtr = *tailPtr;
        (*tailPtr)->nextPtr = *headPtr;
      }
      else *headPtr = *tailPtr = NULL;
      printf( "%d %s is about to be deleted.\n", tempPtr->id, tempPtr->name );
      free( tempPtr ); // free the de-threaded node
      return 1;
   } // end if
   else { 
      previousPtr = *headPtr;
      currentPtr = ( *headPtr )->nextPtr;
      
      // loop to find the correct location in the list
      while (( currentPtr->id != value && ( strcmp(currentPtr->name,name ) != 0 )) && currentPtr != *tailPtr) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != *tailPtr) { 
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         currentPtr = currentPtr->nextPtr;
         currentPtr->pPtr = tempPtr->pPtr;
         printf( "%d %s is about to be deleted.\n", tempPtr->id, tempPtr->name );
         free( tempPtr );
         return 1;
      } else if (currentPtr->id == value || ( strcmp(currentPtr->name,name )) == 0) {
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         currentPtr = currentPtr->nextPtr;
         currentPtr->pPtr = tempPtr->pPtr;
         *tailPtr = (*tailPtr)->pPtr;
         printf( "[end] %d %s is about to be deleted.\n", tempPtr->id, tempPtr->name );
         free( tempPtr );
         return 1;
      } // end if
   } // end else

   return '\0';
} // end function delete

// delete a list element
int delAll( LLPtr *headPtr, LLPtr *tailPtr)
{ 
   LLPtr tempPtr; // temporary node pointer

   // delete node 
      tempPtr = *headPtr; // hold onto node being removed
  while(tempPtr != *tailPtr ){
      *headPtr = ( *headPtr )->nextPtr; // de-thread the node
      printf("Deleting %d %s\n", tempPtr->id, tempPtr->name);
      free(tempPtr);
      tempPtr = *headPtr; // hold onto next node being removed
    } // end while
   if (tempPtr) {
     printf("Deleting %d %s\n", tempPtr->id, tempPtr->name);
     free(tempPtr);
     *headPtr = *tailPtr = NULL;
     printf("Deletion completed\n");
     } else {
     printf("Node is not initialized\n");
     }
   return '\0';
} // end function delAll

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr, LLPtr tailPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // while not the end of the list
     printf("Head is %d [%p]. Tail is %d [%p]\n\n",currentPtr->id, currentPtr, tailPtr->id, tailPtr);
      while ( currentPtr != tailPtr ) {
         printf( "%d %s --> ", currentPtr->id, currentPtr->name);
         currentPtr = currentPtr->nextPtr;
      } // end while

      printf( "%d %s Final --> %d %s\n", currentPtr->id, currentPtr->name, currentPtr->nextPtr->id , currentPtr->nextPtr->name );
       

     
       
   } // end else
} // end function printList

void reverseList( LLPtr currentPtr, LLPtr tailPtr )
{ 
   LLPtr tempPtr = currentPtr;
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The reversed list is:" ); 
     
      while ( currentPtr != tailPtr ) {
         currentPtr = currentPtr->nextPtr;   
      } // end while
     
      // while not the end of the list
      while ( currentPtr != tempPtr) {
         printf( "%d %s --> ", currentPtr->id, currentPtr->name);
         currentPtr = currentPtr->pPtr;   
      } // end while

      printf( "%d %s Final --> %d %s\n", currentPtr->id, currentPtr->name, currentPtr->pPtr->id , currentPtr->pPtr->name );;
       

     
       
   } // end else
} // end function printList