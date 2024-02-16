#pragma once

#include "ContentPage.g.h"

namespace winrt::DialogServiceWinUI::implementation
{
    struct ContentPage : ContentPageT<ContentPage>
    {
        ContentPage();

    public:
        Windows::Foundation::IAsyncAction MessageBox_Click(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::DialogServiceWinUI::factory_implementation
{
    struct ContentPage : ContentPageT<ContentPage, implementation::ContentPage>
    {
    };
}
