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
        CPP_TRACE("Message Dialog will be opened.\n");

        hstring title = App::Window().Title();

        auto result = co_await DialogServiceWRC::ModalView::MessageDialogAsync(
            winrt::box_value<Windows::Foundation::IInspectable>(*this),
            title,
            L"The file cannot be found.",
            DialogServiceWRC::MessageBoxButtonType::OK,
            DialogServiceWRC::MessageBoxIconType::Exclamation);

        auto dialogResult = winrt::unbox_value<Microsoft::UI::Xaml::Controls::ContentDialogResult>(result);

        if (dialogResult == Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary)
        {
            CPP_TRACE("Message Dialog was closed with the primary button.\n");
        }
        else
        {
            CPP_TRACE("Message Dialog was cancelled.\n");
        }

        co_return;
    }
}
