#pragma once

#include "WindowsIncludes.h"
#include <string>

namespace Aggrotech
{
    class Window {
    public:

        /**
         * \brief Determines the "true" window dimensions according to the 
         *        operating system.
         *
         * @param x         window's starting x coordinate
         * @param y         window's starting y coordinate
         * @param width     window's width
         * @param height    window's height
         *
         * @return          true if successful; false if no dimensions are found
         */
        static bool DetermineWindowDimensions(int &x, int &y, int &width, int &height);

        /**
         * \brief Creates a new window with the specified title, width, height, 
         *        and the initial showing state.
         *
         * <strong>Note:</strong> Call the <code>DetermineWindowDimensions</code> 
         * method first to obtain the true dimensions of the window from the 
         * operating system, and then invoke this constructor.
         *
         * @param title     title displayed on the window
         * @param x         starting x location of the window
         * @param y         starting y location of the window
         * @param width     width of the window
         * @param height    height of the window
         * @param nCmdShow  initial showing state (given by WinMain)
         */
        Window(const std::string &title, int x, int y, int width, int height, char *args, int nCmdShow);

        /**
         * \brief Destroys all components used by the window.
         */
        ~Window();

        /**
         * \brief Depending on the argument <code>show</code>, will either display 
         *        the window if true, or hide it otherwise. Returns success state.
         *
         * @param show      true to show, false to hide
         * @return          true if successful; false otherwise
         */
        bool Show(bool show);

        /**
         * \brief Brings the window to the foreground so that its the active 
         *        window. 
         *
         * @return true if successful; false otherwise
         */
        bool BringToForeground();

        /**
         * Starts the event loop, regularly checking for messages from the operating system. Whenever there
         * are no events to handle, the game is given time to perform it's own duties.
         *
         * @return the result of the last event
         */
        int Run();

        /**
         * Returns the low-level device handle to the window.
         *
         * @return the handle to the window
         */
        HWND GetWindowHandle() const;

        /**
         * Returns the width of the window.
         */
        int GetWidth() const;

        /**
         * Returns the height of the window.
         */
        int GetHeight() const;

    private:

        /** Name of the Window Class. This must be a unique identifier. */
        static const LPCTSTR WindowClassName;

        /**
         * A "dummy" window procedure that connects the real event handler, <code>WindowProcedure</code>, 
         * with the operating system. This function overcomes some problems with Win32 event handling and C++.
         *
         * @param hwnd  the window receiving the event
         * @param msg   the event
         * @param arg1  argument of the event
         * @param arg2  argument of the event
         * @return      the result of the handled event
         */
        static LRESULT CALLBACK RemoteWndProc(HWND hwnd, UINT msg, WPARAM arg1, LPARAM arg2);

        /**
         * Alerts the keyboard controller that a key state has been changed.
         *
         * @param key       the changed key
         */
        void HandleKeyboardInput(WPARAM key);

        /**
         * Alerts the mouse controller that the mouse state has changed. The possible states are:
         * <ul>
         *   <li>the mouse cursor has changed it's location</li>
         *   <li>a mouse button has been pressed</li>
         *   <li>a mouse button has been released</li>
         *   <li>the mousewheel has been scrolled</li>
         * </ul>
         *
         * @param x     horizontal position of the mouse at state change
         * @param y     vertical position of the mouse at state change
         * @param type  the state change
         */
        void HandleMouseInput(WORD x, WORD y, UINT type);

        /**
         * Cleans up any resources that the window has taken up, and shuts down any
         * associated components.
         *
         * <strong>Note:</strong> the destructor calls this function. It should not be 
         * called directly.
         */
        void Shutdown();

        /**
         * Deals with the events that the operating system sends to the window. The events deal with 
         * creating the window, closing the window, and keyboard &amp; mouse state changes.
         *
         * @param hwnd  the window receiving the event
         * @param msg   the event
         * @param arg1  argument of the event
         * @param arg2  argument of the event
         * @return      the result of the handled event
         */
        LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM arg1, LPARAM arg2);

        /**
         * Creates a new window. It is expected that the <code>DetermineWindowDimensions</code> function
         * is called beforehand to let the operating system choose proper dimensions before the window is
         * created.
         *
         * @return true if successful; false if window creation failed
         */
        bool MakeWindow(int x, int y, int width, int height);

        /**
         * Creates a new Window Class and returns true if succeeded.
         *
         * @return true if succeeded, false otherwise
         */
        bool MakeWindowClass();

        /** Internal window handle. */
        HWND window;

        /** Width of the window. This may not be the requested width depending on the OS. */
        int width;

        /** Height of the window. This may not be the requested height depending on the OS. */
        int height;

        /** Title of the window. */
        const std::string &title;

        /** State of event handling. If it's false, then the window will proceed to shutdown. */
        bool isRunning;

        char *cmdLine;
    };
}
