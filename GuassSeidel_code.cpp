#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<new>

#define SQ(x) (x)*(x)
#define RESP(x) 1.0/(x)
#define free_arg char*
#define nr_end 1
#define TINY 1.0e-20

using namespace std;
typedef unsigned long int us;

double *dvector (long nl, long nh);
long *lvector (long nl, long nh);
double **matrix (long nrl, long nrh, long ncl, long nch);
long **lmatrix (long nrl, long nrh, long ncl, long nch);
double ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_vector (double *v, long nl, long nh);
void free_lvector (long *v, long nl, long nh);
void free_matrix (double **m, long nrl, long nrh, long ncl, long nch);
void free_lmatrix (long **m, long nrl, long nrh, long ncl, long nch);
void free_tensor(double ***t,long nrl, long nrh, long ncl, long nch, long ndl, long ndh);



int main()
{
long i,j,n,m;
double **a,*x,*b;
cout<<"Number of iterations: "<<endl;
cin>>m;
cout<<endl;
ifstream fin("matrix.txt",ios::in);

fin>>n;
a = matrix(1,n,1,n+1);
x = dvector(1,n);


for(i=1;i<=n;++i){
for(j=1;j<=n+1;++j){
fin>>a[i][j];
if (j==n+1)
{
        b[i] = a[i][j];
}
}
}
fin.close();
for(i=1;i<=n;++i){
for(j=1;j<=n+1;++j){
        cout<<a[i][j]<<" ";
}


cout<<endl;}

cout<<endl;


for(j=1;j<=n;++j){
cout<<b[j]<<endl;
}

cout<<endl;

for (i = 1; i <= n; i++)
{
       x[i] = 0;
}

while(m>0){
for ( i = 1; i <= n; i++)
{
        x[i] = b[i]/a[i][i];
        for ( j = 1; j <= n+1; j++)
        {
                if (i!=j)
                {
                        x[i] = x[i] - (a[i][j]*x[j])/a[i][i];
                }
        }
        
}
m--;
}
for (i = 1; i <= n; i++)
{
        cout<<"x"<<i<<" = "<<x[i]<<endl;
}


return(0);
}



double *dvector (long nl, long nh)
// Allocates a double vector with subscript range v[nl..nh]
         {
                 double *v = new double [nh-nl+1+nr_end];
                         if (!v)
                               {
                               cout<< "allocation failure in vector";
                               exit(1);
                               }
                                                                                                  return v-nl+nr_end;
                                                                                         }
long *lvector (long nl, long nh)
// allocates a long vector with subscript range v[nl..nh]
        {
        long *v = new long [nh-nl+1+nr_end];
        if(!v)
                {
                cout<< "allocation failure in lvector";
                exit(1);
                }
        return v-nl+nr_end;
        }
double **matrix (long nrl, long nrh, long ncl, long nch)
// allocate a double matrix with subscript range m[nrl..nrh][ncl..nch]
        {
        long i, nrow=nrh-nrl+1, ncol=nch-ncl+1;

//allocates pointer to row

        double  **m = new double *[nrow+nr_end];//nr_end=1
        if(!m)
                {
                cout<< "allocation failure 1 in matrix";
                exit(1);
                }
        m+=nr_end;
        m-=nrl;
// allocates rows and set pointers to them
        m[nrl] = new double [nrow*ncol+nr_end];
        if(!m[nrl])
                {
                cout<< "allocation failure 2 in matrix()";
                exit(1);
                }
 m[nrl]+=nr_end;
         m[ncl]-=ncl;
         for(i=nrl+1;i<=nrh;++i)
                m[i]=m[i-1]+ncol;
//return pointer to array of pointers to rows
         return m;
         }

long **lmatrix (long nrl, long nrh, long ncl, long nch)
// allocate a long matrix with subscript range m[nrl..nrh][ncl..nch]
        {
        long i, nrow=nrh-nrl+1, ncol=nch-ncl+1;

//allocates pointer to row

        long  **m = new long *[nrow+nr_end];
        if(!m)
                {
                cout<< "allocation failure 1 in lmatrix";
                exit(1);
                }
        m+=nr_end;
        m-=nrl;
// allocates rows and set pointers to them
        m[nrl] = new long [nrow*ncol+nr_end];
        if(!m[nrl])
                {
                cout<< "allocation failure 2 in lmatrix()";
                exit(1);
                }
         m[nrl]+=nr_end;
         m[ncl]-=ncl;
         for(i=nrl+1;i<=nrh;++i)
                m[i]=m[i-1]+ncol;
//return pointer to array of pointers to rows
         return m;
         }


//  To create the three dimensional arrays using pointers.
 double ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh)
     {
         long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1, ndep=ndh-ndl+1;
    /*allocate pointer to pointers to row*/
     double ***t = new double **[nrow+nr_end];
      if (!t)
     { cout<<"allocation failure 1 in 3tensor";
       exit(1);
     }
        t +=nr_end;
        t -=nrl;
    /*allocate pointer to rows and set pointers to them*/
      t[nrl]=new double *[nrow*ncol+nr_end];
       if (!t[nrl])
      { cout<<"allocation failure 2 in 3tensor";
         exit(1);
      }
      t[nrl] += nr_end;
      t[nrl] -= ncl;
     /*allocate rows and set pointers to them*/
      t[nrl][ncl] = new double [nrow*ncol*ndep+nr_end];
if (!t[nrl][ncl])
{ cout<<"allocation failure 3 in 3 tensor";
        exit(1);
      }
     t[nrl][ncl] += nr_end;
     t[nrl][ncl] -= ndl;
      for(j=ncl+1;j<=nch;++j)
         t[nrl][j]=t[nrl][j-1]+ndep;
      for(i=nrl+1;i<=nrh;++i)
       {
         t[i]=t[i-1]+ncol;
         t[i][ncl]=t[i-1][ncl]+ncol*ndep;
       for(j=ncl+1;j<=nch;++j)
        t[i][j]=t[i][j-1]+ndep;
       }
     return t;
    }

void free_vector (double *v, long nl, long nh)
// free a double vector allocated with dvector()
{
delete ((free_arg)(v+nl-nr_end));
}

void free_lvector (long *v, long nl, long nh)
// free a long vector allocated with lvector()
{
delete ((free_arg)(v+nl-nr_end));
}


void free_matrix (double **m, long nrl, long nrh, long ncl, long nch)
// free a double matrix allocated by matrix().

{    delete ((free_arg) (m[nrl]+ncl-nr_end));
     delete ((free_arg) (m+nrl-nr_end));
}
void free_lmatrix (long **m, long nrl, long nrh, long ncl, long nch)
// free a long matrix allocated by matrix().

{    delete ((free_arg) (m[nrl]+ncl-nr_end));
     delete ((free_arg) (m+nrl-nr_end));
}
void free_tensor(double ***t,long nrl, long nrh, long ncl, long nch, long ndl, long ndh)
{
delete ((free_arg)(t[nrl][ncl]+ndl-nr_end));
delete ((free_arg)(t[nrl]+ncl-nr_end));
delete ((free_arg)(t+nrl-nr_end));
}



