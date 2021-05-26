#pragma once

#include "User.h"

class Patient :
   public User
{
public:
   Patient() {};
   Patient(winrt::hstring userEmail,
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
   winrt::hstring diagnosis;
};
