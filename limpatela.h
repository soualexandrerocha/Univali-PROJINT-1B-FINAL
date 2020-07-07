#ifndef LIMPATELA_H_INCLUDED
#define LIMPATELA_H_INCLUDED

#include <iostream>
#include <windows.h>

using namespace std;

void LimpaTela()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Captura o número de células do buffer do console*/
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Preenche todas as posições com espaços */
    if (!FillConsoleOutputCharacter(
                hStdOut,
                (TCHAR) ' ',
                cellCount,
                homeCoords,
                &count
            )) return;

    /* Preenche tudo com as cores e atributos vigentes */
    if (!FillConsoleOutputAttribute(
                hStdOut,
                csbi.wAttributes,
                cellCount,
                homeCoords,
                &count
            )) return;

    /* Leva o cursor para a posição (0,0) */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

#else

// versão para Linux

#include <unistd.h>
#include <term.h>

void LimpaTela()
{
    if (!cur_term)
    {
        int result;
        setupterm( NULL, STDOUT_FILENO, &result );
        if (result <= 0) return;
    }

    putp( tigetstr( "clear" ) );
}

#endif // LIMPATELA_H_INCLUDED
