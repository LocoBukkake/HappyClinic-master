#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::loginButton_Click(
       winrt::Windows::Foundation::IInspectable const& sender,
       winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
       Frame().Navigate(xaml_typename<HappyClinic::Login>());
    }

    void MainPage::registerButton_Click(
       winrt::Windows::Foundation::IInspectable const& sender,
       winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
       Frame().Navigate(xaml_typename<HappyClinic::Register>());
    }
}
