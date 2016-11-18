#ifndef TESTS_CPP
#define TESTS_CPP
#include <iostream>
#include "string.hpp"
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
using std::cout;
using std::endl;


void string_test(){
	try{
	String first("one");
	String other_first;
	assert(other_first.empty());
	assert(first.back()=='e');
	assert(first.front()=='o');
	assert(first.at(1) == 'n');
	other_first = first;
	size_t first_len = strlen(first.c_str());
	assert(first_len == other_first.length());
	other_first.push_back('c');
	assert(other_first.length() == first_len+1);
	cout<<first<<endl;
	String second = "second";
	assert(second.find('q')==-1);
	assert(second.find('c', 3) == -1);
	second.resize(50);
	assert(second.capacity() == 50);
	size_t second_old_len = second.length();
	second +=first;
	assert(second.length()==second_old_len+first_len);
	String numbers = "one two three  four five six seven eight nine ten";
	assert(numbers.find("two"));
	assert(numbers.find("two", 10)==-1);
	String str1 = "This is 1 string";
	String str2 = "This is othother1 string";
	str1.swap(str2);
	cout<<str1<<endl;
	String str3 = str1+str2;
	cout<<str3<<endl; 
	}catch(std::logic_error &e){
		throw e;
	}catch(std::bad_alloc const& ba){
		throw ba;
	}catch(...){
		throw;
	}
}


#endif