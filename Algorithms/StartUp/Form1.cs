using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using System.Globalization;


namespace StartUp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public string GetCPPString()
        {
            string str = "#include \"CommonHeader.h\"\n\n";
            string name = textBox1.Text;

            str += "#ifdef ";
            str += name.ToUpper();
            str += "\n";
            str += "READ_INPUT(" + name.ToUpper() + ")\n\n";

            str += "#include <iostream>\n";
            str += "#include <algorithm>\n";
            str += "#include <string>\n";
            str += "#include <string.h>\n";
            str += "#include <math.h>\n";
            str += "#include <float.h>\n";
            str += "#include <queue>\n";
            str += "#include <map>\n";
            str += "#include <stdio.h>\n\n";

            str += "using namespace std;\n\n";

            str += "#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)\n";
            str += "#define MAXN 1003\n";
            str += "#define INF 0x3f3f3f3f3f3f3f3fL\n";
            str += "typedef long long ll;\n\n";


            str += "void reset()\n";
            str += "{\n";

            str += "}\n\n";

            str += "int main()\n";
            str += "{\n";
            str += "	int T;\n";
            str += "	scanf(\"%d \", &T);\n";
            str += "FOR(t, 0, T)\n";
            str += "{\n";

            str += "}\n";
            str += "	return 0;\n";
            str += "}\n\n";


            str += "#endif\n";

            return str;
        }


        private void CreateButt_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Length <= 0)
                return;

            string path = @"E:\Test_Preparation\Saurabh_Master\Algorithms\src\uva\";
            string path1 = @"E:\Test_Preparation\Saurabh_Master\Algorithms\input\";
            path += textBox1.Text;
            path1 += textBox1.Text;

            path += ".cpp";
            path1 += ".txt";


            try
            {
                // Create the file.
                using (FileStream fs = File.Create(path))
                {
                    Byte[] info = new UTF8Encoding(true).GetBytes(GetCPPString());
                    // Add some information to the file.
                    fs.Write(info, 0, info.Length);
                }
                // Create the file.
                using (FileStream fs1 = File.Create(path1))
                {
                 
                }

                //Process.Start(path);
                //Process.Start(@"E:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe", path1);
            }

            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
         }
    }
}
