#pragma once

#include "User.h"

class Administrator :
   public User
{
public:
   Administrator(winrt::hstring userEmail,
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
