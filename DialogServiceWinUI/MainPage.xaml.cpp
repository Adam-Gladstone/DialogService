//
// MainPage.xaml.cpp
// Implementation of the MainPage class
//

#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

#include "App.xaml.h"

#include "HomePage.xaml.h"
#include "ContentPage.xaml.h"
#include "SettingsPage.xaml.h"


using namespace winrt;
using namespace winrt::Windows::System;
using namespace winrt::Windows::Foundation;

using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;


namespace winrt::DialogServiceWinUI::implementation
{
    MainPage::MainPage()
    {
        m_mainViewModel = make<DialogServiceWinUI::implementation::MainViewModel>();

        m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
            (L"home", winrt::xaml_typename<DialogServiceWinUI::HomePage>()));
        m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
            (L"content", winrt::xaml_typename<DialogServiceWinUI::ContentPage>()));
        m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
            (L"settings", winrt::xaml_typename<DialogServiceWinUI::SettingsPage>()));

        ApplyTheme();
    }

    DialogServiceWinUI::MainViewModel MainPage::ViewModel()
    {
        return m_mainViewModel;
    }

    DialogServiceWinUI::Settings MainPage::ApplicationSettings()
    {
        return m_settings;
    }

    double MainPage::NavViewCompactModeThresholdWidth()
    {
        return NavView().CompactModeThresholdWidth();
    }

    void MainPage::ContentFrame_NavigationFailed(
        Windows::Foundation::IInspectable const& /* sender */,
        Microsoft::UI::Xaml::Navigation::NavigationFailedEventArgs const& /* args */
    )
    {
        //throw winrt::hresult_error(
        //    E_FAIL, winrt::hstring(L"Failed to load Page ") + args.SourcePageType().Name);
    }

    void MainPage::NavView_Loaded(
        Windows::Foundation::IInspectable const& /* sender */,
        Microsoft::UI::Xaml::RoutedEventArgs const& /* args */
    )
    {
        // You can also add items in code.
        /*
        NavView().MenuItems().Append(Microsoft::UI::Xaml::Controls::NavigationViewItemSeparator());
        Microsoft::UI::Xaml::Controls::NavigationViewItem navigationViewItem;
        navigationViewItem.Content(winrt::box_value(L"My content"));
        navigationViewItem.Icon(Microsoft::UI::Xaml::Controls::SymbolIcon(static_cast<Microsoft::UI::Xaml::Controls::Symbol>(0xF1AD)));
        navigationViewItem.Tag(winrt::box_value(L"content"));
        NavView().MenuItems().Append(navigationViewItem);
        m_pages.push_back(
            std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>(
                L"content", winrt::xaml_typename<DialogServiceWinUI::ContentPage>()));
        */

        // Add handler for ContentFrame navigation.
        ContentFrame().Navigated({ this, &MainPage::On_Navigated });

        // NavView doesn't load any page by default, so load home page.
        NavView().SelectedItem(NavView().MenuItems().GetAt(0));
        
        // If navigation occurs on SelectionChanged, then this isn't needed.
        // Because we use ItemInvoked to navigate, we need to call Navigate
        // here to load the home page.
        NavView_Navigate(L"home", Microsoft::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());

        // Listen to the window directly so the app responds
        // to accelerator keys regardless of which element has focus.

        //winrt::Microsoft::UI::Xaml::Window::Current().CoreWindow().Dispatcher().
        //    AcceleratorKeyActivated({ this, &MainPage::CoreDispatcher_AcceleratorKeyActivated });

        //winrt::Microsoft::UI::Xaml::Window::Current().CoreWindow().
        //    PointerPressed({ this, &MainPage::CoreWindow_PointerPressed });

        //Windows::UI::Core::SystemNavigationManager::GetForCurrentView().
        //  BackRequested({ this, &MainPage::System_BackRequested });
    }

    void MainPage::NavView_ItemInvoked(
        Windows::Foundation::IInspectable const& /* sender */,
        Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args
    )
    {
        if (args.IsSettingsInvoked())
        {
            NavView_Navigate(L"settings", args.RecommendedNavigationTransitionInfo());
        }
        else if (args.InvokedItemContainer())
        {
            NavView_Navigate(
                winrt::unbox_value_or<winrt::hstring>(
                    args.InvokedItemContainer().Tag(), L"").c_str(),
                args.RecommendedNavigationTransitionInfo());
        }
    }

    // NavView_SelectionChanged is not used in this example, but is shown for completeness.
    // You will typically handle either ItemInvoked or SelectionChanged to perform navigation,
    // but not both.
    void MainPage::NavView_SelectionChanged(
        Microsoft::UI::Xaml::Controls::NavigationView const& /* sender */,
        Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args
    )
    {
        if (args.IsSettingsSelected())
        {
            NavView_Navigate(L"settings", args.RecommendedNavigationTransitionInfo());
        }
        else if (args.SelectedItemContainer())
        {
            NavView_Navigate(
                winrt::unbox_value_or<winrt::hstring>(
                    args.SelectedItemContainer().Tag(), L"").c_str(),
                args.RecommendedNavigationTransitionInfo());
        }
    }

    void MainPage::NavView_Navigate(
        std::wstring navItemTag,
        Microsoft::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo
    )
    {
        Windows::UI::Xaml::Interop::TypeName pageTypeName;
        if (navItemTag == L"settings")
        {
            pageTypeName = winrt::xaml_typename<DialogServiceWinUI::SettingsPage>();
        }
        else
        {
            for (auto&& eachPage : m_pages)
            {
                if (eachPage.first == navItemTag)
                {
                    pageTypeName = eachPage.second;
                    break;
                }
            }
        }

        // Get the page type before navigation so you can prevent duplicate
        // entries in the backstack.
        Windows::UI::Xaml::Interop::TypeName preNavPageType = ContentFrame().CurrentSourcePageType();

        // Navigate only if the selected page isn't currently loaded.
        if (pageTypeName.Name != L"" && preNavPageType.Name != pageTypeName.Name)
        {
            ContentFrame().Navigate(pageTypeName, transitionInfo);
        }
    }

    void MainPage::NavView_BackRequested(
        Microsoft::UI::Xaml::Controls::NavigationView const& /* sender */,
        Microsoft::UI::Xaml::Controls::NavigationViewBackRequestedEventArgs const& /* args */
    )
    {
        TryGoBack();
    }

    void MainPage::CoreDispatcher_AcceleratorKeyActivated(
        Windows::UI::Core::CoreDispatcher const& /* sender */,
        Windows::UI::Core::AcceleratorKeyEventArgs const& args
    )
    {
        // When Alt+Left are pressed navigate back
        if (args.EventType() == Windows::UI::Core::CoreAcceleratorKeyEventType::SystemKeyDown
            && args.VirtualKey() == Windows::System::VirtualKey::Left
            && args.KeyStatus().IsMenuKeyDown
            && !args.Handled())
        {
            args.Handled(TryGoBack());
        }
    }

    void MainPage::CoreWindow_PointerPressed(
        Windows::UI::Core::CoreWindow const& /* sender */,
        Windows::UI::Core::PointerEventArgs const& args
    )
    {
        // Handle mouse back button.
        if (args.CurrentPoint().Properties().IsXButton1Pressed())
        {
            args.Handled(TryGoBack());
        }
    }

    void MainPage::System_BackRequested(
        Windows::Foundation::IInspectable const& /* sender */,
        Windows::UI::Core::BackRequestedEventArgs const& args
    )
    {
        if (!args.Handled())
        {
            args.Handled(TryGoBack());
        }
    }

    bool MainPage::TryGoBack()
    {
        if (!ContentFrame().CanGoBack())
            return false;

        // Don't go back if the nav pane is overlayed.
        if (NavView().IsPaneOpen() &&
            (NavView().DisplayMode() == Microsoft::UI::Xaml::Controls::NavigationViewDisplayMode::Compact ||
                NavView().DisplayMode() == Microsoft::UI::Xaml::Controls::NavigationViewDisplayMode::Minimal))
            return false;

        ContentFrame().GoBack();
        return true;
    }

    void MainPage::On_Navigated(
        Windows::Foundation::IInspectable const& /* sender */,
        Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& args
    )
    {
        NavView().IsBackEnabled(ContentFrame().CanGoBack());

        if (ContentFrame().SourcePageType().Name ==
            winrt::xaml_typename<DialogServiceWinUI::SettingsPage>().Name)
        {
            // SettingsItem is not part of NavView.MenuItems, and doesn't have a Tag.
            NavView().SelectedItem(NavView().SettingsItem().as<Microsoft::UI::Xaml::Controls::NavigationViewItem>());
            NavView().Header(winrt::box_value(L"Settings"));
        }
        else if (ContentFrame().SourcePageType().Name != L"")
        {
            for (auto&& eachPage : m_pages)
            {
                if (eachPage.second.Name == args.SourcePageType().Name)
                {
                    for (auto&& eachMenuItem : NavView().MenuItems())
                    {
                        auto navigationViewItem =
                            eachMenuItem.try_as<Microsoft::UI::Xaml::Controls::NavigationViewItem>();
                        {
                            if (navigationViewItem)
                            {
                                winrt::hstring hstringValue =
                                    winrt::unbox_value_or<winrt::hstring>(
                                        navigationViewItem.Tag(), L"");
                                if (hstringValue == eachPage.first)
                                {
                                    NavView().SelectedItem(navigationViewItem);
                                    NavView().Header(navigationViewItem.Content());
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    void MainPage::ToggleButton_Click(
        winrt::Windows::Foundation::IInspectable const& /* sender */,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& /* e */
    )
    {
        auto settings = App::Settings();
        settings.LightTheme(!settings.LightTheme());

        ApplyTheme();
    }

    void MainPage::ApplyTheme()
    {
        auto settings = App::Settings();

        Microsoft::UI::Xaml::FrameworkElement const& element = (*this);

        element.RequestedTheme(settings.LightTheme() ? ElementTheme::Light : ElementTheme::Dark);
    }
}
