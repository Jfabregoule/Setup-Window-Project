#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONDOWN: // G�rer le clic gauche de la souris
    {
        // R�cup�rer les coordonn�es du clic de la souris
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        // Dessiner un pixel al�atoire en bleu � ces coordonn�es
        HDC hdc = GetDC(hwnd);
        SetPixel(hdc, x, y, RGB(0, 0, 255)); // Bleu (0, 0, 255)
        ReleaseDC(hwnd, hdc);
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Cr�ation de la fen�tre
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Options de la fen�tre
        L"MyWindowClass",                // Classe de la fen�tre
        L"Chat Client",                  // Titre de la fen�tre
        WS_OVERLAPPEDWINDOW,            // Style de la fen�tre
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position de la fen�tre (par d�faut)
        800, 600,                       // Taille de la fen�tre
        NULL,                           // Handle de la fen�tre parent
        NULL,                           // Handle du menu
        hInstance,                      // Instance de l'application
        NULL                            // Donn�es de cr�ation de fen�tre suppl�mentaires
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Failed to create window!", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);

    // Boucle principale de messages de la fen�tre
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
