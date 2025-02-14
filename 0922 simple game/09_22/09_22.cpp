﻿// 09_22.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "09_22.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY0922, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0922));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0922));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0922);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 제어할 사각형 선언
RECT g_rect;
// 상대방의 사각형 선언
RECT g_you;
//범위 지정 사각형 선언
RECT g_bigrect;
// 타이머 시간 값 제어 변수
int g_timer;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_TIMER:
       // MessageBox(hWnd, L"타이머가 도착했어요", L"심재호", MB_OK);
        if (1 == wParam)
        {
            // 타이머 값 감소
            if (150 <= g_timer)
                g_timer -= 100;
            // 타이머 재설정
            KillTimer(hWnd, 1);
            SetTimer(hWnd, 1, g_timer, NULL);

            if (g_rect.left < g_you.left)
            {
                if (g_you.left > g_bigrect.left)
                {                
                g_you.left -= 10;
                g_you.right -= 10;
                }
            }
            else
            {
                if (g_you.right < g_bigrect.right) {
                    g_you.left += 10;
                    g_you.right += 10;
                }
            }
            if (g_rect.top < g_you.top)
            {
                if (g_you.top > g_bigrect.top) {
                    g_you.top -= 10;
                    g_you.bottom -= 10;
                }
            }
            else
            {
                if (g_you.bottom < g_bigrect.bottom) {
                    g_you.top += 10;
                    g_you.bottom += 10;
                }
            }
            /////////////// 상대의 좌표 계산 및 이동 완료
            InvalidateRect(hWnd, NULL, true);
            // 겹침이 발생한 경우의 겸침 영역 좌표를 받아올 변수
            RECT isr;

            if (true == IntersectRect(&isr, &g_rect, &g_you))
            {
                // 타이머를 해제
                KillTimer(hWnd, 1);
                // 나는 현재 잡힌 상태
                MessageBox(hWnd, L"GAME OVER", L"아쉬워라", MB_OK);
            }
        }
        else if (2 == wParam)
        {

        }
        
        break;
    // 프로그램이 실행될때, 단 한번 OS가 호출해주는 생성자와 같은 윈도우 메시지
    case WM_CREATE:
    {
        // 타이머 기본 값 설정
        g_timer = 1000;

        // 타이머 설정 - 상대방의 이동
        SetTimer(hWnd, 1, g_timer, NULL);
        // 시간을 재기 위한 타이머
        SetTimer(hWnd, 2, 1000, NULL);

        // 나의 사각형의 기본 좌표를 설정
        g_rect.left = 10;
        g_rect.top = 10;
        g_rect.right = 80;
        g_rect.bottom = 80;

        // 상대방 사각형의 기본 좌표를 설정
        g_you.left = 300;
        g_you.top = 300;
        g_you.right = 370;
        g_you.bottom = 370;

        // 범위 지정 사각형
        g_bigrect.left = 10;
        g_bigrect.top = 10;
        g_bigrect.right = 800;
        g_bigrect.bottom = 500;
    }   
        break;

    // 키보드 입력
    case WM_KEYDOWN:
    {
        // 키 값에 따라 처리를 수행
        switch (wParam)
        {
        // 왼쪽 방향키 입력
        case VK_LEFT:
            //왼쪽 범위 지정
            if(g_rect.left > g_bigrect.left)
            { 
            g_rect.left -= 10;
            g_rect.right -= 10;
            }
            break;
        // 오른쪽 방향키 입력
        case VK_RIGHT:
            //오른쪽 범위 지정
            if (g_rect.right < g_bigrect.right) {
                g_rect.left += 10;
                g_rect.right += 10;
            }
            break;
        // 위쪽 방향키 입력
        case VK_UP:
            //위쪽 범위 지정
            if (g_rect.top > g_bigrect.top) {
                g_rect.top -= 10;
                g_rect.bottom -= 10;
            }
            break;
        // 아래쪽 방향키 입력
        case VK_DOWN:
            //아래쪽 범위 지정
            if (g_rect.bottom < g_bigrect.bottom) {
                g_rect.top += 10;
                g_rect.bottom += 10;
            }
            break;
        }

        // 변경된 좌표 값이 적용된 그림을 그리도록 화면 무효화를 요청
        InvalidateRect(hWnd, NULL, true);
    }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            //범위 지정 사각형 그리기.
            Rectangle(hdc, g_bigrect.left, g_bigrect.top, g_bigrect.right, g_bigrect.bottom);

            // 나의 사각형 그린다.
            Rectangle(hdc, g_rect.left, g_rect.top, g_rect.right, g_rect.bottom);

            // 상대방 사각형 그린다.
            Rectangle(hdc, g_you.left, g_you.top, g_you.right, g_you.bottom);

            

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
