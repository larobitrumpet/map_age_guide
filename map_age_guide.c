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
                break;
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
    NODE* a1 = createNODE("1805 or earlier (before this point, the modern idea of a complete policical map of the world gets hard to apply)", NULL, NULL, NULL, NULL, n3, 0);
    NODE* n4 = createNODE("The United States?", "No", "Yes", NULL, NULL, n3, 1);
    NODE* a2 = createNODE("How sure are you that this map is in English?", NULL, NULL, NULL, NULL, n4, 0);
    NODE* n5 = createNODE("Texas is...", "part of mexico", "independent", "part of the US", NULL, n4, 1);
    NODE* n6 = createNODE("Florida is part of...", "Spain", "the US", NULL, NULL, n5, 0);
    NODE* n7 = createNODE("Paraguay?", "No", "Yes", NULL, NULL, n6, 0);
    NODE* a3 = createNODE("1806-10", NULL, NULL, NULL, NULL, n7, 0);
    NODE* a4 = createNODE("1811-17", NULL, NULL, NULL, NULL, n7, 1);
    NODE* n8 = createNODE("Venezuela and/or Ecuador?", "No", "Yes", NULL, NULL, n6, 1);
    NODE* a5 = createNODE("1818-29", NULL, NULL, NULL, NULL, n8, 0);
    NODE* a6 = createNODE("1830-33", NULL, NULL, NULL, NULL, n8, 1);
    NODE* a7 = createNODE("1834-45", NULL, NULL, NULL, NULL, n5, 1);
    NODE* n9 = createNODE("Does Russia border the Sea of Japan?", "No", "Yes", NULL, NULL, n5, 2);
    NODE* n10 = createNODE("The US's southern border looks...", "weird", "normal", NULL, NULL, n9, 0);
    NODE* a8 = createNODE("1846-53", NULL, NULL, NULL, NULL, n10, 0);
    NODE* a9 = createNODE("1854-56", NULL, NULL, NULL, NULL, n10, 1);
    NODE* a10 = createNODE("1858-67", NULL, NULL, NULL, NULL, n9, 1);
    NODE* n11 = createNODE("South Africa?", "No", "Yes", NULL, NULL, n2, 1);
    NODE* n12 = createNODE("Rhodesia?", "No", "Yes", NULL, NULL, n11, 0);
    NODE* n13 = createNODE("Is Bolivia landlocked?", "No", "Yes", NULL, NULL, n12, 0);
    NODE* n14 = createNODE("\"Buda\" and \"Pest\" or \"Budapest\"?", "Buda and Pest", "Budapest", NULL, NULL, n13, 0);
    NODE* a11 = createNODE("1868-72", NULL, NULL, NULL, NULL, n14, 0);
    NODE* a12 = createNODE("1873-83", NULL, NULL, NULL, NULL, n14, 1);
    NODE* a13 = createNODE("1884-95", NULL, NULL, NULL, NULL, n13, 1);
    NODE* n15 = createNODE("Is Norway part of Sweden?", "Yes", "No", NULL, NULL, n12, 1);
    NODE* a14 = createNODE("1896-1905", NULL, NULL, NULL, NULL, n15, 0);
    NODE* a15 = createNODE("1906-09", NULL, NULL, NULL, NULL, n15, 1);
    NODE* n16 = createNODE("Austria-Hungary?", "Yes", "No", NULL, NULL, n11, 1);
    NODE* n17 = createNODE("Albania?", "No", "Yes", NULL, NULL, n16, 0);
    NODE* a16 = createNODE("1910-12", NULL, NULL, NULL, NULL, n17, 0);
    NODE* a17 = createNODE("1913-18", NULL, NULL, NULL, NULL, n17, 1);
    NODE* n18 = createNODE("Leningrad?", "No", "Yes", NULL, NULL, n16, 1);
    NODE* a18 = createNODE("1919-23", NULL, NULL, NULL, NULL, n18, 0);
    NODE* a19 = createNODE("1924-29", NULL, NULL, NULL, NULL, n18, 1);
    NODE* n19 = createNODE("Does the Ottoman Empire exist?", "Yes", "No", NULL, NULL, n1, 1);
    n19->choice1 = n2;
    NODE* n20 = createNODE("The Soviet Union?", "Yes", "No", NULL, NULL, n19, 1);
    NODE* n21 = createNODE("Saudi Arabia?", "Yes", "No", NULL, NULL, n20, 0);
    NODE* a20 = createNODE("1922-1932", NULL, NULL, NULL, NULL, n21, 1);
    NODE* n22 = createNODE("North Korea?", "Yes", "No", NULL, NULL, n20, 1);
    NODE* n23 = createNODE("Saint Trimble's Island", "No", "Yes", NULL, NULL, n22, 1);
    NODE* a21 = createNODE("No, I made that one up.", NULL, NULL, NULL, NULL, n23, 1);
    NODE* n24 = createNODE("Is Jan Mayen part of the kingdom of Norway?", "Not yet", "What?", "Yes", NULL, n23, 0);
    n24->choice1 = n2;
    NODE* n25 = createNODE("Can you see the familiar continents?", "Yes", "No", NULL, NULL, n24, 1);
    NODE* n26 = createNODE("This sounds like a physical map or satellite photo.", "Yes, that's it", NULL, NULL, NULL, n25, 0);
    NODE* n27 = createNODE("Is Lake Chad missing?", "No", "Yes", NULL, NULL, n26, 0);
    NODE* n28 = createNODE("How far east do the American prairies reach?", "Indiana", "The Mississippi", "Nebraska", "What Prairies?", n27, 0);
    NODE* a22 = createNODE("Before 1830", NULL, NULL, NULL, NULL, n28, 0);
    NODE* a23 = createNODE("1830s-80s", NULL, NULL, NULL, NULL, n28, 1);
    NODE* n29 = createNODE("Is there a big lake in the middle of Southern California? (created by mistake)", "No", "Yes", NULL, NULL, n28, 2);
    NODE* a24 = createNODE("1860s-1900s", NULL, NULL, NULL, NULL, n29, 0);
    NODE* a25 = createNODE("1910s", NULL, NULL, NULL, NULL, n29, 1);
    NODE* n30 = createNODE("Is there a big lake in the middle of Ghana? (created on purpose)", "No", "Yes", NULL, NULL, n28, 3);
    NODE* a26 = createNODE("1920s-50s", NULL, NULL, NULL, NULL, n30, 0);
    NODE* a27 = createNODE("1960s-70s", NULL, NULL, NULL, NULL, n30, 1);
    NODE* n31 = createNODE("Is the Aral Sea missing?", "No", "Yes", NULL, NULL, n27, 1);
    NODE* n32 = createNODE("Rivers \"Sirion\" or \"Anduin\"?", "Yes", "No", NULL, NULL, n25, 1);
    NODE* n33 = createNODE("Mordor?", "No", "Yes", NULL, NULL, n32, 0);
    NODE* n34 = createNODE("Beleriand?", "Yes", "No", NULL, NULL, n33, 0);
    NODE* a28 = createNODE("First Age", NULL, NULL, NULL, NULL, n34, 0);
    NODE* a29 = createNODE("Early Second Age", NULL, NULL, NULL, NULL, n34, 1);
    NODE* n35 = createNODE("Númenor?", "Yes", "No", NULL, NULL, n33, 1);
    NODE* a30 = createNODE("Late Second Age", NULL, NULL, NULL, NULL, n35, 0);
    NODE* n36 = createNODE("The forest east of the Misty Mountains is...", "Greenwood the Great", "Mirkwood", "The Wood of Greenleaves", NULL, n35, 1);
    NODE* a31 = createNODE("Early Third Age", NULL, NULL, NULL, NULL, n36, 0);
    NODE* a32 = createNODE("Late Third Age", NULL, NULL, NULL, NULL, n36, 1);
    NODE* a33 = createNODE("Fourth Age", NULL, NULL, NULL, NULL, n36, 2);
    NODE* n37 = createNODE("Cair Paravel?", "Yes", "No", NULL, NULL, n32, 1);
    NODE* n38 = createNODE("Calormen?", "No", "Yes", NULL, NULL, n37, 0);
    NODE* n39 = createNODE("Lotta islands?", "No", "Yes", NULL, NULL, n38, 0);
    NODE* a34 = createNODE("Dawn Treader", NULL, NULL, NULL, NULL, n39, 1);
    NODE* n40 = createNODE("Beruna", "Ford", "Bridge", NULL, NULL, n39, 0);
    NODE* a35 = createNODE("The Lion, the Witch, and the Wardrobe", NULL, NULL, NULL, NULL, n40, 0);
    NODE* a36 = createNODE("Prince Caspian", NULL, NULL, NULL, NULL, n40, 1);
    NODE* n41 = createNODE("Weird recursive heaven?", "No", "Yes", NULL, NULL, n38, 1);
    NODE* a37 = createNODE("One of the random later books", NULL, NULL, NULL, NULL, n41, 0);
    NODE* a38 = createNODE("The Last Battle", NULL, NULL, NULL, NULL, n41, 1);
    NODE* n42 = createNODE("Mossflower?", "Yes", "No", NULL, NULL, n37, 1);
    NODE* a39 = createNODE("Redwall", NULL, NULL, NULL, NULL, n42, 0);
    NODE* n43 = createNODE("Is the world on the back of a turtle?", "Yes", "No", NULL, NULL, n42, 1);
    NODE* a40 = createNODE("Discworld", NULL, NULL, NULL, NULL, n43, 0);
    NODE* n44 = createNODE("Are you SURE this is a map?", "Yes", "No", NULL, NULL, n43, 1);
    NODE* n45 = createNODE("Did you make it yourself?", "Yes", NULL, NULL, NULL, n44, 0);
    NODE* n46 = createNODE("It's very nice.", "Thank you!", NULL, NULL, NULL, n45, 0);
    NODE* a41 = createNODE("You're welcome!", NULL, NULL, NULL, NULL, n46, 0);
    NODE* n47 = createNODE("Is it trying to bite you?", "No", "Yes", NULL, NULL, n44, 1);
    NODE* n48 = createNODE("Is it larger than a breadbox?", "Yes", "No", "About the same", NULL, n47, 0);
    NODE* a42 = createNODE("Tuba", NULL, NULL, NULL, NULL, n48, 0);
    NODE* a43 = createNODE("Stapler", NULL, NULL, NULL, NULL, n48, 1);
    NODE* a44 = createNODE("Breadbox", NULL, NULL, NULL, NULL, n48, 2);
    NODE* n49 = createNODE("If you let it go, what does it do?", "Hisses and runs away", "Screeches and flaps around the room breaking things", NULL, NULL, n47, 1);
    NODE* a45 = createNODE("Cat", NULL, NULL, NULL, NULL, n49, 0);
    NODE* n50 = createNODE("Does the screeching chill your blood and herald death?", "Yes", "No", NULL, NULL, n49, 1);
    NODE* a46 = createNODE("Banshee", NULL, NULL, NULL, NULL, n50, 0);
    NODE* a47 = createNODE("Seagull", NULL, NULL, NULL, NULL, n50, 1);
    NODE* n51 = createNODE("Does the Soviet Union exist?", "Yes", "No", NULL, NULL, n1, 2);
    NODE* n52 = createNODE("Is most of West Africa a giant French blob?", "Yes", "No", NULL, NULL, n51, 0);
    n21->choice1 = n52;
    NODE* n53 = createNODE("Pakistan?", "No", "Yes", NULL, NULL, n52, 0);
    n24->choice3 = n53;
    NODE* n54 = createNODE("How many Germanys are there?", "One", "One, but it's HUGE", "Two", NULL, n53, 0);
    NODE* a48 = createNODE("1941-45", NULL, NULL, NULL, NULL, n54, 1);
    NODE* a49 = createNODE("1946-47", NULL, NULL, NULL, NULL, n54, 2);
    NODE* n55 = createNODE("Persia or Iran?", "Persia", "Iran", NULL, NULL, n54, 0);
    NODE* a50 = createNODE("1930-34", NULL, NULL, NULL, NULL, n55, 0);
    NODE* a51 = createNODE("1935-40", NULL, NULL, NULL, NULL, n55, 1);
    NODE* n56 = createNODE("Cambodia?", "No", "Yes", NULL, NULL, n53, 1);
    NODE* n57 = createNODE("Eritrea is a part of...", "Italy", "Ethiopia", NULL, NULL, n56, 0);
    NODE* a52 = createNODE("1952-53", NULL, NULL, NULL, NULL, n57, 1);
    NODE* n58 = createNODE("Canada is...", "Missing a piece", "Fine", NULL, NULL, n57, 0);
    NODE* a53 = createNODE("1948", NULL, NULL, NULL, NULL, n58, 0);
    NODE* n59 = createNODE("The United Arab Republic?", "No", "Yes", NULL, NULL, n56, 1);
    NODE* a54 = createNODE("1954-57", NULL, NULL, NULL, NULL, n59, 0);
    NODE* a55 = createNODE("1958-60", NULL, NULL, NULL, NULL, n59, 1);
    NODE* n60 = createNODE("How many Vietnams are there?", "Two", "One", NULL, NULL, n52, 1);
    NODE* n61 = createNODE("Bangladesh?", "No", "Yes", NULL, NULL, n60, 0);
    NODE* a56 = createNODE("1972-75", NULL, NULL, NULL, NULL, n61, 1);
    NODE* n62 = createNODE("Is the area south of Lake Victoria...", "British", "Tanganyika", "Tanzania", NULL, n61, 0);
    NODE* a57 = createNODE("1960", NULL, NULL, NULL, NULL, n62, 0);
    NODE* a58 = createNODE("1961-64", NULL, NULL, NULL, NULL, n62, 1);
    NODE* a59 = createNODE("1965-71", NULL, NULL, NULL, NULL, n62, 2);
    NODE* n63 = createNODE("The town on I-25 between Albuquerque and El Paso is...", "Hot Springs", "Truth or Consequences", NULL, NULL, n58, 1);
    NODE* a60 = createNODE("1948-49", NULL, NULL, NULL, NULL, n63, 0);
    NODE* a61 = createNODE("1950-52", NULL, NULL, NULL, NULL, n63, 1);
    NODE* n64 = createNODE("Jimmy Carter is...", "Being attacked by a giant swimming rabbit", "Fine", NULL, NULL, n60, 1);
    NODE* a62 = createNODE("April 20, 1979", NULL, NULL, NULL, NULL, n64, 0);
    NODE* n65 = createNODE("The Sinai is part of what country?", "Israel", "Mostly Israel", "Mostly Egypt", "Egypt", n64, 1);
    NODE* a63 = createNODE("1976-79", NULL, NULL, NULL, NULL, n65, 0);
    NODE* a64 = createNODE("1980", NULL, NULL, NULL, NULL, n65, 1);
    NODE* a65 = createNODE("1981", NULL, NULL, NULL, NULL, n65, 2);
    NODE* n66 = createNODE("What's the capital of Micronesia?", "Kolonia", "Palikir", NULL, NULL, n65, 3);
    NODE* n67 = createNODE("Republic of the Upper Volta or Burkina Faso?", "Upper Volta", "Burkina Faso", NULL, NULL, n66, 0);
    NODE* a66 = createNODE("1982-84", NULL, NULL, NULL, NULL, n67, 0);
    NODE* a67 = createNODE("1985-88", NULL, NULL, NULL, NULL, n67, 1);
    NODE* n68 = createNODE("(Number of Yemens) + (Number of Germanys) = ?", "Four", "Three", "Two", NULL, n66, 1);
    NODE* a68 = createNODE("1989-Early 1990", NULL, NULL, NULL, NULL, n68, 0);
    NODE* a69 = createNODE("Mid-1990", NULL, NULL, NULL, NULL, n68, 1);
    NODE* a70 = createNODE("Late 1990-1991", NULL, NULL, NULL, NULL, n68, 2);
    NODE* n69 = createNODE("Zaire? or: \"Hong Kong (UK)\"", "Yes", "No", NULL, NULL, n51, 1);
    n22->choice1 = n69;
    NODE* a71 = createNODE("1992-96", NULL, NULL, NULL, NULL, n69, 0);
    NODE* n70 = createNODE("Serbia/Montenegro are...", "One country", "Two countries", NULL, NULL, n69, 1);
    NODE* n71 = createNODE("East Timor?", "No", "Yes", NULL, NULL, n70, 0);
    NODE* a72 = createNODE("1997-2001", NULL, NULL, NULL, NULL, n71, 0);
    NODE* a73 = createNODE("2002-06", NULL, NULL, NULL, NULL, n71, 1);
    NODE* n72 = createNODE("How many Sudans are there?", "One", "Two", NULL, NULL, n70, 1);
    NODE* a74 = createNODE("2007-11", NULL, NULL, NULL, NULL, n72, 0);
    NODE* n73 = createNODE("Is Crimea disputed?", "Yes", "No", NULL, NULL, n72, 1);
    NODE* a75 = createNODE("2012-13", NULL, NULL, NULL, NULL, n73, 1);
    NODE* n74 = createNODE("\"Colorado\" or \"Danger—Radioactive Exclusion Zone—Avoid\"?", "Colorado", "Danger", NULL, NULL, n73, 0);
    NODE* a76 = createNODE("2014-21", NULL, NULL, NULL, NULL, n74, 0);
    NODE* n75 = createNODE("Does the warning mention the spiders?", "No", "Yes", NULL, NULL, n74, 1);
    NODE* a77 = createNODE("2022", NULL, NULL, NULL, NULL, n75, 0);
    NODE* a78 = createNODE("2023 or later", NULL, NULL, NULL, NULL, n75, 1);
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
