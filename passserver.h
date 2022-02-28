#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>
#include <unistd.h>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

	class PassServer {
		public:
			PassServer(size_t size = 101);
			~PassServer();
			
			bool load(const char *filename);
			bool addUser(std::pair<string,  string> & kv);
			bool addUser(std::pair<string, string> && kv);
			bool removeUser(const string & k);
			bool changePassword(const std::pair<string, string> &p, const string & newpassword);
			bool find(const string & user);
			
			void dump();
			
			size_t size();
			
			bool write_to_file(const char *filename);
			
		private:
			HashTable<string, string> ht;
			string encrypt(const string & str);
		
		
		
	};
#endif