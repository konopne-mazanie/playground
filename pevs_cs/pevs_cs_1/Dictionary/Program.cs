using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Dictionary
{
    enum Menu
    {
        Show = 1,
        Add = 2,
        Edit = 3,
        Delete = 4,
        Exit = 5
    }
    class Program
    {
        public const string uri = "http://mvi.mechatronika.cool/sites/default/files/berces.html";
        static void Main(string[] args)
        {
            var records = new WebClient().DownloadString(uri).Split('.').Where(x => !String.IsNullOrEmpty(x.Trim()))
                .Select(x => new Record() { Sentence = x.Trim(), Id = Record.ids++, Author = "undefined" }).ToList();
            while (true)
            {
                Console.WriteLine("Select Option:");
                foreach (var option in Enum.GetValues(typeof(Menu))) Console.WriteLine(((int)option).ToString() + " : " + option);
                int pressed = 0;
                try
                {
                    pressed = Int32.Parse(Console.ReadKey().KeyChar.ToString());
                    Console.WriteLine();
                    if (!((pressed > 0) && (pressed < 6))) throw new Exception();
                }
                catch (Exception e)
                {
                    Console.WriteLine("Invalid choice");
                    continue;
                }
                typeof(Program).GetMethod(((Menu)pressed).ToString()).Invoke(null, new Object[] { records }); //sranda musi byt
            }
        }

        public static void Exit(List<Record> records)
        {
            Console.WriteLine("Bye...");
            Environment.Exit(0);
        }
        public static void Show(List<Record> records)
        {
            Console.WriteLine("*** SHOW ***");
            foreach (var record in records)
            {
                Console.WriteLine("ID: " + record.Id.ToString());
                Console.WriteLine("Author: " + record.Author);
                Console.WriteLine("Sentence: " + record.Sentence);
                Console.WriteLine();
            }
        }

        public static void Add(List<Record> records)
        {
            Console.WriteLine("*** ADD ***");
            Console.WriteLine("Author: ");
            var author = Console.ReadLine();
            Console.WriteLine("Sentence: ");
            var sentence = Console.ReadLine();
            if (String.IsNullOrEmpty(sentence))
            {
                Console.WriteLine("ERROR: Empty Input");
                return;
            }
            author = String.IsNullOrEmpty(author) ? "undefined" : author;
            records.Add(new Record() { Id = Record.ids++, Author = author, Sentence = sentence });
        }

        public static void Edit(List<Record> records)
        {
            Console.WriteLine("*** EDIT ***");
            var record = getRecord(records);
            if (record is null)
            {
                Console.WriteLine("No such record");
                return;
            }
            Console.WriteLine("Current value: ");
            Console.WriteLine("ID: " + record.Id.ToString());
            Console.WriteLine("Author: " + record.Author);
            Console.WriteLine("Sentence: " + record.Sentence);
            Console.WriteLine("New Author (press enter to leave as is): ");
            var author = Console.ReadLine();
            Console.WriteLine("New Sentence (press enter to leave as is): ");
            var sentence = Console.ReadLine();
            if (!String.IsNullOrEmpty(sentence)) record.Sentence = sentence;
            if (!String.IsNullOrEmpty(author)) record.Author = author;
        }

        public static void Delete(List<Record> records)
        {
            Console.WriteLine("*** DELETE ***");
            var record = getRecord(records);
            if (record is null)
            {
                Console.WriteLine("No such record");
                return;
            }
            records.Remove(record);
        }

        private static Record getRecord(List<Record> records)
        {
            int id = 0; //we know 0 does not exist
            Console.WriteLine("ID: ");
            Int32.TryParse(Console.ReadLine(), out id);
            return(records.FirstOrDefault(x => x.Id == id));
        }
    }
}
