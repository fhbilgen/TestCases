using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{


    public interface IOperationActionContext
    {
        string AttachedOperation { get; }

        Exception ContextException { get; }

        bool HasException { get; }
    }



    [Serializable]
    public class OperationActionContext : IOperationActionContext, ICloneable, IDisposable
    {
        public string AttachedOperation { get; private set; }

        public Exception ContextException { get; private set; }

        public bool HasException
        {
            get
            {
                return ContextException != null;
            }
        }

        public static IOperationActionContext Current
        {
            get
            {
                return CallerInformationInitializer.OperationActionContext;
            }
        }

        private OperationActionContext(string attachedOperation, Exception contextException, bool autoInitilize)
        {
            AttachedOperation = attachedOperation;
            ContextException = contextException;
            if (autoInitilize)
            {
                if (CallerInformationInitializer.OperationActionContext != null)
                {
                    throw new NotSupportedException("Nested OperationActionContext is not supported.");
                }
                CallerInformationInitializer.OperationActionContext = this;
            }
        }

        internal OperationActionContext(string attachedOperation, Exception contextException)
            : this(attachedOperation, contextException, true)
        {
        }

        internal OperationActionContext(string attachedOperation)
            : this(attachedOperation, null)
        {
        }

        public object Clone()
        {
            return new OperationActionContext(AttachedOperation, ContextException, false);
        }

        public void Dispose()
        {
            CallerInformationInitializer.OperationActionContext = null;
        }
    }

}
