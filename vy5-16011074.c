#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Stack
{
    int top;//this variable will represent the top element's index of the stack
    int arrayCapacity;
    int *array;

}STACK;

typedef struct varList
{
    char variable;
    int *number;
    int netValue;
    struct varList *next;

}VARS;



int asciiToInteger ( char ch);
int isStackFull (STACK* stack);
void pushVarToStack( STACK* stack , int var );
int isStackEmpty ( STACK* stack );
char popVarFromStack(STACK* stack);
int isOperand ( char ch);
char topElement (STACK * stack);
int asciiToInteger ( char ch);
int isInList(char ch, VARS* tmp);
VARS* createVarNode (char ch);
void addToList ( char ch , VARS* tmp );
int postfixSolver( char *pst, STACK stack,VARS *tmp );

int isVariable [100]= {0,0,0,0};
int isNumber [100]={0,0,0,0};

int main()
{
    
    
    char strRead[50];
    
    FILE* fileOpener = fopen("input.txt","r");
    if (fileOpener){printf (" file opened succesfully\n ");}
    VARS* node1;
    
    while (feof(fileOpener))
    {
        fgets(strRead,45,fileOpener);
        
    }




    return 0;
}

STACK* createStack (int capacity)
{
    STACK* newStack;
    newStack = (STACK*)malloc(sizeof(STACK));
    newStack->arrayCapacity = capacity;
    newStack->top = -1;
    newStack->array = (int*)malloc(capacity*sizeof(int));

    printf("stack has been created succesfully!\n");

    return newStack;
}


int isStackFull (STACK* stack)
{
    if ( stack->top == stack->arrayCapacity-1 ) {  return 1; }
    return 0;//in case of stack is not full
}

int isStackEmpty ( STACK* stack )
{

    if ( stack->top == -1 ){return 1;}

    return 0;//in case of stack is not empty

}

void pushVarToStack( STACK* stack , int var )
{
    //before pushing our variable to stack
    //we must control whether our stack is full or not
    if ( isStackFull(stack) )
    {
        printf("stack over flow occured\nterminating program!!\n");
        exit(1);
    }

    stack->top++;
    stack->array[stack->top] = var;
    printf("pushed variable to stack is = %d\n",var);
}

char popVarFromStack(STACK* stack)
{
    //before popping something from stack
    // we must control whether is empty
    if ( isStackEmpty(stack) )
    {
        printf("stack is empty nothing can be popped!!\nreturning dollar sign!!\nto represent the end of stack.\n");
        return '$';
    }
    stack -> top--;
    return stack->array[(stack -> top)+1];

}


int isOperand ( char ch)
{
    if ( (ch>='a' && ch<='z' )|| (ch>='A'&& ch<='Z') ){return 1;}
    printf("not an operand be careful\n");
    return 0;
}

char topElement (STACK * stack)
{
    return stack->array[stack->top];
}

int asciiToInteger ( char ch )
{
    return ch + 48;
}

int postfixMaker (char *ch, char *postFix, STACK* stck)
{

    int i = 0, j = 0;

    if ( isOperand(ch[0]))
    {
        if ( !(isInList(ch[0])) )
        {
            addToList(ch[0]);
        }
    }
    i = 4;
    while (ch[i]!=";")
    {
        if(isOperand(ch[i]))
        {
            postFix[j++]=ch[i++];
        }
        else if (isOperator (ch[i]))
        {
            if (ch[i]!=')')
            {
                pushVarToStack(stck, ch[i]);
            }
            else
            {
                char newCh = popVarFromStack(stck);
                while(newCh!='(')
                {
                    postFix[j++] = newCh;
                    newCh = popVarFromStack(stck);
                }
            }
        }
        else if (ch[i]!=' ')
        {
            int num1=0;
            while (ch[i]>='0' && ch[i]<='9')
            {
                num1=num1*10 +  ch[i++]-48;
            }
            postFix[j++]=num1;
        }
        else{i++;}

    }
    while(!(isStackEmpty(stck)))
    {
        char newCh2;
        newCh2 = popVarFromStack(stck);
        postFix[j++] = newCh2;
    }
    printf("end of postFix maker func.\n here is postifx = %s\n",postFix);
    printf("to continue please press ENTER\n");
    getchar();

}


VARS* createVarNode (char ch)
{
    VARS* tmp;
    tmp = (VARS*)malloc(sizeof(VARS));
    tmp->variable=ch;
    tmp->netValue=0;
    tmp->next=NULL;
    return tmp;
}

int isInList(char ch, VARS* tmp)
{
    while ( tmp->variable != ch && tmp->next !=NULL )
    {
        tmp = tmp->next;
    }
    if (tmp->variable == ch){return 1;}
    else { return 0;}
}

void addToList ( char ch , VARS* tmp )
{
    while ( tmp->next != NULL )
    {
        tmp=tmp->next;
    }
    tmp->next = createVarNode (ch);
}


int postfixSolver( char *pst, STACK stack,VARS *tmp )
{
    int i=0;
    int j=0;
    int k=0;

    while ( pst[i]!='\0' )
    {
        if ( isVariable[i] )
        {
            while ( tmp->next!=NULL && tmp->variable!= pst[i])
            {
                tmp=tmp->next;
            }
            if ( tmp->variable!= pst[i] )
            {
                pushVarToStack(stack,tmp->netValue);
            }
            else
            {
                printf("value cannot be found\n");
                exit(5);
            }


        }
        else if( isNumber[i] )
        {
            pushVarToStack(stack,pst[i]);
        }
        else
        {
            printf("this is an operator\n");
            int var1,var2;
            var1=popVarFromStack(stack);
            var2 = popVarFromStack(stack);
            if (pst[i]=='+'){pushVarToStack(stack,var1+var2);}
            if (pst[i]=='-'){pushVarToStack(stack,var1-var2);}
            if (pst[i]=='*'){pushVarToStack(stack,var1*var2);}
            if (pst[i]=='/'){pushVarToStack(stack,var1/var2);}
        }
        i++;
    }
    int var3;
    var3 = popVarFromStack(stack);
    return var3;
}




