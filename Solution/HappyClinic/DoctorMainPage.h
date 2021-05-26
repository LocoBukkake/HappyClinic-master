#pragma once

#include "DoctorMainPage.g.h"

namespace winrt::HappyClinic::implementation
{
   struct DoctorMainPage : DoctorMainPageT<DoctorMainPage>
   {
      DoctorMainPage();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      void goToExpertsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

      void goToPatientsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct DoctorMainPage : DoctorMainPageT<DoctorMainPage, implementation::DoctorMainPage>
   {
   };
}
