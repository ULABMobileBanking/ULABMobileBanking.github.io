
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

struct node
{
    char color[20];
    int size;
    struct node *next;
};

struct node *top;

void start()
{

    top = NULL;
}

int isEmpty()
{

    if (top == NULL)

        return 1;

    else

        return 0;
}

void push(char col, int vol)
{

    struct node *temp;

    temp = (struct node *)malloc(sizeof(struct node));

    strcpy(temp->color, col);

    temp->size = vol;

    if (top == NULL)
    {

        top = temp;

        top->next = NULL;
    }
    else
    {

        temp->next = top;

        top = temp;
    }
}

void pop()
{

    struct node *temp;

    if (isEmpty(top))
    {

        printf("\nStack is Empty\n");

        return;
    }
    else
    {

        temp = top;

        top = top->next;

        printf("Removed  Book : \nColor: %s\tsize: %d\n", temp->color, temp->size);

        free(temp);
    }
}

void main()
{

    start();

    push(red, 9);

    push(blue, 8);

    push(green, 9);

    push(yellow, 9);

    pop();

    pop();

    pop();

    pop();

    pop();

    return 0;
}