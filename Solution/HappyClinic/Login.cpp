#include "pch.h"
#include "Login.h"
#if __has_include("Login.g.cpp")
#include "Login.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "Positions.h"
#include "User.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
   Login::Login()
   {
      InitializeComponent();
   }

   int32_t Login::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void Login::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction Login::loginSubmitButton_Click(
      winrt::Windows::Foundation::IInspectable const& sender,
      winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {

      winrt::hstring login = loginTextBox().Text();
      winrt::hstring password = passwordBox().Password();

      // Если хотя бы одно поле не заполнено, выводим сообщение об ошибке и прекращаем обработку события.
      if (login.empty() || password.empty())
      {
         loginResultTextBlock().Text(L"Все поля обязательны для заполнения!");
         co_return;
      }

      if (!(co_await FileSystemHelper::DoesUserExist(login)))
      {
         loginResultTextBlock().Text(L"Пользователя с таким логином не существует.");
         co_return;
      }

      if (!(co_await FileSystemHelper::PasswordIsCorrect(login, password)))
      {
         loginResultTextBlock().Text(L"Неверный пароль!");
         co_return;
      }

      loginResultTextBlock().Text(L"");
      co_await FileSystemHelper::AddCurrentUser(login);
      User user;
      bool result = co_await FileSystemHelper::GetCurrentUser(user);

      if (user.position == Positions::Administrator)
      {
         Frame().Navigate(xaml_typename<HappyClinic::UsersList>());
      }

      if (user.position == Positions::Expert)
      {
         Frame().Navigate(xaml_typename<HappyClinic::Questions>());
      }

      if (user.position == Positions::Doctor)
      {
         Frame().Navigate(xaml_typename<HappyClinic::DoctorMainPage>());
      }

      if (user.position == Positions::Patient)
      {
         Frame().Navigate(xaml_typename<HappyClinic::PatientMainPage>());
      }
   }
}
