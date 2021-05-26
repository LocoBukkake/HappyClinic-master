#include "pch.h"
#include "ExpertsList.h"
#if __has_include("ExpertsList.g.cpp")
#include "ExpertsList.g.cpp"
#endif

#include "FileSystemHelper.h"
#include "SystemDatabase.h"
#include "Expert.h"
#include "Question.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::HappyClinic::implementation
{
   ExpertsList::ExpertsList()
   {
      InitializeComponent();
   }

   int32_t ExpertsList::MyProperty()
   {
      throw hresult_not_implemented();
   }

   void ExpertsList::MyProperty(int32_t /* value */)
   {
      throw hresult_not_implemented();
   }

   winrt::Windows::Foundation::IAsyncAction ExpertsList::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs e)
   {
      SystemDatabase allUsers;
      co_await FileSystemHelper::GetAllNotAdminUsers(allUsers);

      for (Expert expert : allUsers.experts)
      {
         StackPanel panel;

         TextBlock expertNameBlock;
         expertNameBlock.HorizontalAlignment(HorizontalAlignment::Left);
         expertNameBlock.Text(expert.fullName);
         expertNameBlock.FontSize(18);
         Thickness blockThickness;
         blockThickness.Top = 10;
         blockThickness.Bottom = 10;
         blockThickness.Left = 10;
         blockThickness.Right = 10;
         expertNameBlock.Margin(blockThickness);

         panel.Children().Append(expertNameBlock);

         ListView questionsView;
         Thickness viewThickness;
         viewThickness.Left = 10;
         viewThickness.Top = 10;
         viewThickness.Right = 10;
         viewThickness.Bottom = 10;
         questionsView.Margin(viewThickness);

         for (Question question : expert.questions)
         {
            TextBlock questionBlock;
            questionBlock.HorizontalAlignment(HorizontalAlignment::Left);
            questionBlock.Text(question.text);

            Thickness textBlockThickness;
            textBlockThickness.Left = 10;
            textBlockThickness.Top = 0;
            textBlockThickness.Right = 10;
            textBlockThickness.Bottom = 0;
            questionBlock.Margin(textBlockThickness);

            questionsView.Items().Append(questionBlock);
         }

         panel.Children().Append(questionsView);
         experts().Items().Append(panel);
      }

      co_return;
   }

   void ExpertsList::homeButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
   {
      Frame().Navigate(xaml_typename<HappyClinic::DoctorMainPage>());
   }
}
