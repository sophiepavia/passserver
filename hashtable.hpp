template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
  theLists.resize(prime_below(size));
  currentSize = 0;
}//end of constructor

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
  theLists.clear();
}//end of destructor

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const
{
  auto & whichList = theLists[myhash(k)];
  auto itr = whichList.begin();
  for(auto & item : whichList)
  {
    if(item.first == k)
      return true;
    itr++;
  }
  return false;
}//end of contains

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
{
  auto & whichList = theLists[myhash(kv.first)];
  return (find(begin(whichList), end(whichList), kv) != end(whichList));
}//end of match

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv)
{
  auto & whichList = theLists[myhash(kv.first)];
  if(find(begin(whichList), end(whichList), kv) != end(whichList))
    return false;
  //if password is being changed
  if(contains(kv.first))
  {
    pair<K,V> newPair;
    newPair.first = kv.first;
    newPair.second = kv.second;
    remove(kv.first);
    whichList.push_back(kv);
      
    if(++currentSize > theLists.size())
      rehash();
    return true;
  }
  
  whichList.push_back(kv);
  //if no more space in hashtable
  if(++currentSize > theLists.size())
    rehash();
    
  return true;
}//end of insert

template <typename K, typename V>
bool HashTable<K, V>::insert (std::pair<K,  V> && kv)
{
  auto & whichList = theLists[myhash(kv.first)];
  if(find(begin(whichList), end(whichList), kv) != end(whichList))
    return false;
  //if password is being changed
  if(contains(kv.first))
  {
    pair<K,V> newPair;
    newPair.first = kv.first;
    newPair.second = kv.second;
    remove(kv.first);
    whichList.push_back(kv);
      
    if(++currentSize > theLists.size())
      rehash();
    return true;
  }
  
  whichList.push_back(std::move(kv));

  if(++currentSize > theLists.size())
    rehash();
    
  return true;
}//end of move insert

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
  
  auto & whichList = theLists[myhash(k)];
  auto itr = whichList.begin();
  //check to see if in list first
  if(contains(k))
  {
    for(auto & item: whichList)
    {
      if(item.first == k)
      {
        whichList.erase(itr);
        currentSize--;
        return true;
      }
      else 
        itr++;
    }
  }
  return false;
  
}//end of remove

template <typename K, typename V>
void HashTable<K, V>::clear()
{
  makeEmpty();
}//end of clear

template <typename K, typename V>
size_t HashTable<K, V>::size()
{
  return currentSize;
}//end of clear

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
  ifstream in1;
  in1.clear();
  
  in1.open(filename);
  
  if(!in1)
    return false;
  
  K key;
  V value;
  pair<K, V> myPair;
  while(in1)
  {
    in1 >> key >> value;
    myPair.first = key;
    myPair.second = value;
    
    insert(myPair);
  }
  in1.close();
  return true;
}//end of load

template <typename K, typename V>
void HashTable<K, V>::dump()
{
  int i =0;
  for(auto & thisList: theLists)
  {
    cout << "v[" << i << "]: ";
    for(auto & item: thisList)
    {
      cout << item.first << " " << item.second;
      if(item != thisList.back())
        cout << ":";
    }
    cout << endl;
    i++;
  }
  
}//end of dump

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const
{
  ofstream myFile;
  myFile.open(filename);
  myFile.clear();
  
  if(!myFile)
    return false;

  for(auto & thisList: theLists)
  {
    if(!thisList.empty())
    {
      for(auto & item: thisList)
      {
        myFile << item.first << " " << item.second << endl;
        
      }
    }
  }
  myFile.close();
  return true;
}//end of write_to_file

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
  for(auto & thisList: theLists)
    thisList.clear();
  
}//end of makeEmpty

template <typename K, typename V>
void HashTable<K, V>::rehash()
{
  vector<list<pair<K,V>>> oldLists = theLists;
  
  theLists.resize(prime_below(2*theLists.size()));
  for(auto & thisList : theLists)
    thisList.clear();
  
  currentSize = 0;
  pair<K, V> mypair;
  for(auto & thisList: oldLists)
    for(auto & item : thisList)
       insert(std::move(item));
    
}//end of rehash

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
  static hash<K> ht;
  return ht(k)% theLists.size();
  
}//end of myhash



// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
  {
    std::cerr << "** input too large for prime_below()\n";
    return 0;
  }
  if (n == max_prime)
  {
    return max_prime;
  }
  if (n <= 1)
  {
    std::cerr << "** input too small \n";
    std::cerr << "set to default capacity\n";
    std::cerr << "11";
    return 11;
  }
  
  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
  {
    if (v[n] == 1)
    {
      if(n != 101)
        cout << n;
      return n;
    }
      
    --n;
  }
  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
  {
    if (vprimes[i] == 1)
      for(j = i + i ; j < n; j += i)
        vprimes[j] = 0;
  }
}

