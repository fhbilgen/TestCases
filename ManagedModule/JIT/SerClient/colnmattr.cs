using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [AttributeUsage(AttributeTargets.Property, AllowMultiple = false)]
    public sealed class ColumnNameAttribute : Attribute
    {
        public string ColumnName { get; set; }

        public ColumnNameAttribute(string columnName)
        {
            ColumnName = columnName;
        }
    }
}
