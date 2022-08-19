#include <iostream>
#include <cstring>
#include <vector>
#include<sstream>

using namespace std;


char* str = new char[100];

struct List;

List* headl;
struct Tree;
Tree* headr;

struct List {
	List* next;
	int R;
	union {
		List* level;
		char atom;
	};
};

struct Tree {
	char root;
	Tree* left;
	Tree* right;
};

void Input_to_List(List*& p) {
	char symbol;
	symbol = str[0];
	str = str + 1;

	if (symbol != 0) {
		if (symbol == '(') {
			p = new List;
			p->R = 0;
			Input_to_List(p->level);
			Input_to_List(p->next);
		}
		else if ((symbol >= '0' && symbol <= '9') || (symbol == '+') || (symbol == '-') || (symbol == '*') || (symbol == '/')) {
			p = new List;
			p->R = 1;
			p->atom = symbol;
			Input_to_List(p->next);
		}
		else if (symbol == ')')
			p = NULL;
	}
	else
		p = NULL;
}

void Print_of_List(List* p) {
	List* q;
	if (p != NULL) {
		if (p->R == 1)
			cout << p->atom;
		else {
			cout << '(';
			q = p->level;
			while (q != NULL) {
				Print_of_List(q);
				q = q->next;
			}
			cout << ')';
		}
	}
}

void binary_tree(Tree* t) {
	if (t != NULL) {
		if (t->left != NULL) cout << '(';
		binary_tree(t->left);
		cout << t->root;
		binary_tree(t->right);
		if (t->right != NULL) cout << ')';
	}
}

string str3, tmp;
string reverse_polish_entry(Tree* t) {
	if (t != NULL) {
		reverse_polish_entry(t->left);
		reverse_polish_entry(t->right);
		stringstream strstream;
		strstream << t->root;
		strstream >> tmp;
		str3 += tmp;
	}
	return str3;
}

Tree* constructionTree(Tree* t1, char x, Tree* t2) {
	Tree* t = new Tree;
	t->root = x;
	t->left = t1;
	t->right = t2;
	return t;
}

Tree* list_to_tree(List* p) {
	Tree* t = NULL;
	if (p != NULL) {
		if (p->R == 0) {
			t = constructionTree(list_to_tree(p->level), p->level->next->atom, list_to_tree(p->level->next->next));
		}
		else {
			t = constructionTree(NULL, p->atom, NULL);
		}
	}
	return t;
}

int calculate(string str) {
	vector<int> val_vect;
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i]))
			val_vect.push_back((int)(str[i] - '0'));
		else {
			int el = val_vect[val_vect.size() - 1];
			val_vect.pop_back();
			switch (str[i]) {
			case '+': val_vect[val_vect.size() - 1] += el;
				break;
			case '-': val_vect[val_vect.size() - 1] -= el;
				break;
			case '*': val_vect[val_vect.size() - 1] *= el;
				break;
			case '/': val_vect[val_vect.size() - 1] /= el;
				break;
			default:cout << "Error" << endl;
			}
		}
	}
	return val_vect[0];
}


int main()
{

	List* p;
	string str1;
	Tree* p1;

	cin >> str;

	Input_to_List(p);
	cout << endl;

	cout << "list: ";
	Print_of_List(p);
	cout << endl;

	Tree* t2 = list_to_tree(p);
	cout << "Binary tree: ";
	binary_tree(t2);
	cout << endl;

	cout << "Reverse polish entry: " << reverse_polish_entry(t2) << endl;

	cout << "Result: " << calculate(str3) << endl;

	return 0;
}