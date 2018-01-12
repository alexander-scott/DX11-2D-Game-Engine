using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SimpleSampleEditor
{
    public partial class Form1 : Form
    {
        public string ResoucesPath = "C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Resources";

        public Form1()
        {
            InitializeComponent();
            this.FormClosing += this.Form1_FormClosing;

            panel1.Click += new System.EventHandler(PanelMouseClick);
            panel1.MouseMove += new MouseEventHandler(PanelMouseMove);
            this.Controls.Add(this.panel1);

            this.KeyPreview = true;
            this.KeyDown += new KeyEventHandler(KeyboardKeyDown);
            this.KeyUp += new KeyEventHandler(KeyboardKeyUp);
        }

        private void KeyboardKeyUp(object sender, KeyEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void KeyboardKeyDown(object sender, KeyEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void PanelMouseMove(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
        }

        private void PanelMouseClick(object sender, EventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Engine.InitD3D(panel1.Handle, panel1.Width, panel1.Height, ResoucesPath);
            Engine.RenderFrame();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Engine.CleanD3D();
        }
    }

    public class Engine
    {
        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitD3D(IntPtr window, int Width, int Height, string filePath);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RenderFrame();

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CleanD3D();

        [DllImport("SimpleSample.dll")]
        public static extern int Add(int a, int b);
    }
}
