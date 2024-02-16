#pragma once
#include "MainViewModel.g.h"


namespace winrt::DialogServiceWinUI::implementation
{
    struct MainViewModel : MainViewModelT<MainViewModel>
    {
        MainViewModel();

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

    private:
        // Property changed notifications.
        void RaisePropertyChanged(hstring const&);
        event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    };
}
namespace winrt::DialogServiceWinUI::factory_implementation
{
    struct MainViewModel : MainViewModelT<MainViewModel, implementation::MainViewModel>
    {
    };
}
