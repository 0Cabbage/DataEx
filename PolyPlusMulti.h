#pragma once
#include <iostream>
using namespace std;


typedef struct Polynomial
{
	int			coef; // ϵ��
	int			expon; // ָ��
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
	int c; // ϵ��
	int e; // ָ��
	int n; // ����

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
			int sum = pTemp->pNext->coef + pNew->coef; // �����ָ����ȵ���ͺϲ�, ϵ�����
			if (sum) 
				pTemp->pNext->coef += pNew->coef;	
			else	// ����ϲ�����0
			{
				PolyNode t = pTemp->pNext;
				pTemp->pNext = t->pNext;
				free(t);			// �ͷ������ϵĽڵ�
				t = NULL;
			}
			free(pNew);			// Ȼ���ͷ������Ľڵ㣬���˳�
			pNew = NULL;		
			return;
		}
		else
			pTemp = pTemp->pNext;// ����ͼ�������
	}

	if (pTemp->pNext) // ��� pTemp->pNext != NULL ������λ����
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

	// ��δ���������һ������ʽһ�θ��Ƶ��������ʽ����rear��
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
	pTemp = front; // ��frontָ���һ���������ʽ
	front = front->pNext;
	free(pTemp); // �ͷſսڵ�
	pTemp = NULL;

	return front; // �������
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