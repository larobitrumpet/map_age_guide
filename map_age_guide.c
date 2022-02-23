#include <curses.h>
#include <string.h>

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

int c1x;
int c2x;
int c3x;
int c4x;
int choice;
int choice_max;

void displayNODE(NODE* n)
{
    clear();
    move(4, 8);
    int len = strlen(n->message);
    for (int i = 0; i < len; i++)
        addch(n->message[i]);
    int x, y;
    y = 6;
    x = 8;
    move(y, x);
    choice_max = 0;
    if (n->choice1m != NULL)
    {
        choice_max = 1;
        c1x = x;
        int len = strlen(n->choice1m);
        for (int i = 0; i < len; i++)
        {
            addch(n->choice1m[i]);
            x++;
        }
    }
    if (n->choice2m != NULL)
    {
        choice_max = 2;
        c2x = x;
        addch(' ');
        addch(' ');
        addch(' ');
        addch(' ');
        x += 4;
        int len = strlen(n->choice2m);
        for (int i = 0; i < len; i++)
        {
            addch(n->choice2m[i]);
            x++;
        }
    }
    if (n->choice3m != NULL)
    {
        choice_max = 3;
        c3x = x;
        addch(' ');
        addch(' ');
        addch(' ');
        addch(' ');
        x += 4;
        int len = strlen(n->choice3m);
        for (int i = 0; i < len; i++)
        {
            addch(n->choice3m[i]);
            x++;
        }
    }
    if (n->choice4m != NULL)
    {
        choice_max = 4;
        c4x = x;
        addch(' ');
        addch(' ');
        addch(' ');
        addch(' ');
        int len = strlen(n->choice4m);
        for (int i = 0; i < len; i++)
            addch(n->choice4m[i]);
    }
    choice = 1;
    refresh();
    getchar();
}

int main()
{
    initscr();
    clear();
    cbreak();
    noecho();

    NODE node;
    node.message = "Istanbul or Constantinople?";
    node.choice1m = "Constantinople";
    node.choice2m = "Neither";
    node.choice3m = "Istanbul";
    node.choice4m = NULL;
    displayNODE(&node);

    endwin();
    return 0;
}
