#pragma once

#include <string>
#include <vector>
#include <utility>

#include "MainPage.g.h"

#include "Settings.h"
#include "MainViewModel.h"

namespace winrt::DialogServiceWinUI::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        winrt::DialogServiceWinUI::MainViewModel ViewModel();

        winrt::DialogServiceWinUI::Settings ApplicationSettings();

        double NavViewCompactModeThresholdWidth();

        void ContentFrame_NavigationFailed(
            Windows::Foundation::IInspectable const& /* sender */,
            Microsoft::UI::Xaml::Navigation::NavigationFailedEventArgs const& args
        );

        void NavView_Loaded(
            Windows::Foundation::IInspectable const& /* sender */,
            Microsoft::UI::Xaml::RoutedEventArgs const& /* args */
        );

        void NavView_ItemInvoked(
            Windows::Foundation::IInspectable const& /* sender */,
            Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args
        );

        // NavView_SelectionChanged is not used in this example, but is shown for completeness.
        // You'll typically handle either ItemInvoked or SelectionChanged to perform navigation,
        // but not both.
        void NavView_SelectionChanged(
            Microsoft::UI::Xaml::Controls::NavigationView const& /* sender */,
            Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args
        );

        void NavView_Navigate(
            std::wstring navItemTag,
            Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo
        );

        void NavView_BackRequested(
            Microsoft::UI::Xaml::Controls::NavigationView const& /* sender */,
            Microsoft::UI::Xaml::Controls::NavigationViewBackRequestedEventArgs const& /* args */
        );

        void On_Navigated(
            Windows::Foundation::IInspectable const& /* sender */,
            Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& args
        );

        void CoreDispatcher_AcceleratorKeyActivated(
            Windows::UI::Core::CoreDispatcher const& /* sender */,
            Windows::UI::Core::AcceleratorKeyEventArgs const& args
        );

        void CoreWindow_PointerPressed(
            Windows::UI::Core::CoreWindow const& /* sender */,
            Windows::UI::Core::PointerEventArgs const& args
        );

        void System_BackRequested(
            Windows::Foundation::IInspectable const& /* sender */,
            Windows::UI::Core::BackRequestedEventArgs const& args
        );
        
        bool TryGoBack();

        void ToggleButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e
        );

    private:
        DialogServiceWinUI::MainViewModel m_mainViewModel{ nullptr };

        DialogServiceWinUI::Settings m_settings{ nullptr };

        // Vector of std::pair holding the Navigation Tag and the relative Navigation Page.
        std::vector<std::pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>> m_pages;

        void ApplyTheme();
    };
}

namespace winrt::DialogServiceWinUI::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
