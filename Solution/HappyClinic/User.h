#pragma once

class User
{
public:
   User() {};
   User(winrt::hstring _login,
      winrt::hstring _password,
      winrt::hstring _fullName,
      winrt::hstring _birthDate,
      winrt::hstring _position)
   {
      login = _login;
      password = _password;
      fullName = _fullName;
      birthDate = _birthDate;
      position = _position;
   }

   winrt::hstring login;
   winrt::hstring password;
   winrt::hstring fullName;
   winrt::hstring birthDate;
   winrt::hstring position;
};
