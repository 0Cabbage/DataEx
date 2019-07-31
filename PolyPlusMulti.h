#pragma once
#include <iostream>
using namespace std;


typedef struct Polynomial
{
	int			coef; // 系数
	int			expon; // 指数
	Polynomial*	pNext;
}*PolyNode;

PolyNode initList(void);
PolyNode ReadOnly(void);
PolyNode PolyMultiply(PolyNode P1, PolyNode P2);
PolyNode CreateNode(const int coef, const int expon);
void CreatePolynomial(PolyNode pList, const int coef, const int expon);
PolyNode PolyAdd(PolyNode POne, PolyNode PTow);
void Attach(PolyNode* pRear, int c, int e);
bool IsEmpty(PolyNode pList);
void print(PolyNode pList, const char* PolyName);
int Compare(const int e1, const int e2);
void Delete(PolyNode* pList);


PolyNode ReadOnly(void)
{
	int c; // 系数
	int e; // 指数
	int n; // 项数

	cout << "n: ";
	cin >> n;

	PolyNode pNew = initList();
	while (n--)
	{
		cin >> c;
		cin >> e;
		CreatePolynomial(pNew, c, e);
	}
	return pNew;
}

PolyNode PolyMultiply(PolyNode P1, PolyNode P2)
{
	PolyNode pResult = initList();

	if (IsEmpty(P1) || IsEmpty(P2))
		return pResult;

	PolyNode pT1 = P1->pNext;
	PolyNode pT2;

	while (pT1)
	{
		pT2 = P2->pNext;
		while (pT2)
		{
			pResult->coef = pT1->coef * pT2->coef;
			pResult->expon = pT1->expon + pT2->expon;
			CreatePolynomial(pResult, pResult->coef, pResult->expon);
			pT2 = pT2->pNext;
		}
		pT1 = pT1->pNext;
	}

	return pResult;
}

PolyNode initList(void)
{
	PolyNode pHead = new Polynomial;
	pHead->pNext = NULL;
	return pHead;
}

PolyNode CreateNode(const int coef, const int expon)
{
	PolyNode pNew = new Polynomial;
	pNew->coef = coef;
	pNew->expon = expon;
	pNew->pNext = NULL;
	return pNew;
}

int Compare(const int e1, const int e2)
{
	if (e1 > e2) return 1;
	if (e1 < e2) return -1;
	if (e1 == e2) return 0;
}

bool IsEmpty(PolyNode pList)
{
	return pList->pNext == NULL;
}

void CreatePolynomial(PolyNode pList, const int coef, const int expon)
{
	/*
	PolyNode pTemp = pList;
	while (pTemp->pNext)
	{
		pTemp = pTemp->pNext;
	}
	pTemp->pNext = CreateNode(coef, expon);
	*/

	PolyNode pNew = CreateNode(coef, expon);
	PolyNode pTemp = pList;

	while (pTemp->pNext && pTemp->pNext->expon >= pNew->expon)
	{
		if (pTemp->pNext->expon == pNew->expon)
		{
			int sum = pTemp->pNext->coef + pNew->coef; // 如果有指数相等的项就合并, 系数相加
			if (sum) 
				pTemp->pNext->coef += pNew->coef;	
			else	// 如果合并等于0
			{
				PolyNode t = pTemp->pNext;
				pTemp->pNext = t->pNext;
				free(t);			// 释放链表上的节点
				t = NULL;
			}
			free(pNew);			// 然后释放新来的节点，并退出
			pNew = NULL;		
			return;
		}
		else
			pTemp = pTemp->pNext;// 否则就继续后移
	}

	if (pTemp->pNext) // 如果 pTemp->pNext != NULL 则不再首位插入
		pNew->pNext = pTemp->pNext;

	pTemp->pNext = pNew;
}

void Delete(PolyNode* pList)
{
	if (pList == NULL && IsEmpty(*pList))
		return;

	PolyNode pTemp = *pList;
	PolyNode pTemp1 = pTemp->pNext;

	while (pTemp1)
	{
		pTemp->pNext = pTemp1->pNext;
		free(pTemp1);
		pTemp1 = NULL;
		pTemp1 = pTemp->pNext;
	}
	free(*pList);
	*pList = NULL;
}

PolyNode PolyAdd(PolyNode POne, PolyNode PTow)
{
	int sum;
	PolyNode front, rear, pTemp;

	rear = (PolyNode)malloc(sizeof(Polynomial));
	front = rear;

	PolyNode P1 = POne->pNext;
	PolyNode P2 = PTow->pNext;

	while (P1 && P2)
	{
		switch (Compare(P1->expon, P2->expon))
		{
		case 1:
		{
			Attach(&rear, P1->coef, P1->expon);
			P1 = P1->pNext;
		}
		break;
		case -1:
		{
			Attach(&rear, P2->coef, P2->expon);
			P2 = P2->pNext;
		}
		break;
		case 0:
		{
			sum = P1->coef + P2->coef;
			if (sum) Attach(&rear, sum, P1->expon);
			P1 = P1->pNext;
			P2 = P2->pNext;
		}
		break;
		default:
			break;
		}
	}

	// 将未处理完的另一条多项式一次复制到结果多项式链表rear中
	while (P1)
	{
		Attach(&rear, P1->coef, P1->expon);
		P1 = P1->pNext;
	}

	while (P2)
	{
		Attach(&rear, P2->coef, P2->expon);
		P2 = P2->pNext;
	}

	rear->pNext = NULL;
	pTemp = front; // 将front指向第一个结果多项式
	front = front->pNext;
	free(pTemp); // 释放空节点
	pTemp = NULL;

	return front; // 方便接收
}

void Attach(PolyNode* pRear, int c, int e)
{
	PolyNode pCopy = (PolyNode)malloc(sizeof(Polynomial));
	if (pCopy == NULL)
	{
		cout << "pCopy NULL" << endl;
		return;
	}
	pCopy->coef = c;
	pCopy->expon = e;
	pCopy->pNext = NULL;

	(*pRear)->pNext = pCopy;
	*pRear = pCopy;
}

void print(PolyNode pList, const char* PolyName)
{
	if (IsEmpty(pList))
	{
		cout << "NULL" << endl;
		return;
	}

	int i = 0;
	PolyNode pTemp = pList->pNext;
	cout << PolyName << ": ";
	while (pTemp)
	{
		cout << "P" << ++i << "(" << pTemp->coef << "," << pTemp->expon << ") ";
		pTemp = pTemp->pNext;
	}
	cout << "\n\n";
}