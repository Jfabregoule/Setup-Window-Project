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
    case WM_LBUTTONDOWN: // Gérer le clic gauche de la souris
    {
        // Récupérer les coordonnées du clic de la souris
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        // Dessiner un pixel aléatoire en bleu à ces coordonnées
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
    // Création de la fenêtre
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Options de la fenêtre
        L"MyWindowClass",                // Classe de la fenêtre
        L"Chat Client",                  // Titre de la fenêtre
        WS_OVERLAPPEDWINDOW,            // Style de la fenêtre
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position de la fenêtre (par défaut)
        800, 600,                       // Taille de la fenêtre
        NULL,                           // Handle de la fenêtre parent
        NULL,                           // Handle du menu
        hInstance,                      // Instance de l'application
        NULL                            // Données de création de fenêtre supplémentaires
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Failed to create window!", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);

    // Boucle principale de messages de la fenêtre
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
