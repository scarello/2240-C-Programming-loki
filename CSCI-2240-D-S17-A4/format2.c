#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LMAX 20

int main (int argc, char **argv) {

    if (argc < 3 ) {
        fprintf (stderr, "error: insufficient input, usage: %s <resize> <filename>\n",
                argv[0]);
        return 1;
    }
    int nchr;
    char **inputArray, **tmp;        /* array of pointers to char        */
    char *ln;                   /* NULL forces getline to allocate  */
    size_t n;                   /* buf size, 0 use getline default  */
    size_t idx;                 /* array index for number of lines  */
    size_t it;                  /* general iterator variable        */
    size_t lmax;                /* current array pointer allocation */
    FILE *fp;                   /* file pointer                     */
    int resizeNum;              /* line resize value                */

    inputArray = NULL;
    ln = NULL;
    n = 0;
    nchr = 0;
    idx = 0;
    it = 0;
    lmax = LMAX;
    fp = NULL;
    tmp = NULL;

    if (!(fp = fopen (argv[2], "r"))) { /* open file for reading    */
        fprintf (stderr, "error: file open failed '%s'.", argv[2]);
        return 1;
    }

    resizeNum = atoi(argv[1]);
    if (resizeNum < 25 || resizeNum > 100){
        fprintf(stderr, "error: resize value is not in the proper range of 25 <= x <= 100 '%d'", resizeNum);
    }

    /* allocate LMAX pointers and set to NULL. Each of the 255 pointers will
       point to (hold the address of) the beginning of each string read from
       the file below. This will allow access to each string with array[x].
       */
    if (!(inputArray = calloc (LMAX, sizeof *inputArray))) {
        fprintf (stderr, "error: memory allocation failed.");
        return 1;
    }

    /* prototype - ssize_t getline (char **ln, size_t *n, FILE *fp)
       above we declared: char *ln and size_t n. Why don't they match? Simple,
       we will be passing the address of each to getline, so we simply precede
       the variable with the urinary '&' which forces an addition level of
       dereference making char* char** and size_t size_t *. Now the arguments
       match the prototype.
       */
    while ((nchr = getline(&ln, &n, fp)) != -1)    /* read line    */
    {
        while (nchr > 0 && (ln[nchr-1] == '\n' || ln[nchr-1] == '\r'))
            ln[--nchr] = 0;     /* strip newline or carriage rtn    */

        /* allocate & copy ln to array - this will create a block of memory
           to hold each character in ln and copy the characters in ln to that
           memory address. The address will then be stored in array[idx].
           (idx++ just increases idx by 1 so it is ready for the next address)
           There is a lot going on in that simple: array[idx++] = strdup (ln);
           */
        inputArray[idx++] = strdup (ln);

        if (idx == lmax) {      /* if lmax lines reached, realloc   */
            tmp = realloc (inputArray, lmax * 2 * sizeof *inputArray);
            if (!tmp)
                return -1;
            inputArray = tmp;
            lmax *= 2;
        }
    }

    if (fp) fclose (fp);        /* close file */
    if (ln) free (ln);          /* free memory allocated to ln  */

    /*
       process/use lines in array as needed
       (simple print all lines example below)
       */

    printf ("\nLines in file:\n\n");    /* print lines in file  */
    for (it = 0; it < idx; it++)
        printf ("  array [%3zu]  %s\n", it, inputArray[it]);
    printf ("\n");

    for (it = 0; it < idx; it++)        /* free array memory    */
        free (inputArray[it]);
    free (inputArray);

    return 0;
}
