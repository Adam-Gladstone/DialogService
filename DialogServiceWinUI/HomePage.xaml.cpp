﻿#include "pch.h"
#include "HomePage.xaml.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::DialogServiceWinUI::implementation
{
    HomePage::HomePage()
    {
        InitializeComponent();
    }
}
