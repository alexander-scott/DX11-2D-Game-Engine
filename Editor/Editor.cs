using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using SimpleSampleEditor.EditorHierachy;

namespace SimpleSampleEditor
{
    public partial class Editor : Form
    {
        private string mResoucesPath = "C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Resources";

        /// <summary>
        /// Pointer to the instance of the Game. Used to make sure all calls to the engine use the same instance of the Game
        /// </summary>
        private IntPtr mEngine;

        private Hierachy mHierachy;

        public Editor()
        {
            InitializeComponent();
            this.FormClosing += this.EditorClosing;
            this.Shown += this.EditorLoaded;

            panel1.MouseDown += new MouseEventHandler(PanelMouseDown);
            panel1.MouseUp += new MouseEventHandler(PanelMouseRelease);
            panel1.MouseMove += new MouseEventHandler(PanelMouseMove);
            this.Controls.Add(this.panel1);

            this.KeyPreview = true;
            this.KeyDown += new KeyEventHandler(KeyboardKeyDown);
            this.KeyUp += new KeyEventHandler(KeyboardKeyUp);

            mHierachy = new Hierachy();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            mEngine = EngineInterface.InitaliseEngine(panel1.Handle, panel1.Width, panel1.Height, mResoucesPath);
            panel1.Focus();
        }

        private void EditorLoaded(object sender, EventArgs e)
        {
            hierarchyListBox.DataSource = mHierachy.CreateHierachyList(mEngine);

            EngineInterface.StartEditorLoop(mEngine);  
        }

        private void EditorClosing(object sender, FormClosingEventArgs e)
        {
            EngineInterface.CleanD3D(mEngine);
        }

        private void PlayClicked(object sender, EventArgs e)
        {
            EngineInterface.PlayStarted(mEngine);
            hierarchyListBox.DataSource = mHierachy.CreateHierachyList(mEngine); // Update hierarchy
        }

        #region Basic Input

        private void PanelMouseDown(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);

            if (e.Button == MouseButtons.Left)
                EngineInterface.LeftMouseClick(mEngine, point.X, point.Y);
            else
                EngineInterface.RightMouseClick(mEngine, point.X, point.Y);
        }

        private void PanelMouseRelease(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);

            if (e.Button == MouseButtons.Left)
                EngineInterface.LeftMouseRelease(mEngine, point.X, point.Y);
            else
                EngineInterface.RightMouseRelease(mEngine, point.X, point.Y);
        }

        private void PanelMouseMove(object sender, MouseEventArgs e)
        {
            Point point = panel1.PointToClient(Cursor.Position);
            EngineInterface.MouseMove(mEngine, point.X, point.Y);
        }

        private void KeyboardKeyUp(object sender, KeyEventArgs e)
        {
            EngineInterface.KeyUp(mEngine, e.KeyValue);
        }

        private void KeyboardKeyDown(object sender, KeyEventArgs e)
        {
            EngineInterface.KeyDown(mEngine, e.KeyValue);
        }

        #endregion
    }
}
