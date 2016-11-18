#include "tests.cpp"

using namespace std;
int main()
{
	try{
	string_test();
	}catch(std::logic_error &e){
		std::cout<<"\nerror: "<<e.what()<<std::endl;
	}catch(std::bad_alloc const& ba){
		std::cout<<"caught: "<<ba.what()<<std::endl;
	}catch(...){
		std::cout<<"Unrecognized error occured"<<std::endl;
	}

	return 0;
}

