using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [Serializable]
    public class OMAttributeBase : AttributeBase
    {
        public object Value { get; set; }
    }

}
