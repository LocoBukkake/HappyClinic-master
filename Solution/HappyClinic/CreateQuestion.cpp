#include "pch.h"
#include "CreateQuestion.h"
#if __has_include("CreateQuestion.g.cpp")
#include "CreateQuestion.g.cpp"
#endif

#include "Combaseapi.h"
#include "FileSystemHelper.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::HappyClinic::implementation
{
   CreateQuestion::CreateQuestion()
   {
      InitializeComponent();
   }

   int32_t CreateQuestion::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void CreateQuestion::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction CreateQuestion::addQuestionSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {

      winrt::hstring question = questionTextBox().Text();

      if (question.empty())
      {
         addQuestionResultTextBlock().Text(L"Пожалуйста, введите текст вопроса!");
         co_return;
      }

      GUID guid;
      CoCreateGuid(&guid);
      winrt::hstring questionID = L"q" + winrt::to_hstring((unsigned int)guid.Data1);

      co_await FileSystemHelper::AddQuestion(questionID, question);

      Frame().Navigate(xaml_typename<HappyClinic::Questions>());
   }

}
