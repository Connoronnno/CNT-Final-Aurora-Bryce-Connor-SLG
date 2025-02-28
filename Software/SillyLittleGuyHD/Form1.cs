using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SillyLittleGuyHD
{
    public partial class PetMenu : Form
    {
        //Image Selection
        List<Bitmap> SillyLittleGuys = new List<Bitmap>();
        int curImage = 0;

        //Serial Data Control
        public SerialPort port11 = new SerialPort("COM11"); // initilize the serial port class
        public Dictionary<string, string> parsed = null;

        int CheckPortOpenSecond = 2;
        public PetMenu()
        {
            InitializeComponent();

            //set up serial port to match segger's settings
            port11.BaudRate = 115200;
            port11.Parity = Parity.None;
            port11.StopBits = StopBits.One;
            port11.DataBits = 8;
            port11.Handshake = Handshake.None;

            //port11.ReadTimeout = 499;
            //port11.WriteTimeout = 499;

            //open the serial port and wait for data to be recieved
            try
            {
                port11.Open();
            }
            catch
            {
                UI_PetStats_lbx.Items.Add("No Data Provided");
            }
            port11.DataReceived += Port11_DataReceived;

            timer1.Start();

            /// Copilot Prompt: iterate through every file in a folder c#
            /// Asked on 28/02/25
            string folderPath = ".\\SillyLittleGuys";
            if (Directory.Exists(folderPath))
            {
                IEnumerable<string> fileNames = Directory.EnumerateFiles(folderPath);

                foreach (string file in fileNames)
                {
                    //Console.WriteLine(file);
                    SillyLittleGuys.Add((Bitmap)Bitmap.FromFile(file));
                }
                UI_PetPicture_pbx.Image = SillyLittleGuys[curImage];
            }
            
        }

        private void Port11_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadLine();

            parsed = DataParsing(data);
        }

        private Dictionary<string, string> DataParsing(string rawData)
        {
            Dictionary<string, string> parsed = new Dictionary<string, string>();

            string[] seperations = rawData.Split(',');

            foreach(string dataLine in seperations)
            {
                string cleanedData = dataLine.Replace('(', ' ').Replace(')', ' ').Trim();
                string[] values = cleanedData.Split(':');

                parsed.Add(values[0], values[1]);
            }

            return parsed;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(!port11.IsOpen)
            {
                if (--CheckPortOpenSecond <= 0)
                {
                    try
                    {
                        port11.Open();
                    }
                    catch
                    {
                        UI_PetStats_lbx.Items.Clear();
                        UI_PetStats_lbx.Items.Add("No Data Provided");
                    }
                    CheckPortOpenSecond = 2;
                }
                    
            }
            else
            {
                UI_PetStats_lbx.Items.Clear();
                foreach (KeyValuePair<string, string> petData in parsed)
                {
                    UI_PetStats_lbx.Items.Add($"{petData.Key} : {petData.Value}");
                }
            }



        }


        private void UI_NextCycle_btn_Click(object sender, EventArgs e)
        {
            if(++curImage >= SillyLittleGuys.Count)
            {
                curImage = 0;
            }

            UI_PetPicture_pbx.Image = SillyLittleGuys[curImage];
        }

        private void UI_PrevCycle_btn_Click(object sender, EventArgs e)
        {
            if (--curImage < 0)
            {
                curImage = SillyLittleGuys.Count-1;
            }

            UI_PetPicture_pbx.Image = SillyLittleGuys[curImage];
        }
    }
}
