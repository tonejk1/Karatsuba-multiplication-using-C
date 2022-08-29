#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int length (char *);

char *multiply (char *, char *);

char *add (char *, char *, int);

char *sub (char *, char *, int);

char *addzerosl (char *, int, int);

void reallocaddzerosl (char **, int, int);

char *addzerosr (char *, int);

char *karamult (char *, char *);

void removezero (char *);


int
main ()
{

    char a[] =
        "3141592653589793238462643383279502884197169399375105820974944592";

    char b[] =
        "2718281828459045235360287471352662497757247093699959574966967627";


    char *c = karamult (a, b);


    int d = length (c);

    printf ("%s  %d", c, d);

    FILE * F = NULL;

    F = fopen ("test_1.txt", "w");

    fprintf (F, "%s", c);

    fclose (F);

    free (F);

    free (c);

    return 0;

}



// Length of array
int
length (char *c)
{

    int l = 0;

    while ((*c++) != '\0')

        l++;


    return l;

}



// multiply two integers

char *
multiply (char *a, char *b)

{

    char *f = (char *) calloc ((3), sizeof (char));

    if (f == NULL)

    {

        printf ("error in multiply\n");

        exit (EXIT_FAILURE);


    }


    int e = (*a - '0') * (*b - '0');

    f[0] = (e / 10) + '0';

    f[1] = (e % 10) + '0';

    f[2] = '\0';


    removezero (f);


    return f;

}



// add two integers

char *
add (char *a, char *b, int n)
{

    char *f = NULL;

    f = (char *) calloc ((n + 2), sizeof (char));

    if (f == NULL)

    {

        printf ("error in add\n");

        exit (EXIT_FAILURE);


    }


    int car = 0;

    for (int i = n; i > 0; i--)

    {

        int e1 = (a[i - 1] - '0') + (b[i - 1] - '0') + car;

        if (e1 - 10 >= 0)

            car = 1;

        else

            car = 0;

        f[i] = (e1 % 10) + '0';


    }


    if (car)

    {

        f[0] = '1';

        f[n + 1] = '\0';

    }

    else


    {

        f[0] = '0';

        f[n + 1] = '\0';

        char *g = (char *) calloc ((n + 1), sizeof (char));

        for (int i = 0; i < n + 1; i++)

            g[i] = f[i + 1];

        free (f);

        f = NULL;

        return g;

    }


    return f;


}



// sub two integers

char *
sub (char *a, char *b, int n)
{

    char *f = (char *) calloc ((n + 1), sizeof (char));

    if (f == NULL)

    {

        printf ("error in sub\n");

        exit (EXIT_FAILURE);


    }


    int car = 0;

    for (int i = n - 1; i >= 0; i--)

    {

        int e1 = (a[i] - '0') - (b[i] - '0') - car;

        if (e1 < 0)

        {

            car = 1;

            e1 += 10;

            f[i] = e1 + '0';

        }

        else

        {

            f[i] = e1 + '0';

            car = 0;

        }

    }


    f[n] = '\0';

    return f;

}



// add zeros to left

char *
addzerosl (char *a, int a1, int b)

{

    int r = b - a1;

    char *f = (char *) calloc ((b + 1), sizeof (char));

    if (f == NULL)

    {

        printf ("error in addzerosl\n");

        exit (EXIT_FAILURE);


    }


    for (int i = 0; i < a1; i++)

    {

        f[b - 1 - i] = a[a1 - 1 - i];

    }

    for (int i = 0; i < r; i++)

    {

        f[i] = '0';

    }

    f[b] = '\0';

    return f;

}



void
reallocaddzerosl (char **a, int a1, int b)

{

    int r = b - a1;

    *a = (char *) realloc ((*a), (b + 1) * sizeof (char));

    if (*a == NULL)

    {

        printf ("error in reallocaddzerosl\n");

        exit (EXIT_FAILURE);


    }


    for (int i = 0; i < a1; i++)

    {

        (*a)[b - 1 - i] = (*a)[a1 - 1 - i];

    }

    for (int i = 0; i < r; i++)

    {

        (*a)[i] = '0';

    }

    (*a)[b] = '\0';

}


// remove zeros from left

void
removezero (char *a)
{

    int n = length (a);

    int i = 0;


    if (a[0] != '0')

        return;

    else

    {

        while (a[i] == '0' && a[i] != '\0')

            i++;

        int j = 0;

        if (i < n)

        {

            for (j = 0; j < (n - i); j++)

            {

                a[j] = a[i + j];

            }


            a[j] = '\0';

        }

        else

        {

            a[0] = '0';

            a[1] = '\0';

        }

    }

}



// add zeros to right

char *
addzerosr (char *a, int c)
{

    char *f = (char *) calloc ((length (a) + c + 1), sizeof (char));

    if (a == NULL)

    {

        printf ("error in addzerosr\n");

        exit (EXIT_FAILURE);


    }


    for (int i = 0; i < length (a); i++)

        f[i] = a[i];

    for (int i = length (a); i < (length (a) + c); i++)

    {

        f[i] = '0';

    }

    f[(length (a) + c)] = '\0';


    return f;

}



// Karatsuba multiplication

char *
karamult (char *a, char *b)
{

    static int de = 0;

    int la = length (a);

    int lb = length (b);

    char *ca = NULL;

    char *cb = NULL;


    int n = 0;

    char *f = NULL;


    if (la <= 1 && lb <= 1)

    {

        f = multiply (a, b);

        return f;

    }


    if (la > lb)

    {

        n = la;

        cb = addzerosl (b, lb, la);

        ca = addzerosl (a, la, la);

    }

    else if (la < lb)

    {

        n = lb;

        ca = addzerosl (a, la, lb);

        cb = addzerosl (b, lb, lb);

    }

    else

    {

        ca = addzerosl (a, la, la);

        cb = addzerosl (b, lb, lb);

        n = lb;

    }


    if (n % 2)

    {

        reallocaddzerosl (&ca, n, n + 1);

        reallocaddzerosl (&cb, n, n + 1);

        n = n + 1;

    }


    char *a1 = (char *) calloc ((n / 2 + 1), sizeof (char));

    char *b1 = (char *) calloc ((n / 2 + 1), sizeof (char));

    char *c1 = (char *) calloc ((n / 2 + 1), sizeof (char));

    char *d1 = (char *) calloc ((n / 2 + 1), sizeof (char));

    if (a1 == NULL || b1 == NULL || c1 == NULL || d1 == NULL)

    {

        printf ("error in a1\n");

        exit (EXIT_FAILURE);


    }


    for (int i = 0; i < n / 2; i++)

    {

        a1[i] = ca[i];

        b1[i] = ca[i + n / 2];

        c1[i] = cb[i];

        d1[i] = cb[i + n / 2];

    }

    a1[n / 2] = '\0';

    b1[n / 2] = '\0';

    c1[n / 2] = '\0';

    d1[n / 2] = '\0';

    free (ca);

    free (cb);

    ca = NULL;

    cb = NULL;


    char *apb = add (a1, b1, length (a1));

    if (apb == NULL)

    {

        printf ("error in apb\n");

        exit (EXIT_FAILURE);


    }


    char *cpb = add (c1, d1, length (c1));

    if (cpb == NULL)

    {

        printf ("error in cpb\n");

        exit (EXIT_FAILURE);


    }


    char *ac = karamult (a1, c1);

    if (ac == NULL)

    {

        printf ("error in ac\n");

        exit (EXIT_FAILURE);


    }


    char *bd = karamult (b1, d1);

    if (bd == NULL)

    {

        printf ("error in bd\n");

        exit (EXIT_FAILURE);


    }


    removezero (ac);

    removezero (bd);

    removezero (apb);

    removezero (cpb);


    free (a1);

    free (b1);

    free (c1);

    free (d1);

    a1 = NULL;

    b1 = NULL;

    c1 = NULL;

    d1 = NULL;

    char *sec = karamult (apb, cpb);

    if (sec == NULL)

    {

        printf ("error in sec\n");

        exit (EXIT_FAILURE);


    }


    removezero (sec);

    free (apb);

    free (cpb);

    apb = NULL;

    cpb = NULL;

    int lsec = length (sec);

    int lac = length (ac);

    if (lsec > lac)

        reallocaddzerosl (&ac, lac, lsec);

    else if (lsec < lac)

        reallocaddzerosl (&sec, lsec, lac);

    lsec = length (sec);

    char *sec1 = sub (sec, ac, lsec);

    if (sec1 == NULL)

    {

        printf ("error in sec1\n");

        exit (EXIT_FAILURE);


    }


    removezero (sec1);

    free (sec);

    sec = NULL;

    int lsec1 = length (sec1);

    int lbd = length (bd);

    if (lsec1 > lbd)

        reallocaddzerosl (&bd, lbd, lsec1);

    else if (lsec1 < lbd)

        reallocaddzerosl (&sec1, lsec1, lbd);

    lsec1 = length (sec1);

    char *sec2 = sub (sec1, bd, lsec1);

    if (sec2 == NULL)

    {

        printf ("error in sec2\n");

        exit (EXIT_FAILURE);


    }


    removezero (sec2);

    free (sec1);


    sec1 = NULL;

    int i = 0;

    int j = 0;


    char *f1 = addzerosr (ac, n);

    if (f1 == NULL)

    {

        printf ("error in f1\n");

        exit (EXIT_FAILURE);


    }


    free (ac);

    ac = NULL;

    removezero (f1);

    char *f2 = addzerosr (sec2, (n / 2));

    if (f2 == NULL)

    {

        printf ("error in f2\n");

        exit (EXIT_FAILURE);


    }


    free (sec2);


    sec2 = NULL;

    removezero (f2);

    int lf1 = length (f1);

    int lf2 = length (f2);

    if (lf1 > lf2)

        reallocaddzerosl (&f2, lf2, lf1);

    else if (lf1 < lf2)

        reallocaddzerosl (&f1, lf1, lf2);

    lf1 = length (f1);

    char *f3 = add (f1, f2, lf1);

    if (f3 == NULL)

    {

        printf ("error in f3\n");

        exit (EXIT_FAILURE);


    }


    free (f1);

    free (f2);


    f1 = NULL;

    f2 = NULL;

    int lf3 = length (f3);

    removezero (f3);

    removezero (bd);

    lbd = length (bd);

    if (lf3 > lbd)

        reallocaddzerosl (&bd, lbd, lf3);

    else if (lf3 < lbd)

        reallocaddzerosl (&f3, lf3, lbd);

    lf3 = length (f3);

    f = add (f3, bd, lf3);

    if (f == NULL)

    {

        printf ("error in f\n");

        exit (EXIT_FAILURE);


    }


    removezero (f);

    free (f3);


    if (bd == NULL)

    {

        printf ("error in bd\n");

        exit (EXIT_FAILURE);


    }


    free (bd);


    f3 = NULL;

    bd = NULL;


    return f;

}
