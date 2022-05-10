// You will need to add one or more typedefs and
// declarations for whatever structure you use to hold
// your ngrams. You will also need to add prototypes
// for any new methods you add to the class.

#define TABLESIZE 1997 // a prime number for our hashtable size
#define SORTSIZE 97
class Ngrams
{

   struct NodeGram
   {
      std::string ngramString;
      int count;
      struct NodeGram * nextngraminHT; //
      struct NodeGram *nextngraminSortedArray; //
   };

   typedef struct NodeGram NodeGram_t;

private:
   NodeGram_t * first;
   int ngramSz;
   void insertNgram(std::string s);
   
   NodeGram *hashTable[TABLESIZE];
   NodeGram *countArray[50];
   NodeGram * sortedArray[TABLESIZE];

public:
bool inputToF = false;
   Ngrams(int ngramSz, WordList &wl);
   ~Ngrams();
   void addIncreasing(NgramList *);
   void addDecreasing(NgramList *);
   int hashAlgorithm(std::string inputString);
   void sortByCount();
};
