#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::DialogServiceWinUI::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();
    }
}


