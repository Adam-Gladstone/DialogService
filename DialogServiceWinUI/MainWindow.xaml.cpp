#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::DialogServiceWinUI::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        winrt::hstring title{ L"Dialog Service" };

        this->Title(title);

        //
        // Requires including '#include <winrt/Microsoft.UI.Windowing.h>'
        // Otherwise you receive the error: https://devblogs.microsoft.com/oldnewthing/20190530-00/?p=102529
        //
        AppWindow().Resize({ 1200, 800 });

        AppWindow().SetIcon(L"Assets/DocumentEdit_40924.ico");
    }
}
