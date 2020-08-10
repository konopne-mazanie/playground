using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Quizz
{
    class QuizzFactory
    {
        public static QuizzModel loadJSON(string filename)
        {
            try
            {
                using (StreamReader r = new StreamReader(filename))
                {
                    return(JsonConvert.DeserializeObject<QuizzModel>(r.ReadToEnd()));
                }
            } catch (Exception e) {}
            return null;
        }
    }

    class QuizzModel
    {
        public string Name { get; set; }
        public QuizzQuestionModel[] Questions { get; set; }
    }

    class QuizzQuestionModel
    {
        public string[] Answers { get; set; }
        private int correctAnswer;
        public int CorrectAnswer
        {
            get
            {
                return correctAnswer;
            }
            set
            {
                if ((value < 0) || (value > 3)) throw new Exception();
                correctAnswer = value;
            }
        }
        public string Text { get; set; }
        [JsonIgnore]
        public int SelectedAnswer { get; set; }
    }
}
