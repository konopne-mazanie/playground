using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dictionary
{
    class Record
    {
        public static int ids = 1;
        public int Id { get; set; }
        public String Sentence { get; set; }
        public String Author { get; set; }
    }
}
