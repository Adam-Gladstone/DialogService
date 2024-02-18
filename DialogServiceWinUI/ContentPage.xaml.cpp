#include "pch.h"
#include "ContentPage.xaml.h"
#if __has_include("ContentPage.g.cpp")
#include "ContentPage.g.cpp"
#endif

#include "App.xaml.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;

namespace winrt::DialogServiceWinUI::implementation
{
    ContentPage::ContentPage()
    {
        InitializeComponent();
    }

    IAsyncAction ContentPage::MessageBox_Click(IInspectable const& /* sender */, RoutedEventArgs const& /* e */)
    {
        auto title = App::Window().Title();

        // The MessageDialog requires a XamlRoot (for the ContentDialog) so pass the window as a FrameworkElement
        // from which the MessageDialog can get a XamlRoot; an alternative inside a ContentPage is to pass (*this).
        auto root = App::Window().Content().as<winrt::Microsoft::UI::Xaml::FrameworkElement>();

        hstring message{ L"Are you sure you want to do that, Dave?" };

        auto result = co_await DialogServiceWRC::ModalView::MessageDialogAsync(
            winrt::box_value<Windows::Foundation::IInspectable>(root),
            title,
            message,
            DialogServiceWRC::MessageBoxButtonType::YesNoCancel, // Assigned to Primary, Secondary and Close
            DialogServiceWRC::MessageBoxIconType::Stop);

        auto dialogResult = winrt::unbox_value<Microsoft::UI::Xaml::Controls::ContentDialogResult>(result);

        if (dialogResult == Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary)
        {
            CPP_TRACE("The MessageDialog was closed with the primary button.\n");
        }
        else if (dialogResult == Microsoft::UI::Xaml::Controls::ContentDialogResult::Secondary)
        {
            CPP_TRACE("The MessageDialog was closed with the secondary button..\n");
        }

        co_return;
    }
}
