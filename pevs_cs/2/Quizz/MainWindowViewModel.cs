using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace Quizz
{
    class MainWindowViewModel : INotifyPropertyChanged
    {
        #region view
        public enum QustionOptions
        {
            OptionA,
            OptionB,
            OptionC,
            OptionD
        }

        private string quizzName;
        private int questionCnt;
        private int questionNr;
        private string questionText;
        private string questionOptionA;
        private string questionOptionB;
        private string questionOptionC;
        private string questionOptionD;
        private QustionOptions currentOption;
        public string QuizzName { get => quizzName; set { if (quizzName == value) return; quizzName = value; OnPropertyChange("QuizzName"); } }
        public int QuestionCnt { get => questionCnt; set { if (questionCnt == value) return; questionCnt = value; OnPropertyChange("QuestionCnt"); } }

        public int QuestionNr { get => questionNr; set { if (questionNr == value) return; questionNr = value; OnPropertyChange("QuestionNr"); } }
        public string QuestionText { get => questionText; set { if (questionText == value) return; questionText = value; OnPropertyChange("QuestionText"); } }
        public string QuestionOptionA { get => questionOptionA; set { if (questionOptionA == value) return; questionOptionA = value; OnPropertyChange("QuestionOptionA"); } }
        public string QuestionOptionB { get => questionOptionB; set { if (questionOptionB == value) return; questionOptionB = value; OnPropertyChange("QuestionOptionB"); } }
        public string QuestionOptionC { get => questionOptionC; set { if (questionOptionC == value) return; questionOptionC = value; OnPropertyChange("QuestionOptionC"); } }
        public string QuestionOptionD { get => questionOptionD; set { if (questionOptionD == value) return; questionOptionD = value; OnPropertyChange("QuestionOptionD"); } }
        public QustionOptions CurrentOption { get => currentOption; set { if (currentOption == value) return; currentOption = value; OnPropertyChange("CurrentOption"); } }

        public ICommand clearCommand { get; set; }
        public ICommand loadCommand { get; set; }
        public ICommand nextCommand { get; set; }
        public ICommand previousCommand { get; set; }
        #endregion

        QuizzModel quizz;

        public MainWindowViewModel()
        {
            clearCommand = new RelayCommand(param => clear(), null);
            loadCommand = new RelayCommand(param => loadJSON(), null);
            nextCommand = new RelayCommand(param => switchNext(), null);
            previousCommand = new RelayCommand(param => switchPrev(), null);
        }

        public void setQuestion(int nr)
        {
            QuestionNr = nr + 1;
            QuestionText = quizz.Questions[nr].Text;
            QuestionOptionA = quizz.Questions[nr].Answers[0];
            QuestionOptionB = quizz.Questions[nr].Answers[1];
            QuestionOptionC = quizz.Questions[nr].Answers[2];
            QuestionOptionD = quizz.Questions[nr].Answers[3];
            CurrentOption = (QustionOptions) quizz.Questions[nr].SelectedAnswer;
        }

        public void clear()
        {
            if (quizz == null) return;
            QuizzName = quizz.Name;
            QuestionCnt = quizz.Questions.Length;
            foreach (var question in quizz.Questions) question.SelectedAnswer = 0;
            setQuestion(0);
        }

        public void loadJSON()
        {
            QuizzModel loadedQuizz = null;
            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "JSON File (*.json) | *.json";
            if ((openFileDialog.ShowDialog() == true) && !string.IsNullOrEmpty(openFileDialog.FileName))
                loadedQuizz = QuizzFactory.loadJSON(openFileDialog.FileName);
            if (loadedQuizz == null)
            {
                MessageBox.Show("Unable to load Quizz", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            quizz = loadedQuizz;
            clear();
        }

        public void switchPrev()
        {
            if (quizz == null) return;
            quizz.Questions[QuestionNr - 1].SelectedAnswer = (int) CurrentOption;
            if ((QuestionNr - 2) < 0) return;
            setQuestion(QuestionNr - 2);
        }

        public void switchNext()
        {
            if (quizz == null) return;
            quizz.Questions[QuestionNr - 1].SelectedAnswer = (int) CurrentOption;
            if (QuestionNr == QuestionCnt)
            {
                int correct = 0;
                foreach (var question in quizz.Questions)
                {
                    if (question.SelectedAnswer == question.CorrectAnswer) correct++;
                }
                MessageBox.Show("You answered correctly " + correct + " of " + QuestionCnt + " questions.", "Result", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }
            setQuestion(QuestionNr);
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChange(string propertyName)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
