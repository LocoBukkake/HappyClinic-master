#pragma once

class Question
{
public:
   Question() {};
   Question(
      winrt::hstring _id,
      winrt::hstring _text)
   {
      id = _id;
      text = _text;
   }

   winrt::hstring id;
   winrt::hstring text;
};
