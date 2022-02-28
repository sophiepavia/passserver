#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>

using namespace std;

namespace cop4530 {

template <typename K, typename V>
	class HashTable {
		// max_prime is used by the helpful functions provided
		// to you.
		static const unsigned int max_prime = 1301081;
		// the default_capacity is used if the initial capacity 
		// of the underlying vector of the hash table is zero. 
		static const unsigned int default_capacity = 11;
		
		public: 
			HashTable(size_t size = 101);	//constructor
			~HashTable();					//desctructor
			
			bool contains(const K & k) const;
			bool match(const std::pair<K, V> &kv) const;
			bool insert(const std::pair<K, V> & kv);
			bool insert (std::pair<K,  V> && kv);
			bool remove(const K & k);
			
			void clear();
			size_t size();
			bool load(const char *filename);
			void dump();
			bool write_to_file(const char *filename) const;
			
		
		private:
			vector<list<pair<K,V>>> theLists;		//the array of the lists
			int currentSize;
			
			void makeEmpty();
			void rehash();
			
			size_t myhash(const K &k) const;
			
			unsigned long prime_below (unsigned long);
			void setPrimes(vector<unsigned long>&);
			
		};
		
#include "hashtable.hpp"

}//end of namespace 4530

#endif
