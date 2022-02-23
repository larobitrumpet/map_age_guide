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

void displayNODE(NODE* n)
{
    clear();
    move(1, 1);
    int len = strlen(n->message);
    for (int i = 0; i < len; i++)
        addch(n->message[i]);
    move(3, 1);
    if (n->choice1m != NULL)
    {
        int len = strlen(n->choice1m);
        for (int i = 0; i < len; i++)
            addch(n->choice1m[i]);
    }
    if (n->choice2m != NULL)
    {
        addch(' ');
        addch(' ');
        addch(' ');
        addch(' ');
        int len = strlen(n->choice2m);
        for (int i = 0; i < len; i++)
            addch(n->choice2m[i]);
    }
    if (n->choice3m != NULL)
    {
        addch(' ');
        addch(' ');
        addch(' ');
        addch(' ');
        int len = strlen(n->choice3m);
        for (int i = 0; i < len; i++)
            addch(n->choice3m[i]);
    }
    if (n->choice4m != NULL)
    {
        addch(' ');
        addch(' ');
        addch(' ');
        addch(' ');
        int len = strlen(n->choice4m);
        for (int i = 0; i < len; i++)
            addch(n->choice4m[i]);
    }
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
