#include "pch.h"
#include "EditUser.h"
#if __has_include("EditUser.g.cpp")
#include "EditUser.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "User.h"
#include "Positions.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
   EditUser::EditUser()
   {
      InitializeComponent();
   }

   int32_t EditUser::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void EditUser::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction EditUser::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      User user;
      co_await FileSystemHelper::GetUserToEdit(user);
      loginTextBox().Text(user.login);
      passwordBox().Password(user.password);
      fullNameTextBox().Text(user.fullName);
      birthDateTextBox().Text(user.birthDate);

      if (user.position == Positions::Expert)
      {
         positionComboBox().SelectedIndex(0);
      }

      if (user.position == Positions::Doctor)
      {
         positionComboBox().SelectedIndex(1);
      }

      if (user.position == Positions::Patient)
      {
         positionComboBox().SelectedIndex(2);
      }
   }

   winrt::Windows::Foundation::IAsyncAction EditUser::editSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      User oldUser;
      co_await FileSystemHelper::GetUserToEdit(oldUser);

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
         editResultTextBlock().Text(L"Все поля обязательны для заполнения!");
         co_return;
      }

      winrt::hstring position = positionComboBox().SelectedValue().as<winrt::hstring>();

      if (login != oldUser.login && co_await FileSystemHelper::DoesUserExist(login))
      {
         editResultTextBlock().Text(L"Вы попытались сменить логин, но выбранный логин уже занят другим пользователем. Пожалуйста, выберите другой логин.");
         co_return;
      }

      co_await FileSystemHelper::AddOrUpdateUser(login, password, fullName, birthDate, position);
      Frame().Navigate(xaml_typename<HappyClinic::UsersList>());
   }

   winrt::Windows::Foundation::IAsyncAction EditUser::deleteSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      User oldUser;
      co_await FileSystemHelper::GetUserToEdit(oldUser);
      co_await FileSystemHelper::DeleteUser(oldUser.login);
      Frame().Navigate(xaml_typename<HappyClinic::UsersList>());
   }
}
