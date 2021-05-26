#include "pch.h"
#include "Questions.h"
#if __has_include("Questions.g.cpp")
#include "Questions.g.cpp"
#endif

#include <vector>
#include "FileSystemHelper.h"
#include "Question.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::HappyClinic::implementation
{
   Questions::Questions()
   {
      InitializeComponent();
   }

   int32_t Questions::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void Questions::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction Questions::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      std::vector<Question> questions;
      co_await FileSystemHelper::GetQuestions(questions);

      for (Question question : questions)
      {
         TextBlock questionTextBlock;
         questionTextBlock.Name(question.id);
         questionTextBlock.Text(question.text);
         questionsListView().Items().Append(questionTextBlock);
      }
   }

   void Questions::addQuestionButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      Frame().Navigate(xaml_typename<HappyClinic::CreateQuestion>());
   }

   winrt::Windows::Foundation::IAsyncAction Questions::questionsListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
   {
      winrt::hstring questionID = e.ClickedItem().as<TextBlock>().Name();
      co_await FileSystemHelper::AddQuestionToEdit(questionID);
      Frame().Navigate(xaml_typename<HappyClinic::EditQuestion>());
   }
}
