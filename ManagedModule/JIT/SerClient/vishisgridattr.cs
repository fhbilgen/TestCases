using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{

    [AttributeUsage(AttributeTargets.Property, AllowMultiple = false)]
    public sealed class IsVisibleInHistoryGridAttribute : Attribute
    {
        public bool IsVisibleInHistoryGrid { get; set; }

        public IsVisibleInHistoryGridAttribute(bool isVisibleInHistoryGrid)
        {
            IsVisibleInHistoryGrid = isVisibleInHistoryGrid;
        }
    }

}
