#pragma once

#include "Register.g.h"

namespace winrt::HappyClinic::implementation
{
   struct Register : RegisterT<Register>
   {
      Register();

      int32_t MyProperty();
      void MyProperty(int32_t value);

      winrt::Windows::Foundation::IAsyncAction registerSubmitButton_Click(
         winrt::Windows::Foundation::IInspectable const& sender,
         winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
   };
}

namespace winrt::HappyClinic::factory_implementation
{
   struct Register : RegisterT<Register, implementation::Register>
   {
   };
}
