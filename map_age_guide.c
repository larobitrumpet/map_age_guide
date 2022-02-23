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
                choice--;
                choice = mod(choice, choice_max);
                break;
            case KEY_RIGHT:
                choice++;
                choice = mod(choice, choice_max);
                break;
            case KEY_DOWN:
            case '\n':
                return choice;
            case KEY_UP:
                return 4;
            case 'q':
                return 5;
        }
    }
}

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();

    NODE node;
    node.message = "Istanbul or Constantinople?";
    node.choice1m = "Constantinople";
    node.choice2m = "Neither";
    node.choice3m = "Istanbul";
    node.choice4m = NULL;
    choiceLoop(&node);

    endwin();
    return 0;
}
