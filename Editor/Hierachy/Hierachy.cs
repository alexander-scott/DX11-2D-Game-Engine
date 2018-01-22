using SimpleSampleEditor.Engine;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace SimpleSampleEditor.EditorHierachy
{
    public class Hierachy
    {
        List<HierarchyItem> hierarchyItems = new List<HierarchyItem>();

        public List<string> CreateHierachyList(IntPtr engine)
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
            }

            SceneInterface.FreeHierarchyMemory(hierarchy);

            return listBoxItems;
        }
    }
}
