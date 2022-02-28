#include "passserver.h"

PassServer::PassServer(size_t size)
{
	ht = HashTable<string,string>(size);
}//end of constructor

PassServer::~PassServer()
{
	ht.clear();
}//end of destructor

bool PassServer::load(const char *filename)
{
	return ht.load(filename);
}//end of load

bool PassServer::addUser(std::pair<string,  string> & kv)
{
	//encrypt before insert
	kv.second = encrypt(kv.second);
	return ht.insert(kv);
}//end of addUser

bool PassServer::addUser(std::pair<string, string> && kv)
{
	//encrypt before insert
	kv.second = encrypt(kv.second);
	return ht.insert(std::move(kv));
}//end of addUser move

bool PassServer::removeUser(const string & k)
{
	return ht.remove(k);
}//end of remove user

bool PassServer::changePassword(const std::pair<string, string> &p, const string & newpassword)
{
	string p1 = encrypt(p.second);
	string p2 = encrypt(newpassword);
	//if username is not in hash
	if(!ht.contains(p.first))
		return false;
	//if the theres no need to change password
	if(p.second == newpassword)
		return false;
	
	pair<string, string> encryptedP1;
	encryptedP1.first = p.first;
	encryptedP1.second = p1;
	//if exisitng password is in hash
	if(ht.match(encryptedP1))
	{
		pair<string, string> newPair;
		newPair.first = p.first;
		newPair.second = p2;
		ht.insert(newPair);
		return true;
	}
	return false;	
			
}//end of changePassword

bool PassServer::find(const string & user)
{
	return ht.contains(user);
}//end of find

void PassServer::dump()
{
	ht.dump();
}//end of dump

size_t PassServer::size()
{
	return ht.size();
}//end of size

bool PassServer::write_to_file(const char *filename)
{
	return ht.write_to_file(filename);
}//end of write to file

string PassServer::encrypt(const string & str)
{
	char salt[] = "$1$########";
	string key = str;

	char * password = new char [100];
	strcpy(password, crypt(key.c_str(), salt));
	//cut off salt by each $
	password = strtok(password, "$");
	password = strtok(NULL, "$");
	password = strtok(NULL, "$");
	return password;
}//end of encrypt

