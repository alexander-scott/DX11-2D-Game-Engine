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
        // HARDCODED IS BAD
        string ResoucesPath = "C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Resources";

        // Pointer to the instance of the Game. Used to make sure all calls to the engine use the same instance of the Game
        IntPtr GamePointer;

        public Form1()
        {
            InitializeComponent();
            this.FormClosing += this.Form1_FormClosing;

            panel1.MouseDown += new MouseEventHandler(PanelMouseDown);
            panel1.MouseUp += new MouseEventHandler(PanelMouseRelease);
            panel1.MouseMove += new MouseEventHandler(PanelMouseMove);
            this.Controls.Add(this.panel1);

            this.KeyPreview = true;
            this.KeyDown += new KeyEventHandler(KeyboardKeyDown);
            this.KeyUp += new KeyEventHandler(KeyboardKeyUp);
        }

        private void PanelMouseDown(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
            Engine.MouseClick(GamePointer, point.X, point.Y);
        }

        private void PanelMouseRelease(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
            Engine.MouseRelease(GamePointer, point.X, point.Y);
        }

        private void PanelMouseMove(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
            Engine.MouseMove(GamePointer, point.X, point.Y);
        }

        private void KeyboardKeyUp(object sender, KeyEventArgs e)
        {
            Engine.KeyUp(GamePointer, e.KeyValue);
        }

        private void KeyboardKeyDown(object sender, KeyEventArgs e)
        {
            Engine.KeyDown(GamePointer, e.KeyValue);
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            GamePointer = Engine.InitD3D(panel1.Handle, panel1.Width, panel1.Height, ResoucesPath);
            Engine.StartUpdateLoop(GamePointer);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Engine.CleanD3D(GamePointer);
        }
    }

    public class Engine
    {
        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr InitD3D(IntPtr window, int Width, int Height, string filePath);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr StartUpdateLoop(IntPtr gamePtr);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CleanD3D(IntPtr gamePtr);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseClick(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseRelease(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseMove(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyDown(IntPtr gamePtr, int keyCode);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyUp(IntPtr gamePtr, int keyCode);
    }
}
