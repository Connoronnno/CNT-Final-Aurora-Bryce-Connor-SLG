//PROGRAMMERS BLOCK EVENTUALLY

/*
References:

GMap.Net guide: https://www.youtube.com/watch?v=to16P4N-rqg&t=288s

 
 */


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
        public SerialPort port = new SerialPort("COM9"); // initilize the serial port class
        public Dictionary<string, string> parsed = null;

        int CheckPortOpenSecond = 2;

        // Map Object
        GMap.NET.WindowsForms.GMapControl gMap;

        bool work=false;
        public PetMenu()
        {
            InitializeComponent();
            Shown += PetMenu_Shown;
            
        }

        private void PetMenu_Shown(object sender, EventArgs e)
        {
            work = true;
            UI_SendData_btn.Click += UI_SendData_btn_Click;
            _usernameBox.TextChanged += _usernameBox_TextChanged;
            _passBox.TextChanged += _usernameBox_TextChanged;
            //set up serial port to match segger's settings
            port.BaudRate = 115200;
            port.Parity = Parity.None;
            port.StopBits = StopBits.One;
            port.DataBits = 8;
            port.Handshake = Handshake.None;

            //port11.ReadTimeout = 499;
            //port11.WriteTimeout = 499;
            port.DataReceived += Port11_DataReceived;

            //open the serial port and wait for data to be recieved
            try
            {
                port.Open();
            }
            catch
            {
                //UI_PetStats_lbx.Items.Add("No Data Provided");
            }


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

            // GMap setup options
            gMap = new GMap.NET.WindowsForms.GMapControl();
            gMap.MapProvider = GMap.NET.MapProviders.GMapProviders.GoogleSatelliteMap;
            gMap.Dock = DockStyle.Fill;
            gMap.MapProvider = GMap.NET.MapProviders.BingMapProvider.Instance;
            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerAndCache;
            gMap.ShowCenter = false;
            gMap.MinZoom = 1;
            gMap.MaxZoom = 20;

            gMap.Position = new PointLatLng(53.5684, -113.5019); // start location at nait

            // Update UI to show map
            splitContainer1.Panel2.Controls.Add(gMap);
            gMap.Zoom = 15;
            gMap.Update();
            gMap.Refresh();

            //Add Nait as a default location (Probably remove later?)
            GMapAddPoint(53.5684, -113.5019, GMap.NET.WindowsForms.Markers.GMarkerGoogleType.red_pushpin, "NAIT_Default");
            AddPointsToListbox();

            DisplaySLGData();
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
            DataParsing("(lat:12.34),(lon:12.34),(lat:12.34),(lon:12.34),(lat:12.34),(lon:12.34),(lat:12.34),(lon:12.34)");
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
            response = await client.PostAsync("https://thor.cnt.sast.ca/~sillylittleguy/service/clearPositions.php", new FormUrlEncodedContent(postData));
            data = await response.Content.ReadAsStringAsync();
            foreach(PointLatLng p in SLGData.locations) 
            {
                postData = new Dictionary<string, string> { {"uid", SLGData.uid}, { "lat", p.Lat.ToString() }, { "lon", p.Lng.ToString() } };
                response = await client.PostAsync("https://thor.cnt.sast.ca/~sillylittleguy/service/insertpositions.php", new FormUrlEncodedContent(postData));
                data = await response.Content.ReadAsStringAsync();
            }
        }

        private void Port11_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (work)
            {
                try
                {
                    SerialPort sp = (SerialPort)sender;
                    string data = sp.ReadLine();

                    parsed = DataParsing(data);
                    /*if (parsed.ContainsKey("lat"))
                    {
                        PointLatLng ltlng = new PointLatLng();
                        float temp;
                        float.TryParse(parsed["lat"], out temp);
                        ltlng.Lat = temp;
                        float.TryParse(parsed["lon"], out temp);
                        ltlng.Lat = temp;
                        SLGData.locations.Add(ltlng);
                    }*/
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
                        SLGData.uid = parsed["uid"];
                        SLGData.password = parsed["password"];
                        SLGData.lifeSteps = lSteps;
                        SLGData.WeeklySteps = wSteps;
                        SLGData.dailySteps = dSteps;
                        SLGData.friendship = friend;
                        SLGData.difficilty = diff;
                        SLGData.evolution = evo;
                    }
                    catch (Exception ex)
                    {
                        //probably want a universal error box/message box
                        Debug.WriteLine(ex.Message);
                    }
                    DisplaySLGData();
                    GMapAddPoint(SLGData.locations[0].Lat, SLGData.locations[0].Lng, GMap.NET.WindowsForms.Markers.GMarkerGoogleType.blue, "ha");

                }
                catch 
                {
                
                }
            }
        }

        private Dictionary<string, string> DataParsing(string rawData)
        {
            Dictionary<string, string> parsed = new Dictionary<string, string>();
            
            PointLatLng loc = new PointLatLng();
            float temp;
            string[] seperations = rawData.Split(',');
            loc.Lat = 200000;
            loc.Lng = 200000;
            SLGData.locations.Clear();
            foreach (string dataLine in seperations)
            {
                if (!dataLine.Contains("lon") && !dataLine.Contains("lat"))
                {
                    string cleanedData = dataLine.Replace('(', ' ').Replace(')', ' ').Trim();
                    string[] values = cleanedData.Split(':');

                    parsed.Add(values[0], values[1]);
                }
                else 
                {
                    if (dataLine.Contains("lat")) 
                    {
                        string cleanedData = dataLine.Replace('(', ' ').Replace(')', ' ').Trim();
                        string[] values = cleanedData.Split(':');
                        float.TryParse(values[1], out temp);
                        loc.Lat = temp;
                    }
                    if (dataLine.Contains("lon")) 
                    {
                        string cleanedData = dataLine.Replace('(', ' ').Replace(')', ' ').Trim();
                        string[] values = cleanedData.Split(':');
                        float.TryParse(values[1], out temp);
                        loc.Lng = temp;
                    }
                    if (loc.Lat !=200000 && loc.Lng != 200000) 
                    {   
                        SLGData.locations.Add(loc);
                        loc.Lat = 200000;
                        loc.Lng = 200000;
                        
                    }
                }

                
            }

            return parsed;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
            if(!port.IsOpen)
            {
                if (--CheckPortOpenSecond <= 0)
                {
                    try
                    {
                        port.Open();
                    }
                    catch
                    {
                        //UI_PetStats_lbx.Items.Clear();
                        //UI_PetStats_lbx.Items.Add("No Data Provided");
                    }
                    CheckPortOpenSecond = 2;
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


        #region [REGION] GMap Functions

        /// <summary>
        /// Use the given lat and long to create a marker at that point on the GMap control
        /// </summary>
        /// <param name="latitude"> lat of the marker </param>
        /// <param name="longitude"> long of the marker </param>
        /// <param name="markerType"> how the marker will look </param>
        /// <param name="markerName"> name of the marker overlay </param>
        private void GMapAddPoint(double latitude, double longitude, GMap.NET.WindowsForms.Markers.GMarkerGoogleType markerType, string markerName="NewMarker")
        {
            // Create marker overlay to add marker
            var markersOverlay = new GMap.NET.WindowsForms.GMapOverlay(markerName);

            //create marker and add to the overlay
            var marker = new GMap.NET.WindowsForms.Markers.GMarkerGoogle(
                new PointLatLng(latitude, longitude),
                markerType);
            markersOverlay.Markers.Add(marker);
            gMap.Overlays.Add(markersOverlay);

            // Update the UI
            gMap.Update();
            gMap.Refresh();
        }

        /// <summary>
        /// return a list of every point currently stored on the map
        /// </summary>
        /// <returns></returns>
        private List<PointLatLng> GMapGetPoints()
        {
            //grab all points on map
            var overlays = gMap.Overlays;
            List <PointLatLng> points = new List<PointLatLng>();

            //iterate through points and add to the return object
            foreach (var overlay in overlays)
            {
                points.Add(overlay.Markers[0].Position);
            }
            return points;
        }
        /// <summary>
        /// add every point on the GMap to the list box next to it
        /// </summary>
        private void AddPointsToListbox()
        {
            UI_Locations_lbx.Items.Clear();
            foreach (PointLatLng point in GMapGetPoints())
            {
                UI_Locations_lbx.Items.Add($"{point.Lat}, {point.Lng}");
            }
        }

        #endregion


        private void DisplaySLGData()
        {
            if (SLGData == null)
                return;

            UI_LifeSteps_lbl.Text = SLGData.lifeSteps.ToString();
            UI_WeeklySteps_lbl.Text = SLGData.WeeklySteps.ToString();
            UI_DailySteps_lbl.Text = SLGData.dailySteps.ToString();

            UI_Emotion_lbl.Text = SLGData.friendship.ToString();
            if (SLGData.friendship < 90)
            {
                UI_Emotion_lbl.Text += " (Upset)";
            }
            else if (SLGData.friendship > 110)
            {
                UI_Emotion_lbl.Text += " (Happy)";
            }
            else
            {
                UI_Emotion_lbl.Text += " (Neutral)";
            }

            switch (SLGData.evolution)
            {
                case 1:
                    UI_Evolution_lbl.Text = "Young";

                    break;
                case 2:
                    UI_Evolution_lbl.Text = "Teen";

                    break;
                case 3:
                    UI_Evolution_lbl.Text = "Adult";

                    break;
            }

            

        }

        async private void UI_GrabData_btn_Click(object sender, EventArgs e)
        {
            Dictionary<string, string> dataPost = new Dictionary<string, string>();
            dataPost["uid"] = SLGData.uid;

            HttpClient client = new HttpClient();
            var response = await client.PostAsync("https://thor.cnt.sast.ca/~sillylittleguy/service/select.php", new FormUrlEncodedContent(dataPost));
            string data = await response.Content.ReadAsStringAsync();

        }
    }
}
