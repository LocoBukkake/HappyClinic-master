#include "pch.h"
#include "Register.h"
#if __has_include("Register.g.cpp")
#include "Register.g.cpp"
#endif

#include "FilesystemHelper.h"
#include "Positions.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::HappyClinic::implementation
{
   Register::Register()
   {
      InitializeComponent();
   }

   int32_t Register::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void Register::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   IAsyncAction Register::registerSubmitButton_Click(
      winrt::Windows::Foundation::IInspectable const& sender,
      winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      winrt::hstring login = loginTextBox().Text();
      winrt::hstring password = passwordBox().Password();
      winrt::hstring fullName = fullNameTextBox().Text();
      winrt::hstring birthDate = birthDateTextBox().Text();

      // Если хотя бы одно поле не заполнено, выводим сообщение об ошибке и прекращаем обработку события.
      if (login.empty()
         || password.empty()
         || fullName.empty()
         || birthDate.empty())
      {
         registerResultTextBlock().Text(L"Все поля обязательны для заполнения!");
         co_return;
      }

      if (co_await FileSystemHelper::DoesUserExist(login))
      {
         registerResultTextBlock().Text(L"Администратор с таким логином уже существует! Пожалуйста, выберите другой логин.");
         co_return;
      }

      registerResultTextBlock().Text(L"");
      co_await FileSystemHelper::AddOrUpdateUser(login, password, fullName, birthDate, Positions::Administrator);
      co_await FileSystemHelper::AddCurrentUser(login);

      Frame().Navigate(xaml_typename<HappyClinic::UsersList>());
   }
}
