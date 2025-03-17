#include <Windows.h>
LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;

	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MyWndClass";

	RegisterClass(&wc);

	hwnd = CreateWindow(
		L"MyWndClass", // WNDCLASS name
		L"SDK Application", // Window title
		WS_OVERLAPPEDWINDOW,// Window style
		CW_USEDEFAULT, // Horizontal position
		CW_USEDEFAULT, // Vertical position
		300, // Initial width
		200, // Initial height
		HWND_DESKTOP, // Handle of parent window
		NULL, // Menu handle
		hInstance, // Application's instance handle
		NULL // Window-creation data
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

// CALLBACK 함수, 함수 전체를 다른 함수의 매개변수로 넘겨 줄 수 있음, 따로 선언하지 않아도 자동으로 선언됨.

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps; // a structure need to paint the client area of a window
	HDC hdc; // a device context need for drawing on a window

	switch (message) {

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); // start of drawing objects
		Rectangle(hdc, 200, 100, 250, 150); // draw a rectangle using a start and an end point
		Ellipse(hdc, 0, 0, 200, 100); // draw an ellipse using a start and an end point
		EndPaint(hwnd, &ps); // end of drawing objects

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, L"Test", L"Pop-up Box", MB_OK);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}