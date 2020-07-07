
#include <iostream>
#include <windows.h> //para funcionar o text color
#include <conio.h> //getch()
#include <chrono> // para controlar o tempo passado
#include <iomanip>
#include <locale.h>
#include "limpatela.h"

using namespace std;

#define L 10
#define C 10

#define BLACK        0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GRAY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15

void textcolor (int forecolor, int backcolor)
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (WORD) (forecolor | backcolor<<4));
}

void textbackground (int newcolor)
{
    newcolor = newcolor << 4;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (WORD) (newcolor| newcolor));
}

///fase bonus


int main()
{


    //INICIO: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // cursor fica invisível
    SetConsoleCursorInfo(out, &cursorInfo);
    //FIM: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
    //INÍCIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
    short int CX=0, CY=0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA

    int menu;
    int movimentos = 0;


    ///criação de uma matriz
    int mapa[L][C]= {   1,1,1,1,1,1,1,1,1,1,
                        1,0,0,0,0,0,0,1,0,1,
                        1,0,0,0,1,2,0,1,0,1,
                        1,1,1,0,1,0,0,1,0,1,
                        1,0,0,2,0,0,0,1,0,1,
                        1,1,1,0,1,1,0,1,0,1,
                        1,0,0,0,1,1,1,1,0,1,
                        1,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,3,1,
                        1,1,1,1,1,1,1,1,1,1
                    };
    char tecla;


    ///laço do menu
    while(1)
    {
        textcolor(BLACK,WHITE);
        textbackground(WHITE);
        LimpaTela();
        cout<<"\n\n\t\tBEM-VINDO AO";
        cout<<"\n\n\t\tLABIRINTO\n\n";
        cout<<"\n\n\t\t1:\tJOGAR";
        cout<<"\n\n\t\t2:\tCOMANDOS";
        cout<<"\n\n\t\t3:\tSOBRE\n\n";
        textcolor(WHITE,RED);
        cout<<"\n\n\t\tESC:\tSAIR";
        textcolor(BRIGHTWHITE,BLACK);
        menu=getch();

        if (menu==49)  ///significa que apertou o 1 no teclado
        {
            setlocale (LC_ALL, "Englhish_US.1252");

            int jogador_x,jogador_y; ///posição do personagem
            jogador_x=2;
            jogador_y=3;

            tecla = 0;

            LimpaTela();

            Beep (1000,1000);

            auto t0 = chrono::steady_clock::now();

            ///laço do jogo

            do
            {

                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                for (int i=0; i<L; i=i+1)
                {
                    for (int j=0; j<C; j=j+1)
                    {
                        if(i==jogador_x and j==jogador_y)
                        {
                            textcolor (BRIGHTWHITE,GRAY);
                            cout<<char(207);
                        }
                        else if(mapa[i][j]==2)
                        {
                            textcolor (RED,BLACK);
                            cout<<char(219);

                        }
                        else if(mapa[i][j]==1)
                        {
                            textcolor (BRIGHTWHITE,BLACK);
                            cout<<char(176);
                        }
                        else if(mapa[i][j]==3)
                        {
                            textcolor (BRIGHTWHITE,GREEN);
                            cout<<char(197);
                        }
                        else
                        {
                            textcolor (BRIGHTWHITE,GRAY);
                            cout<<" ";
                        }
                    }
                    cout<<"\n";
                }
                if (mapa[jogador_x][jogador_y]==3)
                    break;

                tecla=getch();
                tecla=tolower(tecla);


                switch (tecla)

                {
                case 'w':
                    if (mapa[jogador_x-1][jogador_y]==2 && mapa[jogador_x-2][jogador_y]==0)
                    {
                        mapa[jogador_x-1][jogador_y]=0;
                        mapa[jogador_x-2][jogador_y]=2;
                        jogador_x--;
                        movimentos++;

                    }
                    else if((mapa[jogador_x-1][jogador_y]==0) || (mapa[jogador_x-1][jogador_y]==3) )
                    {
                        jogador_x--;
                        movimentos++;
                    }
                    break;
                case 's':
                    if (mapa[jogador_x+1][jogador_y]==2 && mapa[jogador_x+2][jogador_y]==0)
                    {
                        mapa[jogador_x+1][jogador_y]=0;
                        mapa[jogador_x+2][jogador_y]=2;
                        jogador_x++;
                        movimentos++;
                    }
                    else if (mapa[jogador_x+1][jogador_y]==0 || mapa[jogador_x+1][jogador_y]==3)
                    {
                        jogador_x++;
                        movimentos++;
                    }
                    break;
                case 'a':
                    if (mapa[jogador_x][jogador_y-1]==2 && mapa[jogador_x][jogador_y-2]==0)
                    {
                        mapa[jogador_x][jogador_y-1]=0;
                        mapa[jogador_x][jogador_y-2]=2;
                        jogador_y--;
                        movimentos++;
                    }
                    else if (mapa[jogador_x][jogador_y-1]==0)
                    {
                        jogador_y=jogador_y-1;
                        movimentos++;
                    }
                    break;
                case 'd':
                    if (mapa[jogador_x][jogador_y+1]==2 && mapa[jogador_x][jogador_y+2]==0)
                    {
                        mapa[jogador_x][jogador_y+1]=0;
                        mapa[jogador_x][jogador_y+2]=2;
                        jogador_y++;
                        movimentos++;
                    }
                    else if ((mapa[jogador_x][jogador_y+1]==0) || (mapa[jogador_x][jogador_y+1]==3))
                    {
                        jogador_y++;
                        movimentos++;
                    }
                    break;
                }
                auto t1 = chrono::steady_clock::now();
                auto deltat = chrono::duration <float> {t1-t0};
                SetConsoleCursorPosition(out, {0,15});
                cout << setprecision(2) << fixed;
                cout << "Tempo decorrido: " << deltat.count() << " segundos\n";
                cout << "Movimentos: " << (movimentos) << endl << endl;

            }
            while (tecla!=27);

            switch (tecla)

            case (27):
        {
            cout<<"\n\nTecla ESC pressionada... Retornando para o menu principal";
            Sleep (3000);
            LimpaTela();
            break;
            default:
                auto t1 = chrono::steady_clock::now();
                textcolor (BLACK, YELLOW);
                SetConsoleCursorPosition(out, {0,20});
                cout << "EXCELENTE!!!\n\n";
                cout << setprecision(2) << fixed;
                cout << "Completou o labirinto em " << chrono::duration <float> {t1-t0}.count() << " segundos\n";
                cout << "com " << (movimentos) << " movimentos";
                Sleep (5000);
                textcolor (BRIGHTWHITE, BLACK);


            }
        }

        else if (menu==50)    ///significa que apertou o 2 no teclado
        {

            textbackground (YELLOW);
            LimpaTela();
            cout<<"\n\n\t\tCOMANDOS";

            cout<<endl<<endl;

            cout<<"\n\n\t\tW: para cima";
            cout<<"\n\n\t\tS: para baixo";
            cout<<"\n\n\t\tA: para a esquerda";
            cout<<"\n\n\t\tD: para a direita";
            cout<<"\n\n\t\tESC: volta ao menu"<<endl<<endl;
            system("pause");
        }

        else if (menu==51)
        {

            textbackground (BLUE);
            textcolor(BRIGHTWHITE, BLUE);
            LimpaTela();
            cout<<"\n\n\t\tLABIRINTO";
            cout<<"\n\n\t\tDesenvolvido por Alexandre Goncalves da Rocha como requisito parcial de aprovacao";
            cout<<"\n\n\t\tna disciplina Projeto Integrador I-B de Engenharia de Producao";
            cout<<"\n\n\t\tda Universidade do Vale do Itajai"<<endl<<endl;
            cout<<"\n\n\t\tItajai, Santa Catarina, julho de 2020";
            cout<<"\n\n\t\tPor favor, aguarde...";
            Sleep (5000);

        }
        else if (menu==27)    ///significa que apertou o ESC no teclado
        {
            LimpaTela();
            cout<<"Obrigado por jogar!";
            return 0;
        }
    }



    return 0;
}
