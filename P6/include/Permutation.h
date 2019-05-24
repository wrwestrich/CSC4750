#if !defined PERMUTATION
#define PERMUTATION

#include "Random.h"

#include "ListArray.h"

#include "Integer.h"

#include "String_.h"

namespace CSC1310
{
class Permutation
{
   private:
      int r;
	  int n;
	  
	  ListArray<Integer>* permutation;

   public:
      Permutation(int r, int n);
      virtual ~Permutation();
	  
	  void writeFile(String& file_name);
	  void readFile(String& file_name);
	  
      int next();
	  bool hasNext();
};
}

#endif
