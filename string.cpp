#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include "string.hpp"
//constructors
String::String() : s_len(0), s_capacity(2) , str(new char[s_capacity]){}//default constructor

String::String(const char c_line[])
	: s_len(strlen(c_line))
	, s_capacity(s_len*2)
	, str(new char[s_capacity]){
		for(size_t i = 0; i<s_len; ++i )
			str[i] = c_line[i];
			str[s_len] = '\0';
	}

String::String(char c)
	: s_len(1)
	,s_capacity(3)
	,str(new char[s_capacity]){
	str[0] = c;
	str[1] = '\0';
}

String::String(char *c_line)
	: s_len(strlen(c_line))
	, s_capacity(s_len*2)
	, str(new char[s_capacity]){
		for(size_t i = 0; i<s_len; ++i)
			str[i] = c_line[i];
			str[s_len] = '\0';
	}

String::String(const String &other_str)
	: s_len(other_str.s_len)
	, s_capacity(other_str.s_capacity)
	, str(new char[s_capacity]){
		for(size_t i = 0; i<s_len; ++i )
			str[i] = other_str.str[i];
		str[s_len] = '\0';
	}

String::String(size_t size): s_len(0), s_capacity(size) , str(new char[s_capacity]){}

String:: ~String(){
	delete[] str;
}

size_t String::length() const{
	return s_len;
}
size_t String::capacity() const{
	return s_capacity;
}

size_t String::countwords() const{
	if(empty()) return 0;
	size_t count = 1, index = 0;
	for(size_t i = 0; i < s_len;  ++i){
		if(!isspace(str[i])){
			index = i;
			break;
		}
	}
	for(size_t i = index; i<s_len; ++i){
		if((isspace(str[i])) && !isspace(str[i-1]))
			count++;
	}
	if(isspace(str[s_len-1]))
		--count;
	return count;
}
int String::find(char c, int pos) const{
	if(pos>=static_cast<int>(s_len) || pos< 0){
		throw std::out_of_range("find(): invalid index");
	}
	for(int i = pos; i<static_cast<int>(s_len); ++i)
		if(str[i] == c)
			return i;
	return -1;
}
int String::find(const char* c_line, int pos) const{
	if(pos>=static_cast<int>(s_len) || pos< 0){
		throw std::out_of_range("find(): invalid index");
	}
	int c = 0;
	for(int i = pos; i<static_cast<int>(s_len); ++i){
		c = 0;
		int it = i;
		for(int j = 0; j<static_cast<int>(strlen(c_line)); ++j){
			if(str[it] == c_line[j]){
				it++;
				c++;
			}
		}
		if(c==static_cast<int>(strlen(c_line)))
			return i;
	}
	return -1;
}


bool String::empty() const{
	return s_len == 0;
}

void String::resize(size_t new_size){
	if(s_len >= new_size){
		throw std::out_of_range("resize(): very small value of new size");
	}
	char temp[s_len];
	for(size_t i = 0; i< s_len; i++){
		temp[i] = str[i];
	}
	delete[] str;
	try{
		str = new char[new_size];
	}catch(std::bad_alloc& ba){
		throw ba;
	}
	for(size_t i = 0; i< s_len; i++){
		str[i] = temp[i];
	}
	str[s_len] = '\0';
	s_capacity = new_size;
}
void String::clear(){
	delete [] str;
	s_len = 0;
	s_capacity = 2;
	str = new char[s_capacity];
}

char String::at(size_t index) const{
	if(s_len<index){
		throw std::out_of_range("at(): incorrect index");
	}
	return str[index];
}
char String::back() const{
	if(s_len == 0){
		throw std::out_of_range("back(): string is empty");
	}
	return str[s_len-1];

}
char String::front() const{
	if(s_len == 0){
		throw std::out_of_range("front(): string is empty");
	}
	return str[0];
}

void String::push_back(const char c){
	if(s_capacity - s_len < 2){
		char temp[s_len];
		for(size_t i = 0; i<s_len; ++i){
			temp[i] = str[i];
		}
		delete[] str;
		str = new char[s_capacity*2];
		for(size_t i = 0; i<s_len; ++i){
			str[i] = temp[i];
		}
	}
	s_len ++;
	str[s_len-1] = c;
	str[s_len] = '\0';
}

char String::pop_back(){
	if(s_len == 0){
		throw std::out_of_range("pop_back(): called for empty string");
	}
	char last = str[s_len-1];
	str[s_len-1] = '\0';
	s_len--;
	return last;
}

char* String::c_str() const{
	return str;
}


void String::display() const{
	std::cout<<str<<std::endl;
}

void String::swap(String &other_srt){
	size_t temp_len = other_srt.s_len;
	size_t temp_cap = other_srt.s_capacity;
	char* temp_arr = other_srt.str;

	other_srt.s_len = this->s_len;
	other_srt.s_capacity=this->s_capacity;
	other_srt.str = this->str;

	this->s_len = temp_len;
	this->s_capacity = temp_cap;
	this->str = temp_arr;
}

String& String::append(const String& other_srt)
{
	return *this+=other_srt;
}

String& String::append(const char* c_line)
{
	return *this+=c_line;
}

String& String::append(char *c_line)
{
	return *this+=c_line;
}

String& String::insert(size_t pos,const String& other_srt)
{
	if(pos > s_len){
		throw std::out_of_range("insert(): invalid index");
	}
	size_t new_len = s_len+other_srt.s_len;
	char arr[new_len];
	for(size_t i = 0; i<pos; ++i){
		arr[i] = str[i];
	}
	for(size_t i = pos, j = 0; i<pos+other_srt.s_len; ++i, ++j){
		arr[i] = other_srt.str[j];
	}
	for(size_t i = pos+other_srt.s_len, j = pos; j<s_len; j++, i++){
		arr[i] = str[j];
	}
	delete[] str;
	s_len = new_len;
	s_capacity = s_len*2;
	try{
		str = new char[s_capacity];
	}catch(std::bad_alloc &ba){
		throw ba;
	}
	for(size_t i = 0; i<s_len; ++i){
		str[i] = arr[i];
	}
	str[s_len] = '\0';
	return *this;
}

String& String::insert(size_t pos, char c){
	if(pos > s_len){
		throw std::out_of_range("insert(): invalid index");
	}
	if(s_capacity-s_len<2){
		resize(s_capacity*2);
	}
	for(size_t i =s_len; i>pos; --i){
		str[i] = str[i-1];
	}
	str[pos] = c;
	s_len+=1;
	str[s_len] = '\0';
	return *this;
}
String& String::insert(size_t pos, const char* c_line){
	if(pos > s_len){
		throw std::out_of_range("insert(): invalid index");
	}
	size_t len = strlen(c_line);
	if(s_capacity<s_len+len){
		resize((s_len+len)*2);
	}
	for(size_t i =s_len; i>=pos; --i){
		str[i+len] = str[i];
	}
	for(size_t i = pos, j = 0; i <pos+len; ++i, j++){
		str[i] = c_line[j];
	}
	s_len = s_len+len;
	str[s_len] = '\0';
	return *this;
}

void String::shrink_to_fit(){
	char temp[s_len];
	for(size_t i = 0; i <s_len; ++i)
		temp[i] = str[i];
	delete[] str;
	s_capacity = s_len+1;
	try{
		str = new char[s_capacity];
	}catch(std::bad_alloc& ba){
		throw ba;
	}
	for(size_t i = 0; i <s_len; ++i)
		str[i] = temp[i];
	str[s_len] = '\0';
}
String& String::erase(size_t pos, size_t len){
	if(pos > s_len){
		throw std::out_of_range("erase(): invalid index");
	}
	char temp[s_len];
	for(size_t i= 0; i<s_len; ++i)
		temp[i] = str[i];
	s_len -=len;
	for(size_t i = pos; i<s_len;++i)
		temp[i] = temp[i+len];
	delete[]str;
	s_capacity=s_len*2;
	try{
		str = new char[s_capacity];
	}catch(std::bad_alloc& ba){
		throw ba;
	}
	for(size_t i = 0; i<s_len; ++i)
		str[i] = temp[i];
	str[s_len] = '\0';
	return *this;
}

String& String::erase(size_t pos){
	if(pos > s_len){
		throw std::out_of_range("erase(): invalid index");
	}
	char *temp = new char[pos];
	for(size_t i= 0; i<pos; ++i)
		temp[i] = str[i];
	delete[] str;
	s_len = pos;
	s_capacity=s_len*2;
	try{
		str = new char[s_capacity];
	}catch(std::bad_alloc& ba){
		throw ba;
	}
	for(size_t i = 0; i<s_len; ++i)
		str[i] = temp[i];
	str[s_len] = '\0';
	delete[] temp;
	return *this;
}

String String::substr(size_t pos,size_t len) const{
	if(pos > s_len || pos+len > s_len){
		throw std::out_of_range("substr(): invalid index");
	}
	char temp[len];
	for(size_t i = pos, j = 0; i<pos+len; ++i,  ++j){
		temp[j] = str[i];
	}
	temp[len] = '\0';
	String substring(temp);
	std::cout<<substring<<std::endl;
	std::cout<<substring.capacity()<<std::endl;
	std::cout<<substring.length()<<std::endl;
	return substring;
}

/*
String& String::toupper(){
	for(size_t i = 0; i<s_len;++i)
		if(str[i] >=97 &&str[i] <=122)
			str[i] -=32;
		return *this;
}
	void reverse();
	void tolower();
	//operators
	*/
std::istream& operator>>(std::istream& is, String& obj){

	obj.clear();
	char buf[2000];
	is.getline(buf, sizeof(buf));
	obj.s_len = strlen(buf);
	obj.s_capacity = obj.s_len*2;
	try{
	obj.str = new char[obj.s_capacity];
	}catch(std::bad_alloc &ba){
		throw ba;
	}
	for(size_t i = 0;  i < obj.s_len; ++i){
		obj.str[i] = buf[i];
	}
	obj.str[obj.s_len] = '\0';
	return is;
}
std::ostream& operator<<(std::ostream& os, const String& str){
	os <<str.str;
	return os;
}

String String::operator+(const String& rhs) const
{
	String temp(s_capacity+rhs.s_capacity);
	temp.s_len = s_len+rhs.s_len;
	for(size_t i = 0; i < s_len; ++i)
		temp[i] = str[i];
	for(size_t i = s_len, j = 0; i<temp.s_len; ++i, ++j)
		temp[i] = rhs.str[j];
	temp[temp.s_len] = '\0';
	return temp;
}

String& String::operator = (const String& other_str){
	delete[] str;
	s_len = other_str.s_len;
	s_capacity = other_str.s_capacity;
	try{
		str = new char[s_capacity];
	}catch(std::bad_alloc& ba){
		throw ba;
	}
	for(size_t i =0; i<s_len;++i)
	{
		str[i] = other_str.str[i];
	}
	str[s_len] = '\0';
	return *this;
}
String& String::operator = (const char* c_line){
	delete[] str;
	size_t len = strlen(c_line);
	s_len = len;
	s_capacity = len*2;
	try{
		str = new char[s_capacity];
	}catch(std::bad_alloc& ba){
			throw ba;
		}
	for(size_t i =0; i<len;++i)
	{
		str[i] = c_line[i];
	}
	str[s_len] = '\0';
	return *this;
}
String& String::operator = (char c){
	delete [] str;
	s_len = 1;
	s_capacity = 2;
	str[0] = c;
	str[1] = '\0';
	return *this;
}
char& String::operator [](size_t index){
	return str[index];
}
bool String::operator ==(const String& other_str){
	if(s_len != other_str.s_len) return false;
	for(size_t i = 0; i < s_len; i++){
		if(this->str[i] != other_str.str[i]) return false;
	}
	return true;
}

bool String::operator ==(String& other_str){
	if(s_len != other_str.s_len) return false;
	for(size_t i = 0; i < s_len; i++){
		if(this->str[i] != other_str.str[i]) return false;
	}
	return true;
}
bool String::operator !=(const String& other_str){	
	if(s_len != other_str.s_len) return true;
	for(size_t i = 0; i < s_len; i++){
		if(this->str[i] != other_str.str[i]) return true;
	}
	return false;
}

bool String::operator !=(String& other_str){	
	if(s_len != other_str.s_len) return true;
	for(size_t i = 0; i < s_len; i++){
		if(this->str[i] != other_str.str[i]) return true;
	}
	return false;
}
bool String::operator > (const String& other_str){
	if(strcmp(this->str, other_str.str) > 0) return true;
	return false;
}

bool String::operator < (const String& other_str){
	if(strcmp(this->str, other_str.str) > 0) return false;
	return true;
}

bool String::operator >=(const String& other_str)
{
	if(strcmp(this->str, other_str.str) >= 0) return true;
	return false;
}
bool String::operator <=(const String& other_str)
{
	if(strcmp(this->str, other_str.str) <= 0) return true;
	return false;
}
String& String::operator +=(const String& other_str){
	size_t new_size = this->s_len+other_str.s_len;
	if(this->s_capacity <= new_size){
		this->s_capacity = new_size*2;
		char temp[this->s_len];
		for(size_t i = 0; i<s_len; ++i)
		{
			temp[i] = this->str[i];
		}
		delete[] str;
		str = new char[s_capacity];
		for(size_t i = 0; i<s_len; ++i){
			this->str[i] = temp[i];
		}
	}
	size_t k = 0;
	for(size_t i = this->s_len; i<new_size; ++i){
			str[i] = other_str.str[k];
			k++;
	}
	this->s_len = new_size;
	str[new_size] = '\0';
	return *this;
}

String& String::operator +=(const char* c_line){
	size_t new_len = s_len + strlen(c_line);
	if(s_capacity <=new_len){
		s_capacity = new_len*2;
		char temp[s_len];
		for(size_t i = 0; i<s_len; ++i)
		{
			temp[i] = str[i];
		}
		delete[] str;
		str = new char[s_capacity];
		for(size_t i = 0; i<s_len; ++i){
			this->str[i] = temp[i];
		}
	}
	for(size_t i = s_len, k = 0; i<new_len; ++i, ++k){
			str[i] = c_line[k];
	}
	s_len = new_len;
	str[new_len] = '\0';
	return *this;
}

String& String::operator +=(char c){
	this->push_back(c);
	return *this;
}


	/*
	*/

String::iterator::iterator(String& string, size_t pos) : string_(string), pos_(pos){}

bool String::iterator::check(){
	return (pos_ <=string_.s_len && pos_ != 0);
}

char String::iterator::operator*(){
	if(pos_ < string_.s_len)
		return string_.str[pos_];
	throw std::out_of_range("reference to invalid iterator");	
}

String::iterator& String::iterator::operator++(){
	if(pos_ >= string_.s_len){
		throw std::out_of_range("iterator++: very big value");
	}
	pos_++;
	assert(check());
	return *this;
}

String::iterator String::iterator::operator++(int){
	String::iterator tmp = *this;
	++*this;
	return tmp;
}

String::iterator& String::iterator::operator--(){
	if(pos_ == 0){
		throw std::out_of_range("iterator--():very small value");
	}
	pos_--;
	return *this;
}

String::iterator String::iterator::operator--(int){
	String::iterator tmp = *this;
	--*this;
	return tmp;
}

bool String::iterator::operator==(iterator const& a){
	return(&string_ == &a.string_ && pos_ == a.pos_);
}

bool String::iterator::operator !=(iterator const& a){
	if(&string_ == &a.string_ && pos_ == a.pos_)
		return false;
	return true;
}
String::iterator String::begin(){
	return String::iterator(*this, 0);
}

String::iterator String::end(){
	return String::iterator(*this, s_len);
}
