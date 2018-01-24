using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SimpleSampleEditor.EditorHierachy
{
    public class HItem
    {
        public string GameObjectName;
        public int GameObjectID;
        public HItem HierarchyParent;
        public List<HItem> HierarchyChildren;

        public bool Hidden;

        public HItem(string name,int gameObjectID)
        {
            GameObjectName = name;
            GameObjectID = gameObjectID;
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
            listView.Items.Clear();

            List<string> listBoxItems = new List<string>();
            for (int i = 0; i < numberOfGameObjects; i++)
            {
                // Parse the data recieved from the engine
                IntPtr data = new IntPtr(hierarchy.ToInt64() + structSize * i);
                HierarchyItem hItem = (HierarchyItem)Marshal.PtrToStructure(data, typeof(HierarchyItem));

                // Create the item that will be stored in the hierarchy
                HItem item = new HItem(hItem.GameObjectName, (int)hItem.GameObjectID);

                // Check if the item has a parent
                HItem itemParent = FindParent((int)hItem.GameObjectParentID);
                if (itemParent != null)
                {
                    // If the item has a parent, setup the parent and child data
                    item.HierarchyParent = itemParent;
                    item.Hidden = true;
                    itemParent.HierarchyChildren.Add(item);
                }
                else // Else add it to the visibile list in the hierarchy
                {
                    listView.Items.Add(new ListViewItem(hItem.GameObjectName, 0));
                }

                // Cache the item
                hierarchyItems.Add(item);
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
