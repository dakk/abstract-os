#ifndef STRING_HPP
#define STRING_HPP

/**
 * String class
 */
class string
{
	public:
		string();
		string(char *);
		~string();
		
		char *c_str();
		unsigned size();
		
		
		bool operator==(string &strr);
		string & operator=(string &strr);
		string & operator=(char *strr);
		string & operator+(string &strr);
		string & operator+(char *strr);

		
	private:
		char *str;					///< String data
		unsigned ssize;				///< String size
};


#endif
