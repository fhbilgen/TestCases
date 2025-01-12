using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    public interface IDataTransferObject
    {
        BaseDataTransferObject Copy();
    }

}
