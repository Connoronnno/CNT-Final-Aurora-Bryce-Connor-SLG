using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
            char count = (char)0;
            char found = (char)0;
            char i = (char)0;
            if (bm != null)
            {
                for (int y = 0; y < bm.Height; y++)
                {
                    for (int x = 0; x < bm.Width; x++)
                    {
                        if (!Pallette.Contains(bm.GetPixel(x, y))) Pallette.Add(bm.GetPixel(x, y));
                    }
                }
                for (int y = 0; y < bm.Height; y++)
                {
                    for (int x = 0; x < bm.Width; x++)
                    {
                        
                        i = (char)0;
                        foreach(Color c in Pallette) 
                        {
                            if (c == bm.GetPixel(x, y)) break;
                            i++;
                        }
                        //b.Add($"{(int)i}, ");
                        if (found != i)
                        {
                            found = i;
                            a.Add($"{{{(int)found}, {((int)count)+1}}}, ");
                            count = (char)0;
                        }
                        else 
                        {
                            count++;
                        }
                    }
                }
                foreach (string pixels in a) 
                {
                    textBox1.AppendText(pixels);
                }
                foreach (Color pixels in Pallette)
                {
                    textBox1.AppendText(pixels);
                }
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
    }
}
