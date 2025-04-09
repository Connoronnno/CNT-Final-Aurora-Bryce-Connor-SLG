using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
<<<<<<< Updated upstream
=======
using System.Drawing.Imaging;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
        HashSet<Color> HashPalette = new HashSet<Color>();
        Dictionary<Color, int> DictPalette = new Dictionary<Color,int>();
>>>>>>> Stashed changes
        List<string> a = new List<string>();
        List<string> b = new List<string>();
        public Form1()
        {
            InitializeComponent();
            AllowDrop = true;
            DragEnter += Form1_DragEnter;
            DragDrop += Form1_DragDrop;
            _process.Click += _process_Click;
<<<<<<< Updated upstream
        }

        private void MakePalette()
        { 

        }

=======

            //BLACK
            Palette.Add(Color.FromArgb(0,0,0,0));
            //WHITE
            Palette.Add(Color.FromArgb(255, 255, 255));
            //BLACK
            Palette.Add(Color.FromArgb(0,46,34, 47));
            //OUTLINE
            Palette.Add(Color.FromArgb(62, 53, 70));
            //YELLOW
            Palette.Add(Color.FromArgb(213, 224, 75));
            //DARK GREEN BLUE
            Palette.Add(Color.FromArgb(22, 90, 76));
            //BODY GREEN
            Palette.Add(Color.FromArgb(145, 219, 105));
            //LIGHT GREEN BLUE
            Palette.Add(Color.FromArgb(35, 144, 99));
            //GREY OUTLINE
            Palette.Add(Color.FromArgb(127, 112, 138));
            //GREY GREEN
            Palette.Add(Color.FromArgb(84, 126, 100));
            //GREY
            Palette.Add(Color.FromArgb(155, 171, 178));
        }
>>>>>>> Stashed changes
        private void _process_Click(object sender, EventArgs e)
        {
            a = new List<string>();
            b = new List<string>();
            int count = 0;
            int found = 0;
<<<<<<< Updated upstream
            int palleteIndex = 0;
=======
            int paletteIndex = 0;

>>>>>>> Stashed changes

            //Creating pallete with unique colours
            if (bm != null)
            {
<<<<<<< Updated upstream
                for (int y = 0; y < bm.Height; y++)
                {
                    for (int x = 0; x < bm.Width; x++)
                    {
                        if (!Palette.Contains(bm.GetPixel(x, y))) Palette.Add(bm.GetPixel(x, y));
                    }
                }
                //iterate through bitmap
                for (int y = 0; y < bm.Height; y++)
                {
                    
                    for (int x = bm.Width-1; x >=0; x--)
                    {
                        //get pallete index
                        palleteIndex = 0;
                        foreach(Color c in Palette) 
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
=======
                bm.RotateFlip(RotateFlipType.Rotate90FlipX);
                //for (int y = 0; y < bm.Height; y++)
                //{
                    //for (int x = 0; x < bm.Width; x++)
                    //{
                      //  HashPalette.Add(bm.GetPixel(x, y));
                    //}
                //}
                Console.WriteLine(String.Join(",", Palette));
                paletteIndex = 0;
                //foreach (Color c in HashPalette)
                //{
                //   while (DictPalette.ContainsValue(paletteIndex))
                {
                    //        paletteIndex +=1;
                    //   }
                    //    DictPalette.Add(c, paletteIndex);
                    //    paletteIndex += 1;
                    //}
                    //iterate through bitmap
                    for (int y = 0; y < bm.Height; y++)
                    {

                        for (int x = bm.Width - 1; x >= 0; x--)
                        {
                            //get palette index
                            if (Palette.Contains(bm.GetPixel(x, y)))
                            {
                                paletteIndex = Palette.IndexOf(bm.GetPixel(x, y));
                            }

                            //b.Add($"{(int)i}, ");

                            //
                            if (found != paletteIndex)
                            {
                                if (a.Count == 0) a.Add($"{{{found}, {count}}}, ");
                                else a.Add($"{{{found}, {count + 1}}}, ");

                                found = paletteIndex;
                                count = 0;
                            }
                            else
                            {
                                count++;
                            }
                        }
                    }
                    a.Add($"{{{found}, {count + 1}}}, ");
                    foreach (string pixels in a)
                    {
                        textBox1.AppendText(pixels);
                    }
                    //foreach (Color pixels in Pallette)
                    //{
                    //    textBox1.AppendText(pixels);
                    //}
                    Console.WriteLine(a.Count);
                    OutputToImage(textBox1.Text);
                }
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
                    if (xPos >= 64)
=======
                    if (xPos >= bm.Width)
>>>>>>> Stashed changes
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
