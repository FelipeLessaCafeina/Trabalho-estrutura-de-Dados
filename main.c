#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct disc{
    int cod;
    char * nome;
    float nf;
    struct disc * prox;
    
}Disciplina;

typedef struct no{
    int matricula;
    int cadeiras;
    int qdisc;
    char *aluno;
    char *email;
    Disciplina *disc;
    struct no *esq;
    struct no *dir;
}NO;

NO* raiz=NULL;

//Funções iterativas que fazem o trabalho
NO * adicionar(NO*aux,NO*novo);
NO * delete(NO* aux,int matricula);
NO * search(int matricula, NO*aux);

//Funcoes de utilidade geral as outras funcoes para evitar repeticao
int check ();
int check_aux(NO*aux);
NO * copiar_data (NO* aux,NO * aux2);
NO * sucessorinor (NO* aux2);

//Funções de atendimento ao cliente
void cadastrar();
void remover(int matricula);
void alterar(int matricula);
void buscar(int matricula);


int main(){    
    int matricula;
    printf("Bem vindo ao Sistema de Gerenciamento de Alunos!\n");

    for(int a = 0; a != 5;){

        printf("O que deseja fazer?\n[1] Cadastrar um novo aluno \n[2] Excluir um aluno \n[3] Alterar os dados pessoais de um aluno \n[4] Buscar os dados de um Aluno \n[5] Sair\n");
        scanf("%d", &a);

       
        if(a == 1){

            cadastrar();           
        }
       
       
        if(a == 2)
        {
            if(check())//A funcao check() retorna 1 se a raiz nao for NULL, e printa uma mensagem caso seja
            {
                printf("Informe a matricula a ser removida: \n");
                scanf("%d", &matricula);
                remover(matricula);
            }
                 
        }


        if(a == 3)
        {
            if(check())
            {
                printf("Informe a matricula a ter os dados alterados:\n");
                scanf("%d", &matricula);
                alterar(matricula);
            }

            
        }
        
    
        if(a == 4)
        {
            if(check())
            {
                 printf("Informe a matricula a ser buscada:\n");
                 scanf("%d", &matricula);
                 buscar(matricula);
            }          
                
        }
    
    
        if(a == 5)
        {
            printf("Obrigado por usar o Sistema de Gerenciamento de alunos!\n");
        }
    }
    return 0;
}



void cadastrar()
{    
    NO * Novo=malloc(sizeof(NO));
    printf("Informe a matricula do aluno:\n");
    scanf("%d", &Novo->matricula);
    if( (search(Novo->matricula,raiz)))
    {
        printf("Essa matricula ja esta em uso.\n\n");
    }
    else
    {
        printf("Informe o nome do aluno:\n");
        Novo->aluno = malloc(sizeof(char)*100);
        scanf("%s", Novo->aluno);
        
        printf("Informe o e-mail do aluno:\n");
        Novo->email = malloc(sizeof(char)*100);
        scanf("%s", Novo->email);

        printf("Informe quantas disciplinas o aluno esta cursando:\n");
        scanf("%d", &Novo->qdisc);

        Disciplina * New=malloc(sizeof(Disciplina));
        Novo->disc = New;
        Novo->dir=NULL;
        Novo->esq=NULL;

            for( int y = 0; y < Novo->qdisc; y++)
            {/*utiliza a quantidade de disciplinas como limite para o loop que armazena disciplinas e adiciona
            na lista encadeada*/

                printf("Disciplina %d\nInforme o nome da disciplina:\n", (y + 1));
                New->nome = malloc(sizeof(char)*50);
                scanf("%s",New->nome);

                printf("Informe o codigo da disciplina:\n");
                scanf("%d", &New->cod);

                printf("Informa a nota final do aluno:\n");
                scanf("%f", &New->nf);  
                if (Novo->qdisc-y > 1)//se estiver no ultimo loop, o proximo membro da lista nao e criado
                {New=New->prox=malloc(sizeof(Disciplina));}
                else {New->prox=NULL;}
                
            }
        if (raiz==NULL)
        {
            raiz=Novo;//Necessario para evitar erros com remocao e primeira adicao
        }
        else
        {
            adicionar(raiz,Novo);
            printf("\nCadastro realizado com sucesso!\n\n");
        }


    }
        
}

void remover(int matricula)
{
    if(check())
    {//ha distincao entre check() e check_aux() pois ha mensagens diferentes
        
        if(check_aux(search(matricula,raiz)))
        {     
            if((raiz->dir==NULL) && (raiz->esq==NULL)) 
          {//se raiz for o ultimo membro, simplesmente recebe NULL
            raiz=NULL;
            printf("\nRemocao realizada com sucesso!\n\n");
          }       
           else {
             delete(raiz,matricula);
             printf("\nRemocao realizada com sucesso!\n\n");
           }
        }
    }
}

void alterar(int matricula)
{
    NO* aux = search(matricula,raiz);
    if(check_aux(aux))

    {
        int res;
        printf("Aluno %s de endereco de email %s \n\nQual dado deseja alterar? \n[1] Nome \n[2] Email \n[3] Cancelar alteracao\n\n",aux->aluno,aux->email);
        scanf("%d",&res);
        if (res == 1)
        {
            printf("Digite o nome:\n");
            scanf("%s",aux->aluno);
            printf("Nome alterado com sucesso!");
        }
        if (res==2)
        {
            printf("Digite o endereço de email:\n");
            scanf("%s",aux->email);
            printf("E-mail alterado com sucesso!");
        }
        if (res >=3)
        {
            printf("Alteracao cancelada, nenhum dado mudado.");
        }

    }
    

}

void buscar(int matricula)
{    
    NO * aux = search(matricula,raiz);
    if (check_aux(aux))//check_aux envia a mensagem automaticamente se estiver nulo
    {
        printf("Aluno: %s\nMatricula: %d\nEmail: %s\n\n", aux->aluno, aux->matricula, aux->email);
        Disciplina * dis =aux->disc;
        printf("Disciplinas cursadas:\n\n");
        for(int discurs=0;discurs<aux->qdisc;discurs++)
        {
            printf("%s de codigo %d\nNota final do aluno: %.2f\n\n",dis->nome,dis->cod,dis->nf);
            dis=dis->prox;
        }     

    }
}


NO * adicionar(NO*aux,NO*novo)
{
   
     if (aux == NULL)
     {
        
        aux=novo;
     }
     else if (novo->matricula < aux->matricula)
     {
        aux->esq = adicionar(aux->esq,novo);
     }
     else if(novo->matricula> aux->matricula)
     {
        aux->dir = adicionar(aux->dir,novo);
     }
     return aux;

       
    }

NO * delete(NO* aux,int matricula)
{
    if(aux==NULL)
    {        
        return aux;
    }
    if (matricula < aux->matricula)
    {
        aux->esq=delete(aux->esq, matricula);
    }
    else if (matricula > aux->matricula)
    {
        aux->dir=delete(aux->dir,matricula);
    }
    else
    {
        if(aux->esq==NULL)
        {
            return aux->dir;
        }
        else if (aux->dir==NULL)
        {
            return aux->esq;
        }
        
        aux=copiar_data(aux,sucessorinor(aux->dir));
        aux->dir=delete(aux->dir,matricula);
        
        
    }
    return aux;

}

NO * search(int matricula, NO*aux)
{    
        if (aux == NULL){
            
            return NULL;
        }    


        if (aux->matricula == matricula)
            return aux;

        if (matricula < aux->matricula)
            return search(matricula,aux->esq);

        else if (matricula > aux->matricula)
            return search(matricula,aux->dir);


        return NULL;
}



int check ()
{//Verificar se ha ao menos uma matricula cadastrada no sistema para evitar coletas de dados desnecessarias
    if (raiz==NULL)
    {
        printf("Nao ha alunos cadastrados no sistema!\n\n");//e junto ja vem a mensagem avisando
        return 0;
    }
    else{
        return 1;//retorna 1 (true) para os if 
    }
}

int check_aux(NO*aux)
{//Pode parecer desnecessario, mas o aviso de matricula nao cadastrada aparece em 3 das 4 funções essenciais
    if(aux==NULL)
    {//Usado em conjunto com search() para responder rapidamente os If e evitar coleta desnecessaria de dados
        printf("Essa matricula nao esta cadastrada no sistema!\n\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

NO* copiar_data (NO* aux,NO * aux2)
{/*vi necessario uma funcao para copiar os dados, exceto direita e esquerda, de uma struct para outra
durante a implementacao da funcao delete inspirada no site linkado no relatorio*/
        aux->aluno=aux2->aluno;
        aux->cadeiras = aux2->cadeiras ;
        aux->disc = aux2->disc ;
        aux->email = aux2->email ;
        aux->matricula = aux2->matricula ;
        aux->qdisc = aux2->qdisc ;
        return aux;
}

NO* sucessorinor (NO* aux2)
{//sucessor in orden, tambem para a funcao delete funcionar corretamente.
    NO * aux = copiar_data(aux,aux2);        
        
        while (aux2->esq != NULL)
        {
            aux=copiar_data(aux,aux2->esq);
            aux2=aux2->esq;
        }
        return aux;
} 

