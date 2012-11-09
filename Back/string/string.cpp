extern "C"
{
	#include <mm/mm.h>
	#include <klibc/string.h>
}
#include <string.hpp>


/**
 * Destroy a string
 */
string::~string()
{
	mm_free(str);
}


/**
 * Create a string
 */
string::string()
{
	ssize = 0;
}


/**
 * Create a string with initial buffer
 */
string::string(char *start_string)
{
	str = (char *) mm_alloc(strlen(start_string));
	strcpy(str, start_string);
	ssize = strlen(str);	
}


/**
 * Get the size  of the string
 */
unsigned 
string::size()
{
	return ssize;
}


/**
 * Return string data pointer
 */
char *
string::c_str()
{
	return str;
}



/**
 * Assign a string to another string
 */
string& 
string::operator=(string &strr)
{
	mm_free(str);
	
	str = strr.c_str(); 
	ssize = strlen(str);
	
	return *this;
}


/**
 * Check if two strings are equal
 */
bool 
string::operator==(string &strr)
{
	if(strcmp(this->c_str(), strr.c_str()) == 0)
		return true;
	
	return false;
}



/**
 * Assign char* to a string
 */
string& 
string::operator=(char *strr)
{
	mm_free(str);
	
	str = (char *) mm_alloc(strlen(strr));
	strcpy(str, strr);
	ssize = strlen(str);
	
	return *this;
}



/**
 * Concatenate two strings
 */
string& 
string::operator+(string &strr)
{
	char *temp = (char *) mm_alloc(ssize + strr.size());
	strcpy(temp, str);
	strcat(temp, strr.c_str());
	ssize = ssize + strr.size();
	mm_free(str);
	str = temp;
	
	return *this;
}




/**
 * Concatenate a char* to a string
 */
string& 
string::operator+(char *strr)
{
	char *temp = (char *) mm_alloc(ssize + strlen(strr));
	strcpy(temp, str);
	strcat(temp, strr);
	ssize = ssize + strlen(strr);
	mm_free(str);
	str = temp;
	
	return *this;
}
