#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titulo[100];
    char nomeArtista[100];
    int duracaoSegundos;

} Musica;

typedef struct No{
    Musica musica;
    struct No *proximo;

} No;

//Funcao que retorna NULL para inicializar nossa playlist.
No *inicializar(){
    return NULL;
}

//Funcao que le e retorna todos os parametros da nova musica que vai ser inserida.
Musica lerNovaMusica(){
    Musica musica;
    printf("\nDigite o titulo da musica que quer adicionar: ");
    fgets(musica.titulo, sizeof(musica.titulo), stdin);
    musica.titulo[strcspn(musica.titulo, "\n")] = '\0';
    printf("\nDigite o nome do artista dessa musica: ");
    fgets(musica.nomeArtista, sizeof(musica.nomeArtista), stdin);
    musica.nomeArtista[strcspn(musica.nomeArtista, "\n")] = '\0';
    printf("\nDigite a duracao em seguntos dessa musica: ");
    scanf(" %d", &musica.duracaoSegundos);
    return musica;
}

int main(){
    int op;

    //Atribuimos NULL para definir o inicio da nossa playlist vazia.
    No *playlist = inicializar();

    do{
        printf("\nEscolha uma opcao:");
        printf("\n1 - Adicionar musica ao inicio.");
        printf("\n2 - Adicionar musica ao final.");
        printf("\n3 - Inserir musica antes de...");
        printf("\n4 - Remover musica.");
        printf("\n0 - Sair.");
        scanf(" %d", &op);

        switch(op){
            case 1:
                adicionarInicio(playlist);
                break;
            case 2:
                adicionarFinal(playlist);
                break;
            case 3:
                inserirAntesDe(playlist);
                break;
            case 4:
                remover(playlist);
                break;
            case 5:
                free(playlist);
                return 0;
                
        }
    }while(op!=0);

    free(playlist);
    return 0;
}