#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


// �߰��� ��������� �ʿ��� ��� �����Ӱ� �߰��ص� �˴ϴ�.

#define MAX_LEN   100

// ���� ����ü
typedef struct {
	double* arr;
	int top;
} Stack;

// ���� �ʱ�ȭ �Լ�
void initStack(Stack* pstack, int size)
{
	pstack->arr = (double*)malloc(size * sizeof(double));
	pstack->top = -1;
}
// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Stack* pstack)
{
	return pstack->top == -1;
}

// ���� ���� �Լ�
void push(Stack* pstack, double value)
{//error: stack full
	pstack->arr[++(pstack->top)] = value;
}

// ���� ���� �Լ�
double pop(Stack* pstack)
{
	if (isEmpty(pstack))
		exit(1); //error: empty stack
	--(pstack->top);
}


// ���ÿ��� ���� �о���� �Լ�
double peek(Stack* pstack)
{
	if (isEmpty(pstack))
		exit(1); //error
	return pstack->arr[pstack->top];
}
// prefix notation ���ڿ��� ����ϴ� �Լ�
double prefix_calculate(char* exp)
{
	Stack stack;
	double op1, op2;
	int len = strlen(exp);//���ڿ��� ���� ��ȯ
	initStack(&stack, len);
	for (int i = len - 1; i >= 0; i--)
	{
		if (isdigit(exp[i]))
		{
			// ������ �ǳʶ� ��, ���ڸ� �̻��� ���ڸ� �о��
			double numlen = 0;
			double num = 0;
			while (i >= 0 && !isspace(exp[i]))
			{
				num += pow(10, numlen) * (exp[i] - '0');
				numlen++;
				i--;
			}
			push(&stack, num);
		}
		else if (exp[i] == ' ')
		{
			continue;
		}
		else
		{
			//���ı�ȣ�� ���������� ����
			op2 = peek(&stack), pop(&stack);
			op1 = peek(&stack), pop(&stack);
			if (exp[i] == '+')
				push(&stack, op2 + op1);
			else if (exp[i] == '-')
				push(&stack, op2 - op1);
			else if (exp[i] == '*')
				push(&stack, op2 * op1);
			else if (exp[i] == '/')
				push(&stack, op2 / op1);
		}
	}
	return peek(&stack);
}


int main() {

	// �Ʒ� main �Լ��� �������� ������. 
	char expression[MAX_LEN];
	// ���๮�ڸ� ������ ��� ����� �Է��� �޴´ٴ� �ǹ��Դϴ�.
	scanf("%[^\n]", expression);

	double result = prefix_calculate(expression);
	printf("%.2lf\n", result);

	return 0;
}


