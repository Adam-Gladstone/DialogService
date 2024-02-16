#pragma once

#include "MessageBox.g.h"

namespace winrt::DialogServiceWRC::implementation
{
    struct MessageBox : MessageBoxT<MessageBox>
    {
        MessageBox()
        {
        }

        winrt::hstring ImageSource();
        void ImageSource(winrt::hstring const& value);

        winrt::hstring MessageText();
        void MessageText(winrt::hstring const& value);

    private:
        winrt::hstring m_messageText;
        winrt::hstring m_imageSource;

    };
}

namespace winrt::DialogServiceWRC::factory_implementation
{
    struct MessageBox : MessageBoxT<MessageBox, implementation::MessageBox>
    {
    };
}
