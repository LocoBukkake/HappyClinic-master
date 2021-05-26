#pragma once

#include "MainPage.g.h"

namespace winrt::HappyClinic::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void loginButton_Click(
           winrt::Windows::Foundation::IInspectable const& sender,
           winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        void registerButton_Click(
           winrt::Windows::Foundation::IInspectable const& sender,
           winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::HappyClinic::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
