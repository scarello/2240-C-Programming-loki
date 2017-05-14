/*
Name     : Michael Monical
Class    : 2240-850
Program #    : 5 Database
Due Date     : April 28, 2017

Honor Pledge:  On my honor as a student of the University
of Nebraska at Omaha, I have neither given nor received
unauthorized help on this homework assignment.

NAME: Michael Monical
NUID: 9263
EMAIL: mikemonical@gmail.com

Partners:None

This assignment is a simple database server.

*/







#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT_NUM 20140


/*
Method Name     :strncmp
Parameters      :const char str1 & str2 size_t n
Return Value(s) :int
Partners        :None
Description     :This compares 2 strings. This is only the proto type just to prevent
pedantic/ansi to stop giving warnings.

*/

int strncmp(const char *str1, const char *str2, size_t n);


/*
Method Name     :snprintf
Parameters      :char *, size_t const char*
Return Value(s) :int
Partners        :None
Description     :This if for formatted output to sized buffer. 
This is only the proto type just to prevent pedantic/ansi to stop giving warnings.

*/

int snprintf(char *, size_t, const char*, ...);

/*
Method Name     :student
Parameters      :char * size_t const char * ...
Return Value(s) :typedef struct
Partners        :None
Description     :This is the struct for each student.
*/

typedef struct student {
    char lname[10], initial, fname[10];
    unsigned long SID;
    float GPA;
}SREC;
/*
Method Name     :node
Parameters      :struct
Return Value(s) :typedef
Partners        :None
Description     :This is a student node.
*/

typedef struct node {
    struct student SREC;
    struct node *left, *right;
}node;

struct node *GPAroot, *SIDroot, *Lnameroot, *Fnameroot, *deleteNode;
char* message;
size_t messageSize, sizeRemaining;

/*
Method Name     :newNode
Parameters      :char* lname, fname, char initial, unsigned long SID, float GPA
Return Value(s) :struct temp
Partners        :None
Description     :This is a temporary struct node
*/

struct node *newNode(char* lname, char* fname, char initial, unsigned long SID, float GPA){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    strncpy(temp->SREC.lname, lname, 9);
    strncpy(temp->SREC.fname, fname, 9);
    temp->SREC.initial = initial;
    temp->SREC.SID = SID;
    temp->SREC.GPA = GPA;
    temp->left = temp->right = NULL;
    return temp;
}

/*
Method Name     :LnameInsert
Parameters      :node* node, char* lname, fname, initial, unsigned long SID, float GPA
Return Value(s) :struct node
Partners        :None
Description     :This inserts the name into the binary tree
*/

struct node* LnameInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if((strncmp(lname, node->SREC.lname, 9) < 0))
        node->left = LnameInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = LnameInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}
/*
Method Name     :FnameInsert
Parameters      :struct node* node, char* lname fname, char initial, unsigned long SID, float GPA
Return Value(s) :node:struct
Partners        :None
Description     :This inserts the name into the binary
*/

struct node* FnameInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if((strncmp(fname, node->SREC.fname, 9) < 0))
        node->left = FnameInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = FnameInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}
/*
Method Name     :SIDInsert
Parameters      :node* node, char* lname, fname, initial, unsigned long SID, float GPA
Return Value(s) :struct node
Partners        :None
Description     :This inserts the name into the binary tree
*/

struct node* SIDInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if(SID < node->SREC.SID)
        node->left = SIDInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = SIDInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}
/*
Method Name     :GPAInsert
Parameters      :node* node, char* lname, fname, initial, unsigned long SID, float GPA
Return Value(s) :struct node
Partners        :None
Description     :This inserts the name into the binary tree
*/

struct node* GPAInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if(GPA < node->SREC.GPA)
        node->left = GPAInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = GPAInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}

/*
Method Name     :lNameInOrder
Parameters      :struct node *root
Return Value(s) :none
Partners        :None
Description     :This places things in order by last name.
*/

void lNameInOrder(struct node *root){
    char *temp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        lNameInOrder(root->left);
        snprintf(temp, 48, "| %05lu | %-9s | %-9s | %c | %.2f |\n", root->SREC.SID, root->SREC.lname,
                root->SREC.fname, root->SREC.initial, root->SREC.GPA);
        if(sizeRemaining < 48){
            message =  realloc(message, messageSize * 2 * sizeof *message);
            t = (int) (messageSize - sizeRemaining);
            messageSize *= 2;
            sizeRemaining = (size_t) (messageSize - t);

        }
        strcat(message, temp);
        sizeRemaining -= 48;
        lNameInOrder(root->right);
    }
}
/*
Method Name     :fNameInOrder
Parameters      :struct node *root
Return Value(s) :none
Partners        :None
Description     :This places things in order by first name.
*/

void fNameInOrder(struct node *root){
    char *temp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        fNameInOrder(root->left);
        snprintf(temp, 48, "| %05lu | %-9s | %-9s | %c | %.2f |\n", root->SREC.SID, root->SREC.lname,
                root->SREC.fname, root->SREC.initial, root->SREC.GPA);
        if(sizeRemaining < 48){
            message =  realloc(message, messageSize * 2 * sizeof *message);
            t = (int) (messageSize - sizeRemaining);
            messageSize *= 2;
            sizeRemaining = (messageSize - t);

        }
        strcat(message, temp);
        sizeRemaining -= 48;
        fNameInOrder(root->right);
    }
}
/*
Method Name     :SIDInOrder
Parameters      :struct node *root
Return Value(s) :none
Partners        :None
Description     :This places things in order by SID.
*/

void SIDInOrder(struct node *root){
    char *temp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        SIDInOrder(root->left);
        snprintf(temp, 48, "| %05lu | %-9s | %-9s | %c | %.2f |\n", root->SREC.SID, root->SREC.lname,
                root->SREC.fname, root->SREC.initial, root->SREC.GPA);
        if(sizeRemaining < 48){
            message =  realloc(message, messageSize * 2 * sizeof *message);
            t = (int) (messageSize - sizeRemaining);
            messageSize *= 2;
            sizeRemaining =  (messageSize - t);

        }
        strcat(message, temp);
        sizeRemaining -= 48;
        SIDInOrder(root->right);
    }
}
/*
Method Name     :GPAInOrder
Parameters      :struct node *root
Return Value(s) :none
Partners        :None
Description     :This places things in order by GPA.
*/

void GPAInOrder(struct node *root){
    char *temp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        GPAInOrder(root->right);
        snprintf(temp, 48, "| %05lu | %-9s | %-9s | %c | %.2f |\n", root->SREC.SID, root->SREC.lname,
                root->SREC.fname, root->SREC.initial, root->SREC.GPA);
        if(sizeRemaining < 48){
            message =  realloc(message, messageSize * 2 * sizeof *message);
            t = (int) (messageSize - sizeRemaining);
            messageSize *= 2;
            sizeRemaining =  (messageSize - t);

        }
        strcat(message, temp);
        sizeRemaining -= 48;
        GPAInOrder(root->left);
    }
}
/*
Method Name     :getLname
Parameters      :none
Return Value(s) :none
Partners        :None
Description     :This structures the proper printout.
*/

void getLname(){
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = (size_t) (messageSize - 141);
    lNameInOrder(Lnameroot);
    strcat(message, "+-------+-----------+-----------+---+------+");
}
/*
Method Name     :getFname
Parameters      :none
Return Value(s) :none
Partners        :None
Description     :This structures the proper printout.
*/

void getFname(){
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = (size_t) (messageSize - 141);
    fNameInOrder(Fnameroot);
    strcat(message, "+-------+-----------+-----------+---+------+");
}
/*
Method Name     :getSID  
Parameters      :none
Return Value(s) :none
Partners        :None
Description     :This structures the proper printout.
*/

void getSID(){
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = (size_t) (messageSize - 141);
    SIDInOrder(SIDroot);
    strcat(message, "+-------+-----------+-----------+---+------+");
}
/*
Method Name     :getGPA  
Parameters      :none
Return Value(s) :none
Partners        :None
Description     :This structures the proper printout.
*/

void getGPA(){
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = (size_t) (messageSize - 141);
    GPAInOrder(GPAroot);
    strcat(message, "+-------+-----------+-----------+---+------+");
}
/*
Method Name     :put  
Parameters      :char* fName & lName, char mi, int sid, double gpa
Return Value(s) :int
Partners        :None
Description     :This takes and places each student in the proper spot and correct order.
*/

int put(char* lName, char* fName, char mi, int sid, double gpa){
    printf("lName: %s, fName: %s, mi: %c, sid: %d, gpa: %f\n", lName, fName, mi, sid, gpa);
    Lnameroot = LnameInsert(Lnameroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    Fnameroot = FnameInsert(Fnameroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    SIDroot = SIDInsert(SIDroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    GPAroot = GPAInsert(GPAroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    return 1;
}
/*
Method Name     :minValueNode
Parameters      :struct node* node
Return Value(s) :struct current
Partners        :None
Description     :Given a non-empty binary search tree, return the node with minimum
key value found in that tree. Note that the entire tree does not need to be searched. 
*/
struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}
/*
Method Name     :deleteSID
Parameters      :struct node* root, unsigned long sid
Return Value(s) :struct root
Partners        :None
Description     :This handles the removal of nodes in the binary tree
*/

struct node* deleteSID(struct node* root, unsigned long sid)
{
    struct node* temp;
    
    /* base case */
    if (root == NULL) return root;

    /* If the key to be deleted is smaller than the root's key,
    then it lies in left subtree*/
    if ( sid < root->SREC.SID)
        root->left = deleteSID(root->left, sid);

    /* If the key to be deleted is greater than the root's key,
     then it lies in right subtree*/
    else if (sid > root->SREC.SID)
        root->right = deleteSID(root->right, sid);

    /* if key is same as root's key, then This is the node
     to be deleted*/
    else
    {
        /* node with only one child or no child*/
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        /* node with two children: Get the inorder successor (smallest
         in the right subtree)*/
        temp = minValueNode(root->right);

        /* Copy the inorder successor's content to this node*/
        root->SREC.SID = temp->SREC.SID;
        root->SREC.GPA = temp->SREC.GPA;
        strcpy(root->SREC.lname, temp->SREC.lname);
        root->SREC.initial = temp->SREC.initial;
        strcpy(root->SREC.fname, temp->SREC.fname);

        /* Delete the inorder successor*/
        root->right = deleteSID(root->right, temp->SREC.SID);
    }
    return root;
}
/*
Method Name     :deleteLname
Parameters      :struct node* root, char* lname
Return Value(s) :struct root
Partners        :None
Description     :This handles the removal of nodes in the binary tree
*/


struct node* deleteLname(struct node* root, char* lname)
{
    struct node *temp;
    /* base case*/
    if (root == NULL) return root;

    /* If the key to be deleted is smaller than the root's key,
     then it lies in left subtree*/
    if ( (strncmp(lname, root->SREC.lname, 9) < 0))
        root->left = deleteLname(root->left, lname);

    /* If the key to be deleted is greater than the root's key,
     then it lies in right subtree*/
    else if ((strncmp(lname, root->SREC.lname, 9) > 0))
        root->right = deleteLname(root->right, lname);

    /* if key is same as root's key, then This is the node
     to be deleted*/
    else
    {
        /* node with only one child or no child*/
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        /* node with two children: Get the inorder successor (smallest
         in the right subtree)*/
        temp = minValueNode(root->right);

        /* Copy the inorder successor's content to this node*/
        root->SREC.SID = temp->SREC.SID;
        root->SREC.GPA = temp->SREC.GPA;
        root->SREC.initial = temp->SREC.initial;
        strcpy(root->SREC.lname, temp->SREC.lname);
        strcpy(root->SREC.fname, temp->SREC.fname);

        /* Delete the inorder successor*/
        root->right = deleteLname(root->right, temp->SREC.lname);
    }
    return root;
}
/*
Method Name     :deleteFname
Parameters      :struct node* root, char* fname
Return Value(s) :struct root
Partners        :None
Description     :This handles the removal of nodes in the binary tree
*/

struct node* deleteFname(struct node* root, char* fname)
{
    struct node *temp;
    /* base case*/
    if (root == NULL) return root;

    /* If the key to be deleted is smaller than the root's key,
     then it lies in left subtree*/
    if ( (strncmp(fname, root->SREC.fname, 9) < 0))
        root->left = deleteFname(root->left, fname);

    /* If the key to be deleted is greater than the root's key,
     then it lies in right subtree*/
    else if ((strncmp(fname, root->SREC.fname, 9) > 0))
        root->right = deleteFname(root->right, fname);

    /* if key is same as root's key, then This is the node
     to be deleted*/
    else
    {
        /* node with only one child or no child*/
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        /* node with two children: Get the inorder successor (smallest
         in the right subtree)*/
        temp = minValueNode(root->right);

        /* Copy the inorder successor's content to this node*/
        root->SREC.SID = temp->SREC.SID;
        root->SREC.GPA = temp->SREC.GPA;
        root->SREC.initial = temp->SREC.initial;
        strcpy(root->SREC.lname, temp->SREC.lname);
        strcpy(root->SREC.fname, temp->SREC.fname);

        /* Delete the inorder successor*/
        root->right = deleteFname(root->right, temp->SREC.fname);
    }
    return root;
}
/*
Method Name     :deleteGPA
Parameters      :struct node* root, float GPA
Return Value(s) :struct root
Partners        :None
Description     :This handles the removal of nodes in the binary tree
*/

struct node* deleteGPA(struct node* root, float GPA)
{
    struct node *temp;
    /* base case*/
    if (root == NULL) return root;

    /* If the key to be deleted is smaller than the root's key,
     then it lies in left subtree*/
    if ( GPA < root->SREC.GPA)
        root->left = deleteGPA(root->left, GPA);

    /* If the key to be deleted is greater than the root's key,
     then it lies in right subtree*/
    else if (GPA > root->SREC.GPA)
        root->right = deleteGPA(root->right, GPA);

    /* if key is same as root's key, then This is the node
     to be deleted*/
    else
    {
        /* node with only one child or no child*/
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        /* node with two children: Get the inorder successor (smallest
         in the right subtree)*/
        temp = minValueNode(root->right);

        /* Copy the inorder successor's content to this node*/
        root->SREC.SID = temp->SREC.SID;
        root->SREC.GPA = temp->SREC.GPA;
        root->SREC.initial = temp->SREC.initial;
        strcpy(root->SREC.lname, temp->SREC.lname);
        strcpy(root->SREC.fname, temp->SREC.fname);

        /* Delete the inorder successor*/
        root->right = deleteGPA(root->right, temp->SREC.GPA);
    }
    return root;
}
/*
Method Name     :findDeleteNode
Parameters      :struct node* root, unsigned long sid
Return Value(s) :struct root
Partners        :None
Description     :This handles the removal of nodes in the binary tree
*/

struct node* findDeleteNode(struct node* root, unsigned long sid){
    struct node* temp;
    if (root == NULL)
        return NULL;
    if (sid < root->SREC.SID)
        temp = findDeleteNode(root->left, sid);
    else if (sid > root->SREC.SID)
        temp = findDeleteNode(root->right, sid);
    else
        return root;
    return temp;
}

/*
Method Name     :delete
Parameters      :unsigned long sid
Return Value(s) :int
Partners        :None
Description     :This handles the memory behind deletion of a node
*/

int delete(unsigned long sid){
    unsigned long deleteSid;
    char* lname, *fname;
    float gpa;

    lname = calloc(10, sizeof(char));
    fname = calloc(10, sizeof(char));
    deleteNode = findDeleteNode(SIDroot, sid);
    if (deleteNode == NULL)
        return 0;
    deleteSid = deleteNode->SREC.SID;
    strcpy(lname, deleteNode->SREC.lname);
    strcpy(fname, deleteNode->SREC.fname);
    gpa = deleteNode->SREC.GPA;
    SIDroot = deleteSID(SIDroot, deleteSid);
    Lnameroot = deleteLname(Lnameroot, lname);
    Fnameroot = deleteFname(Fnameroot, fname);
    GPAroot = deleteGPA(GPAroot, gpa);
    return 1;
}
/*
Method Name     :error
Parameters      :char *msg
Return Value(s) :none
Partners        :None
Description     :This handles an error message
*/

void error(char *msg)
{
    perror(msg);
    exit(1);
}
/*
Method Name     :preOrderTraversal
Parameters      :struct node* root, file *fp
Return Value(s) :none
Partners        :None
Description     :This reads through both the struct node and file load
*/

void preOrderTraversal(struct node* root,FILE *fp){

    if (root != NULL){
        fprintf(fp, "%lu,%s,%s,%c,%f\n", root->SREC.SID, root->SREC.lname,
                root->SREC.fname, root->SREC.initial, root->SREC.GPA);
        preOrderTraversal(root->left, fp);
        preOrderTraversal(root->right, fp);
    }
}
/*
Method Name     :saveFile
Parameters      :NONE
Return Value(s) :NONE
Partners        :NONE
Description     :This saves to a file and creates one if one doesn't already exist
*/

void saveFile(){
    FILE *fp;

    fp = fopen("database.bin", "w");
    preOrderTraversal(SIDroot,fp);
    fclose(fp);
    return;
}
/*
Method Name     :loadFile
Parameters      :None
Return Value(s) :none
Partners        :None
Description     :This loads the the existing file if it does exist
*/

void loadFile(){
    FILE *fp;
    char* temp;
    temp = calloc(48, sizeof(char));
    fp = fopen("database.bin", "r");
    if (fp == NULL){
        return;
    }


    while(fgets(temp, 48, fp) != NULL) {
        int sid = atoi(strtok(temp, ","));
        char *lName = strtok(NULL, ",");
        char *fName = strtok(NULL, ",");
        char *mi = strtok(NULL, ",");
        double gpa = atof(strtok(NULL, ","));
        put(lName, fName, mi[0], sid, gpa);
    }

    fclose(fp);
    return;


}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    GPAroot = SIDroot = Lnameroot = Fnameroot = NULL;
    loadFile();
    messageSize = 256;
    message = calloc(messageSize, sizeof(char));

    /*STEP 1********************************************
      int socket(int domain, int type, int protocol);*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /*Make sure opening was successful*/
    if (sockfd < 0)
        error("ERROR opening socket");


    /*STEP 2********************************************
      0 out the server address*/
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    /*convert argument to int*/
    portno = PORT_NUM;
    /*this is always the same for this type of connection*/
    serv_addr.sin_family = AF_INET;
    /*INADDR_ANY is a macro that will find the current machine IP*/
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    /*make sure byte order is correct
      may be a no-op, but better safe than sorry*/
    serv_addr.sin_port = htons((uint16_t) portno);


    /*STEP 3********************************************/
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0)
        error("ERROR on binding");


    /*STEP 4********************************************
      Open server up for listening, if you don't listen
      you won't hear*/
    listen(sockfd,5);


    /*STEP 5******************************************/
    clilen = sizeof(cli_addr);
    /*Accept blocks until a connection with
      a client is made. Returns a new socket
      to communicate with the new connection.
      Also receives address data about client*/
    newsockfd = accept(sockfd,
            (struct sockaddr *) &cli_addr,
            &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    memset(buffer, 0, 256);

    /*Communicate************************************/
    n = (int) read(newsockfd, buffer, 255);
    while ((strcmp(buffer, "stop\n") != 0)) {
        size_t t;
        char* argument;

        message = calloc(messageSize, sizeof(char));
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s", buffer);
        if (strncmp(buffer, "get", 3) == 0){
            strtok(buffer, " ");
            argument = strtok(NULL, " ");
            if (strcmp(argument, "lname\n") == 0)
                getLname();
            else if (strcmp(argument, "fname\n") == 0)
                getFname();
            else if (strcmp(argument, "SID\n") == 0)
                getSID();
            else if (strcmp(argument, "GPA\n") == 0)
                getGPA();
            else
                message = "Not a valid argument";
        } else if (strncmp(buffer, "put", 3) == 0){
            char* lName;
            char* fName;  
            char* mi; 
            int sid;
            double gpa;
            strtok(buffer, " ");
            lName = strtok(NULL, ",");
            fName = strtok(NULL, ",");
            mi = strtok(NULL, ",");
            sid =  atoi(strtok(NULL, ","));
            gpa =  atof(strtok(NULL, ","));
            if(put(lName, fName, mi[0], sid, gpa))
                message = "Put Successful";
            else
                message = "Put failed";
        }
        else if (strncmp(buffer, "delete", 6) == 0){
            unsigned long sid;
            strtok(buffer, " ");
            sid = (unsigned long) atoi(strtok(NULL, " "));
            if(delete(sid))
                message = "delete successful";
            else
                message = "delete unsuccessful";
        } else
            message = "Not a valid command";
        t = sizeof(char) * strlen(message);
        memset(buffer, 0, 256);
        sprintf(buffer, "%d", (int) t);
        write(newsockfd, buffer, strlen(buffer));
        n = (int) write(newsockfd, message, t);
        memset(buffer, 0, 256);
        /*   memset(message, 0, messageSize);*/
        if (n < 0) error("ERROR writing to socket");
        n = (int) read(newsockfd, buffer, 255);
        /* free(message);*/
    }
    write(newsockfd,"stop",strlen("stop"));
    saveFile();
    return 0;
}
