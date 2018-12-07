/*--------------------------------------------------------------------------+
|	Visualizer code for Prog 06, Fall 2018									|
|																			|
|	[Remove this header comment block and replace by your own]				|
|																			|
|	This is the only source file that you should need to modify (you may	|
|	also want to add fields to the Node struct, in the Node.h header file).	|
|	I have indicated in comments where you need to add code ***MUST DO***	|
|	I have also indicated which part are better left untouched.				|
|	Please note that depending on whether you want/need joinable threads, 	|
|	you should enable or disable the USE_JOINABLE_THREADS setting below.	|
|																			|
|	Jean-Yves Hervé, 2018-11-29												|
+--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
//
#include "Node.h"
#include "gl_frontEnd.h"

//	is defined by some compilers, not by some others.
#ifndef M_PI
#define     M_PI				3.1415927f
#endif

//	Enable this if you want/need to use joinable threads in your code.
//	The main thread (which *must* be the glut/GL thread absolutely cannot
//	be blocked waiting for a thread.  Otherwise the display won't refresh
//	anymore.
#define USE_JOINABLE_THREADS	0

//==================================================================================
//	Function prototypes
//==================================================================================
void displayGridPane(void);
void displayStatePane(void);
void initializeApplication(char*);
void swapGrids(void);
unsigned int cellNewState(unsigned int i, unsigned int j);
Node* string2list(char* list, float length, float scale);
void* replacement(void* rRules);
void* createSearchThreads(void* notUsed);
void* search(void* sData);


#if USE_JOINABLE_THREADS
void* mainThreadFunc(void*);
#endif

//==================================================================================
//	Application-level global variables
//==================================================================================

//	Don't touch
GLint gWindowWidth, gWindowHeight;

//	Feel free to rename these variables if you don't like the identifier
Node* curveList;
GLfloat angleUnit;
GLfloat startX, startY;

int numRules;
struct replacementRules{
    Node* replacementList;
    Node* start;
    Node* end;
};

struct searchData{
    char* searchPattern;
    char* replacementPattern;
    float scale;
};

struct searchData** sDataArr;
pthread_mutex_t lock;
//==================================================================================
//	These are callback functions there are setup in glFrontEnd.c
//	You should never call them directly:  They will be called by glut.
//	I marked parts that are "don't touch."
//==================================================================================

//	This callback function is called when a keyboard event occurs
//	I include it here just in case you want to add controls to speedup or
//	slowdown the threads (adjusting the base sleep tim)
void keyboardHandler(unsigned char c, int x, int y)
{
    switch (c)
    {
        //	'ESC' --> exit the application
        case 27:
            exit(0);
            break;

        default:
            break;
    }
    glutPostRedisplay();
}


void drawCurve(void)
{
    //	This is OpenGL/glut magic.  Don't touch
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(startX, startY, 0);
    glColor3f(1.f, 0.f, 0.f);

    //	***MUST DO***
    //	Here you may have to add some synchronization code
    pthread_mutex_lock(&lock);
    Node* currentNode = curveList;
    while (currentNode != NULL)
    {
        printf("%c", currentNode->letter);
        switch(currentNode->letter)
        {
            case 'F':
                glBegin(GL_LINES);
                glVertex2f(0.f, 0.f);
                glVertex2f(currentNode->length, 0.f);
                glEnd();
                glTranslatef(currentNode->length, 0.f, 0.f);
                break;

            case 'f':
                glTranslatef(currentNode->length, 0.f, 0.f);
                break;

            case '+':
                glRotatef(angleUnit, 0.f, 0.f, 1.f);
                break;

            case '-':
                glRotatef(-angleUnit, 0.f, 0.f, 1.f);
                break;

            default:
                printf("Invalid character in curve string.\n");
                exit(10);
        }
        currentNode = currentNode->next;

    }
    pthread_mutex_unlock(&lock);
    printf("\n");
    //	This is OpenGL/glut magic.  Don't touch
    glutSwapBuffers();
}

#if USE_JOINABLE_THREADS
void* mainThreadFunc(void* arg)
	{
		//	This thread doesn't need any argument all the important variables
		//	would be global, unless you want to pass the path to the input file

		//	This is presumably where you would start creating the first threads
int count = 0;
		int keepGoing = 1;
		while (keepGoing)
		{
			//	presumably here you would be looking for threads that terminate
			//	and spawn new ones.
printf("main thread func looping [%d]\n", count++);
			//	I have nothing to do but sleep and loop forever.
			usleep(10000);
		}

		//	Nothing interesting to return
		return NULL;
	}
#endif



//	***MUST DO***
//--------------------------------------------------------------
//	Here you would be reading data from the input file
//	I simply hard-code initial values for the variables I need
//--------------------------------------------------------------
void initializeApplication(char* fileName)
{
    pthread_mutex_init(&lock, NULL);
    float width, height, x, y, length;
    float angle;
    float scale;
    char* rule;
    char* searchPattern;
    char* replacementPattern;

    char* line = (char*)malloc(sizeof(char));
    size_t len = 0;
    FILE* fp;
    fp = fopen(fileName, "r");


    fscanf(fp, "%f %f\n", &width, &height);
    gWindowWidth = width;
    gWindowHeight = height;

    fscanf(fp, "%f %f\n", &x, &y);
    startX = x;
    startY = y;

    fscanf(fp, "%f\n", &length);

    fscanf(fp, "%f\n", &angle);
    angleUnit = angle;

    getline(&line, &len, fp);
    curveList = string2list(line, length, 1);

    fscanf(fp,"%d\n", &numRules);
    printf("%d\n",numRules);
    //Can't read this line for some reason
    //sscanf(line, "%s %s %f", searchPattern, replacementPattern, &scale);
    //printf("%s",line);
    //createSearchThreads(searchPattern, replacementPattern, length, scale);
    sDataArr = (struct searchData**) calloc (numRules,sizeof(struct searchData*));
    for(int i = 0; i < numRules; i++)
    {
        getline(&line, &len, fp);
        sDataArr[i] = (struct searchData*)malloc(sizeof(struct searchData));
        sDataArr[i]->searchPattern  = (char*)malloc(len*sizeof(char));
        sDataArr[i]->replacementPattern = (char*)malloc(len*sizeof(char));
        sscanf(line,"%s %s %f",sDataArr[i]->searchPattern, sDataArr[i]->replacementPattern, &scale);
        sDataArr[i]->scale=scale;
        printf("RP: %f\n",scale);
    }
    free(line);
    fclose(fp);
}

/*
 *
 * @param list	explain
 *
 * @return
 */
Node* string2list(char* list, float length, float scale)
{
    int size = strlen(list);
    //printf("%d\n",size);
    //curveList = (Node*) calloc(1, sizeof(Node));
    Node* currentNode = (Node*) calloc(1, sizeof(Node));
    Node* head = currentNode;
    int i;
    for( i = 0; i  < size ; i++)
    {
        if(list[i] == 'F')
        {
            currentNode->letter = 'F';
            currentNode->length = length*scale;
            currentNode->next = (Node*) calloc(1, sizeof(Node));
            currentNode->next->prev = currentNode;
            currentNode = currentNode->next;
        }
        else if(list[i] == 'f')
        {
            currentNode->letter = 'f';
            currentNode->length = length*scale;
            currentNode->next = (Node*) calloc(1, sizeof(Node));
            currentNode->next->prev = currentNode;
            currentNode = currentNode->next;
        }
        else if(list[i] == '+')
        {
            currentNode->letter = '+';
            currentNode->length = length*scale;
            currentNode->next = (Node*) calloc(1, sizeof(Node));
            currentNode->next->prev = currentNode;
            currentNode = currentNode->next;
        }
        else if(list[i] == '-')
        {
            currentNode->letter = '-';
            currentNode->length = length*scale;
            currentNode->next = (Node*) calloc(1, sizeof(Node));
            currentNode->next->prev = currentNode;
            currentNode = currentNode->next;
        }
    }
    currentNode = currentNode->prev;
    free(currentNode->next);
    currentNode->next = NULL;
    return head;
}

/*
 *
 *
 * @param rRules 	explain
 */
//void replacement(Node* list, Node* start, Node* end) // ***Original***
void* replacement(void* rRules)
{
    struct replacementRules* rules = (struct replacementRules*) rRules;
    Node* list = rules->replacementList;
    Node* start = rules->start;
    Node* end = rules->end;

    if(list->next != NULL && start->prev == NULL)
    {
        start->letter = list->letter;
        start->length = list->length;
        start->next = list->next;
        list->next->prev = start;
        while(list->next != NULL)
        {
            list = list->next;
        }
        list->next = end;
        if(end != NULL)
        {
            end->prev = list;
        }
    }
    else if (list->next == NULL)
    {
        start->letter = list->letter;
        start->length = list->length;
    }
    else
    {
        Node* temp = start->prev;
        if(temp != NULL)
        {
            temp->next = list;
        }
        list->prev = temp;
        while(list->next != NULL)
        {
            list = list->next;
        }
        if(end != NULL)
        {
            end->prev = list;
        }
        list->next = end;
    }

    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}


/*
 *
 *
 * @param	searchPattern	explain
 * @param replacementPattern	explain
 */
//Should numRules be an parameters for this function???
void* createSearchThreads(void* notUsed)
{
    pthread_t id[numRules]; //should this be an array of size numRules???
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);

    //should this be inside a loop
    for(;;)
    {
        for(int i = 0; i < numRules; i++)
        {
            pthread_create(&id[i], &attributes, search, sDataArr[i]);
            usleep(10000);
        }
        //is USLEEP suppose to be called here???
        //should this be inside a loop
        for(int i = 0; i < numRules; i++)
        {
            pthread_join(id[i], NULL);
        }
    }


}

/*
 *
 * @param	sData	explain
 */
//void search(char* searchPattern, char* replacementPattern) // ***Original ***
void* search(void* sData)
{
    pthread_mutex_lock(&lock);
    struct searchData* data = (struct searchData*) sData;
    char* searchPattern = data->searchPattern;
    char* replacementPattern = data->replacementPattern;
    float scale = data->scale;
    Node* head = curveList;
    Node* start;
    Node* end;
    //printf("data-> %s",data->searchPattern);
    int slen = strlen(searchPattern);
    char listPattern[slen];
    while(head != NULL)
    {
        start = head;
        end = start;
        for(int i = 0; i < slen && end != NULL; i++)
        {
            listPattern[i] = end->letter;
            end = end->next;
        }
        //compare this string and call replacement via createthreads.
        if(strcmp(listPattern, searchPattern) == 0)
        {
            //Call replacement via createthreads with start and end.
            //printf("%s\n", listPattern);
            //printf("Pattern Matches\n");
            struct replacementRules* replacementR = (struct replacementR*)malloc(sizeof(struct replacementRules));
            replacementR->replacementList = string2list(replacementPattern, start->length, scale);
            replacementR->start = start;
            replacementR->end = end;
            pthread_t id;
            pthread_attr_t attributes;
            pthread_attr_init(&attributes);

            pthread_create(&id, &attributes, replacement, replacementR);
            pthread_detach(id);

        }
        head=head->next;
    }
    pthread_exit(0);
}
//------------------------------------------------------------------------
//	You shouldn't have to change anything in the main function
//------------------------------------------------------------------------
int main(int argc, char** argv)
{
    initializeApplication(argv[1]);

    //	This takes care of initializing glut and the GUI.
    //	You shouldn’t have to touch this
    initializeFrontEnd(argc, argv);
    pthread_t id;
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);

    pthread_create(&id, &attributes, createSearchThreads, NULL);
    pthread_detach(id);

    // replacement(replacementList, start, end);



    // char** array = malloc(8 * sizeof(char*));
    // int index = 0;
    // char buff[1000];
    // FILE *fp;
    // fp = fopen(argv[1],"r");
    // while (fgets(buff, sizeof(buff), fp) != NULL)
    // {
    // 	buff[strlen(buff) - 1] = '\0';
    // 	//printf("%s\n",buff);
    // 	array[index] = buff;
    // 	printf("%s\n",buff);
    // 	index++;
    // }
    // fclose(fp);

    //	***MUST DO***

    //	Now would be the place & time to create a global mutex lock and threads
    //	if you don't need joinable threads.

    //	If you need joinable threads, then thread creation should happen here
#if USE_JOINABLE_THREADS
    pthread_t mainThread;
		int errCode = pthread_create (&mainThread, NULL, mainThreadFunc, NULL);
		if (errCode != 0)
		{
			printf ("could not pthread_create main thread. Error code %d: %s\n",
					 errCode, strerror(errCode));
			exit (13);
		}
#endif

    //	glut/gl magic.  Don't touch.
    //	Now we enter the main loop of the program and to a large extend
    //	"lose control" over its execution.  The callback functions that
    //	we set up earlier will be called when the corresponding event
    //	occurs
    glutMainLoop();

    //	This will never be executed (the exit point will be in one of the
    //	call back functions).
    return 0;
}