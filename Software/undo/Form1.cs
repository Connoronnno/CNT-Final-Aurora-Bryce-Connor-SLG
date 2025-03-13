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
        List<Color> Pallette = new List<Color>();
        List<string> a = new List<string>();
        List<string> b = new List<string>();
        public Form1()
        {
            InitializeComponent();
            AllowDrop = true;
            DragEnter += Form1_DragEnter;
            DragDrop += Form1_DragDrop;
            _process.Click += _process_Click;
        }

        private void _process_Click(object sender, EventArgs e)
        {
            a = new List<string>();
            b = new List<string>();
            int count = 0;
            int found = 0;
            int palleteIndex = 0;

            //Creating pallete with unique colours
            if (bm != null)
            {
                for (int y = 0; y < bm.Height; y++)
                {
                    for (int x = 0; x < bm.Width; x++)
                    {
                        if (!Pallette.Contains(bm.GetPixel(x, y))) Pallette.Add(bm.GetPixel(x, y));
                    }
                }
                //iterate through bitmap
                for (int y = 0; y < bm.Height; y++)
                {
                    
                    for (int x = bm.Width-1; x >=0; x--)
                    {
                        //get pallete index
                        palleteIndex = 0;
                        foreach(Color c in Pallette) 
                        {
                            if (bm.GetPixel(y, x) == c) 
                                break;
                            palleteIndex++;
                        }

                        //b.Add($"{(int)i}, ");

                        //
                        if (found != palleteIndex)
                        {
                            if (a.Count == 0) a.Add($"{{{found}, {count}}}, ");
                            else a.Add($"{{{found}, {count+1}}}, ");
                            
                            found = palleteIndex;
                            count = 0;
                        }
                        else 
                        {
                            count++;
                        }
                    }
                }
                a.Add($"{{{found}, {count+1}}}, ");
                foreach (string pixels in a) 
                {
                    textBox1.AppendText(pixels);
                }
                //foreach (Color pixels in Pallette)
                //{
                //    textBox1.AppendText(pixels);
                //}

                OutputToImage(textBox1.Text);
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
                    if (xPos >= 64)
                    {
                        xPos = 0;
                        yPos++;
                    }
                    canvas.SetBBScaledPixel(xPos, yPos, Pallette[i.Item1]);
                    xPos++;
                    curTime++;
                }
                
            }

                
        }
    }
}
