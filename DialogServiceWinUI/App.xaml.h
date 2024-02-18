#pragma once

#include "App.xaml.g.h"

#include "Settings.h"

namespace winrt::DialogServiceWinUI::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);
        void OnNavigationFailed(IInspectable const&, Microsoft::UI::Xaml::Navigation::NavigationFailedEventArgs const&);

        static winrt::Microsoft::UI::Xaml::Window Window() { return window; }

        static winrt::DialogServiceWinUI::Settings Settings() { return m_settings; }

    private:
        static winrt::Microsoft::UI::Xaml::Window window;

        static winrt::DialogServiceWinUI::Settings m_settings;

        Microsoft::UI::Xaml::Controls::Frame CreateRootFrame();

    };
}
