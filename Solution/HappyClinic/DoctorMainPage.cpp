#include "pch.h"
#include "DoctorMainPage.h"
#if __has_include("DoctorMainPage.g.cpp")
#include "DoctorMainPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
   DoctorMainPage::DoctorMainPage()
   {
      InitializeComponent();
   }

   int32_t DoctorMainPage::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void DoctorMainPage::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   void DoctorMainPage::goToExpertsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      Frame().Navigate(xaml_typename<HappyClinic::ExpertsList>());
   }

   void DoctorMainPage::goToPatientsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      Frame().Navigate(xaml_typename<HappyClinic::PatientsList>());
   }
}

