#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // para usar o bool

typedef struct _livro{
    char titulo[100];
    unsigned int num_paginas;
    float preco;
}Livro;


typedef struct _aluno{
    char nome[100];
    int idade;
    Livro *livro_fav;
}Aluno;


//construtor para o livro
//quando se passa um char podemos passar um ponteiro como esta sendo feito, ou titulo[]
Livro *create_Livro(const char *titulo, unsigned int num_paginas, float preco){
  Livro *livro = (Livro*) calloc(1, sizeof(Livro));
  
  strcpy(livro ->titulo, titulo);
  livro ->num_paginas = num_paginas;
  livro ->preco = preco;
  
  return livro;
}

//desalocador do livro
//** porque precisa do endereco de memoria do pra onde o aluno aponta o comeco do livro
void destroy_livro(Livro **livro_ref){
    
    Livro *livro = *livro_ref;
    free(livro);
    *livro_ref = NULL; //dessa forma voce esvazia o espaco da memoria e associa ele a nulo
    //free(*livro_ref); - opcao mais facil, menos detalhista 
}

//essa função pega o livro e retorna uma copia desse livro e seus dados, ele vai na criação, cria um novo bloco e passa os exatos msms parametros do livro original
Livro *copy_livro(const Livro *livro){
    
    return create_Livro(livro ->titulo, livro -> num_paginas, livro -> preco);
}

//exibidor
void print_livro(const Livro *livro){
    printf("Titulo: %s\n", livro ->titulo);
    printf("Numero de paginas: %d\n", livro -> num_paginas);
    printf("Preco: RS%.2f\n\n", livro -> preco);
}


Aluno *create_aluno(const char *nome, unsigned int idade, const Livro *livro_fav){
    
    Aluno *aluno = (Aluno *) calloc(1, sizeof(Aluno));
    
    strcpy(aluno -> nome, nome);
    aluno -> idade = idade;
    aluno -> livro_fav = copy_livro(livro_fav); //aqui criamos uma copia do livro exclusivamente para um aluno 
    
    return aluno;
}

void destroy_aluno(Aluno **aluno_ref){
    
    Aluno *aluno = *aluno_ref; //pegando o conteudo de aluno_ref, pro bloco de memoria onde os dados do aluno estao armazenados
    
    destroy_livro(&aluno -> livro_fav); // destroindo o bloco de memoria da copia do livro do aluno e seta o ponteiro para NULL
    free(aluno);//apaga o bloco de memoria dos dados do Aluno
    
    *aluno_ref = NULL; //pega o ponteiro que esta na stack apontando para aluno e faz ele apontar para nulo 
    
}

void print_aluno(const Aluno *aluno){
    printf("Nome: %s\n", aluno -> nome);
    printf("Idade: %d\n", aluno -> idade);
    puts("Livro favorito : ");
    puts("--------------"); // apenas formatacao
    print_livro(aluno -> livro_fav); // chamando a funcao para exibir todos os dados do livro
}

//comparando se os titulos sao iguais 
bool equals_titulos(const Livro *original, const Livro *copia){
    if(strcmp(original -> titulo, copia -> titulo) == 0 ){
        return true;
    }else{
        return false;
    }
}


int main(){
    
    //criando livro
    Livro *livro1 = create_Livro("Harry Potter 1", 400, 219.90);
    
    //exibindo
    print_livro(livro1);
    
    //modificando
    livro1 -> preco = 199.90;
    
    //exibindo
    print_livro(livro1);
    
    
    
    //criando aluno 
    Aluno *aluno1 = create_aluno("Giovanna", 20, livro1);
    
    //exibindo aluno
    print_aluno(aluno1);
    
    //comparando referencias de ponteiro
    //pergunta se o livro favorito e exatamente ao mesmo que o livro origianl na memoria, como se os dois tivessem a mesma copia fisica 
    //a saida sera false, pois o livro_fav aponta para um endereco onde se armazena a copia do livro, enquanto livro1 aponta para o original
    puts("aluno1 -> livro_fav == livro1\n");
    if(aluno1 -> livro_fav == livro1){
        puts("true");
        puts("-------");
    }else{
        puts("false");
        puts("-------");
    }
    
    //conferindo se os titulos batem
    puts("\nequals_titulos\n");
    if(equals_titulos(aluno1 -> livro_fav, livro1)){
        puts("TRUE");
        puts("-------");
    }else{
        puts("FALSE");
        puts("-------");
    }
    
    
    //destroindo livro
    destroy_livro(&livro1);
    
    
    //exibindo novamente o aluno sem livro
    print_aluno(aluno1);
    
    
    //destroindo o aluno
    destroy_aluno(&aluno1);
    
    //condicional para garantir que a função de destruicao funcionou corretamente
    printf("livro1 == NULL? %d\n", livro1 == NULL);
    //retorna 1 pra true e 0 para false 
    
    return 0;
}
