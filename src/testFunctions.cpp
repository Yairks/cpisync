#include <iostream>
#include "testFunctions.h"
using namespace std;

template<typename T>
std::vector<uint8_t> ToVec(T number)
{
    std::vector<uint8_t> v(sizeof(T));
    for (size_t i = 0; i < sizeof(T); i++) {
        v.at(i) = (number >> i*8) & 0xff;
    }
    return v;
}

uint64_t FromVec(std::vector<uint8_t> v) {
    uint64_t number = 0;
    if(v.size() == 0)
        return number;
    
    for(size_t i = 0; i < v.size(); i++) {
        number << i*8;
        number += v.at(i);
    }
    
    return number;
}

//creates an array of pointers to arrays of key value pairs
//input numEntries = number of key-value pairs to be created
//input maxVal = the maximum value of keys/values generated
int** createValues(int numEntries, int maxVal)
{
  srand(time(NULL));

  int** valueArray = new int*[numEntries];

  //loops through outer array of pointers and fills with pointers to 1x2 arrays with key value pairs
  //ensures that no repeat keys are produced
  for (int i = 0; i < numEntries; i++)
  {
    valueArray[i] = new int[2];

    bool newKeyPass;

    //initialize new key and generate new value
    int newKey;

    int newVal = rand() % (maxVal + 1);

    //continually generates key vals until a unique key is made
    do
    {
      newKeyPass = true;

      //generate potential new key
      newKey = rand() % (maxVal + 1);

      //checks through existing keys to determine if new key is unique
      for (int j = 0; j <= i; j++)
      {
        if (valueArray[j][0] == newKey)
        {
          newKeyPass = false;

          break;
        }
      }
    }
    while (!newKeyPass);

    //inserts the key-value pair into the larger array
    valueArray[i][0] = newKey;

    valueArray[i][1] = newVal;
  }

  //insertion sort the array by key value to ensure insertion into set is correct
  for (int i = 0; i < numEntries - 1; i++)
  {
    for (int j = i + 1; j < numEntries; j++)
    {
      if (valueArray[i][0] > valueArray[j][0])
      {
        int* tempArray = valueArray[i];
        valueArray[i] = valueArray[j];
        valueArray[j] = tempArray;
      }
    }
  }

  return valueArray;
}

//creates a multidimensional array of key value pairs
//keys are generated in increasing order from minval to minval+numEntries
//input numEntries = number of key-value pairs to be created
//input minVal = the minimum value of keys/values generated
int** createValues3(int numEntries, int minVal)
{
  //creates the matrix
  int** valueArray = new int*[numEntries];

  //creates/inserts key value pairs with keys from minVal to numEntries + minVal - 1
  //randomly generates  values between 0 and minval + i
  for (int i = 0; i < (numEntries); i++)
  {
    valueArray[i] = new int[2];

    int newVal = rand() % (i + minVal + 1);

    valueArray[i][0] = i + minVal;

    valueArray[i][1] = newVal;
  }

  return valueArray;
}

//creates an array of pointers to arrays of key value pairs (keys= not necessarily unique)
//input numEntries = number of key-value pairs to be created
//input maxVal = the maximum value of values generated
int** createValues5(int numEntries, int maxVal)
{
  srand(time(NULL));

  int** valueArray = new int*[numEntries];

  for (int i = 0; i < numEntries; i++)
  {
    valueArray[i] = new int[2];

    bool newKeyPass;

    int newKey;

    int newVal = rand() % (maxVal + 1);

      newKey = rand() % (maxVal + 1);

    valueArray[i][0] = newKey;

    valueArray[i][1] = newVal;
  }
  //sort the array by key
  for (int i = 0; i < numEntries - 1; i++)
  {
    for (int j = i + 1; j < numEntries; j++)
    {
      if (valueArray[i][0] > valueArray[j][0])
      {
        int* tempArray = valueArray[i];
        valueArray[i] = valueArray[j];
        valueArray[j] = tempArray;
      }
    }
  }

  return valueArray;
}


//inserts the entries generated by createValues() into the IBLT
//input: entries = array of arrays of key value pairs
//input: iblt = pointer to the iblt object
//input: numEntries = the number of key-value pairs being inserted into the iblt
void addEntries(int** entries, IBLT* iblt, int numEntries)
{
  for (int i = 0; i < numEntries; i++)
  {
    iblt->insert(entries[i][0], ToVec(entries[i][1]));
  }
}

//compares the set made by the IBLT during list values to the key-value pairs generated by createValues()
//input: positiveValues = set of key value pairs generated by IBLT during list values operation
//input: myEntries = multidimensional array of key value pairs that were inserted into the iblt
//input: numEntries = the number of entries originally inserted into the iblt
void compare(std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValues, int** myEntries, int numEntries)
{
  //creates new set with the key value pairs from myEntries
  std::set<std::pair<uint64_t, std::vector<uint8_t> > > entrySet;

  for (int i = 0; i < numEntries; i++)
  {
    entrySet.insert(std::make_pair(myEntries[i][0], ToVec(myEntries[i][1])));
  }

  //compares manually created set to iblt generated set
  //gives corresponding output to indicate success of list entries
  //states that listing entries was successful or counts the number of missing entries
  if (entrySet == positiveValues)
  {
    cout << "Successful Listing of All Entries" << endl;
  }
  else
  {
    int missingEntries = entrySet.size() - positiveValues.size();

    cout << missingEntries << " Entries were not listed." << endl;
  }

}

//compares the set made by the IBLT during list values to the key-value pairs generated by createValues()
//input: positiveValues = set of key value pairs generated by IBLT during list values operation
//input: myEntries = multidimensional array of key value pairs that were inserted into the iblt
//input: numEntries = the number of entries originally inserted into the iblt
//output: returns true if all of the inserted key/value pairs were successfully listed out during list entries
bool compare2(std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValues, int** myEntries, int numEntries)
{
  std::set<std::pair<uint64_t, std::vector<uint8_t> > > entrySet;

  for (int i = 0; i < numEntries; i++)
  {
    entrySet.insert(std::make_pair(myEntries[i][0], ToVec(myEntries[i][1])));
  }

  if (entrySet == positiveValues)
  {
    return true;
  }
  else
  {
    return false;
  }

}

//Generates a vector of keys that are unique to one of the sets
//input: aVals, bVals = multidimensional arrays of key value pairs
//input: numEntries = number of pairs in each multidimensional array
//output: vector = keys that are only found in one of the sets
vector<int*> makeDiffVector(int** aVals, int** bVals, int numEntries)
{
  //sort the array by key
  for (int i = 0; i < numEntries - 1; i++)
  {
    for (int j = i + 1; j < numEntries; j++)
    {
      if (aVals[i][0] > aVals[j][0])
      {
        int* tempArray = aVals[i];
        aVals[i] = aVals[j];
        aVals[j] = tempArray;
      }
    }
  }

  //sorts the array by key
  for (int i = 0; i < numEntries - 1; i++)
  {
    for (int j = i + 1; j < numEntries; j++)
    {
      if (bVals[i][0] > bVals[j][0])
      {
        int* tempArray = bVals[i];
        bVals[i] = bVals[j];
        bVals[j] = tempArray;
      }
    }
  }

  //creates a vector of keys that are only in one of the arrays
  vector<int*> differences;

  bool unique = false;

  //iterates through all keys in aVals to check if they are also in bVals
  for (int k = 0; k < numEntries; k++)
  {
    for (int m = 0; m < numEntries; m++)
    {
      if (aVals[k][0] == bVals[m][0])
      {
        unique = false;

        break;
      }
      else
      {
        unique = true;
      }
    }

    //if value is only in aVal, adds the key to differences
    if (unique)
    {
      differences.push_back(aVals[k]);
    }
  }

  //ierates through all keys in bVals to check if they are also in aVals
  for (int k = 0; k < numEntries; k++)
  {
    for (int m = 0; m < numEntries; m++)
    {
      if (bVals[k][0] == aVals[m][0])
      {
        unique = false;

        break;
      }
      else
      {
        unique = true;
      }
    }

    //if the key is only in bVals, it adds it ot differences
    if (unique)
    {
      differences.push_back(bVals[k]);
    }
  }

  return differences;

}
