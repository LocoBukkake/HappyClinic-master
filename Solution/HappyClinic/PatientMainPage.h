#pragma once

#include "PatientMainPage.g.h"

namespace winrt::HappyClinic::implementation
{
   struct PatientMainPage : PatientMainPageT<PatientMainPage>
   {
      PatientMainPage();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct PatientMainPage : PatientMainPageT<PatientMainPage, implementation::PatientMainPage>
   {
   };
}
