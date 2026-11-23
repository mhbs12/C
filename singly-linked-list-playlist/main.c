#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//musica dentro de cada no.
typedef struct {
    char titulo[100];
    char nomeArtista[100];
    int duracaoSegundos;

} Musica;

//No para estruturar a lista.
typedef struct No{
    Musica musica;
    struct No *proximo;

} No;

//funcao que retorna NULL para inicializar nossa playlist.
No *inicializar(){
    return NULL;
}

//funcao que le e retorna todos os parametros da nova musica que vai ser inserida.
Musica lerNovaMusica(){
    Musica musica;
    printf("\nDigite o titulo da musica que quer adicionar: ");
    fgets(musica.titulo, sizeof(musica.titulo), stdin);
    //o fgets guarda o enter junto, entao trocamos o \n por \0.
    musica.titulo[strcspn(musica.titulo, "\n")] = '\0';
    printf("\nDigite o nome do artista dessa musica: ");
    fgets(musica.nomeArtista, sizeof(musica.nomeArtista), stdin);
    musica.nomeArtista[strcspn(musica.nomeArtista, "\n")] = '\0';
    printf("\nDigite a duracao em segundos dessa musica: ");
    scanf(" %d", &musica.duracaoSegundos);
    //limpa o buffer para o proximo fgets nao ler o enter que sobrou.
    while(getchar() != '\n');
    return musica;
}

//funcao que percorre a playlist e mostra todas as musicas.
void exibirPlaylist(No *playlist){
    if(playlist == NULL){
        printf("\nA playlist esta vazia!\n");
        return;
    }
    //usamos um ponteiro auxiliar para nao perder o inicio da lista.
    int posicao = 1;
    No *atual = playlist;
    printf("\n----- Playlist -----");
    while(atual != NULL){
        printf("\n%d - %s | %s | %d segundos", posicao, atual->musica.titulo, atual->musica.nomeArtista, atual->musica.duracaoSegundos);
        atual = atual->proximo;
        posicao++;
    }
    printf("\n");
}

//funcao unificada para manipular a adicao de musicas na playlist.
//modo 1 = adicionar no inicio.
//modo 2 = adicionar no final.
//modo 3 = adicionar no meio de outras musicas quaisquer.
void adicionarMusica(No **playlist, int modo){
    if(modo == 1){
        No *novo = (No*)malloc(sizeof(No));
        if (novo == NULL) {
        printf("\nErro: Falha na alocacao de memoria!\n");
        return;
        }
        novo->musica = lerNovaMusica();
        //o novo aponta para o antigo primeiro e vira o inicio.
        novo->proximo = *playlist;
        *playlist = novo;

    }

    if(modo == 2){
        No *novo = (No*)malloc(sizeof(No));
        if (novo == NULL) {
        printf("\nErro: Falha na alocacao de memoria!\n");
        return;
        }
        novo->musica = lerNovaMusica();
        novo->proximo = NULL;
        //lista vazia, o novo ja e o primeiro e o ultimo.
        if(*playlist == NULL){
            *playlist = novo;
            return;
        }
        //anda ate o ultimo no para ligar o novo depois dele.
        No *atual = *playlist;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    if(modo == 3){
        int q = 0;
        int escolha = 0;
        No *novo = (No*)malloc(sizeof(No));
        if (novo == NULL) {
        printf("\nErro: Falha na alocacao de memoria!\n");
        return;
        }
        //sem musicas entao liberamos o no.
        if(*playlist == NULL){
            printf("\nA playlist esta vazia, use a opcao 1 ou 2 para adicionar a primeira musica.\n");
            free(novo);
            return;
        }
        exibirPlaylist(*playlist);
        //contamos as musicas para saber quais posicoes sao validas.
        No *atual = *playlist;
        while(atual != NULL){
            q++;
            atual = atual->proximo;
        }
        printf("\nDigite a posicao da musica antes da qual quer adicionar a nova (1 a %d): ", q);
        scanf(" %d", &escolha);
        while(getchar() != '\n');

        //posicao invalida, o no alocado nao vai ser usado.
        if(escolha < 1 || escolha > q){
            printf("\nErro: Posicao invalida! Escolha um numero entre 1 e %d.\n", q);
            free(novo);
            return;
        }
        novo->musica = lerNovaMusica();

        //antes da primeira e a mesma coisa que inserir no inicio.
        if(escolha == 1){
            novo->proximo = *playlist;
            *playlist = novo;
            return;
        }
        //paramos na musica anterior a escolhida, pois so ela consegue apontar para o novo no.
        atual = *playlist;
        for(int i = 1; i < escolha - 1; i++){
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

//funcao que remove uma musica da playlist pelo titulo.
void removerMusica(No **playlist){
    char titulo[100];
    if(*playlist == NULL){
        printf("\nA playlist esta vazia, nao ha musicas para remover!\n");
        return;
    }
    printf("\nDigite o titulo da musica que quer remover: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    //guardamos o anterior pois e ele que vai pular o no removido.
    No *anterior = NULL;
    No *atual = *playlist;
    while(atual != NULL && strcmp(atual->musica.titulo, titulo) != 0){
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL){
        printf("\nA musica %s nao foi encontrada na playlist!\n", titulo);
        return;
    }
    //se nao tem anterior a musica e a primeira, entao o inicio muda.
    if(anterior == NULL){
        *playlist = atual->proximo;
    }else{
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("\nMusica %s removida com sucesso!\n", titulo);
}

//funcao que busca uma musica pelo titulo e mostra seus dados e sua posicao na playlist.
void buscarMusica(No *playlist){
    char titulo[100];
    if(playlist == NULL){
        printf("\nA playlist esta vazia, nao ha musicas para buscar!\n");
        return;
    }
    printf("\nDigite o titulo da musica que quer buscar: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    int posicao = 1;
    No *atual = playlist;
    while(atual != NULL){
        //strcmp retorna 0 quando os titulos sao iguais.
        if(strcmp(atual->musica.titulo, titulo) == 0){
            printf("\nMusica encontrada na posicao %d:", posicao);
            printf("\nTitulo: %s", atual->musica.titulo);
            printf("\nArtista: %s", atual->musica.nomeArtista);
            printf("\nDuracao: %d segundos\n", atual->musica.duracaoSegundos);
            return;
        }
        atual = atual->proximo;
        posicao++;
    }
    printf("\nA musica %s nao foi encontrada na playlist!\n", titulo);
}

//funcao que libera todos os nos da playlist.
void liberarPlaylist(No **playlist){
    No *atual = *playlist;
    while(atual != NULL){
        //guardamos o proximo antes do free, depois nao da mais para acessar.
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *playlist = NULL;
}

int main(){
    int op;

    //atribuimos NULL para definir o inicio da nossa playlist vazia.
    No *playlist = inicializar();

    do{
        op = -1;
        printf("\nEscolha uma opcao:");
        printf("\n1 - Adicionar musica ao inicio.");
        printf("\n2 - Adicionar musica ao final.");
        printf("\n3 - Inserir musica antes de...");
        printf("\n4 - Remover musica.");
        printf("\n5 - Buscar musica.");
        printf("\n6 - Exibir playlist.");
        printf("\n0 - Sair.");
        printf("\n");
        scanf(" %d", &op);
        while(getchar() != '\n');

        //a playlist vai com & quando a funcao pode mudar o inicio da lista.
        switch(op){
            case 1:
                adicionarMusica(&playlist, 1);
                break;
            case 2:
                adicionarMusica(&playlist, 2);
                break;
            case 3:
                adicionarMusica(&playlist, 3);
                break;
            case 4:
                removerMusica(&playlist);
                break;
            case 5:
                buscarMusica(playlist);
                break;
            case 6:
                exibirPlaylist(playlist);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    }while(op!=0);

    //libera todos os nos alocados.
    liberarPlaylist(&playlist);
    return 0;
}
