#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

namespace winrt
{
    using namespace Windows::Foundation;
    using namespace Microsoft::UI::Xaml;
    using namespace Microsoft::UI::Xaml::Controls;
    using namespace Microsoft::UI::Xaml::Navigation;

    using namespace DialogServiceWinUI;
    using namespace DialogServiceWinUI::implementation;
}

winrt::Microsoft::UI::Xaml::Window winrt::App::window{ nullptr };

winrt::DialogServiceWinUI::Settings winrt::App::m_settings{ nullptr };

//
// Initializes the singleton application object.
//
winrt::App::App()
{
    CPP_TRACE("App starting ...\n");

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
    UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
    {
        if (IsDebuggerPresent())
        {
            auto errorMessage = e.Message();
            __debugbreak();
        }
    });
#endif

    m_settings = make<DialogServiceWinUI::implementation::Settings>();
}

//
// Invoked when the application is launched.
//
void winrt::App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
{
    CPP_TRACE("App::OnLaunched()\n");

    window = make<MainWindow>();

    Frame rootFrame = CreateRootFrame();
    if (!rootFrame.Content())
    {
        rootFrame.Navigate(xaml_typename<DialogServiceWinUI::MainPage>());
    }

    window.Activate();
}

//
// Invoked when Navigation to a certain page fails
//
void winrt::App::OnNavigationFailed(IInspectable const&, NavigationFailedEventArgs const& e)
{
    CPP_TRACE("App::OnNavigationFailed()\n");

    throw hresult_error(E_FAIL, hstring(L"Failed to load Page ") + e.SourcePageType().Name);
}

//
winrt::Frame winrt::App::CreateRootFrame()
{
    Frame rootFrame{ nullptr };
    auto content = window.Content();
    if (content)
    {
        rootFrame = content.try_as<Frame>();
    }

    // Don't repeat app initialization when the Window already has content,
    // just ensure that the window is active
    if (!rootFrame)
    {
        // Create a Frame to act as the navigation context
        rootFrame = Frame();

        rootFrame.NavigationFailed({ this, &App::OnNavigationFailed });

        // Place the frame in the current Window
        window.Content(rootFrame);
    }

    return rootFrame;
}
