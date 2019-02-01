#include <iostream>
#include <fstream>
//#include <time.h>
#include <math.h>
#include "rbtree.h"

using namespace std;

int main(int argc, char* argv[]){
	if(argc <= 1 ){
		cout << "Enter a file name\nuse as: ./a.exe file_name\neg: ./a.out primes.txt" << endl;
		return 0;
	}

	ifstream primes(argv[1], ios::in);
	
	unsigned long prime, n = 0;
	unsigned long long countt = 0;

	rbtree<unsigned long> tree;
	cout << "builiding tree...\n";

	while(primes>>prime){
		countt++;
		tree.insert(prime);
	}
	
	cout << "total primes: " << countt << endl;
	cout << "log(" << countt << ") = " << floor((long double)log2(countt)) << endl;
	cout << "the tree height is: " << tree.height() << endl;
	cout << "the tree black height is: " << tree.bh() << endl;

	// ***************** take input and print requres data ****************
	cout << "\nEnter n: ";
	cin >> n;
	while(n != 0){
		rb_tree_node<unsigned long>* search_result = tree.search_lower_bound(n);
		if(search_result->data == n){
			cout << n << " is a prime" << endl;
		}else{
			cout << "The next prime is " << search_result->data<<endl;
		}
		cout << "\nEnter n: ";
		cin >> n;
	}
	return 0;
}