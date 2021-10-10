
#include <stdio.h>
#include <stdlib.h>

#define big 10

int count = 0;

struct stack
{
    int items[big];
    int edge;
};
typedef struct stack st;

void builds(st *s)
{
    s->edge = -1;
}

int isfull(st *s)
{
    if (s->edge == big - 1)
        return 1;
    else
        return 0;
}

int isempty(st *s)
{
    if (s->edge == -1)
        return 1;
    else
        return 0;
}

void push(st *s, int newboi)
{
    if (isfull(s))
    {
        printf("STACK FULL");
    }
    else
    {
        s->edge++;
        s->items[s->edge] = newboi;
    }
    count++;
}

void pop(st *s)
{
    if (isempty(s))
    {
        printf("\n STACK EMPTY \n");
    }
    else
    {
        printf("Book popped= %d", s->items[s->edge]);
        s->edge--;
    }
    count--;
    printf("\n");
}

void display(st *s)
{
    printf("Stack: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

int main()
{
    int ch;
    st *s = (st *)malloc(sizeof(st));

    builds(s);

    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);

    display(s);

    pop(s);

    printf("\nAfter popping book out\n");
    display(s);
}