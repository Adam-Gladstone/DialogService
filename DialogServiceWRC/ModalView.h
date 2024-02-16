#pragma once
#include "ModalView.g.h"

namespace winrt::DialogServiceWRC::implementation
{
    struct ModalView : ModalViewT<ModalView>
    {
        ModalView() = default;

        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::IInspectable>
            MessageDialogAsync(
                winrt::Windows::Foundation::IInspectable value,
                hstring title, 
                hstring message
           );
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::IInspectable>
            MessageDialogAsync(
                winrt::Windows::Foundation::IInspectable value,
                hstring title, 
                hstring message, 
                winrt::DialogServiceWRC::MessageBoxButtonType buttons, 
                winrt::DialogServiceWRC::MessageBoxIconType icon
            );

    private:
        static hstring GetImageSource(DialogServiceWRC::MessageBoxIconType icon);
        static void SetDialogButtons(
            winrt::Microsoft::UI::Xaml::Controls::ContentDialog& dialog,
            DialogServiceWRC::MessageBoxButtonType buttons
        );

    };
}
namespace winrt::DialogServiceWRC::factory_implementation
{
    struct ModalView : ModalViewT<ModalView, implementation::ModalView>
    {
    };
}
