#pragma once

#include "CreateUsers.g.h"

namespace winrt::HappyClinic::implementation
{
   struct CreateUsers : CreateUsersT<CreateUsers>
   {
      CreateUsers();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction registerSubmitButton_Click(
         winrt::Windows::Foundation::IInspectable const& sender,
         winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct CreateUsers : CreateUsersT<CreateUsers, implementation::CreateUsers>
   {
   };
}
