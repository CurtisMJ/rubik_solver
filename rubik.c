
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <sys/types.h>
#include <assert.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>

#include <sys/stat.h>
#define MAX_STACK_LEVELS 50

const char ascii[] = ""
 "     ___________\n"
 "   /___/___/___/|\n"
 "  /___/___/___/||\n"
 " /___/___/__ /|/|\n"
 "|   |   |   | /||\n"
 "|___|___|___|/|/|\n"
 "|   |   |   | /||\n"
 "|___|___|___|/|/\n"
 "|   |   |   | /\n"
 "|___|___|___|/\n";

 const char* asciix2[] ={
"__  __  ___",
"\\ \\/ / |__ \\",
" \\  /    / /",
" /  \\   / /_",
"/_/\\_\\ |____|"};

 const char* asciimoves[] = {
// 0,0
 "     __------->_ \n"
 "   /___/___/___/|\n"
 "  /___/___/___/||\n"
 " /___/___/__ /|/|\n"
 "| <-------- | /||\n"
 "|___|___|___|/|/|\n"
 "|   |   |   | /||\n"
 "|___|___|___|/|/ \n"
 "|   |   |   | /  \n"
 "|___|___|___|/   \n",
// 0,1
 "     __<-------_ \n"
 "   /___/___/___/|\n"
 "  /___/___/___/||\n"
 " /___/___/__ /|/|\n"
 "|  -------> | /||\n"
 "|___|___|___|/|/|\n"
 "|   |   |   | /||\n"
 "|___|___|___|/|/ \n"
 "|   |   |   | /  \n"
 "|___|___|___|/   \n",
// 1,0
"        ___________ \n"
"      /|   |   |   |\n"
"     / ||__|___|___|\n"
"    /|/||  |   |   |\n"
"   ||/ ||__|___|___|\n"
" ^ |/|/|v  |   |   |\n"
" | ||/ |___|___|___|\n"
" | |/|/ __/___/___/ \n"
" | ||/___/___/___/  \n"
"   |/___/___/___/   \n",
// 1,1
"        ___________ \n"
"      /|   |   |   |\n"
"     / |^__|___|___|\n"
"    /|/||  |   |   |\n"
"   ||/ ||__|___|___|\n"
" | |/|/||  |   |   |\n"
" | ||/ |___|___|___|\n"
" | |/|/ __/___/___/ \n"
" v ||/___/___/___/  \n"
"   |/___/___/___/   \n",
// 2,0
"     ___________ \n"
"   /___/___/___/|\n"
"  /___/___/___/||\n"
" /___/___/__ /|/|\n"
"|  -------> | /||\n"
"|___|___|___|/|/|\n"
"|   |   |   | /||\n"
"|___|___|___|/|/ \n"
"|   |   |   | /  \n"
"|__<------__|/   \n",
// 2,1
"     ___________ \n"
"   /___/___/___/|\n"
"  /___/___/___/||\n"
" /___/___/__ /|/|\n"
"|  <------- | /||\n"
"|___|___|___|/|/|\n"
"|   |   |   | /||\n"
"|___|___|___|/|/ \n"
"|   |   |   | /  \n"
"|__------>__|/   \n",
// 3, 0
 "     ___________    \n"
 "   /___/___/___/|   \n"
 "  /___/___/___/|| | \n"
 " /___/___/__ /|/| | \n"
 "|   |   |   | /|| | \n"
 "|___|___|__^|/|/| v \n"
 "|   |   |  || /||   \n"
 "|___|___|__||/|/    \n"
 "|   |   |  || /     \n"
 "|___|___|___|/      \n",
 // 3, 1
 "     ___________    \n"
 "   /___/___/___/|   \n"
 "  /___/___/___/|| ^ \n"
 " /___/___/__ /|/| | \n"
 "|   |   |   | /|| | \n"
 "|___|___|__||/|/| | \n"
 "|   |   |  || /||   \n"
 "|___|___|__||/|/    \n"
 "|   |   |  v| /     \n"
 "|___|___|___|/      \n",
 // 4, 0
 "     __<------__    \n"
 "   /___/___/___/|   \n"
 "  /___/___/___/|| ^ \n"
 " /___/___/__ /|/| | \n"
 "|   |   |   | /|| | \n"
 "|___|___|___|/|/| | \n"
 "|   |   |   | /||   \n"
 "|___|___|___|/|/    \n"
 "|   |   |   | /     \n"
 "|___|___|___|/      \n",
  // 4, 1
 "     __------>__    \n"
 "   /___/___/___/|   \n"
 "  /___/___/___/|| | \n"
 " /___/___/__ /|/| | \n"
 "|   |   |   | /|| | \n"
 "|___|___|___|/|/| v \n"
 "|   |   |   | /||   \n"
 "|___|___|___|/|/    \n"
 "|   |   |   | /     \n"
 "|___|___|___|/      \n",
 // 5,0
"     ___________ \n"
"   /|   |   |   |\n"
"  / |___|___|___|\n"
" /|/|   |   |   |\n"
"||/ |___|___|___|\n"
"|/|/|   |   |   |\n"
"||/ |___|___|___|\n"
"|/|/ __----->__/ \n"
"||/___/___/___/  \n"
"|/___<-----__/   \n",
 // 5,0
"     ___________ \n"
"   /|   |   |   |\n"
"  / |___|___|___|\n"
" /|/|   |   |   |\n"
"||/ |___|___|___|\n"
"|/|/|   |   |   |\n"
"||/ |___|___|___|\n"
"|/|/ __<-----__/ \n"
"||/___/___/___/  \n"
"|/___----->__/   \n"
};

// helper-function to print the current stack trace
void print_stacktrace()
{

}

void printascii(int move, int t2)
{
    if (t2 != 2)
    {
        puts(asciimoves[move]);
        return;
    }
    char cpy[300];
    strcpy(cpy, asciimoves[move]);
    char *p, *temp;
    p = strtok_r(cpy, "\n", &temp);
    int count = 0;
    do {
        if (count > 4)
        {
          puts(p);
        }
        else
          printf("%s   %s\n", p, asciix2[count]);
        ++count;
    } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);
puts("");
}

/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 */
int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    // Supporting larger values for n would requires an even more
    // elaborate implementation that combines multiple calls to rand()
    // Chop off all of the values that would cause skew...
    int end = RAND_MAX / n; // truncate skew
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}

/*
Sides:
  0
1 2 3 4
  5

Indices:
          0 1 2 
          3 4 5           ^0
          6 7 8  8 5 2  2 1 0       
        
2  0 1 2  0 1 2  0 1 2  0 1 2  0 
5  3 4 5  3 4 5  3 4 5  3 4 5  3 ^1
8  6 7 8  6 7 8  6 7 8  6 7 8  6
          
          0 1 2  2 5 8  8 7 6
          3 4 5           ^5
          6 7 8

Transformation directions:
Twist side clockwise:

Side 5:
   1.6 = 4.6
   1.7 = 4.7
   1.8 = 4.8
   2.6 = 1.6
   2.7 = 1.7
   2.8 = 1.8
   3.6 = 2.6
   3.7 = 2.7
   3.8 = 2.8
   4.6 = 3.6
   4.7 = 3.7
   4.8 = 3.8

Side 4:
    0.0 = 3.2
    0.1 = 3.5
    0.2 = 3.8
    1.0 = 0.2
    1.3 = 0.1
    1.6 = 0.0
    5.6 = 1.0
    5.7 = 1.3
    5.8 = 1.6
    3.2 = 5.8
    3.5 = 5.7
    3.8 = 5.6

Side 3:
    0.2 = 2.2
    0.5 = 2.5
    0.8 = 2.8
    2.2 = 5.2
    2.5 = 5.5
    2.8 = 5.8
    5.2 = 4.6
    5.5 = 4.3
    5.8 = 4.0
    4.0 = 0.8
    4.3 = 0.5
    4.6 = 0.2

Side 2:
    0.6 = 1.8
    0.7 = 1.5
    0.8 = 1.2
    1.2 = 5.0
    1.5 = 5.1
    1.8 = 5.2
    5.0 = 3.6
    5.1 = 3.3
    5.2 = 3.0
    3.0 = 0.6
    3.3 = 0.7
    3.6 = 0.8

Side 1:
    0.0 = 4.8
    0.3 = 4.5
    0.6 = 4.2
    2.0 = 0.0
    2.3 = 0.3
    2.6 = 0.6
    5.0 = 2.0
    5.3 = 2.3
    5.6 = 2.6
    4.2 = 5.6
    4.5 = 5.3
    4.8 = 5.0

Side 0:
    1.0 = 2.0
    1.1 = 2.1 
    1.2 = 2.2
    2.0 = 3.0
    2.1 = 3.1
    2.2 = 3.2
    3.0 = 4.0
    3.1 = 4.1
    3.2 = 4.2
    4.0 = 1.0
    4.1 = 1.1
    4.2 = 1.2

self -> 0 = 6
        1 = 3
        2 = 0
        5 = 1
        8 = 2
        7 = 5
        6 = 8
        3 = 7
        4 = 4

 Solving:
    given start cube,
    make all 12 possible moves, (move mapping)
    save 12 cubes to file, order of cubes determines moves made
    save move history to source cube for each file
    keep track on number of files
    flip-flop between 2 sets
    process all files in set generating another file for each dest cube in other set

*/

void err(char* msg)
{
    printf("Error: %s\n Stack:\n", msg);
    print_stacktrace();
    exit(EXIT_FAILURE);
}

typedef struct {
    void* prev;
    char moveno;
} movehist;

typedef struct {
    char cells[9];
} side;

typedef struct {
    side* sides[6];
} cube;

typedef struct {
    cube* cubes[12];
    movehist* lastmove;
    char solution;
} cubeset;

void init_side(side** _side, char num)
{
    *_side = malloc(sizeof(side));
    if (*_side == NULL) err("malloc()");
    for (char i = 0; i < 9; ++i)
    {
        (*_side)->cells[i] = num ;
    }
}

void init_cube(cube** _cube)
{
    *_cube = malloc(sizeof(cube));
    if (*_cube == NULL) err("malloc()");
    for (char i = 0; i < 6; ++i)
    {
        init_side(&((*_cube)->sides[i]), i);
    }
}

void clone_cube(cube* src, cube** dst)
{
    *dst = malloc(sizeof(cube));
    if (*dst == NULL) err("malloc()");
    for (char i = 0; i < 6; ++i)
    {
        (*dst)->sides[i] = malloc(sizeof(side));
        if ((*dst)->sides[i] == NULL) err("malloc()");
        *(*dst)->sides[i] = *src->sides[i];
    }
}

void free_cube(cube* _cube)
{
    for (char i = 0; i < 6; ++i)
    {
        free(_cube->sides[i]);
    }
    free(_cube);
}

char cube_solved(cube* _cube)
{
    // block 4 never changes
    for (char i = 0; i < 6; ++i)
    {
        char middle = _cube->sides[i]->cells[4];
        for (char x = 0; x < 9; ++x)
        {
            if (x == 4) continue;
            if (_cube->sides[i]->cells[x] != middle) return 0;
        }
    }
    return 1;
}

void dump_cube(FILE * file, cube* cube)
{
    for (char i = 0; i < 6; i++)
    {
        if (fwrite(cube->sides[i], sizeof(side), 1, file) != 1) err("fwrite()");
    }
}

void load_cube(FILE * file, cube** _cube)
{
    *_cube = malloc(sizeof(cube));
    if (*_cube == NULL) err("malloc()");
    for (char i = 0; i < 6; i++)
    {
        (*_cube)->sides[i] = malloc(sizeof(side));
        if ((*_cube)->sides[i] == NULL) err("malloc()");
        if (fread((*_cube)->sides[i], sizeof(side), 1, file) != 1) err("fread()");
    }
}

typedef struct {
    char side1[12];
    char cell1[12];
    char side2[12];
    char cell2[12];
} adjmapping;

adjmapping* adjmappings[6];

void init_mappings()
{
    adjmappings[0] = malloc(sizeof(adjmapping));
    if (adjmappings[0] == NULL) err("malloc()");
    memcpy(adjmappings[0]->side1, (const char[]){ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4 }, sizeof(adjmappings[0]->side1));
    memcpy(adjmappings[0]->cell1, (const char[]){ 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2 }, sizeof(adjmappings[0]->cell1));
    memcpy(adjmappings[0]->side2, (const char[]){ 2, 2, 2, 3, 3, 3, 4, 4, 4, 1, 1, 1 }, sizeof(adjmappings[0]->side2));
    memcpy(adjmappings[0]->cell2, (const char[]){ 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2 }, sizeof(adjmappings[0]->cell2));

    adjmappings[1] = malloc(sizeof(adjmapping));
    if (adjmappings[1] == NULL) err("malloc()");
    memcpy(adjmappings[1]->side1, (const char[]){ 0, 0, 0, 2, 2, 2, 5, 5, 5, 4, 4, 4 }, sizeof(adjmappings[1]->side1));
    memcpy(adjmappings[1]->cell1, (const char[]){ 0, 3, 6, 0, 3, 6, 0, 3, 6, 2, 5, 8 }, sizeof(adjmappings[1]->cell1));
    memcpy(adjmappings[1]->side2, (const char[]){ 4, 4, 4, 0, 0, 0, 2, 2, 2, 5, 5, 5 }, sizeof(adjmappings[1]->side2));
    memcpy(adjmappings[1]->cell2, (const char[]){ 8, 5, 2, 0, 3, 6, 0, 3, 6, 6, 3, 0 }, sizeof(adjmappings[1]->cell2));

    adjmappings[2] = malloc(sizeof(adjmapping));
    if (adjmappings[2] == NULL) err("malloc()");
    memcpy(adjmappings[2]->side1, (const char[]){ 0, 0, 0, 1, 1, 1, 5, 5, 5, 3, 3, 3 }, sizeof(adjmappings[2]->side1));
    memcpy(adjmappings[2]->cell1, (const char[]){ 6, 7, 8, 2, 5, 8, 0, 1, 2, 0, 3, 6 }, sizeof(adjmappings[2]->cell1));
    memcpy(adjmappings[2]->side2, (const char[]){ 1, 1, 1, 5, 5, 5, 3, 3, 3, 0, 0, 0 }, sizeof(adjmappings[2]->side2));
    memcpy(adjmappings[2]->cell2, (const char[]){ 8, 5, 2, 0, 1, 2, 6, 3, 0, 6, 7, 8 }, sizeof(adjmappings[2]->cell2));

    adjmappings[3] = malloc(sizeof(adjmapping));
    if (adjmappings[3] == NULL) err("malloc()");
    memcpy(adjmappings[3]->side1, (const char[]){ 0, 0, 0, 2, 2, 2, 5, 5, 5, 4, 4, 4 }, sizeof(adjmappings[3]->side1));
    memcpy(adjmappings[3]->cell1, (const char[]){ 2, 5, 8, 2, 5, 8, 2, 5, 8, 0, 3, 6 }, sizeof(adjmappings[3]->cell1));
    memcpy(adjmappings[3]->side2, (const char[]){ 2, 2, 2, 5, 5, 5, 4, 4, 4, 0, 0, 0 }, sizeof(adjmappings[3]->side2));
    memcpy(adjmappings[3]->cell2, (const char[]){ 2, 5, 8, 2, 5, 8, 6, 3, 0, 8, 5, 2 }, sizeof(adjmappings[3]->cell2));

    adjmappings[4] = malloc(sizeof(adjmapping));
    if (adjmappings[4] == NULL) err("malloc()");
    memcpy(adjmappings[4]->side1, (const char[]){ 0, 0, 0, 1, 1, 1, 5, 5, 5, 3, 3, 3 }, sizeof(adjmappings[4]->side1));
    memcpy(adjmappings[4]->cell1, (const char[]){ 0, 1, 2, 0, 3, 6, 6, 7, 8, 2, 5, 8 }, sizeof(adjmappings[4]->cell1));
    memcpy(adjmappings[4]->side2, (const char[]){ 3, 3, 3, 0, 0, 0, 1, 1, 1, 5, 5, 5 }, sizeof(adjmappings[4]->side2));
    memcpy(adjmappings[4]->cell2, (const char[]){ 2, 5, 8, 2, 1, 0, 0, 3, 6, 8, 7, 6 }, sizeof(adjmappings[4]->cell2));

    adjmappings[5] = malloc(sizeof(adjmapping));
    if (adjmappings[5] == NULL) err("malloc()");
    memcpy(adjmappings[5]->side1, (const char[]){ 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4 }, sizeof(adjmappings[5]->side1));
    memcpy(adjmappings[5]->cell1, (const char[]){ 6, 7, 8, 6, 7, 8, 6, 7, 8, 6, 7, 8 }, sizeof(adjmappings[5]->cell1));
    memcpy(adjmappings[5]->side2, (const char[]){ 4, 4, 4, 1, 1, 1, 2, 2, 2, 3, 3, 3 }, sizeof(adjmappings[5]->side2));
    memcpy(adjmappings[5]->cell2, (const char[]){ 6, 7, 8, 6, 7, 8, 6, 7, 8, 6, 7, 8 }, sizeof(adjmappings[5]->cell2));
}

void free_mappings()
{
    for (char i = 0; i < 6; i++)
    {
        free(adjmappings[i]);
    }
}

char twistMap1[9] = { 0, 1, 2, 5, 8, 7, 6, 3, 4 };
char twistMap2[9] = { 6, 3, 0, 1, 2, 5, 8, 7, 4 };
char temp[12];

void twist_single_side(side* _side, char dir)
{
    char i;
    if (!dir)
    {
        for (i = 0; i < 9; ++i)
        {
            temp[twistMap1[i]] = _side->cells[twistMap2[i]];
        }
    }
    else
    {
        for (i = 0; i < 9; ++i)
        {
            temp[twistMap2[i]] = _side->cells[twistMap1[i]];
        }
    }
    for (i = 0; i < 9; ++i)
    {
        _side->cells[i] = temp[i];
    }
}

void apply_adj_mapping(cube* _cube, char sideno, char dir)
{
    char i;
    if (!dir)
    {
        for (i = 0; i < 12; ++i)
        {
            temp[i] = _cube->sides[adjmappings[sideno]->side2[i]]->cells[adjmappings[sideno]->cell2[i]];
        }
        for (i = 0; i < 12; ++i)
        {
            _cube->sides[adjmappings[sideno]->side1[i]]->cells[adjmappings[sideno]->cell1[i]] = temp[i];
        }
    }
    else
    {
        for (i = 0; i < 12; ++i)
        {
            temp[i] = _cube->sides[adjmappings[sideno]->side1[i]]->cells[adjmappings[sideno]->cell1[i]];
        }
        for (i = 0; i < 12; ++i)
        {
            _cube->sides[adjmappings[sideno]->side2[i]]->cells[adjmappings[sideno]->cell2[i]] = temp[i];
        }
    }
}

void twist(cube* _cube, char sideno, char dir)
{
    twist_single_side(_cube->sides[sideno], dir);
    apply_adj_mapping(_cube, sideno, dir);
}

void print_row(side* _side, char startindex)
{
    for (char i = 0; i < 3; ++i )
    {
        printf("%d ", _side->cells[i + startindex]);
    }
    printf(" ");
}

void print_cube(cube* _cube)
{
    printf("       ");             print_row(_cube->sides[0], 0); printf("\n");
    printf("       ");             print_row(_cube->sides[0], 3); printf("\n");
    printf("       ");             print_row(_cube->sides[0], 6); printf("\n"); printf("\n");
    print_row(_cube->sides[1], 0); print_row(_cube->sides[2], 0); print_row(_cube->sides[3], 0); print_row(_cube->sides[4], 0); printf("\n");
    print_row(_cube->sides[1], 3); print_row(_cube->sides[2], 3); print_row(_cube->sides[3], 3); print_row(_cube->sides[4], 3); printf("\n"); 
    print_row(_cube->sides[1], 6); print_row(_cube->sides[2], 6); print_row(_cube->sides[3], 6); print_row(_cube->sides[4], 6); printf("\n"); printf("\n");
    printf("       ");             print_row(_cube->sides[5], 0); printf("\n");
    printf("       ");             print_row(_cube->sides[5], 3); printf("\n");
    printf("       ");             print_row(_cube->sides[5], 6); printf("\n");
    printf("solved? %s\n", cube_solved(_cube) ? "yes" : "no");
}
                    //   0  1  2  3  4  5  6  7  8  9  10  11 
char moveMapSide[12] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4,  5,  5 };
char moveMapDir[12]  = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,  0,  1 };
char moveMapComp[12] = { 1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10 };

typedef struct {
    char side, dir;
    int streak;
    void* prev;
} movestash;

movestash * laststash = NULL;

void stashmove(char side, char dir)
{
    movestash * stash; 
    if (laststash != NULL)
    {
        if (laststash->side == side)
        {
            if (laststash->dir == dir)
            {
                ++laststash->streak;
                if (laststash->streak == 3)
                {
                    laststash->dir = !laststash->dir;
                    laststash->streak = 1;
                }
            }
            else
            {
                --laststash->streak;
                if (laststash->streak < 1)
                {
                    stash = laststash;
                    laststash = laststash->prev;
                    free(stash);
                }
            }
            return;
        }
    } 

    stash = malloc(sizeof(movestash));
    if (stash == NULL) err("malloc()");
    stash->prev = laststash;
    stash->side = side;
    stash->dir = dir;
    stash->streak = 1;
    laststash = stash;
}

void print_ins(char side, char dir)
{
    //printf("Turn side %d %s\n", side + 1, (dir ? "counter-clockwise" : "clockwise"));
    stashmove(side, dir);
}

void dump_inst()
{
    int moves = 0, count, streakc, side, dir;
    movestash* curr_move = laststash;
    while (curr_move != NULL)
    {
        ++moves;
        curr_move = curr_move->prev;
    }
    streakc = count = moves;
    moves *= 2;
    printf("st %d cn %d mv %d\n", streakc, count, moves);
    char * movestream = malloc(moves * sizeof(char));
    int * streaks = malloc(streakc * sizeof(int));
    curr_move = laststash;
    while (curr_move != NULL)
    {
        movestream[--moves] = curr_move->dir;
        movestream[--moves] = curr_move->side;
        streaks[--streakc] = curr_move->streak;
        curr_move = curr_move->prev;
    }
    puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    for (int i = 0; i < count; ++i)
    {   
        moves = i * 2;
        side = movestream[moves];
        dir = movestream[moves + 1];
        if (streaks[i] > 1)
            printf("Turn side %d %s x%d\n", movestream[moves] + 1, (movestream[moves + 1] ? "counter-clockwise" : "clockwise"), streaks[i]);
        else
            printf("Turn side %d %s\n", movestream[moves] + 1, (movestream[moves + 1] ? "counter-clockwise" : "clockwise"));

        printascii((side * 2) + dir, streaks[i]);
        
        if (((i + 1) % 2 == 0) && ((i + 1) < count))
        {
            printf("%d/%d\n-----------------\nPress any key...", (i + 1), count);
            getchar();
            puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
    }
    puts("Done!\n----------------------------------");
}

void print_solution(cubeset* set)
{
    char * movestream;
    int moves = 1, count;
    movehist* curr_move = set->lastmove;
    while (curr_move != NULL)
    {
        ++moves;
        curr_move = curr_move->prev;
    }
    movestream = malloc(sizeof(char) * moves);
    count = moves;
    curr_move = set->lastmove;
    movestream[--moves] = set->solution;
    while (curr_move != NULL)
    {
        movestream[--moves] = curr_move->moveno;
        curr_move = curr_move->prev;
    }
    for (int i = 0; i < count; ++i)
    {
        print_ins(moveMapSide[movestream[i]], moveMapDir[movestream[i]]);
    }
}

void twistp(cube* _cube, char sideno, char dir)
{
    twist(_cube, sideno, dir);
    print_ins(sideno, dir);
}


void add_movehist(cubeset* set, char move)
{
    movehist* new_move = malloc(sizeof(movehist));
    if (new_move == NULL) err("malloc()");
    new_move->moveno = move;
    new_move->prev = set->lastmove;
    set->lastmove = new_move;
}

void copy_movehist(movehist* src, movehist** dest)
{
    if (src == NULL) return;
    movehist* tmp;
    tmp = malloc(sizeof(movehist));
    if (tmp == NULL) err("malloc()");
    *dest = tmp;
    tmp->moveno = src->moveno;
    tmp->prev = NULL;
    src = src->prev;
    while (src != NULL)
    {
        tmp->prev = malloc(sizeof(movehist));
        if (tmp->prev == NULL) err("malloc()");
        tmp = tmp->prev;
        tmp->moveno = src->moveno;
        tmp->prev = NULL;
        src = src->prev;
    }
}

const char histterm = 12;

char isdud(movehist* lastmove, char move)
{
    if (lastmove == NULL) return 0;
    if (lastmove->moveno == moveMapComp[move]) return 1;

    // if we can count at least 3 of the exact same move
    // backwards then a fourth is a dud as the entire sequence
    // doesnt really do much
    for (char i = 0; i < 3; ++i)
    {
        if ((lastmove == NULL) || (lastmove->moveno != move))
            return 0;

        lastmove = lastmove->prev;
    }
    return 1;
    
}

void init_set(cubeset** set, cube* start, movehist* lastmove, char move, char(*solvecrit)(cube* cube))
{
    *set = malloc(sizeof(cubeset));
    if (*set == NULL) err("malloc()");
    (*set)->lastmove = NULL;
    (*set)->solution = histterm; 
    copy_movehist(lastmove, &(*set)->lastmove);
    if (move != histterm) add_movehist(*set , move);
    // clone 12 cubes (minus a complementary move)
    char i;
    for (i = 0; i < 12; ++i)
    {
        if (isdud((*set)->lastmove, i))
        {
            (*set)->cubes[i] = NULL;
        }
        else
        {
            clone_cube(start, &(*set)->cubes[i]);
            twist((*set)->cubes[i], moveMapSide[i], moveMapDir[i]);
            //print_cube((*set)->cubes[i]);
            if ((*solvecrit)((*set)->cubes[i])) {
                (*set)->solution = i;
                break;
            }
        }
    }

}

void free_set(cubeset* set)
{
    if (set->solution < histterm)
        ++set->solution; 
    for (char i = 0; i < set->solution; ++i)
    {
        if (set->cubes[i] != NULL)
            free_cube(set->cubes[i]);
    }
    movehist* curr_move = set->lastmove, *prev;
    while (curr_move != NULL)
    {
        prev = (movehist*)curr_move->prev;
        free(curr_move);
        curr_move = prev;
    }
    free(set);
}

char cubeyes = 45, cubeno = 46;

void dump_set(FILE * file, cubeset* set)
{
    movehist* curr_move = set->lastmove;

    while (curr_move != NULL)
    {
        if (fwrite(&curr_move->moveno, sizeof(char), 1, file) != 1) err("fwrite()");
        curr_move = curr_move->prev;
    }
    if (fwrite(&histterm, sizeof(char), 1, file) != 1) err("fwrite()");
    for (char i = 0; i < 12; ++i)
    {
        if (set->cubes[i] != NULL)
        {
            if (fwrite(&cubeyes, sizeof(char), 1, file) != 1) err("fwrite()");
            dump_cube(file, set->cubes[i]);
        }
        else if (fwrite(&cubeno, sizeof(char), 1, file) != 1) err("fwrite()");
    }
}

void load_set(FILE * file, cubeset** set)
{
    *set = malloc(sizeof(cubeset));
    if (*set == NULL) err("malloc()");
    // read move history first
    (*set)->lastmove = NULL;
    (*set)->solution = histterm; 
    char src;
    if (fread(&src, sizeof(char), 1, file) != 1) err("fread(1)");
    if ((src < 0) || (src > histterm)) { printf("src: %d\n", src); err("malformed file(1)"); };
    if (src != histterm)
    {
        movehist* tmp;
        tmp = malloc(sizeof(movehist));
        if (tmp == NULL) err("malloc()");
        (*set)->lastmove = tmp;
        tmp->moveno = src;
        tmp->prev = NULL;
        if (fread(&src, sizeof(char), 1, file) != 1) err("fread(2)"); 
        if ((src < 0) || (src > histterm)) err("malformed file(2)");
        while (src != histterm)
        {
            tmp->prev = malloc(sizeof(movehist));
            if (tmp->prev == NULL) err("malloc()");
            tmp = tmp->prev;
            tmp->moveno = src;
            tmp->prev = NULL;
            if (fread(&src, sizeof(char), 1, file) != 1) err("fread(3)");
            if ((src < 0) || (src > histterm)) err("malformed file(3)");
        }
    }
    char cubestate;
    for (char i = 0; i < 12; ++i)
    {
        if (fread(&cubestate, sizeof(char), 1, file) != 1) err("fread(4)");
        if (cubestate == cubeno)
        {
            (*set)->cubes[i] = NULL;
        }
        else if (cubestate == cubeyes)
        {
            load_cube(file, &(*set)->cubes[i]);
        }
        else 
            err("malformed set(1)");
    }

}

void mutate_set(cubeset *src, cubeset **dstarr, char(*solvecrit)(cube* cube))
{
    // for each cube in the src set, init a set
    // copy move history and add the move of the
    // cube that it was inited from. Blank cubes
    // are complementary moves
    cubeset* res;
    char i;
    for (i = 0; i < 12; ++i)
    {
        if (src->cubes[i] == NULL)
        {   
            dstarr[i] = NULL;
            continue;
        }
        init_set(&res, src->cubes[i], src->lastmove, i, solvecrit);
        dstarr[i] = res;
        if (res->solution != histterm)
            break;
    }
}

typedef struct 
{
    void *prev;
    int indice;
} indice;

void add_indice(indice **last, int _indice)
{
    indice *newind = malloc(sizeof(indice));
    if (newind == NULL) err("malloc()");
    newind->prev = *last;
    newind->indice = _indice;
    *last = newind;
}

void free_indices(indice *last)
{
    indice* currind = last, *prev;
    while (currind != NULL)
    {
        prev = (indice*)currind->prev;
        free(currind);
        currind = prev;
    }
}

void capture_cell(side* side, int i, char* col, int coli)
{	
	char* cell = &(side->cells[(i*3) + coli]);

		if (strcmp("r", col) == 0)
			*cell = 0;
			else
		if (strcmp("b", col) == 0)
			*cell = 1;
			else
		if (strcmp("w", col) == 0)
			*cell = 2;
			else
		if (strcmp("g", col) == 0)
			*cell = 3;
			else
		if (strcmp("y", col) == 0)
			*cell = 4;
			else
		if (strcmp("o", col) == 0)
			*cell = 5;
			
}

void capture_side(side* side)
{
	char** caps;
	caps = malloc(sizeof(char*) * 3);
	caps[0] = malloc(sizeof(char) * 80);
	caps[1] = malloc(sizeof(char) * 80);
	caps[2] = malloc(sizeof(char) * 80);
	printf("x x x *3\n");
	for (int i = 0; i < 3; ++i)
	{
		scanf("%s %s %s", caps[0], caps[1], caps[2]);
		capture_cell(side, i, caps[0], 0);
		capture_cell(side, i, caps[1], 1);
		capture_cell(side, i, caps[2], 2);
	}
	free(caps[0]);
	free(caps[1]);
	free(caps[2]);
	free(caps);
}

char setterm = 56, setcont = 57;
char tempdir[] = "rubiktmp";



void bruteforce(cube** start, char(*solvecrit)(cube* cube))
{
    rmdir(tempdir);
    if (mkdir(tempdir, 0700)) err("mkdir");
    cubeset* set;
    init_set(&set, *start, NULL, histterm, solvecrit);
    cubeset *mutset[12];
    int x;
    for (x = 0; x < 12; ++x)
    {
        mutset[x] = NULL;
    }
    FILE *fo, *fd;
    indice *validsets, *prevvalidset;
    validsets = NULL;
    char fn[PATH_MAX];
    long long level = 0;
    char flipflop = 0, setdiv;
    snprintf(fn, PATH_MAX, "%s/%d.bin", tempdir, flipflop);
    fd = fopen(fn, "wb");
    if (fd == NULL) err("fopen()");
    dump_set(fd, set);
    free_set(set);
    if (fwrite(&setterm, sizeof(char), 1, fd) != 1) err("fwrite()");
    if (fclose(fd)) err("fclose()");
    for (;;)
    {
        snprintf(fn, PATH_MAX, "%s/%d.bin", tempdir, flipflop);
        fd = fopen(fn, "rb");
        if (fd == NULL) err("fopen()");
        flipflop = !flipflop;
        snprintf(fn, PATH_MAX, "%s/%d.bin", tempdir, flipflop);
        fo = fopen(fn, "wb");
        if (fo == NULL) err("fopen()");
        for (;;)
        {
            load_set(fd, &set);
            mutate_set(set, mutset, solvecrit);
            free_set(set);
            for (int i = 11; i >= 0; --i)
            {
                if (mutset[i] != NULL)
                    add_indice(&validsets, i);
            }

            while (validsets != NULL)
            {
                if (mutset[validsets->indice]->solution != histterm)
                {
                    print_solution(mutset[validsets->indice]);
                    
                    if (fclose(fd)) err("fclose()");
                    if (fclose(fo)) err("fclose()");
                    rmdir(tempdir);
                    free_cube(*start);
                    clone_cube(mutset[validsets->indice]->cubes[mutset[validsets->indice]->solution], start);
                    free_set(mutset[validsets->indice]); 
                    return;
                }
                else
                {
                    dump_set(fo, mutset[validsets->indice]);
                    if (validsets->prev != NULL)
                    {
                        if (fwrite(&setcont, sizeof(char), 1, fo) != 1) err("fwrite()");
                    }
                    free_set(mutset[validsets->indice]); 
                }
                prevvalidset = validsets->prev;
                free(validsets);
                validsets = prevvalidset;
            }
            
            if (fread(&setdiv, sizeof(char), 1, fd) != 1) err("fread()");
            if (!((setdiv == setterm) || (setdiv == setcont))) err("malformed superset");
            if (fwrite(&setdiv, sizeof(char), 1, fo) != 1) err("fwrite()");
            if (setdiv == setterm) break;
        }
        if (fclose(fd)) err("fclose()");
        if (fclose(fo)) err("fclose()");
        ++level;
    }
}

char stage1daisy_solvecrit(cube* _cube)
{
    int opside = _cube->sides[0]->cells[4];
    return ((_cube->sides[5]->cells[1] == opside) && (_cube->sides[5]->cells[3] == opside) && (_cube->sides[5]->cells[5] == opside) && (_cube->sides[5]->cells[7] == opside));
}

char stage2dud_solvecrit(cube* _cube)
{
    int topside = _cube->sides[0]->cells[4];
    int i = 0;
    for (i = 0; i < 9; ++i)
    {
        if (i == 4) continue;
        if (_cube->sides[0]->cells[i] != topside)
            return 0;
    }
    for (i = 1; i < 5; ++i)
    {
        topside = _cube->sides[i]->cells[4];
        if ((_cube->sides[i]->cells[0] != topside) || (_cube->sides[i]->cells[1] != topside) || (_cube->sides[i]->cells[2] != topside))
            return 0;
    }
    return 1;
}

void stage2(cube** _cube)
{
    puts("\nFirst stage:\n----------------------------");
    /* Create "daisy" */
    puts("Bottom \"Daisy\"\n------------------");
    bruteforce(_cube, stage1daisy_solvecrit);
    /* twist over to white cross */
    
    puts("------------------\nTop \"Cross\"\n------------------");
    cube* cb = *_cube;
    char sidesdn = 0;
    int topmap[5] = { -1, 3, 1, 5, 7 };
    int topside = cb->sides[0]->cells[4];
    while (sidesdn < 4)
    {
        for (int i = 1; i < 5; i++)
        {
            if ((cb->sides[5]->cells[topmap[i]] == topside) && (cb->sides[i]->cells[7] == cb->sides[i]->cells[4]))
            {
                twistp(cb, i, 0);
                twistp(cb, i, 0);
                ++sidesdn;
            }
        }
        if (sidesdn < 4)
        {
            twistp(cb, 5, 0);
        }
    }
    puts("----------------------------"); 
    print_cube(*_cube); 
}

void stage3(cube** _cb)
{
    cube* cb = *_cb;
    puts("----------------------------\nSecond stage:\n----------------------------");
    int topside = cb->sides[0]->cells[4];
    char clean = 0;
    int i;
    puts("------------------\nSolve Corners\n------------------");
    int adjfc;
    int btmapcel[4] = { 0, 2, 8, 6 };
    int btmapcel2[4] = { 6, 0, 2, 8 };
    int btmapsid1[4] = { 2, 3, 4, 1 };
    int btmapsid2[4] = { 1, 2, 3, 4 };
    while (clean < 20)
    {  
        clean = 0;

        for (i = 1; i < 5; ++i)
        {   
            if (cb->sides[i]->cells[8] != topside) ++clean;
            else
            {
                adjfc = i + 1;
                if (adjfc > 4) adjfc = 1;
                if ((cb->sides[adjfc]->cells[6] ==  cb->sides[adjfc]->cells[4]) && (cb->sides[5]->cells[btmapcel[i-1]] ==  cb->sides[i]->cells[4]))
                {
                    twistp(cb, 5, 1);
                    twistp(cb, i, 1);
                    twistp(cb, 5, 0);
                    twistp(cb, i, 0);
                    continue;
                }
            }

            if (cb->sides[i]->cells[6] != topside) ++clean;
            else
            {
                adjfc = i - 1;
                if (adjfc < 1) adjfc = 4;
                if ((cb->sides[adjfc]->cells[8] ==  cb->sides[adjfc]->cells[4]) && (cb->sides[5]->cells[btmapcel2[i-1]] ==  cb->sides[i]->cells[4]))
                {
                    twistp(cb, i, 1);
                    twistp(cb, 5, 1);
                    twistp(cb, i, 0);
                    continue;
                }
            }
        }

        for (i = 0; i < 4; ++i)
        {
            if (cb->sides[5]->cells[btmapcel[i]] != topside) ++clean;
            else
            {
                if ((cb->sides[btmapsid1[i]]->cells[6] ==  cb->sides[btmapsid2[i]]->cells[4]) && (cb->sides[btmapsid2[i]]->cells[8] ==  cb->sides[btmapsid1[i]]->cells[4]))
                {
                    twistp(cb, btmapsid1[i], 1);
                    twistp(cb, 5, 1);
                    twistp(cb, 5, 1);
                    twistp(cb, btmapsid1[i], 0);
                    twistp(cb, 5, 0);
                    twistp(cb, btmapsid1[i], 1);
                    twistp(cb, 5, 1);
                    twistp(cb, btmapsid1[i], 0);
                    continue;
                }
            }
        }

        if (clean < 12)
        {
            twistp(cb, 5, 0);
        }

        for (i = 1; i < 5; ++i)
        {
            if (cb->sides[i]->cells[0] != topside) ++clean;
            else
            {
                twistp(cb, i, 1);
                twistp(cb, 5, 1);
                twistp(cb, i, 0);
                continue;
            }
            if (cb->sides[i]->cells[2] != topside) ++clean;
            else
            {
                twistp(cb, i, 0);
                twistp(cb, 5, 1);
                twistp(cb, i, 1);
                continue;
            } 
        }
    }
    print_cube(cb);
    char dud = stage2dud_solvecrit(cb);
    printf("correct? %hhd\n", dud);
    if (!dud)
    {
        printf("could not resolve, bruteforcing remaining moves...\n");
        bruteforce(&cb, stage2dud_solvecrit);
        print_cube(cb);
        *_cb = cb;
    }
}


char stage3dud_solvecrit(cube* _cube)
{
    int topside = _cube->sides[0]->cells[4];
    int i = 0;
    for (i = 0; i < 9; ++i)
    {
        if (i == 4) continue;
        if (_cube->sides[0]->cells[i] != topside)
            return 0;
    }
    for (i = 1; i < 5; ++i)
    {
        topside = _cube->sides[i]->cells[4];
        if ((_cube->sides[i]->cells[0] != topside) || (_cube->sides[i]->cells[1] != topside) || (_cube->sides[i]->cells[2] != topside) || (_cube->sides[i]->cells[3] != topside) || (_cube->sides[i]->cells[5] != topside))
            return 0;
    }
    return 1;
}

void algo1(cube* cb, int side, int sideside, char isleft)
{
    twistp(cb, 5, !isleft);
    twistp(cb, sideside, !isleft);
    twistp(cb, 5, isleft);
    twistp(cb, sideside, isleft);
    twistp(cb, 5, isleft);
    twistp(cb, side, isleft);
    twistp(cb, 5, !isleft);
    twistp(cb, side, !isleft);
}

void stage4(cube** _cb)
{
    cube* cb = *_cb;
    puts("----------------------------\nThird stage:\n----------------------------");
    int sidemap[5] = { -1, 3, 1, 5, 7 };
    char count = 0;
    int sidel, sider;
    while (1)
    {
        for (int i = 1; i < 5; ++i)
        {
            sider = i + 1;
            if (sider > 4) sider = 1;
            sidel = i - 1;
            if (sidel < 1) sidel = 4;

            if ((cb->sides[i]->cells[5] == cb->sides[i]->cells[4])
            && (cb->sides[sider]->cells[3] != cb->sides[sider]->cells[4]))
            {
                algo1(cb, i, sider, 0);
                count = 0;
                continue;
            }

            if ((cb->sides[i]->cells[3] == cb->sides[i]->cells[4])
            && (cb->sides[sidel]->cells[5] != cb->sides[sidel]->cells[4]))
            {
                algo1(cb, i, sidel, 1);
                count = 0;
                continue;
            }

            if ((cb->sides[i]->cells[5] == cb->sides[sider]->cells[4])
            && (cb->sides[sider]->cells[3] == cb->sides[i]->cells[4]))
            {
                // wrong oriented piece, do twice
                algo1(cb, i, sider, 0);
                algo1(cb, i, sider, 0);
                count = 0;
                continue;
            }

            if ((cb->sides[i]->cells[3] == cb->sides[sidel]->cells[4])
            && (cb->sides[sidel]->cells[5] == cb->sides[i]->cells[4]))
            {
                // wrong oriented piece, do twice
                algo1(cb, i, sider, 0);
                algo1(cb, i, sider, 0);
                count = 0;
                continue;
            }

            if (cb->sides[i]->cells[7] == cb->sides[i]->cells[4])
            {
                
                if (cb->sides[5]->cells[sidemap[i]] == cb->sides[sider]->cells[4])
                {
                    algo1(cb, i, sider, 0);
                    count = 0;
                    continue;
                }
                
                if (cb->sides[5]->cells[sidemap[i]] == cb->sides[sidel]->cells[4])
                {
                    algo1(cb, i, sidel, 1);
                    count = 0;
                    continue;
                }
            }
        }
        twistp(cb, 5, 0);
        count++;
        if (count >= 4) 
        {
            if (stage3dud_solvecrit(cb)) break;
            else
            {
                for (int i = 1; i < 5; ++i)
                {
                    sider = i + 1;
                    if (sider > 4) sider = 1;
                    sidel = i - 1;
                    if (sidel < 1) sidel = 4;
                    if (cb->sides[i]->cells[3] != cb->sides[i]->cells[4])
                    {
                        algo1(cb, i, sidel, 1);
                        count = 0;
                        continue;
                    }

                    if (cb->sides[i]->cells[5] != cb->sides[i]->cells[4])
                    {
                        algo1(cb, i, sider, 0);
                        count = 0;
                        continue;
                    }
                }
          
            }
        }
    }
    print_cube(cb);
}

/* 
Instruction translations:
Sides:
R - 3
L - 1
U - 0
D - 5
F - 2
B - 4


          0 1 2 
          3 4 5           ^0
          6 7 8  8 5 2  2 1 0       
        
2  0 1 2  0 1 2  0 1 2  0 1 2  0 
5  3 4 5  3 4 5  3 4 5  3 4 5  3 ^1
8  6 7 8  6 7 8  6 7 8  6 7 8  6
          
          0 1 2  2 5 8  8 7 6
          3 4 5           ^5
          6 7 8

        if twist adjmapping[side] clockwise, then side 1 cell 1 will equal side 2 cell 2
*/

void stage5(cube **_cb)
{
    cube* cb = *_cb;
    puts("----------------------------\nFourth stage:\n----------------------------");
    char ycels[4] = {0,0,0,0};
    if ((cb->sides[5]->cells[1] != cb->sides[5]->cells[4])
     && (cb->sides[5]->cells[3] != cb->sides[5]->cells[4])
     && (cb->sides[5]->cells[7] != cb->sides[5]->cells[4])
     && (cb->sides[5]->cells[5] != cb->sides[5]->cells[4]))
    {
        // "dot"
        puts("------------------\nCreate Pattern\n------------------");
        twistp(cb, 2, 0);
        twistp(cb, 5, 0);
        twistp(cb, 1, 0);
        twistp(cb, 5, 1);
        twistp(cb, 1, 1);
        twistp(cb, 2, 1);
        print_cube(cb);
    }
    if (cb->sides[5]->cells[1] == cb->sides[5]->cells[4]) { ycels[0] = 1; }
    if (cb->sides[5]->cells[3] == cb->sides[5]->cells[4]) { ycels[1] = 1; }
    if (cb->sides[5]->cells[7] == cb->sides[5]->cells[4]) { ycels[2] = 1; }
    if (cb->sides[5]->cells[5] == cb->sides[5]->cells[4]) { ycels[3] = 1; }
    /* 
      State 3:
        x y x
        y y x
        x x x
      State 4:
        x x x
        y y y
        x x x

       */
    int fside, tside = 5, rside, ptype;
    if (ycels[0] && ycels[1] && !ycels[2] && !ycels[3])
    {
        /* x y x
           y y x
           x x x */
        ptype = 3;
        fside = 4;
        rside = 3;
    }
    else if (ycels[1] && ycels[2] && !ycels[0] && !ycels[3])
    {
        /* x x x
           y y x
           x y x */
        ptype = 3;
        fside = 3;
        rside = 2;
    }
    else if (ycels[2] && ycels[3] && !ycels[0] && !ycels[1])
    {
        /* x x x
           x y y
           x y x */
        ptype = 3;
        fside = 2;
        rside = 1;
    }
    else if (ycels[3] && ycels[0] && !ycels[1] && !ycels[2])
    {
        /* x y x
           x y y
           x x x */
        ptype = 3;
        fside = 1;
        rside = 4;
    }
    else if (ycels[1] && ycels[3] && !ycels[0] && !ycels[2])
    {
        /* x x x
           y y y
           x x x */
        ptype = 4;
        fside = 4;
        rside = 3;
    }
    else if (ycels[0] && ycels[2] && !ycels[1] && !ycels[3])
    {
        /* x y x
           x y x
           x y x */
        ptype = 4;
        fside = 3;
        rside = 2;
    }
    else if (ycels[0] && ycels[1] && ycels[2] && ycels[3])
    {
        /* x y x
           y y y
           x y x */
        ptype = 1;
    }

    puts("------------------\nBottom \"Cross\"\n------------------");
    switch (ptype)
    {
        case 3:
            twistp(cb, fside, 0);
            twistp(cb, tside, 0);
            twistp(cb, rside, 0);
            twistp(cb, tside, 1);
            twistp(cb, rside, 1);
            twistp(cb, fside, 1);
            break;
        case 4:
            twistp(cb, fside, 0);
            twistp(cb, rside, 0);
            twistp(cb, tside, 0);
            twistp(cb, rside, 1);
            twistp(cb, tside, 1);
            twistp(cb, fside, 1);
            break;
        case 1:
            // already solved
            printf("already done\n");
            break;
        default:
            err("unknown pattern\n");
            break;
    }
    print_cube(cb);

    puts("------------------\nBottom Face\n------------------");
    char cornc = 0;
    int i;
    
    while (1)
    {
        cornc = 0;
        if (cb->sides[5]->cells[0] == cb->sides[5]->cells[4]) { ++cornc; }
        if (cb->sides[5]->cells[2] == cb->sides[5]->cells[4]) { ++cornc; }
        if (cb->sides[5]->cells[8] == cb->sides[5]->cells[4]) { ++cornc; }
        if (cb->sides[5]->cells[6] == cb->sides[5]->cells[4]) { ++cornc; }
        if (cornc >= 4) break;
        
        switch (cornc)
        {
            case 0:
                for (i = 1; i < 5; ++i)
                {
                    if (cb->sides[i]->cells[6] == cb->sides[5]->cells[4])
                        break;
                }
                if (i >= 5)
                {
                    err("no match side found\n");
                }
                fside = i - 1;
                if (fside < 1) fside = 4;
                rside = fside - 1;
                if (rside < 1) rside = 4;
                break;
            case 1:
                if (cb->sides[5]->cells[0] == cb->sides[5]->cells[4]) { fside = 1; rside = 4; }
                if (cb->sides[5]->cells[2] == cb->sides[5]->cells[4]) { fside = 2; rside = 1; }
                if (cb->sides[5]->cells[8] == cb->sides[5]->cells[4]) { fside = 3; rside = 2; }
                if (cb->sides[5]->cells[6] == cb->sides[5]->cells[4]) { fside = 4; rside = 3; }
                break;
            case 2:
                for (i = 1; i < 5; ++i)
                {
                    if (cb->sides[i]->cells[8] == cb->sides[5]->cells[4])
                        break;
                }
                if (i >= 5)
                {
                    err("no match side found\n");
                }
                fside = i;
                rside = fside - 1;
                if (rside < 1) rside = 4;
                break;
            default:
                err("unknown pattern\n");
                break;
        }

        twistp(cb, rside, 0);
        twistp(cb, tside, 0);
        twistp(cb, rside, 1);
        twistp(cb, tside, 0);
        twistp(cb, rside, 0);
        twistp(cb, tside, 0);
        twistp(cb, tside, 0);
        twistp(cb, rside, 1);
    }
    print_cube(cb);
    puts("------------------\nBottom Corners\n------------------");
    
    char corns[4];
    int bside;
    while (1)
    {
        cornc = 0;
        for (i = 1; i < 5; ++i)
        {
            rside = i + 1;
            if (rside > 4) rside = 1;
            if (corns[i - 1] = ((cb->sides[i]->cells[8] == cb->sides[i]->cells[4]) && (cb->sides[rside]->cells[6] == cb->sides[rside]->cells[4])))
            {
                ++cornc;
            }
        }
        if (cornc < 2)
        {
            twistp(cb, 5, 0);
            continue;
        }
        if (cornc >= 4) break;

        if (corns[0] && corns[1])
        {
            fside = 4;
            rside = 3;
            bside = 2;
        }
        else if (corns[1] && corns[2])
        {
            fside = 1;
            rside = 4;
            bside = 3;
        }
        else if (corns[2] && corns[3])
        {
            fside = 2;
            rside = 1;
            bside = 4;
        }
        else if (corns[3] && corns[0])
        {
            fside = 3;
            rside = 2;
            bside = 1;
        }
        else // diagonal
        {
            fside = 4;
            rside = 3;
            bside = 2;
        }

        twistp(cb, rside, 1);
        twistp(cb, fside, 0);
        twistp(cb, rside, 1);
        twistp(cb, bside, 0);
        twistp(cb, bside, 0);
        twistp(cb, rside, 0);
        twistp(cb, fside, 1);
        twistp(cb, rside, 1);
        twistp(cb, bside, 0);
        twistp(cb, bside, 0);
        twistp(cb, rside, 0);
        twistp(cb, rside, 0);
        twistp(cb, tside, 1);
    }
    print_cube(cb);

    puts("------------------\nBottom Edges\n------------------");
    /* 0 0 0 
       0 0 0 
       0 0 0         
        
1 1 1  2 2 2  3 3 3  4 4 4   
1 1 1  2 2 2  3 3 3  4 4 4  
1 1 1  2 2 2  3 3 3  4 4 4  
         1  
       0 1 2  2 5 8  8 7 6
     0 3 4 5 2          ^5
       6 7 8
         3  
    */
    int lside;
    while (1)
    {
        cornc = 0;
        for (i = 1; i < 5; ++i)
        {
            rside = i + 1;
            if (rside > 4) rside = 1;
            if (corns[i - 1] = (cb->sides[i]->cells[7] == cb->sides[i]->cells[4]))
            {
                ++cornc;
            }
        }
        if (cornc >= 4) break;
        switch (cornc)
        {
            case 0:
                ptype = 1;
                fside = 2;
                lside = 3;
                rside = 1;
                break;
            case 1:
                if (corns[0])
                {
                    fside = 3;
                    lside = 4;
                    rside = 2;
                    cornc = 1;
                }
                else if (corns[1])
                {
                    fside = 4;
                    lside = 1;
                    rside = 3;
                    cornc = 2;
                }
                else if (corns[2])
                {
                    fside = 1;
                    lside = 2;
                    rside = 4;
                    cornc = 3;
                }
                else if (corns[3])
                {
                    fside = 2;
                    lside = 3;
                    rside = 1;
                    cornc = 4;
                }
                bside = cb->sides[cornc]->cells[7];
                do 
                {
                    cornc++;
                    if (cornc > 4) cornc = 1;
                } while (!corns[cornc - 1]);
                ptype = (cb->sides[cornc]->cells[4] == bside);
                break;
            default:
                err("unkown pattern\n");
                break;
        }

        if (ptype)
        {
            twistp(cb, fside, 0);
            twistp(cb, fside, 0);
            twistp(cb, tside, 0);
            twistp(cb, lside, 0);
            twistp(cb, rside, 1);
            twistp(cb, fside, 0);
            twistp(cb, fside, 0);
            twistp(cb, lside, 1);
            twistp(cb, rside, 0);
            twistp(cb, tside, 0);
            twistp(cb, fside, 0);
            twistp(cb, fside, 0);
        }
        else
        {
            twistp(cb, fside, 0);
            twistp(cb, fside, 0);
            twistp(cb, tside, 1);
            twistp(cb, lside, 0);
            twistp(cb, rside, 1);
            twistp(cb, fside, 0);
            twistp(cb, fside, 0);
            twistp(cb, lside, 1);
            twistp(cb, rside, 0);
            twistp(cb, tside, 1);
            twistp(cb, fside, 0);
            twistp(cb, fside, 0);
        }
    }
    print_cube(cb);
}

int main(int argc, char** argv)
{
    puts(ascii);
    srand(time(NULL)); 
    init_mappings();
    cube* _cube;
    init_cube(&_cube);
    if ((argc == 2) && (strcmp(argv[1], "random") == 0))
    {
	    for (int i = 0; i < 1000; i++)
	    {
	    	twist(_cube, randint(6), randint(2));
	    }
    }
    else
    {
        puts("Sides:");
        print_cube(_cube);
        for (int i = 0; i < 6; ++i)
        {
            printf("Capture side %d:\nFormat: ", i);
            capture_side(_cube->sides[i]);
        }
    }
    print_cube(_cube);
    stage2(&_cube); 
    stage3(&_cube);
    stage4(&_cube);
    stage5(&_cube); 
    dump_inst();
    free_mappings();
    return 0; 
}
