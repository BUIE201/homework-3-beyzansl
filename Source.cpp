#include <iostream>

using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;

	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}

void DeleteNodeWithTwoChildren(Node*& q, Node*& p)
{
	if (p->pRight)
	{
		DeleteNodeWithTwoChildren(q, p->pRight);
		return;
	}

	p->i = q->i;
	q = p;
	p = p->pLeft;
}

void DeleteNodeFromTree(Node*& pRoot, int i)
{
	if (!pRoot)
		return;

	if (pRoot->i < i)
	{
		DeleteNodeFromTree(pRoot->pRight, i);
		return;
	}

	if (pRoot->i > i)
	{
		DeleteNodeFromTree(pRoot->pLeft, i);
		return;
	}

	Node* q = pRoot;
	if (!q->pRight)
		pRoot = q->pLeft;
	else if (!q->pLeft)
		pRoot = q->pRight;
	else
		DeleteNodeWithTwoChildren(q, q->pLeft);

	delete q;
}

void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++) {
		cout << "  ";
	}
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}

void Insert(Node*& pRoot, Node* pNewNode)
{
	if (!pRoot)
		pRoot = pNewNode;
	else
	{
		if (pNewNode->i < pRoot->i)
			Insert(pRoot->pLeft, pNewNode);
		else
			Insert(pRoot->pRight, pNewNode);
	}
}
int largestbranch(Node* pRoot)
{
	if (!pRoot) {
		return 0;
	}
	int right_sum = largestbranch(pRoot->pRight);
	int left_sum = largestbranch(pRoot->pLeft);
	int max_sum = max(right_sum, left_sum);
	return pRoot->i + max_sum;
}
void print_branch(Node* n) {
	int left = largestbranch(n->pLeft);
	int right = largestbranch(n->pRight);
	if (left > right && n->pLeft) {
		cout << n->pLeft->i<<" ";
		n = n->pLeft;
		print_branch(n);
	}
	else if (left < right && n->pRight) {
		cout << n->pRight->i<<" ";
		n = n->pRight;
		print_branch(n);
	}

}



void Find_max_branch(Node* pRoot) {
	cout << "Branch with the largest sum is: ";
	cout << pRoot->i << " ";
	print_branch(pRoot);
	cout << "  -> SUM : " << largestbranch(pRoot);
}

void main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}

	PrintTree(pRoot, 1);
	cout << endl;
	Find_max_branch(pRoot);
}

