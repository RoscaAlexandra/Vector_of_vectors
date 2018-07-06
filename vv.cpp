#include <iostream>

using namespace std;
class vector { int dim;
               int *v;
            public:
               vector(int) ;
               vector(int,int);
               ~vector();
               vector(vector &);
               int get_dim();
               int get_el(int);
               void set_el(int ,int);
               friend istream & operator >>(istream&, vector &);
               friend ostream & operator <<(ostream&, vector &);
               };
istream & operator>>(istream &in, vector &p)
{   cout<<"introduceti dimensiunea vectorului:\n";
    in>>p.dim;
    p.v=new int[p.dim];
    cout<<"introduceti elementele vectorului:\n";
    for(int i=0;i<p.dim;i++)
        in>>p.v[i];

    return in;
}
ostream & operator<<(ostream &out, vector &p)
{
    for(int i=0;i<p.dim;i++)
       out<<p.v[i]<<" ";

    cout<<"\n";
    return out;
}
vector::vector(int n=0) //initializare
{
    dim=n;
    v=new int[dim];
}
vector::vector(int n,int x) //initializare cu un nr x
{
    dim=n;
    v=new int[dim];
    for(int i=0;i<dim;i++)
        v[i]=x;
}
vector::~vector() //destructor

{
    delete []v;
}
vector :: vector(vector &p) //constructor de copiere
{
    dim=p.dim;
    v=new int[dim];
    for(int i=0;i<dim;i++)
        v[i]=p.v[i];
}

int vector :: get_dim()
{
    return dim;
}
int vector :: get_el(int i)
{
    return v[i];
}
void vector :: set_el(int i,int x)
{
    v[i]=x;
}
class vector_de_vectori {int dim;
                         vector *v;
                      public:
                         vector_de_vectori(int);
                         vector_de_vectori(int,const vector&);
                         vector get_vect(int);
                         int get_el(int, int);
                         int get_dim();
                         void set_el(int,int,int);
                         ~vector_de_vectori();
                         vector_de_vectori(const vector_de_vectori &);
                         int ** matrice();
                         int ** operator +(vector_de_vectori &);
                         friend istream & operator >>(istream &, vector_de_vectori &);
                         friend ostream & operator <<(ostream&, const vector_de_vectori &);};
vector_de_vectori :: vector_de_vectori(int n=0)
{
    dim=n;
    v=new vector[dim];
}
vector vector_de_vectori :: get_vect(int i)
{
    return v[i];
}
int vector_de_vectori :: get_el(int i,int j)
{
    return v[i].get_el(j);
}
void vector_de_vectori :: set_el(int i,int j, int x)
{
    v[i].set_el(j,x);
}
int vector_de_vectori :: get_dim()
{
    return dim;
}
vector_de_vectori::vector_de_vectori(int n,const vector &x)
{
    dim=n;
    v=new vector[dim];
    for(int i=0;i<dim;i++)
        v[i]=x;

}
vector_de_vectori :: ~vector_de_vectori()
{
    delete[] v;
}
vector_de_vectori :: vector_de_vectori(const vector_de_vectori &v1)
{
    dim=v1.dim;
    v=new vector[dim];
    for(int i=0;i<dim;i++)
       v[i]=v1.v[i];
}
int ** vector_de_vectori :: matrice()
{
    int i,j,max=0,x;
    for(i=0;i<dim;i++)
    { x=v[i].get_dim();
        if(x>max)
           max=x;}


    int  **A;
    A=new int*[dim];
    for(i=0;i<dim;i++)
        A[i]=new int[max];

    for(i=0;i<dim;i++)
        for(j=0;j<max;j++)
          A[i][j]=0; //initializarea matricii cu 0

    for(i=0;i<dim;i++)
        for(j=0;j<v[i].get_dim();j++)
          A[i][j]=A[i][j]+v[i].get_el(j); //adunam elementele existente



    return A;
}
int ** vector_de_vectori :: operator+(vector_de_vectori &v2)
{
  int **C,i,j,dim1=this->dim,dim2=v2.get_dim(), dimm=dim, max1=0,max2=0,max;
  if(dimm<dim2)
    dimm=dim2; //nr linii al sumei

  for(i=0;i<dim1;i++)
    if(v[i].get_dim()>max1)
        max1=v[i].get_dim();
  int x;
  for(i=0;i<dim2;i++)
  {
    x=((v2.get_vect(i)).get_dim());
    if(x > max2)
        max2=x;
  }
  max=max1;
  if(max<max2)
     max=max2; //nr de col al sumei

  C=new int *[dimm];
  for(i=0;i<dimm;i++)
     C[i]=new int[max]; //alocarea matricii suma

  for(i=0;i<dimm;i++)
     for(j=0;j<max;j++)
        C[i][j]=0; //matricea suma initializata cu 0

  int **A, **B;
  A=this->matrice();
  B=v2.matrice(); //matricile corespunzatoare ficarui vector de vectori

cout<<"matricea primului termen:\n";
 for(i=0;i<dim1;i++)
   {for(j=0;j<max1;j++)
        cout<<A[i][j]<<" ";
    cout<<"\n";}
cout<<"matricea celui de-al doilea termen:\n";
for(i=0;i<dim2;i++)
   {for(j=0;j<max2;j++)
        cout<<B[i][j]<<" ";
    cout<<"\n";}
for(i=0;i<dim1;i++)
    for(j=0;j<max1;j++)
       C[i][j]=C[i][j]+A[i][j];

for(i=0;i<dim2;i++)
    for(j=0;j<max2;j++)
       C[i][j]=C[i][j]+B[i][j];

cout<<"suma:\n";
for(i=0;i<dimm;i++)
    {for(j=0;j<max;j++)
        cout<<C[i][j]<<" ";
     cout<<"\n";}
return C;

}
istream& operator>> (istream &in ,vector_de_vectori &P)
{
    cout<<"introduceti nr de vectori";
    in>>P.dim;
    P.v=new vector[P.dim];
    for(int i=0;i<P.dim;i++)
        in>>P.v[i];
    return in;

}
ostream & operator<< (ostream &out ,const vector_de_vectori &p)
{
    for(int i=0;i<p.dim;i++)
        out<<p.v[i]<<" ";
    out<<"\n";
    return out;
}
void principal(int n)
{
    vector_de_vectori V[n];
    for(int i=0;i<n;i++)
        cin>>V[i];
    for(int i=0;i<n;i++)
        cout<<V[i];


}
int main()
{ //lista vectori de vectori
  /*int n;
  cout<<"introduceti numarul de obiecte:";
  cin>>n;
  principal(n);*/
  vector_de_vectori M1,M2;
  cin>>M1; cin>>M2;
  int **C=M1+M2;


    return 0;
}
