using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedTest
{
    public class MyObject
    {
        string _str;
        double _d;
        int _i;

        public MyObject()
        {
            _str = "0123456789";
            _d = 41.5;
            _i = 34;
        }
    }

    public class MemoryConsumer
    {
        public static List<MyObject> _objList = new List<MyObject>();

        public static void GrowList(int numOfObjectstoAdd)
        {
            for (int i = 0; i != numOfObjectstoAdd; i++)
                _objList.Add(new MyObject());
        }

        public static void ShrinkList(int numOfObjectstoRemove)
        {
            int x = 0;

            if (_objList.Count == 0)
                return;

            x = _objList.Count - numOfObjectstoRemove - 1;
            for (int i = _objList.Count - 1; i != x; i--)
                _objList.RemoveAt(i);

        }
    }

}
