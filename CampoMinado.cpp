#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define linhas 3
#define colunas 3
#define minas 2

int main() {
    int vlinhas = linhas, vcolunas = colunas, vminas = minas, menu; //tranforma as constantes em variaveis para que possa ser manipulada durante o codigo!

    do{ //Faz um loop infinito para que o menu sempre apareça.
        cout << "Menu do Jogador, Escolha uma opção:\n";
        cout << "1. Jogar\n";
        cout << "2. Sobre\n";
        cout << "3. Sair\n";
        cin >> menu;

        switch (menu) {
            case 1:{
                // Garantir que haja pelo menos 2 minas e que o tabuleiro tenha mais de 1 linha e coluna.
                if (vminas < 2) vminas = 2;
                if (vlinhas < 2) vlinhas = 2;
                if (vcolunas < 2) vcolunas = 2;

                int tabuleiro[vlinhas][vcolunas];
                bool revelado[vlinhas][vcolunas];

                for (int i = 0; i < vlinhas; i++) { // Inicializa o tabuleiro e o estado das células reveladas.
                    for (int j = 0; j < vcolunas; j++) {
                        tabuleiro[i][j] = 0;
                        revelado[i][j] = false;
                    }
                }

                srand(time(NULL));
                int minasColocadas = 0;
                while (minasColocadas < vminas) { // Distribui as minas aleatoriamente.
                    int linha = rand() % vlinhas;
                    int coluna = rand() % vcolunas;
                    if (tabuleiro[linha][coluna] != 9) { // Verifica se a célula já contém uma mina.
                        tabuleiro[linha][coluna] = 9;
                        minasColocadas++;
                        for (int i = -1; i <= 1; i++) { // Atualiza os números adjacentes.
                            for (int j = -1; j <= 1; j++) {
                                int adjLinha = linha + i;
                                int adjColuna = coluna + j;
                                if (adjLinha >= 0 && adjLinha < vlinhas && adjColuna >= 0 && adjColuna < vcolunas && 
                                  tabuleiro[adjLinha][adjColuna] != 9) {
                                    tabuleiro[adjLinha][adjColuna]++;
                                }
                            }
                        }
                    }
                }

                int jogadasValidas = 0;
                bool jogoTerminado = false;

                while (!jogoTerminado) { // Loop principal do jogo.
                    cout<<"\033c";
                    cout << "  "; // Exibe o tabuleiro.
                    for (int j = 0; j < vcolunas; j++) {
                        cout << j << " ";
                    }
                    cout << endl;
                    for (int i = 0; i < vlinhas; i++) {
                        cout << i << " ";
                        for (int j = 0; j < vcolunas; j++) {
                            if (revelado[i][j]) {
                                if (tabuleiro[i][j] == 9) {
                                    cout << "X ";
                                } else {
                                    cout << tabuleiro[i][j] << " ";
                                }
                            } else {
                                cout << ". ";
                            }
                        }
                        cout << endl;
                    }

                    // Leitura dos dados de linha e coluna.
                    int linha, coluna;
                    cout << "Informe uma linha (0-" << vlinhas - 1 << "): ";
                    cin >> linha;
                    cout << "Informe uma coluna (0-" << vcolunas - 1 << "): ";
                    cin >> coluna;

                    if (linha < 0 || linha >= vlinhas || coluna < 0 || coluna >= vcolunas || revelado[linha][coluna]) {
                        cout << "Coordenadas inválidas ou posição já revelada. Tente novamente." << endl;
                        bool entradaValida = false;
                        while (!entradaValida) {
                            cout << "Pressione 1 para tentar novamente: ";
                            int resposta;
                            cin >> resposta;
                            if (resposta == 1) {
                                entradaValida = true;
                            }
                        }
                    }  else {
                        revelado[linha][coluna] = true;
                        if(tabuleiro[linha][coluna] != 9) { // Adiciona ao contador de jogadas válidas, se não for uma mina.
                            jogadasValidas++;
                        }

                        if (tabuleiro[linha][coluna] == 9) { // Verifica se o jogador acertou uma mina.
                            cout<<"\033c";
                            cout << "Você acertou uma mina! Fim de jogo." << endl;
                            jogoTerminado = true;
                        } else { // Verifica se o jogador revelou todas as posições livres
                            bool vitoria = true;
                            for (int i = 0; i < vlinhas; i++) {
                                for (int j = 0; j < vcolunas; j++) {
                                    if (tabuleiro[i][j] != 9 && !revelado[i][j]) {
                                        vitoria = false;
                                    }
                                }
                            }
                            if (vitoria) {
                                cout<<"\033c";
                                cout << "Parabéns! Você revelou todas as posições livres!" << endl;
                                jogoTerminado = true;
                            }
                        }
                    }
                }

                // Exibe o tabuleiro final
                cout << "Tabuleiro final:" << endl;
                cout << "  ";
                for (int j = 0; j < vcolunas; j++) {
                    cout << j << " ";
                }
                cout << endl;
                for (int i = 0; i < vlinhas; i++) {
                    cout << i << " ";
                    for (int j = 0; j < vcolunas; j++) {
                        if (tabuleiro[i][j] == 9) {
                            cout << "X ";
                        } else {
                            cout << tabuleiro[i][j] << " ";
                        }
                    }
                    cout << endl;
                }

                cout << "Número de jogadas válidas: " <<                   jogadasValidas << endl;
                char jogarNovamente;
                jogarNovamente = 1;
          cout<<"Digite qualquer tecla para jogar novamente: ";
          cin>>jogarNovamente;
          break;
            }
            case 2: { //Mostra os criadores/data/orientador.
                cout<<"\033c";
                cout << "Equipe de Desenvolvimento:\n";
                cout << "- Antony Kellves de Sá Costa\n";
                cout << "- Carlos Miguel Bernardo\n";
                cout << "- Kaynan Matheus Wisenteiner\n";
                cout << "- Welby Roberto Pereira junior\n";
                cout << "- 13/jun - 25/jun\n";
                cout << " Junho/2024\n";
                cout << "Professor/Disciplina: Rafael Ballotin/Algoritmos e Programação\n";
                cout<<"\n\n";
                break;
            }
            case 3: {
                cout << "Obrigado por jogar! Até mais.\n";
                break;
            }default: {
                cout << "Opção inválida. Por favor, tente novamente.\n";
                cout<<"\n\n";
                break;
            }
        }


    } while (menu != 3);
}