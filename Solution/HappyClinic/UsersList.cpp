#include "pch.h"
#include "UsersList.h"
#if __has_include("UsersList.g.cpp")
#include "UsersList.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "SystemDatabase.h"
#include "Expert.h"
#include "Doctor.h"
#include "Patient.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::HappyClinic::implementation
{
   UsersList::UsersList()
   {
      InitializeComponent();
   }

   int32_t UsersList::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void UsersList::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   IAsyncAction UsersList::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      SystemDatabase allUsers;
      co_await FileSystemHelper::GetAllNotAdminUsers(allUsers);

      for (Expert user : allUsers.experts)
      {
         TextBlock userTextBlock;
         userTextBlock.Name(user.login);
         userTextBlock.Text(user.fullName + L" (" + user.birthDate + L")");
         expertsListView().Items().Append(userTextBlock);
      }

      for (Doctor user : allUsers.doctors)
      {
         TextBlock userTextBlock;
         userTextBlock.Name(user.login);
         userTextBlock.Text(user.fullName + L" (" + user.birthDate + L")");
         doctorsListView().Items().Append(userTextBlock);
      }

      for (Patient user : allUsers.patients)
      {
         TextBlock userTextBlock;
         userTextBlock.Name(user.login);
         userTextBlock.Text(user.fullName + L" (" + user.birthDate + L")");
         patientsListView().Items().Append(userTextBlock);
      }
   }

   void UsersList::addNewUserButton_Click(
      winrt::Windows::Foundation::IInspectable const& sender,
      winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      Frame().Navigate(xaml_typename<HappyClinic::CreateUsers>());
   }

   IAsyncAction UsersList::expertsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
   {
      winrt::hstring userLogin = e.ClickedItem().as<TextBlock>().Name();
      co_await FileSystemHelper::AddUserToEdit(userLogin);
      Frame().Navigate(xaml_typename<HappyClinic::EditUser>());
   }

   IAsyncAction UsersList::doctorsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
   {
      co_await FileSystemHelper::AddUserToEdit(e.ClickedItem().as<TextBlock>().Name());
      Frame().Navigate(xaml_typename<HappyClinic::EditUser>());
   }

   IAsyncAction UsersList::patientsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
   {
      co_await FileSystemHelper::AddUserToEdit(e.ClickedItem().as<TextBlock>().Name());
      Frame().Navigate(xaml_typename<HappyClinic::EditUser>());
   }
}
