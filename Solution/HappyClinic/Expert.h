#pragma once

#include <vector>
#include "User.h"
#include "Question.h"

class Expert :
   public User
{
public:
   Expert() {};
   Expert(winrt::hstring userEmail,
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
   std::vector<Question> questions;
};
