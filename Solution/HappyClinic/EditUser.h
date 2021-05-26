#pragma once

#include "EditUser.g.h"

namespace winrt::HappyClinic::implementation
{
    struct EditUser : EditUserT<EditUser>
    {
        EditUser();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        winrt::Windows::Foundation::IAsyncAction OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e);
        
        winrt::Windows::Foundation::IAsyncAction editSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        
        winrt::Windows::Foundation::IAsyncAction deleteSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::HappyClinic::factory_implementation
{
    struct EditUser : EditUserT<EditUser, implementation::EditUser>
    {
    };
}
