#pragma once

#include "Login.g.h"

namespace winrt::HappyClinic::implementation
{
    struct Login : LoginT<Login>
    {
        Login();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        winrt::Windows::Foundation::IAsyncAction loginSubmitButton_Click(
           winrt::Windows::Foundation::IInspectable const& sender,
           winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::HappyClinic::factory_implementation
{
    struct Login : LoginT<Login, implementation::Login>
    {
    };
}
