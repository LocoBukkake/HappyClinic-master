#pragma once

#include "UsersList.g.h"

namespace winrt::HappyClinic::implementation
{
   struct UsersList : UsersListT<UsersList>
   {
      UsersList();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e);

      void addNewUserButton_Click(
         winrt::Windows::Foundation::IInspectable const& sender,
         winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

      winrt::Windows::Foundation::IAsyncAction expertsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);

      winrt::Windows::Foundation::IAsyncAction doctorsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);

      winrt::Windows::Foundation::IAsyncAction patientsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct UsersList : UsersListT<UsersList, implementation::UsersList>
   {
   };
}
