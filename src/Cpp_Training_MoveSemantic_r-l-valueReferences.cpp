//============================================================================
// Name        : Cpp_Training_MoveSemantic_r-l-valueReferences.cpp
// Author      : Nico
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>

using namespace std;

class IntVector {
	public:
		IntVector(int default_size = 0) : size(default_size), data(new int[size])
		{
			log("Constructor");  // Default Constructor Or Conversion Constructor with int parameter
			memset(data, 0, size);
		}

		IntVector(const IntVector& other): size(other.size), data(new int[size])
		{
			log("Copy Constructor");

			for (int i = 0; i < size; i++){
				data[i] = other.data[i];
			}
		}

		IntVector(IntVector&& other): size(other.size), data(new int[size])
		{
			log("Move Constructor");

			for (int i = 0; i < size; i++){
				data[i] = other.data[i];
			}
			delete [] other.data;
			other.data = nullptr;
			other.size = 0;
		}

		IntVector& operator=(const IntVector& other)
		{
			log("Copy Assignment");

//			if (this != &other){	// traditional solution

//				size = other.size;
//				delete [] data;
//				data = new int [size];
//				for (int i = 0; i < size; i++){
//					data[i] = other.data[i];
//				}
//			}

			IntVector tempIntVector(other);
			swap(size, tempIntVector.size);
			swap(data, tempIntVector.data);

			return *this;	// "this": address = value of current object = rvalue reference
							// "*this": address = value of current object, but converted to be an lvalue reference
		}

		IntVector& operator=(IntVector&& other)
		{
			log("Move Assignment");

//			if (this != &other) {	// traditional solution
//				size = other.size;
//				delete [] data;
//				data = new int [size];
//				for (int i = 0; i < size; i++){
//					data[i] = other.data[i];
//				}
//				other.size = 0;
//				delete [] other.data;
//				other.data = nullptr;
//			}

			swap(size, other.size);
			swap(data, other.data);

			return *this;	// "this": address = value of current object = rvalue reference
							// "*this": address = value of current object, but converted to be an lvalue reference
		}

		int& operator[] (int index){
//			if (index < size){			// needs out of array check
				return data[index];
//			}
//			return -1;
		}

		int getSize() {
			return size;
		}

		~IntVector()
		{
			log("Destructor");

			if (data){
				delete [] data;
				data = nullptr;
			}
		}

		friend ostream& operator<< (ostream&, IntVector&);

	private:
		void log(string output){
			cout << "object at address "<< this << ": " << output << endl;
		}

		int size;
		int* data;
};

ostream& operator<< (ostream& output, IntVector& intVector){
	output << &intVector << endl;
	output << "\tsize: " << intVector.size << endl;
	for (int i = 0; i < intVector.size; i++){
		output << "\tdata[" << i << "]:" << intVector.data[i] << endl;
	}
	return output;
}

int main() {
	IntVector intVectorA;
	IntVector intVectorB(15);
	for (int i = 0; i < intVectorB.getSize(); i++){
		intVectorB[i] = i % 5;
	}

	cout << "intVectorA: " << intVectorA;
	cout << "intVectorB: " << intVectorB;

	cout << "...begin assigning lvalue to an lvalue" << endl;
	cout << "intVectorA = intVectorB;" << endl;
	intVectorA = intVectorB;
	cout << "...end assigning lvalue to an lvalue" << endl;

	cout << "intVectorA: " << intVectorA;

	cout << endl;

	cout << "...begin assigning rvalue to an lvalue" << endl;
	cout << "intVectorA = IntVector(5);" << endl;
	intVectorA = IntVector(5);
	cout << "...end assigning rvalue to an lvalue" << endl;

	cout << "intVectorA: " << intVectorA;

	return 0;
}
