using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SillyLittleGuyHD
{
    public partial class Form1 : Form
    {
        public SerialPort port11 = new SerialPort("COM11"); // initilize the serial port class

        public Dictionary<string, string> parsed = null;
        public Form1()
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
            port11.Open();
            port11.DataReceived += Port11_DataReceived;

            timer1.Start();
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
            UI_List_lbx.Items.Clear();
            foreach (KeyValuePair<string, string> petData in parsed)
            {
                UI_List_lbx.Items.Add($"{petData.Key} : {petData.Value}");
            }
        }
    }
}
