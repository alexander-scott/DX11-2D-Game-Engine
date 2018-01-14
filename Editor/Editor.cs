using System;
using System.Drawing;
using System.Windows.Forms;

namespace SimpleSampleEditor
{
    public partial class Editor : Form
    {
        private string mResoucesPath = "C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Resources";

        /// <summary>
        /// Pointer to the instance of the Game. Used to make sure all calls to the engine use the same instance of the Game
        /// </summary>
        private IntPtr mGame;

        private bool mGameStarted = false;

        public Editor()
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
            if (!mGameStarted)
                return;

            Point point = panel1.PointToClient(Cursor.Position);
            EngineInterface.MouseClick(mGame, point.X, point.Y);
        }

        private void PanelMouseRelease(object sender, MouseEventArgs e)
        {
            if (!mGameStarted)
                return;

            Point point = panel1.PointToClient(Cursor.Position);
            EngineInterface.MouseRelease(mGame, point.X, point.Y);
        }

        private void PanelMouseMove(object sender, MouseEventArgs e)
        {
            if (!mGameStarted)
                return;

            Point point = panel1.PointToClient(Cursor.Position);
            EngineInterface.MouseMove(mGame, point.X, point.Y);
        }

        private void KeyboardKeyUp(object sender, KeyEventArgs e)
        {
            if (!mGameStarted)
                return;

            EngineInterface.KeyUp(mGame, e.KeyValue);
        }

        private void KeyboardKeyDown(object sender, KeyEventArgs e)
        {
            if (!mGameStarted)
                return;

            EngineInterface.KeyDown(mGame, e.KeyValue);
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            if (mGameStarted)
                return;

            mGameStarted = true;

            mGame = EngineInterface.InitD3D(panel1.Handle, panel1.Width, panel1.Height, mResoucesPath);
            panel1.Focus();

            EngineInterface.StartUpdateLoop(mGame);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!mGameStarted)
                return;

            EngineInterface.CleanD3D(mGame);
        }
    }
}
