#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NRCHILD 500
#define NMAX 9999999
FILE *input,*output;
typedef struct arbore
{
    int castigat;
    char v[4][4];
    struct arbore *child[NRCHILD];
} arbore;
typedef struct arboreMinimax
{
    int val,nrfii;
    struct arboreMinimax *child[NRCHILD];
} arboreMinimax;
typedef struct node
{
    arboreMinimax *data;
    struct node *next;
} node;
typedef struct Queue
{
    struct node *head, *tail;
    int len;
} Queue;
int minimum (arboreMinimax **joc);
int maximum (arboreMinimax **joc);

void initQ(Queue **q)
{
    // initializarea cozii
    (*q)=malloc(sizeof(Queue));
    (*q)->head=NULL;
    (*q)->tail=NULL;
    (*q)->len=0;
}
int is_emptyQ(Queue *q)
{
    if(q->len==0)
        return 1;
    return 0;
}
int add_queue(Queue *q, arboreMinimax *val)
{
    // adaugare in coada
    node *p;
    p=(node*)malloc(sizeof(node));
    if(p==NULL)
        return 0;
    p->data=val;
    p->next=NULL;
    if(is_emptyQ(q))
    {
        q->head=p;
        q->tail=p;
        q->len++;
        return 1;
    }
    q->len++;
    q->tail->next=p;
    q->tail=p;
    return 1;
}
void pop_queue(Queue *q)
{
    // scoaterea din coada
    if(is_emptyQ(q))
        return;
    node *p;
    p=q->head;
    q->head=q->head->next;
    free(p);
    q->len--;
}
void init(arbore ** joc)
{
    // initializarea arborelui de joc
    int i,j;
    (*joc)=(arbore*)malloc(sizeof(arbore));
    for(i=0; i<=2; i++)
        for(j=0; j<=2; j++)
            (*joc)->v[i][j]='-';
    (*joc)->castigat=0;
    for(i=0; i<NRCHILD; i++)
        (*joc)->child[i]=NULL;
}
void initAMM(arboreMinimax **joc)
{
    // initializarea arborelui minimax (task 3)
    int i;
    (*joc)=(arboreMinimax*)malloc(sizeof(arboreMinimax));
    (*joc)->val=0;
    (*joc)->nrfii=0;
    for(i=0; i<NRCHILD; i++)
        (*joc)->child[i]=NULL;
}
void printMatrix(arbore *joc,int height)
{
    // afisare tabla de joc (task 1)
    int i,j,k;
    for(i=0; i<=2; i++)
    {
        for(k=1; k<=height; k++)
            fprintf(output,"\t");
        for(j=0; j<=1; j++)
            fprintf(output,"%c ",joc->v[i][j]);
        if(i==2)
            fprintf(output,"%c\n\n",joc->v[i][j]);
        else
            fprintf(output,"%c\n",joc->v[i][j]);
    }
}
int joc_terminat(arbore *joc)
{
    int i,j;
    for(i=0; i<=2; i++)
    {
        // 3 X sau 3 O pe aceeasi linie
        if(joc->v[i][0]==joc->v[i][1] && joc->v[i][1]==joc->v[i][2]
                && joc->v[i][0]!='-')
            return 1;
        // 3 X sau 3 O pe aceeasi coloana
        if(joc->v[0][i]==joc->v[1][i] && joc->v[1][i]==joc->v[2][i]
                && joc->v[0][i]!='-')
            return 1;
    }
    //diagonala principala
    if(joc->v[0][0]==joc->v[1][1] && joc->v[1][1]==joc->v[2][2]
            && joc->v[0][0]!='-')
        return 1;
    // diagonala secundara
    if(joc->v[0][2]==joc->v[1][1] && joc->v[1][1]==joc->v[2][0]
            && joc->v[0][2]!='-')
        return 1;
    return 0;
}
void exec_adancime(arbore *joc,int height,char dePus)
{
    // afisam tabla de joc nou-generata
    printMatrix(joc,height);
    int i,j,contor=0,k,l;
    arbore *nou;
    for(i=0; i<=2; i++)
        for(j=0; j<=2; j++)
            if(joc->v[i][j]=='-' && !joc_terminat(joc))
            {
                // creem noua tabla de joc
                init(&nou);
                for(k=0; k<=2; k++)
                    for(l=0; l<=2; l++)
                        nou->v[k][l]=joc->v[k][l];
                nou->v[i][j]=dePus;
                joc->child[contor]=nou;
                if(dePus=='O')
                    exec_adancime(joc->child[contor],height+1,'X');
                else
                    exec_adancime(joc->child[contor],height+1,'O');
                contor++;
            }
}
void freeMemory(arbore **joc)
{
    // eliberarea memoriei (task 1+2)
    int i;
    for(i=0; i<NRCHILD; i++)
        if((*joc)->child[i]!=NULL)
            freeMemory(&(*joc)->child[i]);
    free(*joc);
}
void freeMemoryAMM(arboreMinimax **joc)
{
    // eliberarea memoriei (task 3)
    int i;
    for(i=0; i<NRCHILD; i++)
        if((*joc)->child[i]!=NULL)
            freeMemoryAMM(&(*joc)->child[i]);
    free(*joc);
}
void c1()
{
    // rezolvare task 1
    int i,j;
    arbore *joc;
    init(&joc);
    char start,line[6],newline;
    start=fgetc(input);
    newline=fgetc(input);
    for(i=0; i<=2; i++)
    {
        fgets(line,6,input);
        newline=fgetc(input);
        for(j=0; j<=2; j++)
        {
            joc->v[i][j]=line[2*j];
        }
    }
    exec_adancime(joc,0,start);
    freeMemory(&joc);
}
int check_castigat(arbore *joc,char player)
{
    int i,j,ok=1;
    for(i=0; i<=2; i++)
    {
        // 3 X sau 3 O pe aceeasi linie
        if(joc->v[i][0]==joc->v[i][1] && joc->v[i][1]==joc->v[i][2]
                && joc->v[i][0]==player)
            return 1;
        // 3 X sau 3 O pe aceeasi coloana
        if(joc->v[0][i]==joc->v[1][i] && joc->v[1][i]==joc->v[2][i]
                && joc->v[0][i]==player)
            return 1;
    }
    // diagonala principala
    if(joc->v[0][0]==joc->v[1][1] && joc->v[1][1]==joc->v[2][2]
            && joc->v[0][0]==player)
        return 1;
    // diagonala secundara
    if(joc->v[0][2]==joc->v[1][1] && joc->v[1][1]==joc->v[2][0]
            && joc->v[0][2]==player)
        return 1;
    return 0;
}
void exec_adancime_modificat(arbore *joc,int height,char dePus,char start)
{
    int i,j,ct=0,k,l,ok=1;
    arbore *nou;
    // verificam daca jucatorul a castigat pe tabla de joc nou-generata
    if(check_castigat(joc,start))
    {
        joc->castigat=1;
        return;
    }
    for(i=0; i<=2; i++)
        for(j=0; j<=2; j++)
            if(joc->v[i][j]=='-' && !joc_terminat(joc))
            {
                // creem noua tabla de joc
                init(&nou);
                for(k=0; k<=2; k++)
                    for(l=0; l<=2; l++)
                        nou->v[k][l]=joc->v[k][l];
                nou->v[i][j]=dePus;
                joc->child[ct]=nou;
                if(dePus=='O')
                    exec_adancime_modificat(joc->child[ct],height+1,'X',start);
                else
                    exec_adancime_modificat(joc->child[ct],height+1,'O',start);
                ct++;
            }
    for(i=0; i<=2&&ok; i++)
        for(j=0; j<=2; j++)
            if(joc->v[i][j]=='-')
            {
                ok=0;
                break;
            }
    /* ok=1 => tabla de joc este plina (niciun jucator nu mai poate face nicio
    mutare => remiza */
    if(ok)
        return;
    if(dePus==start)
    {
        // se face operatia 'sau' intre valorile copiilor nodului curent
        for(i=0; i<ct; i++)
            if(joc->child[i]->castigat)
            {
                joc->castigat=1;
                return;
            }
    }
    else
    {
        // se face operatia 'si' intre valorile copiilor nodului curent
        for(i=0; i<ct; i++)
            if(!joc->child[i]->castigat)
                break;
        if(i==ct)
            joc->castigat=1;
        else
            joc->castigat=0;
    }
}
void print_si_sau(arbore *joc,int height)
{
    // afisarea arborelui si_sau (task 2)
    int i;
    for(i=1; i<=height; i++)
        fprintf(output,"\t");
    if(joc->castigat==1)
    {
        fprintf(output,"T\n");
    }
    else
        fprintf(output,"F\n");
    for(i=0; i<NRCHILD; i++)
        if(joc->child[i]!=NULL)
            print_si_sau(joc->child[i],height+1);
}
void c2()
{
    // rezolvarea cerintei 2
    int i,j;
    arbore *joc;
    init(&joc);
    char start,line[6],newline;
    start=fgetc(input);
    newline=fgetc(input);
    for(i=0; i<=2; i++)
    {
        fgets(line,6,input);
        newline=fgetc(input);
        for(j=0; j<=2; j++)
        {
            joc->v[i][j]=line[2*j];
        }
    }
    exec_adancime_modificat(joc,0,start,start);
    print_si_sau(joc,0);
    freeMemory(&joc);
}
void print_graph(arboreMinimax *joc,int height)
{
    // afisarea arborelui minimax (task 3)
    int i;
    for(i=0; i<height; i++)
        fprintf(output,"\t");
    fprintf(output,"%d\n",joc->val);
    for(i=0; i<joc->nrfii; i++)
        print_graph(joc->child[i],height+1);
}
void c3()
{
    /* c=parantezele citite, q=coada de arbori
    contor1=numarul de perechi de "(x) " citite pe fiecare rand
    contor2=suma numarului de noduri citite pe fiecare rand
    i,j,k iteratori */
    Queue *q;
    char c,newline;
    int i,n,value,contor2=0,contor=1,j,k;
    arboreMinimax *joc,*nou;
    initAMM(&joc);
    joc->nrfii=1;
    initQ(&q);
    nou=joc;
    fscanf(input,"%d",&n);
    newline=fgetc(input);
    add_queue(q,nou);
    for(i=1; i<=n; i++)
    {
        contor2=0;
        for(j=1; j<=contor; j++)
        {
            nou=q->head->data;
            c=fgetc(input);
            fscanf(input,"%d",&value);
            c=fgetc(input);
            if(c==']')
            {
                nou->val=value;
            }
            else
            {
                for(k=0; k<value; k++)
                {
                    initAMM(&nou->child[k]);
                    add_queue(q,nou->child[k]);
                }
                nou->val=NMAX;
                nou->nrfii=value;
                contor2+=value;
            }
            pop_queue(q);
            c=fgetc(input);
        }
        contor=contor2;
    }
    free(q);
    joc->val=maximum(&joc);
    print_graph(joc,0);
    freeMemoryAMM(&joc);
}
int main(int argc, char *argv[])
{
    input=fopen(argv[2],"r");
    output=fopen(argv[3],"w");
    if(!strcmp(argv[1],"-c1"))
        c1();
    if(!strcmp(argv[1],"-c2"))
        c2();
    if(!strcmp(argv[1],"-c3"))
        c3();
    fclose(input);
    fclose(output);
    return 0;
}
int minimum (arboreMinimax **joc)
{
    int vmin=NMAX,i;
    // cazul banal: arboreleMinimax este o frunza
    if((*joc)->nrfii==0)
        return (*joc)->val;
    else
    {
        for(i=0; i<(*joc)->nrfii; i++)
        {
            /* daca valoarea unui copil este NMAX atunci inseamna ca nu i
            s-a calculat valoarea reala. */
            if((*joc)->child[i]->val==NMAX)
                (*joc)->child[i]->val=maximum(&(*joc)->child[i]);
            if((*joc)->child[i]->val<vmin)
                vmin=(*joc)->child[i]->val;
        }


    }
    return vmin;
}
int maximum(arboreMinimax **joc)
{
    int vmax=-NMAX,i;
    if((*joc)->nrfii==0)
        return (*joc)->val;
    else
    {
        for(i=0; i<(*joc)->nrfii; i++)
        {
            /* daca valoarea unui copil este NMAX atunci inseamna ca nu i
            s-a calculat valoarea reala. */
            if((*joc)->child[i]->val==NMAX)
                (*joc)->child[i]->val=minimum(&(*joc)->child[i]);
            if((*joc)->child[i]->val>vmax)
                vmax=(*joc)->child[i]->val;
        }
    }
    return vmax;
}
