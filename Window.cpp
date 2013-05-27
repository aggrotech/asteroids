#include "Window.h"

const LPCTSTR Aggrotech::Window::WindowClassName = TEXT("AsteroidsWindowClassName");

bool Aggrotech::Window::DetermineWindowDimensions(int &x, int &y, int &width, int &height)
{
    RECT rect = { x, y, width, height };
    BOOL success = ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    x       = rect.left;
    y       = rect.top;
    width   = rect.right;
    height  = rect.bottom;

    return success != 0;
}

Aggrotech::Window::Window(const std::string &title, int x, int y, int width, int height, char *args, int nCmdShow) 
    : width(width), height(height), title(title), isRunning(true) 
{
    MakeWindowClass();
    MakeWindow(x, y, width, height);

    ::ShowWindow(window, nCmdShow);
    ::UpdateWindow(window);

    cmdLine = args;
}

bool Aggrotech::Window::Show(bool show)
{
    int nCmdShow = (show == true) ? SW_SHOW : SW_HIDE;

    return ::ShowWindow(window, nCmdShow) && ::UpdateWindow(window);
}

bool Aggrotech::Window::BringToForeground( )
{
    return ::SetForegroundWindow(window) != 0;
}

int Aggrotech::Window::Run()
{
    MSG msg;
    //GameTimer timer;

    while(isRunning)
    {
        if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        } 
        else
        {
            //timer.Tick();
            //viewer->Update( timer.GetFrameDelta() );
        }
    }

    return static_cast< int >(msg.wParam);
}

HWND Aggrotech::Window::GetWindowHandle() const
{
    return window;
}

int Aggrotech::Window::GetWidth() const
{
    return width;
}

int Aggrotech::Window::GetHeight() const
{
    return height;
}

Aggrotech::Window::~Window() {
    Shutdown();
}

void Aggrotech::Window::HandleKeyboardInput( WPARAM key )
{
    
}

void Aggrotech::Window::HandleMouseInput( WORD x, WORD y, UINT type )
{
    
}

void Aggrotech::Window::Shutdown()
{
    ::UnregisterClass(WindowClassName, GetModuleHandle(NULL));
    ::DestroyWindow(window);
}

LRESULT CALLBACK Aggrotech::Window::WindowProcedure(HWND hwnd, UINT msg, WPARAM arg1, LPARAM arg2)
{
    static POINT p;

    switch(msg)
    {
        // Handle mouse messages.
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MOUSEWHEEL:
            ::GetCursorPos(&p);
            ::ScreenToClient(hwnd, &p);
            HandleMouseInput(static_cast< WORD >(p.x), 
                             static_cast< WORD >(p.y), msg);
            return 0;

        // Handle keyboard messages.
        case WM_KEYUP:
        case WM_KEYDOWN:
            HandleKeyboardInput(arg1);
            return 0;

        // Handle the OS closing message
        case WM_CLOSE:
            isRunning = false;
            return 0;
    }

    return ::DefWindowProc(hwnd, msg, arg1, arg2);
}

LRESULT CALLBACK Aggrotech::Window::RemoteWndProc(HWND hwnd, UINT msg, WPARAM arg1, LPARAM arg2)
{
    static Window *w;

    // First message that is received needs to be specially handled. 
    // The Window pointer is passed in to be used for all other messages.
    if (msg == WM_NCCREATE)
    {
        w = reinterpret_cast< Window* >((((LPCREATESTRUCT)arg2)->lpCreateParams));
        ::SetWindowLongPtr(hwnd, GWL_USERDATA, reinterpret_cast< LONG >(w));
        return ::DefWindowProc(hwnd, msg, arg1, arg2);
    }

    // All other messages, let the window handle it.
    w = reinterpret_cast< Window *>(::GetWindowLongPtr(hwnd, GWL_USERDATA));

    return w->WindowProcedure(hwnd, msg, arg1, arg2);
}

bool Aggrotech::Window::MakeWindow(int x, int y, int width, int height)
{
    // Convert the title string to a Win32 usable form
    LPCTSTR windowTitle = (LPCTSTR)title.c_str();

    window = ::CreateWindow(WindowClassName,
                            windowTitle,
                            WS_OVERLAPPEDWINDOW,
                            x,
                            y,
                            width,
                            height,
                            NULL,
                            NULL,
                            GetModuleHandle(NULL),
                            this);

    return window != NULL;
}

bool Aggrotech::Window::MakeWindowClass()
{
    WNDCLASS wc = { 0 };

    wc.style           = CS_CLASSDC;
    wc.lpfnWndProc     = RemoteWndProc;
    wc.cbClsExtra      = 0;
    wc.cbWndExtra      = 0;
    wc.hInstance       = GetModuleHandle(NULL);
    wc.hIcon           = NULL;
    wc.hCursor         = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground   = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName    = NULL;
    wc.lpszClassName   = WindowClassName;

    return ::RegisterClass(&wc) != 0;
}