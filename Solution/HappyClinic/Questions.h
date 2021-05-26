#pragma once

#include "Questions.g.h"

namespace winrt::HappyClinic::implementation
{
   struct Questions : QuestionsT<Questions>
   {
      Questions();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e);

      winrt::Windows::Foundation::IAsyncAction questionsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
      
      void addQuestionButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct Questions : QuestionsT<Questions, implementation::Questions>
   {
   };
}
