#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;
///Fun��o que auxilia na colis�o de blocos
void InverteBloco (int &bolaX, int &bolaY, int &direcaoX, int &direcaoY, int m[22][22], int&pontos){
    direcaoX= -direcaoX; //inverte sentido
    direcaoY = (rand() % 3) -1;//randomiza dire��o
        if (m[bolaX+direcaoX][bolaY+direcaoY]==2){//Se na nova dire��o h� um bloco
                m[bolaX+direcaoX][bolaY+direcaoY]=0;//Tira o bloco
                pontos+= 3; //Adiciona tr�s pontos
                direcaoY = (rand() % 2) ? -direcaoY : 0;//tenta outras
        }

}
///Fun��o que auxilia na colis�o de paredes
void InverteParede (int &bolaX, int &bolaY, int &direcaoX, int &direcaoY, int m[22][22]){
    direcaoX= -direcaoX; //inverte sentido
    direcaoY = (rand() % 3) -1;//randomiza dire��o
        if (m[bolaX+direcaoX][bolaY+direcaoY]==1){//Se na nova dire��o h� uma parede
                direcaoY = (rand() % 2) ? -direcaoY : 0;//tenta outras
        }

}
///Detecta colis�o com blocos, e remove
void Blocos (int &bolaX, int &bolaY, int &direcaoX, int &direcaoY, int m[22][22], int&pontos){
    if (m[bolaX+direcaoX][bolaY]==2){///Se h� uma colis�o vertical
            m[bolaX+direcaoX][bolaY]=0;//Tira o bloco
            pontos+= 3; //Adiciona tr�s pontos
            InverteBloco (bolaX,bolaY,direcaoX,direcaoY,m,pontos); //Colide
    } else if (m[bolaX][bolaY+direcaoY]==2){ ///Se h� uma colis�o lateral
                m[bolaX][bolaY+direcaoY]=0;//Tira o bloco
                pontos+= 3; //Adiciona tr�s pontos
                direcaoY= -direcaoY;//inverte dire��o
    } else if (m[bolaX+direcaoX][bolaY+direcaoY]==2){///Se h� uma colis�o diagonal
                m[bolaX+direcaoX][bolaY+direcaoY]=0;//Tira o bloco
                pontos+= 3; //Adiciona tr�s pontos
                InverteBloco (bolaX,bolaY,direcaoX,direcaoY,m,pontos); //Colide
    } else if (m[bolaX][bolaY] == 2) { ///Entrou em um bloco
                m[bolaX][bolaY] = 0; //Remove o bloco
                pontos += 3; //Pontos
                InverteBloco (bolaX,bolaY,direcaoX,direcaoY,m,pontos); //Colide
    }
}
///Detecta colis�o com paredes
void Paredes (int &bolaX, int &bolaY, int &direcaoX, int &direcaoY, int m[22][22]){
    if (m[bolaX+direcaoX][bolaY]==1){///Se h� uma colis�o vertical
        InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    } else if (m[bolaX][bolaY+direcaoY]==1){ ///Se h� uma colis�o lateral
                direcaoY= -direcaoY;//inverte dire��o
    } else if (m[bolaX+direcaoX][bolaY+direcaoY]==1){///Se h� uma colis�o diagonal
                InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    } else if (m[bolaX][bolaY] == 1){ ///Entrou em uma parede
        if (direcaoY>0) { //Vindo da esquerda
                bolaY--; //For�a 1 para esquerda
                InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
            }else if (direcaoY<0) { //Vindo da direita
                        bolaY++; //For�a 1 para direita
                        InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
            }else if (direcaoX>0){ //Se vem de cima
                        bolaX--; //For�a um para cima
                        InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
            }else if (direcaoX<0){ //Se vem de baixo
                        bolaX++;//For�a um para baixo
                        InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
            }
        }
}
///Diferencia blocos e paredes
void Colisao (int &bolaX, int &bolaY, int &direcaoX, int &direcaoY, int m[22][22], int&pontos){
    Blocos (bolaX,bolaY,direcaoX,direcaoY,m,pontos);
    Paredes (bolaX,bolaY,direcaoX,direcaoY,m);
}
///Func. para movimentar a bolinha
void moverBolinha(int &bolaX, int &bolaY, int &direcaoX, int &direcaoY, int m[22][22], int paddleY, int&pontos, int&menu, int&jogando, int&alvo) {
    srand(static_cast<unsigned int>(time(0)));
///PONTUA��O COME�O
    if (pontos == alvo) { ///Verifica a pontua��o
        jogando = 0; // Para o jogo e retorna ao menu
        menu = 5;
        return; //sair da fun��o
    }
///PONTUA��O FIM

///PADDLE COME�O
    if ((bolaX + direcaoX == 18) && (bolaY >= paddleY - 1) && (bolaY <= paddleY + 4)) {
        direcaoX = -1; // Faz a bolinha ir para cima
        if (bolaY == paddleY - 1) { ///Bate no extremo esquerdo
            if (bolaY > 1) { ///Se n�o est� no canto esquerdo do mapa
                direcaoY = -1; //for�a esquerda
            } else {
                direcaoY = 1; //for�a direita
            }
        } else if (bolaY == paddleY) { ///Bate no esquerdo
            if (bolaY > 1) { ///Se n�o est� no canto esquerdo do mapa
                direcaoY = (rand() % 3) - 1; //qualquer dire��o
            } else {
            direcaoY = 1; //for�a direita
            }
        } else if (bolaY == paddleY + 4) { ///Bate no extremo direito
            if (bolaY < 21) { //Se n�o est� no canto direito do mapa
                direcaoY = 1; //for�a direita
            } else {
                direcaoY = -1; //for�a esquerda
            }
        } else if (bolaY == paddleY + 3) { ///Bate no direito
            if (bolaY < 21) { //Se n�o est� no canto direito do mapa
                direcaoY = (rand() % 3) - 1; //qualquer dire��o
            } else {
            direcaoY = -1; //for�a esquerda
            }
        } else { ///Bate em qualquer outra posi��o
            direcaoY = (rand() % 3) - 1; //qualquer dire��o
        }
    }
///PADDLE FIM

/// COME�O DA CORRE��O DE CLIPS
    if (bolaX<1){ ///Corrige clips no teto
        bolaX++; //For�a casa 1
        InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    }
    if (bolaY<1){ ///Corrige clips na extrema esquerda
        bolaY++; //For�a casa 1
        InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    } else if (bolaY>21){ ///Corrige clips na extrema direita
        bolaY--; //For�a casa 21
        InverteParede (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    }
/// FIM DA CORRE��O DE CLIPS

///DETECTOR DE COLIS�O COME�O
    Colisao(bolaX,bolaY,direcaoX,direcaoY,m,pontos);
///DETECTOR DE COLIS�O FIM


///COME�O ATUALIZA A DIRE��O
    bolaX+=direcaoX;
    bolaY+=direcaoY;
///FIMA ATUALIZA DIRE��O

/// COME�O GAME OVER
    if (bolaX > 19) {
        jogando = 0; /// Para o jogo e retorna ao menu
        menu = 6;
        return; //sair da fun��o
    }
///FIM GAME OVER
}


int main()
{
    int menu, jogando, submenu, dificuldade=1, pontos=0, alvo=30, velocidade=130;
    ///MAPAS
    int a[22][22]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,0,2,0,2,0,2,0,0,2,2,2,2,0,0,2,0,2,0,2,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    int b[22][22]={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,0,2,2,2,0,0,0,0,2,2,2,2,0,0,0,0,2,2,2,0,1,
                    1,0,0,2,2,2,0,0,2,2,0,2,2,0,0,0,2,2,2,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    int c[22][22]={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,0,2,2,2,0,0,0,2,2,0,2,2,0,0,0,0,2,2,2,0,1,
                    1,0,0,2,2,2,0,0,2,2,0,2,2,0,0,0,2,2,2,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,2,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,0,0,2,1,
                    1,2,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,0,0,2,1,
                    1,2,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,2,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    ///FACIL POR PADRAO
    int m[22][22]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,0,2,2,2,0,0,0,0,2,2,2,2,0,0,0,0,2,2,2,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    cout << "\nBEM VINDO AO ARKANOID!\n\nMENU\n\n[ 1 ] JOGAR\n[ 2 ] ESCOLHER A DIFICULDADE\n[ 3 ] SOBRE\n[ 4 ] SAIR\n"<< endl;
    cin >> menu;
    while (menu!=4) {
switch (menu) {
    case 1:
jogando=1;//jogando agora
pontos=0;//zera os pontos
system("cls");
///CARREGA O MAPA DE ACORDO COM A DIFICULDADE
if (dificuldade==1){
    for (int i = 0; i < 22; ++i) {
        for (int j = 0; j < 22; ++j) {
            m[i][j] = a[i][j];///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
                }
        }
    } else if (dificuldade==2){
        for (int i = 0; i < 22; ++i) {
            for (int j = 0; j < 22; ++j) {///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
                m[i][j] = b[i][j];
                }
            }
    } else {
        for (int i = 0; i < 22; ++i) {
            for (int j = 0; j < 22; ++j) {///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
                m[i][j] = c[i][j];
                }
            }
        }
///COME�A O JOGO
    do {
    // INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    // FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    // INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    // Posi��o inicial do personagem no console
    int x = 18, y = 8;
    // Posi��o e dire��o inicial da bolinha
    int bx = 10, by = 10; // Posi��o inicial da bolinha
    // Inicializa o gerador de n�meros aleat�rios
    srand(static_cast<unsigned int>(time(0)));
    int dx = -1; // Dire��o aleat�ria horizontal
    int dy = (rand() % 2) ? 1 : -1;// Dire��o vertical
    // Vari�vel para tecla pressionada
    char tecla;

    /// COME�O DAS VARI�VEIS DE TEMPO
    DWORD lastUpdate = GetTickCount();
    DWORD ballUpdateInterval = velocidade; // Intervalo para atualiza��o da bolinha em milissegundos
    /// FIM DAS VARI�VEIS DE TEMPO

///Enquanto n�o houver game over:
    while (jogando!=0) {
        // Posiciona a escrita no in�cio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        /// Atualiza e chama a bolinha para o jogo com base no tempo decorrido
        DWORD currentTick = GetTickCount();
        if (currentTick - lastUpdate > ballUpdateInterval) {
            lastUpdate = currentTick;
            moverBolinha(bx, by, dx, dy, m, y, pontos, menu,jogando,alvo);
        }
        // Imprime o jogo: mapa, paddle e bolinha
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 22; j++) {
                if (i == x && j >= y && j <= y + 3) {
                    cout << "=";
                } else if (i == bx && j == by) {
                    cout << "O"; // bolinha
                } else {
                    switch (m[i][j]) {
                        case 0: cout << " ";
                        break; // caminho
                        case 1: cout << char(219);
                        break; // parede
                        case 2: cout << char(35);
                        break; // blocos
                    }
                }
            }
            cout << "\n";
        }
        cout << "Pontos: "<< pontos << " de "<<alvo;

        /// Executa os movimentos do personagem
        if (_kbhit()) {
            tecla = getch();
            switch (tecla) {
                case 75: case 'a': // esquerda
                    if (y > 1) { // limite do mapa
                        y--;
                    }
                    break;
                case 77: case 'd': // direita
                    if (y < 17) { // limite do mapa
                        y++;
                    }
                    break;
            }
        }
    }

    } while (jogando==1);
break;

    case 2:
    do {
    system("cls");
        cout << "\nSELECIONAR DIFICULDADE\n" << endl;
        cout << "[ 1 ] FACIL\n";
        cout << "[ 2 ] MEDIO\n";
        cout << "[ 3 ] DIFICIL\n";
        cout << "ESCOLHA DIGITANDO O NUMERO [ X ]\n";
        cout << "Digite [ 0 ] para sair\n";
        cin >> submenu;
            if (submenu == 1) {
                    velocidade = 130;
                    alvo = 30;
                         for (int i = 0; i < 22; ++i) {
                            for (int j = 0; j < 22; ++j) {
                                m[i][j] = a[i][j];///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
                                    }
                                }
                     menu=99;///VAI PARA MENU DEFAULT
                     dificuldade=submenu; ///SALVA A DIFICULDADE
                     submenu=0; ///RESETA ESSE MENU

        } else if (submenu == 2) {
                    velocidade = 115;
                    alvo = 60;
                     for (int i = 0; i < 22; ++i) {
                            for (int j = 0; j < 22; ++j) {///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
                                m[i][j] = b[i][j];
                            }
                     }
                     menu=99;///VAI PARA MENU DEFAULT
                     dificuldade=submenu; ///SALVA A DIFICULDADE
                     submenu=0; ///RESETA ESSE MENU
        } else if (submenu == 3) {
                    velocidade = 100;
                    alvo = 90;
                     for (int i = 0; i < 22; ++i) {
                            for (int j = 0; j < 22; ++j) {///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
                                m[i][j] = c[i][j];
                            }
                     }
                     menu=99;///VAI PARA MENU DEFAULT
                     dificuldade=submenu; ///SALVA A DIFICULDADE
                     submenu=0; ///RESETA ESSE MENU
        } else {
                    menu = 99;
                    submenu=0;
        }
    } while (submenu!=0);
menu = 0;
break;

    case 3: ///MENU SOBRE
    system("cls");
        cout << "ARKANOID\nFoi lancado pela Taito em 1986\n";
        cout <<"E um jogo de quebrar blocos usando uma bolinha.\n";
        cout <<"Seu objetivo e destruir todos os blocos na tela.\n";
        cout <<"O jogador controla uma 'nave' (paddle) para rebater a bolinha.\n";
        cout <<"Com o tempo, surgiram versoes modernas e remakes.\n\n";
        cout <<"ARKANOID LITE\n";
        cout <<"Esta e minha versao simplificada do classico.\n";
        cout <<"Com jogabilidade e controles simples.\n";
        cout <<"Blocos, paredes e paddle compoem o desafio.\n";
        cout <<"Desenvolvido em C++ no Code::Blocks.";
        cout << "\n\nMENU\n\n[ 1 ] JOGAR\n[ 2 ] ESCOLHER A DIFICULDADE\n[ 3 ] SOBRE\n[ 4 ] SAIR\n"<< endl;
        cin >> menu;
break;
    case 4: ///SAIR
    return 0;
break;
    case 5: /// VIT�RIA
        system("cls");
        cout << "\n\nVOCE VENCEU! PARABENS!\nOBRIGADO POR JOGAR!"<< endl;
        cout << "\n\nMENU\n\n[ 1 ] JOGAR\n[ 2 ] ESCOLHER A DIFICULDADE\n[ 3 ] SOBRE\n[ 4 ] SAIR\n"<< endl;
        cin >> menu;
break;
    case 6: /// DERROTA
        system("cls");
        cout << "\n\nVOCE PERDEU!\nPARABENS PELOS "<<pontos<<" PONTOS!"<< endl;
        cout << "\n\nMENU\n\n[ 1 ] JOGAR\n[ 2 ] ESCOLHER A DIFICULDADE\n[ 3 ] SOBRE\n[ 4 ] SAIR\n"<< endl;
        cin >> menu;
break;
    default: /// INV�LIDO
        system("cls");
        cout << "\nBEM VINDO AO ARKANOID!\n\nMENU\n\n[ 1 ] JOGAR\n[ 2 ] ESCOLHER A DIFICULDADE\n[ 3 ] SOBRE\n[ 4 ] SAIR\n"<< endl;
        cin >> menu;
break;
        }
    }
}
