#include <iostream>
#include <string>
#include "WordList.h"
#include "NgramList.h"
#include "NgramFast.h"

/* You may NOT declare any global variables. */

/* You may add data members to the NgramFast class by adding them to NgramFast.h */
/* You may add more methods to the NgramFast class.  Put prototypes in NgramFast.h */
/* You may add more classes.  If you do, they need to be cleanly
 * separated into a .h and a .C files. You would add an include
 * for the .h at the top.  You would need to change the makefile
 * so that your new classes are compiled and linked with the
 * executable. */

/*
 * Ngrams
 *
 * Takes as input the size of the ngrams to be built and the list
 * of words to build the ngrams from and builds a collection
 * of ngrams. You may not use the C++ STL to define a collection object.
 * You need to implement your own.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, WordList &wl)
{
   // Add any code you need to initialize whatever structure
   // you use to hold your ngrams.

   // initialze hashtable to nulls.
   for (int i = 0; i < TABLESIZE; i++)
   {
      hashTable[i] = NULL;
   }
   for (int i = 0; i < TABLESIZE; i++)
   {
      sortedArray[i] = NULL;
   }

   // This code doesn't change
   this->ngramSz = ngramSz;
   wl.beginIter();
   while (!wl.endIter())
   {
      std::string ngram = wl.getNextNgram(ngramSz);
      wl.incrementIter();
      // Insert the ngram in the collection object
      if (!ngram.empty())
         insertNgram(ngram);
   }

   // You can make additional calls here if you need to.
}

/*
 * Ngrams destructor
 *
 * Automatically called when Ngrams object goes out of scope.
 * Delete any space dynamically allocated to hold the ngrams.
 */
Ngrams::~Ngrams()
{
   /* Warning: this destructor contains a memory error. */
   NodeGram *ptr3;
   NodeGram *ptr2;
   NodeGram *ptr;
   for (int i = 0; i < TABLESIZE; i++)
   {
      ptr = hashTable[i];
      while (ptr != NULL)
      {
         ptr2 = ptr->nextngraminHT;
         delete (ptr); //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         ptr = ptr2;
         // delete(ptr2);
      }
      // delete(ptr2);

      ptr3 = sortedArray[i];
      while (ptr3 != NULL)
      {
         ptr2 = ptr3->nextngraminSortedArray;
         delete (ptr3);
         ptr3 = ptr2;
      }
   }
   ptr2 = NULL;
   // delete(ptr2);
}

/*
 * insertNgram
 *
 * Inserts ngram into whatever structure you choose to hold
 * your ngrams. If the ngram is already in the collection, the
 * insert simply increments the count.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(std::string s)
{

   bool ngramFound = false;
   // NodeGram *ngramPtr = new NodeGram();
   // NodeGram *ngramPtr2 = new NodeGram();
   int hashedString = hashAlgorithm(s);

   // ngramPtr->ngramString = s;
   // ngramPtr->count = 1;
   // ngramPtr->nextngraminSortedArray = NULL;
   // ngramPtr->nextngraminHT = NULL;
   // delete (ngramPtr2);
   // if the hashed spot is null do this if statement
   if (hashTable[hashedString] == NULL) // used to be if(hashTable == NULL)
   {
      NodeGram *ngramPtr = new NodeGram();

      ngramPtr->ngramString = s;
      ngramPtr->count = 1;
      ngramPtr->nextngraminSortedArray = NULL;
      ngramPtr->nextngraminHT = NULL;
      hashTable[hashedString] = ngramPtr;
   }
   else
   { // if the hashed spot is not empty do this code
      NodeGram *ngramPtr2;
      ngramPtr2 = hashTable[hashedString];
      while (ngramPtr2 != NULL)
      {
         if (ngramPtr2->ngramString == s)
         {
            ngramFound = true;
            ngramPtr2->count = ngramPtr2->count + 1;
            // delete (ngramPtr);
            break;
         }
         ngramPtr2 = ngramPtr2->nextngraminHT; // to the next node ngrame thing.
      }
      ngramPtr2 = NULL; //????????????????????????????????????
      // if did not find the ngram's node do this code(ngramFound == false)
      // and the hashed spot is not empty
      // this means we need to hash the string into the linked node of that hashed spot
      if (!ngramFound)
      {
         NodeGram *ngramPtr = new NodeGram();
         ngramPtr->ngramString = s;
         ngramPtr->count = 1;
         ngramPtr->nextngraminSortedArray = NULL;
         ngramPtr->nextngraminHT = NULL;

         ngramPtr->nextngraminHT = hashTable[hashedString]; // place the node at the front of the linked list
         hashTable[hashedString] = ngramPtr;                //^^ this new node is now the ngramPtr.
      }
   }
}

/*
 * addIncreasing
 *
 * Adds the ngrams to the ngram list in increasing order of ngram count.
 *
 */
void Ngrams::addIncreasing(NgramList *incrLst)
{

   // The call to add it to the list looks something like this:
   // incrLst->addToNgramList(ngramStr, ngramCnt);
   // You will probably have this call inside of a loop (or two)
   // NodeGram *ptr = new NodeGram();
   // NodeGram *ptr2 = new NodeGram();

   // for (int i = 0; i < TABLESIZE; i++)
   // {
   //    ptr = hashTable[i];

   //    while (ptr != NULL)
   //    {
   //       ptr->count;
   //    }
   // }

   if (inputToF == false)
   {
      sortByCount();
   }

   // NodeGram *ptr;

   for (int i = 0; i < TABLESIZE; i++)
   {
      if (sortedArray[i] != NULL)
      {

         NodeGram *ptr = sortedArray[i];
         while (ptr != NULL)
         {
            incrLst->addToNgramList(ptr->ngramString, ptr->count);
            ptr = ptr->nextngraminHT;
         }
         ptr = NULL;
      }
      // delete(ptr);
   }
   // delete(ptr);   //works too??
}

/*
 * addDecreasing
 *
 * Adds the ngrams to the ngram list in decreasing order of ngram count.
 *
 */
void Ngrams::addDecreasing(NgramList *decrLst)
{
   // The call to add it to the list looks something like this:
   // decrLst->addToNgramList(ngramStr, ngramCnt);
   // You will probably have this call inside of a loop (or two)
   if (inputToF == false)
   {
      sortByCount();
   }

   NodeGram *ptr = first;

   for (int i = TABLESIZE - 1; i > 0; i--)
   {
      if (sortedArray[i] != NULL)
      {
         // ptr = sortedArray[i];

         // incrLst->addToNgramList(ptr->ngramString, ptr->count);
         // ptr->nextngraminHT;

         ptr = sortedArray[i];
         while (ptr != NULL)
         {
            decrLst->addToNgramList(ptr->ngramString, ptr->count);
            ptr = ptr->nextngraminHT;
         }
      }
   }
   // delete(ptr);
   ptr = NULL;
}

int Ngrams::hashAlgorithm(std::string inputString)
{
   uint64_t hashedInputString = TABLESIZE;
   char stringChar = inputString[0];
   for (int i = 0; i < inputString.length(); i++)
   {
      hashedInputString += (((inputString[i] * 32) + inputString[i]));
   }

   return hashedInputString % TABLESIZE;
}

void Ngrams::sortByCount()
{

   //NodeGram *pastPtr;

   // NodeGram_t *ptr = first;

   for (int i = 0; i < TABLESIZE; i++)
   {
       NodeGram *currentPtr;
      currentPtr = hashTable[i];
      //delete(currentPtr); seg fULT
      while (currentPtr != NULL)
      {
         //delete(currentPtr); /inif loop
         int currcount = currentPtr->count;
         std::string currngram = currentPtr->ngramString;

         NodeGram *newNodePtr = new NodeGram();
         newNodePtr->ngramString = currngram;
         newNodePtr->count = currcount;
          //delete(newNodePtr); //seg fault
         // if (sortedArray[currentPtr->count] == NULL)
         if(sortedArray[currcount] ==NULL)
         {
            //sortedArray[currentPtr->count] = currentPtr;
            //take #17
            //  delete(newNodePtr); //infinate loop
            newNodePtr->nextngraminHT = NULL;
            sortedArray[currcount] = newNodePtr;
            currentPtr = currentPtr->nextngraminHT;
            //  delete(newNodePtr); //infinate loop
            //delete(currentPtr); results not correct
            continue;
            
         }
         
         else{
            // pastPtr = sortedArray[currentPtr->count];
            // sortedArray[currentPtr->count] = currentPtr;
            // currentPtr->nextngraminSortedArray = pastPtr;
            // delete(newNodePtr); //seg fault
            //**************************************************
            // NodeGram * ptr4 = sortedArray[currcount];
            // newNodePtr->nextngraminHT = ptr4;
            //**********************************************
            newNodePtr->nextngraminHT =sortedArray[currcount];
            sortedArray[currcount] = newNodePtr;

            //***********************************************
            currentPtr = currentPtr->nextngraminHT;
            
         // delete(newNodePtr); //seg fault
         //delete(currentPtr); //infi loop
         }
         // currentPtr = currentPtr->nextngraminHT;
         // delete(newNodePtr); //seg fault
         //delete(currentPtr); //infi loop
         

      }
      // delete(newNodePtr); //not in the scope
      delete(currentPtr); //@@@@@@@@@@@@@@@@@@@@@
      
   }
   // delete(newNodePtr); //not in the scope
   
   inputToF = true;
}
