#pragma once

#include "EditQuestion.g.h"

namespace winrt::HappyClinic::implementation
{
    struct EditQuestion : EditQuestionT<EditQuestion>
    {
        EditQuestion();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        winrt::Windows::Foundation::IAsyncAction OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e);

        winrt::Windows::Foundation::IAsyncAction editQuestionSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        winrt::Windows::Foundation::IAsyncAction deleteQuestionSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::HappyClinic::factory_implementation
{
    struct EditQuestion : EditQuestionT<EditQuestion, implementation::EditQuestion>
    {
    };
}
