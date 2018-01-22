using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SimpleSampleEditor.EditorHierachy
{
    public class Hierachy
    {
        private List<HierarchyItem> hierarchyItems = new List<HierarchyItem>();

        private ListView listView;

        public Hierachy(ListView lv)
        {
            listView = lv;
        }

        public void CreateHierachyList(IntPtr engine)
        {
            int numberOfGameObjects = SceneInterface.GetGameObjectCount(engine);
            IntPtr hierarchy = SceneInterface.PopulateHierarchyItems(engine, numberOfGameObjects);
            int structSize = Marshal.SizeOf(typeof(HierarchyItem));

            hierarchyItems.Clear();

            List<string> listBoxItems = new List<string>();
            for (int i = 0; i < numberOfGameObjects; i++)
            {
                IntPtr data = new IntPtr(hierarchy.ToInt64() + structSize * i);
                HierarchyItem hItem = (HierarchyItem)Marshal.PtrToStructure(data, typeof(HierarchyItem));
                hierarchyItems.Add(hItem);
                listBoxItems.Add(hItem.GameObjectName);

                ListViewItem item = new ListViewItem(hItem.GameObjectName, 0);
                listView.Items.Add(item);
            }

            SceneInterface.FreeHierarchyMemory(hierarchy);

            //return listBoxItems;
        }
    }
}
