#include "pch.h"
#include "PatientMainPage.h"
#if __has_include("PatientMainPage.g.cpp")
#include "PatientMainPage.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "User.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
   PatientMainPage::PatientMainPage()
   {
      InitializeComponent();
   }

   int32_t PatientMainPage::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void PatientMainPage::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction PatientMainPage::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      User user;
      co_await FileSystemHelper::GetCurrentUser(user);
      winrt::hstring diagnosis;
      co_await FileSystemHelper::GetUserDiagnosis(user.login, diagnosis);
      userData().Text(user.fullName + L" (" + user.birthDate + L")\nДиагноз: " + diagnosis);
   }
}
