#pragma once

#include "CreateQuestion.g.h"

namespace winrt::HappyClinic::implementation
{
   struct CreateQuestion : CreateQuestionT<CreateQuestion>
   {
      CreateQuestion();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction addQuestionSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct CreateQuestion : CreateQuestionT<CreateQuestion, implementation::CreateQuestion>
   {
   };
}
