#include "pch.h"
#include "MessageBox.xaml.h"
#if __has_include("MessageBox.g.cpp")
#include "MessageBox.g.cpp"
#endif

namespace winrt::DialogServiceWRC::implementation
{
    winrt::hstring MessageBox::MessageText()
    {
        return m_messageText;
    }
    void MessageBox::MessageText(winrt::hstring const& value)
    {
        m_messageText = value;
    }

    winrt::hstring MessageBox::ImageSource()
    {
        return m_imageSource;
    }
    void MessageBox::ImageSource(winrt::hstring const& value)
    {
        m_imageSource = value;
    }

}
