#include "line_search_user.h"
#include "line_search.h"
#include <math.h>

double myvalue
(
    double   *x,
    INT       n
) ;

void mygrad
(
    double    *g,
    double    *x,
    INT        n
) ;

double myvalgrad
(
    double    *g,
    double    *x,
    INT        n
) ;

double InnerProduct(double *v,double *u,INT n)
{
	double ip = 0.0;
	for (INT i = 0 ; i < n ; i++)
		ip += v[i] * u[i];
	return ip;
}

int main (void)
{
    double *x,*d,*g ;
    double fx0,fx;
	double gnorm2;
	INT i, n, iter ;
	cg_stats_struct cg_stat;
	
    /* allocate space for solution */
    n = 100;
    x = (double *) malloc (n*sizeof (double)) ;
	d = (double *) malloc (n*sizeof (double)) ;
	g = (double *) malloc (n*sizeof (double)) ;
    cg_stat.g = (double *) malloc (n*sizeof (double));

	iter = 0;
	/* set starting guess */
    for (i = 0; i < n; i++) x [i] = 1. ;
	fx=fx0 = myvalue(x,n);
	mygrad(g,x,n);
	for (i = 0; i < n; i++) 
	{
		d[i]  = -g[i];
	}
	do{
		iter ++;
	printf("d'g = %f\n",InnerProduct(g,d,n));


	/* run the code */
	line_search (x, n, d, cg_stat, NULL,myvalue, mygrad, myvalgrad) ;
	
	printf("line search:\n      nf = %d,\n      ng=%d\n      alpha=%f\n",cg_stat.nfunc,cg_stat.ngrad,cg_stat.alpha);

	for(i=0;i<n;i++)
		g[i] = cg_stat.g[i];

	/*printf("x=[");
	for (i = 0; i < n; i++) printf("%f ",x [i]) ; 
	printf("]\n");*/

	/*compute the new objective function's value */
    fx0=fx;
	fx = cg_stat.f;

	printf("iter = %-5d, fxold = %10.6e, fx= %10.6e, fxold-fx=%10.6e\n",iter,fx0,fx,fx0-fx);

	for (i = 0; i < n; i++) 
	{
		d[i]  = -g[i];
	}
	gnorm2 = InnerProduct(g,g,n);
	printf("gnorm2 = %10.6e \n",gnorm2);
	}while (gnorm2 > 0.00000001);
	

	

    free (x) ;
	free (d) ;
	free (g) ;
	free (cg_stat.g);
	/*MY:Save screen to view date*/
	printf("\nPlease press Enter to exit");
	getchar();
}

double myvalue
(
    double   *x,
    INT       n
)
{
    double f, t ;
    INT i ;
    f = 0. ;
    for (i = 0; i < n; i++)
    {
        t = i+1 ;
        t = sqrt (t) ;
        f += exp (x [i]) - t*x [i] ;
    }
    return (f) ;
}

void mygrad
(
    double    *g,
    double    *x,
    INT        n
)
{
    double t ;
    INT i ;
    for (i = 0; i < n; i++)
    {
        t = i + 1 ;
        t = sqrt (t) ;
        g [i] = exp (x [i]) -  t ;
    }
    return ;
}

double myvalgrad
(
    double    *g,
    double    *x,
    INT        n
)
{
    double ex, f, t ;
    INT i ;
    f = (double) 0 ;
    for (i = 0; i < n; i++)
    {
        t = i + 1 ;
        t = sqrt (t) ;
        ex = exp (x [i]) ;
        f += ex - t*x [i] ;
        g [i] = ex -  t ;
    }
    return (f) ;
}