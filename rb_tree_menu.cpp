#include <iostream>
#include <string>
#include "rbtree.h"
using namespace std;

int string_to_int(string s){
	int ret = 0;
	for (unsigned int i = 0; i < s.length(); i++){
		ret = (ret*10) + (short)(s[i] - '0');
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	rbtree <int> t;

	string s;
	int n;
	cout << "choose from:\n(m)inimmum and maximum \n(p)redecessor and successor\n(s)earch\n(i)nsert\n(q)uit\n";

	while (cin >> s)
	{
		if (s == "m")
		{
			rb_tree_node<int> *min = t.min();
			rb_tree_node<int> *max = t.max();
			if (min != NULL)
				cout << "min: " << min->data;
			if (max != NULL)
				cout << " max: " << max->data << endl;
		}
		else if (s == "p")
		{
			cin >> n;
			rb_tree_node<int> *pre = t.predecessor(n);
			rb_tree_node<int> *suc = t.successor(n);
			if (pre != NULL)
				cout << "predecessor: " << pre->data << ", ";
			else
				cout << "no predecessor, ";
			if (suc != NULL)
				cout << " successor: " << suc->data << endl;
			else
				cout << "no successor" << endl;
		}else if(s == "s"){
			cin>>n;
			cout<<t.search(n)<<endl;
		}else if(s == "i"){
			cin>>n;
			t.insert(n);
		}
		else if(s == "q" || s == "Q" || s == "quit"){
			return 0;
		}else{
			cout<<"invalid command"<<endl;
		}
		t.linear_display();
		if (t.bh() == 0) {
			cout << "Something is Wrong " << endl;
			return 0;
		}
	}
	
	return 0;
}
