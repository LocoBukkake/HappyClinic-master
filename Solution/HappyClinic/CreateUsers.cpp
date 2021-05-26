#include "pch.h"
#include "CreateUsers.h"
#if __has_include("CreateUsers.g.cpp")
#include "CreateUsers.g.cpp"
#endif

#include "FileSystemHelper.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
   CreateUsers::CreateUsers()
   {
      InitializeComponent();
   }

   int32_t CreateUsers::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void CreateUsers::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction CreateUsers::registerSubmitButton_Click(
      winrt::Windows::Foundation::IInspectable const& sender,
      winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      winrt::hstring login = loginTextBox().Text();
      winrt::hstring password = passwordBox().Password();
      winrt::hstring fullName = fullNameTextBox().Text();
      winrt::hstring birthDate = birthDateTextBox().Text();
      int positionIndex = positionComboBox().SelectedIndex();

      // Если хотя бы одно поле не заполнено, выводим сообщение об ошибке и прекращаем обработку события.
      if (login.empty()
         || password.empty()
         || fullName.empty()
         || birthDate.empty()
         || positionIndex == -1)
      {
         registerResultTextBlock().Text(L"Все поля обязательны для заполнения!");
         co_return;
      }

      winrt::hstring position = positionComboBox().SelectedValue().as<winrt::hstring>();

      if (co_await FileSystemHelper::DoesUserExist(login))
      {
         registerResultTextBlock().Text(L"Пользователь с таким логином уже существует! Пожалуйста, выберите другой логин.");
         co_return;
      }

      registerResultTextBlock().Text(L"");
      co_await FileSystemHelper::AddOrUpdateUser(login, password, fullName, birthDate, position);

      Frame().Navigate(xaml_typename<HappyClinic::UsersList>());
   }
}
