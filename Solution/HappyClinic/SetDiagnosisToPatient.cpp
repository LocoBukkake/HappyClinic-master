#include "pch.h"
#include "SetDiagnosisToPatient.h"
#if __has_include("SetDiagnosisToPatient.g.cpp")
#include "SetDiagnosisToPatient.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "Patient.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
   SetDiagnosisToPatient::SetDiagnosisToPatient()
   {
      InitializeComponent();
   }

   int32_t SetDiagnosisToPatient::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void SetDiagnosisToPatient::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction SetDiagnosisToPatient::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      Patient patient;
      co_await FileSystemHelper::GetUserToSetDiagnosis(patient);

      fullNameTextBlock().Text(patient.fullName);
      birthDateTextBlock().Text(patient.birthDate);
      diagnosisTextBox().Text(patient.diagnosis);
   }

   winrt::Windows::Foundation::IAsyncAction SetDiagnosisToPatient::setDiagnosisSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      winrt::hstring diagnosis = diagnosisTextBox().Text();
      co_await FileSystemHelper::EditDiagnosis(diagnosis);
      Frame().Navigate(xaml_typename<HappyClinic::PatientsList>());
   }
}
