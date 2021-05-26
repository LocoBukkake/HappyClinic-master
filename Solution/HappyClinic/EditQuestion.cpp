#include "pch.h"
#include "EditQuestion.h"
#if __has_include("EditQuestion.g.cpp")
#include "EditQuestion.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "Question.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::HappyClinic::implementation
{
   EditQuestion::EditQuestion()
   {
      InitializeComponent();
   }

   int32_t EditQuestion::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void EditQuestion::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction EditQuestion::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      Question question;
      co_await FileSystemHelper::GetQuestionToEdit(question);
      questionTextBox().Name(question.id);
      questionTextBox().Text(question.text);

      co_return;
   }

   winrt::Windows::Foundation::IAsyncAction EditQuestion::editQuestionSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      winrt::hstring question = questionTextBox().Text();

      if (question.empty())
      {
         editQuestionResultTextBlock().Text(L"Вопрос не может быть пустой. Пожалуйста, введите вопрос.");
         co_return;
      }

      co_await FileSystemHelper::UpdateQuestion(question);
      Frame().Navigate(xaml_typename<HappyClinic::Questions>());
   }

   winrt::Windows::Foundation::IAsyncAction EditQuestion::deleteQuestionSubmitButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      co_await FileSystemHelper::DeleteQuestion();
      Frame().Navigate(xaml_typename<HappyClinic::Questions>());
   }
}

