#pragma once

#include <algorithm>
#include <vector>

#include "winrt/Windows.Storage.h"
#include "winrt/Windows.Storage.Pickers.h"

#include "SystemDatabase.h"
#include "Positions.h"
#include "User.h"
#include "Expert.h"
#include "Doctor.h"
#include "Patient.h"
#include "Question.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Storage;

class FileSystemHelper
{
public:
   // Проверям существует ли файл, хранящий данные пользователя логином, указанном в userLogin.
   inline static IAsyncOperation<bool> DoesUserExist(winrt::hstring userLogin)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageItem userFile = co_await localFolder.TryGetItemAsync(L"users\\" + userLogin + L".txt");

      if (userFile != NULL) {
         co_return true;
      }
      else
      {
         co_return false;
      }
   }
   // Проверям правильный ли пароль ввёл пользователь.
   inline static IAsyncOperation<bool> PasswordIsCorrect(winrt::hstring userLogin, winrt::hstring enteredPassword)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile userFile = co_await localFolder.GetFileAsync(L"users\\" + userLogin + L".txt");
      winrt::hstring userDataString = co_await FileIO::ReadTextAsync(userFile);

      std::vector<winrt::hstring> userData;
      winrt::hstring tempString;

      for (unsigned int letterIndex = 0; letterIndex < std::size(userDataString); letterIndex++)
      {
         wchar_t letters[2] = { userDataString[letterIndex] };
         winrt::hstring letter(letters);

         if (letter == L"\n")
         {
            userData.push_back(tempString);
            tempString = L"";
            continue;
         }

         tempString = tempString + letter;

         if (letterIndex >= (std::size(userDataString) - 1))
         {
            userData.push_back(tempString);
         }
      }

      if (enteredPassword == userData[1])
      {
         co_return true;
      }
      else
      {
         co_return false;
      }
   }
   // Создаём файл для пользователя с указанными атрибутами (логин, пароль, ФИО и т.п.).
   inline static IAsyncAction AddOrUpdateUser(
      winrt::hstring login,
      winrt::hstring password,
      winrt::hstring fullName,
      winrt::hstring birthDate,
      winrt::hstring position
   )
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile userFile = co_await localFolder.CreateFileAsync(
         L"users\\" + login + L".txt",
         CreationCollisionOption::ReplaceExisting);

      co_await FileIO::WriteTextAsync(
         userFile,
         login + L"\n" + password + L"\n" + fullName + L"\n" + birthDate + L"\n" + position);
   }
   // Храним информацию о текущем пользователе системы в специальном файле.
   inline static IAsyncAction AddCurrentUser(winrt::hstring userLogin)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile currentUserLoginFile = co_await localFolder.CreateFileAsync(
         L"settings\\currentUserLogin.txt",
         CreationCollisionOption::ReplaceExisting);
      co_await FileIO::WriteTextAsync(currentUserLoginFile, userLogin);
   }
   // Храним информацию о пользователе, которого собираемся редактировать в специальном файле.
   inline static IAsyncAction AddUserToEdit(winrt::hstring userLogin)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile userToEditFile = co_await localFolder.CreateFileAsync(
         L"settings\\userToEditLogin.txt",
         CreationCollisionOption::ReplaceExisting);
      co_await FileIO::WriteTextAsync(userToEditFile, userLogin);
   }
   // Возвращаем объект текущего пользователя на основании его логина.
   inline static IAsyncOperation<bool> GetCurrentUser(User& user)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile currentUserLoginFile = co_await localFolder.GetFileAsync(L"settings\\currentUserLogin.txt");
      winrt::hstring currentUserLogin = co_await FileIO::ReadTextAsync(currentUserLoginFile);
      IStorageFile userFile = co_await localFolder.GetFileAsync(L"users\\" + currentUserLogin + L".txt");
      winrt::hstring currentUserDataString = co_await FileIO::ReadTextAsync(userFile);

      std::vector<winrt::hstring> userData;
      winrt::hstring tempString;

      for (unsigned int letterIndex = 0; letterIndex < std::size(currentUserDataString); letterIndex++)
      {
         wchar_t letters[2] = { currentUserDataString[letterIndex] };
         winrt::hstring letter(letters);

         if (letter == L"\n")
         {
            userData.push_back(tempString);
            tempString = L"";
            continue;
         }

         tempString = tempString + letter;

         if (letterIndex >= (std::size(currentUserDataString) - 1))
         {
            userData.push_back(tempString);
         }
      }

      User newUser(userData[0], userData[1], userData[2], userData[3], userData[4]);
      user = newUser;
      co_return true;
   }
   // Возвращаем объект пользователя, которого хотим отредактировать на основании его логина.
   inline static IAsyncAction GetUserToEdit(User& user)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile settingsFile = co_await localFolder.GetFileAsync(L"settings\\userToEditLogin.txt");
      winrt::hstring userToEditLogin = co_await FileIO::ReadTextAsync(settingsFile);
      IStorageFile userFile = co_await localFolder.GetFileAsync(L"users\\" + userToEditLogin + L".txt");
      winrt::hstring userToEditDataString = co_await FileIO::ReadTextAsync(userFile);

      std::vector<winrt::hstring> userData;
      winrt::hstring tempString;

      for (unsigned int letterIndex = 0; letterIndex < std::size(userToEditDataString); letterIndex++)
      {
         wchar_t letters[2] = { userToEditDataString[letterIndex] };
         winrt::hstring letter(letters);

         if (letter == L"\n")
         {
            userData.push_back(tempString);
            tempString = L"";
            continue;
         }

         tempString = tempString + letter;

         if (letterIndex >= (std::size(userToEditDataString) - 1))
         {
            userData.push_back(tempString);
         }
      }

      User newUser(userData[0], userData[1], userData[2], userData[3], userData[4]);
      user = newUser;
      co_return;
   }
   // Получаем список все пользователей, кроме администраторов.
   inline static IAsyncAction GetAllNotAdminUsers(SystemDatabase& allUsers)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IVectorView<StorageFolder> foldersList = co_await localFolder.GetFoldersAsync();

      StorageFolder usersFolder = localFolder;

      // Я надеюсь, никто никогда не увидит, что мы получаем вложенную подпапку вот так.
      for (StorageFolder folder : foldersList)
      {
         if (folder.Name() == L"users")
         {
            usersFolder = folder;
            break;
         }
      }

      SystemDatabase database;

      IVectorView<StorageFile> filesList = co_await usersFolder.GetFilesAsync();

      for (StorageFile file : filesList)
      {
         winrt::hstring userDataString = co_await FileIO::ReadTextAsync(file);
         std::vector<winrt::hstring> userData;
         winrt::hstring tempString;

         for (unsigned int letterIndex = 0; letterIndex < std::size(userDataString); letterIndex++)
         {
            wchar_t letters[2] = { userDataString[letterIndex] };
            winrt::hstring letter(letters);

            if (letter == L"\n")
            {
               userData.push_back(tempString);
               tempString = L"";
               continue;
            }

            tempString = tempString + letter;

            if (letterIndex >= (std::size(userDataString) - 1))
            {
               userData.push_back(tempString);
            }
         }

         if (userData[4] == Positions::Expert)
         {
            Expert expert(userData[0], userData[1], userData[2], userData[3], userData[4]);

            // Для каждого эксперта заполняем список его вопросов.

            IVectorView<StorageFolder> rootFoldersList = co_await localFolder.GetFoldersAsync();
            StorageFolder questionsFolder = localFolder;

            for (StorageFolder folder : rootFoldersList)
            {
               if (folder.Name() == L"questions")
               {
                  questionsFolder = folder;
                  break;
               }
            }

            IVectorView<StorageFolder> questionsFoldersList = co_await questionsFolder.GetFoldersAsync();
            StorageFolder expertQuestionsFolder = localFolder;

            for (StorageFolder folder : questionsFoldersList)
            {
               if (folder.Name() == expert.login)
               {
                  expertQuestionsFolder = folder;
                  break;
               }
            }

            IVectorView<StorageFile> questionFilesList = co_await expertQuestionsFolder.GetFilesAsync();

            for (StorageFile file : questionFilesList)
            {
               winrt::hstring questionID = file.DisplayName();
               winrt::hstring questionText = co_await FileIO::ReadTextAsync(file);
               Question question(questionID, questionText);
               expert.questions.push_back(question);
            }

            database.experts.push_back(expert);
            continue;
         }

         if (userData[4] == Positions::Doctor)
         {
            Doctor doctor(userData[0], userData[1], userData[2], userData[3], userData[4]);
            database.doctors.push_back(doctor);
            continue;
         }

         if (userData[4] == Positions::Patient)
         {
            Patient patient(userData[0], userData[1], userData[2], userData[3], userData[4]);

            // Для каждого пациента заполняем диагноз.
            IStorageItem diagnosisFileItem = co_await localFolder.TryGetItemAsync(L"diagnosis\\" + patient.login + L".txt");

            if (diagnosisFileItem != NULL) {

               IStorageFile diagnosisFile = co_await localFolder.GetFileAsync(L"diagnosis\\" + patient.login + L".txt");
               winrt::hstring diagnosisText = co_await FileIO::ReadTextAsync(diagnosisFile);
               patient.diagnosis = diagnosisText;
            }

            database.patients.push_back(patient);
            continue;
         }
      }

      allUsers = database;
      co_return;
   }
   // Удаляем пользователя с указанным логином.
   inline static IAsyncAction DeleteUser(winrt::hstring userLogin)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageItem userFile = co_await localFolder.TryGetItemAsync(L"users\\" + userLogin + L".txt");

      if (userFile == NULL) {
         co_return;
      }

      co_await userFile.DeleteAsync();
   }
   // Добавляем новый вопрос.
   inline static IAsyncAction AddQuestion(winrt::hstring questionID, winrt::hstring question)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile currentUserLoginFile = co_await localFolder.GetFileAsync(L"settings\\currentUserLogin.txt");
      winrt::hstring currentUserLogin = co_await FileIO::ReadTextAsync(currentUserLoginFile);

      IStorageFile questionFile = co_await localFolder.CreateFileAsync(
         L"questions\\" + currentUserLogin + L"\\" + questionID + L".txt",
         CreationCollisionOption::ReplaceExisting);

      co_await FileIO::WriteTextAsync(questionFile, question);
   }
   // Обновляем информацию о редактируемом вопросе.
   inline static IAsyncAction UpdateQuestion(winrt::hstring question)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile currentUserLoginFile = co_await localFolder.GetFileAsync(L"settings\\currentUserLogin.txt");
      winrt::hstring currentUserLogin = co_await FileIO::ReadTextAsync(currentUserLoginFile);

      IStorageFile questionToEditFile = co_await localFolder.GetFileAsync(L"settings\\questionToEditID.txt");
      winrt::hstring questionToEditID = co_await FileIO::ReadTextAsync(questionToEditFile);

      IStorageFile questionFile = co_await localFolder.CreateFileAsync(
         L"questions\\" + currentUserLogin + L"\\" + questionToEditID + L".txt",
         CreationCollisionOption::ReplaceExisting);

      co_await FileIO::WriteTextAsync(questionFile, question);
   }
   // Добавляем ID вопроса, который собираеся редактировать в специальный файл.
   inline static IAsyncAction AddQuestionToEdit(winrt::hstring questionID)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile questionToEditFile = co_await localFolder.CreateFileAsync(
         L"settings\\questionToEditID.txt",
         CreationCollisionOption::ReplaceExisting);
      co_await FileIO::WriteTextAsync(questionToEditFile, questionID);
   }
   // Возвращаем все вопросы текущего пользователя.
   inline static IAsyncAction GetQuestions(std::vector<Question>& questions)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile currentUserLoginFile = co_await localFolder.GetFileAsync(L"settings\\currentUserLogin.txt");
      winrt::hstring currentUserLogin = co_await FileIO::ReadTextAsync(currentUserLoginFile);

      IVectorView<StorageFolder> rootFoldersList = co_await localFolder.GetFoldersAsync();
      StorageFolder questionsFolder = localFolder;

      for (StorageFolder folder : rootFoldersList)
      {
         if (folder.Name() == L"questions")
         {
            questionsFolder = folder;
            break;
         }
      }

      IVectorView<StorageFolder> questionsFoldersList = co_await questionsFolder.GetFoldersAsync();
      StorageFolder expertQuestionsFolder = localFolder;

      for (StorageFolder folder : questionsFoldersList)
      {
         if (folder.Name() == currentUserLogin)
         {
            expertQuestionsFolder = folder;
            break;
         }
      }

      IVectorView<StorageFile> questionFilesList = co_await expertQuestionsFolder.GetFilesAsync();

      for (StorageFile file : questionFilesList)
      {
         winrt::hstring questionID = file.DisplayName();
         winrt::hstring questionText = co_await FileIO::ReadTextAsync(file);
         Question question(questionID, questionText);
         questions.push_back(question);
      }

      co_return;
   }
   // Получаем текст текущего вопроса на редактирование.
   inline static IAsyncAction GetQuestionToEdit(Question& question)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile currentUserLoginFile = co_await localFolder.GetFileAsync(L"settings\\currentUserLogin.txt");
      winrt::hstring currentUserLogin = co_await FileIO::ReadTextAsync(currentUserLoginFile);

      IStorageFile questionToEditFile = co_await localFolder.GetFileAsync(L"settings\\questionToEditID.txt");
      winrt::hstring questionToEditID = co_await FileIO::ReadTextAsync(questionToEditFile);

      IStorageFile questionFile = co_await localFolder.GetFileAsync(L"questions\\" + currentUserLogin + L"\\" + questionToEditID + L".txt");
      winrt::hstring questionText = co_await FileIO::ReadTextAsync(questionFile);
      Question gotQuestion(questionToEditID, questionText);
      question = gotQuestion;

      co_return;
   }
   // Удаляем вопрос с указанным ID.
   inline static IAsyncAction DeleteQuestion()
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile currentUserLoginFile = co_await localFolder.GetFileAsync(L"settings\\currentUserLogin.txt");
      winrt::hstring currentUserLogin = co_await FileIO::ReadTextAsync(currentUserLoginFile);

      IStorageFile questionToEditFile = co_await localFolder.GetFileAsync(L"settings\\questionToEditID.txt");
      winrt::hstring questionToEditID = co_await FileIO::ReadTextAsync(questionToEditFile);

      IStorageItem questionFile = co_await localFolder.TryGetItemAsync(
         L"questions\\" + currentUserLogin + L"\\" + questionToEditID + L".txt");

      if (questionFile == NULL) {
         co_return;
      }

      co_await questionFile.DeleteAsync();
   }
   // Добавляем логин пациента, которому хотим поставить диагноз в специальный файл.
   inline static IAsyncAction AddUserToSetDiagnosis(winrt::hstring userLogin)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile patientToSetDiagnosisFile = co_await localFolder.CreateFileAsync(
         L"settings\\patientToSetDiagnosisLogin.txt",
         CreationCollisionOption::ReplaceExisting);
      co_await FileIO::WriteTextAsync(patientToSetDiagnosisFile, userLogin);
   }
   // Получаем объект пациента, которому хотим поставить диагноз.
   inline static IAsyncAction GetUserToSetDiagnosis(Patient& patient)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile userToSetDiagnosisFile = co_await localFolder.GetFileAsync(L"settings\\patientToSetDiagnosisLogin.txt");
      winrt::hstring userToSetDiagnosisLogin = co_await FileIO::ReadTextAsync(userToSetDiagnosisFile);
      IStorageFile userFile = co_await localFolder.GetFileAsync(L"users\\" + userToSetDiagnosisLogin + L".txt");
      winrt::hstring userDataString = co_await FileIO::ReadTextAsync(userFile);

      std::vector<winrt::hstring> userData;
      winrt::hstring tempString;

      for (unsigned int letterIndex = 0; letterIndex < std::size(userDataString); letterIndex++)
      {
         wchar_t letters[2] = { userDataString[letterIndex] };
         winrt::hstring letter(letters);

         if (letter == L"\n")
         {
            userData.push_back(tempString);
            tempString = L"";
            continue;
         }

         tempString = tempString + letter;

         if (letterIndex >= (std::size(userDataString) - 1))
         {
            userData.push_back(tempString);
         }
      }

      Patient newPatient(userData[0], userData[1], userData[2], userData[3], userData[4]);
      IStorageItem diagnosisFileItem = co_await localFolder.TryGetItemAsync(L"diagnosis\\" + newPatient.login + L".txt");

      if (diagnosisFileItem != NULL) {
         IStorageFile diagnosisFile = co_await localFolder.GetFileAsync(L"diagnosis\\" + newPatient.login + L".txt");
         winrt::hstring diagnosisText = co_await FileIO::ReadTextAsync(diagnosisFile);
         newPatient.diagnosis = diagnosisText;
      }

      patient = newPatient;
   }
   // Ввести новый диагноз пациента.
   inline static IAsyncAction EditDiagnosis(winrt::hstring diagnosis)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageFile userToSetDiagnosisFile = co_await localFolder.GetFileAsync(L"settings\\patientToSetDiagnosisLogin.txt");
      winrt::hstring userToSetDiagnosisLogin = co_await FileIO::ReadTextAsync(userToSetDiagnosisFile);

      IStorageFile patientDiagnosisFile = co_await localFolder.CreateFileAsync(
         L"diagnosis\\" + userToSetDiagnosisLogin + L".txt",
         CreationCollisionOption::ReplaceExisting);
      co_await FileIO::WriteTextAsync(patientDiagnosisFile, diagnosis);
   }
   // Возвращаем диагноз пациента по его логину.
   inline static IAsyncAction GetUserDiagnosis(winrt::hstring userLogin, winrt::hstring& diagnosis)
   {
      StorageFolder localFolder = ApplicationData::Current().LocalFolder();
      IStorageItem diagnosisFileItem = co_await localFolder.TryGetItemAsync(L"diagnosis\\" + userLogin + L".txt");

      if (diagnosisFileItem == NULL) {
         diagnosis = L"";
         co_return;
      }

      IStorageFile diagnosisFile = co_await localFolder.GetFileAsync(L"diagnosis\\" + userLogin + L".txt");
      winrt::hstring diagnosisText = co_await FileIO::ReadTextAsync(diagnosisFile);
      diagnosis = diagnosisText;
      co_return;
   }
};
