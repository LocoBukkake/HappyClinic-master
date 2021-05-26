#pragma once

#include "User.h"

class Doctor :
   public User
{
public:
   Doctor() {};
   Doctor(winrt::hstring userEmail,
      winrt::hstring userPassword,
      winrt::hstring userFullName,
      winrt::hstring userBirthDate,
      winrt::hstring userPosition)
      : User(userEmail,
         userPassword,
         userFullName,
         userBirthDate,
         userPosition)
   {}
};
