#include "WordList.h"
#include "NgramList.h"
#include "NgramSTL.h"

#include <bits/stdc++.h>

using namespace std;
std::map<std::string, int> hashmap;
vector<pair<string, int> > vec;

list<int> *table;

/* You may NOT include any additional header files or declare any global variables. */
/* You may add data members to the class by adding them to NgramSTL.h */
/* You may add more methods to the class. Add the prototype to NgramSTL.h */
/* You can also add functions (outside of any class) to this file, but only */
/* if you absolutely are required to by the STL. */

/*
 * Ngrams
 *
 * Takes as input the size of the ngrams to be built and the list
 * of words to build the ngrams from and calls insertNgram to
 * insert the ngram into some collection object defined using a
 * C++ template class. You get to choose the template class.
 * You'll need to add a declaration of the template class object
 * to NgramSTL.h.  You may need more than one.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, WordList &wl)
{
      // Add any code you need to initialize whatever structure
      // you use to hold your ngrams.
      // Hash(int V);

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
 * If you didn't dynamically allocate any date then this
 * method stays empty.
 */
Ngrams::~Ngrams()
{
}

/*
 * insertNgram
 *
 * Inserts the ngram into whatever collection object you choose to hold
 * your ngrams. If the ngram is already in the collection, it should
 * simply increment the count.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(std::string s)
{
      if (hashmap.count(s) == 0)
      {
            hashmap.insert(pair<string, int>(s, 1));
      }
      else{
      int count = hashmap.at(s);
      hashmap.erase(hashmap.find(s));
      count = count + 1;
      hashmap.insert(pair<string, int>(s, count));
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
      // You will probably have this call inside of a loop

      if (inputToF == false)
      {
            sortByCount();
      }

      for (int i = 0; i < vec.size(); i++)
      {

            incrLst->addToNgramList(vec[i].first, vec[i].second);
            

      }


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
      // You will probably have this call inside of a loop
      if (inputToF == false)
      {
            sortByCount();
      }
      for (int i = vec.size() - 1; i >= 0; i--)
      {
            decrLst->addToNgramList(vec[i].first, vec[i].second);
      }
}

bool sortBySnd(const pair<string, int> &a, 
               const pair<string, int> &b) 
{ 
    return (a.second < b.second); 
}

void Ngrams::sortByCount()
{

      map<string, int>::iterator iter;
      for (iter = hashmap.begin(); iter != hashmap.end(); iter++)
      {
            vec.push_back(make_pair(iter->first, iter->second));
      }
      sort(vec.begin(), vec.end(), sortBySnd);

      inputToF = true;
}



