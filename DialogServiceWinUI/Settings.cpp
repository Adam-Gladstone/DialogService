#include "pch.h"
#include "Settings.h"
#include "Settings.g.cpp"

using namespace winrt;

using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Data;
using namespace Microsoft::UI::Xaml::Media;

namespace winrt::DialogServiceWinUI::implementation
{
    Settings::Settings()
    {
        bool hasSetting = localSettings ? localSettings.Values().HasKey(L"LightTheme") : false;
        LightTheme(hasSetting ? localSettings.Values().Lookup(L"LightTheme").as<bool>() : true);
    }

    bool Settings::LightTheme()
    {
        return m_isLightTheme;
    }

    void Settings::LightTheme(bool value)
    {
        if (m_isLightTheme != value)
        {
            m_isLightTheme = value;

            localSettings.Values().Insert(L"LightTheme", box_value(m_isLightTheme));

            RaisePropertyChanged(L"LightTheme");
        }
    }

    //
    // PropertyChanged handling
    //

    event_token Settings::PropertyChanged(PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    // Unregisters property changed event handler.
    void Settings::PropertyChanged(event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }

    // Triggers property changed notification.
    void Settings::RaisePropertyChanged(hstring const& propertyName)
    {
        m_propertyChanged(*this, PropertyChangedEventArgs(propertyName));
    }
}
