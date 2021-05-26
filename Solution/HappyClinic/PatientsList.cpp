#include "pch.h"
#include "PatientsList.h"
#if __has_include("PatientsList.g.cpp")
#include "PatientsList.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "SystemDatabase.h"
#include "Patient.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::HappyClinic::implementation
{
   PatientsList::PatientsList()
   {
      InitializeComponent();
   }

   int32_t PatientsList::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void PatientsList::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction PatientsList::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      SystemDatabase allUsers;
      co_await FileSystemHelper::GetAllNotAdminUsers(allUsers);

      for (Patient patient : allUsers.patients)
      {
         TextBlock patientTextBlock;
         
         Thickness thickness;
         thickness.Left = 10;
         thickness.Top = 10;
         thickness.Right = 10;
         thickness.Bottom = 10;
         patientTextBlock.Margin(thickness);

         patientTextBlock.Name(patient.login);
         patientTextBlock.Text(patient.fullName + L" (" + patient.birthDate + L")\nДиагноз: " + patient.diagnosis);
         patientsListView().Items().Append(patientTextBlock);
      }
   }

   void PatientsList::homeButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      Frame().Navigate(xaml_typename<HappyClinic::DoctorMainPage>());
   }

   winrt::Windows::Foundation::IAsyncAction PatientsList::patientsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
   {
      winrt::hstring userLogin = e.ClickedItem().as<TextBlock>().Name();
      co_await FileSystemHelper::AddUserToSetDiagnosis(userLogin);
      Frame().Navigate(xaml_typename<HappyClinic::SetDiagnosisToPatient>());
   }
}
