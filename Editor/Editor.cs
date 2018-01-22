﻿using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SimpleSampleEditor
{
    public partial class Editor : Form
    {
        private string mResoucesPath = "C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Resources";

        /// <summary>
        /// Pointer to the instance of the Game. Used to make sure all calls to the engine use the same instance of the Game
        /// </summary>
        private IntPtr mEngine;

        public Editor()
        {
            InitializeComponent();
            this.FormClosing += this.Form1_FormClosing;
            this.Shown += this.Form1_Shown;

            panel1.MouseDown += new MouseEventHandler(PanelMouseDown);
            panel1.MouseUp += new MouseEventHandler(PanelMouseRelease);
            panel1.MouseMove += new MouseEventHandler(PanelMouseMove);
            this.Controls.Add(this.panel1);

            this.KeyPreview = true;
            this.KeyDown += new KeyEventHandler(KeyboardKeyDown);
            this.KeyUp += new KeyEventHandler(KeyboardKeyUp);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            mEngine = EngineInterface.InitaliseEngine(panel1.Handle, panel1.Width, panel1.Height, mResoucesPath);
            panel1.Focus();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            int numberOfGameObjects = SceneInterface.GetGameObjectCount(mEngine);
            IntPtr hierarchy = SceneInterface.PopulateHierarchyItems(mEngine, numberOfGameObjects);
            int structSize = Marshal.SizeOf(typeof(HierarchyItem));

            List<HierarchyItem> items = new List<HierarchyItem>();
            List<string> listBoxItems = new List<string>();

            for (int i = 0; i < numberOfGameObjects; i++)
            {
                IntPtr data = new IntPtr(hierarchy.ToInt64() + structSize * i);
                HierarchyItem hItem = (HierarchyItem)Marshal.PtrToStructure(data, typeof(HierarchyItem));
                items.Add(hItem);
                listBoxItems.Add(hItem.GameObjectName);
            }

            hierarchyListBox.DataSource = listBoxItems;

            SceneInterface.FreeHierarchyMemory(hierarchy);

            EngineInterface.StartEditorLoop(mEngine);  
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            EngineInterface.PlayPressed(mEngine);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            EngineInterface.CleanD3D(mEngine);
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
