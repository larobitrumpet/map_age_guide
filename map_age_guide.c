#include <stdlib.h>
#include <curses.h>
#include <string.h>

int mod(int a, int b)
{
    return a < 0 ? a % b + b : a % b;
}

typedef struct NODE
{
    char* message;
    char* choice1m;
    char* choice2m;
    char* choice3m;
    char* choice4m;
    struct NODE* choice1;
    struct NODE* choice2;
    struct NODE* choice3;
    struct NODE* choice4;
    struct NODE* prev;
} NODE;

NODE* createNODE(char* m, char* c1, char* c2, char* c3, char* c4, NODE* previous, int prev_choice)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->message = strdup(m);
    if (c1 != NULL)
        newNode->choice1m = strdup(c1);
    else
        newNode->choice1m = NULL;
    if (c2 != NULL)
        newNode->choice2m = strdup(c2);
    else
        newNode->choice2m = NULL;
    if (c3 != NULL)
        newNode->choice3m = strdup(c3);
    else
        newNode->choice3m = NULL;
    if (c4 != NULL)
        newNode->choice4m = strdup(c4);
    else
        newNode->choice4m = NULL;
    newNode->prev = previous;
    newNode->choice1 = NULL;
    newNode->choice2 = NULL;
    newNode->choice3 = NULL;
    newNode->choice4 = NULL;
    switch (prev_choice)
    {
        case 0:
            previous->choice1 = newNode;
            break;
        case 1:
            previous->choice2 = newNode;
            break;
        case 2:
            previous->choice3 = newNode;
            break;
        case 3:
            previous->choice4 = newNode;
            break;
    }
    return newNode;
}

void displayChoice(char* str, bool selected)
{
    addch(' ');
    addch(' ');
    addch(' ');
    addch(' ');
    int len = strlen(str);
    if (selected)
    {
        for (int i = 0; i < len; i++)
            addch(str[i] | A_REVERSE);
    }
    else
    {
        for (int i = 0; i < len; i++)
            addch(str[i]);
    }
}

void displayNODE(NODE* n, int choice)
{
    clear();
    move(4, 8);
    int len = strlen(n->message);
    for (int i = 0; i < len; i++)
        addch(n->message[i]);
    move(6, 4);
    if (n->choice1m != NULL)
        displayChoice(n->choice1m, choice == 0);
    if (n->choice2m != NULL)
        displayChoice(n->choice2m, choice == 1);
    if (n->choice3m != NULL)
        displayChoice(n->choice3m, choice == 2);
    if (n->choice4m != NULL)
        displayChoice(n->choice4m, choice == 3);
    move(0, 0);
    refresh();
}

int choiceLoop(NODE* n)
{
    int choice = 0;
    int choice_max = 0;
    if (n->choice1m != NULL)
        choice_max = 1;
    if (n->choice2m != NULL)
        choice_max = 2;
    if (n->choice3m != NULL)
        choice_max = 3;
    if (n->choice4m != NULL)
        choice_max = 4;
    int ch;
    while (true)
    {
        displayNODE(n, choice);
        ch = getch();
        switch (ch)
        {
            case KEY_LEFT:
                if (choice_max)
                {
                    choice--;
                    choice = mod(choice, choice_max);
                }
                break;
            case KEY_RIGHT:
                if (choice_max)
                {
                    choice++;
                    choice = mod(choice, choice_max);
                }
                break;
            case KEY_DOWN:
            case '\n':
                if (choice_max)
                    return choice;
            case KEY_UP:
                return 4;
            case 'q':
                return 5;
        }
    }
}

NODE* getNextNode(NODE* n, int choice)
{
    switch (choice)
    {
        case 0:
            return n->choice1;
            break;
        case 1:
            return n->choice2;
            break;
        case 2:
            return n->choice3;
            break;
        case 3:
            return n->choice4;
            break;
    }
}

NODE* getPrevNode(NODE* n)
{
    if (n->prev != NULL)
        return n->prev;
    else
        return n;
}

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();

    NODE* n1 = createNODE("Istanbul or Constantinople?", "Constantinople", "Neither", "Istanbul", NULL, NULL, -1);
    {
    NODE* n2 = createNODE("Do any of these exist? *Independent Canada *US Territory of Alaska *Tokyo", "No", "Yes", NULL, NULL, n1, 0);
    NODE* n3 = createNODE("The Holy Roman Empire?", "Yes", "No", NULL, NULL, n2, 0);
    }

    NODE* node = n1;
    while (true)
    {
        int choice = choiceLoop(node);
        if (choice == 4)
            node = getPrevNode(node);
        else if (choice == 5)
            break;
        else
            node = getNextNode(node, choice);
    }

    clear();
    endwin();
    return 0;
}
