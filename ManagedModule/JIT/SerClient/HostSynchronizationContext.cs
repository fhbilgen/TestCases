using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    public interface IHostSyncronizationContext
    {
        string Service { get; }

        string Operation { get; }

        string OperationKey { get; }

        Exception ContextException { get; }

        bool HasException { get; }
    }


    [Serializable]
    public class HostSyncronizationContext : IHostSyncronizationContext, ICloneable, IDisposable
    {
        public string Service { get; private set; }

        public string Operation { get; private set; }

        public string OperationKey
        {
            get
            {
                return string.Format("{0}.{1}", Service, Operation);
            }
        }

        public Exception ContextException { get; private set; }

        public bool HasException
        {
            get
            {
                return ContextException != null;
            }
        }

        public static IHostSyncronizationContext Current
        {
            get
            {
                return CallerInformationInitializer.HostSyncronizationContext;
            }
        }

        private HostSyncronizationContext(string service, string operation, Exception contextException, bool autoInitilize)
        {
            Service = service;
            Operation = operation;
            ContextException = contextException;
            if (autoInitilize)
            {
                if (CallerInformationInitializer.HostSyncronizationContext != null)
                {
                    throw new NotSupportedException("Nested HostSyncronizationContext is not supported.");
                }
                CallerInformationInitializer.HostSyncronizationContext = this;
            }
        }

        internal HostSyncronizationContext(string service, string operation, Exception contextException)
            : this(service, operation, contextException, true)
        {
        }

        internal HostSyncronizationContext(string service, string operation)
            : this(service, operation, null)
        {
        }

        public object Clone()
        {
            return new HostSyncronizationContext(Service, Operation, ContextException, false);
        }

        public void Dispose()
        {
            CallerInformationInitializer.HostSyncronizationContext = null;
        }
    }
}
