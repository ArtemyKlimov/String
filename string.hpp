#ifndef STRING_HPP
#define STRING_HPP
#include <iostream>
#include <stdexcept>


class String{
private:
	size_t s_len;
	size_t s_capacity;
	char * str;
public:
	//constructors
	String();//defaul constructor
	String(const char* src);
	String(char *src);
	String(char c);
	String(const String &str);//copy constructor
	String(size_t size);
	~String();
	//methods
	size_t length() const;
	size_t capacity() const;
	size_t countwords() const;
	int find(char c, int pos = 0) const;
	int find(const char* c_line, int pos = 0) const;
	bool empty() const;
	void resize(size_t new_size);
	void clear();
	char at(size_t index) const;
	char back() const;
	char front() const;
	void push_back(const char c);
	char pop_back();
	void swap(String &other_srt);
	void reverse();
	void display() const;
	String& toupper();//this unfortunately works only with ISO basic Latin alphabet
	char* c_str() const;
	void tolower();//not implemented
	void shrink_to_fit();
	String substr(size_t pos,size_t len) const;
	String& erase(size_t pos, size_t len);
	String& erase(size_t pos);
	String& insert(size_t pos,const String& other_srt);
	String& insert(size_t pos, const char* c_line);
	String& insert(size_t pos, char c);
	String& append(const String& other_srt);
	String& append(const char* c_line);
	String& append(char *c_line);
	//operators
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);
	String& operator = (const String& str);
	String& operator = (const char* c_line);
	String& operator = (char c);
	String& operator +=(const String& str);
	String& operator +=(const char* c_line);
	String& operator +=(char c);
	String operator+(const String& rhs) const;
	char& operator [](size_t index);
	bool operator < (const String& str);
	bool operator > (const String& str);
	bool operator ==(const String& str);
	bool operator >=(const String& str);
	bool operator <=(const String& str);
	bool operator !=(const String& str);
	bool operator ==(String& other_str);
	bool operator !=(String& other_str);

	class iterator{
	private:
		String& string_;
		size_t pos_;
		bool check();
	public:
		iterator(String& string,size_t pos);
		char operator*();
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator==(iterator const& a);
		bool operator!=(iterator const& a);
	};
	iterator begin();
	iterator end();

};

#endif