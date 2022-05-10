
//Lots of STL header files included here.
//You shouldn't have to include any others.
#include <iostream>
#include <set>
#include <string>
#include <array>
#include <iterator>
#include <list>
#include <tuple>
#include <utility>
#include <map>
#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>


#define TABLESIZE 1997
//You will need to add more method headers and data members
//to the class declaration below.
class Ngrams 
{
   private:
      int ngramSz;
      void insertNgram(std::string s);
       bool inputToF = false;


   public:
      Ngrams(int ngramSz, WordList & wl);
      ~Ngrams();
      void addIncreasing(NgramList * );
      void addDecreasing(NgramList * );
      void sortByCount();


};

