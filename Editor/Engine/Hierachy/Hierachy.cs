using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SimpleSampleEditor.EditorHierachy
{
    public class HItem
    {
        public int GameObjectID;
        public HItem HierarchyParent;
        public List<HItem> HierarchyChildren;

        public bool Hidden;

        public HItem(int gameObjectID, HItem parent)
        {
            GameObjectID = gameObjectID;
            HierarchyParent = parent;
            HierarchyChildren = new List<HItem>();

            Hidden = false;
        }
    };

    public class Hierachy
    {
        private List<HItem> hierarchyItems = new List<HItem>();

        private ListView listView;

        public Hierachy(ListView lv)
        {
            listView = lv;

            listView.MouseDoubleClick += ItemDoubleClicked;
        }

        private void ItemDoubleClicked(object sender, MouseEventArgs e)
        {
            
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

                HItem itemParent = FindParent((int)hItem.GameObjectParentID);
                HItem item = new HItem((int)hItem.GameObjectID, itemParent);

                if (itemParent != null)
                {
                    itemParent.HierarchyChildren.Add(item);
                }

                hierarchyItems.Add(item);

                listView.Items.Add(new ListViewItem(hItem.GameObjectName, 0));
            }

            SceneInterface.FreeHierarchyMemory(hierarchy);
        }

        private HItem FindParent(int parentID)
        {
            for (int i = 0; i < hierarchyItems.Count; i++)
            {
                if (hierarchyItems[i].GameObjectID == parentID)
                {
                    return hierarchyItems[i];
                }
            }

            return null;
        }
    }
}
