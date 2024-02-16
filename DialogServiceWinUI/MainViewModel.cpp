#include "pch.h"
#include "MainViewModel.h"
#include "MainViewModel.g.cpp"

using namespace winrt;
using namespace winrt::Windows::System;
using namespace winrt::Windows::Foundation;

using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Data;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::DialogServiceWinUI::implementation
{
    MainViewModel::MainViewModel()
    {
    }

    // Registers property changed event handler.
    event_token MainViewModel::PropertyChanged(PropertyChangedEventHandler const& value)
    {
        return m_propertyChanged.add(value);
    }

    // Unregisters property changed event handler.
    void MainViewModel::PropertyChanged(event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

    // Triggers property changed notification.
    void MainViewModel::RaisePropertyChanged(hstring const& propertyName)
    {
        m_propertyChanged(*this, PropertyChangedEventArgs(propertyName));
    }
}
