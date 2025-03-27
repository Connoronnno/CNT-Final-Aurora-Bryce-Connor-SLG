using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using GMap;
using GMap.NET;
using GMap.NET.WindowsForms;

namespace SillyLittleGuyHD
{
    public partial class PetMenu : Form
    {
        SillyLittleData SLGData = new SillyLittleData("default", "default", 0, 0, 0, 100, 1, 1);

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

            UI_SendData_btn.Click += UI_SendData_btn_Click;
            _usernameBox.TextChanged += _usernameBox_TextChanged;
            _passBox.TextChanged += _usernameBox_TextChanged;
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
                //UI_PetStats_lbx.Items.Add("No Data Provided");
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

            //UI_Map_pbx.Image = (Bitmap)Bitmap.FromFile(".\\map.jpg");

            //UI_Map_gmap.Dock = DockStyle.Fill;
            UI_Map_gmap.Position = new PointLatLng(53.0000, -111.0000);
            UI_Map_gmap.Zoom = 10;



        }

        private void _usernameBox_TextChanged(object sender, EventArgs e)
        {
            if (_uEnBox.Checked) 
            {
                SLGData.uid = _usernameBox.Text;

            }
            if (_pEnBox.Checked)
            {
                SLGData.password = _passBox.Text;

            }
        }
        async private void UI_SendData_btn_Click(object sender, EventArgs e)
        {
            /*microsoft copilot's dummy data
             * var postData = new Dictionary<string, string>
        {
            { "uid", "22345" },
            { "password", "dummyPassword" },
            { "dailySteps", "5000" },
            { "weeklySteps", "33000" },
            { "lifeSteps", "1000000" },
            { "friendship", "5" },
            { "difficulty", "2" },
            { "evolution", "1" }
        };*/
            
            Dictionary<string, string> postData = new Dictionary<string, string> { 
                {"uid", SLGData.uid},
                {"password",SLGData.password}, 
                {"dailySteps", SLGData.dailySteps.ToString()},
                {"weeklySteps", SLGData.WeeklySteps.ToString()},
                {"lifeSteps", SLGData.lifeSteps.ToString()},
                {"friendship", SLGData.friendship.ToString() },
                {"difficulty", SLGData.difficilty.ToString() },
                {"evolution", SLGData.evolution.ToString()}
            };
            HttpClient client = new HttpClient();
            var response = await client.PostAsync("https://thor.cnt.sast.ca/~sillylittleguy/service/insertmainSave.php", new FormUrlEncodedContent(postData));
            string data = await response.Content.ReadAsStringAsync();
        }

        private void Port11_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadLine();

            parsed = DataParsing(data);
            int dSteps;
            int wSteps;
            int lSteps;
            int friend;
            int diff;
            int evo;
            
            int.TryParse(parsed["dailySteps"], out dSteps);
            int.TryParse(parsed["weeklySteps"], out wSteps);
            int.TryParse(parsed["lifeSteps"], out lSteps);
            int.TryParse(parsed["friendship"], out friend);
            int.TryParse(parsed["difficulty"], out diff);
            int.TryParse(parsed["evolution"], out evo);
            try
            {
                SLGData = new SillyLittleData("default", "default", dSteps, wSteps, lSteps, friend, diff, evo);
            }
            catch(Exception ex)
            {
                //probably want a universal error box/message box
                Debug.WriteLine(ex.Message);
            }
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
                        //UI_PetStats_lbx.Items.Clear();
                        //UI_PetStats_lbx.Items.Add("No Data Provided");
                    }
                    CheckPortOpenSecond = 2;
                }
                    
            }
            else
            {
                //UI_PetStats_lbx.Items.Clear();
                foreach (KeyValuePair<string, string> petData in parsed)
                {
                    //UI_PetStats_lbx.Items.Add($"{petData.Key} : {petData.Value}");
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
