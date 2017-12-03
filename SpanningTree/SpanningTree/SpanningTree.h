#ifndef SPANNINGTREE
#define SPANNINGTREE
#include<cmath>

using namespace std;

struct node{
	node *lc, *rc, *par;
	//node *child[2];
	int val, weight;
};

class spanningTree{
private:
	node *root;
public:
	spanningTree(){
		root = NULL;
	}

	//��������
	void Zig(node *x){
		node *y = x->par;
		y->lc = x->lc;
		if (x->rc)
			x->rc->par = y;
		x->par = y->par;
		if (y->par){
			if (y == y->par->lc)
				y->par->lc = x;
			else
				y->par->rc = x;
		}
		x->rc = y;
		y->par = x;
	}

	//��������
	void Zag(node *x){
		node *y = x->par;
		y->rc = x->lc;
		if (x->lc)
			x->lc->par = y;
		x->par = y->par;
		if (y->par){
			if (y == y->par->lc)
				y->par->lc = x;
			else
				y->par->rc = x;
		}
		x->lc = y;
		y->par = x;
	}


	////������������0Ϊ���ӽ�㣬1Ϊ���ӽ��
	//void turn(node *x,int d){
	//	node *y = x->par;
	//	y->child[!d] = x->child[d];
	//	if (x->child[d])
	//		x->child[d]->par = y;
	//	x->par = y->par;
	//	if (y->par){
	//		if (y == y->par->child[0])
	//			y->par->child[0] = x;
	//		else
	//			y->par->child[1] = x;
	//	}
	//	x->child[d] = y;
	//	y->par = x;
	//}


	//�ӽ��x���������yΪ˫�׵�λ��
	void Splay(node *x, node *y){
		while (x->par != y){
			if (x->par->par == y){
				x->par->lc == x ? Zig(x) : Zag(x);
			}
			else if (x->par->par->lc == x->par){
				if (x->par->lc == x){
					Zig(x->par);
					Zig(x);
				}
				else{
					Zag(x);
					Zig(x);
				}
			}
			else{
				if (x->par->rc == x){
					Zag(x->par);
					Zag(x);
				}
				else{
					Zig(x);
					Zag(x);
				}
			}
		}
		if (y == 0)
			root = x;
	}

	bool find(node *x, int key){
		if (!x)
			return false;
		if (x->val == key){
			Splay(x, 0);
			return true;
		}
		else{
			if (x->val < key)
				return find(x->rc, key);
			else
				return find(x->lc, key);
		}
	}


	void insert(int key){
		node *p = root, *y = 0;
		while (1){
			if (!p){
				p = new node;
				p->lc = p->rc = 0;
				p->val = key;
				p->weight = 1;
				p->par = y;
				Splay(p, 0);
				break;
			}
			y = p;
			if (key == p->val){
				p->weight++;
				Splay(p, 0);
				break;
			}
			else if (key < p->val){
				p = p->lc;
			}
			else{
				p = p->lc;
			}
		}
	}


	int calT(){
		node *left = root->lc;
		node *rigth = root->rc;
		if (left == NULL)
			return abs(root->val - rigth->val);
		if (rigth == NULL)
			return abs(root->val - left->val);

		while (left->rc)
			left = left->rc;
		int leftFluct = abs(root->val - left->val);
		while (rigth->lc)
			rigth = rigth->lc;
		int rigthFluct = abs(root->val - rigth->val);
		return leftFluct < rigthFluct ? leftFluct : rigthFluct;
	}
};



////�ϲ�����
//node *join(node *s1, node *s2){
//	if (s1)
//		s1->par = 0;
//	if (s2)
//		s2->par = 0;
//	if (!s1)
//		return s2;
//	if (!s2)
//		return s1;
//	s1->par = s2->par = 0;
//	node *c = s1;
//	while (c->rc)
//		c = c->rc;
//	Splay(c, 0);
//	c->rc = s2;
//	s2->par = c;
//	return c;
//}
//
////ɾ������
//void remove(node *x){
//	Splay(x, 0);
//	root = join(x->lc, x->rc);
//}
//
////ɾ����Сֵ
//void delmin(int &min, int &cnt){
//	node *x = root;
//	while (x->lc)
//		x = x->lc;
//	min = x->val;
//	cnt = x->weight;
//	remove(x);
//}
//
////ɾ�����ֵ
//void delmax(int &max, int &cnt){
//	node *x = root;
//	while (x->rc)
//		x = x->rc;
//	max = x->val;
//	cnt = x->weight;
//	remove(x);
//}
#endif