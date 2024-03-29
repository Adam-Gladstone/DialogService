#include "pch.h"
#include "ModalView.h"
#include "ModalView.g.cpp"

using namespace winrt;
using namespace winrt::Windows::System;
using namespace winrt::Windows::Foundation;

using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Data;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media::Imaging;

using namespace DialogServiceWRC;

namespace {

    hstring GetImageSource(MessageBoxIconType icon)
    {
        hstring source{ L"ms-appx:///Assets/" };

        switch (icon)
        {
        case MessageBoxIconType::Hand:
            return source + hstring(L"hand.png");
        case MessageBoxIconType::Error:
            return source + hstring(L"error.png");
        case MessageBoxIconType::Stop:
            return source + hstring(L"stop.png");
        case MessageBoxIconType::Question:
            return source + hstring(L"question.png");
        case MessageBoxIconType::Exclamation:
            return source + hstring(L"exclamation.png");
        case MessageBoxIconType::Warning:
            return source + hstring(L"warning.png");
        case MessageBoxIconType::Information:
            return source + hstring(L"information.png");
        case MessageBoxIconType::Asterisk:
            return source + hstring(L"asterisk.png");
        default:
            return hstring(L"");
        }
    }

    void CreateMessageDialog(hstring const& message, MessageBoxIconType icon, ContentDialog& dialog)
    {
        StackPanel stackPanel{};
        stackPanel.Orientation(Orientation::Horizontal);

        TextBlock textBlock{};
        textBlock.VerticalAlignment(VerticalAlignment::Center);
        textBlock.Margin(ThicknessHelper::FromLengths(10, 0, 0, 0));
        textBlock.Text(message);
        textBlock.TextWrapping(TextWrapping::Wrap);

        ImageIcon imageIcon{};
        imageIcon.HorizontalAlignment(HorizontalAlignment::Left);
        imageIcon.Width(32.0);
        imageIcon.Height(32.0);

        Uri uri{ GetImageSource(icon) };
        BitmapImage bitmapImage{};
        bitmapImage.UriSource(uri);
        imageIcon.Source(bitmapImage);

        stackPanel.Children().Append(imageIcon);
        stackPanel.Children().Append(textBlock);

        dialog.Content(winrt::box_value(stackPanel));
    }

    void SetDialogButtons(MessageBoxButtonType buttons, ContentDialog& dialog)
    {
        if (buttons == MessageBoxButtonType::OK)
        {
            dialog.PrimaryButtonText(L"OK");
        }
        else if (buttons == MessageBoxButtonType::OKCancel)
        {
            dialog.PrimaryButtonText(L"OK");
            dialog.SecondaryButtonText(L"Cancel");
        }
        else if (buttons == MessageBoxButtonType::RetryCancel)
        {
            dialog.PrimaryButtonText(L"Retry");
            dialog.SecondaryButtonText(L"Cancel");
        }
        else if (buttons == MessageBoxButtonType::YesNo)
        {
            dialog.PrimaryButtonText(L"Yes");
            dialog.SecondaryButtonText(L"No");
        }
        else if (buttons == MessageBoxButtonType::YesNoCancel)
        {
            dialog.PrimaryButtonText(L"Yes");
            dialog.SecondaryButtonText(L"No");
            dialog.CloseButtonText(L"Cancel");
        }
        else if (buttons == MessageBoxButtonType::AbortRetryIgnore)
        {
            dialog.PrimaryButtonText(L"Abort");
            dialog.SecondaryButtonText(L"Retry");
            dialog.CloseButtonText(L"Ignore");
        }
        else
        {
            dialog.PrimaryButtonText(L"OK");
        }

        dialog.DefaultButton(ContentDialogButton::Primary);
    }
}

namespace winrt::DialogServiceWRC::implementation
{
    IAsyncOperation<IInspectable> ModalView::MessageDialogAsync(IInspectable value, hstring title, hstring message)
    {
        co_return co_await MessageDialogAsync(value, title, message, MessageBoxButtonType::OK, MessageBoxIconType::Information);
    }

    IAsyncOperation<IInspectable> ModalView::MessageDialogAsync(IInspectable value, hstring title, hstring message, 
        MessageBoxButtonType buttons, MessageBoxIconType icon)
    {
        ContentDialog dialog{};

        auto element = winrt::unbox_value<winrt::Microsoft::UI::Xaml::FrameworkElement>(value);

        dialog.XamlRoot(element.XamlRoot());
        dialog.Title(box_value(title));
        
        CreateMessageDialog(message, icon, dialog);
        SetDialogButtons(buttons, dialog);

        auto result = co_await dialog.ShowAsync();

        co_return winrt::box_value(result);
    }
}
