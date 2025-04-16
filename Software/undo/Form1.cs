using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GDIDrawer;

namespace undo
{
    public partial class Form1 : Form
    {
        Bitmap bm;
        List<Color> Palette = new List<Color>();
        List<string> a = new List<string>();
        List<string> b = new List<string>();
        public Form1()
        {
            InitializeComponent();
            AllowDrop = true;
            DragEnter += Form1_DragEnter;
            DragDrop += Form1_DragDrop;
            _process.Click += _process_Click;
            Palette = GetPalette(new Bitmap("../../palette.png"));
        }
        private List<Color> GetPalette(Bitmap pic)
        { 
            HashSet<Color> palette = new HashSet<Color>();
            for (int x = 0; x < pic.Width; x++)
            {
                for (int y = 0; y < pic.Height; y++)
                {
                    palette.Add(pic.GetPixel(x, y));
                }
            }
            return palette.ToList();
        }
        private void _process_Click(object sender, EventArgs e)
        {
            var badColors = new HashSet<Color>();
            a = new List<string>();
            b = new List<string>();
            int count = 0;
            int found = 0;
            int paletteIndex = 0;
            bm.RotateFlip(RotateFlipType.Rotate90FlipX);
            //Creating pallete with unique colours
            if (bm != null)
            {
                //iterate through bitmap
                for (int y = 0; y < bm.Height; y++)
                {
                    
                    for (int x = bm.Width-1; x >=0; x--)
                    {
                        //get pallete index
                        paletteIndex = 0;
                        paletteIndex = Palette.IndexOf(bm.GetPixel(x, y));
                        if (paletteIndex < 0)
                            paletteIndex = 9;

                        //b.Add($"{(int)i}, ");

                        //
                        if (found != paletteIndex)
                        {
                            if (a.Count == 0) a.Add($"{{{found}, {count}}}");
                            
                            else a.Add($"{{{found}, {count+1}}}");
                            
                            found = paletteIndex;
                            count = 0;
                        }
                        else 
                        {
                            count++;
                        }
                    }
                }
                Console.WriteLine(String.Join("\n", badColors));
                a.Add($"{{{found}, {count+1}}}");
                textBox1.AppendText($"{a.Count()}\r\n");
                textBox1.AppendText(String.Join(", ", a) + "\r\n");

                //OutputToImage(textBox1.Text);
            }
        }

        private void Form1_DragDrop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.Copy;
            else
                e.Effect = DragDropEffects.None;

        }


        private void Form1_DragEnter(object sender, DragEventArgs e)
        {
            //get file path
            string path = ((string[])e.Data.GetData(DataFormats.FileDrop)).First();

            //assign and display bitmap
            bm = (Bitmap)Bitmap.FromFile(path);
            UI_PicBox.Image = bm;
        }

        private void OutputToImage(string data)
        {
            // Split into individual items
            string[] groups = data.Split('{');
            List<string> cleaned = new List<string>();
            List<(int, int)> cleanedData = new List<(int, int)>();
            foreach (string item in groups.Skip(1))
            {
                string trimmed = item.Remove(item.Length-3, 3);
                cleaned.Add(trimmed);
            }
            foreach (string item in cleaned)
            {
                string[] values = item.Split(',');
                int.TryParse(values[0].Trim(), out int key);
                int.TryParse(values[1].Trim(), out int value);
                cleanedData.Add((key, value));
            }

            CDrawer canvas = new CDrawer();
            canvas.Scale = 3;
            int xPos = 0;
            int yPos = 0;
            foreach(var i in cleanedData)
            {
                int timesDrawn = i.Item2;
                int curTime = 0;
                while(curTime < timesDrawn)
                {
                    if (xPos >= bm.Width)
                    {
                        xPos = 0;
                        yPos++;
                    }
                    canvas.SetBBScaledPixel(xPos, yPos, Palette[i.Item1]);
                    xPos++;
                    curTime++;
                }
                
            }

                
        }
    }
}
