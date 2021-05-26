#pragma once

#include "SetDiagnosisToPatient.g.h"

namespace winrt::HappyClinic::implementation
{
   struct SetDiagnosisToPatient : SetDiagnosisToPatientT<SetDiagnosisToPatient>
   {
      SetDiagnosisToPatient();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction SetDiagnosisToPatient::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e);

      winrt::Windows::Foundation::IAsyncAction setDiagnosisSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct SetDiagnosisToPatient : SetDiagnosisToPatientT<SetDiagnosisToPatient, implementation::SetDiagnosisToPatient>
   {
   };
}
