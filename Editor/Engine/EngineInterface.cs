using System;
using System.Runtime.InteropServices;

namespace SimpleSampleEditor.Engine
{
    class EngineInterface
    {
        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr InitaliseEngine(IntPtr window, int Width, int Height, string filePath);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void StartEditorLoop(IntPtr gamePtr);

        [DllImport("SimpleSample.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void StartUpdateLoop(IntPtr gamePtr);

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
