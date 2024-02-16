#pragma once

#include "HomePage.g.h"

namespace winrt::DialogServiceWinUI::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

    private:

    };
}

namespace winrt::DialogServiceWinUI::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
