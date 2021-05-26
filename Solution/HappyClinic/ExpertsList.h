#pragma once

#include "ExpertsList.g.h"

namespace winrt::HappyClinic::implementation
{
   struct ExpertsList : ExpertsListT<ExpertsList>
   {
      ExpertsList();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e);
      
      void homeButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct ExpertsList : ExpertsListT<ExpertsList, implementation::ExpertsList>
   {
   };
}
